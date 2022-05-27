#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>

int func(int n)
{
    if (n==0)
        return 1;
    else
        return func(n-1)*n;
}

int main() {
	SetWindowText(GetConsoleWindow(), "Factorial");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	int n;
	do {
		system("cls");
		printf("Enter a number [0;9] (to exit enter 10):\n");
    	scanf("%d", &n);
    	if (n==10)
    	{
    		printf("Exit...");
    		break;
    	}
    	else
    		printf("%d\n", func(n));
    	system("pause");
	}
	while (1);
	return 0;
}
