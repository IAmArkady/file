#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Train
{
       char destination[30];
       char number_train[10];
       char type_train[20];
       char depature_time[6];
       char travel_time[6];
};
  
typedef struct Train DataType;

struct List
{
       DataType data;
       struct List * next;
};

typedef struct List * list;

DataType input_train (void);
list read_file (char * filetrain);
list add (list, DataType);
int write_file (char * filetrain, list);
void delete_list (list);
void edit (list);
void list_of_trains (list);
void search (list begin);
list del (list);
void show (list);

int main (void)
{
    char file[50];
    char menu;
    list train = NULL;
    puts ("Enter the file name");
    gets (file);
    train = read_file (file);
    do
    {
       system ("CLS");
       puts ("1. Add");
       puts ("2. Redact record");
       puts ("3. list of trains");
       puts ("4. Show");
       puts ("5. Search");
       puts ("6. Delete record");
       puts ("7. Exit");
       menu = getchar(); getchar(); 
       switch (menu)
       {
              case '1': train = add (train, input_train()); break;
              case '2': edit (train); break;
              case '3': list_of_trains (train); break;
              case '4': show (train); break;
              case '5': search (train); break;
              case '6': train = del (train);
       }
    }
    while (menu!='7');
    if (write_file (file, train))
        puts ("File saved");
    else
    	puts ("File not saved");
    delete_list (train);
    return 0;
}

DataType input_train (void)
{
    DataType train;
    puts ("destination");
    gets (train.destination);
    puts ("number train");
    gets (train.number_train);
    puts ("type train");
    gets (train.type_train);
    puts ("depature time");
    gets (train.depature_time);
    puts ("travel time");
    gets (train.travel_time); 
	getchar();
    return train;
}

list add (list begin, DataType Train)
{
    list temp = (list) malloc (sizeof(struct List));
    temp->data = Train;
    temp->next = begin;
    return temp;
}

list read_file (char * filetrain)
{
    FILE * f;
    DataType train;
    list begin=NULL, cur;
    if ((f = fopen (filetrain, "rb")) == NULL)
    {
        perror ("Error open file");
        getchar();
        return begin;
    }
    if (fread(&train, sizeof(train), 1, f))
        begin = add (begin, train);
    else
        return NULL;
    cur = begin;
    while (fread(&train, sizeof(train), 1, f))
    {
        cur->next = add (cur->next, train);
        cur = cur->next;
	}
    fclose(f);
    return begin;
}

void delete_list (list begin)
{
    list temp = begin;
    while (temp)
    {
        begin = temp->next;
        free (temp);
        temp = begin;
    }
}

int write_file (char * filetrain, list begin)
{
    FILE * f;
    if ((f = fopen (filetrain, "wb")) == NULL)
    {
        perror ("Error create file");
        getchar();
        return 0;
    }
    while (begin)
    {
        if (fwrite (&begin->data, sizeof(DataType), 1, f))
            begin = begin->next;
        else
        	return 0;
    }
    return 1;
}

void print_data (struct Train Train)
{
    printf ("destination :%s\n number train : %s\n type train : %s\n depature time : %s\n travel time : %s\n", Train.destination, 
             Train.number_train, Train.type_train, Train.depature_time, Train.travel_time);
}

void edit (list cur)
{

     int n, k=1;
     char yes;
     system ("CLS");
     if (cur == NULL)
     {
          puts ("List is empty");
          getchar();
          return;
     }
     puts ("Number record for redact?");
     scanf ("%d", &n);
     getchar();
     if (n < 1)
     {
          puts ("Error");
          getchar();
          return;
     }
     while (cur && k < n)
     {
          cur = cur->next;
          k++;
     }
     if (cur == NULL)
     {
          puts ("Error");
          getchar();
          return;
     }
     print_data (cur->data);
     puts ("Redact? (y/n)");
     do
     {
          yes=getchar(); getchar();
	 }
	 while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
     if (yes=='y' || yes=='Y')
          cur->data = input_train();
}

