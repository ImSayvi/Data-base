#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bazaOtwarta = 0;
char nazwaOtwartejBazy[12];

typedef char* string;

struct probka
{
    char nazwa[10];
    char typ[10];
    char dataPoboru[11];
    char region[31];
    char wataha[30];
    double x;
    double y;
    char kto[20];
};

void menu(void);
struct probka wczytStruct(void);
void drukStruct(struct probka st);
void sortujBaze(void);
void przegladBazy(void);
void modStruct(int pos);
void usunStruct(int pos);
void utworzBaze(void);
void otworzBaze(void);
int sprawdzNazweBazy(char *nazwa);
void dopiszStruct(void);
void przegladMenu(int pos);
void wyswietlStrukture(int pos);
void home(void);
void end(void);
void next(int *pos);
void previous(int *pos);
int liczbaStruktur(void);
void drukujWszystkieStruktury(void);

int main(void)
{
    menu();
    return 0;
}

void menu(void)
{
    char ch;
    int pos = 1;
    FILE *fp;

    do
    {
        system("cls");
        printf("\n");
        printf(" ============================\n");
        printf(" 1. Otworz baze danych\n");
        printf(" 2. Utworz nowa baze\n");
        printf(" 3. Przeglad bazy\n");
        printf(" 4. Sortowanie bazy\n");
        printf(" 5. Modyfikacja struktury\n");
        printf(" 6. Usun plik bazy danych\n");
        printf(" 7. Zakoncz program\n");
        printf(" ============================\n");
        printf(" Wybierz opcje :");
        ch = getch();

        switch(ch)
        {
        case '1':
            otworzBaze();
            przegladMenu(pos);
            break;
        case '2':
            utworzBaze();
            przegladMenu(pos);
            break;
        case '3':
            przegladBazy();
            break;
        case '4':
            sortujBaze();
            break;
        case '5':
        {
            int pos;
            printf("\n Podaj pozycje struktury do modyfikacji: ");
            scanf("%d", &pos);
            modStruct(pos);
            break;
        }
        case '6':
        {
            char odpowiedz;
            printf("\n Czy na pewno chcesz usunac baze danych '%s'? (T/N): ", nazwaOtwartejBazy);
            odpowiedz = getch();
            if (odpowiedz == 'T' || odpowiedz == 't')
            {
                remove(nazwaOtwartejBazy);
                printf("\n Baza danych '%s' zostala usunieta.", nazwaOtwartejBazy);
                bazaOtwarta = 0;
            }
            else
            {
                printf("\n Operacja usuniecia bazy danych anulowana.");
            }
            break;
        }
        case '7':
        {
            char odpowiedz;
            printf("\n Czy chcesz zapisac aktualny stan bazy danych przed wyjsciem? (T/N): ");
            odpowiedz = getch();
            if (odpowiedz == 'T' || odpowiedz == 't')
            {

                if (bazaOtwarta)
                {
                    printf("\n Zapisywanie aktualnego stanu bazy danych...");
                    fclose(fp);
                    printf("\n Aktualny stan bazy danych zostal zapisany.");
                }
                else
                {
                    printf("\n Nie ma otwartej bazy danych do zapisania.");
                }
            }
            else
            {
                printf("\n Stan bazy danych nie zostanie zapisany.");
            }
            printf("\n Zamykanie programu...");
            exit(0);
        }
        }
    }
    while (ch != '7');
}

struct probka wczytStruct(void)
{
    struct probka st;
    printf("\nNazwa:");
    scanf("%9s", st.nazwa);
    printf("\nTyp:");
    scanf("%9s", st.typ);
    printf("\nData poboru:");
    scanf("%9s", st.dataPoboru);
    printf("\nRegion:");
    scanf("%30s", st.region);
    printf("\nWataha:");
    scanf("%29s", st.wataha);
    printf("\nKoordynaty x:");
    scanf("%lf", &st.x);
    printf("\nKoordynaty y:");
    scanf("%lf", &st.y);
    printf("\nOsoba, ktora pobrala probke:");
    scanf("%19s", st.kto);
    return st;
}

