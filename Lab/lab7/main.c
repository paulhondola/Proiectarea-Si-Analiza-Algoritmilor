#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "arborib.h"

#define MAX_RAND 10000
Pagina *radacina;

void insert_into_file(FILE* f, int count) {
	for (int i = 0; i < count; i++) {
		int x = rand() % MAX_RAND;
		fprintf(f, "%d ", x);
	}
	fprintf(f, "\n");
}

void insert_into_file_ascending(FILE* f, int count) {
	for (int i = 0; i < count; i++) {
		fprintf(f, "%d ", i);
	}
	fprintf(f, "\n");
}

int insert_into_tree(FILE* f) {
	int x = 0, count = 0;
	while (feof(f) == 0) {
		if (fscanf(f, "%d", &x) != 1)
			break;
		count++;
		radacina = insereaza(radacina, x, NULL);
	}

	return count;
}

void erase_from_tree(int count) {
	printf("Arborele-B initial:\n");
	afisare(radacina, 1);
	printf("\n\n");

	for (int i = 1; i <= count; i++) {
		printf("Dupa stergerea lui %d:\n", i);
		radacina = suprima(radacina, i, NULL);
		afisare(radacina, 1);
		printf("\n\n");
	}
}

void get_insert_performance(FILE *f, int count) {
	LARGE_INTEGER frequency;
	LARGE_INTEGER start, end;
	double elapsedTime;

	// Get clock frequency
	QueryPerformanceFrequency(&frequency);

	// Start timer
	QueryPerformanceCounter(&start);

	nr_scindari = 0;
	count = insert_into_tree(f);

	// End timer
	QueryPerformanceCounter(&end);

	// Calculate elapsed time in seconds
	elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	printf("Insert time: %.6f miliseconds\n", elapsedTime * 1000);
	printf("Total splits (nr_scindari): %d\n", nr_scindari);
}

void get_search_performance() {
	TipCheie x = rand() % MAX_RAND;

	LARGE_INTEGER frequency;
	LARGE_INTEGER start, end;
	double elapsedTime;

	// Get clock frequency
	QueryPerformanceFrequency(&frequency);

	// Start timer
	QueryPerformanceCounter(&start);

	nr_pasi_cautare = 0;
	int found = cautare(radacina, x);

	// End timer
	QueryPerformanceCounter(&end);

	// Calculate elapsed time in seconds
	elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	printf("Search time: %.6f microseconds\n", elapsedTime * 1000000);
	printf("Numarul cautat: %d\n", x);
	printf("Numar pasi cautare: %d\n", nr_pasi_cautare);
}

int main(){

	srand(time(NULL));
	FILE* f = NULL;
	int count = 10000;

	/*
	// insert the numbers into a file
	f = fopen("date.txt", "w");
	if (f == NULL) {
		perror("OUTPUT FILE");
		return 1;
	}

	insert_into_file(f, count);

	fclose(f);
	*/

	

	// get the numbers from an input file
	f = fopen("date.txt", "r");

	if(f == NULL){
		perror("INPUT FILE");
		return 1;
	}
	
	get_insert_performance(f, count);
	get_search_performance();

	return 0;
}