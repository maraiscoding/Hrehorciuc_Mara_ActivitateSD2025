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
//	Nod* st;
//	Nod* dr;
//};
//
//
//void afiseazaVacanta(Vacanta v) {
//	printf("Id:%d\n", v.id);
//	printf("Pret:%5.2f\n", v.pret);
//	printf("Nr. pers:%d\n", v.nrPers);
//	printf("Destinatie:%s\n", v.destinatie);
//	printf("Hotel:%s\n\n", v.hotel);
//}
//
//Vacanta citesteVacantaDinFisier(FILE* f) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, f);
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
//void adaugaVacantaInArbore(Nod** arbore, Vacanta vacantaNoua) {
//	if (!(*arbore)) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = vacantaNoua;
//		nou->st = NULL;
//		nou->dr = NULL;
//		(*arbore) = nou;
//	}
//	else {
//		if ((*arbore)->info.id > vacantaNoua.id) {
//			adaugaVacantaInArbore(&((*arbore)->st), vacantaNoua);
//		}
//		else if ((*arbore)->info.id < vacantaNoua.id) {
//			adaugaVacantaInArbore(&((*arbore)->dr), vacantaNoua);
//		}
//	}
//}
//
//Nod* citesteArboreVacanteDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* arbore = NULL;
//	while (!feof(f)) {
//		adaugaVacantaInArbore(&arbore, citesteVacantaDinFisier(f));
//	}
//	fclose(f);
//	return arbore;
//}
//
//void afiseazaInOrdineSRD(Nod* arbore) {
//	if (arbore) {
//		afiseazaInOrdineSRD(arbore -> st);
//		afiseazaVacanta(arbore->info);
//		afiseazaInOrdineSRD(arbore->dr);
//	}
//}
//
//void afiseazaPreordineRSD(Nod* arbore) {
//	if (arbore) {
//		afiseazaVacanta(arbore->info);
//		afiseazaPreordineRSD(arbore->st);
//		afiseazaPreordineRSD(arbore->dr);
//	}
//}
//
//void afiseazaPostordineSDR(Nod* arbore) {
//	if (arbore) {
//		afiseazaPostordineSDR(arbore->st);
//		afiseazaPostordineSDR(arbore->dr);
//		afiseazaVacanta(arbore->info);
//	}
//}
//
//void dezalocaArbore(Nod** arbore) {
//	if (*arbore) {
//		dezalocaArbore(&(*arbore)->st);
//		dezalocaArbore(&(*arbore)->dr);
//		free((*arbore)->info.destinatie);
//		free((*arbore)->info.hotel);
//		free(*arbore);
//		(*arbore) = NULL;
//	}
//}
//
//Vacanta getVacantaById(Nod* arbore, int id) {
//	Vacanta v;
//	v.id = -1;
//	if (arbore) {
//		if (arbore->info.id < id) {
//			return getVacantaById(arbore->dr, id);
//		}
//		else if (arbore->info.id > id) {
//			return getVacantaById(arbore->st, id);
//		}
//		else {
//			return arbore->info;
//		}
//	}
//	return v;
//}
//
//int determinaNumarNoduri(Nod* arbore) {
//	if (arbore) {
//		int noduriSt = determinaNumarNoduri(arbore->st);
//		int noduriDr = determinaNumarNoduri(arbore->dr);
//		return 1 + noduriSt + noduriDr;
//	}
//	return 0;
//}
//
//float calculeazaPretTotal(Nod* arbore) {
//	if (arbore) {
//		float totalSt = calculeazaPretTotal(arbore->st);
//		float totalDr = calculeazaPretTotal(arbore->dr);
//		return arbore->info.pret + totalSt + totalDr;
//	}
//	return 0;
//}
//
//
//float calculeazaPretTotalDestinatie(Nod* arbore, const char* destinatie) {
//	if (arbore) {
//		float totalSt = calculeazaPretTotalDestinatie(arbore->st, destinatie);
//		float totalDr = calculeazaPretTotalDestinatie(arbore->dr, destinatie);
//		float sumaCrt = 0;
//		if (strcmp(arbore->info.destinatie, destinatie) == 0) {
//			sumaCrt += arbore->info.pret;
//		}
//		return sumaCrt + totalSt + totalDr;
//	}
//	return 0;
//}
//
//int main() { 
//	Nod* arbore = citesteArboreVacanteDinFisier("vacante.txt");
//	printf("Afisare SRD: \n");
//	afiseazaInOrdineSRD(arbore);
//	printf("Afisare RSD: \n");
//	afiseazaPreordineRSD(arbore);
//	printf("Afisare SDR: \n");
//	afiseazaPostordineSDR(arbore);
//
//	printf("Vacanta cu id 1: \n");
//	Vacanta v = getVacantaById(arbore, 1);
//	afiseazaVacanta(v);
//	
//	int nrNoduri = determinaNumarNoduri(arbore);
//	printf("Nr noduri:%d\n", nrNoduri);
//
//
//	float pretTotal = calculeazaPretTotal(arbore);
//	printf("Pret total:%5.2f\n", pretTotal);
//
//	float pretEgipt = calculeazaPretTotalDestinatie(arbore, "Egipt");
//	printf("Pret Egipt:%5.2f\n", pretEgipt);
//}