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
typedef struct NodDublu NodDublu;
typedef struct Nod Nod;

struct Nod {
	Programare info;
	Nod* next;
};

struct NodDublu {
	Programare info;
	NodDublu* next;
	NodDublu* prev;
};

struct ListaDubla {
	NodDublu* prim;
	NodDublu* ultim;
};

typedef struct ListaDubla Lista;


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


void pushStack(Nod** stiva, Programare p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = (*stiva);
	(*stiva) = nou;
}

Programare popStack(Nod** stiva) {
	if (*stiva) {
		Nod* temp = (*stiva);
		Programare p = temp->info;
		(*stiva) = temp->next;
		free(temp);
		return p;
	}
	else {
		return (Programare) { -1, 0, NULL, NULL };
	}
}

Nod* citesteStivaProgramariFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* stiva = NULL;
	while (!feof(f)) {
		pushStack(&stiva, citesteProgramareDinFisier(f));
	}
	fclose(f);
	return stiva;
}

void dezalocaStiva(Nod** stiva) {
	while (*stiva) {
		Programare p = popStack(stiva);
		free(p.serviciu);
		free(p.data);
	}
}

int size(Nod* stiva) {
	int contor = 0;
	while (stiva) {
		contor++;
		stiva = stiva->next;
	}
	return contor;
}


unsigned char isStackEmpty(Nod* stiva) {
	return stiva == NULL;
}

float calculeazaPretTotalStiva(Nod** stiva) {
	Nod* temp = NULL;
	float suma = 0;
	while (!isStackEmpty(*stiva)) {
		Programare p = popStack(stiva);
		suma += p.pret;
		pushStack(&temp, p);
	}
	while (!isStackEmpty(temp)) {
		pushStack(stiva, popStack(&temp));
	}
	return suma;
}

Programare getProgramareByID(Nod** stiva, int id) {
	Nod* temp = NULL;
	Programare rezultat = (Programare){ -1, 0, NULL, NULL };
	while (!isStackEmpty(*stiva)) {
		Programare p = popStack(stiva);
		if (p.id == id && rezultat.id == -1) {
			rezultat = p;
		}
		pushStack(&temp, p);
	}
	while (!isStackEmpty(temp)) {
		pushStack(stiva, popStack(&temp));
	}
	return rezultat;
}

void enqueue(Lista* coada, Programare p) {
	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
	nou->info = p;
	nou->next = NULL;
	nou->prev = coada->ultim;
	if (coada->ultim) {
		coada->ultim->next = nou;
	}
	else {
		coada->prim = nou;
	}
	coada->ultim = nou;
}

Programare dequeue(Lista* coada) {
	if (coada->prim) {
		Programare p = coada->prim->info;
		NodDublu* temp = coada->prim;
		coada->prim = coada->prim->next;
		free(temp);
		if (coada->prim == NULL) {
			coada->ultim = NULL;
		}
		else {
			coada->prim->prev = NULL;
		}
		return p;
	}
	else {
		Programare p;
		p.id = -1;
		return p;
	}
}

Lista citireCoadaDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista coada;
	coada.prim = NULL;
	coada.ultim = NULL;
	while (!feof(f)) {
		enqueue(&coada, citesteProgramareDinFisier(f));
	}
	fclose(f);
	return coada;
}

void dezalocaCoada(Lista* coada) {
	if (coada->prim) {
		Programare p =dequeue(coada);
		free(p.data);
		free(p.serviciu);
	}
}

float calculeazaPretTotalCoada(Lista* coada) {
	Lista temp;
	temp.prim = NULL;
	temp.ultim = NULL;
	float suma = 0;
	while (coada->prim) {
		Programare p = dequeue(coada);
		suma += p.pret;
		enqueue(&temp, p);
	}
	while (temp.prim) {
		enqueue(coada, dequeue(&temp));
	}
	return suma;
}

Programare getProgramareByIdCoada(Lista* coada, int id) {
	Lista temp;
	temp.prim = NULL;
	temp.ultim = NULL;
	Programare rezultat = (Programare){ -1, 0, NULL, NULL };
	while (coada->prim) {
		Programare p = dequeue(coada);
		if(p.id==id&&rezultat.id==-1) {
			rezultat = p;
		}
		enqueue(&temp, p);
	}
	while (temp.prim) {
		enqueue(coada, dequeue(&temp));
	}
	return rezultat;
}


int main() {
	Nod* stiva = citesteStivaProgramariFisier("programari.txt");
	Programare p1 = popStack(&stiva);
	afiseazaProgramare(p1);

	float suma = calculeazaPretTotalStiva(&stiva);
	printf("Pret total:%5.2f\n", suma);

	Programare p2 = getProgramareByID(&stiva, 2);
	afiseazaProgramare(p2);

	Lista coada = citireCoadaDinFisier("programari.txt");
	Programare p3 = dequeue(&coada);
	afiseazaProgramare(p3);

	float sumaCoada = calculeazaPretTotalCoada(&coada);
	printf("Total coada: %5.2f\n", sumaCoada);

	Programare p4 = getProgramareByIdCoada(&coada, 4);
	afiseazaProgramare(p4);
}