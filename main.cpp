#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

struct Produkt {
    double cena;
    char nazwa[100];
};

int main() {
    FILE *wej, *wyj;
    double kwotaDocelowa;
    Produkt lista[32];
    int n = 0;

    wej = fopen("wej.txt", "r");
    wyj = fopen("wyj.txt", "w");

    if (!wej || !wyj) {
        printf("Blad otwarcia plikow!\n");
        return 1;
    }

    fscanf(wej, "%le", &kwotaDocelowa);

    while (fscanf(wej, "%le ", &lista[n].cena) != EOF && n < 32) {
        fgets(lista[n].nazwa, 100, wej);
        lista[n].nazwa[strcspn(lista[n].nazwa, "\n")] = 0;
        n++;
    }

    unsigned long long kombinacje = 1ULL << n; 
    int znaleziono = 0;

    for (unsigned long long i = 1; i < kombinacje; i++) {
        double sumaAktualna = 0.0;
        
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                sumaAktualna += lista[j].cena;
            }
        }

        if (fabs(sumaAktualna - kwotaDocelowa) < 0.001) {
            znaleziono = 1;
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) {
                    fprintf(wyj, "%d ", j + 1);
                }
            }
            fprintf(wyj, "\n");
        }
    }

    if (!znaleziono) {
        fprintf(wyj, "Brak konfiguracji.\n");
    }

    fclose(wej);
    fclose(wyj);
    printf("Przetwarzanie zakonczone. Sprawdz plik wyj.txt\n");
    _getch();
    return 0;
}
