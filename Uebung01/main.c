

typedef enum{
	IFM,
	ELM
}enrolled;

char* getEnumName(enrolled in){
	switch (in)
	{
	case IFM:
		return "IFM";
		break;
	case ELM:
		return "ELM";
 	}
}

typedef struct {
	char* name;
	enrolled enrolled;
	int cps;
}student;

struct node {
	struct node *prev;
	struct node *next;
	student data;
};

struct node * new_list(student data){
    struct node *new = (struct node*) malloc(sizeof(struct node));
	new->data = data;
    new->prev = new;
    new->next = new;
    return new;
};

struct node * insert_next(struct node *list,student data){
    struct node *new = (struct node *) malloc(sizeof(struct node));
	new->data        = data;
	new->prev        = list;
	new->next       = list->next;
	list->next      = new;
	new->next->prev = new;
	return new;
}


struct node * delete(struct node *list){
	list->next->prev = list->prev;         //setzt linken Wert des rechten Nachbarn auf linken Wert von list
	list->prev->next = list->next;        //setzt rechten Wert des linken Nachbarn auf rechten Wert von list
	return list->prev;
}

void print_list(struct node *list){
	
	for(i=0;;i++){
		printf("name: %s | enrolled: %s | credit points: %i",list[i].data.name,getEnumName(list[i].data.enrolled),list[i].data.cps);
	}
}
struct node* getTestList(){
	student holger = {"Holger",IFM,394};
	student beate = {"Beate",IFM,8};
	student heinz = {"Heinz",ELM,10};
	struct node* main_list = new_list(holger);
	insert_next(main_list,beate);
	insert_next(main_list,heinz);
	return main_list;
}

int main(){
	struct node*main_list = getTestList();
	print_list(main_list);
	return 0;
}






