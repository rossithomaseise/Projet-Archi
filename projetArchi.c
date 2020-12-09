#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int main()
// {
// 	FILE* fichier;
// 	fichier=fopen("test.txt","r");

// 	char tabC[50];
// 	int tailleNom=0;

// 	fscanf(fichier,"%s",tabC);
// 	char* nom = malloc(strlen(tabC)+1);
// 	tailleNom+=strlen(tabC)+1;//+1 pour l'espace
// 	strcpy(nom,tabC);

// 	fscanf(fichier,"%s",tabC);
// 	char* prenom = malloc(strlen(tabC)+1);
// 	tailleNom+=strlen(tabC)+1;//+1 pour \0
// 	strcpy(prenom,tabC);

// 	char* toutleNOM = malloc(tailleNom);
// 	strcpy(toutleNOM,nom);
// 	strcat(toutleNOM," ");
// 	strcat(toutleNOM,prenom);

// 	UnIndiv->nom = toutleNOM;

// 	free(nom);
// 	free(prenom);



	int main()
{
    FILE* fichier = NULL;
    int NbCaracLigne = 100;
    int NbLignesPage = 20;
    int caractereActuel = 0;

    int NbLignes = 0;
    int NbPages = 0;

    int TempLigne = 0;
    int TempPage = 0;
 
    fichier = fopen("Marseillaise.txt", "r");
 
    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        while (caractereActuel != EOF)
        {
            caractereActuel = fgetc(fichier); // On lit le caractère

            if ((caractereActuel=='\n')||(TempLigne==NbCaracLigne))
            {
            	NbLignes+=1;
            	TempLigne=0;
            	TempPage+=1;
            }

            if (TempPage==NbLignesPage)
            {
            	NbPages+=1;
            	TempPage=0;
            }
        } // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

 		NbLignes+=1;	//pour la derniere ligne

        fclose(fichier);

        printf("Le fichier à %d lignes.\nEt il à %d pages.\n", NbLignes, NbPages);
    }
 
    return 0;
}

// 	fclose(fichier);
// 	return 0;
// }
