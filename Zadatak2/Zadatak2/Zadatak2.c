#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 50

//definira se struktura
typedef struct person {
    char name[MAX];
    char surname[MAX];
    int birthYear;
    struct person* next;
}_person;

void addBeginning(_person** head);

void printList(_person* head);

void addEnd(_person** head);

void findbySurname(_person* head, char* surname);

void deleteBySurname(_person** head, char* surname);

//Glavna funkcija
int main() {
    _person* head = NULL;

    int choice;

    printf("\nOdaberite operaciju:\n");
    printf("1. Dodavanje nove osobe na pocetak liste\n");
    printf("2. Dodavanje nove osobe na kraj liste\n");
    printf("3. Ispis liste\n");
    printf("4. Pronalazak osobe po prezimenu\n");
    printf("5. Brisanje osobe po prezimenu\n");
    printf("6. Izlaz iz programa\n");
    printf("Izbor: ");
    scanf_s("%d", &choice);

    switch (choice != 6) {
    case 1:
        addBeginning(&head);
        break;
    case 2:
        addEnd(&head);
        break;
    case 3:
        printList(head);
        break;
    case 4: {
        char surname[MAX];
        printf("\nUnesite prezime: ");
        scanf_s("%s", surname);
        findbySurname(head, surname);
        break;
    }
    case 5: {
        char surname[MAX];
        printf("\nUnesite prezime za brisanje: ");
        scanf_s("%s", surname);
        deleteBySurname(&head, surname);
        break;
    }
    }
}


//funkcija za dinamicko dodavanje osobe na pocetak liste
void addBeginning(_person** head) {

    _person* newPerson = (_person*)malloc(sizeof(_person));

    if (newPerson == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    printf("Unesite ime i prezime: \n");
    scanf_s("%s %s", newPerson->name, newPerson->surname);
    printf("Unesite godinu rodenja: \n");
    scanf_s("%d", &newPerson->birthYear);

    newPerson->next = *head;
    *head = newPerson;
}


//funkcija za ispis liste
void printList(_person* head) {
    _person* temp = head;

    while (temp != NULL) {
        printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }
}


//funkcija za dinamicko dodavanje osobe na kraj liste
void addEnd(_person** head) {
    _person* newPerson = (_person*)malloc(sizeof(_person));

    if (newPerson == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    printf("Unesite ime i prezime: \n");
    scanf_s("%s %s", newPerson->name, newPerson->surname);
    printf("Unesite godinu rodenja: \n");
    scanf_s("%d", &newPerson->birthYear);

    newPerson->next = NULL;

    if (*head == NULL) {
        *head = newPerson;
    }
    else {
        _person* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPerson;
    }
}


//funkcija za pronalazak elementa(osobe) po prezimenu
void findbySurname(_person* head, char* surname) {
    _person* temp = head;

    int found = 0;

    while (temp != NULL) {
        if (strcmp(temp->surname, surname) == 0) {
            printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n", temp->name, temp->surname, temp->birthYear);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Osoba sa prezimenom %s nije pronadena.\n", surname);
    }
}


//funkcija za brisanje elementa(osobe) po prezimenu
void deleteBySurname(_person** head, char* surname) {
    _person* current = *head;
    _person* prev = NULL;

    while (current != NULL && strcmp(current->surname, surname) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Osoba sa prezimenom %s nije pronadena.\n", surname);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    }
    else {
        prev->next = current->next;
    }

    free(current);
    printf("Osoba sa prezimenom %s je obrisana.\n", surname);
}
