#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	int main()
{
    FILE* fichier = NULL;
    int NbCaracLigne = 100;
    int NbLignesPage = 20;
    int caractereActuel = 0;

    int NbLignes = 0;
    int NbPages = 0;
    int NbPhrases = 0;

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

            if ((caractereActuel=='.')||(caractereActuel=='!')||(caractereActuel=='?'))
            {
                NbPhrases+=1;
            }
        } // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

 		NbLignes+=1;	//Pour compter la derniere ligne

        fclose(fichier);

        printf("Le fichier à %d lignes.\nEt il à %d pages.\nEt il y à %d phrases\n", NbLignes, NbPages,NbPhrases);
    }
 
    return 0;
}