void drukStruct(struct probka st)
{
    printf("\n Nazwa: %s", st.nazwa);
    printf("\n Typ: %s", st.typ);
    printf("\n Data poboru: %s", st.dataPoboru);
    printf("\n Region: %s", st.region);
    printf("\n Wataha: %s", st.wataha);
    printf("\n Koordynaty x: %lf", st.x);
    printf("\n Koordynaty y: %lf", st.y);
    printf("\n Osoba, ktora pobrala probke: %s", st.kto);
}

int sprawdzNazweBazy(char *nazwa)
{
    char lan1[4], lan2[3], lan3[5];
    int wynik1, wynik2, wynik3;


    strncpy(lan1, nazwa, 4);
    lan1[4] = '\0';
    strncpy(lan2, nazwa + 4, 2);
    lan2[2] = '\0';
    strcpy(lan3, nazwa + 6);


    wynik1 = strcmp(lan1, "baza");
    wynik2 = isdigit(lan2[0]) && isdigit(lan2[1]);
    wynik3 = strcmp(lan3, ".dat");


    if (!wynik1 && wynik2 && !wynik3)
    {
        printf("\n Nazwa bazy jest zgodna z wymogami");
        return 1;
    }
    else
    {
        printf("\n Nazwa bazy jest niezgodna z wymogami");
        return 0;
    }
}

void otworzBaze(void)
{
    FILE *fp;
    char nazwa[12];
    char odpowiedz;

    if (bazaOtwarta)
    {
        printf("\n Plik minibazy %s jest otwarty. Czy zamknac plik T/N?", nazwaOtwartejBazy);
        odpowiedz = getch();
        if (odpowiedz == 'T' || odpowiedz == 't')
        {
            bazaOtwarta = 0;
        }
        else
        {
            printf("\n Powrot do menu glownego.");
            return;
        }
    }

    printf("\n Podaj nazwe minibazy do otwarcia: ");
    scanf("%11s", nazwa);

    if (!sprawdzNazweBazy(nazwa))
    {
        printf("\n Nazwa bazy niezgodna z wymogami.");
        return;
    }

    fp = fopen(nazwa, "rb");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal otwarty", nazwa);
        return;
    }
    else
    {
        printf("\n Plik %s zostal otwarty", nazwa);
        strcpy(nazwaOtwartejBazy, nazwa);
        fclose(fp);
        bazaOtwarta = 1;
    }
}

void sortujBaze(void)
{
    FILE *fp;
    struct probka bufs1, bufs2;
    int n = liczbaStruktur(), zam, i;

    if (n <= 1)
    {
        printf("\n Brak wystarczajacej liczby struktur do sortowania");
        return;
    }

    fp = fopen(nazwaOtwartejBazy, "r+b");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal otwarty", nazwaOtwartejBazy);
        exit(1);
    }

    do
    {
        zam = 0;
        for (i = 0; i < n - 1; i++)
        {
            fseek(fp, i * sizeof(struct probka), SEEK_SET);
            fread(&bufs1, sizeof(struct probka), 1, fp);
            fread(&bufs2, sizeof(struct probka), 1, fp);
            if (strcmp(bufs1.nazwa, bufs2.nazwa) > 0)
            {
                fseek(fp, i * sizeof(struct probka), SEEK_SET);
                fwrite(&bufs2, sizeof(struct probka), 1, fp);
                fwrite(&bufs1, sizeof(struct probka), 1, fp);
                zam = 1;
            }
        }
        n--;
    }
    while (zam);

    fclose(fp);
    printf("\n Plik %s zostal posortowany", nazwaOtwartejBazy);
}

int liczbaStruktur(void)
{
    FILE *fp;
    int count = 0;
    struct probka bufs;

    fp = fopen(nazwaOtwartejBazy, "rb");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal otwarty", nazwaOtwartejBazy);
        exit(1);
    }

    while (fread(&bufs, sizeof(struct probka), 1, fp))
    {
        count++;
    }

    fclose(fp);
    return count;
}

void przegladBazy(void)
{
    przegladMenu(1);
}

