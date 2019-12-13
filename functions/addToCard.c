void addPanier(GtkWidget *btn) {
	printf("J'ajoute : %s\n", gtk_button_get_label(GTK_BUTTON(btn)));
	 /*MYSQL mysql;
    //Initialisation de MySQL
    mysql_init(&mysql);
                //On stock la requete dans notre tableau de char

                //On execute la requete
                mysql_query(&mysql, scanf("SELECT productId FROM products WHERE productName = '%s'", gtk_button_get_label(GTK_BUTTON(btn))));
        //Déclaration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;

        unsigned int i = 0;
        unsigned int num_champs = 0;

        //On met le jeu de résultat dans le pointeur result
        result = mysql_use_result(&mysql);

        //On récupère le nombre de champs
        num_champs = mysql_num_fields(result);

        //Tant qu'il y a encore un résultat ...
        while ((row = mysql_fetch_row(result)))
        {
            //On déclare un pointeur long non signé pour y stocker la taille des valeurs
            unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

            //On fait une boucle pour avoir la valeur de chaque champs
            for(i = 0; i < num_champs; i++)
            {
               //On ecrit toutes les valeurs
               printf("[%.*s] ", (int) lengths[i], row[i]);
            }
            printf("\n");
        }

        //Libération du jeu de résultat
        mysql_free_result(result);*/
}
