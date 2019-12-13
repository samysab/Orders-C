void adminLoginWindow();

void firstWindow(){

	// Déclaration des widget 
	GtkWidget *pWindow;
	GtkWidget *pLabelOrdersC;
	GtkWidget *pLabelDescription;
	gchar* sUtf8;
	GtkWidget *pButton[3];
	GtkWidget *pTable;
	// Création de la fenêtre 
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		// Ajouter un titre à la fenetre
	gtk_window_set_title(GTK_WINDOW(pWindow), "Page acceuil");
		//Initialise la taille des fenetres par défaut
	gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 400);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

	pTable= gtk_table_new(5,4,TRUE);
	gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));

	// Création du label
	pLabelOrdersC = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\"><span font_family=\"Courier New\">C Orders</span></span></u></b>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelOrdersC), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelOrdersC), GTK_JUSTIFY_CENTER);


	// Création du label
	pLabelDescription = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<span size=\"15\">Ou souhaitez vous mangez ?</span>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelDescription), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelDescription), GTK_JUSTIFY_CENTER);




	pButton[0] = gtk_button_new_with_label("Sur Place");
	pButton[1] = gtk_button_new_with_label("A Emporter");
	pButton[2] = gtk_button_new_with_label("Admin");

	gtk_table_attach(GTK_TABLE(pTable), pButton[0], 0, 2, 3, 4, GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[1], 2, 4, 3, 4, GTK_EXPAND | GTK_FILL , GTK_EXPAND | GTK_FILL, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[2], 3, 4, 0, 1, GTK_EXPAND | GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelOrdersC, 1, 3, 1, 2,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelDescription, 1, 3, 2, 3,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);



	//permet d'ouvrir une anouvelle fenetre
	g_signal_connect(G_OBJECT(pButton[0]),"clicked",G_CALLBACK(Windowscommande),NULL);
	g_signal_connect(G_OBJECT(pButton[1]),"clicked",G_CALLBACK(Windowscommande),NULL);
	g_signal_connect(G_OBJECT(pButton[2]),"clicked",G_CALLBACK(adminLoginWindow),NULL);

	// Connexion du signal "destroy" 
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);


	//Permet d'afficher toute les infos sur la fenetre
	// gtk_container_add(GTK_CONTAINER(pWindow), pLabelOrdersC);
	// gtk_container_add(GTK_CONTAINER(pWindow), pLabelDescription);

	gtk_widget_show_all(pWindow);
	// Affichage de la fenêtre 
	gtk_widget_show(pWindow);

	// Demarrage de la boucle evenementielle 
	gtk_main();
	newOrder();

}
