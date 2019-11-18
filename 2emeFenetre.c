#include <stdlib.h>
#include <gtk/gtk.h>
#include <winsock.h>
#include <MYSQL/mysql.h>

void OnDestroy(GtkWidget *pWidget, gpointer pData);
void Windowscommande(GtkWidget *widget);


int main(int argc,char **argv)
{

    gtk_init(&argc,&argv);

    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    if(mysql_real_connect(&mysql,"127.0.0.1","root","","c",0,NULL,0))
    {
        //Requête qui sélectionne tout dans ma table ma_table
        mysql_query(&mysql, "SELECT * FROM ma_table");

        //Déclaration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;

        unsigned int i = 0;
        unsigned int num_champs = 0;

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
               printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
        //Libération du jeu de résultat
        mysql_free_result(result);
        mysql_close(&mysql);
    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion a la BDD!");
    }
    Windowscommande(GTK_WINDOW_TOPLEVEL);
    return EXIT_SUCCESS;
}

void Windowscommande(GtkWidget *widget){

       /* Déclaration des widget */
    GtkWidget *pWindow;
    GtkWidget *pLabelOrdersC;
    GtkWidget *pLabelOrders;
    gchar* sUtf8;
    GtkWidget *pButton[5];
    GtkWidget *pTable;



            /* Création de la fenêtre */
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        // Ajouter un titre à la fenetre
    gtk_window_set_title(GTK_WINDOW(pWindow), "MENU - Orders C");
        //Initialise la taille des fenetres par défaut
    gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 800);
    gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

    pTable= gtk_table_new(7,6,TRUE);
    gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));

   /* Création du label Titre*/
    pLabelOrdersC = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("<b><u><span size=\"20\"><span font_family=\"Courier New\">C Orders</span></span></u></b>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelOrdersC), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabelOrdersC), GTK_JUSTIFY_CENTER);

   /* Création du label Panier*/
    pLabelOrders = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("<b><u><span font_family=\"Courier New\">Panier :</span></u></b>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelOrders), sUtf8);
    g_free(sUtf8);
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

    /* Connexion du signal "destroy" */
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);


    //Permet d'afficher toute les infos sur la fenetre
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelOrdersC);
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelOrders);




    gtk_widget_show_all(pWindow);
    /* Affichage de la fenêtre */
    gtk_widget_show(pWindow);

    /* Demarrage de la boucle evenementielle */
    gtk_main();

}

void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
    /* Arret de la boucle evenementielle */
    gtk_main_quit();
}
