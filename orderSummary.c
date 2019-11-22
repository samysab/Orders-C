
void orderWindow(GtkWidget *widget){

       /* Déclaration des widget */
    GtkWidget *pWindow;
    GtkWidget *pLabelRecapitulatif;
    GtkWidget *pLabelCommentary;
    gchar* sUtf8;
    GtkWidget *pTable;
    GtkWidget* text_view;
    GtkWidget *pButton[2];

            /* Création de la fenêtre */
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        // Ajouter un titre à la fenetre
    gtk_window_set_title(GTK_WINDOW(pWindow), "Recapitulatif de votre commande - Burger C");
        //Initialise la taille des fenetres par défaut
    gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 400);
    gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

    pTable= gtk_table_new(5,4,TRUE);
    gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));

   /* Création du label*/
    pLabelRecapitulatif = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\">Votre Recapitulatif </span></u></b>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelRecapitulatif), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabelRecapitulatif), GTK_JUSTIFY_CENTER);


      /* Création du label*/
    pLabelCommentary = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("<span size=\"15\">Un commentaire ?</span>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelCommentary), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabelCommentary), GTK_JUSTIFY_CENTER);


    /* Creation du GtkEntry */
    text_view=gtk_text_view_new();


    pButton[0] = gtk_button_new_with_label("Terminer la commande");

    gtk_table_attach(GTK_TABLE(pTable), pLabelRecapitulatif, 0, 2, 0, 1,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pLabelCommentary, 0, 2, 2, 3,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), text_view, 0, 4, 3, 4,GTK_EXPAND| GTK_FILL ,  GTK_EXPAND | GTK_FILL, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pButton[0], 3, 4, 4, 5,GTK_EXPAND,  GTK_EXPAND  , 0,0);

    /* Connexion du signal "destroy" */
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);


    //Permet d'afficher toute les infos sur la fenetre
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelRecapitulatif);
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelCommentary);




    gtk_widget_show_all(pWindow);
    /* Affichage de la fenêtre */
    gtk_widget_show(pWindow);

    /* Demarrage de la boucle evenementielle */
    gtk_main();

}
