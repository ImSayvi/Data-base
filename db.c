#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char nazwaOtwartegoPliku[12];

struct SilnikElektryczny {
    char model[30];
    char producent[30];
    int moc; // w kilowatach
    int obroty; // obroty na minutê
    double cena; // w z³otówkach
};

void menu(void);
void otworzBazeDanych(void);
void utworzNowaBaze(void);
void przegladBazy(void);
void sortowanie(void);
void usunBaze(void);
void zakonczProgram(void);
int sprawdzNazweBazy(char *nazwa);

int main() {
    menu();
    return 0;
}

void menu(void) {
    char ch;
    while (1) {
        system("cls");
        printf("\n ============================");
        printf("\n 1. Otwórz bazê danych");
        printf("\n 2. Utwórz now¹ bazê");
        printf("\n 3. Przegl¹d bazy");
        printf("\n 4. Sortowanie bazy");
        printf("\n 5. Usuñ bazê");
        printf("\n 6. Zakoñcz program");
        printf("\n ===========================");
        printf("\n Wybierz opcjê :");
        fflush(stdin);
        ch = getchar();
        switch (ch) {
            case '1':
                otworzBazeDanych();
                break;
            case '2':
                utworzNowaBaze();
                break;
            case '3':
                przegladBazy();
                break;
            case '4':
                sortowanie();
                break;
            case '5':
                usunBaze();
                break;
            case '6':
                zakonczProgram();
                return;
            default:
                printf("\n Nieprawid³owy wybór. Spróbuj ponownie.");
        }
    }
}

void otworzBazeDanych() {
    char nazwa[12];
    printf("\n Podaj nazwê bazy danych (format bazaXX.dat): ");
    scanf("%s", nazwa);

    if (sprawdzNazweBazy(nazwa)) {
        if (strcmp(nazwa, nazwaOtwartegoPliku) == 0) {
            printf("\n Plik ju¿ jest otwarty.");
            return;
        }

        FILE *plik = fopen(nazwa, "rb+");
        if (plik == NULL) {
            printf("\n Plik nie istnieje.");
            return;
        } else {
            strcpy(nazwaOtwartegoPliku, nazwa);
            printf("\n Plik zosta³ otwarty.");
            fclose(plik);
        }
    } else {
        printf("\n Niepoprawna nazwa pliku.");
    }
}

void utworzNowaBaze() {
    char nazwa[12];
    printf("\n Podaj nazwê nowej bazy danych (format bazaXX.dat): ");
    scanf("%s", nazwa);

    if (sprawdzNazweBazy(nazwa)) {
        if (strcmp(nazwa, nazwaOtwartegoPliku) == 0) {
            printf("\n Plik ju¿ jest otwarty.");
            return;
        }

        FILE *plik = fopen(nazwa, "rb");
        if (plik != NULL) {
            printf("\n Plik o takiej nazwie ju¿ istnieje.");
            fclose(plik);
            return;
        }

        plik = fopen(nazwa, "wb");
        if (plik == NULL) {
            printf("\n Nie uda³o siê utworzyæ pliku.");
            return;
        } else {
            strcpy(nazwaOtwartegoPliku, nazwa);
            printf("\n Nowy plik bazy danych zosta³ utworzony.");
            fclose(plik);
        }
    } else {
        printf("\n Niepoprawna nazwa pliku.");
    }
}

void przegladBazy() {
    if (strcmp(nazwaOtwartegoPliku, "") == 0) {
        printf("\n Brak otwartej bazy danych.");
        return;
    }
    // implementacja przegl¹dania bazy
}

void sortowanie() {
    if (strcmp(nazwaOtwartegoPliku, "") == 0) {
        printf("\n Brak otwartej bazy danych.");
        return;
    }

    char ch;
    printf("\n Pola bazy:");
    printf("\n 1. model");
    printf("\n 2. producent");
    printf("\n 3. moc");
    printf("\n 4. obroty");
    printf("\n 5. cena");
    printf("\n Podaj numer pola wg którego baza bêdzie sortowana: ");
    ch = getchar();
    // implementacja sortowania
}

void usunBaze() {
    char nazwa[12];
    printf("\n Podaj nazwê bazy danych do usuniêcia (format bazaXX.dat): ");
    scanf("%s", nazwa);

    if (sprawdzNazweBazy(nazwa)) {
        FILE *plik = fopen(nazwa, "rb");
        if (plik == NULL) {
            printf("\n Plik nie istnieje.");
            return;
        }
        fclose(plik);

        if (strcmp(nazwa, nazwaOtwartegoPliku) == 0) {
            strcpy(nazwaOtwartegoPliku, "");
        }

        if (remove(nazwa) == 0) {
            printf("\n Plik zosta³ usuniêty.");
        } else {
            printf("\n Nie uda³o siê usun¹æ pliku.");
        }
    } else {
        printf("\n Niepoprawna nazwa pliku.");
    }
}

void zakonczProgram() {
    if (strcmp(nazwaOtwartegoPliku, "") != 0) {
        printf("\n Czy zapisaæ aktualny stan bazy przed zakoñczeniem? (T/N): ");
        char ch = getchar();
        if (ch == 'T' || ch == 't') {
            // zapisanie stanu bazy
        }
    }
    printf("\n Program zakoñczony.");
}

int sprawdzNazweBazy(char *nazwa) {
    int dlugosc = strlen(nazwa);
    if (dlugosc < 9 || dlugosc > 10) return 0;

    if (strncmp(nazwa, "baza", 4) != 0) return 0;

    for (int i = 4; i < dlugosc - 4; i++) {
        if (!isdigit(nazwa[i])) return 0;
    }
    return 1;
}

