#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <wincon.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAXLENGHT 200

void setWindowTitle() {
	char title[MAXLENGHT];
	system("cls");
	printf("Введите заголовок окна: ");
	getchar();
	gets(title);
	SetWindowText(GetConsoleWindow(), title);
	printf("...Успешно изменено...\n");
}

void setWindowCp() {
	int code;
	system("cls");
	printf("Введите кодовую страницу: ");
	getchar();
	scanf("%d", &code);
	if (!SetConsoleCP(code))
		MessageBox(NULL, "Ошибка: Неверная кодовая страница", "Ошибка", MB_OK);
	else
		printf("...Успешно изменено...\n");
}

void setWindowColor() {
	int code;
	system("cls");
	printf("Введите код цвета: ");
	getchar();
	scanf("%d", &code);
	if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code))
		MessageBox(NULL, "Ошибка: Неверный код цвета", "Ошибка", MB_OK);
	else
		printf("...Успешно изменено...\n");
}

int main(int argc, char *argv[]) {
	int dig = 0;
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	do {
		system("cls");
		printf("1. Изменить заголовок текущего окна \n");
		printf("2. Изменить кодовую страницу ввода данных (%d)\n", GetConsoleCP());
		printf("3. Изменить цвет текста и фона окна\n");
		printf("0. Выход\n");
		printf("\n:");
		scanf("%d", &dig);
		switch (dig) {
			case 1: setWindowTitle(); system("pause"); break;
			case 2: setWindowCp(); system("pause"); break;
			case 3: setWindowColor(); system("pause"); break;
		}
	} while (dig != 0);
	system("pause");
	return 0;
}

