#include "libsdb.h"
#include <stdlib.h>

// budowa struktury z definicją słowa
// definiujemy tutaj zmienne ktore beda wartosciami 
// pojedynczego rekordu znajdujacego sie w bazie danych


int open_record(char *filename)
{
    int fd;
    
    // open otwiera okreslony sciezka plik, flaga 0_CREAT tworzy plik 
    // jesli nie istnieje, 0_APPEND otwiera plik w trybie dolaczenia
    // O_RDWR nadaje dostep read/write, 0644 nadajace prawa uzytkownikom
    fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
    return fd;
}

int open_record_update(char *filename)
{
    int fd;
    fd = open(filename, O_CREAT | O_RDWR, 0644);
    return fd;
}

void close_record(int fd){
    close(fd); //close() zamykajacy deskryptor pliku
}

int get_record(int fd, person *rec, int id)
{
    int ret;
    while ((ret = read(fd, rec, sizeof(person))) != -1)
    {
        if(ret == 0)
        {
	    // zastosowanie memset pozwala na wypelnienie
	    // kolejnych bajtow ustalona wartoscia
            memset(rec, 0, sizeof(person));
            break;
            return ret;
        }
        else if (id == rec->id)
            return ret;
    }
    memset(rec, 0, sizeof(person));
    return ret;
}

int show_local_db()
{
    int fd;
    person rec;

    //petla pobierajaca pierwsze 10 id i wyswietla dane polaczone 
    //z owymi id na terminalu
    for (int i = 0; i<10; i++) 
    {
        fd = open_record("data1");
        get_record(fd, &rec, i);

    //dane drukowane na terminaulu odwoluja sie do struktury
        printf("ID = %d\n", rec.id);
        printf("Imie = %s\n", rec.fname);
        printf("Nazwisko = %s\n", rec.lname);
        printf("Wartosc = %d\n", rec.value);
    }
    close_record(fd);
}


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
