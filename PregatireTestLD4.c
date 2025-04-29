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
//	Nod* next;
//	Nod* prev;
//};
//
//struct ListaDubla {
//	Nod* prim;
//	Nod* ultim;
//};
//
//typedef struct ListaDubla Lista;
//
//void afiseazaLaptop(Laptop l) {
//	printf("Id:%d\n", l.id);
//	printf("Pret:%5.2f\n", l.pret);
//	printf("Marca:%s\n", l.marca);
//	printf("Procesor:%s\n\n", l.procesor);
//}
//
//Laptop initializeazaLaptop(int id, float pret, const char* marca, const char* procesor) {
//	Laptop l;
//	l.id = id;
//	l.pret = pret;
//	l.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
//	strcpy_s(l.marca, strlen(marca) + 1, marca);
//	l.procesor = (char*)malloc(sizeof(char) * (strlen(procesor) + 1));
//	strcpy_s(l.procesor, strlen(procesor) + 1, procesor);
//	return l;
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
//void afiseazaListaDubla(Lista lista) {
//	Nod* p = lista.prim;
//	while (p) {
//		afiseazaLaptop(p->info);
//		p = p->next;
//	}
//}
//
//void adaugaInListaDublaFinal(Lista* lista, Laptop laptopNou) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = laptopNou;
//	nou->prev = lista->ultim;
//	nou->next = NULL;
//	if (lista->ultim != NULL) {
//		lista->ultim->next = nou;
//	}
//	else {
//		lista->prim = nou;
//	}
//	lista->ultim = nou;
//}
//
//Lista citesteListaDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Lista lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//	while (!feof(f)) {
//		adaugaInListaDublaFinal(&lista, citesteLaptopDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocaLista(Lista* lista) {
//	Nod* p = lista->prim;
//	while (p->next != NULL) {
//		free(p->info.procesor);
//		free(p->info.marca);
//		p = p->next;
//		free(p->prev);
//	}
//	free(p->info.procesor);
//	free(p->info.marca);
//	free(p);
//	lista->prim = NULL;
//	lista->ultim = NULL;
//}
//
//float calculeazaPretMediu(Lista lista) {
//	Nod* p = lista.prim;
//	float suma = 0;
//	int count = 0;
//	while (p) {
//		suma += p->info.pret;
//		count++;
//		p = p->next;
//	}
//	return suma / count;
//}
//
//char* getCelMaiScumpLaptop(Lista lista) {
//	if(lista.prim) {
//		Nod* max = lista.prim;
//		Nod* p = lista.prim->next;
//		while (p) {
//			if (p->info.pret > max->info.pret) {
//				max = p;
//			}
//			p = p->next;
//		}
//		char* marca = (char*)malloc(strlen(max->info.marca));
//		strcpy_s(marca, strlen(max->info.marca) + 1, max->info.marca);
//		return marca;
//	}
//	else {
//		return NULL;
//	}
//}
//
//typedef struct NodSimplu NodSimplu;
//
//struct NodSimplu {
//	Laptop info;
//	NodSimplu* next;
//};
//
//void afiseazaListaSimpla(NodSimplu* cap) {
//	while (cap) {
//		afiseazaLaptop(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaInListaSimpla(NodSimplu** cap, Laptop laptopNou) {
//	NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
//	nou->info = laptopNou;
//	nou->next = NULL;
//	if ((*cap) == NULL) {
//		(*cap) = nou;
//	}
//	else {
//		NodSimplu* p = (*cap);
//		while (p->next != NULL) {
//			p = p->next;
//		}
//		p->next = nou;
//	}
//}
//
//NodSimplu* insereazaInListaSimplaDinListaDubla(Lista lista) {
//	Nod* cap = NULL;
//	Nod* p = lista.prim;
//	while (p) {
//		Laptop copie = initializeazaLaptop(p->info.id, p->info.pret, p->info.marca, p->info.procesor);
//		adaugaInListaSimpla(&cap, copie);
//		p = p->next;
//	}
//	return cap;
//}
//
//
//Laptop* insereazaInVector(Lista lista, int* dimVector) {
//	int count = 0;
//	Nod* temp = lista.prim;
//	while (temp) {
//		count++;
//		temp = temp->next;
//	}
//	Laptop* vector = (Laptop*)malloc(sizeof(Laptop) * count);
//	temp = lista.prim;
//	for (int i = 0; i < count; i++) {
//		vector[i] = initializeazaLaptop(temp->info.id, temp->info.pret, temp->info.marca, temp->info.procesor);
//		temp = temp->next;
//	}
//	*dimVector = count;
//	return vector;
//}
//
////hash
//
//struct HashTable {
//	NodSimplu** vector;
//	int dim;
//};
//
//typedef struct HashTable HashTable;
//
//HashTable initializeazaHashTable(int dimensiune) {
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.vector = (NodSimplu**)malloc(sizeof(NodSimplu*) * dimensiune);
//	for (int i = 0; i < dimensiune; i++) {
//		ht.vector[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(const char* marca, int dimensiune) {
//	int suma = 0;
//	for (int i = 0; i < strlen(marca); i++) {
//		suma += marca[i];
//	}
//	return suma % dimensiune;
//}
//
//void adaugaInHashTable(HashTable hash, Laptop laptop) {
//	if (hash.dim) {
//		int pozitie = calculeazaHash(laptop.marca, hash.dim);
//		if (pozitie < hash.dim) {
//			if (hash.vector[pozitie] != NULL) {
//				adaugaInListaSimpla(&(hash.vector[pozitie]), laptop);
//			}
//			else {
//				hash.vector[pozitie] = (NodSimplu*)malloc(sizeof(NodSimplu));
//				hash.vector[pozitie]->info = laptop;
//				hash.vector[pozitie]->next = NULL;
//			}
//		}
//	}
//}
//
//
//void insereazaInHtDinLd(HashTable hash, Lista lista) {
//	Nod* p = lista.prim;
//	while (p) {
//		adaugaInHashTable(hash, p->info);
//		p = p->next;
//	}
//}
//
//void afiseazaTabela(HashTable ht) {
//	for (int i = 0; i < ht.dim; i++) {
//		printf("Suntem pe pozitia:%d\n", i);
//		afiseazaListaSimpla(ht.vector[i]);
//	}
//}
//int main() {
//	Lista lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//	lista = citesteListaDinFisier("laptops.txt");
//	afiseazaListaDubla(lista);
//
//	printf("Cel mai scump laptop:%s\n", getCelMaiScumpLaptop(lista));
//
//	NodSimplu* cap = NULL;
//	cap = insereazaInListaSimplaDinListaDubla(lista);
//	printf("Lista simpla:\n");
//	afiseazaListaSimpla(cap);
//
//	int dim = 0;
//	Laptop* vector = insereazaInVector(lista, &dim);
//	for (int i = 0; i < dim; i++) {
//		afiseazaLaptop(vector[i]);
//	}
//
//	int dimensiune = 7;
//	HashTable hash = initializeazaHashTable(dimensiune);
//	insereazaInHtDinLd(hash, lista);
//	afiseazaTabela(hash);
//}