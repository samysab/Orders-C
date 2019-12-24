// structure pour la manipulation des listes chainees des produits
typedef struct product {
	int id;
	char name[50];
	char image_path[50];
	int price;

	struct product *next;
} product_t;
