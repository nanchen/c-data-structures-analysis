#include <stdio.h>
#include "list.h"
#include "resourcetrack.h"

void PrintList(const List L) {
	ListPosition P = List_header(L);

	if (List_isEmpty(L))
		printf("Empty list\n");
	else {
		do {
			P = List_advance(P);
			printf("%d ", List_retrieve(P));
		} while (!List_isLast(P, L));
		printf("\n");
	}
}

int List_test(void) {
	List L;
	ListPosition P;
	int i;

	L = List_makeEmpty(NULL);
	P = List_header(L);
	PrintList(L);

	for (i = 0; i < 10; i++) {
		List_insert(i, L, P);
		PrintList(L);
		P = List_advance(P);
	}
	for (i = 0; i < 10; i += 2)
		List_delete(i, L);

	for (i = 0; i < 10; i++)
		if ((i % 2 == 0) == (List_find(i, L) != NULL))
			printf("Find fails\n");

	printf("Finished deletions\n");

	PrintList(L);

	List_deleteList(L);

	return 0;
}
