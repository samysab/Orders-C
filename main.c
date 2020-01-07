/*
* Application Burger C - Borne de commande
* Developped by
*	Samy HAMED E SABERI
*	Narek KHATCHATRIAN
*
* From November 8 th 2019 to January 6 th 2020
*
* Burger C 2019 - 2020 ©
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <winsock.h>

#include <MYSQL/mysql.h>
#include <setjmp.h>
#include "hpdf.h"

#include "ressources/structures.h"
#include "ressources/prototypes.h"

#include "ressources/functions/config.c"
#include "ressources/functions/fn_menuWindows.c"
#include "ressources/functions/fn_orderSummary.c"
#include "ressources/functions/exportPdf.c"

#include "ressources/menuWindow.c"
#include "ressources/orderSummary.c"
#include "ressources/adminLogIn.c"
#include "ressources/firstWindow.c"


int main(int argc,char **argv) {

	gtk_init(&argc,&argv);

	firstWindow();

	return EXIT_SUCCESS;
}
