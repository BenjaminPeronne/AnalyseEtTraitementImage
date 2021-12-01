#include "image.h"

#include <stdio.h>
#include <stdlib.h>

void menu_principal(struct fichierimage *fichier, struct fichierimage *fichier2, struct fichierimage *fichier3) {
    // Menu de selection et affichage d'une image

    int choix = 27;
    while (choix != 0) {
        printf("Merci de bien voulori choisir l'action à effectuer");
        printf("\n  1. Ouverture image original");
        printf("\n  2. Une image en niveau de gris");
        printf("\n  3. Une image miroir");
        printf("\n  4. Une image symétrie");
        printf("\n  5. Une image pivot gauche");
        printf("\n  6. Une image pivot droite");
        printf("\n  7. Passage d'une image RGB à TSL");
        printf("\n  8. Passage d'une image TSL à RGB");
        printf("\n  9. Calcul du pourcentage de couleur");
        printf("\n  10. Création d'une image négative");
        printf("\n  11. Seuillage d'une image"); // Seuillage d'une image
        printf("\n  12. Inversion des couleurs d'une image");
        printf("\n  13. Réduction d'une image (changement d'échelle)");
        printf("\n  14. Agrandissement d'une image (changement d'échelle)");
        printf("\n  15. Une image monochrome");
        printf("\n  16. Supperposition d'image");
        printf("\n  17. Rotation Image");
        printf("\n  18. Réduire le bruit d'une image");
        printf("\n  19. Filtrage");
        printf("\n  20. Modification de la luminosité d'une image");
        printf("\n  21. Récupérations d'informations d'une images");
        printf("\n  22. Selectionner une zone de l'image");
        printf("\n  23. Calcul de l'histogramme d'une image");
        printf("\n  24. Filtre moyenneur");
        printf("\n  25. Egalisation de l'histogramme");
        printf("\n  26. Contraste"); 
        printf("\n  27. Convolution de l'image");
        printf("\n  0. Quitter");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("clear");
        system("cls");

        if (choix == 1) {
            // Entrer le nom du fichier à charger
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];                                   // nom du fichier
            printf("Entrer le nom du fichier à charger : "); // Demande le nom du fichier à charger
            scanf("%s", nomFichier);                                // Récupère le nom du fichier à charger

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension); // Concatène le nom du fichier avec l'extension .bmp

            // Charger l'image
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp"); // Charge mon Image .bmp télécharger depuis le web
            fichier = charger(nomEnregistrement); // Charge mon Image .bmp télécharger depuis le web

            // Afficher l'image
            sprintf(nomEnregistrement, "open %s%s", nomFichier, extension); // Concatène le nom du fichier avec l'extension .bmp
            // sprintf(nomEnregistrement, "start %s%s", nomFichier, extension); // Concatène le nom du fichier avec l'extension .bmp
            system(nomEnregistrement);
            free(fichier);
        } else if (choix == 2) {
            // -------------------------  Niveau de gris
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];                                   // nom du fichier
            printf("Entrer le nom du fichier à charger : "); // Demande le nom du fichier à charger
            scanf("%s", nomFichier);                                // Récupère le nom du fichier à charger

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension); // Concatène le nom du fichier avec l'extension .bmp

            // Charger l'image
            fichier = charger(nomEnregistrement); // Charge mon Image .bmp télécharger depuis le web
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp"); // Charge mon Image .bmp télécharger depuis le web

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            imageVersNiveauDeGris(fichier, nom, prenom);                    
        } 
        else if (choix == 3) {
            // ------------------------- Image Miroir
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];                            
            printf("Entrer le nom du fichier à charger : "); 
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            imageVersMirroir(fichier, nom, prenom);
        } else if (choix == 4) {
            // ------------------------- Image symétrie
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];                            
            printf("Entrer le nom du fichier à charger : "); 
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            imageVersSymetrie(fichier, nom, prenom);
        } else if (choix == 5) {
            // ------------------------- Image Pivot Gauche
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            pivoterImageDroit(fichier, nom, prenom);
        } else if (choix == 6) {
            // ------------------------- Image Pivot Droite
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            
            pivoterImageGauche(fichier, nom, prenom);
        } else if (choix == 7) {
            // Image RGB vers TSL
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            passageRVBTsl(fichier, nom, prenom);
        } else if (choix == 8) {
            // Image TSL vers RGB

            // fichier = charger("./res/LAURETTA_PERONNE_T.bmp");
            // fichier2 = charger("./res/LAURETTA_PERONNE_S.bmp");
            // fichier3 = charger("./res/LAURETTA_PERONNE_L.bmp");

            // imageTSLVersRGB(fichier, fichier2, fichier3);
            // // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_RGV.bmp", fichier);
            // // system("./res/LAURETTA_PERONNE_resultat_Lena_RGV.bmp");
            // free(fichier);
            // free(fichier2);
            // free(fichier3);

        } else if (choix == 9) {
            // Calcul du pourcentage de couleur

            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            // calculerPourcentageCouleur(fichier);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_PourcentageCouleur.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_PourcentageCouleur.bmp");
            // free(fichier);
        } else if (choix == 10) {
            // Image négative
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            imageNegative(fichier, nom, prenom);        
        } else if (choix == 11) {
            // Seuillage de l'image
            int seuil = 0;
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            printf("Entrer le seuil : ");
            scanf("%d", &seuil);

            seuillage(fichier, nom, prenom, seuil);
        } else if (choix == 12) {
            // Inversion des couleurs d'une image
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            fichier = charger(nomEnregistrement);

            inversionCouleur(fichier, nom, prenom);        
        } else if (choix == 13) {
            // Réduction de l'image
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            int echelle = 0;
            printf("Entrer l'échelle : ");
            scanf("%d", &echelle);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

                    
            fichier = charger(nomEnregistrement);

            reductionImage(fichier, nom, prenom, echelle);
            // free(fichier);
        } else if (choix == 14) {
            // Agrandissement de l'image
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);
            
            int echelle = 0;

            printf("Entrer l'échelle : ");
            scanf("%d", &echelle);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);
        
            agrandissementImage(fichier, nom, prenom, echelle);
        } else if (choix == 15) {
            // monochrome d'une image en paramètre un canal
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);
        
            // Entrer une couleur  soit R ou G ou B
            char couleur;

            printf("Entrer la couleur : \n");
            scanf(" %c", &couleur);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            monochromeImage(fichier, nom, prenom, couleur);
        } else if (choix == 16) {
            // Supperposition d'une image sur une autre
            char nomEnregistrement1[100];
            char nomEnregistrement2[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier1[100];
            char nomFichier2[100];

            printf("Entrer le nom du premier fichier à charger : ");
            scanf("%s", nomFichier1);

            sprintf(nomEnregistrement1, "%s%s", nomFichier1, extension);

            printf("Entrer le nom du deuxième fichier à charger : ");
            scanf("%s", nomFichier2);

            sprintf(nomEnregistrement2, "%s%s", nomFichier2, extension);
            
            fichier = charger(nomEnregistrement1);
            fichier2 = charger(nomEnregistrement2);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            // fichier2 = charger("LAURETTA_PERONNE_Paysage.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            supperposition(fichier, fichier2, nom, prenom);

            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Superposition.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Superposition.bmp");
            free(fichier);
            free(fichier2);
        } else if (choix == 17) {
            // Rotation Image
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);
            
            int angle = 0;
            printf("Entrer l'angle : ");
            scanf("%d", &angle);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            rotationImage(fichier, nom, prenom, angle);
        } else if (choix == 18) {
            // Réduction de bruite d'une image
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            reductionBruite(fichier, nom, prenom);
        } else if (choix == 19) {
            // Filtre                             
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);

            int matrice[3][3];
            int i, j;
            
            printf("\n");
            printf("Entrer une matrice 3x3 séparer par des espaces\n");
            printf("Par exemple : 1 2 1 2 4 2 1 2 1 \n");
            printf("Entrer la matrice : \n");
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    scanf("%d", &matrice[i][j]);
                }
            }

            printf("\n");
            printf("voici le masque saisie");
            printf("\n");
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    printf("%4d ", matrice[i][j]);
                }
                printf("\n");
            }

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            char prenom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            printf("Entrer votre prenom : ");
            scanf("%s", prenom);

            filtreImage(fichier, nom, prenom, matrice);            
        } else if (choix == 20) {
            // luminosite d'une image
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);

            int luminosite = 0;
            printf("Entrer la luminosité  entre 0 et 100 : ");
            scanf("%d", &luminosite);

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];            

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            modifLuminanceImage(fichier, nom, luminosite);            
            // modifLuminanceImage(fichier, luminosite);                        
        } else if (choix == 21) {
            //  Récupérations d'informations d'une images.
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
        
            informationSurImage(fichier);
            free(fichier);
        } else if (choix == 22) {
            // Selectionner une partie d'une image
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);

            int x, y, x2, y2;
            printf("Entrer les coordonnées de la zone : \n");
            printf("x : ");
            scanf("%d", &x);
            printf("y : ");
            scanf("%d", &y);
            printf("x2 : ");
            scanf("%d", &x2);
            printf("y2 : ");
            scanf("%d", &y2);

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];            

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            
            selectionnerZone(fichier, nom, x, y, x2, y2);

            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Selection.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Selection.bmp");
            free(fichier);

        } else if (choix == 23) {
            // Appel de la fonction permettant le calcul de l'histogramme d'une image
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            calculHistogramme(fichier);
        } else if (choix == 24) {
            // Filtre moyenneur
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);            
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];            

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            filtreMoyenneur(fichier, nom);
        } else if (choix == 25) {
            // egalisation histogramme
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];            

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            histogrammeEgalisation(fichier, nom);                
        } else if (choix == 26) {
            // Contraste
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);

            int contraste;
            
            printf("Entrer le niveau de contraste : "); 
            scanf("%d", &contraste);

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];

            printf("Entrer votre nom : ");
            scanf("%s", nom);

            contrasteImage(fichier, nom, contraste);      
        } else if (choix == 27) {
            // convulation de l'image |last|
            char nomEnregistrement[100];
            char extension[5] = ".bmp";

            // Entrer le nom du fichier à charger
            char nomFichier[100];
            printf("Entrer le nom du fichier à charger : ");
            scanf("%s", nomFichier);

            sprintf(nomEnregistrement, "%s%s", nomFichier, extension);

            fichier = charger(nomEnregistrement);
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");


            int i, j, diviseur;
            int masque[3][3];
            // int masque[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
            // int masque[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

            // Normalisation de l'image en fonction de la matrice de convolution
            printf("Valeur du diviseur afin de réalisation la normalisation  : \n");
            scanf("%d", &diviseur);

            // Masque de convulation
            printf("Entrer le masque de convulation : \n");
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    scanf("%d", &masque[i][j]);
                }
            }
            printf("\n");
            printf("voici le masque saisie");
            printf("\n");
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    printf("%4d ", masque[i][j]);
                }
                printf("\n");
            }

            // Nom de l'utilisateur pour sauvegarder l'image
            char nom[50];
            printf("Entrer votre nom : ");
            scanf("%s", nom);

            convolution(fichier, nom, masque, diviseur);            
        } else if (choix == 0) {
            printf("Au revoir  \n");
        } else {
            printf("Votre choix n'est pas valide \n");
        }
    }
}
