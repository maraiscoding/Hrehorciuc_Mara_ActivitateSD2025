//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//typedef struct Nod Nod;
//
//struct Nod {
//	Masina info;
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
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasiniInceput(Lista lista) {
//	Nod* p = lista.prim;
//	while (p) {
//		afisareMasina(p->info);
//		p = p->next;
//	}
//}
//
//void adaugaMasinaInLista(Lista* lista, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
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
//void adaugaLaInceputInLista(Lista* lista, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = lista->prim;
//	nou->prev = NULL;
//	if (lista->prim != NULL) {
//		lista->prim->prev = nou;
//	}
//	else {
//		lista->ultim = nou;
//	}
//	lista->prim = nou;
//}
//
//Lista citireLDMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Lista lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//	while (!feof(f)) {
//		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//Lista citireLDMasiniDinFisier1(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Lista lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;
//	while (!feof(f)) {
//		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//
//void afisareListaMasiniSfarsit(Lista lista) {
//	Nod* p = lista.ultim;
//	while (p) {
//		afisareMasina(p->info);
//		p = p->prev;
//	}
//}
//
//
//void dezalocareLDMasini(Lista* lista) {
//	Nod* p = lista->prim;
//	while (p->next != NULL) {
//		free(p->info.numeSofer);
//		free(p->info.model);
//		p = p->next;
//		free(p->prev);
//	}
//	free(p->info.numeSofer);
//	free(p->info.model);
//	free(p);
//	lista->prim = NULL;
//	lista->ultim = NULL;
//}
//
//float calculeazaPretMediu(Lista lista) {
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
//void stergeMasinaDupaID(/*lista masini*/ int id) {
//	//sterge masina cu id-ul primit.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//}
//
//char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
//	//cauta masina cea mai scumpa si 
//	//returneaza numele soferului acestei maasini.
//	return NULL;
//}
//
//int main() {
//	Lista lista;
//	lista = citireLDMasiniDinFisier1("masini.txt");
//	afisareListaMasiniInceput(lista);
//
//	printf("Pret mediu:%5.2f\n", calculeazaPretMediu(lista));
//	return 0;
//}