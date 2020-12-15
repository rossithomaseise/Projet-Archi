.data
erreur_ouverture_fichier:	.asciiz "erreur ouverture fichier\n"
success_ouverture_fichier:	.asciiz "succès ouverture fichier\n"
chemin_texte:                	.asciiz "test.txt"

    .text

main:
    li  $v0, 13            	 #open file
        la  $a0, chemin_texte  	 # file path
        li  $a1,0        	 #lecture =0 (flag)
        li  $a2,0        	 # = 0 (mode : reading from standard input)
        syscall        		 #ouverture du fichier
	move $s6, $v0      	 #adresse fichier 
	
        #si erreur d'ouverture du fichier
        bltz $v0,erreur_ouverture 		# erreur_ouverture
        la $a0,success_ouverture_fichier	# charge le texte
   	ori $v0,$zero,4				# 4 affichage texte
        syscall

        j fin_programme

erreur_ouverture:

    la $a0,erreur_ouverture_fichier
    ori $v0,$zero,4
        syscall

fin_programme:
	li   $v0, 16       # 16 pour fermer le fichier
  	move $a0, $s6      # adresse fichier dans $a0 pour fermeture
  	syscall            # fermeture

        ori $v0,$zero,10	#sortie
        syscall