void draw_line_vertical_price(HPDF_Page page, float x, float y);
void draw_line_vertical(HPDF_Page page, float x, float y);
void draw_line_horizontal_price(HPDF_Page page, float x, float y);
void draw_line_horizontal(HPDF_Page page, float x, float y);
void draw_image (HPDF_Doc pdf, const char *filename, float x, float y);
void pdgPage(char** tableau2d, sum_t *head);

jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler  (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}
//char** tableau2d
void pdgPage(char** tableau2d, sum_t *head){
    const char* page_title = "Burger C - Bon de commande";

    HPDF_Doc  pdf;
    HPDF_Font font;
    HPDF_Page page;
    char fname[256] = "";


    float tw;
    // char pdfName[20] = "";

    /*
    * Tableau2d correpond à toute les infos récupperer dans le fichier de configuration
    * tableau2d[0] = nom du fichier PDF
    */

    strcpy(fname,tableau2d[0]);
    if(fname[strlen(fname)-1] == '\n'){
        fname[strlen(fname)-1] = '\0';
    }
    strcat (fname, ".pdf");




    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
    }

    /* create default-font */
    font = HPDF_GetFont (pdf, "Helvetica", NULL);

    /* add a new page object. */
    page = HPDF_AddPage (pdf);

    /* print the title of the page (with positioning center). */
    HPDF_Page_SetFontAndSize (page, font, 24);
    tw = HPDF_Page_TextWidth (page, page_title);
    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, (HPDF_Page_GetWidth(page) - tw) / 2,
                HPDF_Page_GetHeight (page) - 50);
    HPDF_Page_ShowText (page, page_title);
    HPDF_Page_EndText (page);

    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 13);
    HPDF_Page_MoveTextPos (page, 300, HPDF_Page_GetHeight (page) - 120);
    HPDF_Page_ShowText (page, "Etat de la commande : En cours de preparation ");
    HPDF_Page_EndText (page);

    HPDF_Page_SetFontAndSize (page, font, 10);

    /*
    =====================================
    ======= Tableau des commandes =======
    =====================================
    */
    int space = 35;
    int yArray = 700;

    // Lignes du tableau
    for(int i = 0; i<8; i++){
        HPDF_Page_SetLineWidth (page, 0);
        draw_line_horizontal (page, 20, yArray );
        yArray -= space;
    }
    HPDF_Page_SetLineWidth (page, 0);
    draw_line_vertical(page, 20, 700 );
    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 13);
    HPDF_Page_MoveTextPos (page, 220, HPDF_Page_GetHeight (page) - 176);
    HPDF_Page_ShowText (page, "Articles ");
    HPDF_Page_EndText (page);

    int posY = 210;
    sum_t *current = head;
    char totalOrder[10];
    char price[10];
    char number[10];
    int sumPrice;
    int total = 0;

    while (current != NULL) {
    sprintf(number,"%d", current->nb);
    sumPrice = current->price * current->nb;
    sprintf(price,"%d", sumPrice);


        HPDF_Page_BeginText (page);
        HPDF_Page_SetFontAndSize (page, font, 13);
        HPDF_Page_MoveTextPos (page, 220, HPDF_Page_GetHeight (page) - posY);
        HPDF_Page_ShowText (page, current->name);
        HPDF_Page_EndText (page);
        HPDF_Page_BeginText (page);
        HPDF_Page_SetFontAndSize (page, font, 13);
        HPDF_Page_MoveTextPos (page, 465, HPDF_Page_GetHeight (page) - posY);
        HPDF_Page_ShowText (page, number);
        HPDF_Page_EndText (page);
        HPDF_Page_BeginText (page);
        HPDF_Page_SetFontAndSize (page, font, 13);
        HPDF_Page_MoveTextPos (page, 515, HPDF_Page_GetHeight (page) - posY);
        HPDF_Page_ShowText (page, price);
        HPDF_Page_EndText (page);
        total += sumPrice;
        current = current->next;
        posY+= 35;
    }
    sprintf(totalOrder,"%d", total);

    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 13);
    HPDF_Page_MoveTextPos (page, 515, HPDF_Page_GetHeight (page) - 425);
    HPDF_Page_ShowText (page, totalOrder);
    HPDF_Page_EndText (page);

    HPDF_Page_SetLineWidth (page, 0);
    draw_line_vertical(page, 450, 700 );
    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 13);
    HPDF_Page_MoveTextPos (page, 450, HPDF_Page_GetHeight (page) - 176);
    HPDF_Page_ShowText (page, "Quantite ");
    HPDF_Page_EndText (page);


    HPDF_Page_SetLineWidth (page, 0);
    draw_line_vertical(page, 500, 700 );
    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 13);
    HPDF_Page_MoveTextPos (page, 510, HPDF_Page_GetHeight (page) - 176);
    HPDF_Page_ShowText (page, "Prix ");
    HPDF_Page_EndText (page);

    HPDF_Page_SetLineWidth (page, 0);
    draw_line_vertical(page, 550, 700 );

    //carre pour le total
    HPDF_Page_SetLineWidth (page, 0);
    draw_line_horizontal_price (page, 500, 420 );
    HPDF_Page_SetLineWidth (page, 0);
    draw_line_vertical_price(page, 500, 455 );
    HPDF_Page_SetLineWidth (page, 0);
    draw_line_vertical_price(page, 550, 455 );
    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 13);
    HPDF_Page_MoveTextPos (page, 460, HPDF_Page_GetHeight (page) - 425);
    HPDF_Page_ShowText (page, "Total ");
    HPDF_Page_EndText (page);

        HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, font, 13);
    HPDF_Page_MoveTextPos (page, 20, HPDF_Page_GetHeight (page) - 470);
    HPDF_Page_ShowText (page, "Commentaire :");
    HPDF_Page_EndText (page);
    draw_image (pdf, "tampon-paye-png.png", 400, HPDF_Page_GetHeight (page) - 550);


    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

}

