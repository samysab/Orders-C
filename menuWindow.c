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

	// Creation du container root
	// rootBox = gtk_hbox_new(TRUE, 0);
	
	// Ajouter un titre à la fenetre
	gtk_window_set_title(GTK_WINDOW(pWindow), "MENU - Burger C");
	
	//Initialise la taille des fenetres par défaut
	gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 700);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

	pTable = gtk_table_new(7,6,TRUE);

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




	// box


	GtkWidget* productsHbox;
	productsHbox = gtk_hbox_new(FALSE, 10);

	gtk_table_attach(GTK_TABLE(pTable), productsHbox, 2, 6, 1, 5, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);


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
		int iColStart = 2;
		int iColEnd = 3;
		int j = 1;
		int k = 2;
		GtkWidget* burger_button;
		while ((row = mysql_fetch_row(result))) {
			for (int i = 0; i < num_champs; i++) {

				sUtf8 = g_locale_to_utf8(row[i], -1, NULL, NULL, NULL);
				burger_button = gtk_button_new_with_label(sUtf8);
				//gtk_box_pack_start(GTK_BOX(productsHbox), burger_button, FALSE, FALSE, 0);
				gtk_table_attach(GTK_TABLE(pTable), burger_button, iColStart, iColEnd, j, k, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

				iColEnd +=1;
				iColStart +=1;

				if(iColEnd == 6){
					iColStart = 2;
					iColEnd = 3;
					j ++;
					k ++;
				}
			}

		}
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
