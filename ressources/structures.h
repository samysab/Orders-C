// structure pour la manipulation des listes chainees des produits
typedef struct product {
	int id;
	char name[50];
	char image_path[50];
	int price;

	struct product *next;
} product_t;

typedef struct sum_node {
	char name[50];
	int id;
	int price;
	int nb;
	struct sum_node *next;
} sum_t;
