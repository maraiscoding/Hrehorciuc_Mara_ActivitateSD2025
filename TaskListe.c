#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
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

//Nod** pt ca adaugam la inceput si modificam adresa primului
void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = cap;
	(*cap) = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

Nod* citireListaMasiniDinFisier1(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareListaMasini(Nod** cap) {
	while ((*cap) != NULL) {
		Nod* aux = (*cap);
		*cap = (*cap)->next;
		free(aux->info.numeSofer);
		free(aux->info.model);
		free(aux);
	}
}

float calculeazaPretMediu(Nod* lista) {
	if (!lista) {
		return 0;
	}
	int count = 0;
	float suma = 0;
	while (lista) {
		suma += lista->info.pret;
		count++;
		lista = lista->next;
	}
	return suma / count;
}

void stergeMasiniDinSeria(Nod** lista, char serieCautata) {
	Nod* p = *lista;
	while (p != NULL && p->info.serie == serieCautata) {
		Nod* sters = p;
		p = p->next;

		free(sters->info.model);
		free(sters->info.numeSofer);
		free(sters);
	}

	*lista = p;
	if (p != NULL) {
		Nod* ant = p;
		Nod* curent = p->next;
		while (curent != NULL) {
			if (curent->info.serie == serieCautata) {
				Nod* sters = curent;
				ant->next = curent->next;
				curent = curent->next;

				free(sters->info.model);
				free(sters->info.numeSofer);
				free(sters);
			}
			else {
				ant = curent;
				curent = curent->next;
			}
		}

	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	float suma = 0;
	while (lista) {
		if (strcmp(numeSofer, lista->info.numeSofer) == 0) {
			suma += lista->info.pret;
		}
		lista = lista->next;
	}
	return suma;
}

char* getCeaMaiScumpaMasina(Nod* lista) {
	float pretulMaxim = 0;
	char* modelScump = NULL;
	while (lista) {
		if (lista->info.pret > pretulMaxim) {
			pretulMaxim = lista->info.pret;
			modelScump = lista->info.model;
		}
		lista = lista->next;
	}
	if (pretulMaxim > 0) {
		char* nou = malloc(strlen(modelScump));
		strcpy_s(nou, strlen(modelScump) + 1, modelScump);
		return nou;
	}
	else {
		return NULL;
	}
}

//Implementati o functie care sterge un nod de pe o pozitie data ca parametru. Daca lista
//are mai putine noduri decat index - ul dat, nu se realizeaza stergerea

void stergeNodLaPozitie(Nod** cap, int pozitie) {
	if (*cap == NULL || pozitie < 0) {
		return; 
	}
	Nod* temp = *cap;
	if (pozitie == 0) {
		*cap = temp->next; 
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
		return;
	}
	Nod* anterior = NULL;
	for (int i = 0; temp != NULL && i < pozitie; i++) {
		anterior = temp;
		temp = temp->next;
	}
	if (temp == NULL) {
		return;
	}
	anterior->next = temp->next;
	free(temp->info.model);
	free(temp->info.numeSofer);
	free(temp);
}

//Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel
//incat acestea a fie sortate crescator dupa un camp la alegerea voastra
void inserareOrdonataDupaPret(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	if (*cap == NULL || (*cap)->info.pret > masinaNoua.pret) {
		nou->next = *cap;
		*cap = nou;
		return;
	}
	Nod* curent = *cap;
	while (curent->next != NULL && curent->next->info.pret < masinaNoua.pret) {
		curent = curent->next;
	}
	nou->next = curent->next;
	curent->next = nou;
}

Nod* citireListaMasiniSortataDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("Eroare la deschiderea fisierului\n");
		return NULL;
	}

	Nod* lista = NULL;
	while (!feof(f)) {
		Masina masinaNoua = citireMasinaDinFisier(f);
		inserareOrdonataDupaPret(&lista, masinaNoua);
	}
	fclose(f);
	return lista;
}

