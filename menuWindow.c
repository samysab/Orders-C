void OnDestroy(GtkWidget *pWidget, gpointer pData);
void addPanier(GtkWidget *pWidget);
void loadTypes(GtkWidget *pWidget, void**);
void orderWindow();

void Windowscommande(){

	// Déclaration des widget
	GtkWidget *pWindow;
	GtkWidget *pLabelOrdersC;
	GtkWidget *pLabelOrders;
	gchar* sUtf8;
	GtkWidget *pButton[5];
	GtkWidget *pTable;

	// Création de la fenêtre
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// Ajouter un titre à la fenetre
	gtk_window_set_title(GTK_WINDOW(pWindow), "MENU - Burger C");

	//Initialise la taille des fenetres par défaut
	gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 700);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

	pTable = gtk_table_new(7, 6, TRUE);
	// marge entre les menus et les produits
	gtk_table_set_col_spacing(GTK_TABLE(pTable), 0, 50);
	// marge entre les produits et le bouton Valider la commande ?

	// Création du label Titre
	pLabelOrdersC = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\"><span font_family=\"Courier New\">Burger C - Passer commande</span></span></u></b>",-1, NULL,NULL, NULL); //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelOrdersC), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelOrdersC), GTK_JUSTIFY_CENTER);

	 // Création du label Panier
	pLabelOrders = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span font_family=\"Courier New\">Panier :</span></u></b>",-1, NULL,NULL, NULL); //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelOrders), sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelOrders), GTK_JUSTIFY_CENTER);


	// pButton[0] = gtk_button_new_with_label("Menus");
	// pButton[1] = gtk_button_new_with_label("Petites faim");
	// pButton[2] = gtk_button_new_with_label("Boissons");
	// pButton[3] = gtk_button_new_with_label("Glaces");
	pButton[4] = gtk_button_new_with_label("Valider la commande");


	gtk_table_attach(GTK_TABLE(pTable), pLabelOrdersC, 1, 2, 0, 1,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelOrders, 0, 1, 5, 6,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[4], 5, 6, 6, 7, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);




















	/*
	* Partie 1) Récupérer les types, supprimer les doublons et les afficher
	* Partie 2) Fonction qui récupère les produits selon une catégorie donnée et les ajoute
	*/

	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");


	if (mysql_real_connect(&mysql, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {
		int i, j;
		GtkWidget* productsTable;
		productsTable = gtk_table_new(1, 4, TRUE);



		// on passe a la deuxieme requete (les produits)


		mysql_query(&mysql, "SELECT productId, productName, productImg FROM products");

		MYSQL_RES *result = NULL;
		MYSQL_ROW row;


		result = mysql_use_result(&mysql);

		GtkWidget* burger_box;
		GtkWidget* burger_image;
		GtkWidget* burger_button;


		// Le 4 correspond au nombre de lignes,
		// il devrait etre calculé en fonction du nombre de produits qu'on a
		// nb_produits / 3
		// euh  si on met un nombre inferieur au nombre correct de lignes
		// ca marche quand meme, hmm
		// les marges entre less lignes et colonnes

		/* je les ai remontés plus haut pour pouvoir donner l'adresse de productsTable a la fonction loadTypes()
		GtkWidget* productsTable;
		productsTable = gtk_table_new(1, 4, TRUE);
		*/
		gtk_table_set_row_spacings(GTK_TABLE(productsTable), 20);
		gtk_table_set_col_spacings(GTK_TABLE(productsTable), 20);
		int row_start = 0;
		int row_end = 1;
		int col_start = 0;
		int	col_end = 1;



		GtkWidget* scrolledWindow;
		scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		while ((row = mysql_fetch_row(result))) {
			/*
			* les index (genre row[0], row[1]...) sont dans l'ordre dans lequel on a fait le SELECT !!!
			*
			*/


			// burger box contient l'image du burger ainsi que son bouton heponyme
			burger_box = gtk_vbox_new(FALSE, 10);

			burger_image = gtk_image_new_from_file(row[2]);

			sUtf8 = g_locale_to_utf8(row[1], -1, NULL, NULL, NULL);
			burger_button = gtk_button_new_with_label(sUtf8);


				// on ajoute la fonction d'ajout au panier sur le bouton
				g_signal_connect(G_OBJECT(burger_button), "clicked", G_CALLBACK(addPanier), NULL);

			gtk_box_pack_start(GTK_BOX(burger_box), burger_image, FALSE, FALSE, 0);
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

			// comme on utilise la meme variable pour tous les burgers,
			// il faut la vider pour lui donner une nouvelle identite
			// sans le free ca marche mais on a des erreurs gtk_table_assertion_failed
			free(burger_box);
		}

		// on ajoute burger box a la box de tous les produits
		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledWindow), productsTable);

		gtk_table_attach(GTK_TABLE(pTable), scrolledWindow, 1, 6, 1, 5, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

		mysql_free_result(result);










		// on cree le tableau dynamique qui va contenir les types en unique
		char** fullTypesArray;
		char** inter;
		int fullTypesArraySize = 1;
		fullTypesArray = malloc(sizeof(char*) * fullTypesArraySize);

		mysql_query(&mysql, "SELECT productType FROM products");

		MYSQL_ROW firstRow;
		// num_champs = 0;

		result = mysql_use_result(&mysql);
		// num_champs = mysql_num_fields(result);

		firstRow = mysql_fetch_row(result);
		fullTypesArray[0] = malloc(sizeof(char) * 255);
		strcpy(fullTypesArray[0], firstRow[0]);

		while ((row = mysql_fetch_row(result))) {

			inter = malloc(sizeof(char*) * (fullTypesArraySize + 1));
			for (int i = 0; i < fullTypesArraySize; i++) {
				inter[i] = malloc(sizeof(char) * 255);
				strcpy(inter[i], fullTypesArray[i]);
			}

			inter[fullTypesArraySize] = malloc(sizeof(char) * 255);
			strcpy(inter[fullTypesArraySize], row[0]);

			free(fullTypesArray);

			fullTypesArray = inter;

			fullTypesArraySize += 1;

			// ### A DECOMMENTER POUR COMPRENDRE
			// printf("Voici fullTypes : \n");
			// for (int i = 0; i < fullTypesArraySize; i++)
			// 	printf("	%s\n", fullTypesArray[i]);
		}

		free(inter);

		// on a un tableau dynamique qui contient tous les types
		// on doit supprimer les doublons
		for (i = 0; i < fullTypesArraySize; i++) {
			for (j = i+1; j < fullTypesArraySize; j++) {
				if (!strcmp(fullTypesArray[i], fullTypesArray[j])) {
					// ### A DECOMMENTER POUR COMPRENDRE
					// printf("doublon : %s == %s\n", fullTypesArray[i], fullTypesArray[j]);
					strcpy(fullTypesArray[j], "");
				}
				// } else {
					// ### A DECOMMENTER POUR COMPRENDRE
					// printf("differents : %s <> %s\n", fullTypesArray[i], fullTypesArray[j]);
				// }
			}
		}

		// ### A DECOMMENTER POUR COMPRENDRE
		// printf("\nTrie fullTypes : \n");
		// for (i = 0; i < fullTypesArraySize; i++)
		// 	printf("	%s\n", fullTypesArray[i]);

		int typesSize = 1;
		char** types = malloc(sizeof(char*) * typesSize);
		types[0] = malloc(sizeof(char) * 255);
		strcpy(types[0], "");

		// on cherche a savoir cb de types on a finalement
		int typesCounter = 0;
		for (i = 0; i < fullTypesArraySize; i++) {
			// si on trouve une case du tableau qui est differente de "" (strcmp renvoie un nb different de 0 si c different)
			if (strcmp(fullTypesArray[i], "")) {
				typesCounter++;

				inter = malloc(sizeof(char*) * typesSize + 1);
				// on copie types dans inter
				for (j = 0; j < typesSize; j++) {
					inter[j] = malloc(sizeof(char) * 255);
					strcpy(inter[j], types[j]);
				}

				inter[typesSize] = malloc(sizeof(char) * 255);
				strcpy(inter[j], fullTypesArray[i]);

				free(types);

				types = inter;

				typesSize++;

			}
		}

		// ### A DECOMMENTER POUR COMPRENDRE
		// printf("On a %d types\n", typesCounter);
		// printf("types : ");
		// for (i = 0; i < typesSize; i++)
		// 	printf("	%s\n", types[i]);


		// maintenant on ajoute ces types dans la barre a gauche
		GtkWidget* vboxTypes = gtk_vbox_new(TRUE, 0);
		GtkWidget* type_button;
		GtkWidget* scrolledWindowTypes;
		scrolledWindowTypes = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindowTypes), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		// on cree le tableau qui contiendra nos widgets de reference
		void* widgetsTab[2];
		widgetsTab[0] = pTable;
		widgetsTab[1] = scrolledWindow;
		widgetsTab[2] = &mysql;

		for (i = 1; i < typesSize; i++) {
			sUtf8 = g_locale_from_utf8(types[i] ,-1, NULL,NULL, NULL);
			type_button = gtk_button_new_with_label(sUtf8);

			g_signal_connect(G_OBJECT(type_button), "clicked", G_CALLBACK(loadTypes), widgetsTab);
			gtk_box_pack_start(GTK_BOX(vboxTypes), type_button, TRUE, TRUE, 0);

			free(type_button);
		}

		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledWindowTypes), vboxTypes);

		gtk_table_attach(GTK_TABLE(pTable), scrolledWindowTypes, 0, 1, 1, 5, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);





		for (i = 0; i < fullTypesArraySize; i++)
			free(fullTypesArray[i]);

		for (i = 0; i < typesSize; i++)
			free(inter[i]);

		for (i = 0; i < typesSize; i++)
			free(types[i]);

		free(fullTypesArray);
		free(inter);
		free(types);





		mysql_free_result(result);





		// mysql_close(&mysql);

	} else {
		printf("Erreur bdd");
	}






	g_signal_connect(G_OBJECT(pButton[4]),"clicked",G_CALLBACK(orderWindow),NULL);

	// Connexion du signal "destroy"
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

	gtk_container_add(GTK_CONTAINER(pWindow), pTable);


	// On libere la memoire de de la chaine de caractere sutf8
	g_free(sUtf8);

	gtk_widget_show_all(pWindow);

	// Affichage de la fenêtre
	gtk_widget_show(pWindow);

	// Demarrage de la boucle evenementielle
	gtk_main();

}

