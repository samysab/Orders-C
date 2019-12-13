void addPanier(GtkWidget *btn, MYSQL *mysql) {
	printf("J'ajoute : %s\n", gtk_button_get_label(GTK_BUTTON(btn)));
	 //On déclare un tableau de char pour y stocker la requete
                char requete[150] = "";
                //char test[10] = "Hamburger";
                //On stock la requete dans notre tableau de char
                sprintf(requete, "SELECT productId FROM products WHERE productName = '%s'", gtk_button_get_label(GTK_BUTTON(btn)));
                //On execute la requete
                mysql_query(&mysql, requete);
        //Déclaration des objets
        MYSQL_RES *arrayResult = NULL;
        MYSQL_ROW line;

        unsigned int j = 0;
        unsigned int number_champs = 0;

        //On met le jeu de résultat dans le pointeur result
        arrayResult = mysql_use_result(&mysql);

        //On récupère le nombre de champs
        number_champs = mysql_num_fields(arrayResult);

        //Tant qu'il y a encore un résultat ...
        while ((line = mysql_fetch_row(arrayResult)))
        {
            //On déclare un pointeur long non signé pour y stocker la taille des valeurs
            unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(arrayResult);

            //On fait une boucle pour avoir la valeur de chaque champs
            for(j = 0; j < number_champs; j++)
            {
               //On ecrit toutes les valeurs
               printf("[%.*s] ", (int) lengths[j], line[j]);
            }
            printf("\n");
        }

        //Libération du jeu de résultat
        mysql_free_result(arrayResult);
}
