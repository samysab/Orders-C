#include <time.h>

typedef struct sum_node {
	char name[50];
	int id;
	int price;
	int nb;
	struct sum_node *next;
} sum_t;

int currentIsInRecap(char name[50], sum_t *list) {
	sum_t *list_current = list;

	while (list_current != NULL) {
		if (!strcmp(list_current->name, name))
			return 1;

		list_current = list_current->next;
	}

	return 0;
}

void addRecap(sum_t **head, char name[20], int nb, int id, int price) {
	if (*head == NULL) {
		*head = malloc(sizeof(sum_t));
		strcpy((*head)->name, name);
		(*head)->nb = nb;
		(*head)->id = id;
		(*head)->price = price;
		(*head)->next = NULL;
		return;
	}

	sum_t *current = *head;

	while (current->next != NULL)
		current = current->next;

	current->next = malloc(sizeof(sum_t));
	strcpy(current->next->name, name);
	current->next->nb = nb;
	current->next->id = id;
	current->next->price = price;
	current->next->next = NULL;
}


sum_t* sum(product_t *head) {

	product_t *current = head;
	sum_t *recap = NULL;
	int i;

	while (current != NULL) {
		i = 0;

		// si le name du maillon qu'on analyse est deja dans notre liste
		// recapitulative, bah on a pas besoin de recompter ses occurrences
		if (currentIsInRecap(current->name, recap)) {
			current = current->next;
			continue;
		}

		// pour chaque noeud de head,
		// on re-parcourt la liste pour trouver les occurrences,
		// tmp est la variable itérée dans notre 2e parcours
		product_t *tmp = head;
		while (tmp != NULL) {
			if (!strcmp(tmp->name, current->name)) {
				// si on a trouvé une occurrence, on incrémente le compteur pour chaque noeud (chaque "current")
				i++;
			}

			tmp = tmp->next;
		}
		// decommenter pour afficher le recap dans la fonction
		printf("%d %s(id:%d) (price:%d)\n", i, current->name, current->id, current->price);

		addRecap(&recap, current->name, i, current->id, current->price);


		current = current->next;
	}

	// printf("dernier : %s\n", current->name);

	return recap;


}


int insertInOrders(int productId, int orderId, char name[50]) {
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if (mysql_real_connect(&mysql, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {
		int rowCount;

		char query[255];
		sprintf(query, "INSERT INTO inorders(Products_productId, Orders_orderId) VALUES (%d, %d)", productId, orderId);
		mysql_query(&mysql, query);
		rowCount = mysql_affected_rows(&mysql);
		printf("%d ligne affectee pour %s\n", rowCount, name);

		return 1;
	} else {
		printf("errrrrrrrrrrr");
		return 0;
	}

}

int insertOrder(sum_t *head, char comment[255]) {
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");


	printf("RECAAAAAAAAAP\n");
	sum_t* curr = head;
	while (curr != NULL) {
		printf("INFOS : name(%s), id(%d), nb(%d), price(%d)\n", curr->name, curr->id, curr->nb, curr->price);

		curr = curr->next;
	}






	printf("alors : %s\n", comment);

	if (mysql_real_connect(&mysql, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {
		int rowCount;

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		char the_date[12];
		sprintf(the_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1,	tm.tm_mday);

		// insert orders
		char query[255];
		sprintf(query, "INSERT INTO orders(orderComment, orderTime) VALUES (\"%s\", \"%s\")", comment, the_date);
		printf("query : %s\n", query);
		mysql_query(&mysql, query);

		rowCount = mysql_affected_rows(&mysql);
		printf("%d ligne affectee\n", rowCount);



		// on recupere l'order id;
		MYSQL_ROW row;
		MYSQL_RES *result = NULL;

		mysql_query(&mysql, "SELECT MAX(orderId) FROM orders");

		result = mysql_use_result(&mysql);
		row = mysql_fetch_row(result);

		int orderId;
		orderId = atoi(row[0]);
		// orderId = 55;
		printf("last id : %d\n", orderId);

		// insert in orders
		sum_t *current = head;
		int i;

		//pdgPage(current);
		configuration(current);

		while (current != NULL) {
			for (i = 0; i < current->nb; i++) {

				// WTF
				// printf("infos : %s %d \n", current->name, current->id);
				// strcpy(query, "");
				// sprintf(query, "INSERT INTO inorders(Products_productId, Orders_orderId) VALUES (%d, %d)", current->id, orderId);

				// mysql_query(&mysql, query);

				// rowCount = mysql_affected_rows(&mysql);
				// printf("%s a ete ajoute %d fois - %d ligne affectee\n", current->name, current->nb, rowCount);

				insertInOrders(current->id, orderId, current->name);
			}

			current = current->next;
		}

		// mysql_close(&mysql);

		printf("fin");

	} else {
		printf("Erreur lors de l'ajout de la commande a la base de donnees\n");
		return 0;
	}


	return 1;

}


void confirmOrder (GtkWidget *btn, void* infos[3]) {

	GtkWidget* view = (GtkWidget*)infos[2];
	GtkTextBuffer* text_buffer=0;
	GtkTextIter start;
	GtkTextIter end;
	gchar* buf=0;




	//On récupère le buffer
	text_buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	//On récupère l'origine du buffer
	gtk_text_buffer_get_start_iter(text_buffer,&start);
	//On récupère la fin du buffer
	gtk_text_buffer_get_end_iter(text_buffer,&end);

	//On copie le contenu du buffer dans une variable
	buf=gtk_text_buffer_get_text(text_buffer,&start, &end,TRUE);


	GtkWidget *dialog = NULL;

	dialog = gtk_dialog_new_with_buttons("Terminer la commande", GTK_WINDOW((GtkWidget*)infos[0]), GTK_DIALOG_MODAL, "_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL);

	// GtkWidget* label_str = gtk_label_new("Confirmer votre commande ?\nUne facture en pdf sera genere");
	// gtk_dialog_add_action_widget(GTK_DIALOG(dialog), label_str, 5);

	gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);

	gtk_dialog_run (GTK_DIALOG (dialog));


	if (insertOrder((sum_t*)infos[1], buf))
		printf("Tout sest bien passe");
	else
		printf("Erreurrrr");

	gtk_widget_destroy (dialog);

}

void orderWindow(GtkWidget* btn, gpointer panier){


	printf("order ##\n");
	product_t *head = (product_t*)panier;
	browseList(head);

	// pour l'instant je mets head->next pour skip le 1er
	// mais au prochain push je ferai en sorte que ce soit clean
	// sum_t *list_pointer = sum(head->next);
	// while (list_pointer != NULL) {
	// 	printf("%s : %d\n", list_pointer->name, list_pointer->nb);
	// 	list_pointer = list_pointer->next;
	// }


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

	void *confirmArray[3];
	confirmArray[0] = pWindow;
	confirmArray[1] = list_pointer;
	confirmArray[2] = text_view;
	// Connexion du signal "destroy"
	g_signal_connect (G_OBJECT (pButton[0]), "clicked", G_CALLBACK (confirmOrder), (gpointer) (confirmArray) );
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

	while (list_pointer != NULL) {

		printf("%s : %d\n", list_pointer->name, list_pointer->nb);

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

	//Permet d'afficher toute les infos sur la fenetre
	// gtk_container_add(GTK_CONTAINER(pWindow), pLabelRecapitulatif);
	// gtk_container_add(GTK_CONTAINER(pWindow), pLabelCommentary);




	// Affichage de la fenêtre
	gtk_widget_show_all(pWindow);

	// Demarrage de la boucle evenementielle
	gtk_main();

}
