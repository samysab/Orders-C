void removeProduct(GtkWidget*);

// fonction pour afficher une liste
void browseList(product_t *head) {
	printf("\n### Browse list ###\n");
	product_t *current = head;
	while (current != NULL) {
		printf("	current->id : %d\n", current->id);
		printf("	current->name : %s\n", current->name);
		printf("	current->image_path : %s\n", current->image_path);
		printf("	current->price : %d\n\n", current->price);
		current = current->next;
	}
}

// fonction pour ajouter un produit en fin d'une liste
void addList(product_t *head, int id, char name[50], char image_path[50], int price) {
	product_t *current = head;

	while (current->next != NULL)
		current = current->next;

	current->next = malloc(sizeof(product_t));

	current->next->id = id;
	strcpy(current->next->name, name);
	strcpy(current->next->image_path, image_path);
	current->next->price = price;
	current->next->next = NULL;
}

// suppression en tete
product_t* deleteFirst(product_t *start) {
	product_t *current = start;
	if (current != NULL) {
		start = start->next;
		free(current);
	}
	return start;
}

product_t* deleteList(product_t *start) {
	while (start != NULL) {
		start = deleteFirst(start);
	}
	return NULL;
}


/*
* ####################################
* ######## Ajout d'un produit ########
* ####################################
*/

void addTypesList(GtkWidget *btn, void** data) {
	/*
	* addTypesList va recevoir :
	*	- les details d'un produit clique
	*	- la liste chaine head
	*
	* et va ajouter a head comme nouveau maillon le produit clique
	*
	*/

	char produit_choisi[50];
	strcpy(produit_choisi, gtk_button_get_label(GTK_BUTTON(btn)));


	printf("\nPartie 1 - Details du produit clique\n");


	product_t *loadList = (product_t*)data[5];
	// on ignore le premier car c'est pas une vraie donnee
	loadList = loadList->next;

	// on s'avance jusqu'a la case qui contient les details du produit qu'on a clique
	while (strcmp(loadList->name, produit_choisi)) {
		loadList = loadList->next;
	}
	// printf("stop");
	// affichage des details du produit clique
	printf("%d\n", loadList->id);
	printf("%s\n", loadList->name);
	printf("%s\n", loadList->image_path);
	printf("%d\n", loadList->price);

	// on a les infos du produit
	// on a les adresses du tableau pTable
	// on peut joindre les 2 bouts
	/*
	* 1. on retirer la windowScrollbar actuelle pour mettre une nouvelle version
	* 2. on declare nos widgets panierWindowScrollbar, panierRootbox, et ceux pour les produits
	* 3. on ajoute les produits produits déjà présents depuis la liste chainee panier A cette rootbox
	* 4. on ajoute le produit clique a la rootbox
	* 5. on ajoute la rootbox a panierRootbox
	* 6. 
	*/

	// 1
	gtk_container_remove(GTK_CONTAINER((GtkWidget*)data[0]), (GtkWidget*)data[4]);

	// 2
	GtkWidget* panierWindowScrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(panierWindowScrollbar), GTK_POLICY_ALWAYS, GTK_POLICY_NEVER);
	// on cree une box racine (les windowsscrollbar ne peuvent contenir qu'un seul enfant)
	GtkWidget* panierRootbox = gtk_hbox_new(FALSE, 0);

	// la box du produit
	GtkWidget* newProduitDansPanier;
	// le label du produit 
	GtkWidget* newProduitLabel;
	// le bouton Retirer
	GtkWidget* enleverButton;

	product_t *current = (product_t*)data[3];
	current = current->next;

	// 3
	// on remplit notre windowScrollbar avec les produits déjà cliqués auparavant
	while (current != NULL) {
		// la box du produit
		GtkWidget* newProduitDansPanier;
		// le label du produit 
		GtkWidget* newProduitLabel;
		// le bouton Retirer
		GtkWidget* enleverButton;

		newProduitDansPanier = gtk_vbox_new(FALSE, 0);
		newProduitLabel = gtk_label_new(current->name);
		enleverButton = gtk_button_new_with_label("Retirer");

		g_signal_connect(G_OBJECT(enleverButton), "clicked", G_CALLBACK(removeProduct), NULL);

		// on pack le tout dans la box
		gtk_box_pack_start(GTK_BOX(newProduitDansPanier), newProduitLabel, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(newProduitDansPanier), enleverButton, FALSE, FALSE, 0);

		// on pack la box dans la rootbox
		gtk_box_pack_start(GTK_BOX(panierRootbox), newProduitDansPanier, FALSE, FALSE, 0);

		// on passe au suivant
		current = current->next;
	}


	// 4
	// la box du produit 
	newProduitDansPanier = gtk_vbox_new(FALSE, 0);
	// le nom du produit 
	newProduitLabel = gtk_label_new(loadList->name);
	// le bouton retirer
	enleverButton = gtk_button_new_with_label("Retirer");

	g_signal_connect(G_OBJECT(enleverButton), "clicked", G_CALLBACK(removeProduct), NULL);

	// on pack le tout dans la box
	gtk_box_pack_start(GTK_BOX(newProduitDansPanier), newProduitLabel, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(newProduitDansPanier), enleverButton, FALSE, FALSE, 0);

	// 5
	// on ajoute la box a la rootbox
	gtk_box_pack_start(GTK_BOX(panierRootbox), newProduitDansPanier, FALSE, FALSE, 0);

	// on a une nouvelle rootbox avec le nouveau produit
	// on ajoute la rootbox au panierWindowScrollbar qui est widgetsTab[4];
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(panierWindowScrollbar), panierRootbox);

	// // on ajoute la windowScrollbar au pTable (a notre fenetre)
	gtk_table_attach(GTK_TABLE((GtkWidget*)data[0]), panierWindowScrollbar, 1, 5, 5, 7, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

	gtk_widget_show_all((GtkWidget*)data[0]);


	// on ajoute le produit a la panierRootbox


	// on ajoute le produit clique a la liste chainee du panier
	printf("\nPartie 2 - Affichage du panier actuel\n");
	printf("clique sur : %s\n", produit_choisi);
	// on recupere head, en le convertissant en son type respectif
	product_t *panier = (product_t*)data[3];
	// // on affiche l'id par exemple
	printf("%d\n", (int*)loadList->id);
	printf("%s\n", (int*)loadList->name);
	printf("%s\n", (int*)loadList->image_path);
	printf("%d\n", (int*)loadList->price);
	addList(panier, loadList->id, loadList->name, loadList->image_path, loadList->price);

	printf("Voici le panier : \n");
	browseList(panier);


	printf("went through\n");
}