void przegladMenu(int pos)
{
    char ch;
    do
    {
        printf(" \n\n============================");
        printf("\nB(lub strzalka w dol)- przesuniecie o jedna strukture w dol\n");
        printf("Y(lub strzalka w gore)- przesuniecie o jedna strukture w gore\n");
        printf("G (lub HOME)- przesuniecie na poczatek\n");
        printf("H (lub END)- przesuniecie na koniec\n");
        printf("D- dopisz nowa strukture\n");
        printf("U- usun biezaca strukture\n");
        printf("M- modyfikuj strukture\n");
        printf("S- sortuj baze danych\n");
        printf("A- drukuj wszystkie struktury\n");
        printf("esc- powrot do menu\n");
        printf(" ============================\n");

        ch = getch();
        switch(ch)
        {
        case 80:
        case 'b':
            next(&pos);
            break;
        case 72:
        case 'y':
            previous(&pos);
            break;
        case 71:
        case 'g':
            home();
            pos = 1;
            break;
        case 79:
        case 'h':
            end();
            pos = liczbaStruktur();
            break;
        case 'D':
        case 'd':
            dopiszStruct();
            break;
        case 'U':
        case 'u':
            usunStruct(pos);
            break;
        case 'M':
        case 'm':
            modStruct(pos);
            break;
        case 'S':
        case 's':
            sortujBaze();
            break;
        case 'A':
        case 'a':
            drukujWszystkieStruktury();
            break;
        case 27:
            menu();
            return;
        }
        wyswietlStrukture(pos);
    }
    while (ch != 27);
}

void wyswietlStrukture(int pos)
{
    FILE *fp;
    struct probka bufs;

    fp = fopen(nazwaOtwartejBazy, "rb");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal otwarty", nazwaOtwartejBazy);
        exit(1);
    }

    fseek(fp, (pos - 1) * sizeof(struct probka), SEEK_SET);
    if (fread(&bufs, sizeof(struct probka), 1, fp) == 1)
    {
        system("cls");
        printf("\n Struktura %d", pos);
        drukStruct(bufs);
    }
    else
    {
        printf("\n Brak struktury na pozycji %d", pos);
    }

    fclose(fp);
}

void drukujWszystkieStruktury(void)
{
    FILE *fp;
    struct probka bufs;
    int pos = 1;

    fp = fopen(nazwaOtwartejBazy, "rb");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal otwarty", nazwaOtwartejBazy);
        exit(1);
    }

    while (fread(&bufs, sizeof(struct probka), 1, fp))
    {
        printf("\n\n Struktura %d", pos++);
        drukStruct(bufs);
    }

    fclose(fp);

    printf("\nNacisnij dowolny klawisz, aby wrocic do menu...");
    getch();

    menu();
}

void home(void)
{
    wyswietlStrukture(1);
}

void end(void)
{
    wyswietlStrukture(liczbaStruktur());
}

void next(int *pos)
{
    if (*pos < liczbaStruktur())
    {
        (*pos)++;
        wyswietlStrukture(*pos);
    }
}

void previous(int *pos)
{
    if (*pos > 1)
    {
        (*pos)--;
        wyswietlStrukture(*pos);
    }
}

void dopiszStruct(void)
{
    FILE *fp;
    struct probka nowa = wczytStruct();

    fp = fopen(nazwaOtwartejBazy, "ab");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal otwarty", nazwaOtwartejBazy);
        exit(1);
    }

    fwrite(&nowa, sizeof(struct probka), 1, fp);
    fclose(fp);
    printf("\n Nowa struktura zostala dodana");
}

void modStruct(int pos)
{
    FILE *fp;
    struct probka nowa;

    fp = fopen(nazwaOtwartejBazy, "r+b");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal otwarty", nazwaOtwartejBazy);
        exit(1);
    }

    fseek(fp, (pos - 1) * sizeof(struct probka), SEEK_SET);
    if (fread(&nowa, sizeof(struct probka), 1, fp) != 1)
    {
        printf("\n Brak struktury na pozycji %d", pos);
        fclose(fp);
        return;
    }

    printf("\n Biezaca struktura na pozycji %d:", pos);
    drukStruct(nowa);

    printf("\n\n Podaj nowe wartosci dla struktury na pozycji %d:\n", pos);
    nowa = wczytStruct();

    fseek(fp, (pos - 1) * sizeof(struct probka), SEEK_SET);
    fwrite(&nowa, sizeof(struct probka), 1, fp);
    fclose(fp);

    printf("\n Struktura na pozycji %d zostala zmodyfikowana", pos);
}

