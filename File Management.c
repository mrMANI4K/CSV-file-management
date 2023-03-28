#include <stdio.h>                          // CUDENNEC Evann
#include <stdlib.h>                         // PETIT Quentin
#include <string.h>                         // SOUCHERE Jules
#include <ctype.h>
#include <strings.h>
#define MAXcli 800


int i, j,choice, choice2, choice3,  end;                     // on définit les variables utiles
char espace=' ', givenName[31], givenPrenom[31];                                                              
const char separators[] = ",";                              // on définit le caractère pour remplacer les virgules par des espaces



typedef struct clients {        // on défini un type de structure nommé "clients"

    char id[20];
    char prenom[20];
    char nom[20];
    char pays[20];
    char codeDep[20];
    char nbJour[20];
    char age[20];
    char nbPers[20];
} clients;


// l'initialisation permet de stocker dans la mémoire chacun des éléments du fichier csv
int initialisation(clients cli[MAXcli]) {       
    int ligne = 0, comptage = 0;
    FILE *csvread = fopen("database.csv", "r");
    if (csvread == NULL) {                                                  // ceci est une condition de sécurité au cas où il y a un problème avec le fichier "database.csv"
        printf("il y a eu un probleme lors de l'ouverture du fichier");     //
        exit(1);
    }
    char text[255];
    while(fgets(text,255, csvread) != NULL) {       //ici on recupère une ligne du fichier csv
        char *token = strtok(text, separators);     //grâce à strtok, on peu remplacer les virgules du csv en un caractère NULL permettant de sépararer ce qu'il y a entre les virgules
        while (token != NULL) {
            if (comptage == 0) {                    //ici on associe chacune des valeurs récupérées dans la section adéquate 
                strcpy(cli[ligne].id, token);
            } else if (comptage == 1) {
                strcpy(cli[ligne].prenom, token);
            } else if (comptage == 2) {
                strcpy(cli[ligne].nom, token);
            } else if (comptage == 3) {
                strcpy(cli[ligne].pays, token);
            } else if (comptage == 4) {
                strcpy(cli[ligne].codeDep, token);
            } else if (comptage == 5) {
                strcpy(cli[ligne].nbJour, token);
            } else if (comptage == 6) {
                strcpy(cli[ligne].age, token);
            } else if (comptage == 7) {
                strcpy(cli[ligne].nbPers, token);
            }
            token = strtok(NULL, separators);           // on récupère le token suivant et on recommence la boucle jusqu'a la fin de la ligne
            comptage++;
        }
        ligne++, comptage = 0;      //on effectue les démarche nécessaires et on retourne au début du while pour reprendre avec la prochaine ligne
    }
    fclose(csvread);            // on oublie pas de fermer le fichier après utilisation
    return ligne;
}



// la fonction affichage permet d'afficher toutes les valeurs de notre structure
void affichage (clients *cli, int tabsize) {             
    int i,j, ligne;

    for (ligne=0; ligne < tabsize; ligne++) {   // ici on affiche un à un les valeurs de chaque ligne de la structure via une boucle for durant le nombre de ligne du tableau
        printf(cli[ligne].id);                                         
        for (i=0;i<25-strlen(cli[ligne].id);i++) printf(&espace);       // cette ligne permet de faire des espaces adaptatifs afin de pouvoir afficher un tableau bien ordonné et droit dans l'invite de commmande/console
        printf(cli[ligne].prenom);
        for (i=0;i<25-strlen(cli[ligne].prenom);i++) printf(&espace);
        printf(cli[ligne].nom);
        for (i=0;i<25-strlen(cli[ligne].nom);i++) printf(&espace);
        printf(cli[ligne].pays);
        for (i=0;i<25-strlen(cli[ligne].pays);i++) printf(&espace);
        printf(cli[ligne].codeDep);
        for (i=0;i<25-strlen(cli[ligne].codeDep);i++) printf(&espace);
        printf(cli[ligne].nbJour);
        for (i=0;i<25-strlen(cli[ligne].nbJour);i++) printf(&espace);
        printf(cli[ligne].age);
        for (i=0;i<25-strlen(cli[ligne].age);i++) printf(&espace);
        printf(cli[ligne].nbPers);
        for (i=0;i<25-strlen(cli[ligne].nbPers);i++) printf(&espace);
        printf("\n\n");                
    }
}


