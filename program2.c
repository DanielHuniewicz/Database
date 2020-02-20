#include "libsdb.h"

// fuckcja dodajaca wartosci do bazy danych poprzez
// prosty formularz terminalowy
int adding()
{
	int fd;
    	person rec;
	fd = open_record("data1");

    	printf("Podaj ID  : ");
    	scanf("%d", &rec.id);
    	printf("Podaj imie : ");
	scanf("%s", &rec.fname);
        printf("Podaj nazwisko  : ");
        scanf("%s", &rec.lname);
        printf("Podaj wartosc : ");
        scanf("%d", &rec.value);

        insert_record(fd, &rec);
        printf("\n Rekord zostal dodany");
    	close_record(fd);
}

// funkcja pobierajaca zmienna value z pojedynczego rekordu
// bazy danych, modyfikujaca go a nastepnie zapisujaca
// ponowanie w pliku binarnym
int editing()
{
	int fd; 
	int w_id;
	int w_value;
    	person rec;
	fd = open_record("data1");

	printf("Podaj ID  : ");
        scanf("%d" , &w_id);
        printf("Podaj nowa wartosc  : ");
        scanf("%d" , &w_value);

        fd = open_record_update("data1");
        edit_record(fd, w_id, w_value);
	close_record(fd);
}

// funkcja main programu posiadajaca proste menu 
// bazujaca ma przelaczniku switch
int main()
{
    	int wybor;

    	printf("---MENU---\n\n");
   	printf("Wybierz operacje numerycznie:\n");
    	printf("1. Dodaj dane\n");
    	printf("2. Edytuj dane\n");
    	printf("3. Wyjscie\n");
    	scanf("%d", &wybor);

    switch (wybor)
    {
    case 1:
    // dodawanie
	adding();
        break;

    case 2:
    //wyswietlanie
	editing();
        break;

    case 3:
    //wyjscie
        break;

    default:
        printf("Podales zla wartosc");
    }

}
