#include <stdlib.h>
#include <gtk/gtk.h>

#define EXEMPLE_1 0

void OnDestroy(GtkWidget *pWidget, gpointer pData);
void addBtn(GtkWidget *pWindow, gint iExemple);

int main(int argc,char **argv)
{
    /* Déclaration des widget */
    GtkWidget *pWindow;
    GtkWidget *pLabel;
    GtkWidget *pLabelQuantiteProduit;
    GtkWidget *pLabelPrixProduit;
    GtkWidget* pLabelNomProduit;
    GtkWidget* pLabelReference;
    GtkWidget* pLabelDescription;
    gchar* sUtf8;
    GtkWidget *pButton[3];
    GtkWidget *pTable;

    gtk_init(&argc,&argv);


        /* Création de la fenêtre */
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        // Ajouter un titre à la fenetre
    gtk_window_set_title(GTK_WINDOW(pWindow), "StockInfo");
        //Initialise la taille des fenetres par défaut
    gtk_window_set_default_size(GTK_WINDOW(pWindow),500, 400);
    gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);

    pTable= gtk_table_new(8,6,TRUE);
    gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));

   /* Création du label*/
    pLabel = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("<b>Stock actuel</b>",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabel), GTK_JUSTIFY_RIGHT);


    pLabelQuantiteProduit = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("Quantite",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelQuantiteProduit), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabelQuantiteProduit), GTK_JUSTIFY_CENTER);

    pLabelNomProduit = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("Nom",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelNomProduit), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabelNomProduit), GTK_JUSTIFY_CENTER);

    pLabelPrixProduit = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("Prix",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelPrixProduit), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabelPrixProduit), GTK_JUSTIFY_CENTER);

    pLabelReference = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("Reference",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelReference), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabelReference), GTK_JUSTIFY_CENTER);

    pLabelDescription = gtk_label_new(NULL);
    sUtf8 = g_locale_from_utf8("Description",-1, NULL,NULL, NULL);     //-1 permet de laisser la lib calculer la longueur de la chaine
    gtk_label_set_markup(GTK_LABEL(pLabelDescription), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabelDescription), GTK_JUSTIFY_CENTER);


    pButton[0] = gtk_button_new_with_label("Valider");
    pButton[1] = gtk_button_new_with_label("Supprimer");
    pButton[2] = gtk_button_new_with_label("Nouveau produit");

    gtk_table_attach(GTK_TABLE(pTable), pButton[0], 4, 5, 7, 8, GTK_EXPAND | GTK_FILL , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pButton[1], 3, 4, 7, 8, GTK_EXPAND | GTK_FILL , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pButton[2], 2, 3, 7, 8, GTK_EXPAND | GTK_FILL , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pLabel, 2, 4, 0, 1,GTK_EXPAND| GTK_FILL , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pLabelNomProduit, 0, 1, 1, 2,GTK_EXPAND , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pLabelPrixProduit, 0, 1, 2, 3,GTK_EXPAND , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pLabelQuantiteProduit, 0, 1, 3, 4,GTK_EXPAND , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pLabelReference, 0, 1, 4, 5,GTK_EXPAND , GTK_EXPAND, 0,0);
    gtk_table_attach(GTK_TABLE(pTable), pLabelDescription, 0, 1, 5, 6,GTK_EXPAND , GTK_EXPAND, 0,0);



    /* Connexion du signal "destroy" */
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);


    //Permet d'afficher toute les infos sur la fenetre
    gtk_container_add(GTK_CONTAINER(pWindow), pLabel);
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelQuantiteProduit);
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelPrixProduit);
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelNomProduit);
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelReference);
    gtk_container_add(GTK_CONTAINER(pWindow), pLabelDescription);



    gtk_widget_show_all(pWindow);
    /* Affichage de la fenêtre */
    gtk_widget_show(pWindow);

    /* Demarrage de la boucle evenementielle */
    gtk_main();

    return EXIT_SUCCESS;
}



void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
    /* Arret de la boucle evenementielle */
    gtk_main_quit();
}
