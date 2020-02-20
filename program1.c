#include "libsdb.h"
#include <stdlib.h>

//funkcja wykonujaca prosta operacje matematyczna na
// pobranych wartosciach z bazy danych
int data_operation()
{
    int fd;
    int w_id1;
    int multi;

    person rec;
    fd = open_record("data1");

    printf("Podaj ID osoby : ");
    scanf("%d" , &w_id1);
    get_record(fd, &rec, w_id1);

    printf("Podana wartosc: %d\n", rec.value);

    multi = rec.value * rec.value;
    printf("Kwadrat wartosci = %d\n", multi);

    close_record(fd);
}

// funkcja main programu posiadajaca proste menu 
// bazujaca ma przelaczniku switch
int main()
{
    // uzycie funkcji wczytujacej dane z pliku do RAM-u 
    // przy otwarciu programu
    show_local_db();
    int wybor;

    printf("---MENU---\n\n");
    printf("Wybierz operacje numerycznie:\n");
    printf("1. Operacje na danych\n");
    printf("2. Wyjscie\n");
    scanf("%d", &wybor);

    switch (wybor)
    {
    case 1:
    // operacje na danych
	data_operation();
        break;

    case 2:
    //wyjscie
    	break;

    default:
        printf("Podales zla wartosc");
    }
}
