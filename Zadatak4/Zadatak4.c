#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct polynom* poly;

struct polynom {
    int coeff;
    int exp;
    poly term[MAX];
    int n;
};

void printPolynomial(poly p);
void readPolynomialFromLine(poly p, char* line);
int readPolynomials(const char* filename, poly polys[], int maxPolys);
void addPolynomials(poly p1, poly p2, poly result);
void multiplyPolynomials(poly p1, poly p2, poly result);
void insertSorted(poly p, int coeff, int exp);


int main() {
    poly polys[MAX];
    int nPolys = readPolynomials("Polinomi.txt", polys, MAX);

    printf("Ucitano %d polinoma:\n", nPolys);

    for (int i = 0; i < nPolys; i++) {
        printf("P%d(x) = ", i + 1);
        printPolynomial(polys[i]);
    }

    if (nPolys >= 2) {
        struct polynom Sum, Product;

        addPolynomials(polys[0], polys[1], &Sum);
        multiplyPolynomials(polys[0], polys[1], &Product);

        printf("\nZbroj polinoma: ");
        printPolynomial(&Sum);

        printf("\nUmnozak polinoma: ");
        printPolynomial(&Product);
    }

    return 0;
}

//Funkcija za ispis polinoma
void printPolynomial(poly p) {
    for (int i = 0; i < p->n; i++) {
        int coeff = p->term[i]->coeff;
        int exp = p->term[i]->exp;

        if (i > 0 && coeff > 0) {
            printf("+");
        }

        if (exp == 0) {
            printf("%d", coeff);
        }
        else if (exp == 1) {
            printf("%dx", coeff);
        }
        else {
            printf("%dx^%d", coeff, exp);
        }
    }
    printf("\n");
}

//Funkcija za citanje polinoma iz linije
void readPolynomialFromLine(poly p, char* line) {
    p->n = 0;
    int coeff, exp;
    char* ptr = line;

    while (sscanf(ptr, "%d %d", &coeff, &exp) == 2) {
        insertSorted(p, coeff, exp);
        while (*ptr && *ptr != ' ') {
            ptr++;
        }
        while (*ptr && *ptr == ' ') {
            ptr++;
        }
    }
}

//Funkcija za citanje polinoma iz datoteke
int readPolynomials(const char* filename, poly polys[], int maxPolys) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Greska pri otvaranju datoteke %s\n", filename);
        return 0;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < maxPolys) {
        polys[count] = (poly)malloc(sizeof(struct polynom));
        readPolynomialFromLine(polys[count], line);
        count++;
    }

    fclose(file);
    return count;
}

//Funkcija za zbrajanje polinoma
void addPolynomials(poly p1, poly p2, poly result) {
    result->n = 0;

    for (int i = 0; i < p1->n; i++) {
        insertSorted(result, p1->term[i]->coeff, p1->term[i]->exp);
    }
    for (int i = 0; i < p2->n; i++) {
        insertSorted(result, p2->term[i]->coeff, p2->term[i]->exp);
    }
}

//Funkcija za mnozenje polinoma
void multiplyPolynomials(poly p1, poly p2, poly result) {
    result->n = 0;

    for (int i = 0; i < p1->n; i++) {
        for (int j = 0; j < p2->n; j++) {
            int coeff = p1->term[i]->coeff * p2->term[j]->coeff;
            int exp = p1->term[i]->exp + p2->term[j]->exp;
            insertSorted(result, coeff, exp);
        }
    }
}

//Funkcija za umetanje polinoma u sortiranu listu
void insertSorted(poly p, int coeff, int exp) {
    poly t = (poly)malloc(sizeof(struct polynom));
    t->coeff = coeff;
    t->exp = exp;
    t->n = 0;

    int i = 0;

    while (i < p->n && p->term[i]->exp > exp) {
        i++;
    }

    if (i < p->n && p->term[i]->exp == exp) {
        p->term[i]->coeff += coeff;
        free(t);
        return;
    }

    for (int j = p->n; j < i; j--) {
        p->term[j] = p->term[j - 1];
    }

    p->term[i] = t;
    p->n++;
}
