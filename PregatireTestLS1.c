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
////vreau sa pun elementele din lista simpla intr-o lista dubla
//
//typedef struct NodDublu NodDublu;
//
//struct NodDublu {
//	Carte info;
//	NodDublu* prev;
//	NodDublu* next;
//};
//
//struct ListaDubla {
//	NodDublu* prim;
//	NodDublu* ultim;
//};
//
//typedef struct ListaDubla ListaDubla;
//
//void afisareListaDublaCarti(ListaDubla lista) {
//	NodDublu* p = lista.prim;
//	while (p) {
//		afisareCarte(p->info);
//		p = p->next;
//	}
//}
//
//void adaugaInListaDublaFinal(ListaDubla* lista, Carte carteNoua) {
//	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
//	nou->info = carteNoua;
//	nou->prev = lista->ultim;
//	nou->next = NULL;
//	if (lista->ultim!= NULL) {
//		lista->ultim->next = nou;
//	}
//	else {
//		lista->prim = nou;
//	}
//	lista->ultim = nou;
//}
//
//ListaDubla copieListaSimplaInDubla(Nod* cap) {
//	ListaDubla listaDubla;
//	listaDubla.prim = NULL;
//	listaDubla.ultim = NULL;
//
//	while (cap) {
//	
//		Carte copie = initializareCarte(
//			cap->info.id,
//			cap->info.pret,
//			cap->info.autor,
//			cap->info.editura
//		);
//
//		adaugaInListaDublaFinal(&listaDubla, copie);
//
//		cap = cap->next;
//	}
//
//	return listaDubla;
//}
//
////vreau sa iau elementele din lista simpla si sa le pun in hashtable
//struct HashTable {
//	Nod** vector;
//	int dim;
//};
//
//typedef struct HashTable HashTable;
//
//
//HashTable initializareHashTable(int dimensiune) {
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
//	for (int i = 0; i < dimensiune; i++) {
//		ht.vector[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(const char* autor, int dim) {
//	int suma = 0;
//	for (int i = 0; i < strlen(autor); i++) {
//		suma += autor[i];
//	}
//	return suma % dim;
//}
//
//void inserareInTabela(HashTable hash, Carte carte) {
//	if (hash.dim > 0) {
//		int pozitie = calculeazaHash(carte.autor, hash.dim);
//		if (pozitie < hash.dim) {
//			if (hash.vector[pozitie] != NULL) {
//				adaugaCarteLaFinal(&(hash.vector[pozitie]), carte);
//			}
//			else {
//				hash.vector[pozitie] = (Nod*)malloc(sizeof(Nod));
//				hash.vector[pozitie]->info = carte;
//				hash.vector[pozitie]->next = NULL;
//			}
//		}
//	}
//}
//
//void afisareTabelaCarti(HashTable ht) {
//	for (int i = 0; i < ht.dim; i++) {
//		printf("Suntem pe pozitia:%d\n", i);
//		afisareListaCarti(ht.vector[i]);
//	}
//}
//
//void inserareListaSimplaInHashTable(Nod* cap, HashTable* hash) {
//	while (cap) {
//		inserareInTabela(*hash, cap->info);
//		cap = cap->next;
//	}
//}
//
////vreau sa inserez intr un vector
//Carte* conversieListaSimplaInVector(Nod* cap, int* dimVector) {
//	int count = 0;
//	Nod* temp = cap;
//
//
//	while (temp) {
//		count++;
//		temp = temp->next;
//	}
//
//	Carte* vector = (Carte*)malloc(sizeof(Carte) * count);
//
//
//	temp = cap;
//	for (int i = 0; i < count; i++) {
//		vector[i] = initializareCarte(
//			temp->info.id,
//			temp->info.pret,
//			temp->info.autor,
//			temp->info.editura
//		);
//		temp = temp->next;
//	}
//
//	
//	*dimVector = count;
//
//	return vector;
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
//	ListaDubla listaDubla = copieListaSimplaInDubla(cap);
//	printf("\nLista dublu inlantuita (afisata de la inceput):\n");
//	afisareListaDublaCarti(listaDubla);
//
//	HashTable ht = initializareHashTable(10);
//	inserareListaSimplaInHashTable(cap, &ht);
//	printf("\nHashTable-ul cartilor:\n");
//	afisareTabelaCarti(ht);
//
//	int dimVector = 0;
//	Carte* vectorCarti = conversieListaSimplaInVector(cap, &dimVector);
//
//	printf("\nAfisare vector carti:\n");
//	for (int i = 0; i < dimVector; i++) {
//		afisareCarte(vectorCarti[i]);
//	}
//
//
//	dezalocare(&cap);
//}
//
//