//La fonction add sert à ajouter une entrée dans la base de donnée
void add(int tabsize) {
    int id2, codeDep2, nbJour2, age2, nbPers2;      // on initialise les variables nécessaires au bon fonctionnement de la fonction
    char prenom2[30], nom2[30], pays2[30];
    FILE * csva = fopen("database.csv","a");          //  on ouvre le csv en "add" pour ecrire à la suite sans effacer 
    if (csva == NULL) {                                                                                  // ceci est une condition de sécurité au cas où il y a un problème avec le fichier "database.csv"
        printf("il y a eu un probleme lors de l'ouverture du fichier");                                  //
        exit(1);
    }
    id2 = tabsize;                                      // dans toute cette partie on demande à l'utilisateur chaque valeurs afin qu'il les saisisse. 
    printf("prenom : ");                                //
    scanf("%s", prenom2);                               //
    printf("nom : ");                                   //
    scanf("%s", nom2);                                  //
    printf("pays : ");                                  //
    scanf("%s", pays2);                                 //
    printf("code de departement : ");                   //
    scanf("%d", &codeDep2);                             //
    printf("nombre de jours : ");                       //
    scanf("%d", &nbJour2);                              //
    printf("age : ");                                   //
    scanf("%d", &age2);                                 //
    printf("nombre de personnes : ");                   //
    scanf("%d", &nbPers2);                              //
    fprintf(csva, "%d,%s,%s,%s,%d,%d,%d,%d,\n", id2,prenom2,nom2,pays2,codeDep2,nbJour2,age2,nbPers2);           // on printf toutes les valeurs voulues et correspondantes
    printf("Client ajoute ! :)\n\n");
    fclose(csva);                           // on oublie pas de fermer le fichier apres utilisation
}


// La fonction del sert à supprimer une entrée choisie en fonction de l'id 
void del(int id, clients *cli, int tabsize) {
    FILE *csvFile = fopen("database.csv", "r");             // on ouvre en read
    FILE *csvwrite = fopen("database.txt", "w");            // on ouvre en write de manière simultanée et pour reset ou créer le fichier temporaire (ici .txt)
    if (csvFile == NULL) {                                                                                  
        printf("il y a eu un probleme lors de l'ouverture du fichier");                 
        exit(1);
    }
    if (csvwrite == NULL) {                                                                                  
        printf("il y a eu un probleme lors de l'ouverture du fichier");                 
        exit(1);
    }
    int count = 0, deleted = 0;
    char text[255];         // Initialisation d'une chaine de caractère qui va stocker le contenu d'une ligne du csv.
    id++ ;

    while(!feof(csvFile) && deleted == 0) {                                         //ceci est la partie tri. cela s'effectura tant que nous n'avons pas atteint la fin du fichier
        strcpy(text, "\0") ;
        fgets(text, 255, csvFile) ;
        if (!feof(csvFile)) {                                          // on écrit dans le fichier temporaire si la correspondance n'est pas trouvée. S'il y'a correspondance alors la personne ne sera pas marqué dans le fichier temp
            count++;
            deleted = 1;
            if (count != id) {
                fprintf(csvwrite, "%s", text);
                deleted = 0;
            }
        }
    }
    if (deleted == 1 && count < tabsize) {                                         //ceci est la partie tri. cela s'effectura tant que nous n'avons pas atteint la fin du fichier
        for (i = count; i < tabsize; i++) {
            fprintf(csvwrite, "%d,%s,%s,%s,%s,%s,%s,%s,\n", i-1,cli[i].prenom, cli[i].nom, cli[i].pays, cli[i].codeDep, cli[i].nbJour, cli[i].age, cli[i].nbPers);
        }
    }
    printf("\n\nsuppression effectuee avec succes !\n\n");
    fclose(csvFile);
    fclose(csvwrite);                   // on n'oublie pas de fermer les fichiers ouverts après leur utilisation
    remove("database.csv");                            //
    rename("database.txt", "database.csv");            // on procède ensuite au remplacement les fichiers
}


