#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <time.h>

#define TAM 50

struct hashTab {
	char letra;
	hashTab* ptr;
};

hashTab* startList(hashTab *lista, int tam) {
	for (int i = 0; i < tam; i++) {
		lista[i].letra = 0;
		lista[i].ptr = nullptr;
	}
	return lista;
}

hashTab* tabelaHash(hashTab* list) {

	// Create HashTable with collision 
	for (int i = 0; i < TAM * 10; i++) 
	{
		int asciiChar = rand() % 128;
		int indice = asciiChar % TAM;

		// New var of hashTab
		hashTab *tmp = new hashTab;
		tmp->letra = asciiChar;
		tmp->ptr = nullptr;

		/* Process the collision*/
		// Is the first, link to first
		if ((list + indice)->ptr == nullptr) {
			(list + indice)->ptr = tmp;
		}
		// or traveling in list to the last component, and link the last at the new component
		else {
			hashTab *aux = (list + indice);	// Creating aux to scroll through the list

			while (aux->ptr != nullptr && aux->letra != tmp->letra) {
				aux = aux->ptr;
			}
			if(aux->letra != tmp->letra)
				aux->ptr = tmp;
		}
		
	}
	return list;
}

int searchHashTable(hashTab* list, char search) {
	int m_cont = 1;
	int m_indice = search % TAM;
	std::cout << m_indice << std::endl;
	if ((list + m_indice)->letra == search) {
		return m_cont;
	}
	else {
		hashTab * aux = (list + m_indice);
		std::cout << aux->letra << std::endl;
		while (aux != nullptr) {
			if (aux->letra == search)
				return m_cont;
			m_cont++;
			aux = aux->ptr;
		}
	}
	return -1;
	
}

int main() {
	srand(time(NULL));
	hashTab* m_listTable = new hashTab[TAM];
	FILE* arquivo; 
	arquivo = fopen("hashSearch.txt", "w");
	m_listTable = startList(m_listTable, TAM);
	m_listTable = tabelaHash(m_listTable);
	int m_option = 0;
	
	for (int i = 0; i < 128; i++) {
		int cont = searchHashTable(m_listTable, i);

		fprintf(arquivo, "%c\t%d\n", (char)i, cont);

	}
	fclose(arquivo);
	system("pause");
	return 0;
}