void OnDestroy(GtkWidget *pWidget, gpointer pData) {
	// Arret de la boucle evenementielle
	gtk_main_quit();
}



void loadTypes(GtkWidget *btn, void** widgetsTab) {
	printf("Je veux les produits de la categorie : %s\n", gtk_button_get_label(GTK_BUTTON(btn)));

	// on supprime le tableau actuel
	gtk_container_remove(GTK_CONTAINER(widgetsTab[0]), widgetsTab[1]);

	MYSQL* conn = (MYSQL*)&widgetsTab[2];

	if (mysql_real_connect(conn, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {
		GtkWidget* productsTable;
		productsTable = gtk_table_new(1, 4, TRUE);
		gchar* sUtf8;

		// longueur de partie avant variable = 76
		// on craft la requete avec le contenu du bouton cliqué passé en parametre de la fonction callback
		char query[200];
		sprintf(query, "SELECT productId, productName, productImg FROM products WHERE productType = \"%s\"", gtk_button_get_label(GTK_BUTTON(btn)));

		mysql_query(conn, query);

		MYSQL_RES *result = NULL;
		MYSQL_ROW row;


		result = mysql_use_result(conn);

		GtkWidget* burger_box;
		GtkWidget* burger_image;
		GtkWidget* burger_button;

		gtk_table_set_row_spacings(GTK_TABLE(productsTable), 20);
		gtk_table_set_col_spacings(GTK_TABLE(productsTable), 20);
		int row_start = 0;
		int row_end = 1;
		int col_start = 0;
		int	col_end = 1;


		GtkWidget* scrolledWindow;
		scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		while ((row = mysql_fetch_row(result))) {

			// burger box contient l'image du burger ainsi que son bouton heponyme
			burger_box = gtk_vbox_new(FALSE, 10);

			burger_image = gtk_image_new_from_file(row[2]);

			sUtf8 = g_locale_to_utf8(row[1], -1, NULL, NULL, NULL);
			burger_button = gtk_button_new_with_label(sUtf8);


			// on ajoute la fonction d'ajout au panier sur le bouton
			g_signal_connect(G_OBJECT(burger_button), "clicked", G_CALLBACK(addPanier), NULL);


			gtk_box_pack_start(GTK_BOX(burger_box), burger_image, FALSE, FALSE, 0);
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

			free(burger_box);
			free(sUtf8);

		}

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