// La fonction search sert à rechercher une entrée dans la base de donnée grâce à une saisie clavier
void search(clients *cli, int tabsize, char search_name[30], char search_prenom[30]) {       //search_name est la variable où est contenu le nom à rechercher 
    int ligne, ind = 0, Oneline = 0;

    for (ligne=0; ligne<tabsize; ligne++) {
        if (strcasecmp(cli[ligne].nom, search_name) == 0 && strcasecmp(cli[ligne].prenom, search_prenom) == 0 || Oneline == 0) {                    // on compare le nom demandé et le nom en mémoire
            printf(cli[ligne].id);                                                         // si il y'a égalité, on peut donc afficher toute les valeurs correspondantes stockées en mémoire
            for (i=0;i<25-strlen(cli[ligne].id);i++) printf(&espace);
            printf(cli[ligne].prenom);
            for (i=0;i<25-strlen(cli[ligne].prenom);i++) printf(&espace);
            printf(cli[ligne].nom);
            for (i=0;i<25-strlen(cli[ligne].nom);i++) printf(&espace);
            printf(cli[ligne].pays);
            for (i=0;i<25-strlen(cli[ligne].pays);i++) printf(&espace);
            printf(cli[ligne].codeDep);
            for (i=0;i<25-strlen(cli[ligne].codeDep);i++) printf(&espace);
            printf(cli[ligne].nbJour);
            for (i=0;i<25-strlen(cli[ligne].nbJour);i++) printf(&espace);
            printf(cli[ligne].age);
            for (i=0;i<25-strlen(cli[ligne].age);i++) printf(&espace);
            printf(cli[ligne].nbPers);
            for (i=0;i<25-strlen(cli[ligne].nbPers);i++) printf(&espace);
            printf("\n");
            if (Oneline == 0) printf("\n");                                             //oneline est une variable de contrôle permettant d'arreter les comparaison si le resultat est trouvé. cela affiche donc seulement le premier resultat 
            Oneline++;  
        }
    }            
}


