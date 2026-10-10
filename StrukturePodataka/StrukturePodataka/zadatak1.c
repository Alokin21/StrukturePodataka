/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 50
#define BufferSize 256
#define maxPoints 100.0

//Definiranje strukture student s podacima ime, prezime i broj bodova
typedef struct student {
	char name[N];
	char surname[N];
	float points;
}_stud;

//Funkcija za odredivanje broja redaka u datoteci u svrhu dinamične alokacije memorije
int countLines(char* fp) {
	int lines = 0;

	FILE* file = fopen("studenti.txt", "r");

	if (file == NULL) {
		printf("Dogodila se greska pri otvaranju datoteke(count).\n");
		return -1;
	}

	char buffer[BufferSize];

	while (fgets(buffer, BufferSize, file)) {
		lines++;
	}

	fclose(file);
	return lines;
}

//Funkcija za ucitavanje podataka studenata po zadanoj strukturi
int loadStudents(char* dat, _stud* student, int studNum) {
	int i;

	FILE* file = fopen(dat, "r");

	if (!file) {
		printf("Dogodila se greska pri otvaranju datoteke(load).\n");
		return -1;
	}

	for (i = 0; i < studNum; i++) {
		fscanf(file, "%s %s %f", student[i].name, student[i].surname, &student[i].points);
	}

	fclose(file);
	return 0;
}


//Glavna funkcija
int main() {
	int studNum;
	int i;

	const char* fp = "studenti.txt";
	studNum = countLines(fp);

	_stud* student = (_stud*)malloc(studNum * sizeof(_stud));

	if (!student) {
		printf("Dogodila se greska pri alokaciji memorije.\n");
		return -1;
	}

	if (loadStudents(fp, student, studNum) != 0) {
		printf("Dogodila se greska pri ucitavanju podataka studenata.\n");
		return -1;
	}

	for (i = 0; i < studNum; i++) {
		float relativePoints = ((float)student[i].points / maxPoints) * 100.0;
		printf("%s %s %.2f %.2f\n", student[i].name, student[i].surname, student[i].points, relativePoints);
	}

	free(student);

	return 0;
}