void usunStruct(int pos)
{
    FILE *fp, *temp;
    struct probka bufs;
    int count = 0;

    fp = fopen(nazwaOtwartejBazy, "rb");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal otwarty", nazwaOtwartejBazy);
        exit(1);
    }

    temp = fopen("temp.bin", "wb");
    if (temp == NULL)
    {
        printf("\n Tymczasowy plik nie zostal utworzony");
        fclose(fp);
        exit(1);
    }

    while (fread(&bufs, sizeof(struct probka), 1, fp))
    {
        count++;
        if (count != pos)
        {
            fwrite(&bufs, sizeof(struct probka), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(nazwaOtwartejBazy);
    rename("temp.bin", nazwaOtwartejBazy);

    printf("\n Struktura na pozycji %d zostala usunieta", pos);
}

void utworzBaze(void)
{
    FILE *fp;
    char nazwa[12];
    char odpowiedz;

    if (bazaOtwarta)
    {
        printf("\n Plik minibazy %s jest otwarty. Czy zamknac plik T/N?", nazwaOtwartejBazy);
        odpowiedz = getch();
        if (odpowiedz == 'T' || odpowiedz == 't')
        {
            bazaOtwarta = 0;
        }
        else
        {
            printf("\n Powrot do menu glownego.");
            return;
        }
    }

    printf("\n Wymagania co do nazwy: ");
    printf("\n 1. Max 11 znakow dlugosci ");
    printf("\n 2. format 'bazaXX.dat', gdzie 'XX' to dwie cyfry, a '.dat' to rozszerzenie pliku ");
    printf("\n 3. Pierwsze cztery znaki musza byc 'baza' ");
    printf("\n 4. Nastepne dwa znaki musza byc cyframi. ");
    printf("\n 5. Ostatnie cztery znaki musza byc '.dat'\n");
    printf("\n Podaj nazwe nowej minibazy: ");
    scanf("%11s", nazwa);

    if (!sprawdzNazweBazy(nazwa))
    {
        printf("\n Niepoprawna nazwa bazy.");
        return;
    }

    strcpy(nazwaOtwartejBazy, nazwa);

    fp = fopen(nazwaOtwartejBazy, "rb");
    if (fp != NULL)
    {
        fclose(fp);
        printf("\n Plik %s juz istnieje. Wybierz inna nazwe.", nazwaOtwartejBazy);
        return;
    }

    fp = fopen(nazwaOtwartejBazy, "w+b");
    if (fp == NULL)
    {
        printf("\n Plik %s nie zostal utworzony", nazwaOtwartejBazy);
        exit(1);
    }

    struct probka tablicaStruktur[] =
    {
        {"BD234", "tkanka", "2014.02.10", "Bory Dolnoslaskie", "Zagan", 15.2579, 51.5585, "J.Karwanski"},
        {"LNR028","odchody", "2016.02.18", "Lasy Napiwodzko-Ramuckie", "Nidzica/Jedwabno", 19.82024, 53.74159, "M. Szewczyk"},
        {"PK008","mocz", "2016.01.10", "Puszcza Kampinoska", "Kampinoska", 20.51367, 52.36366, "M. Szewczyk"},
        {"WE27","odchody", "2023.01.10", "Wysoczyzna Elbląska", "Kadyny", 20.48580, 54.07302, "J.Sparzak"}
    };

    fwrite(tablicaStruktur, sizeof(struct probka), sizeof(tablicaStruktur) / sizeof(struct probka), fp);

    fclose(fp);
    printf("\n Nowy plik %s zostal utworzony", nazwaOtwartejBazy);
    bazaOtwarta = 1;
}


