#define TAILLE_MAX 1000
void configuration();


void configuration(){
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = "";
    int* str;
    int i = 0;
    int nbLine = 3;
   // char temp[5][20];


    char ** tableau2d = malloc(nbLine*sizeof(char));

    for(int i = 0; i < nbLine; ++i){
        tableau2d[i] = malloc(20*sizeof(char));
    }


    fichier = fopen("configuration.txt", "r");
ffe
    if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            //printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
            str = strstr(chaine, "=");
            if(str!= NULL){
                 //printf(" @ : %p \n", p);
                    strcpy(tableau2d[i], str);
                    //printf("%s", temp);
                    i ++;
            }
        }

        char searchPV[5] = ";";
        char searchSpace[5] = "= ";
        char *ptr;

       // printf("***Parametres isole***\n\n");
        for(int i =0; i< nbLine; i ++){
            ptr = tableau2d[i];

            ptr = strstr(ptr,searchSpace);
            while((ptr=strstr(ptr,searchSpace))!=NULL){

            strcpy(ptr,ptr+strlen(searchSpace));
            }

            ptr = tableau2d[i];

            ptr = strstr(ptr,searchPV);
            while((ptr=strstr(ptr,searchPV))!=NULL){

                strcpy(ptr,ptr+strlen(searchPV));
            }
            //printf("%s", tableau2d[i]);
        }
        fclose(fichier);
    }
    //pdgPage(tableau2d);
        //Windowscommande(panier, tableau2d);
    //firstWindow(tableau2d);
}