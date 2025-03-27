#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pictura {
	int id;
	float pret;
	int anRealizare;
	char* centruExpozitie;
	char* numeAutor;
};
typedef struct Pictura Pictura;
typedef struct Nod Nod;

struct Nod {
	Pictura info;
	Nod* prev;
	Nod* next;
};

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

typedef struct ListaDubla Lista;

void afisarePictura(Pictura pictura) {
	printf("Id:%d\n", pictura.id);
	printf("Pret:%.2f\n", pictura.pret);
	printf("An realizare:%d\n", pictura.anRealizare);
	printf("Centru expozitie:%s\n", pictura.centruExpozitie);
	printf("Nume autor:%s\n\n", pictura.numeAutor);
}

void afisareListaDublaPicturiInceput(Lista lista) {
	Nod* p = lista.prim;
	while (p) {
		afisarePictura(p->info);
		p = p->next;
	}
}

