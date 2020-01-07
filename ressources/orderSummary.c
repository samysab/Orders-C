#include <time.h>

void orderWindow(GtkWidget* btn, void** orderVarsArray){

	product_t *head = (product_t*)orderVarsArray[0];
	browseList(head);

	// Déclaration des widget
	GtkWidget *pWindow;
	GtkWidget *pLabelRecapitulatif;
	GtkWidget *recapScrolledWindow;
	GtkWidget *pLabelCommentary;
	gchar* sUtf8;
	GtkWidget *pTable;
	GtkWidget* text_view;
	GtkWidget *pButton[2];

	// Création de la fenêtre
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		// Ajouter un titre à la fenetre
	gtk_window_set_title(GTK_WINDOW(pWindow), "Recapitulatif de votre commande - Burger C");
		//Initialise la taille des fenetres par défaut
	gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 400);
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

	pTable= gtk_table_new(5,4,TRUE);
	gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));

	// Création du label
	pLabelRecapitulatif = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\">Votre Recapitulatif </span></u></b>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelRecapitulatif), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelRecapitulatif), GTK_JUSTIFY_CENTER);

	recapScrolledWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(recapScrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

	// Création du label
	pLabelCommentary = gtk_label_new(NULL);
	sUtf8 = g_locale_from_utf8("<span size=\"15\">Un commentaire ?</span>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
	gtk_label_set_markup(GTK_LABEL(pLabelCommentary), sUtf8);
	g_free(sUtf8);
	gtk_label_set_justify(GTK_LABEL(pLabelCommentary), GTK_JUSTIFY_CENTER);

	// Creation du GtkEntry
	text_view = gtk_text_view_new();
	pButton[0] = gtk_button_new_with_label("Terminer la commande");

	gtk_table_attach(GTK_TABLE(pTable), pLabelRecapitulatif, 0, 2, 0, 1, GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), recapScrolledWindow, 0, 4, 1, 2, GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pLabelCommentary, 0, 2, 2, 3, GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), text_view, 0, 4, 3, 4, GTK_EXPAND| GTK_FILL ,  GTK_EXPAND | GTK_FILL, 0,0);
	gtk_table_attach(GTK_TABLE(pTable), pButton[0], 3, 4, 4, 5, GTK_EXPAND,  GTK_EXPAND  , 0,0);

	int row_start = 0;
	int row_end = 1;
	int col_start = 0;
	int	col_end = 1;
	GtkWidget* recapTable = gtk_table_new(3, 3, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(recapTable), 20);
	gtk_table_set_col_spacings(GTK_TABLE(recapTable), 20);


	GtkWidget* recap_label;
	sum_t *list_pointer = sum(head->next);

	void** confirmArray = malloc(sizeof(void*)*5);
	confirmArray[0] = pWindow;
	confirmArray[1] = list_pointer;
	confirmArray[2] = text_view;
	confirmArray[3] = pWindow;
	confirmArray[4] = orderVarsArray[1];

	g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(confirmOrder), confirmArray );
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

	while (list_pointer != NULL) {

		// printf("%s : %d\n", list_pointer->name, list_pointer->nb);

		char recap_str[50];
		sprintf(recap_str, "%d x %s", list_pointer->nb, list_pointer->name);
		recap_label = gtk_label_new(recap_str);

		gtk_table_attach(GTK_TABLE(recapTable), recap_label, row_start, row_end, col_start, col_end, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

		row_start += 1;
		row_end += 1;

		if (row_start == 2) {
			row_start = 0;
			row_end = 1;

			col_start += 1;
			col_end = col_start + 1;
		}

		list_pointer = list_pointer->next;
	}

	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(recapScrolledWindow), recapTable);

	gtk_widget_show_all(pWindow);

	gtk_main();

}
