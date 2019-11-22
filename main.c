#include <stdlib.h>
#include <gtk/gtk.h>
#include "menuWindow.c"
#include "launchWindow.c"
#include "orderSummary.c"

void firstWindow(GtkWidget *widget);
void Windowscommande(GtkWidget *widget);
void orderWindow(GtkWidget *widget);


int main(int argc,char **argv)
{
    gtk_init(&argc,&argv);

    firstWindow(GTK_WINDOW_TOPLEVEL);

    return EXIT_SUCCESS;
}
