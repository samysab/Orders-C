#include <stdlib.h>
#include <gtk/gtk.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include "menuWindow.c"
#include "launchWindow.c"
#include "orderSummary.c"
#include "adminLogIn.c"
#include "functions/addToCard.c"
#include "functions/newOrder.c"
#include "functions/fn_menuWindows.c"

void firstWindow();
void Windowscommande();
void orderWindow();
void adminLoginWindow();
void newOrder();

int main(int argc,char **argv)
{

    gtk_init(&argc,&argv);
    Windowscommande();
    // newOrder();
    // A la fin du programme, l'id de orderId s'incremmente autmatiquement
    return EXIT_SUCCESS;
}