void list_of_trains (list cur)
{
     int k=0; 
     system ("CLS");
     if (cur == NULL)
     {
          puts ("List is empty"); 
          getchar();   
          return;
     }
    
     puts ("|  N |          destination                |   number train   |    type train  |   depature time   |   travel time  |");
     puts ("---------------------------------------------------------------------------------------------------------------------");
     while (cur)
     {
            printf ("|%3d |           %-9s                 |    %10s    |   %10s   |    %5s          |     %5s      |\n", ++k, cur->data.destination, 
                cur->data.number_train, cur->data.type_train, cur->data.depature_time, cur->data.travel_time);
            cur = cur->next;
     }
     puts ("---------------------------------------------------------------------------------------------------------------------");
     getchar();
}
      
void show (list cur)
{
	int k=0;
     char destination[30], time1[5],yes;
     system ("CLS");
        puts ("select your destination");
        scanf("%s",&destination);
        getchar();
        puts ("select the departure time");
        scanf("%s",&time1);
        getchar();
        puts ("|  N |          destination                |   number train   |    type train  |   depature time   |   travel time  |");
        puts ("---------------------------------------------------------------------------------------------------------------------");
        while (cur)
       {
         	if (strcmp (cur->data.destination, destination)==0 && strcmp (cur->data.depature_time, time1)==0)
        	{
                printf ("|%3d |           %-9s                 |    %10s    |   %10s   |    %5s          |     %5s      |\n", ++k, cur->data.destination, 
				  cur->data.number_train, cur->data.type_train, cur->data.depature_time, cur->data.travel_time);
                cur = cur->next;
            }
            else cur = cur->next;
        }
    puts ("---------------------------------------------------------------------------------------------------------------------");
    getchar();
}

void search (list cur)
{
	 char destination[30], type_train[20];
	 char time_1[5];
	 int i,tm2, k=-1,z,min_travel_time=10000;
	 DataType train;
	 char *t;
     system ("CLS");
     if (cur == NULL)
     {
	    puts ("List is empty");
	    getchar();
	    return;
     }
     puts ("destination?");
     scanf ("%s",&destination);
     getchar();
     puts ("type train?");
     scanf ("%s",&type_train);
     getchar();
     while (cur)
     {
        k++;
        if (strcmp (cur->data.destination, destination)==0 && strcmp (cur->data.type_train, type_train)==0)
        {
        	t=cur->data.travel_time;
        	i=0;
        	z=0;
            for (i=0;*(t+i)!='\0';i++)
            {
            	if (*(t+i) !=':')
            	{
           	        time_1[z] = (cur->data.travel_time[i]);
           	        z++;
           	    }
           	    
		    }
		    tm2= atoi (time_1);
		    memset(time_1, '\0', i);
        }
        if (tm2<min_travel_time && tm2>0)
        {
            min_travel_time=tm2;
            train = cur->data;
        }
        cur = cur->next;
     }
     if (min_travel_time == 10000) puts ("Not found");
     print_data (train);
     getchar();
 }

list del (list begin)
{
     int n, k=1;
     char yes;
     list temp, temp1;
     system ("CLS");
     if (begin == NULL)
     {
          puts ("List is empty");
          getchar();
          return NULL;
     }
     puts ("Number record for delete?");
     scanf ("%d", &n);
     getchar();
     if (n < 1)
     {
          puts ("Error");
          getchar();
          return begin;
     }
     if (n == 1) 
     {
          print_data (begin->data);
          puts ("Delete? (y/n)");
          do
          {
             yes=getchar(); getchar();
		  }
          while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
          if (yes=='y' || yes=='Y')
          {
               temp = begin->next;
               free (begin);
               return temp;
          }
          else return begin;
     }
     if (begin->next == NULL && n > 1)
     {
          puts ("Error");
          getchar();
          return begin;
     }
     temp = begin;
     temp1 = temp->next;
     while (temp1->next && k < n-1)
     {
          temp = temp1;
          temp1 = temp->next;
          k++;
     }
     if (k < n-1)
     {
          puts ("Error");
          getchar();
          return begin;
     }
     print_data (temp1->data);
     puts ("Delete? (y/n)");
     do
     {
          yes=getchar(); getchar();
	 }
     while (yes!='y' && yes!='Y' && yes!='n' && yes!='N');
     if (yes=='y' || yes=='Y')
     {
          temp->next = temp1->next;
          free (temp1);
     }
     return begin;
 }