void draw_line_horizontal(HPDF_Page page, float x, float y){
    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, x, y - 10);
    HPDF_Page_EndText (page);

    HPDF_Page_MoveTo (page, x, y - 15);
    HPDF_Page_LineTo (page, x + 531, y - 15);
    HPDF_Page_Stroke (page);
}
void draw_line_horizontal_price(HPDF_Page page, float x, float y){
    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, x, y - 10);
    HPDF_Page_EndText (page);

    HPDF_Page_MoveTo (page, x, y - 15);
    HPDF_Page_LineTo (page, x + 50, y - 15);
    HPDF_Page_Stroke (page);
}

void draw_line_vertical(HPDF_Page page, float x, float y){
    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, x, y - 10);
    HPDF_Page_EndText (page);

    HPDF_Page_MoveTo (page, x, y - 15);
    HPDF_Page_LineTo (page, x, y - 260);
    HPDF_Page_Stroke (page);
}
void draw_line_vertical_price(HPDF_Page page, float x, float y){
    HPDF_Page_BeginText (page);
    HPDF_Page_MoveTextPos (page, x, y - 10);
    HPDF_Page_EndText (page);

    HPDF_Page_MoveTo (page, x, y - 15);
    HPDF_Page_LineTo (page, x, y - 50);
    HPDF_Page_Stroke (page);
}

void draw_image (HPDF_Doc pdf, const char *filename, float x, float y){
    #ifdef __WIN32__
        const char* FILE_SEPARATOR = "\\";
    #else
        const char* FILE_SEPARATOR = "/";
    #endif
    char filename1[255];

    HPDF_Page page = HPDF_GetCurrentPage (pdf);
    HPDF_Image image;

    strcpy(filename1, "pngsuite");
    strcat(filename1, FILE_SEPARATOR);
    strcat(filename1, filename);

    image = HPDF_LoadPngImageFromFile (pdf, filename1);

    /* Draw image to the canvas. */
    HPDF_Page_DrawImage (page, image, x, y, HPDF_Image_GetWidth (image),
    HPDF_Image_GetHeight (image));

}
