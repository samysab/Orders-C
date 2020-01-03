#include <stdlib.h>
#include <gtk/gtk.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <setjmp.h>
#include "hpdf.h"
#include "structures.h"
#include "functions/addToCard.c"
#include "functions/newOrder.c"
#include "functions/fn_menuWindows.c"
#include "functions/config.c"
#include "functions/exportPdf.c"
#include "menuWindow.c"
#include "launchWindow.c"
#include "orderSummary.c"
#include "adminLogIn.c"


void firstWindow();
void Windowscommande(product_t*);
void adminLoginWindow();
void newOrder();
// void orderWindow(int**);
char** configuration();

int main(int argc,char **argv) {

    gtk_init(&argc,&argv);

	product_t *panier = NULL;
	panier = malloc(sizeof(product_t));
	panier->id = 1;
	strcpy(panier->name, "Premier Element Panier");
	strcpy(panier->image_path, "./sample.png");
	panier->price = 0;
	panier->next = NULL;

	Windowscommande(panier);
    // orderWindow(&abc);
    // newOrder();
    // A la fin du programme, l'id de orderId s'incremmente autmatiquement
    return EXIT_SUCCESS;
}
