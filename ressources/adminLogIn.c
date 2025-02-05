void adminLoginWindow(){

	// D�claration des widget 
	GtkWidget *pWindow;
	GtkWidget *pLabelAdminPanel;
	GtkWidget *pLabelLogin;
	GtkWidget *pLabelPassword;
	gchar* sUtf8;
	GtkWidget *pTable;
	GtkWidget *pButton[2];
	GtkWidget *pEntryLogin;
	GtkWidget *pEntryPassword;


	// Cr�ation de la fen�tre 
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// Creation du container root

	// Ajouter un titre � la fenetre
	gtk_window_set_title(GTK_WINDOW(pWindow), "Recapitulatif de votre commande - Burger C");
	//Initialise la taille des fenetres par d�faut
	gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 400);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

	pTable= gtk_table_new(5,4,TRUE);

	// Cr�ation du label
	pLabelAdminPanel = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\">Connexion panel Admin </span></u></b>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelAdminPanel), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelAdminPanel), GTK_JUSTIFY_CENTER);


	// Cr�ation du label
	pLabelLogin = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<span size=\"15\">Login</span>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelLogin), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelLogin), GTK_JUSTIFY_CENTER);


	pLabelPassword = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<span size=\"15\">Mot de passe</span>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelPassword), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelPassword), GTK_JUSTIFY_CENTER);

	pButton[0] = gtk_button_new_with_label("Connexion");

	pEntryLogin = gtk_entry_new();
	pEntryPassword = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(pEntryPassword), FALSE);


	gtk_table_attach(GTK_TABLE(pTable), pLabelAdminPanel, 0, 4, 0, 1,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelLogin, 0, 4, 1, 2,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pEntryLogin, 1, 3, 1, 3,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelPassword, 0, 4, 2, 3,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pEntryPassword, 1, 3, 2, 4,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[0], 1, 3, 3, 4,GTK_EXPAND,  GTK_EXPAND  , 0,0);

	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

	GtkWidget* creds[2];
	creds[0] = pEntryLogin;
	creds[1] = pEntryPassword;
	g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(login_connect), creds);

	gtk_container_add(GTK_CONTAINER(pWindow), pTable);

	gtk_widget_show_all(pWindow);

	gtk_main();

}


void login_connect(GtkWidget* button_clicked, GtkWidget** credsArray) {

	// MYSQL mysql;
	// mysql_init(&mysql);
	// mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	char login[10];
	char pass[10];

	strcpy(login, gtk_entry_get_text(GTK_ENTRY(credsArray[0])));
	strcpy(pass, gtk_entry_get_text(GTK_ENTRY(credsArray[1])));

	printf("login: %s - pass: %s\n", login, pass);

	char query[200];
	sprintf(query, "SELECT adminLogin, adminPassword FROM admins WHERE adminLogin = \"%s\" AND adminPassword = \"%s\"", login, pass);

	printf("query : %s\n", query);

	// if (mysql_real_connect(&mysql, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {

		// MYSQL_RES *result = NULL;
		// MYSQL_ROW row;


		// printf("bruhhh\n");
		// mysql_query(&mysql, query);

		// result = mysql_use_result(&mysql);

		// while ((row = mysql_fetch_row(result))) {
		// 	printf("voici l'admin %s\n", row[0]);

		// }

		// printf("Fin code de bdd\n");

	// 	mysql_close(&mysql);
	// } else {
	// 	printf("Erreur bdd");
	// }

}
