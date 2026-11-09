#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
    double value;
    struct Node* next;
} Node;

int push(Node** head, double value);
double pop(Node** head);
double postfix(char* filename);

int main() {
    char filename[100];
    printf("Unesite ime datoteke:\n");
    scanf("%s", filename);

    double result = postfix(filename);

    printf("Rezultat: %lf\n", result);

    return 0;
}

int push(Node** head, double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return -1;
    }
    newNode->value = value;
    newNode->next = *head;
    *head = newNode;
    return 0;
}

double pop(Node** head) {
    if (*head == NULL) {
        printf("Greska: Prazan stog.\n");
        return 0;
    }
    Node* temp = *head;
    double value = temp->value;
    *head = temp->next;
    free(temp);
    return value;
}

double postfix(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Greska pri otvaranju file-a.\n");
        return 0;
    }

    Node* head = NULL;

    char buffer[50];
    while (fscanf(file, "%s", buffer) == 1) {
        char* endptr;
        double num = strtod(buffer, &endptr);

        if (*endptr == '\0') {
            push(&head, num);
        }

        else {
            double second = pop(&head);
            double first = pop(&head);
            double result;

            switch (buffer[0]) {
            case '+':
                result = first + second;
                break;
            case '-':
                result = first - second;
                break;
            case '*':
                result = first * second;
                break;
            case '/':
                result = first / second;
                break;
            default:
                printf("Greska: Nepoznata operacija.\n");
                return 0;
            }
            push(&head, result);
        }

    }
    fclose(file);
    double finalResult = pop(&head);

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return finalResult;
}