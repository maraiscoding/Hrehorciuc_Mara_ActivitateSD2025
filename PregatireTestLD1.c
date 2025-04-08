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
//Carte initializareCarte(int id, float pret, const char* autor, const char* editura) {
//	Carte c;
//	c.id = id;
//	c.pret = pret;
//	c.autor = (char*)malloc(sizeof(char)*(strlen(autor)+1));
//	strcpy_s(c.autor, strlen(autor) + 1, autor);
//	c.editura = (char*)malloc(sizeof(char) * (strlen(editura) + 1));
//	strcpy_s(c.editura, strlen(editura) + 1, editura);
//	return c;
//}
//void afisareCarte(Carte c) {
//		printf("Id:%d\n", c.id);
//		printf("Pret:%5.2f\n", c.pret);
//		printf("Autor:%s\n", c.autor);
//		printf("Editura:%s\n\n", c.editura);
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
//void afisareListaCartiInceput(Lista lista) {
//	Nod* p = lista.prim;
//	while (p) {
//		afisareCarte(p->info);
//		p = p->next;
//	}
//}
//
//void afisareListaCartiFinal(Lista lista) {
//	Nod* p = lista.ultim;
//	while (p) {
//		afisareCarte(p->info);
//		p = p->prev;
//	}
//}
//
//void adaugaCarteInListaFinal(Lista* lista, Carte carteNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = carteNoua;
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
//void adaugaCarteInListaInceput(Lista* lista, Carte carteNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = carteNoua;
//	nou->prev = NULL;
//	nou->next = lista->prim;
//	if (lista->prim != NULL) {
//		lista->prim->prev = nou;
//	} else {
//		lista->ultim = nou;
//	}
//	lista->prim = nou;
//}
//
//Lista citireListaDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Lista lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//	while (!feof(f)) {
//		adaugaCarteInListaInceput(&lista, citireCarteDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocare(Lista* lista) {
//	Nod* p = lista->prim;
//	while (p->next != NULL) {
//		free(p->info.editura);
//		free(p->info.autor);
//		p = p->next;
//		free(p->prev);
//	}
//	free(p->info.editura);
//	free(p->info.autor);
//	free(p);
//	lista->prim = NULL;
//	lista->ultim = NULL;
//}
//
//float calculeazaMedie(Lista lista) {
//	Nod* aux = lista.prim;
//	float suma = 0;
//	int contor = 0;
//	while (aux) {
//		suma += aux->info.pret;
//		contor++;
//		aux = aux->next;
//	}
//	return suma / contor;
//}
//
//char* getAutorCarteScumpa(Lista lista) {
//	if (lista.prim) {
//		Nod* max = lista.prim;;
//		Nod* p = lista.prim->next;
//		while (p) {
//			if (p->info.pret > max->info.pret) {
//				max = p;
//			}
//			p = p->next;
//		}
//		char* autor = (char*)malloc(strlen(max->info.autor) + 1);
//		strcpy_s(autor, strlen(max->info.autor) + 1, max->info.autor);
//		return autor;
//	}
//	else {
//		return NULL;
//	}
//}
//
//typedef struct NodSimplu NodSimplu;
//
//struct NodSimplu {
//	Carte info;
//	NodSimplu* next;
//};
//
//void afisareListaSimpla(NodSimplu* cap) {
//	while (cap) {
//		afisareCarte(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaCarteLaFinalLS(NodSimplu** cap, Carte carteNoua) {
//	NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
//	nou->info = carteNoua;
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
//Nod* inserareListaDublaInListaSimpla(Lista lista) {
//	NodSimplu* cap = NULL;
//	Nod* p = lista.prim;
//	while (p) {
//		
//		Carte copie = initializareCarte(
//			p->info.id,
//			p->info.pret,
//			p->info.autor,
//			p->info.editura
//		);
//		adaugaCarteLaFinalLS(&cap, copie);
//		p = p->next;
//	}
//	return cap;
//}
//
////inserez in hashtable
//
//struct HashTable {
//	NodSimplu** vector;
//	int dim;
//};
//
//typedef struct HashTable HashTable;
//
//void afisareTabelaCarti(HashTable ht) {
//	for (int i = 0; i < ht.dim; i++) {
//		printf("Suntem pe pozitia:%d\n", i);
//		afisareListaSimpla(ht.vector[i]);
//	}
//}
//
//HashTable initializareHashTable(int dimensiune) {
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.vector = (NodSimplu**)malloc(sizeof(NodSimplu*) * dimensiune);
//	for (int i = 0; i < ht.dim; i++) {
//		ht.vector[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(const char* autor, int dimensiune) {
//	int suma = 0;
//	for (int i = 0; i < strlen(autor); i++) {
//		suma += autor[i];
//	}
//	return suma % dimensiune;
//}
//
//void adaugaCarteInTabela(HashTable hash, Carte carte) {
//	if (hash.dim > 0) {
//		int pozitie = calculeazaHash(carte.autor, hash.dim);
//		if (pozitie < hash.dim) {
//			if (hash.vector[pozitie] != NULL) {
//				adaugaCarteLaFinalLS(&(hash.vector[pozitie]), carte);
//			}
//			else {
//				hash.vector[pozitie] = (NodSimplu*)malloc(sizeof(NodSimplu*));
//				hash.vector[pozitie]->info = carte;
//				hash.vector[pozitie]->next = NULL;
//			}
//		}
//	}
//}
//
//void listaDublaInHashTable(HashTable tabela, Lista lista) {
//	Nod* p = lista.prim;
//	while (p) {
//		adaugaCarteInTabela(tabela, p->info);  
//		p = p->next;
//	}
//}
//
////vreau sa transfer in vector
//Carte* conversieListaDublaInVector(Lista lista, int* dimVector) {
//	int count = 0;
//	Nod* temp = lista.prim;
//
//
//	while (temp) {
//		count++;
//		temp = temp->next;
//	}
//
//	
//	Carte* vector = (Carte*)malloc(sizeof(Carte) * count);
//
//	
//	temp = lista.prim;
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
//
//int main() {
//	//Lista lista = citireListaDinFisier("carti.txt");
//	//afisareListaCartiFinal(lista);
//
//	Lista lista1;
//	lista1.prim = NULL;
//	lista1.ultim = NULL;
//
//	Carte carte1 = initializareCarte(1, 35, "Eminescu", "Adevarul");
//	Carte carte2 = initializareCarte(2, 36, "Ion Creanga", "Humanitas");
//	Carte carte3 = initializareCarte(3, 40, "Voiculescu", "Art");
//
//	adaugaCarteInListaFinal(&lista1, carte1);
//	adaugaCarteInListaFinal(&lista1, carte2);
//	adaugaCarteInListaFinal(&lista1, carte3);
//
//	afisareListaCartiInceput(lista1);
//
//	printf("Pretul mediu este:%5.2f\n", calculeazaMedie(lista1));
//	printf("Cea mai scumpa carte e scrisa de:%s\n", getAutorCarteScumpa(lista1));
//
//	NodSimplu* listaNoua = inserareListaDublaInListaSimpla(lista1);
//	printf("\nLista simpla reconstruita din lista dubla:\n");
//	afisareListaSimpla(listaNoua);
//
//	int dimensiune = 7;
//	HashTable hash = initializareHashTable(dimensiune);
//	listaDublaInHashTable(hash, lista1);
//	printf("Elementele in hashtable:\n");
//	afisareTabelaCarti(hash);
//
//	int dim = 0;
//	Carte* vectorCarti = conversieListaDublaInVector(lista1, &dim);
//	printf("Elementele din vector sunt:\n");
//	for (int i = 0; i < dim; i++) {
//		afisareCarte(vectorCarti[i]);
//	}
//	
//
//	dezalocare(&lista1);
//}