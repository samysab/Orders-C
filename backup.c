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
    gchar* sUtf8;
    GtkWidget *pHBox;
    GtkWidget *pButton;

    gtk_init(&argc,&argv);


        /* Création de la fenêtre */
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        // Ajouter un titre à la fenetre
    gtk_window_set_title(GTK_WINDOW(pWindow), "StockInfo");
        //Initialise la taille des fenetres par défaut
    gtk_window_set_default_size(GTK_WINDOW(pWindow),320, 200);
    gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);


   /* Création du label*/
    pLabel = gtk_label_new(NULL);

    //-1 permet de laisser la lib calculer la longueur de la chaine
    sUtf8 = g_locale_from_utf8("<b>Stock actuel</b>",-1, NULL,NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
    g_free(sUtf8);
    gtk_label_set_justify(GTK_LABEL(pLabel), GTK_JUSTIFY_CENTER);

    // Craeation de la box horizontale
    pHBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pHBox);
    pButton = gtk_button_new_with_label("BOUTON");
    gtk_box_pack_end(GTK_BOX(pHBox), pButton, FALSE, FALSE, 0);


    /* Connexion du signal "destroy" */
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);


    //Permet d'afficher toute les infos sur la fenetre
    gtk_container_add(GTK_CONTAINER(pWindow), pLabel);
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
