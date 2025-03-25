//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct CalCursa {
//	int id;
//	int numarCursa;
//	float pretLicitatie;
//	char* urmatoareaCursa;
//	char* detinator;
//};
//
//
//typedef struct CalCursa Cal;
//typedef struct Nod Nod;
//
//struct Nod {
//	Cal info;
//	Nod* next;
//};
//
//Cal citesteCalDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Cal c1;
//	token = strtok(buffer, delimitator);
//	c1.id = atoi(token);
//	c1.numarCursa = atoi(strtok(NULL, delimitator));
//	c1.pretLicitatie = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	c1.urmatoareaCursa = malloc(strlen(token) + 1);
//	strcpy_s(c1.urmatoareaCursa, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	c1.detinator = malloc(strlen(token) + 1);
//	strcpy_s(c1.detinator, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return c1;
//}
//
//void afisareCal(Cal cal) {
//	printf("Id:%d\n", cal.id);
//	printf("Numar cursa:%d\n", cal.numarCursa);
//	printf("Pret licitatie:%5.2f\n", cal.pretLicitatie);
//	printf("Urmatoarea cursa:%s\n", cal.urmatoareaCursa);
//	printf("Detinator:%s\n\n", cal.detinator);
//}
//
//void afisareListaCai(Nod* cap) {
//	while (cap) {
//		afisareCal(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaLaFinalInLista(Nod** cap, Cal calNou) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = calNou;
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
//void adaugaLaInceputInLista(Nod** cap, Cal calNou) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = calNou;
//	nou->next = cap;
//	(*cap) = nou;
//}
//
//Nod* citesteListaDinFisier(const char* numeF) {
//	FILE* f = fopen(numeF, "r");
//	Nod* lista = NULL;
//	while (!feof(f)) {
//		adaugaLaFinalInLista(&lista, citesteCalDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//float calculeazaPretMediu(Nod* lista) {
//	if (!lista) {
//		return 0;
//	}
//	int count = 0;
//	float suma = 0;
//	while (lista) {
//		suma += lista->info.pretLicitatie;
//		count++;
//		lista = lista->next;
//	}
//	return suma / count;
//}
//
//float calculeazaPretulCailorUnuiDetinator(Nod* lista, const char* numeDetinator) {
//	float suma = 0;
//	while (lista) {
//		if (strcmp(numeDetinator, lista->info.detinator) == 0) {
//			suma += lista->info.pretLicitatie;
//		}
//		lista = lista->next;
//	}
//	return suma;
//}
//
//void dezalocare(Nod** cap) {
//	while ((*cap) != NULL) {
//		Nod* aux = (*cap);
//		*cap = (*cap)->next;
//		free(aux->info.detinator);
//		free(aux->info.urmatoareaCursa);
//		free(aux);
//	}
//}
//
//
//char* getCelMaiScumpCal(Nod* lista) {
//	float pretulMaxim = 0;
//	char* detinatorBogat = NULL;
//	while (lista) {
//		if (lista->info.pretLicitatie > pretulMaxim) {
//			pretulMaxim = lista->info.pretLicitatie;
//			detinatorBogat = lista->info.detinator;
//		}
//		lista = lista->next;
//	}
//	if (pretulMaxim > 0) {
//		char* nou = malloc(strlen(detinatorBogat));
//		strcpy_s(nou, strlen(detinatorBogat) + 1, detinatorBogat);
//		return nou;
//	}
//	else {
//		return NULL;
//	}
//}
//
//
//void modificaUrmatoareaCursa(Nod* lista, const char* detinator, const char* urmatoareaCursa, const char* cursaNoua) {
//	while (lista != NULL) {
//		if (strcmp(lista->info.detinator, detinator)==0 && strcmp(lista->info.urmatoareaCursa, urmatoareaCursa) == 0 ) {
//			free(lista->info.urmatoareaCursa);
//			lista->info.urmatoareaCursa = (char*)malloc(sizeof(char) * (strlen(cursaNoua) + 1));
//			strcpy_s(lista->info.urmatoareaCursa, strlen(cursaNoua) + 1, cursaNoua);
//
//		}
//		lista = lista->next;
//	}
//}
//
//float calculeazaPretMediuPerDetinator(Nod* lista, const char* detinator) {
//	if (!lista) {
//		return 0;
//	}
//	float suma = 0;
//	int count = 0;
//	while (lista) {
//		if (strcmp(lista->info.detinator, detinator) == 0) {
//			suma += lista->info.pretLicitatie;
//			count++;
//		}
//		lista = lista->next;
//	}
//	return suma / count;
//}
//
//int main() {
//	Nod* cap = NULL;
//	cap = citesteListaDinFisier("cai.txt");
//	afisareListaCai(cap);
//
//	printf("Media este:%5.2f\n", calculeazaPretMediu(cap));
//	printf("Caii lui Frederick valoreaza:%5.2f\n", calculeazaPretulCailorUnuiDetinator(cap, "Frederick"));
//	printf("\n%s", getCelMaiScumpCal(cap));
//
//	
//	modificaUrmatoareaCursa(cap, "Frederick", "Monza", "Nice");
//	printf("Lista dupa modificare:");
//	afisareListaCai(cap);
//
//	printf("Media preturilor cailor lui Hugo este:%5.2f", calculeazaPretMediuPerDetinator(cap, "Hugo"));
//
//}