// ...
// |__panierWindowScrollbar
// 	|___panierRootbox
// 		|___newProduitDansPanier
// 			|__btn

void removeProduct(GtkWidget* btn) {

	printf("je supprime \n");

	GtkWidget* la_box_du_produit_clique = gtk_widget_get_parent(btn);
	GtkWidget* rootbox = gtk_widget_get_parent(la_box_du_produit_clique);


	gtk_container_remove(GTK_CONTAINER(rootbox), la_box_du_produit_clique);

	gtk_widget_show_all(rootbox);

}



void loadTypes(GtkWidget *btn, void** widgetsTab) {
	printf("\n=============\nJe veux les produits de la categorie : %s\n", gtk_button_get_label(GTK_BUTTON(btn)));

	// on supprime le tableau actuel
	gtk_container_remove(GTK_CONTAINER(widgetsTab[0]), widgetsTab[1]);

	// on pourrait se servir directement dans widgetsTab pour accéder à la base de donnees mais c moche et hardcore a lire
	// du coup on se fait plaiz on recree une autre connexion qu'on close ensuite juste pour l'esthetique de code
	MYSQL* conn = (MYSQL*)widgetsTab[2];
	mysql_init(conn);


	if (mysql_real_connect(conn, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {
		GtkWidget* scrolledWindow;
		GtkWidget* productsTable;
		gchar* sUtf8;
		GtkWidget* burger_box;
		GtkWidget* burger_price;
		GtkWidget* burger_image;
		GtkWidget* burger_button;

		// longueur de partie avant variable = 76
		// on craft la requete avec le contenu du bouton cliqué passé en parametre de la fonction callback
		char query[200];
		sprintf(query, "SELECT productId, productName, productImg, productPrice FROM products WHERE productType = \"%s\"", gtk_button_get_label(GTK_BUTTON(btn)));

		mysql_query(conn, query);
		MYSQL_RES *result = NULL;
		MYSQL_ROW row;
		result = mysql_use_result(conn);


		productsTable = gtk_table_new(1, 4, TRUE);

		gtk_table_set_row_spacings(GTK_TABLE(productsTable), 20);
		gtk_table_set_col_spacings(GTK_TABLE(productsTable), 20);
		int row_start = 0;
		int row_end = 1;
		int col_start = 0;
		int	col_end = 1;

		scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);


		// creation de la liste chainee de reference qui contient tous les produits du type clique
		// product_t *loadTypesListHead = widgetsTab[5];
		product_t *loadTypesListHead = NULL;

		loadTypesListHead = malloc(sizeof(product_t));
		loadTypesListHead->id = 9999;
		strcpy(loadTypesListHead->name, "name_test");
		strcpy(loadTypesListHead->image_path, "./demo.png");
		loadTypesListHead->price = 8888;
		loadTypesListHead->next = NULL;


		while ((row = mysql_fetch_row(result))) {

			addList(loadTypesListHead, atoi(row[0]), row[1], row[2], atoi(row[3]));


			printf("J'ai ajoute le premier produit \"%s\" a la chaine\n", row[1]);


			// burger box contient l'image du burger ainsi que son bouton heponyme
			burger_box = gtk_vbox_new(FALSE, 10);

			burger_image = gtk_image_new_from_file(row[2]);

			sUtf8 = g_locale_to_utf8(strcat(row[3], " €"), -1, NULL, NULL, NULL);
			burger_price = gtk_label_new(sUtf8);


			sUtf8 = g_locale_to_utf8(row[1], -1, NULL, NULL, NULL);
			burger_button = gtk_button_new_with_label(sUtf8);


			sUtf8 = g_locale_to_utf8(row[0], -1, NULL, NULL, NULL);

			widgetsTab[5] = loadTypesListHead;


			printf("les produits de cette categorie: \n   id : %d;\n   name : %s;\n   img: %s;\n   price : %d\n\n", atoi(row[0]), row[1], row[2], atoi(row[3]));

			// on ajoute la fonction d'ajout au panier sur le bouton
			g_signal_connect(G_OBJECT(burger_button), "clicked", G_CALLBACK(addTypesList), widgetsTab );


			gtk_box_pack_start(GTK_BOX(burger_box), burger_image, FALSE, FALSE, 0);
			gtk_box_pack_start(GTK_BOX(burger_box), burger_price, FALSE, FALSE, 0);
			gtk_box_pack_start(GTK_BOX(burger_box), burger_button, FALSE, FALSE, 0);

			gtk_table_attach(GTK_TABLE(productsTable), burger_box, row_start, row_end, col_start, col_end, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
			row_start += 1;
			row_end += 1;

			if (row_start == 4) {
				row_start = 0;
				row_end = 1;

				col_start += 1;
				col_end = col_start + 1;
			}

			// free(burger_box);
			// free(burger_price);
			// free(burger_image);
			// free(burger_button);
		}

		printf("Voici la liste :\n");
		browseList(loadTypesListHead);

		// on ajoute burger box a la box de tous les produits
		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledWindow), productsTable);

		gtk_table_attach(GTK_TABLE(widgetsTab[0]), scrolledWindow, 1, 6, 1, 5, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
		widgetsTab[1] = scrolledWindow;

		mysql_free_result(result);

		mysql_close(conn);
	}



	// on affiche le nouveau tableau
	gtk_widget_show_all(widgetsTab[1]);


}


