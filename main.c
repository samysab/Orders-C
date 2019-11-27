#include <stdlib.h>
#include <gtk/gtk.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include "menuWindow.c"
#include "launchWindow.c"
#include "orderSummary.c"
#include "adminLogIn.c"

void firstWindow();
void Windowscommande();
void orderWindow();
void adminLoginWindow();

int main(int argc,char **argv)
{
    gtk_init(&argc,&argv);

    adminLoginWindow();
    return EXIT_SUCCESS;
}
