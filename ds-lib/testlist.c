#include <stdio.h>
#include "list.h"

void PrintList(const List L) {
	Position P = List_Header(L);

	if (List_IsEmpty(L))
		printf("Empty list\n");
	else {
		do {
			P = List_Advance(P);
			printf("%d ", List_Retrieve(P));
		} while (!List_IsLast(P, L));
		printf("\n");
	}
}

int List_Test(void) {
	List L;
	Position P;
	int i;

	L = List_MakeEmpty(NULL);
	P = List_Header(L);
	PrintList(L);

	for (i = 0; i < 10; i++) {
		List_Insert(i, L, P);
		PrintList(L);
		P = List_Advance(P);
	}
	for (i = 0; i < 10; i += 2)
		List_Delete(i, L);

	for (i = 0; i < 10; i++)
		if ((i % 2 == 0) == (List_Find(i, L) != NULL))
			printf("Find fails\n");

	printf("Finished deletions\n");

	PrintList(L);

	List_DeleteList(L);

	return 0;
}
