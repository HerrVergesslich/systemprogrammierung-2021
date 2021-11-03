

typedef enum {
	IFM,
	ELM
}enrolled;

struct student {
	char* name;
	enum enrolled;
	int cps;
};

struct node {
	struct node *left;
	struct node *right;
	struct student data;
};

struct node * new_list() {
    struct node *new = (struct node*) malloc(sizeof(struct node));
    new->data = -1;
    new->left = new;
    new->right = new;
    return new;
};

struct node * insert_right(struct node *list, int data){
    struct node *new = (struct node *) malloc(sizeof(struct node));
	new->data        = data;
	new->left        = list;
	new->right       = list->right;
	list->right      = new;
	new->right->left = new;
	return new;
}

struct node * delete(struct node *list){
	list->right->left = list->left;         //setzt linken Wert des rechten Nachbarn auf linken Wert von list
	list->left->right = list->right;        //setzt rechten Wert des linken Nachbarn auf rechten Wert von list
	return list->left;
}

void print_all(struct node* list){
	struct node *head = list;
	struct node *current = list;
	printf("%d ", head->data);
	while (head != (current = current->right)){
		printf("%d ", current->data);
	}
	printf("\n");
}

