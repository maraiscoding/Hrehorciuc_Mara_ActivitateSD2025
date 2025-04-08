#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Programare {
	int id;
	float pret;
	char* serviciu;
	char* data;
};

typedef struct Programare Programare;
typedef struct Nod Nod;

struct Nod {
	Programare info;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

typedef struct ListaDubla Lista;

Programare initializareProgramare(int id, float pret, const char* serviciu, const char* data) {
	Programare p;
	p.id = id;
	p.pret = pret;
	p.serviciu = (char*)malloc(sizeof(char) * (strlen(serviciu) + 1));
	strcpy_s(p.serviciu, strlen(serviciu) + 1, serviciu);
	p.data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
	strcpy_s(p.data, strlen(data) + 1, data);
	return p;
}

Programare citesteProgramareDinFisier(FILE* file) {
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	Programare p;
	token = strtok(buffer, delimitator);
	p.id = atoi(token);
	p.pret = atof(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	p.serviciu = (char*)malloc(strlen(token) + 1);
	strcpy_s(p.serviciu, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	p.data = (char*)malloc(strlen(token) + 1);
	strcpy_s(p.data, strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	return p;
}

void afiseazaProgramare(Programare p) {
	printf("Id:%d\n", p.id);
	printf("Pret:%5.2f\n", p.pret);
	printf("Serviciu:%s\n", p.serviciu);
	printf("Data:%s\n\n", p.data);
}

void afiseazaListaDublaProgramariInceput(Lista lista) {
	Nod* p = lista.prim;
	while (p) {
		afiseazaProgramare(p->info);
		p = p->next;
	}
}

void afiseazaListaDublaProgramariSfarsit(Lista lista) {
	Nod* p = lista.ultim;
	while (p) {
		afiseazaProgramare(p->info);
		p = p->prev;
	}
}

void adaugaProgramareInListaDublaSfarsit(Lista* lista, Programare programareNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = programareNoua;
	nou->next = NULL;
	nou->prev = lista->ultim;
	if (lista->ultim != NULL) {
		lista->ultim->next = nou;
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

void adaugaProgramareInListaDublaInceput(Lista* lista, Programare programareNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = programareNoua;
	nou->next = lista->prim;
	nou->prev = NULL;
	if (lista->prim != NULL) {
		lista->prim->prev = nou;
	}
	else {
		lista->ultim = nou;
	}
	lista->prim = nou;
}


Lista citesteListaDublaProgramariFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	while (!feof(f)) {
		adaugaProgramareInListaDublaInceput(&lista, citesteProgramareDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareListaDubla(Lista* lista) {
	Nod* p = lista->prim;
	while (p->next != NULL) {
		free(p->info.data);
		free(p->info.serviciu);
		p = p->next;
		free(p->prev);
	}
	free(p->info.data);
	free(p->info.serviciu);
	free(p);
	lista->prim = NULL;
	lista->ultim = NULL;
}

float calculeazaPretMediuListaDubla(Lista lista) {
	Nod* p = lista.prim;
	float suma = 0;
	int count = 0;
	while (p) {
		suma += p->info.pret;
		count++;
		p = p->next;
	}
	return suma / count;
}


char* getCeaMaiScumpaProgramare(Lista lista) {
	if (lista.prim) {
		Nod* max = lista.prim;
		Nod* p = lista.prim->next;
		while (p) {
			if (p->info.pret > max->info.pret) {
				max = p;
			}
			p = p->next;
		}
		char* serviciu = (char*)malloc(strlen(max->info.serviciu));
		strcpy_s(serviciu, strlen(max->info.serviciu) + 1, max->info.serviciu);
		return serviciu;
	}
	else {
		return NULL;
	}
}

//vreau sa inserez in lista simpla

typedef struct NodSimplu NodSimplu;

struct NodSimplu {
	Programare info;
	NodSimplu* next;
};

void afiseazaListaSimplaProgramari(NodSimplu* cap) {
	while (cap) {
		afiseazaProgramare(cap->info);
		cap = cap->next;
	}
}

void adaugaProgramareInListaSimpla(NodSimplu** cap, Programare programareNoua) {
	NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
	nou->info = programareNoua;
	nou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		Nod* p = (*cap);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

NodSimplu* insereazaDinListaDublaInListaSimpla(Lista lista) {
	NodSimplu* cap = NULL;
	Nod* p = lista.prim;
	while (p) {
		Programare copie = initializareProgramare(p->info.id, p->info.pret, p->info.serviciu, p->info.data);
		adaugaProgramareInListaSimpla(&cap, copie);
		p = p->next;
	}
	return cap;
}

//vreau sa inserez in HashTable

struct HashTable {
	NodSimplu** vector;
	int dim;
};

typedef struct HashTable HashTable;

void afiseazaTabela(HashTable hash) {
	for (int i = 0; i < hash.dim; i++) {
		printf("Suntem pe pozitia:%d\n", i);
		afiseazaListaSimplaProgramari(hash.vector[i]);
	}
}

HashTable initializeazaHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.vector = (NodSimplu**)malloc(sizeof(NodSimplu*) * dimensiune);
	for (int i = 0; i < ht.dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(const char* serviciu, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(serviciu); i++) {
		suma += serviciu[i];
	}
	return suma % dimensiune;
}

void adaugaInTabela(HashTable hash, Programare programare) {
	if (hash.dim) {
		int pozitie = calculeazaHash(programare.serviciu, hash.dim);
		if (pozitie < hash.dim) {
			if (hash.vector[pozitie] != NULL) {
				adaugaProgramareInListaSimpla(&(hash.vector[pozitie]), programare);
			}
			else {
				hash.vector[pozitie] = (NodSimplu*)malloc(sizeof(NodSimplu));
				hash.vector[pozitie]->info = programare;
				hash.vector[pozitie]->next = NULL;
			}
		}
	}
}

void insereazaListaDublaInTabela(HashTable hash, Lista lista) {
	Nod* p = lista.prim;
	while (p) {
		adaugaInTabela(hash, p->info);
		p = p->next;
	}
}

void dezalocareTabela(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		free(&(ht->vector[i]));
	}
	free(ht->vector);
	ht->vector = NULL;
	ht->dim = 0;
}


//vreau sa inserez in vector
Programare* insereazaListaDublaInVector(Lista lista, int* dimVector) {
	int count = 0;
	Nod* temp = lista.prim;
	while (temp) {
		count++;
		temp = temp->next;
	}
	Programare* vectorProgramari = (Programare*)malloc(sizeof(Programare) * count);
	temp = lista.prim;
	for (int i = 0; i < count; i++) {
		vectorProgramari[i] = initializareProgramare(temp->info.id, temp->info.pret, temp->info.serviciu, temp->info.data);
		temp = temp->next;
	}
	*dimVector = count;
	return vectorProgramari;
}
int main() {
	Lista lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	lista = citesteListaDublaProgramariFisier("programari.txt");
	afiseazaListaDublaProgramariInceput(lista);

	/*Lista lista1;
	lista1.prim = NULL;
	lista1.ultim = NULL;

	Programare p1 = initializareProgramare(23, 700, "vopsit", "08.04.2025");
	Programare p2 = initializareProgramare(24, 1700, "balayage", "08.04.2025");
	Programare p3 = initializareProgramare(25, 200, "laminare gene", "08.04.2025");
	Programare p4 = initializareProgramare(26, 280, "laminare spracene", "08.04.2025");

	adaugaProgramareInListaDublaSfarsit(&lista1, p1);
	adaugaProgramareInListaDublaSfarsit(&lista1, p2);
	adaugaProgramareInListaDublaSfarsit(&lista1, p3);
	adaugaProgramareInListaDublaSfarsit(&lista1, p4);

	afiseazaListaDublaProgramariInceput(lista1);*/

	printf("Pretul mediu este:%5.2f\n", calculeazaPretMediuListaDubla(lista));
	printf("Cel mai scump serviciu este:%s\n", getCeaMaiScumpaProgramare(lista));

	NodSimplu* cap = NULL;
	cap = insereazaDinListaDublaInListaSimpla(lista);
	printf("Lista simpla obtinuta:\n");
	afiseazaListaSimplaProgramari(cap);

	int dimensiune = 7;
	HashTable hash = initializeazaHashTable(dimensiune);
	insereazaListaDublaInTabela(hash, lista);
	printf("HashTable-ul obtinut:\n");
	afiseazaTabela(hash);

	int dimVector = 0;
	Programare* vectorProgramari = insereazaListaDublaInVector(lista, &dimVector);
	printf("Vectorul obtinut:\n");
	for (int i = 0; i < dimVector; i++) {
		afiseazaProgramare(vectorProgramari[i]);
	}
}