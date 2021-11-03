#ifndef LIST_H
#define LIST_H

typedef enum
{
	IFM,
	ELM
} enrolled;

typedef struct
{
	char *name;
	enrolled enrolled;
	int cps;
} student;

struct node *new_list(student data);

struct node *getLastElement(struct node* list);

void insert_next(struct node *list, student data);

void append(struct node* list,student element);

void delete(struct node *element);

void print_list(struct node *list);

#endif