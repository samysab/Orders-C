void OnDestroy(GtkWidget *pWidget, gpointer pData);
void orderWindow();

void Windowscommande(){

	// Déclaration des widget 
	GtkWidget *pWindow;
	// GtkWidget *rootBox;
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

	pTable = gtk_table_new(7,6,TRUE);
	gtk_table_set_col_spacings(pTable, 20);

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


	pButton[0] = gtk_button_new_with_label("Menus");
	pButton[1] = gtk_button_new_with_label("Petites faim");
	pButton[2] = gtk_button_new_with_label("Boissons");
	pButton[3] = gtk_button_new_with_label("Glaces");
	pButton[4] = gtk_button_new_with_label("Valider la commande");


	gtk_table_attach(GTK_TABLE(pTable), pButton[0], 0, 1, 1, 2, GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[1], 0, 1, 2, 3, GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[2], 0, 1, 3, 4, GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[3], 0, 1, 4, 5, GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelOrdersC, 0, 2, 0, 1,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelOrders, 0, 1, 5, 6,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[4], 5, 6, 6, 7, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);



	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	
	
	if (mysql_real_connect(&mysql, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {

		mysql_query(&mysql, "SELECT productName FROM products");

		MYSQL_RES *result = NULL;
		MYSQL_ROW row;

		unsigned int num_champs = 0;

		result = mysql_use_result(&mysql);

		num_champs = mysql_num_fields(result);

		GtkWidget* burger_box;
		GtkWidget* burger_image;
		GtkWidget* burger_button;
		

		GtkWidget* productsBox;


		// Le 4 correspond au nombre de lignes,
		// il devrait etre calculé en fonction du nombre de produits qu'on a
		// nb_produits / 3
		// euh quand si on met un nombre inferieur au nombre correct de lignes
		// ca marche quand meme, hmm
		productsBox = gtk_table_new(1, 3, TRUE);
		gtk_table_set_row_spacings(productsBox, 10);
		int row_start = 0;
		int row_end = 1;
		int col_start = 0;
		int	col_end = 1;



		GtkWidget* scrolledWindow;
		scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		while ((row = mysql_fetch_row(result))) {
			for (int i = 0; i < num_champs; i++) {
				// burger box contient l'image du burger ainsi que son bouton heponyme
				burger_box = gtk_vbox_new(FALSE, 5);

				burger_image = gtk_image_new_from_file("./burger.png");

				sUtf8 = g_locale_to_utf8(row[i], -1, NULL, NULL, NULL);
				burger_button = gtk_button_new_with_label(sUtf8);

				gtk_box_pack_start(GTK_BOX(burger_box), burger_image, FALSE, FALSE, 0);
				gtk_box_pack_start(GTK_BOX(burger_box), burger_button, FALSE, FALSE, 0);

				gtk_table_attach(GTK_TABLE(productsBox), burger_box, row_start, row_end, col_start, col_end, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
				row_start += 1;
				row_end += 1;

				if (row_start == 3) {
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
		}

		// on ajoute burger box a la box de tous les produits
		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledWindow), productsBox);

		gtk_table_attach(GTK_TABLE(pTable), scrolledWindow, 2, 5, 1, 5, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

		mysql_close(&mysql);
	} else {
		printf("Erreur bdd");
	}






	g_signal_connect(G_OBJECT(pButton[4]),"clicked",G_CALLBACK(orderWindow),NULL);

	// Connexion du signal "destroy"
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);


	// Permet d'afficher toute les infos sur la fenetre
	// gtk_container_add(GTK_CONTAINER(pWindow), pLabelOrdersC);
	// gtk_container_add(GTK_CONTAINER(pWindow), pLabelOrders);


	// On ajoute le tableau a la rootbox
	// gtk_box_pack_start(GTK_BOX(rootBox), pTable, FALSE, FALSE, 0);

	// on ajoute la rootbox a la fenetre
	// gtk_container_add(GTK_CONTAINER(pWindow), rootBox);
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
