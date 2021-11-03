#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	IFM,
	ELM
} enrolled;

char *getEnumName(enrolled in)
{
	switch (in)
	{
	case IFM:
		return "IFM";
		break;
	case ELM:
		return "ELM";
	}
}

typedef struct
{
	char *name;
	enrolled enrolled;
	int cps;
} student;

struct node{
	struct node *prev;
	struct node *next;
	student data;
};

struct node *new_list(student data)
{
	struct node *new = (struct node *)malloc(sizeof(struct node));
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	return new;
}

struct node *insert_next(struct node *list, student data)
{
	struct node *new = (struct node *)malloc(sizeof(struct node));
	new->data = data;
	new->prev = list;
	new->next = list->next;
	list->next = new;
	new->next->prev = new;
	return new;
}

struct node *getLastElement(struct node* list){
	struct node* head = list;
	struct node* current = list;
	while(head != current){
		current = current->next;
	}
	return current->prev;
}

struct node *append(struct node* list,student element){
	struct node *new = (struct node *)malloc(sizeof(struct node));
	new->data = element;
	struct node *lastelement = getLastElement(list);
	lastelement->next = new;
	new->next = NULL;
	new->prev = lastelement;
	printf("name: %s | enrolled: %s | credit points: %i\n", lastelement->next->data.name, getEnumName(lastelement->next->data.enrolled), lastelement->next->data.cps);
	return new;
}



struct node *delete (struct node *list)
{
	list->next->prev = list->prev; //setzt linken Wert des rechten Nachbarn auf linken Wert von list
	list->prev->next = list->next; //setzt rechten Wert des linken Nachbarn auf rechten Wert von list
	return list->prev;
}

void print_list(struct node *list)
{

	while (list->next != NULL)
	{
		printf("name: %s | enrolled: %s | credit points: %i\n", list->data.name, getEnumName(list->data.enrolled), list->data.cps);
		list = list->next;
	}
}

struct node *getTestList()
{
	student holger = {"Holger", IFM, 394};
	student beate = {"Beate", IFM, 8};
	student heinz = {"Heinz", ELM, 10};
	struct node *main_list = new_list(holger);
	append(main_list, beate);
	append(main_list, heinz);
	return main_list;
}

int main()
{
	struct node *main_list = getTestList();
	print_list(main_list);
	return 0;
}
