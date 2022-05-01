#include <stdio.h>
#include <stdlib.h>
#include "priority_queue_list.h"

void qlist(pqueue* head, void (*print_data)(void*)) {
	pqueue* p;

	for (p = head; p != NULL; p = p->next) {
		printf("%d: ", p->k);
		print_data(p->data);
		printf("\n");
	}
}

void qinsert(pqueue** phead, void* data, int k) {
	if (*phead == NULL) { //brak elementow
		*phead = (pqueue*)malloc(sizeof(pqueue));
		(*phead)->data = data;
		(*phead)->k = k;
		(*phead)->next = NULL;
		(*phead)->prev = NULL;
		return;
	}
	else {	//jest juz conajmniej jeden element
		if ((*phead)->k < k) { //jesli ten element powinien byc przed naszym
			pqueue* temp = (pqueue*)malloc(sizeof(pqueue));
			temp->next = *phead;
			temp->prev = NULL;
			temp->data = data;
			temp->k = k;

			(*phead)->prev = temp;
			*phead = temp;
		}
		else { // jesli ten element jest o wyzszym priorytecie, a za nim nie ma elementu, to dodaje za nim
			if ((*phead)->next == NULL) {
				pqueue* temp = (pqueue*)malloc(sizeof(pqueue));
				temp->next = NULL;
				temp->prev = *phead;
				temp->data = data;
				temp->k = k;

				(*phead)->next = temp;
			}
			else { // jesli ten element jest o wyzszym priorytecie, a za nim jest juz element, to wykonuje ta funkcje rekurencyjnie
				qinsert((*phead)->next, data, k);
			}
		}
	}
}


void qremove(pqueue** phead, int k) {
	//usuwali pierwszy element z listy
	if (phead == NULL) {
		return;
	}
	pqueue* temp = *phead;
	*phead = (*phead)->next;
	if (*phead == NULL) { // konieczne sprawdzenie zeby nie zmieniac wskaznika nalezacego do nulla
		(*phead)->prev = NULL;
	}
	free(temp);
}
