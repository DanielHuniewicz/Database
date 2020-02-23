#include "libsdb.h"


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

int insert_record(int fd, person *rec)
{
    int ret; // ret wartosc zwracana

    ret = write(fd, rec, sizeof(person));
    return ret;
}

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
