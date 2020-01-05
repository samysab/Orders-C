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

#include "structures.h"
#include "prototypes.h"

#include "functions/config.c"
#include "functions/fn_menuWindows.c"
#include "functions/fn_orderSummary.c"
#include "functions/exportPdf.c"

#include "menuWindow.c"
#include "orderSummary.c"
#include "adminLogIn.c"
#include "firstWindow.c"


int main(int argc,char **argv) {

	gtk_init(&argc,&argv);

	firstWindow();

	return EXIT_SUCCESS;
}
