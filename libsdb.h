#ifndef LIBSDB.H
#define LIBSDB.H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// budowa struktury z definicją słowa
// definiujemy tutaj zmienne ktore beda wartosciami 
// pojedynczego rekordu znajdujacego sie w bazie danych

typedef struct {
    // wartosc unsignet aby wartosci przypadkiem nie byly ujemne
    unsigned int id;
    char fname[16];
    char lname[16];
    unsigned int value;
}person;

// funkcja otwierajaca lub tworzaca w przypadku jego braku plik binarny
int open_record(char *filename)
{
    int fd;
    
    // open otwiera okreslony sciezka plik, flaga 0_CREAT tworzy plik 
    // jesli nie istnieje, 0_APPEND otwiera plik w trybie dolaczenia
    // O_RDWR nadaje dostep read/write, 0644 nadajace prawa uzytkownikom
    fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
    return fd;
}

// zmodfikowna funkcja open_record bez uwzglednienia flagi O_APPEND
int open_record_update(char *filename)
{
    int fd;
    fd = open(filename, O_CREAT | O_RDWR, 0644);
    return fd;
}

// funkcja zamykajaca rekord
void close_record(int fd){
    close(fd); //close() zamykajacy deskryptor pliku
}

// funkcja wstawiajaca tresc do rekordu
int insert_record(int fd, person *rec)
{
    int ret; // ret wartosc zwracana

    ret = write(fd, rec, sizeof(person));
    return ret;
}

// funkcja pobierajaca rekord z przypisanym id z bazy danych
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

// funkcja pobierajaca rekord z przypisanym id z bazy danych
// i zmieniajaca jego pojedyncza wartosc w strukturze
int edit_record(int fd, int id, int m_value)
{
    int ret;
    person rec;

    off_t pos;
    // funkcja lseek pozwala ustawic sie na odpowiednim bicie
    // w pliku binarym tak aby funkcja write mogla nadpisac jego
    // wczesniejsza wartosc
    pos = lseek(fd, 0 , SEEK_SET);

    while((ret = read(fd, &rec, sizeof(person))) != -1)
    {
        if(ret==0)
        {
            return ret;
        }
        else if (id == rec.id)
        {
	    // flaga SEEK_SET ustawia przesuniecie pliku
            lseek(fd, pos, SEEK_SET);

            rec.value = m_value;

            ret = write(fd, &rec, sizeof(person));
            return ret;
        }
	// flaga SEEK_CUR ustawia przesuniecie pliku na
	// biezaca lokalizacje
        pos = lseek(fd, 0 , SEEK_CUR);
    }
    return ret;
}

//funkcja pobierajaca dane z pliku przy uruchomieniu programu
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

#endif

