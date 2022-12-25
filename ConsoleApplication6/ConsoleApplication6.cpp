#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define FNAME_I "D:\\bd15.dat\0"	//имя файла с исходной базой
#define FNAME_R "D:\\bd25.dat\0"	//имя файла с результатами поиска

int check_file(const char* fname, const char* pr);   //проверка наличия файла;
void add_a_file(const char* fname);        //добавить файл;
void zag1();
void zag2();
void viewBD1(const char* fname);
void viewBD2(const char* fname);
void findTitle(const char* fname1, const char* fname2);
void sort_for_title(const char* fname);
void sort_for_price(const char* fname);

const char PR_R[] = "rb";	//признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";	//признак открытия файла на чтение и запись
const char PR_W[] = "wb";	//признак открытия файла на запись
const char PR_A[] = "ab";	//признак открытия файла на добавление

typedef struct {
	char district[15];	//район
	char title[15];	//название населенного пункта
	int distance;			//расстояние от города
	int square;			//площадь, кол-во соток
	int price;		//цена за сотку
}landPlot;

//main_Begin______________________________________________________________
int main() {
	int var;
	char otv;
	char fname_i[36] = FNAME_I;
	char fname_r[39] = FNAME_R;

	setlocale(LC_ALL, "Russian");

	for (;;) {
		printf("\n    Вид действия:\n");
		printf("  1 - создание базы данных\n");
		printf("  2 - добавление новых записей\n");
		printf("  3 - сортировка по названию н.п.\n");
		printf("  4 - сортировка участков по цене за сотку\n");
		printf("  5 - поиск участков по названию населенного пункта\n");
		printf("  6 - просмотр базы данных\n");
		printf("  7 - просмотр базы данных поиска участков\n");
		printf("  8 - завершение задачи\n");
		printf("  Введите вид действия ->");
		scanf("%i", &var);
		switch (var)
		{
		default:break;
		case 1: if (check_file(fname_i, PR_R))
		{
			printf(" Файл базы данных земельных участков с именем ", fname_i);
			printf(" был создан раньше.\n");
			printf(" Создаём файл с новым именем? [Y/N] ");
			while ((otv = getchar()) == '\n');
			if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н')
			{
				printf(" Задайте имя создаваемого файла: ");
				scanf("%s", fname_i);
			}
			else break;
		}
			  if (!check_file(fname_i, PR_W))
			  {
				  printf("\n Ошибка открытия файла для записи\n");
				  break;
			  }
			  printf(" Создаем базу ", fname_i, '\n');
			  getchar();
			  add_a_file(fname_i);
			  printf("\n Создание файла закончено.\n");
			  if (check_file(fname_i, PR_R))
				  printf(" База данных готова к работе\n");
			  else printf("\n база не создана\n");
			  break;
		case 2: if (check_file(fname_i, PR_R))
		{
			printf(" Файл базы данных земельных участков с именем ", fname_i);
			printf(" был создан раньше.\n");
			printf(" Будем добавлять новые записи в него? [Y/N] ");
			while ((otv = getchar()) == '\n');
			if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т')
			{
				printf(" Задайте имя файла другой базы: ");
				scanf("%s", fname_i);
				if (!check_file(fname_i, PR_R))
				{
					printf(" Такая база данных не создавалась\n");
					break;
				}
			}
		}
			  printf(" Добавляем записи в файл ", fname_i, '\n');
			  add_a_file(fname_i);
			  printf("\n Изменение файла закончено.");
			  break;
		case 3: if (!check_file(fname_i, PR_S))
		{
			printf("\n Ошибка открытия файла для чтения и записи\n");
			break;
		}
			  sort_for_title(fname_i);
			  printf("\n Сортировка по названию Населенного пункта закончена.");
			  break;
		case 4: if (!check_file(fname_i, PR_S))
		{
			printf("\n Ошибка открытия файла для чтения и записи\n");
			break;
		}
			  sort_for_price(fname_i);
			  printf("\n Сортировка по цене за сотку закончена.");
			  break;
		case 5: if (!check_file(fname_i, PR_R))
		{
			printf("\n Ошибка открытия файла для чтения\n");
			break;
		}
			  if (!check_file(fname_r, PR_W))
			  {
				  printf("\n Ошибка открытия файла для записи\n");
				  break;
			  }
			  findTitle(fname_i, fname_r);
			  printf("\n Поиск по названию Населенного пункта закончен.");
			  break;
		case 6: if (!check_file(fname_i, PR_R))
		{
			printf("\n Ошибка открытия файла для чтения\n");
			break;
		}
			  viewBD1(fname_i);
			  break;
		case 7: if (!check_file(fname_r, PR_R))
		{
			printf("\n Ошибка открытия файла для чтения\n");
			break;
		}
			  viewBD2(fname_r);
			  break;
		case 8: return 0;
		}
	}
}
//main_End________________________________________________________________

int check_file(const char* fname, const char* pr) {
	if (!(fopen(fname, pr)))
	{
		return 0;
	}
	return 1;
}