//Implementati o functie care salveaza intr-un vector toate obiectele care indeplinesc o
//conditie stabilita de voi.Realizati deep copy, astfel incat elementele din vector sa fie
//diferentiate de cele din lista.Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti
//pentru cate elemente veti aloca spatiu.

Masina* salveazaMasiniInVector(Nod* lista, int* dimensiune, float pretMinim) {
	int count = 0;
	Nod* temp = lista;
	while (temp) {
		if (temp->info.pret > pretMinim) {
			count++;
		}
		temp = temp->next;
	}
	if (count == 0) {
		*dimensiune = 0;
		return NULL;
	}
	Masina* vector = (Masina*)malloc(count * sizeof(Masina));
	temp = lista;
	int index = 0;
	while (temp) {
		if (temp->info.pret > pretMinim) {
			vector[index].id = temp->info.id;
			vector[index].nrUsi = temp->info.nrUsi;
			vector[index].pret = temp->info.pret;
			vector[index].serie = temp->info.serie;
			vector[index].model = _strdup(temp->info.model);
			vector[index].numeSofer = _strdup(temp->info.numeSofer);

			index++;
		}
		temp = temp->next;
	}
	*dimensiune = count;
	return vector;
}

void afisareVectorMasini(Masina* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		afisareMasina(vector[i]);
	}
}

//Implementati o functie care primeste lista si doua pozitii. In cadrul functiei trebuie sa
//interschimbati elementele de pe cele doua pozitii din lista primita.
void interschimbaNoduri(Nod** cap, int poz1, int poz2) {
	if (poz1 == poz2) {
		printf("Pozitiile au aceeasi valoare\n");
		return;
	}
	Nod* prev1 = NULL, * prev2 = NULL, * nod1 = *cap, * nod2 = *cap;
	int index = 0;
	while (nod1 && index < poz1) {
		prev1 = nod1;
		nod1 = nod1->next;
		index++;
	}
	index = 0;
	while (nod2 && index < poz2) {
		prev2 = nod2;
		nod2 = nod2->next;
		index++;
	}
	if (!nod1 || !nod2) {
		printf("Una dintre pozitii nu exista\n");
		return;
	}
	if (prev1) {
		prev1->next = nod2;
	}
	else {
		*cap = nod2;
	}
	if (prev2) {
		prev2->next = nod1;
	}
	else {
		*cap = nod1;
	}
	Nod* temp = nod1->next;
	nod1->next = nod2->next;
	nod2->next = temp;
}


int main() {
	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini2.txt");
	afisareListaMasini(cap);

	float pretMediu = calculeazaPretMediu(cap);
	printf("Pretul mediu este: %5.2f\n", pretMediu);

	float pretSofer = calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu");
	printf("Pretul masinilor lui Ionescu este: %5.2f", pretSofer);

	printf("\n%s", getCeaMaiScumpaMasina(cap));

	//char serieCautata = 'A';
	//stergeMasiniDinSeria(&cap, serieCautata);
	//printf("Seria dupa stergere:\n");
	//afisareListaMasini(cap);

	//printf("\nStergere nod de pe pozitia 2...\n");
	//stergeNodLaPozitie(&cap, 2); // 
	//afisareListaMasini(cap); 

	Nod* cap1 = citireListaMasiniSortataDinFisier("masini2.txt");
	printf("Lista ordonata crescator:\n");
	afisareListaMasini(cap1); 

	int dimensiuneVector = 0;
	Masina* vectorMasini = salveazaMasiniInVector(cap, &dimensiuneVector, 5000);

	printf("\nMasini mai scumpe de 5000:\n");
	afisareVectorMasini(vectorMasini, dimensiuneVector);


	int poz1 = 1;
	int poz2 = 3;
	printf("\nInterschimbare noduri de pe poz %d si %d...\n", poz1, poz2);
	interschimbaNoduri(&cap, poz1, poz2);

	printf("\nLista dupa interschimbare:\n");
	afisareListaMasini(cap);

	dezalocareListaMasini(&cap);

	return 0;
}