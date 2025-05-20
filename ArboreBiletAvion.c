//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct BiletAvion {
//	int id;
//	float pret;
//	char* destinatie;
//	char* poartaImbarcare;
//};
//
//typedef struct BiletAvion Bilet;
//typedef struct Nod Nod;
//
//struct Nod {
//	Bilet info;
//	Nod* st;
//	Nod* dr;
//};
//
//Bilet citireBiletDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Bilet b;
//	token = strtok(buffer, delimitator);
//	b.id = atoi(token);
//	b.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	b.destinatie = malloc(strlen(token) + 1);
//	strcpy_s(b.destinatie, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	b.poartaImbarcare = malloc(strlen(token) + 1);
//	strcpy_s(b.poartaImbarcare, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return b;
//}
//
//void afisareBilet(Bilet b) {
//	printf("Id:%d\n", b.id);
//	printf("Pret:%5.2f\n", b.pret);
//	printf("Destinatie:%s\n", b.destinatie);
//	printf("Poarta imbarcare:%s\n\n", b.poartaImbarcare);
//}
//
//void adaugaBiletInArbore(Nod** arbore, Bilet biletNou) {
//	if (!(*arbore)) {
//		Nod* nou=(Nod*)malloc(sizeof(Nod));
//		nou->info=biletNou;
//		nou->st = NULL;
//		nou->dr = NULL;
//		(*arbore) = nou;
//	}
//	else {
//		if ((*arbore)->info.id > biletNou.id) {
//			adaugaBiletInArbore(&((*arbore)->st), biletNou);
//		}
//		else if ((*arbore)->info.id < biletNou.id) {
//			adaugaBiletInArbore(&((*arbore)->dr), biletNou);
//		}
//	}
//}
//
//Nod* citesteArboreDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* arbore = NULL;
//	while (!feof(f)) {
//		adaugaBiletInArbore(&arbore, citireBiletDinFisier(f));
//	}
//	fclose(f);
//	return(arbore);
//}
//
//void afisareInOrdineSRD(Nod* arbore) {
//	if (arbore) {
//		afisareInOrdineSRD(arbore->st);
//		afisareBilet(arbore->info);
//		afisareInOrdineSRD(arbore->dr);
//	}
//}
//
//void afisarePreordineRSD(Nod* arbore) {
//	if (arbore) {
//		afisareBilet(arbore->info);
//		afisarePreordineRSD(arbore->st);
//		afisarePreordineRSD(arbore->dr);
//	}
//}
//
//void afisarePostordineSDR(Nod* arbore) {
//	if (arbore) {
//		afisarePostordineSDR(arbore->st);
//		afisarePostordineSDR(arbore->dr);
//		afisareBilet(arbore->info);
//	}
//}
//
//
//void dezalocareArbore(Nod** arbore) {
//	if (*arbore) {
//		dezalocareArbore(&(*arbore)->st);
//		dezalocareArbore(&(*arbore)->dr);
//		free((*arbore)->info.destinatie);
//		free((*arbore)->info.poartaImbarcare);
//		free(*arbore);
//		(*arbore) = NULL;
//	}
//}
//
//Bilet getBiletById(Nod* arbore, int id) {
//	Bilet b;
//	b.id = -1;
//	if (arbore) {
//		if (arbore->info.id < id) {
//			return getBiletById(arbore->dr, id);
//		}
//		else if (arbore->info.id > id) {
//			return getBiletById(arbore->st, id);
//		}
//		else {
//			return arbore->info;
//		}
//	}
//	return b;
//}
//
//int determinaNrNoduri(Nod* arbore) {
//	if (arbore) {
//		int noduriSt = determinaNrNoduri(arbore->st);
//		int noduriDr = determinaNrNoduri(arbore->dr);
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
//
//	}
//	return 0;
//}
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
//	Nod* arbore = citesteArboreDinFisier("bilete.txt");
//	printf("Afisare SRD:\n");
//	afisareInOrdineSRD(arbore);
//
//	Bilet b = getBiletById(arbore, 4);
//	afisareBilet(b);
//
//	int nrNoduri = determinaNrNoduri(arbore);
//	printf("Nr noduri:%d\n", nrNoduri);
//
//	float total = calculeazaPretTotal(arbore);
//	printf("Pret total:%5.2f\n", total);
//
//	float totalRoma = calculeazaPretTotalDestinatie(arbore, "Roma");
//	printf("Pret total Roma:%5.2f\n", totalRoma);
//
//}