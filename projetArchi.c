#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	int main()
{
    FILE* fichier = NULL;
    int NbCaracLigne = 100;
    int NbLignesPage = 20;
    int caractereActuel = 0;
    int lastCaracter = 0;

    int NbLignes = 0;
    int NbPages = 0;
    int NbPhrases = 0;
    int NbMots = 0;

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

            if ((caractereActuel=='.')||(caractereActuel==' ')||(caractereActuel=='\n'))     
            {
                if ((caractereActuel=='\n'))
                {
                    if ((lastCaracter=='?')||(lastCaracter=='!')||(lastCaracter=='\n'));
                    else
                    {
                        NbMots+=1;
                    }
                }
                else
                {
                    NbMots+=1;
                }
            }
            //printf("%c ---mot %d\n", caractereActuel,NbMots);

            lastCaracter=caractereActuel;

        } // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

 		NbLignes+=1;	//Pour compter la derniere ligne    40

        fclose(fichier);

        printf("Le fichier a %d lignes.\nEt il a %d pages.\nEt il a %d phrases\nEt il a %d mots.\n", NbLignes, NbPages, NbPhrases,NbMots);
    }
 
    return 0;
}
