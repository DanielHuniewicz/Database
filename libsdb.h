#ifndef LIBSDB.H
#define LIBSDB.H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct {
    // wartosc unsignet aby wartosci przypadkiem nie byly ujemne
    unsigned int id;
    char fname[16];
    char lname[16];
    unsigned int value;
}person;

// funkcja otwierajaca lub tworzaca w przypadku jego braku plik binarny
int open_record(char *filename);

// zmodfikowna funkcja open_record bez uwzglednienia flagi O_APPEND
int open_record_update(char *filename);

// funkcja zamykajaca rekord
void close_record(int fd);

// funkcja wstawiajaca tresc do rekordu
int insert_record(int fd, person *rec);

// funkcja pobierajaca rekord z przypisanym id z bazy danych
int get_record(int fd, person *rec, int id);

// funkcja pobierajaca rekord z przypisanym id z bazy danych
// i zmieniajaca jego pojedyncza wartosc w strukturze
int edit_record(int fd, int id, int m_value);

//funkcja pobierajaca dane z pliku przy uruchomieniu programu
int show_local_db();

#endif

