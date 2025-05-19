//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct BiletAvion {
//	int id;
//	float pret;
//	char* destinatie;
//	char* poartaImbarcare;
//};
//
//typedef struct BiletAvion Bilet;
//typedef struct Nod Nod;
//
//struct Nod {
//	Bilet info;
//	Nod* next;
//};
//
//
//Bilet initializareBilet(int id, float pret, const char* destinatie, const char* poarta) {
//	Bilet b;
//	b.id = id;
//	b.pret = pret;
//	b.destinatie = (char*)malloc(sizeof(char) * (strlen(destinatie) + 1));
//	strcpy_s(b.destinatie, strlen(destinatie) + 1, destinatie);
//	b.poartaImbarcare = (char*)malloc(sizeof(char) * (strlen(poarta) + 1));
//	strcpy_s(b.poartaImbarcare, strlen(poarta) + 1, poarta);
//	return b;
//}
//
//Bilet citireBiletDinFisier(FILE* file) {
//	char buffer[100];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token;
//	Bilet b;
//	token = strtok(buffer, delimitator);
//	b.id = atoi(token);
//	b.pret = atof(strtok(NULL, delimitator));
//	token = strtok(NULL, delimitator);
//	b.destinatie = malloc(strlen(token) + 1);
//	strcpy_s(b.destinatie, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	b.poartaImbarcare = malloc(strlen(token) + 1);
//	strcpy_s(b.poartaImbarcare, strlen(token) + 1, token);
//	token = strtok(NULL, delimitator);
//	return b;
//}
//
//void afisareBilet(Bilet b) {
//	printf("Id:%d\n", b.id);
//	printf("Pret:%5.2f\n", b.pret);
//	printf("Destinatie:%s\n", b.destinatie);
//	printf("Poarta imbarcare:%s\n\n", b.poartaImbarcare);
//}
//
//void afisareListaBilete(Nod* cap) {
//	while (cap) {
//		afisareBilet(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaLaFinal(Nod** cap, Bilet biletNou) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = biletNou;
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
//void adaugaLaInceput(Nod** cap, Bilet biletNou) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = biletNou;
//	nou->next = *cap;
//	(*cap) = nou;
//}
//
//
//Nod* citesteListaBileteFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* lista = NULL;
//	while (!feof(f)) {
//		adaugaLaFinal(&lista, citireBiletDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocare(Nod** cap) {
//	while ((*cap)) {
//		Nod* aux = (*cap);
//		free(aux->info.poartaImbarcare);
//		free(aux->info.destinatie);
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
//float calculeazaPretMediuDestinatie(Nod* lista, const char* destinatie) {
//	float suma = 0;
//	int count = 0;
//	while (lista) {
//		if (strcmp(lista->info.destinatie, destinatie) == 0) {
//			suma += lista->info.pret;
//			count++;
//		}
//		lista = lista->next;
//	}
//	return suma / count;
//}
//
//char* getCelMaiScumpBilet(Nod* lista) {
//	float pretulMaxim = 0;
//	char* destinatieScumpa = NULL;
//	while (lista) {
//		if (lista->info.pret > pretulMaxim) {
//			pretulMaxim = lista->info.pret;
//			destinatieScumpa = lista->info.destinatie;
//		}
//		lista = lista->next;
//	}
//	if (pretulMaxim > 0) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		strcpy_s(nou, strlen(destinatieScumpa) + 1, destinatieScumpa);
//		return nou;
//	}
//	else {
//		return NULL;
//	}
//}
//
//void modificaPoartaImbarcare(Nod* lista, const char* destinatie, const char* poarta, const char* poartaNoua) {
//	while (lista) {
//		if (strcmp(lista->info.destinatie, destinatie) == 0 && strcmp(lista->info.poartaImbarcare, poarta) == 0) {
//			free(lista->info.poartaImbarcare);
//			lista->info.poartaImbarcare = (char*)malloc(sizeof(char) * (strlen(poartaNoua) + 1));
//			strcpy_s(lista->info.poartaImbarcare, strlen(lista->info.poartaImbarcare) + 1, poartaNoua);
//		}
//		lista = lista->next;
//	}
//}
//
//int main() {
//Nod* cap = NULL;
//cap = citesteListaBileteFisier("bilete.txt");
//afisareListaBilete(cap);
//
//printf("Pretul mediu este:%5.2f\n", calculeazaPretMediu(cap));
//printf("Pretul mediu al biletelor catre Roma este:%5.2f\n", calculeazaPretMediuDestinatie(cap, "Roma"));
//printf("Cea mai scumpa destinatie:%s\n", getCelMaiScumpBilet(cap));
//modificaPoartaImbarcare(cap, "Roma", "spate", "fata");
//printf("Lista noua:\n");
//afisareListaBilete(cap);
//
//	Nod* cap1 = NULL;
//	Bilet b1 = initializareBilet(11, 134, "Istanbul", "spate");
//	Bilet b2 = initializareBilet(12, 237, "Munchen", "fata");
//	Bilet b3 = initializareBilet(13, 89, "Tirana", "spate");
//
//	adaugaLaInceput(&cap1, b1);
//	adaugaLaInceput(&cap1, b2);
//	adaugaLaInceput(&cap1, b3);
//
//	afisareListaBilete(cap1);
//}