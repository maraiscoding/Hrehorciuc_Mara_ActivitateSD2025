//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct Buchet {
//	int id;
//	float pret;
//	char* flori;
//	char* florarie;
//};
//
//typedef struct Buchet Buchet;
//typedef struct Nod Nod;
//
//
//struct Nod {
//	Buchet info;
//	Nod* next;
//};
//
//
//void afisareBuchet(Buchet b) {
//	printf("Id:%d\n", b.id);
//	printf("Pret:%5.2f\n", b.pret);
//	printf("Flori:%s\n", b.flori);
//	printf("Florarie:%s\n\n", b.florarie);
//}
//
//void afisareListaBuchete(Nod* cap) {
//	while (cap != NULL) {
//		afisareBuchet(cap->info);
//		cap = cap->next;
//	}
//}
//
//Buchet citireBuchetDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Buchet b;
//	token = strtok(buffer, delimitator);
//	b.id = atoi(token);
//	b.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	b.flori = malloc(strlen(token) + 1);
//	strcpy_s(b.flori, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	b.florarie = malloc(strlen(token) + 1);
//	strcpy_s(b.florarie, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return b;
//}
//
//void adaugaLaFinalInLista(Nod** cap, Buchet buchetNou) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = buchetNou;
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
//void adaugaLaInceputInLista(Nod** cap, Buchet buchetNou) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = buchetNou;
//	nou->next = (*cap);
//	(*cap) = nou;
//}
//
//Nod* citireListaFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* lista = NULL;
//	while (!feof(f)) {
//		adaugaLaFinalInLista(&lista, citireBuchetDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//
//void dezalocareLista(Nod** cap) {
//	while ((*cap)) {
//		Nod* aux = (*cap);
//		(*cap) = (*cap)->next;
//		free(aux->info.florarie);
//		free(aux->info.flori);
//		free(aux);
//	}
//}
//
//float calculeazaPretMediu(Nod* lista) {
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
//float calculeazaPretulBuchetelorDinFlorarie(Nod* lista, const char* florarie) {
//	float suma = 0;
//	while (lista) {
//		if (strcmp(lista->info.florarie, florarie) == 0) {
//			suma += lista->info.pret;
//		}
//		lista = lista->next;
//	}
//	return suma;
//}
//
//char* getCelMaiScumpBuchet(Nod* lista) {
//	float pretulMaxim = 0;
//	char* floriScumpe = NULL;
//	while (lista) {
//		if (lista->info.pret > pretulMaxim) {
//			pretulMaxim = lista->info.pret;
//			floriScumpe = lista->info.flori;
//		}
//		lista = lista->next;
//	}
//	if (pretulMaxim > 0) {
//		char* nou = malloc(strlen(floriScumpe) + 1);
//		strcpy_s(nou, strlen(floriScumpe) + 1, floriScumpe);
//		return nou;
//	}
//	else {
//		return NULL;
//	}
//}
//
//int main() {
//	Nod* cap = NULL;
//	cap = citireListaFisier("buchete.txt");
//	afisareListaBuchete(cap);
//
//	printf("Pretul mediu:%5.2f\n", calculeazaPretMediu(cap));
//	printf("Suma buchetelor de la Iris este:%5.2f\n", calculeazaPretulBuchetelorDinFlorarie(cap, "Iris"));
//	printf("%s", getCelMaiScumpBuchet(cap));
//}