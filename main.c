#include <stdlib.h>
#include <gtk/gtk.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include "menuWindow.c"
#include "launchWindow.c"
#include "orderSummary.c"
#include "adminLogIn.c"

void firstWindow(GtkWidget *widget);
void Windowscommande(GtkWidget *widget);
void orderWindow(GtkWidget *widget);
void adminLoginWindow(GtkWidget *widget);

int main(int argc,char **argv)
{
    gtk_init(&argc,&argv);

    Windowscommande(GTK_WINDOW_TOPLEVEL);
    return EXIT_SUCCESS;
}
