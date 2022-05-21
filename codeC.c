#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAXLENGT 255

typedef struct patient {
	char surname[MAXLENGT];
	char sex;
	int age;
	char city[MAXLENGT];
	char diagnosis[MAXLENGT];
}patient;

patient *array_patient = NULL;
int count_patient = 0;

void printMenu() {
	system("cls");
	if (count_patient == 0) {
		printf("�����\n");
	}
	else {
		for (int i = 0; i < count_patient; i++) {
			printf("%d. %s %c %d \"%s\" \"%s\" \n", i + 1, array_patient[i].surname, array_patient[i].sex, array_patient[i].age, array_patient[i].city, array_patient[i].diagnosis);
		}
	}
}

void add(patient temp) {
	if (!array_patient) {
		array_patient = (patient*)malloc(sizeof(patient));
		array_patient[count_patient].age = temp.age;
		strcpy(array_patient[count_patient].city, temp.city);
		strcpy(array_patient[count_patient].diagnosis, temp.diagnosis);
		array_patient[count_patient].sex = temp.sex;
		strcpy(array_patient[count_patient].surname, temp.surname);
	}
	else {
		array_patient = (patient*)realloc(array_patient, sizeof(patient)*(count_patient+1));
		array_patient[count_patient].age = temp.age;
		strcpy(array_patient[count_patient].city, temp.city);
		strcpy(array_patient[count_patient].diagnosis, temp.diagnosis);
		array_patient[count_patient].sex = temp.sex;
		strcpy(array_patient[count_patient].surname, temp.surname);
	}
	++count_patient;
	system("pause");
}

void addMenu() {
	patient temp;
	system("cls");
	printf("�������: ");
	scanf("%s", &temp.surname);
	printf("���: ");
	getchar();
	scanf("%c", &temp.sex);
	printf("�������: ");
	scanf("%d", &temp.age);
	printf("����� ����������: ");
	getchar();
	gets(&temp.city);
	printf("�������: ");
	gets(&temp.diagnosis);
	
	add(temp);
}

void delete(int index) {
	if (count_patient == 1) {
		--count_patient;
		free(array_patient);
		array_patient = NULL;
		return;
	}

	patient* temp_array = (patient*)malloc(sizeof(patient)*count_patient - 1);
	for (int i = 0, j = 0; i < count_patient; i++, j++) {
		if (i == index) {
			++i;
			if (i >= count_patient)
				break;
		}
		temp_array[j].age = array_patient[i].age;
		strcpy(temp_array[j].city, array_patient[i].city);
		strcpy(temp_array[j].diagnosis, array_patient[i].diagnosis);
		temp_array[j].sex = array_patient[i].sex;
		strcpy(temp_array[j].surname, array_patient[i].surname);
	}
	--count_patient;
	free(array_patient);
	array_patient = temp_array;
}

void deleteMenu() {
	system("cls");
	printMenu();
	if (array_patient) {
		int del;
		printf("\n������� ����� �������� ��� �������� (0 - ��� ������): ");
		scanf("%d", &del);
		if (del == 0)
			return;
		else {
			if (del < 0 || del > count_patient)
				printf("������ ������������ ����� ��������\n");
			else {
				delete(del - 1);
			}
		}

	}
	system("pause");
}

void printPensAge() {
	char flag = 0;
	system("cls");
	if (count_patient == 0) {
		printf("�����\n");
	}
	else {
		for (int i = 0; i < count_patient; i++) {
			if (array_patient[i].age >= 60) {
				printf("%d. %s %c %d \"%s\" \"%s\" \n", i + 1, array_patient[i].surname, array_patient[i].sex, array_patient[i].age, array_patient[i].city, array_patient[i].diagnosis);
				if (!flag)
					flag = 1;
			}
		}
		if (!flag)
			printf("����� �������� �����������\n");
	}
}

void writeInFile(const char* filename) {
	FILE* file = fopen(filename, "wb+");
	if (!file) {
		perror("������ ��������/�������� �����");
		exit(1);
	}
	fwrite(&count_patient, sizeof(int), 1, file);
	fwrite(array_patient, sizeof(patient), count_patient, file);
}

void readFile(FILE* file) {
	fread(&count_patient, sizeof(int), 1, file);
	array_patient = (patient*)malloc(sizeof(patient)*count_patient);
	fread(array_patient, sizeof(patient), count_patient, file);
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* file = NULL;
	char filename[MAXLENGT], sym;
	if (argc > 1)
		strcpy(&filename, argv[1]);
	else {
		printf("������� �������� �����: ");
		scanf("%s", filename);
	}

	if (!(file = fopen(filename, "rb+"))) {
		perror("������ �������� �����");
		do {
			printf("\n������� ����� ���� � ����� �� ������ ? (Y, N): ");
			while (getchar() != '\n');
			sym = getchar();
			if (sym == 'Y') {
				if (!(file = fopen(filename, "wb"))) {
					perror("������ �������� �����");
					return 1;
				}
				break;
			}
			else
				if (sym == 'N')
					return 0;
		} while (1);
	}
	else
		readFile(file);

	int dig = 0;
	do {
		system("cls");
		printf("1. �������� ������ � ��������\n");
		printf("2. ������� ������ � ��������\n");
		printf("3. �������� ���������� � ���� ���������\n");
		printf("4. �������� ���������� � ��������� ����������� ��������\n");
		printf("0. ����� � ���������\n");
		scanf("%d", &dig);
		switch (dig)
		{
			case 1: addMenu(); break;
			case 2: deleteMenu(); break;
			case 3: printMenu(); system("pause"); break;
			case 4: printPensAge(); system("pause"); break;
		}
	} while (dig !=0);
	writeInFile(filename);
	return 0;
}

