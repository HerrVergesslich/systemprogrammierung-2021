#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct node *getTestList()
{
	student holger = {"Holger", IFM, 394};
	student beate = {"Beate", IFM, 8};
	student heinz = {"Heinz", ELM, 10};
	student bernd = {"Bernd", IFM, 12};
	struct node *main_list = new_list(holger);
	append(main_list, beate);
	append(main_list, heinz);
	append(main_list, bernd);
	return main_list;
}

int main()
{
	struct node *main_list = getTestList();
	print_list(main_list);
	return 0;
}
