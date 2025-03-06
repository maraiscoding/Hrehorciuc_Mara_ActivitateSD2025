#include<stdio.h>
#include<stdlib.h>

struct Masina {
	int id;
	int nrLocuri;
	char* marca;
	float capacitateC;
	char normaPoluare;
};

struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitateC, char normaPoluare) {
	struct Masina m;
	m.id = id;
	m.nrLocuri = nrLocuri;
	m.capacitateC = capacitateC;
	m.normaPoluare = normaPoluare;
	if (marca == NULL) {
		m.marca = NULL;
	}
	else {
		m.marca = (char*)malloc(strlen(marca) + 1);
		strcpy_s(m.marca, strlen(marca) + 1, marca);
	}
	return m;
}

void afisare(struct Masina m) {
	printf("\n Id masina: %d\n Nr locuri: %d\n Capacitate: %.2f\n Marca: %s\n Euro: %c", m.id, m.nrLocuri, m.capacitateC, m.marca, m.normaPoluare);
}

void modifica_NrLocuri(struct Masina* m, int nrNou) {
	if (nrNou > 0) {
		m->nrLocuri = nrNou;
	}
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	if ((*vector) != NULL) {
		for (int i = 0; i < *nrElemente; i++) {
			free((*vector)[i].marca);
		}
		free(*vector);
		*vector = NULL;
		*nrElemente = 0;
	}
}

void afisareVector(struct Masina* vector, int nrElem) {
	if (vector != NULL) {
		for (int i = 0; i < nrElem; i++)
		{
			afisare(vector[i]);
			printf("\n");
		}
	}
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	if (nrElementeCopiate < nrElemente && nrElementeCopiate>0) {
		struct Masina* vectorNou = (struct Masina*)malloc(nrElementeCopiate * sizeof(struct Masina));
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i] = initializare(vector[i].id, vector[i].nrLocuri, vector[i].marca, vector[i].capacitateC, vector[i].normaPoluare);
			
		}
		return vectorNou;
	}
	else {
		return NULL;
	}
}



void copiazaMasiniCuCCMare(struct Masina* vector, int nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie 
	
	(*dimensiune) = 0;
	for (char i = 0; i < nrElemente; i++) {
		if (prag < vector[i].capacitateC) {
			(*dimensiune)++;
		}
	}
	if ((*dimensiune) > 0) {
		(*vectorNou) = (struct Masina*)malloc((*dimensiune) * sizeof(struct Masina));
		int j = 0;
		for (int i = 0; i < nrElemente; i++) {
			if (prag < vector[i].capacitateC) {
				(*vectorNou)[j] = vector[i];
				(*vectorNou)[j].marca = malloc(sizeof(char) * (strlen(vector[i].marca) + 1));
				strcpy_s((*vectorNou)[j].marca, strlen(vector[i].marca) + 1, vector[i].marca);
				j++;
			}
		}
	}

}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].marca, conditie) == 0)
			return vector[i];
	}
	return initializare(-1, 0, NULL, 0, '-');
}


int main() {
	struct Masina masina = initializare(1, 5, "Dacia", 1.5, '4'); // "4" '4'
	struct Masina* vector;
	int nrElem = 3;

	vector = (struct  Masina*)malloc(nrElem * sizeof(struct Masina));
	vector[0] = initializare(1, 5, "Dacia", 1.5, '4');
	vector[1] = initializare(1, 5, "Honda", 1.5, '4');
	vector[2] = initializare(1, 5, "BMW", 1.5, '4');
	afisareVector(vector, nrElem);

	int nrElemCopiate = 2;
	struct Masina* masiniCopiate = copiazaPrimeleNElemente(vector, nrElem, nrElemCopiate);
	printf("\n\n Masinile copiate: ");
	afisareVector(masiniCopiate, nrElemCopiate);

	struct Masina* masiniCuCCMare = NULL;
	int nrMasiniCuCCMare = 2;
	copiazaMasiniCuCCMare(vector, nrElem, 1, &masiniCuCCMare, &nrMasiniCuCCMare);
	printf("Afisare masini cu cc mare:");
	printf("\n\n");
	afisareVector(masiniCuCCMare, nrMasiniCuCCMare);

	struct Masina primaMasina = getPrimulElementConditionat(vector, nrElem, "Dacia");
	printf("Prima masina: \n");
	afisare(primaMasina);
	dezalocare(&vector, &nrElem);

}