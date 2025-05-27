//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct Laptop {
//	int id;
//	float pret;
//	char* marca;
//	char* procesor;
//};
//
//typedef struct Laptop Laptop;
//typedef struct Nod Nod;
//
//struct Nod {
//	Laptop info;
//	Nod* st;
//	Nod* dr;
//	int gradEchilibru;
//};
//
//
//void afiseazaLaptop(Laptop l) {
//	printf("Id:%d\n", l.id);
//	printf("Pret:%5.2f\n", l.pret);
//	printf("Marca:%s\n", l.marca);
//	printf("Procesor:%s\n\n", l.procesor);
//}
//
//Laptop citesteLaptopDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Laptop l;
//	token = strtok(buffer, delimitator);
//	l.id = atoi(token);
//	l.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	l.marca = (char*)malloc(strlen(token) + 1);
//	strcpy_s(l.marca, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	l.procesor = (char*)malloc(strlen(token) + 1);
//	strcpy_s(l.procesor, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return l;
//}
//
//void rotireStanga(Nod** arbore) {
//	Nod* aux = (*arbore)->dr;
//	(*arbore)->dr = aux->st;
//	aux->st = (*arbore);
//	(*arbore) = aux;
//	(*arbore)->gradEchilibru--;
//}
//
//void rotireDreapta(Nod** arbore) {
//	Nod* aux = (*arbore)->st;
//	(*arbore)->st = aux->dr;
//	aux->dr = (*arbore);
//	(*arbore) = aux;
//	(*arbore)->gradEchilibru++;
//}
//
//void adaugaLaptopInArbore(Nod** arbore, Laptop laptop) {
//	if (!(*arbore)) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = laptop;
//		nou->st = NULL;
//		nou->dr = NULL;
//		nou->gradEchilibru = 0;
//		(*arbore) = nou;
//	}
//	else {
//		if ((*arbore)->info.id > laptop.id) {
//			adaugaLaptopInArbore(&((*arbore)->st), laptop);
//			(*arbore)->gradEchilibru++;
//		} 
//		else {
//			adaugaLaptopInArbore(&((*arbore)->dr), laptop);
//			(*arbore)->gradEchilibru--;
//		}
//		if ((*arbore)->gradEchilibru == 2) {
//			if ((*arbore)->st->gradEchilibru == 1) {
//				rotireDreapta(arbore);
//			}
//			else {
//				rotireStanga(&((*arbore)->st));
//				rotireDreapta(arbore);
//			}
//		} else if ((*arbore)->gradEchilibru == -2) {
//			if ((*arbore)->dr->gradEchilibru != -1) {
//				rotireDreapta(&((*arbore)->dr));
//
//			}
//			rotireStanga(arbore);
//		}
//	}
//}
//
//int calculInaltime(Nod* radacina) {
//	if (radacina) {
//		int inaltimeSt = calculInaltime(radacina->st);
//		int inaltimeDr = calculInaltime(radacina->dr);
//		if (inaltimeSt > inaltimeDr) {
//			return 1 + inaltimeSt;
//		}
//		else {
//			return 1 + inaltimeDr;
//		}
//	}
//	else {
//		return 0;
//	}
//}
//
//Nod* citesteArboreDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* arbore = NULL;
//	while (!feof(f)) {
//		adaugaLaptopInArbore(&arbore, citesteLaptopDinFisier(f));
//	}
//	fclose(f);
//	return arbore;
//}
//
//void afisarePreordineRSD(Nod* arbore) {
//	if (arbore) {
//		afiseazaLaptop(arbore->info);
//		afisarePreordineRSD(arbore->st);
//		afisarePreordineRSD(arbore->dr);
//	}
//}
//
//int main() {
//	Nod* arbore = citesteArboreDinFisier("laptops.txt");
//	afisarePreordineRSD(arbore);
//
//	int inaltime = calculInaltime(arbore);
//	printf("Inaltime:%d\n", inaltime);
//}