//ici se trouve la fonction permettant de trier par tri fusion la liste des clients contenue dans la ram selon le nom des clients 
void fusion_nom(clients *cli, int start, int middle, int end) {             
    int i, j, k;
    int n1 = middle - start + 1;
    int n2 = end - middle;

    clients left[MAXcli];
    clients right[MAXcli];

    for (i = 0; i < n1; i++) {
        left[i] = cli[start + i];
    }
    for (j = 0; j < n2; j++) {
        right[j] = cli[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2) {
        if (strcmp(left[i].nom, right[j].nom) <= 0) {
            cli[k] = left[i];
            i++;
        } else  {
            cli[k] = right[j];
            j++;
            
        }
        k++;
    }

    while (i < n1) {
        cli[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        cli[k] = right[j];
        j++;
        k++;
    }

}
void fusion_pays(clients *cli, int start, int middle, int end) {            // ici se trouve la fonction permettant de trier et fusionner la liste des clients contenue dans la ram selon le pays d'origine                   
    int i, j, k;                                                            // des clients
    int n1 = middle - start + 1;                                            //
    int n2 = end - middle;                                                  // on procède par séparer le tableau en deux et ensuite on compare grace à strcmp les valeurs une à une et on les replace dans 
                                                                            // le tableau principal

    clients left[MAXcli];
    clients right[MAXcli];

    for (i = 0; i < n1; i++) {
        left[i] = cli[start + i];
    }
    for (j = 0; j < n2; j++) {
        right[j] = cli[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2) {
        if (strcmp(left[i].pays, right[j].pays) <= 0) {
            cli[k] = left[i];
            i++;
        } else  {
            cli[k] = right[j];
            j++;
            
        }
        k++;
    }

    while (i < n1) {
        cli[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        cli[k] = right[j];
        j++;
        k++;
    }

}


// Cette fonction sert à mettre en ordre les étapes afin de réaliser un tri fusion... ici sur les nom des clients
void tri_fusion_nom(clients *cli, int start, int end) {             
    if (start < end) {
        int middle = (start + end) /2;
        fusion_nom(cli, start, middle, end);
        tri_fusion_nom(cli, start, middle);
        tri_fusion_nom(cli, middle + 1, end);
        fusion_nom(cli, start, middle, end);
    }

}


// la fonction tri fusion sert à mettre en ordre les étpaes afin de réaliser un tri fusion... ici sur le pays des clients
void tri_fusion_pays(clients *cli, int start, int end) {
    if (start < end) {
        int middle = (start + end) /2;
        fusion_pays(cli, start, middle, end);
        tri_fusion_pays(cli, start, middle);
        tri_fusion_pays(cli, middle + 1, end);
        fusion_pays(cli, start, middle, end);
    }

}

int main () {       //le main représente la partie menu du programme 

    clients cli[MAXcli];
    do {    
        
        int tabsize = initialisation(cli);      //on initialise notre structure et on recupère le nb de ligne dans tabsize
                                              
        end = 0;
        int choice;
        printf("\n\n\nQue voulez vous faire ? \n\n1 ~ Afficher la liste complete des clients\n\n2 ~ ajouter / supprimer un client\n\n3 ~ Rechercher un client par son nom et son prenom\n\n4 ~ Trier les donnees du tableau par nom des clients\n\n5 ~ Fermer le programme\n\n");
        scanf("%d", &choice);
        while(getchar() != '\n');                //cette ligne permet de ne pas avoir de problème si l'utilisateur entre une donnée non-attendue
        printf("\n\n\n");
        switch(choice) {          //un case-switch etait la meilleure des solutions afin d'avoir un menu à selection par entrée de valeur numérique 
            case 1 : affichage(cli, tabsize); break;               
            case 2 : printf("\n\n\n\nQue voulez-vous faire exactement ?\n\n1 ~ Ajouter un client\n\n2 ~ Supprimer un client\n\n3 ~ Revenir en arriere\n\n");
                     scanf("%d", &choice2);
                     if (choice2 == 1) {
                        add(tabsize);
                     }
                     else if (choice2 == 2) {
                     int givenID ;
                     printf("\n\n\nquel est l'ID de la personne que vous voulez supprimer ?\n\n");
                     scanf("%d", &givenID);
                     del(givenID, cli, tabsize);
                     }
                     else if (choice2 == 3) {
                     }; break;
            case 3 : printf("\n\n\nQuel est le nom de la personne dont vous voulez obtenir les informations ?\n\n");
                     scanf("%s", givenName);
                     printf("\n\n\nQuel est le prenom de la personne dont vous voulez obtenir les informations ?\n\n");
                     scanf("%s", givenPrenom);
                     printf("\n\n\n");
                     search(cli, tabsize, givenName, givenPrenom); break;
            case 4 : printf("\n\n\n\nQue voulez-vous faire exactement ?\n\n1 ~ Trier par nom ?\n\n2 ~ Trier par pays ?\n\n3 ~ Revenir en arriere\n\n");
                     scanf("%d", &choice3);
                     if (choice3 == 1) {
                        tri_fusion_nom(cli, 1, tabsize-1); affichage(cli, tabsize); break;
                     }
                     else if (choice3 == 2) {
                        tri_fusion_pays(cli, 1, tabsize-1); affichage(cli, tabsize); break;
                     }
                     else if (choice2 == 3) {
                     }; break;
            case 5 : printf("\n\n\nAu revoir !!!! :)\n\n");
                     end = 1; break;
            default : printf("je n'ai pas compris votre demande :(\n\n"); break;
        }
            
    } while (end != 1);         //le do while permet de repeter le menu à chaque fois qu'il est effectué

    return 0;

}