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
//
//typedef struct Carte Carte;
//typedef struct Nod Nod;
//
//struct Nod {
//	Carte info;
//	Nod* next;
//};
//
//Carte initializareCarte(int id, float pret, const char* autor, const char* editura) {
//	Carte c;
//	c.id = id;
//	c.pret = pret;
//	c.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
//	strcpy_s(c.autor, strlen(autor) + 1, autor);
//	c.editura = (char*)malloc(sizeof(char) * (strlen(editura) + 1));
//	strcpy_s(c.editura, strlen(editura) + 1, editura);
//	return c;
//}
//
//Carte citireCarteDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Carte c;
//	token = strtok(buffer, delimitator);
//	c.id = atoi(token);
//	c.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	c.autor = (char*)malloc(strlen(token) + 1);
//	strcpy_s(c.autor, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	c.editura = (char*)malloc(strlen(token) + 1);
//	strcpy_s(c.editura, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return c;
//}
//
//void afisareCarte(Carte c) {
//	printf("Id:%d\n", c.id);
//	printf("Pret:%5.2f\n", c.pret);
//	printf("Autor:%s\n", c.autor);
//	printf("Editura:%s\n\n", c.editura);
//}
//
//void afisareListaCarti(Nod* cap) {
//	while (cap) {
//		afisareCarte(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaCarteLaFinal(Nod** cap, Carte carteNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = carteNoua;
//	nou->next = NULL;
//	if ((*cap) == NULL) {
//		(*cap) = nou;
//	}
//	else {
//		Nod* p = (*cap);
//		while (p->next != NULL) {
//			p = p->next;
//		}
//		p->next = nou;
//	}
//}
//
//void adaugaCarteLaInceput(Nod** cap, Carte carteNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = carteNoua;
//	nou->next = (*cap);
//	(*cap) = nou;
//}
//
//Nod* citireListaDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* lista = NULL;
//	while (!feof(f)) {
//		adaugaCarteLaFinal(&lista, citireCarteDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//
//float calculeazaPretMediu(Nod* lista) {
//	if (!lista) {
//		return 0;
//	} 
//	int count = 0;
//	float suma = 0;
//	while (lista) {
//		suma += lista->info.pret;
//		count++;
//		lista = lista->next;
//	}
//	return suma / count;
//}
//
//char* getCeaMaiScumpaCarte(Nod* lista) {
//	float pretulMaxim = 0;
//	char* autorScump = NULL;
//	while (lista) {
//		if (lista->info.pret > pretulMaxim) {
//			pretulMaxim = lista->info.pret;
//			autorScump = lista->info.autor;
//		}
//		lista = lista->next;
//	}
//	if (pretulMaxim > 0) {
//		char* autor = (char*)malloc(strlen(autorScump));
//		strcpy_s(autor, strlen(autorScump) + 1, autorScump);
//		return autor;
//	}
//	else {
//		return NULL;
//	}
//}
//
//void dezalocare(Nod** cap) {
//	while ((*cap)) {
//		Nod* aux = (*cap);
//		(*cap) = (*cap)->next;
//		free(aux->info.editura);
//		free(aux->info.autor);
//		free(aux);
//	}
//}
//
//int main() {
//	Nod* cap = NULL;
//	cap = citireListaDinFisier("carti.txt");
//	afisareListaCarti(cap);
//
//	printf("Pretul mediu este:%5.2f\n", calculeazaPretMediu(cap));
//	printf("Cartea cea mai scumpa apartine autorului:%s\n", getCeaMaiScumpaCarte(cap));
//
//	dezalocare(&cap);
//}