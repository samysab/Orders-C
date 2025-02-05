void Windowscommande() {

	char** config = configuration();

	// D�claration des widget
	GtkWidget *pWindow;
	GtkWidget *pLabelOrdersC;
	GtkWidget *pLabelOrders;
	GtkWidget *pLabelTotal;
	gchar* sUtf8;
	GtkWidget *btnValidateOrder;
	GtkWidget *pTable;
	GtkWidget *panierWindowScrollbar;

	// Cr�ation de la fen�tre
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// Ajouter un titre � la fenetre
	gtk_window_set_title(GTK_WINDOW(pWindow), "MENU - Burger C");

	//Initialise la taille des fenetres par d�faut
	gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 700);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

	pTable = gtk_table_new(7, 6, TRUE);
	// marge entre les menus et les produits
	gtk_table_set_col_spacing(GTK_TABLE(pTable), 0, 30);
	// marge entre les produits et le bouton Valider la commande ?




	// Cr�ation du label Titre
	pLabelOrdersC = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\"><span font_family=\"Courier New\">Burger C - Passer commande</span></span></u></b>",-1, NULL,NULL, NULL); //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelOrdersC), sUtf8);
	// gtk_label_set_markup(GTK_LABEL(pLabelOrdersC), "Burger C - Passer commande");
	gtk_label_set_justify(GTK_LABEL(pLabelOrdersC), GTK_JUSTIFY_CENTER);

	// Label Total
	pLabelTotal = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\"><span font_family=\"Courier New\">Total : 0 �</span></span></u></b>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(pLabelTotal), "Total : 0 euro");
	gtk_label_set_justify(GTK_LABEL(pLabelTotal), GTK_JUSTIFY_CENTER);

	// Cr�ation du label Panier
	pLabelOrders = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span font_family=\"Courier New\">Panier :</span></u></b>",-1, NULL,NULL, NULL); //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelOrders), sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelOrders), GTK_JUSTIFY_CENTER);

	btnValidateOrder = gtk_button_new_with_label("Valider la commande");

	panierWindowScrollbar = gtk_scrolled_window_new(NULL, NULL);
	GtkWidget* panierRootbox = gtk_hbox_new(FALSE, 0);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(panierWindowScrollbar), panierRootbox);

	// marge entre tableau des produits et le panier
	gtk_table_set_row_spacing(GTK_TABLE(pTable), 4, 25);


	gtk_table_attach(GTK_TABLE(pTable), pLabelOrdersC, 2, 4, 0, 1, GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelTotal, 0, 1, 5, 6, GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelOrders, 0, 1, 6, 7, GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), btnValidateOrder, 5, 6, 6, 7, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), panierWindowScrollbar, 1, 5, 5, 7, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);


	// par defaut on peut pas appuyer sur le bouton Valider si on n'a aucun produit dans le panier
	gtk_widget_set_sensitive(btnValidateOrder, FALSE);


	// creation de la liste chainee du panier
	product_t *panier = NULL;

	panier = malloc(sizeof(product_t));
	panier->id = 1;
	strcpy(panier->name, "Premier Element Panier");
	strcpy(panier->image_path, "./sample.png");
	panier->price = 0;
	panier->next = NULL;


	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");


	if (mysql_real_connect(&mysql, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {
		int i, j;
		GtkWidget* scrolledWindow;
		scrolledWindow = gtk_scrolled_window_new(NULL, NULL);


		// on cree le tableau dynamique qui va contenir les types en unique
		char** fullTypesArray;
		char** inter;
		int fullTypesArraySize = 1;
		fullTypesArray = malloc(sizeof(char*) * fullTypesArraySize);


		char query[200];

		char borneLocation[50];
		strcpy(borneLocation, config[2]);

		if(borneLocation[strlen(borneLocation)-1] == '\n'){
			borneLocation[strlen(borneLocation)-1] = '\0';
		}

		sprintf(query, "SELECT productType FROM products WHERE borneLocation = \"%s\"", borneLocation);
		mysql_query(&mysql, query);

		MYSQL_ROW firstRow;
		MYSQL_ROW row;

		MYSQL_RES *result = NULL;

		result = mysql_use_result(&mysql);

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
				// on verifie qu'on compare pas rien et Quelque chose
				// printf("%s ? %s\n", fullTypesArray[i], fullTypesArray[j]);
				if (strlen(fullTypesArray[i]) != 0 && strlen(fullTypesArray[j]) != 0) {
					if (strcmp(fullTypesArray[i], fullTypesArray[j]) == 0) {
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

		// on cree une liste chainee des produits contenus
		product_t *loadTypesList = NULL;
		loadTypesList = malloc(sizeof(product_t));
		loadTypesList->id = 5555;
		strcpy(loadTypesList->name, "name_test_origin");
		strcpy(loadTypesList->image_path, "./demo.png");
		loadTypesList->price = 6666;
		loadTypesList->next = NULL;

		int totalPanier = 0;

		// on cree le tableau qui contiendra nos widgets de reference
		void** widgetsTab;
		widgetsTab = malloc(sizeof(void*) * 9);
		widgetsTab[0] = pTable;
		widgetsTab[1] = scrolledWindow;
		widgetsTab[2] = &mysql;
		widgetsTab[3] = panier;
		widgetsTab[4] = panierWindowScrollbar;
		widgetsTab[5] = loadTypesList;
		widgetsTab[6] = &totalPanier;
		widgetsTab[7] = pLabelTotal;
		widgetsTab[8] = btnValidateOrder;



		for (i = 1; i < typesSize; i++) {
			sUtf8 = g_locale_from_utf8(types[i] ,-1, NULL,NULL, NULL);
			type_button = gtk_button_new_with_label(sUtf8);

			g_signal_connect(G_OBJECT(type_button), "clicked", G_CALLBACK(loadTypes), widgetsTab);
			gtk_box_pack_start(GTK_BOX(vboxTypes), type_button, FALSE, TRUE, 0);

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



		GtkWidget* productsTable;
		productsTable = gtk_table_new(1, 4, TRUE);



		// on passe a la deuxieme requete (les produits)

		sprintf(query, "SELECT productId, productName, productImg, productPrice FROM products WHERE borneLocation = \"%s\"", borneLocation);
		mysql_query(&mysql, query);

		result = mysql_use_result(&mysql);

		GtkWidget* burger_box;
		GtkWidget* burger_image;
		GtkWidget* burger_price;
		GtkWidget* burger_button;


		// Le 4 correspond au nombre de lignes,
		// il devrait etre calcul� en fonction du nombre de produits qu'on a
		// nb_produits / 3
		// euh  si on met un nombre inferieur au nombre correct de lignes
		// ca marche quand meme, hmm
		// les marges entre less lignes et colonnes

		/* je les ai remont�s plus haut pour pouvoir donner l'adresse de productsTable a la fonction loadTypes()
		GtkWidget* productsTable;
		productsTable = gtk_table_new(1, 4, TRUE);
		*/
		gtk_table_set_row_spacings(GTK_TABLE(productsTable), 20);
		gtk_table_set_col_spacings(GTK_TABLE(productsTable), 20);
		int row_start = 0;
		int row_end = 1;
		int col_start = 0;
		int	col_end = 1;

		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		product_t *current;

		while ((row = mysql_fetch_row(result))) {
			/*
			* les index (genre row[0], row[1]...) sont dans l'ordre dans lequel on a fait le SELECT !!!
			*
			*/

			// burger box contient l'image du burger ainsi que son bouton heponyme
			burger_box = gtk_vbox_new(FALSE, 10);

			burger_image = gtk_image_new_from_file(row[2]);

			sUtf8 = g_locale_to_utf8(strcat(row[3], " �"), -1, NULL, NULL, NULL);
			burger_price = gtk_label_new(sUtf8);

			sUtf8 = g_locale_to_utf8(row[1], -1, NULL, NULL, NULL);
			burger_button = gtk_button_new_with_label(sUtf8);

			current = loadTypesList;

			addList(current, atoi(row[0]), row[1], row[2], atoi(row[3]));


			widgetsTab[5] = loadTypesList;

			// on ajoute la fonction d'ajout au panier sur le bouton
			g_signal_connect(G_OBJECT(burger_button), "clicked", G_CALLBACK(addTypesList), widgetsTab);


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

		// 	// comme on utilise la meme variable pour tous les burgers,
		// 	// il faut la vider pour lui donner une nouvelle identite
		// 	// sans le free ca marche mais on a des erreurs gtk_table_assertion_failed
		// 	free(burger_box);
		}

		// on ajoute burger box a la box de tous les produits
		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledWindow), productsTable);

		gtk_table_attach(GTK_TABLE(pTable), scrolledWindow, 1, 6, 1, 5, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

		mysql_free_result(result);

		// source de crashs inopin�s
		// mysql_close(&mysql);

	} else {
		printf("Erreur bdd");
	}


	void** orderVarsArray = malloc(sizeof(void*)*2);
	orderVarsArray[0] = panier;
	orderVarsArray[1] = pWindow;

	g_signal_connect(G_OBJECT(btnValidateOrder),"clicked", G_CALLBACK(orderWindow), orderVarsArray);

	// Connexion du signal "destroy"
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

	gtk_container_add(GTK_CONTAINER(pWindow), pTable);


	// On libere la memoire de de la chaine de caractere sutf8
	g_free(sUtf8);

	gtk_widget_show_all(pWindow);

	// Affichage de la fen�tre
	gtk_widget_show(pWindow);

	// Demarrage de la boucle evenementielle
	gtk_main();

}