//add_a_file_Begin___________________________________________________________
//Добавление новых элементов в базу данных
void add_a_file(const char* fname) {
	char otv;
	landPlot land;
	FILE* baza;
	baza = fopen(fname, PR_A);
	rewind(baza);
	do
	{
		printf("\n Наименование района? ");
		scanf("%s", &land.district);

		printf(" Название населенного пункта? ");
		scanf("%s", &land.title);

		printf(" Расстояние от города? (км) ");
		scanf("%i", &land.distance);

		printf(" Площадь? (кол-во соток) ");
		scanf("%i", &land.square);

		printf(" Цена за сотку? ");
		scanf("%d", &land.price);

		fwrite(&land, sizeof(land), 1, baza);

		printf("\n Продолжать?[Y/N]");
		while ((otv = getchar()) == '\n');
	} while (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н');
	fclose(baza);
	return;
}
//add_a_file_End_____________________________________________________________

//Zag1_Begin______________________________________________________________
//Вывод заголовка при просмотре исходного файла
void zag1() {
	int i;

	printf("\n");
	for (i = 1; i <= 106; i++)
		printf("-");
	printf("\n");
	printf("|%20s|%20s|%20s|%20s|%20s|\n", "Район", "Название н.п.",
		"Расстояние от города", "S, кол-во соток", "Цена за сотку");
	for (i = 1; i <= 106; i++)
		printf("-");
	return;
}

//Zag1_End________________________________________________________________

//Zag2_Begin______________________________________________________________
//Вывод заголовка при просмотре файла поиска участка
void zag2() {
	int i;

	printf("\n");
	for (i = 1; i <= 106; i++)
		printf("-");
	printf("\n");
	printf("|%20s|%20s|%20s|%20s|%20s|\n", "Название н.п.", "Район",
		"Расстояние от города", "S, кол-во соток", "Цена за сотку");
	for (i = 1; i <= 106; i++)
		printf("-");
	return;
}
//Zag2_End________________________________________________________________

//ViewBD1_Begin_______________________________________________________
//Просмотр базы данных земельных участков
void viewBD1(const char* fname) {
	int i;
	landPlot land;
	FILE* baza;
	baza = fopen(fname, PR_R);
	printf("\n     База данных земельных участков");
	zag1();
	while (fread(&land, sizeof(land), 1, baza) > 0)
	{
		printf("\n|%20s|%20s|%20i|%20i|%20i|", land.district, land.title,
			land.distance, land.square, land.price);
	}
	printf("\n");
	for (i = 1; i <= 106; i++)
		printf("-");
	fclose(baza);
	return;
}
//ViewBD1_End_________________________________________________________

//ViewBD2_Begin_______________________________________________________
//Просмотр базы данных поиска земельных участков по Названию н.п.
void viewBD2(const char* fname) {
	int i;
	landPlot land;
	FILE* baza;
	baza = fopen(fname, PR_R);
	printf("\n     База данных земельных участков по Району");
	zag2();
	while (fread(&land, sizeof(land), 1, baza) > 0)
	{
		printf("\n|%20s|%20s|%20i|%20i|%20i|", land.title, land.district,
			land.distance, land.square, land.price);
	}
	printf("\n");
	for (i = 1; i <= 106; i++)
		printf("-");
	fclose(baza);
	return;
}
//ViewBD2_End_________________________________________________________

//FindTitle_Begin______________________________________________________
//Поиск туров по названию земельного участка
void findTitle(const char* fname1, const char* fname2) {
	char title[15];
	landPlot land;
	FILE* in,					//исходный файл
		* out;				//файл результатов поиска
	in = fopen(fname1, PR_R);		//открываем файл на чтение
	out = fopen(fname2, PR_W);		//открываем файл на запись
	printf("\n Название земельного участка для поиска? ");
	scanf("%s", &title);
	while (fread(&land, sizeof(land), 1, in) > 0)
		if (strncmp(land.title, title, 15) == 0)
			fwrite(&land, sizeof(land), 1, out);
	fclose(out);
	fclose(in);
	return;
}
//FindTitle_End________________________________________________________

//Sort_for_title_Begin_________________________________________________________
//Сортировка по наименованию турпоездки по алфавиту
void sort_for_title(const char* fname) {
	int i;
	int fl;
	landPlot ppp, land;
	FILE* baza;
	baza = fopen(fname, PR_S);	//открываем файл на чтение и запись
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&land, sizeof(land), 1, baza) > 0; i += sizeof(land),
			fseek(baza, i, SEEK_SET))	//позиция i от НАЧАЛА файла
		{
			if (fread(&ppp, sizeof(land), 1, baza) > 0)
			{
				if (strncmp(land.title, ppp.title, 15) > 0)
				{
					fseek(baza, i, SEEK_SET);	//позиция i от НАЧАЛА файла
					fwrite(&ppp, sizeof(land), 1, baza);
					fwrite(&land, sizeof(land), 1, baza);
					fl = 1;
				}
			}
		}
	} while (fl);
	fclose(baza);
	return;
}
//Sort_for_title_End___________________________________________________________

//Sort_for_price_Begin_________________________________________________________
//Сортировка по убыванию стоимости путевки
void sort_for_price(const char* fname) {
	int i;
	int fl;
	landPlot ppp, land;
	FILE* baza;
	baza = fopen(fname, PR_S);	//открываем файл на чтение и запись
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&land, sizeof(land), 1, baza) > 0; i += sizeof(land),
			fseek(baza, i, SEEK_SET))
		{
			if (fread(&ppp, sizeof(land), 1, baza) > 0)
			{
				if (land.price > ppp.price)
				{
					fseek(baza, i, SEEK_SET);	//позиция i от НАЧАЛА файла
					fwrite(&ppp, sizeof(land), 1, baza);
					fwrite(&land, sizeof(land), 1, baza);
					fl = 1;
				}
			}
		}
	} while (fl);
	fclose(baza);
	return;
}
//Sort_for_price_End___________________________________________________________