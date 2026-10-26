#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void addAfterSpecificElement(_person** head, char* surname);

void addBeforeSpecificElement(_person** head, char* surname);

void sortBySurname(_person** head);

void writeListToFile(_person* head, const char* filename);

void readListFromFile(_person** head, const char* filename);

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
    printf("6. Dodavanje nove osobe iza odredene osobe po prezimenu\n");
    printf("7. Dodavanje nove osobe ispred odredene osobe po prezimenu\n");
    printf("8. Sortiranje liste po prezimenu\n");
    printf("9. Upisivanje liste u datoteku\n");
    printf("10. Citanje liste iz datoteke\n");
    printf("11. Izlaz iz programa\n");
    printf("Izbor: ");
    scanf("%d", &choice);

    char surname[MAX];
    char filename[MAX];

    switch (choice) {
    case 1:
        addBeginning(&head);
        break;
    case 2:
        addEnd(&head);
        break;
    case 3:
        printList(head);
        break;
    case 4:
        printf("\nUnesite prezime: ");
        scanf("%s", &surname);
        findbySurname(head, surname);
        break;

    case 5:
        printf("\nUnesite prezime za brisanje: ");
        scanf("%s", &surname);
        deleteBySurname(&head, surname);
        break;

    case 6:
        printf("\nUnesite prezime iza kojeg zelite dodati novu osobu: ");
        scanf("%s", &surname);
        addAfterSpecificElement(&head, surname);
        break;

    case 7:
        printf("\nUnesite prezime ispred kojeg zelite dodati novu osobu: ");
        scanf("%s", &surname);
        addBeforeSpecificElement(&head, surname);
        break;

    case 8:
        sortBySurname(&head);
        break;

    case 9:
        printf("\nUnesite ime datoteke za upis: ");
        scanf("%s", &filename);
        writeListToFile(head, filename);
        break;

    case 10:
        printf("\nUnesite ime datoteke za citanje: ");
        scanf("%s", &filename);
        readListFromFile(&head, filename);
        break;

    }
}


//funkcija za dinamicko dodavanje osobe na pocetak liste
void addBeginning(_person** head) {

    _person* newPerson = (_person*)malloc(sizeof(_person));

    if (newPerson == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return;
    }

    printf("Unesite ime i prezime: \n");
    scanf("%s %s", newPerson->name, newPerson->surname);
    printf("Unesite godinu rodenja: \n");
    scanf("%d", &newPerson->birthYear);

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
        printf("Greska pri alokaciji memorije.\n");
        return;
    }

    printf("Unesite ime i prezime: \n");
    scanf("%s %s", newPerson->name, newPerson->surname);
    printf("Unesite godinu rodenja: \n");
    scanf("%d", &newPerson->birthYear);

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
        printf("Osoba s prezimenom %s nije pronadena.\n", surname);
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
        printf("Osoba s prezimenom %s nije pronadena.\n", surname);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    }
    else {
        prev->next = current->next;
    }

    free(current);
    printf("Osoba s prezimenom %s je obrisana.\n", surname);
}

//funkcija za dodavanje elementa(osobe) iza odredene osobe po prezimenu
void addAfterSpecificElement(_person** head, char* surname) {
    _person* current = *head;

    while (current != NULL && strcmp(current->surname, surname) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Osoba s prezimenom %s nije pronadena.\n", surname);
        return;
    }

    _person* newPerson = (_person*)malloc(sizeof(_person));

    if (newPerson == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return;
    }

    printf("Unesite ime i prezime: \n");
    scanf("%s %s", newPerson->name, newPerson->surname);
    printf("Unesite godinu rodenja: \n");
    scanf("%d", &newPerson->birthYear);

    newPerson->next = current->next;
    current->next = newPerson;

    printf("Nova osoba je dodana iza osobe s prezimenom %s.\n", surname);
}

//funkcija za dodavanje elementa(osobe) ispred odredene osobe po prezimenu
void addBeforeSpecificElement(_person** head, char* surname) {
    _person* current = *head;
    _person* prev = NULL;

    while (current != NULL && strcmp(current->surname, surname) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Osoba s prezimenom %s nije pronadena.\n", surname);
        return;
    }

    _person* newPerson = (_person*)malloc(sizeof(_person));

    if (newPerson == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return;
    }

    printf("Unesite ime i prezime: \n");
    scanf("%s %s", newPerson->name, newPerson->surname);
    printf("Unesite godinu rodenja: \n");
    scanf("%d", &newPerson->birthYear);

    newPerson->next = current;

    if (prev == NULL) {
        *head = newPerson;
    }
    else {
        prev->next = newPerson;
    }

    printf("Nova osoba je dodana ispred osobe s prezimenom %s.\n", surname);
}

//funkcija za sortiranje liste po prezimenu
void sortBySurname(_person** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    _person* sorted = NULL;
    _person* current = *head;

    while (current != NULL) {
        _person* next = current->next;

        if (sorted == NULL || strcmp(current->surname, sorted->surname) < 0) {
            current->next = sorted;
            sorted = current;
        }
        else {
            _person* temp = sorted;
            while (temp->next != NULL && strcmp(current->surname, temp->next->surname) >= 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *head = sorted;
    printf("Lista je sortirana po prezimenu.\n");
}

void writeListToFile(_person* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    _person* temp = head;
    while (temp != NULL) {
        fprintf(file, "Ime: %s, Prezime: %s, Godina rodenja: %d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }

    fclose(file);
    printf("Lista je upisana u datoteku %s.\n", filename);
}

void readListFromFile(_person** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        _person* newPerson = (_person*)malloc(sizeof(_person));
        if (newPerson == NULL) {
            printf("Greska pri alokaciji memorije.\n");
            fclose(file);
            return;
        }

        sscanf(line, "Ime: %s, Prezime: %s, Godina rodenja: %d", newPerson->name, newPerson->surname, &newPerson->birthYear);
        newPerson->next = *head;
        *head = newPerson;
    }

    fclose(file);
    printf("Lista je ucitana iz datoteke %s.\n", filename);
}