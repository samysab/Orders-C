/*
* Fonction utilisee pour verifier si un element de liste est dans une autre
* Renvoie 1 si elle en trouve un 
* Renvoie 0 si elle en trouve pas
*/
int currentIsInRecap(char name[50], sum_t *list) {
	sum_t *list_current = list;

	while (list_current != NULL) {
		if (!strcmp(list_current->name, name))
			return 1;

		list_current = list_current->next;
	}

	return 0;
}


/*
* Fonction qui 
*
*/
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
	int nb_de_fois_produit_dans_liste;

	while (current != NULL) {
		nb_de_fois_produit_dans_liste = 0;

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
				nb_de_fois_produit_dans_liste++;
			}

			tmp = tmp->next;
		}
		// decommenter pour afficher le recap dans la fonction
		// printf("%d %s(id:%d) (price:%d)\n", nb_de_fois_produit_dans_liste, current->name, current->id, current->price);

		addRecap(&recap, current->name, nb_de_fois_produit_dans_liste, current->id, current->price);

		current = current->next;
	}

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
		printf("Erreur bdd insertOrder");
		return 0;
	}

}

int insertOrder(sum_t *head, char comment[255]) {
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");


	printf("Recapitulatif :\n");
	sum_t* curr = head;
	while (curr != NULL) {
		printf("INFOS : name(%s), id(%d), nb(%d), price(%d)\n", curr->name, curr->id, curr->nb, curr->price);

		curr = curr->next;
	}






	printf("Commentaire : %s\n", comment);

	if (mysql_real_connect(&mysql, "localhost", "root", "", "burgerc_db", 0, NULL, 0)) {
		int rowCount;

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		char the_date[12];
		sprintf(the_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1,	tm.tm_mday);

		// insert orders
		char query[255];
		sprintf(query, "INSERT INTO orders(orderComment, orderTime) VALUES (\"%s\", \"%s\")", comment, the_date);
		mysql_query(&mysql, query);

		rowCount = mysql_affected_rows(&mysql);
		printf("%d ligne affectee\n", rowCount);



		// on recupere l'order id;
		MYSQL_ROW row;
		MYSQL_RES *result = NULL;

		mysql_query(&mysql, "SELECT MAX(orderId) FROM orders");

		result = mysql_use_result(&mysql);
		row = mysql_fetch_row(result);

		// on recupere le dernier id pour le mettre dans une autre table
		int orderId;
		orderId = atoi(row[0]);


		// insert in orders
		sum_t *current = head;
		int i;

		char** config = configuration();

		pdgPage(config, current, comment);

		while (current != NULL) {
			for (i = 0; i < current->nb; i++) {

				insertInOrders(current->id, orderId, current->name);
			}

			current = current->next;
		}

		// mysql_close(&mysql);

		printf("fin,\n");

	} else {
		printf("Erreur lors de l'ajout de la commande a la base de donnees\n");
		return 0;
	}


	return 1;

}


void confirmOrder (GtkWidget *btn, void* infos[5]) {

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


	if (insertOrder((sum_t*)infos[1], buf)) {
		printf("Tout sest bien passe, fin de demonstration\n\n");
		// on ferme orderSummary
		gtk_widget_destroy((GtkWidget*)infos[3]);
		// on ferme menuWindow
		gtk_widget_destroy((GtkWidget*)infos[4]);
		// return;
	} else {
		printf("Erreurrrr");
	}

	gtk_widget_destroy(dialog);

}



