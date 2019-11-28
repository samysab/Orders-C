void login_connect(GtkWidget*, GtkWidget**);


void adminLoginWindow(){

	// Déclaration des widget 
	GtkWidget *pWindow;
	GtkWidget *rootBox;
	GtkWidget *pLabelAdminPanel;
	GtkWidget *pLabelLogin;
	GtkWidget *pLabelPassword;
	gchar* sUtf8;
	GtkWidget *pTable;
	GtkWidget *pButton[2];
	GtkWidget *pEntryLogin;
	GtkWidget *pEntryPassword;


	// Création de la fenêtre 
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// Creation du container root
	rootBox = gtk_hbox_new(TRUE, 0);

	// Ajouter un titre à la fenetre
	gtk_window_set_title(GTK_WINDOW(pWindow), "Recapitulatif de votre commande - Burger C");
	//Initialise la taille des fenetres par défaut
	gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 400);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

	pTable= gtk_table_new(5,4,TRUE);

	// Création du label
	pLabelAdminPanel = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\">Connexion panel Admin </span></u></b>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelAdminPanel), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelAdminPanel), GTK_JUSTIFY_CENTER);


	// Création du label
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

	// Creation du GtkEntry 
	pEntryLogin = gtk_entry_new();
	pEntryPassword = gtk_entry_new();
	// cacher ce qui est tape
	gtk_entry_set_visibility(GTK_ENTRY(pEntryPassword), FALSE);


	gtk_table_attach(GTK_TABLE(pTable), pLabelAdminPanel, 0, 4, 0, 1,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelLogin, 0, 4, 1, 2,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pEntryLogin, 1, 3, 1, 3,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelPassword, 0, 4, 2, 3,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pEntryPassword, 1, 3, 2, 4,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[0], 1, 3, 3, 4,GTK_EXPAND,  GTK_EXPAND  , 0,0);

	// Connexion du signal "destroy" 
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

	// afficher login pass quand on appuie sur login
	// on cree un tableau dont la nature de donnee est un widget (d'ou le GtkWidget* )
	// un tableau etant un pointeur, on a donc un pointeur (tableau) de pointeurs (widgets)
	GtkWidget* creds[2];
	creds[0] = pEntryLogin;
	creds[1] = pEntryPassword;
	g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(login_connect), creds);


	// Permet d'afficher toute les infos sur la fenetre
	// gtk_container_add(GTK_CONTAINER(pWindow), pLabelAdminPanel);
	// gtk_box_pack_start(GTK_BOX(rootBox), pLabelAdminPanel, FALSE, FALSE, 0);

	// gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));

	gtk_container_add(GTK_CONTAINER(pWindow), pTable);


	// gtk_widget_show_all(pWindow); Affichage de la fenêtre */
	gtk_widget_show_all(pWindow);

	// Demarrage de la boucle evenementielle 
	gtk_main();

}


void login_connect(GtkWidget* button_clicked, GtkWidget** credsArray) {

	const char* login;
	const char* pass;

	login = gtk_entry_get_text(GTK_ENTRY(credsArray[0]));;
	pass = gtk_entry_get_text(GTK_ENTRY(credsArray[1]));;

	printf("login: %s - pass: %s\n", login, pass);

	// MYSQL mysql;
	// mysql_init(&mysql);
	// mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	// if (mysql_real_connect(&mysql, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {

	// 	mysql_query(&mysql, "SELECT adminLogin, adminPassword FROM admins");

	// 	MYSQL_RES *result = NULL;
	// 	MYSQL_ROW row;

	// 	unsigned int num_champs = 0;

	// 	result = mysql_use_result(&mysql);

	// 	num_champs = mysql_num_fields(result);

	// 	// char adminName[100];

	// 	// while ((row = mysql_fetch_row(result))) {
	// 	// 	printf("%s", row[0]);
	// 	// 	// for (int i = 0; i < num_champs; i++) {

	// 	// 	// 	// loginString = g_locale_to_utf8((char*)row[i], -1, NULL, NULL, NULL);
	// 	// 	// 	// sprintf(adminName, "Voici un admin : %s\n", row[i]);
	// 	// 	// 	// puts(adminName);
	// 	// 	// }
	// 	// }

	// 	printf("Fin code de bdd ok");
	// 	mysql_close(&mysql);
	// } else {
	// 	printf("Erreur bdd");
	// }

}
