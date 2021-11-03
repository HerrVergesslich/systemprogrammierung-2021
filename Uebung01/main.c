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

struct node *getLastElement(struct node* list){
	struct node* head = list;
	struct node* current = list;
	while(head != current){
		current = current->next;
	}
	return current;
}

void insert_next(struct node *list, student data)
{
	struct node *new = (struct node *)malloc(sizeof(struct node));
	new->data = data;
	new->prev = list;
	new->next = list->next;
	list->next = new;
	new->next->prev = new;
}

void append(struct node* list,student element){
	struct node *new = (struct node *)malloc(sizeof(struct node));
	struct node *lastelement = getLastElement(list);
	new->data = element;
	new->prev = lastelement;
	new->next = NULL;
	lastelement->next = new;
}

void delete(struct node *list)
{
	list->next->prev = list->prev; //setzt linken Wert des rechten Nachbarn auf linken Wert von list
	list->prev->next = list->next; //setzt rechten Wert des linken Nachbarn auf rechten Wert von list
}

void print_list(struct node *list)
{
	struct node* next = list;
	while (next != NULL)
	{
		printf("name: %s | enrolled: %s | credit points: %i\n", next->data.name, getEnumName(next->data.enrolled), next->data.cps);
		next = next->next;
	}
}

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
