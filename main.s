	.data
erreur_ouverture_fichier:	.asciiz "erreur ouverture fichier\n"
success_ouverture_fichier:	.asciiz "succès ouverture fichier\n"
chemin_texte:                	.asciiz "/home/polytech/Téléchargements/Projet_Archi/Marseillaise.txt"
buffer:				.space 1
tab_resultat_f2:		.word 0,0

    .text
main:
	subu $sp,$sp,8    	#prologue
	sw $fp,4($sp)
	addi $fp,$sp,8

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
        
        la $t6,tab_resultat_f2			# chargement du tableau pour resultat
        
        ori $s7,$zero,0			# var LAST_CARACTER fonction nb_mot initialisé à 0
        
        jal f1_lecture_caractere 		# appel fonction
  
        lw $fp,4($sp)				#FIN
	addu $sp,$sp,8
	
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
        
f1_lecture_caractere:  			#lecture du fichier caractère par caractère	
        subu $sp,$sp,12    		#prologue
	sw $fp,4($sp)
	sw $ra,8($sp)
	addu $fp,$sp,12
	
	lecture_caractere_f1:
        li $v0,14			#code service lecture fichier
        #chargement des paramètres
        ori $a0,$s6,0			#adresse fichier
        la $a1,buffer			#adresse buffer
        
        ori $a2,$zero,1			#nombre de caractère lue
        syscall
        ori $s0,$v0,0			#si V0= 0 => fin fichier
        
        beq $s0,$zero,fin_programme_f1	#on sort si c'est le dernier caractère
        
  	
        jal f2_compteur_phrase
        
        jal f3_compteur_mot
        
        ori $a0,$a1,0			#affichage du caractère
        ori $v0,$zero,4
        syscall
        
        ori $a0,$zero,0x20		#affichage espace
        ori $v0,$zero,11
        syscall
        
        j lecture_caractere_f1 		#on refait un tour de boucle
	
	fin_programme_f1:		
		
	lw $s4,0($t6)			# affichage du tab_resultat f2
	ori $a0,$s4,0
	ori $v0,$zero,1
	syscall
	
	lw $s4,4($t6)			# affichage du tab_resultat f3
	ori $a0,$s4,0
	ori $v0,$zero,1
	syscall
	

	lw $ra,8($sp)			#EPILOGUE
	lw $fp,4($sp)
	addu $sp,$sp,12
	
	jr $ra

f2_compteur_phrase:
	subu $sp,$sp,8   		#prologue
	sw $fp,4($sp)
	addu $fp,$sp,8
	
	ori $t0,$zero,0x21		# caract '!'
	ori $t1,$zero,0x2E		# caract '.'
	ori $t2,$zero,0x3F		# caract '?'
	
	lb $s5,0($a1)			# on récupoère le caractère lu
	
	beq $s5,$t0,compteur_phrase_f2	 #si ='!'
	beq $s5,$t1,compteur_phrase_f2 	#si ='.'
	beq $s5,$t2,compteur_phrase_f2	#si ='?'
	j fin_programme_f2	
	
	compteur_phrase_f2:
	addi $s1,$s1,1
	
	fin_programme_f2:		#EPILOGUE
	lw $fp,4($sp)
	addu $sp,$sp,8

	sw $s1,0($t6)			# on écrit dans le tab_resultat
	
	jr $ra

f3_compteur_mot:
	subu $sp,$sp,8   		#prologue
	sw $fp,4($sp)
	addu $fp,$sp,8
	
	#variables fonctions
	ori $t0,$zero,0x21		# caract '!'
	ori $t1,$zero,0x2E		# caract '.'
	ori $t2,$zero,0x3F		# caract '?'
	ori $t3,$zero,0x20		# caract ' ' (espace)
	ori $t4,$zero,0x2C		# caract ','
	ori $t5,$zero,0x3B		# caract ';'
	ori $t7,$zero,0x0A		# caract '\n'
	
	lb $s5,0($a1)			# on récupère le caractère lu
	
	#1er if
	beq $s5,$t1,compteur_mot_2_f3 	# if == '.'
	beq $s5,$t3,compteur_mot_2_f3	# if == ' '
	beq $s5,$t7,compteur_mot_1_f3	# if == '\n'
	j fin_programme_f3		# sinon on sort du programme
	
	#2 if et son sous if
	compteur_mot_1_f3:		
	beq $s7,$t2,fin_programme_f3	# if == '?'
	beq $s7,$t0,fin_programme_f3	# if == '!'
	beq $s7,$t7,fin_programme_f3	# if == '\n'
	beq $s7,$t1,fin_programme_f3	# if == '.'
	beq $s7,$t4,fin_programme_f3	# if == ','
	beq $s7,$t5,fin_programme_f3	# if == ';'
	
	addi $s2,$s2,1			# NbMots +=1
	j fin_programme_f3
	
	#2 else if
	compteur_mot_2_f3:
	beq $s7,$t0,fin_programme_f3	# if == '!'
	beq $s7,$t2,fin_programme_f3	# if == '?'
	beq $s7,$t3,fin_programme_f3	# if == ' '
	beq $s7,$t5,fin_programme_f3	# if == ';'
	
	addi $s2,$s2,1			# NbMots +=1
	
	j fin_programme_f3
	
fin_programme_f3:			#EPILOGUE
	ori $s7,$s5,0			#last_Caracter = caractere_Actuel
	sw $s2,4($t6)			# on écrit dans le tab_resultat
	
	lw $fp,4($sp)
	addu $sp,$sp,8
	jr $ra
