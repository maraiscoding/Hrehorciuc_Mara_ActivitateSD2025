//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct Vacanta {
//	int id;
//	float pret;
//	int nrPers;
//	char* destinatie;
//	char* hotel;
//};
//
//typedef struct Vacanta Vacanta;
//typedef struct Nod Nod;
//
//struct Nod {
//	Vacanta info;
//	Nod* next;
//};
//
//void afisareVacanta(Vacanta v) {
//	printf("Id:%d\n", v.id);
//	printf("Pret:%5.2f\n", v.pret);
//	printf("Numar persoane:%d\n", v.nrPers);
//	printf("Destinatie:%s\n", v.destinatie);
//	printf("Hotel:%s\n\n", v.hotel);
//}
//
//void afisareListaVacante(Nod* cap) {
//	while (cap) {
//		afisareVacanta(cap->info);
//		cap = cap->next;
//	}
//}
//
//Vacanta citireVacantaDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Vacanta v;
//	token = strtok(buffer, delimitator);
//	v.id = atoi(token);
//	v.pret = atof(strtok(NULL, delimitator));
//	v.nrPers = atoi(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	v.destinatie = malloc(strlen(token) + 1);
//	strcpy_s(v.destinatie, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	v.hotel = malloc(strlen(token) + 1);
//	strcpy_s(v.hotel, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return v;
//}
//
//void adaugaLaFinal(Nod** cap, Vacanta vacantaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = vacantaNoua;
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
//void adaugaLaInceput(Nod** cap, Vacanta vacantaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = vacantaNoua;
//	nou->next = (*cap);
//	(*cap) = nou;
//}
//
//Nod* citireListaVacante(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* lista = NULL;
//	while (!feof(f)) {
//		adaugaLaFinal(&lista, citireVacantaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//float calculeazaPretMediu(Nod* lista) {
//	if (!lista) {
//		return 0;
//	}
//	float suma = 0;
//	int count = 0;
//	while (lista) {
//		suma += lista->info.pret;
//		count++;
//		lista = lista->next;
//	}
//	return suma / count;
//}
//
//float calculeazaPretulTotalPtDestinatie(Nod* lista, const char* destinatie) {
//	float suma = 0;
//	while (lista) {
//		if (strcmp(lista->info.destinatie, destinatie) == 0) {
//			suma += lista->info.pret;
//		}
//		lista = lista->next;
//	}
//	return suma;
//}
//
//void modificaDestinatie(Nod* lista, const char* destinatie, const char* hotel, const char* hotelNou) {
//	while (lista) {
//		if (strcmp(lista->info.hotel, hotel) == 0 && strcmp(lista->info.destinatie, destinatie) == 0) {
//			free(lista->info.hotel);
//			lista->info.hotel = (char*)malloc(sizeof(char) * (strlen(hotelNou) + 1));
//			strcpy_s(lista->info.hotel, strlen(lista->info.hotel) + 1, hotelNou);
//		}
//		lista = lista->next;
//	}
//}
//
//char* getCeaMaiScumpaVacanta(Nod* lista) {
//	float pretulMaxim = 0;
//	char* hotelScump = NULL;
//	while (lista) {
//		if (lista->info.pret > pretulMaxim) {
//			pretulMaxim = lista->info.pret;
//			hotelScump = lista->info.hotel;
//		}
//		lista = lista->next;
//	}
//	if (pretulMaxim > 0) {
//		char* nou = malloc(strlen(hotelScump));
//		strcpy_s(nou, strlen(hotelScump) + 1, hotelScump);
//		return nou;
//	}
//	else {
//		return NULL;
//	}
//}
//
//int main() {
//	Nod* cap = NULL;
//	cap = citireListaVacante("vacante.txt");
//	afisareListaVacante(cap);
//
//	printf("Pretul mediu al vacantelor agentiei este: %5.2f\n", calculeazaPretMediu(cap));
//	printf("Pretul total al sejururilor din Egipt este: %5.2f\n", calculeazaPretulTotalPtDestinatie(cap, "Egipt"));
//	
//	modificaDestinatie(cap, "Egipt", "Hurgada", "Comandante");
//	printf("Lista dupa modificare:\n");
//	afisareListaVacante(cap);
//
//	printf("%s\n", getCeaMaiScumpaVacanta(cap));
//}