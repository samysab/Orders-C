
void newOrder(){
//Déclaration de l'objet de type MYSQL
    MYSQL mysql;
    //Initialisation de MySQL
    mysql_init(&mysql);
    //Options de connexion
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    //Si la connexion réussie...
    if(mysql_real_connect(&mysql,"localhost", "root", "", "burgerc_db", 0, NULL, 0))
    {
        mysql_query(&mysql, "INSERT INTO orders(orderStatus) VALUES('En attente')");

        //Fermeture de MySQL
        mysql_close(&mysql);
    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }
}
