//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct Carte {
//	int id;
//	float pret;
//	char* autor;
//	char* editura;
//};
//typedef struct Carte Carte;
//typedef struct Nod Nod;
//
//struct Nod {
//	Carte info;
//	Nod* next;
//};
//
//Carte citesteCarteDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Carte c;
//	token = strtok(buffer, delimitator);
//	c.id = atoi(token);
//	c.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	c.autor = malloc(strlen(token) + 1);
//	strcpy_s(c.autor, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	c.editura = malloc(strlen(token) + 1);
//	strcpy_s(c.editura, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return c;
//}
//
//void afiseazaCarte(Carte c) {
//	printf("Id:%d\n", c.id);
//	printf("Pret:%5.2f\n", c.pret);
//	printf("Autor:%s\n", c.autor);
//	printf("Editura:%s\n\n", c.editura);
//}
//
//void pushStack(Nod** stiva, Carte carteNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = carteNoua;
//	nou->next = (*stiva);
//	(*stiva) = nou;
//}
//
//unsigned char isStackEmpty(Nod* stiva) {
//	return stiva == NULL;
//}
//
//Carte popStack(Nod** stiva) {
//	if (*stiva) {
//		Nod* temp = (*stiva);
//		Carte c = temp->info;
//		(*stiva) = temp->next;
//		free(temp);
//		return c;
//	}
//	else {
//		return (Carte) { -1, 0, NULL, NULL };
//	}
//}
//
//Nod* citesteStivaDinFiser(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* stiva = NULL;
//	while (!feof(f)) {
//		pushStack(&stiva, citesteCarteDinFisier(f));
//	}
//	fclose(f);
//	return stiva;
//}
//
//void dezalocaStiva(Nod** stiva) {
//	while (*stiva) {
//		Carte c = popStack(stiva);
//		free(c.autor);
//		free(c.editura);
//	}
//}
//
//int size(Nod* stiva) {
//	int contor = 0;
//	while (stiva) {
//		contor++;
//		stiva = stiva->next;
//	}
//	return contor;
//
//}
//
//float calculeazaPretTotal(Nod** stiva) {
//	Nod* temp = NULL;
//	float suma = 0;
//	while (!isStackEmpty(*stiva)) {
//		Carte c = popStack(stiva);
//		suma += c.pret;
//		pushStack(&temp, c);
//	}
//	while (!isStackEmpty(temp)) {
//		pushStack(stiva, popStack(&temp));
//	}
//	return suma;
//}
//
//
//Carte getCarteByID(Nod** stiva, int id) {
//	Nod* temp = NULL;
//	Carte rezultat = (Carte){ -1, 0, NULL, NULL };
//	while (!isStackEmpty(*stiva)) {
//		Carte c = popStack(stiva);
//		if (c.id == id && rezultat.id == -1) {
//			rezultat = c;
//		}
//		pushStack(&temp, c);
//	}
//	while (!isStackEmpty(temp)) {
//		pushStack(stiva, popStack(&temp));
//	}
//	return rezultat;
//}
//
//int main() {
//	Nod* stiva = citesteStivaDinFiser("carti.txt");
//	Carte c1 = popStack(&stiva);
//	afiseazaCarte(c1);
//
//	float suma = calculeazaPretTotal(&stiva);
//	printf("Suma:%5.2f\n", suma);
//
//	Carte rezultat = getCarteByID(&stiva, 1);
//	afiseazaCarte(rezultat);
//
//}