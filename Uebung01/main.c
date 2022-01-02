#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "include/ledanzeige/TM1637.h"

int main()
{

	student holger = {"Holger", IFM, 394};
	student beate = {"Beate", IFM, 8};
	student heinz = {"Heinz", ELM, 10};

	struct node* main_list = new_list(holger);
	struct node* ifm_students = new_list(holger);
	struct node* students_sorted_by_ects = new_list(beate);

	append(main_list, beate);
	append(main_list, heinz);

	append(ifm_students, beate);

	append(students_sorted_by_ects, heinz);
	append(students_sorted_by_ects, holger);

	printf("(Aufg.2) Anzahl an Studenten: %d\n", count(main_list));

	printf("(Aufg.3):\n");
	print_list(main_list);

	printf("(Aufg.4): \n");
	struct node* filterList = filterByStudiengang(main_list, IFM);
	print_list(filterList);
	printf("Anzahl an gefilterten Elementen: %d\n", count(filterList));

	printf("(Aufg.5): \n");
	printf("Anzahl vor Löschen: %d\n", count(main_list));
	delete(main_list, 0);
	printf("Anzahl nach Löschen: %d\n", count(main_list));

	printf("(Aufg.6):\n");
	printf("Es werden %d Elemente gelöscht!\n", count(main_list));
	clear(main_list, 1);

	return EXIT_SUCCESS;
}
