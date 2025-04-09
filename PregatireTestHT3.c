//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct Programare {
//	int id;
//	float pret;
//	char* serviciu;
//	char* data;
//};
//
//typedef struct Programare Programare;
//typedef struct Nod Nod;
//
//struct Nod {
//	Programare info;
//	Nod* next;
//};
//
//struct HashTable {
//	Nod** vector;
//	int dim;
//};
//
//typedef struct HashTable HashTable;
//
//Programare initializareProgramare(int id, float pret, const char* serviciu, const char* data) {
//	Programare p;
//	p.id = id;
//	p.pret = pret;
//	p.serviciu = (char*)malloc(sizeof(char) * (strlen(serviciu) + 1));
//	strcpy_s(p.serviciu, strlen(serviciu) + 1, serviciu);
//	p.data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
//	strcpy_s(p.data, strlen(data) + 1, data);
//	return p;
//}
//
//Programare citesteProgramareDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Programare p;
//	token = strtok(buffer, delimitator);
//	p.id = atoi(token);
//	p.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	p.serviciu = (char*)malloc(strlen(token) + 1);
//	strcpy_s(p.serviciu, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	p.data = (char*)malloc(strlen(token) + 1);
//	strcpy_s(p.data, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return p;
//}
//
//void afiseazaProgramare(Programare p) {
//	printf("Id:%d\n", p.id);
//	printf("Pret:%5.2f\n", p.pret);
//	printf("Serviciu:%s\n", p.serviciu);
//	printf("Data:%s\n\n", p.data);
//}
//
//void afiseazaListaSimplaProgramari(Nod* cap) {
//	while (cap) {
//		afiseazaProgramare(cap->info);
//		cap = cap->next;
//	}
//}
//
//HashTable initializeazaHashTable(int dimensiune) {
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
//	for (int i = 0; i < dimensiune; i++) {
//		ht.vector[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(const char* serviciu, int dimensiune) {
//	int suma = 0;
//	for (int i = 0; i < strlen(serviciu); i++) {
//		suma += serviciu[i];
//	}
//	return suma % dimensiune;
//}
//
//void afiseazaTabelaProgramari(HashTable hash) {
//	for (int i = 0; i < hash.dim; i++) {
//		printf("Suntem pe pozitia:%d\n", i);
//		afiseazaListaSimplaProgramari(hash.vector[i]);
//	}
//}
//
//void adaugaProgramareInListaSimpla(Nod** cap, Programare programareNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = programareNoua;
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
//void adaugaProgramareInTabela(HashTable hash, Programare programare) {
//	if (hash.dim > 0) {
//		int pozitie = calculeazaHash(programare.serviciu, hash.dim);
//		if (pozitie < hash.dim) {
//			if (hash.vector[pozitie] != NULL) {
//				adaugaProgramareInListaSimpla(&(hash.vector[pozitie]), programare);
//			}
//			else {
//				hash.vector[pozitie] = (Nod*)malloc(sizeof(Nod));
//				hash.vector[pozitie]->info = programare;
//				hash.vector[pozitie]->next = NULL;
//			}
//		}
//	}
//}
//
//
//HashTable citesteHashDinFisier(const char* numeFisier, int dimensiune) {
//	FILE* f = fopen(numeFisier, "r");
//	HashTable hash = initializeazaHashTable(dimensiune);
//	while (!feof(f)) {
//		adaugaProgramareInTabela(hash, citesteProgramareDinFisier(f));
//	}
//	fclose(f);
//	return(hash);
//}
//
//void dezalocaListaSimpla(Nod** cap) {
//	Nod* aux = (*cap);
//	(*cap) = (*cap)->next;
//	free(aux->info.data);
//	free(aux->info.serviciu);
//	free(aux);
//}
//
//void dezalocaTabelaProgramari(HashTable* ht) {
//	for (int i = 0; i < ht->dim; i++) {
//		dezalocaListaSimpla(&(ht->vector[i]));
//	}
//	free(ht->vector);
//	ht->vector = NULL;
//	ht->dim = 0;
//}
//
//float calculeazaPretMediuLista(Nod* lista) {
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
//
//
//float* calculeazaPreturiMediiPerClustere(HashTable hash, int* nrClustere) {
//	float* preturi = NULL;
//	*nrClustere = 0;
//	for (int i = 0; i < hash.dim; i++) {
//		if (hash.vector[i] != NULL) {
//			(*nrClustere)++;
//		}
//	}
//	preturi = (float*)malloc(sizeof(float) * (*nrClustere));
//	int contor = 0;
//	for (int i = 0; i < hash.dim; i++) {
//		if (hash.vector[i] != NULL) {
//			preturi[contor] = calculeazaPretMediuLista(hash.vector[i]);
//			contor++;
//		}
//	}
//	return preturi;
//}
//int main() {
//	int dimensiune = 7;
//	HashTable hash = initializeazaHashTable(dimensiune);
//
//	Programare p1 = initializareProgramare(23, 700, "vopsit", "08.04.2025");
//	Programare p2 = initializareProgramare(24, 1700, "balayage", "08.04.2025");
//	Programare p3 = initializareProgramare(25, 200, "laminare gene", "08.04.2025");
//	Programare p4 = initializareProgramare(26, 280, "laminare spracene", "08.04.2025");
//
//	adaugaProgramareInTabela(hash, p1);
//	adaugaProgramareInTabela(hash, p2);
//	adaugaProgramareInTabela(hash, p3);
//	adaugaProgramareInTabela(hash, p4);
//
//	afiseazaTabelaProgramari(hash);
//
//	int nrClustere = 0;
//	float* preturi = calculeazaPreturiMediiPerClustere(hash, &nrClustere);
//	for (int i = 0; i < nrClustere; i++) {
//		printf("Media pretului per clusterul:%d\n", i);
//		printf("%5.2f\n", preturi[i]);
//	}
//}