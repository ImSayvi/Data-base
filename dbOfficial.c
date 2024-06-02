#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef char* string;

char nazwaOtwartegoPliku[12];

struct probka {
    char nazwa[10];
    char typ[10];
    char dataPoboru[10];
    char region[20];
    char wataha[30];
    double x;
    double y;
    char kto[20];
};
struct probka pTablica[10];

int main(int argc, char *argv[]) {
    menu();
    return 0;
}

void menu(void) {
    char ch;
    system("cls");

    printf("\n");
    printf(" ============================\n");
    printf(" 1. Otworz baze danych\n");
    printf(" 2. Utworz nowa baze\n");
    printf(" 3. Przeglad bazy\n");
    printf(" 4. Sortowanie bazy\n");
    printf(" 5. Modyfikacja struktury\n");
    printf(" 6. Usun strukture\n");
    printf(" 7. Zakoncz program\n");
    printf(" ============================\n");
    printf(" Wybierz opcje :");
    fflush(stdin);
    do {
        ch = getch();
    } while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5' && ch != '6' && ch != '7' && ch != 27);

    if (ch == '1') {
        otworzBaze();
        przegladBazy();
    } else if (ch == '2') {
        utworzBaze();
        przegladBazy();
    } else if (ch == '3') {
        przegladBazy();
    } else if (ch == '4') {
        sortujBaze();
    } else if (ch == '5') {
        int pos;
        printf("\n Podaj pozycje struktury do modyfikacji: ");
        scanf("%d", &pos);
        modStruct(pos);
    } else if (ch == '6') {
        int pos;
        printf("\n Podaj pozycje struktury do usuniecia: ");
        scanf("%d", &pos);
        usunStruct(pos);
    } else if (ch == 27 || ch == '7') {
        printf("\n Wybrano zakonczenie programu");
        getchar();
        exit(0);
    }
}
