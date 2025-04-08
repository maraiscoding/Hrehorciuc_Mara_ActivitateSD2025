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
};

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

void afiseazaListaSimplaProgramari(Nod* cap) {
	while (cap) {
		afiseazaProgramare(cap->info);
		cap = cap->next;
	}
}

void adaugaProgramareInListaSimplaFinal(Nod** cap, Programare programareNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
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

void adaugaProgramareInListaSimplaInceput(Nod** cap, Programare programareNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = programareNoua;
	nou->next = (*cap);
	(*cap) = nou;
}

Nod* citesteListaProgramariFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaProgramareInListaSimplaFinal(&lista, citesteProgramareDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareListaSimpla(Nod** cap) {
	while (cap) {
		Nod* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux->info.data);
		free(aux->info.serviciu);
		free(aux);
	}
}

float calculeazaPretMediu(Nod* lista) {
	if (!lista) {
		return 0;
	}
	float suma = 0;
	int count = 0;
	while (lista) {
		suma += lista->info.pret;
		count++;
		lista = lista->next;
	}
	return suma / count;
}

char* getCelMaiScumpServiciu(Nod* lista) {
	float pretulMaxim = 0;
	char* serviciuScump = NULL;
	while (lista) {
		if (lista->info.pret > pretulMaxim) {
			pretulMaxim = lista->info.pret;
			serviciuScump = lista->info.serviciu;
		}
		lista = lista->next;
	}
	if (pretulMaxim > 0) {
		char* nou = (char*)malloc(strlen(serviciuScump) + 1);
		strcpy_s(nou, strlen(serviciuScump) + 1, serviciuScump);
		return nou;
	}
	else {
		return 0;
	}
}

//transfer in lista dubla

typedef struct NodDublu NodD;
struct NodDublu {
	Programare info;
	NodD* prev;
	NodD* next;
};

struct ListaDubla {
	NodD* prim;
	NodD* ultim;
};

typedef struct ListaDubla Lista;

void afiseazaListaDublaProgramari(Lista lista) {
	NodD* p = lista.prim;
	while (p) {
		afiseazaProgramare(p->info);
		p = p->next;
	}
}

void adaugaProgramareInListaDublaFinal(Lista* lista, Programare programareNoua) {
	NodD* nou = (NodD*)malloc(sizeof(NodD));
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
	NodD* nou = (NodD*)malloc(sizeof(Nod));
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

void dezalocareListaDubla(Lista* lista) {
	NodD* p = lista->prim;
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

Lista insereazainListaSimplaInDubla(Nod* cap) {
	Lista listaDubla;
	listaDubla.prim = NULL;
	listaDubla.ultim = NULL;
	while (cap) {
		Programare copie = initializareProgramare(cap->info.id, cap->info.pret, cap->info.serviciu, cap->info.data);
		adaugaProgramareInListaDublaFinal(&listaDubla, copie);
		cap = cap->next;
	}
	return listaDubla;
}

//vreau sa inserez in vector
Programare* insereazaInVectorDinListaSimpla(Nod* cap, int* dimVector) {
	int count = 0;
	Nod* temp = cap;
	while (temp) {
		count++;
		temp = temp->next;
	}
	Programare* vector = (Programare*)malloc(sizeof(Programare) * count);
	temp = cap;
	for (int i = 0; i < count; i++) {
		vector[i] = initializareProgramare(temp->info.id, temp->info.pret, temp->info.serviciu, temp->info.data);
		temp = temp->next;
	}
	*dimVector = count;
	return vector;
}


//vreau sa inserez in HashTable

struct HashTable {
	Nod** vector;
	int dim;
};

typedef struct HashTable HashTable;

void afiseazaHashTable(HashTable hash) {
	for (int i = 0; i < hash.dim; i++) {
		printf("Sntem pe pozitia:%d\n", i);
		afiseazaListaSimplaProgramari(hash.vector[i]);
	}
}

HashTable initializeazaHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.vector = (Nod*)malloc(sizeof(Nod) * dimensiune);
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


void adaugaProgramareInTabela(HashTable hash, Programare programare) {
	if (hash.dim > 0) {
		int pozitie = calculeazaHash(programare.serviciu, hash.dim);
		if (pozitie < hash.dim) {
			if (hash.vector[pozitie] != NULL) {
				adaugaProgramareInListaSimplaFinal(&(hash.vector[pozitie]), programare);

			}
			else {
				hash.vector[pozitie] = (Nod*)malloc(sizeof(Nod));
				hash.vector[pozitie]->info = programare;
				hash.vector[pozitie]->next = NULL;
			}
		}
	}
}

void insereazaInHashTableDinListaSimpla(Nod* cap, HashTable* hash) {
	while (cap) {
		adaugaProgramareInTabela(*hash, cap->info);
		cap = cap->next;
	}
}

	int main() {
	Nod* cap = NULL;
	cap = citesteListaProgramariFisier("programari.txt");
	afiseazaListaSimplaProgramari(cap);

	/*Nod* cap1 = NULL;
	Programare p1 = initializareProgramare(23, 700, "vopsit", "08.04.2025");
	Programare p2 = initializareProgramare(24, 1700, "balayage", "08.04.2025");
	Programare p3 = initializareProgramare(25, 200, "laminare gene", "08.04.2025");
	Programare p4 = initializareProgramare(26, 280, "laminare spracene", "08.04.2025");
	adaugaProgramareInListaSimplaFinal(&cap1, p1);
	adaugaProgramareInListaSimplaFinal(&cap1, p2);
	adaugaProgramareInListaSimplaFinal(&cap1, p3);
	adaugaProgramareInListaSimplaFinal(&cap1, p4);
	afiseazaListaSimplaProgramari(cap1);*/

	printf("Pretul mediu al serviciilor este:%5.2f\n", calculeazaPretMediu(cap));
	printf("Cel mai scump serviciu este:%s\n", getCelMaiScumpServiciu(cap));

	Lista listaDubla;
	listaDubla.prim = NULL;
	listaDubla.ultim = NULL;
	printf("Lista dubla obtinuta:\n");
	listaDubla = insereazainListaSimplaInDubla(cap);
	afiseazaListaDublaProgramari(listaDubla);

	int dimVector = 0;
	Programare* vectorProgramari = insereazaInVectorDinListaSimpla(cap, &dimVector);
	printf("Vectorul obtinut:\n");
	for (int i = 0; i < dimVector; i++) {
		afiseazaProgramare(vectorProgramari[i]);
	}

	int dimensiune = 7;
	HashTable hash = initializeazaHashTable(dimensiune);
	insereazaInHashTableDinListaSimpla(cap, &hash);
	afiseazaHashTable(hash);
	
	dezalocareListaSimpla(&cap);
}