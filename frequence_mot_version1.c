#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int frequence_mot(FILE *file){
	char motActuel[100];
	char frequencemot[100];
	int compteur=1;
	int index_mot = 0;
	double index_depart;
	double index_boucle;

	int doublure =0;
	do{
		int j=0;
		// if(j=0){
		// 	fscanf(file,"%s",motActuel);
		// }
		/*on scanne le mot suivant
		pour j=0 c'est le 1er mot
		ensuite à chaque tour, on passe au mot suivant par index_mot++ en fin de fichier*/
		while(j!=index_mot){
			fscanf(file,"%s",motActuel);
			j++;
		}
		if(feof(file)){
			return 0;
		}
		/*position actuel du curseur*/
		index_depart= ftell(file);
		strcpy(frequencemot,motActuel);
		/*place le curseur au début du fichier*/
		fseek(file,0, SEEK_SET);
		do{
			/*on scanne notre 2nd mot*/
			fscanf(file,"%s",frequencemot);
			/*index du mot actuel*/
			index_boucle = ftell(file);
			/*on compare les chaines*/
			if(strcmp(frequencemot,motActuel)==0){
				if(index_boucle < index_depart){
					doublure =1;
				}
				else{
				compteur++;
				}
			}
		}while(!feof(file));
		index_mot ++;
		if(doublure ==0){
			printf("Pour %s on a %d caractères\n",motActuel,compteur);
		}
		doublure =0;
		compteur = 0;
		/*on replace notre curseur au début du fichier*/
		fseek(file,0, SEEK_SET);
	}while(!feof(file));
	return 1;
}

int main(){
	// int compteur_nb_mot;
	// int compteur_phras;
	FILE *file = fopen("Marseillaise.txt","r");
	/*Vérification de l'ouverture du fichier*/
	if(file==NULL){ 
		printf("erreur lors de l'ouverture du fichier");	
		return 0;
	}
	else{
		// printf("ouverture fichier");		
		// compteur_nb_mot = compteur_mot(file);
		// printf("le nombre de mot est : %d\n",compteur_nb_mot);

		// compteur_phras = compteur_phrase(file);
		// printf("le nombre de phrase est : %d\n",compteur_phras);
		// fclose(file);
		frequence_mot(file);
	}
	return 1;
}

//gcc -c main.c && gcc -o main main.o && ./main

