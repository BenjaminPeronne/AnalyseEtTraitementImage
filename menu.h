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
        printf("\n  26. Convolution de l'image");
        printf("\n  0. Quitter");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("clear");
        system("cls");

        if (choix == 1) {
            // Entrer le nom du fichier à charger
            // char nom[100];                                   // nom du fichier
            // printf("Entrer le nom du fichier à charger : "); // Demande le nom du fichier à charger
            // scanf("%s", nom);                                // Récupère le nom du fichier à charger

            // Charger l'image
            // fichier = charger(nom); // Charge mon Image .bmp télécharger depuis le web
            fichier = charger("LAURETTA_PERONNE_Lena.bmp"); // Charge mon Image .bmp télécharger depuis le web

            system("open LAURETTA_PERONNE_Lena.bmp");
            free(fichier);
        } else if (choix == 2) {
            // Niveau de gris

            // Entrer le nom du fichier à charger
            // char nom[100];                                   // nom du fichier
            // printf("Entrer le nom du fichier à charger : "); // Demande le nom du fichier à charger
            // scanf("%s", nom);                                // Récupère le nom du fichier à charger

            // Charger l'image
            // fichier = charger(nom); // Charge mon Image .bmp télécharger depuis le web
            fichier = charger("LAURETTA_PERONNE_Lena.bmp"); // Charge mon Image .bmp télécharger depuis le web
            imageVersNiveauDeGris(fichier);                                                // Convertit l'image en niveau de gris

            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_NiveauDeGris.bmp", fichier); // Enregistre l'image modifié sous un notre fichier
            system("open ./res/LAURETTA_PERONNE_resultat_Lena_NiveauDeGris.bmp");          // Ouverture de du fichier image dans la visionneuse
            free(fichier);                                                                 // On Libère la mémoire                        
        } 
        else if (choix == 3) {
            // Image Miroir

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            imageVersMirroir(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Miroir.bmp", fichier);
            system("open ./res/LAURETTA_PERONNE_resultat_Lena_Miroir.bmp");
            free(fichier);
        } else if (choix == 4) {
            // Image symétrie

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            imageVersSymetrie(fichier);
            // enregistrer("open ./res/LAURETTA_PERONNE_resultat_Lena_Symetrie.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Symetrie.bmp");
            // free(fichier);

        } else if (choix == 5) {
            // Image Pivot Gauche

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            pivoterImageDroit(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_PivotDroit.bmp", fichier);
            system("open ./res/LAURETTA_PERONNE_resultat_Lena_PivotDroit.bmp");
            free(fichier);
        } else if (choix == 6) {
            // Image Pivot Droite

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            pivoterImageGauche(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_PivotGauche.bmp", fichier);
            system("open ./res/LAURETTA_PERONNE_resultat_Lena_PivotGauche.bmp");
            free(fichier);
        } else if (choix == 7) {
            // Image RGB vers TSL

            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            // imageRGBVersTSL(fichier);
            // // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_RGV.bmp", fichier);
            // // system("./res/LAURETTA_PERONNE_resultat_Lena_RGV.bmp");
            // free(fichier);

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

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            imageNegative(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Negatif.bmp", fichier);
            system("open ./res/LAURETTA_PERONNE_resultat_Lena_Negatif.bmp");
            free(fichier);

        } else if (choix == 11) {
            // Seuillage de l'image
            int seuil = 0;
            char nomEnregistrement[100];

            printf("Entrer le seuil : ");
            scanf("%d", &seuil);

            sprintf(nomEnregistrement, "./res/LAURETTA_PERONNE_resultat_Lena_Seuillage_%d.bmp", seuil);

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            seuillage(fichier, seuil);

            enregistrer(nomEnregistrement, fichier);
            sprintf(nomEnregistrement, "open ./res/LAURETTA_PERONNE_resultat_Lena_Seuillage_%d.bmp", seuil);
            system(nomEnregistrement);
            free(fichier);
        } else if (choix == 12) {
            // Inversion des couleurs d'une image

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            inversionCouleur(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_InversionCouleur.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_InversionCouleur.bmp");
            free(fichier);
        } else if (choix == 13) {
            // Réduction de l'image

            int echelle = 0;
            printf("Entrer l'échelle : ");
            scanf("%d", &echelle);

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            reductionImage(fichier, echelle);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Reduction.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Reduction.bmp");
            free(fichier);
        } else if (choix == 14) {
            // Agrandissement de l'image
            int echelle = 0;

            printf("Entrer l'échelle : ");
            scanf("%d", &echelle);

            // fichier = charger("LAURETTA_PERONNE_resultat_Lena_Reduction.bmp");
            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            agrandissementImage(fichier, echelle);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Agrandissement.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Agrandissement.bmp");
            free(fichier);

        } else if (choix == 15) {
            // monochrome d'une image en paramètre un canal

            // Entrer une couleur  soit R ou G ou B
            char couleur;

            printf("Entrer la couleur : \n");
            scanf(" %c", &couleur);

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            monochromeImage(fichier, couleur);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Monochrome.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Monochrome.bmp");
            free(fichier);
        } else if (choix == 16) {
            // Supperposition d'une image sur une autre

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            fichier2 = charger("LAURETTA_PERONNE_Paysage.bmp");

            superpositionImage(fichier, fichier2);

            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Superposition.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Superposition.bmp");
            free(fichier);
            free(fichier2);
        } else if (choix == 17) {
            // Rotation Image

            int angle = 0;
            printf("Entrer l'angle : ");
            scanf("%d", &angle);

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            rotationImage(fichier, angle);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Rotation.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Rotation.bmp");
            free(fichier);

        } else if (choix == 18) {
            // Réduction de bruite d'une image

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            reductionBruite(fichier);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_ReductionBruite.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_ReductionBruite.bmp");
            free(fichier);
        } else if (choix == 19) {
            // Filtre
            // int matrice[3][3];
            // int i, j;

            // printf("Entrer la matrice : \n");
            // for (i = 0; i < 3; i++) {
            //     for (j = 0; j < 3; j++) {
            //         scanf("%d", &matrice[i][j]);
            //     }
            // }

            // printf("\n");
            // printf("voici le masque saisie");
            // printf("\n");
            // for (i = 0; i < 3; i++) {
            //     for (j = 0; j < 3; j++) {
            //         printf("%4d ", matrice[i][j]);
            //     }
            //     printf("\n");
            // }

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            filtreImage(fichier);

        } else if (choix == 20) {
            int luminosite = 0;
            printf("Entrer la luminosité  entre 0 et 100 : ");
            scanf("%d", &luminosite);

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            modifLuminanceImage(fichier, luminosite);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_ModificationLuminosite.bmp", fichier);
            free(fichier);
        } else if (choix == 21) {
            //  Récupérations d'informations d'une images.
            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            informationSurImage(fichier);
            free(fichier);
        } else if (choix == 22) {
            // Selectionner une partie d'une image
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

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            selectionnerZone(fichier, x, y, x2, y2);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Selection.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Selection.bmp");
            free(fichier);

        } else if (choix == 23) {
            // Appel de la fonction permettant le calcul de l'histogramme d'une image

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            calculHistogramme(fichier);
        } else if (choix == 24) {
            // Filtre moyenneur

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            filtreMoyenneur(fichier);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_FiltreMoyenneur.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_FiltreMoyenneur.bmp");
            // free(fichier);
        } else if (choix == 25) {
            // egalisation histogramme

            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            // histogrammeEgalisation(fichier);

            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_EgalisationHistogramme.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_EgalisationHistogramme.bmp");
            // free(fichier);            
        } else if (choix == 26) {
            // convulation de l'image |last|

            int i, j, diviseur;
            int masque[3][3];
            // int masque[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
            // int masque[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

            // Entrer le nom du fichier à charger
            // char nom[100];
            // printf("Entrer le nom du fichier à charger : ");
            // scanf("%s", nom);

            // charger l'image
            // fichier = charger(nom);
            fichier = charger("LAURETTA_PERONNE_Lena.bmp");

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

            // convolution(fichier, masque, diviseur);
            convolution(fichier, masque, diviseur);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Convolution.bmp", fichier);
            system("./res/LAURETTA_PERONNE_resultat_Lena_Convolution.bmp");
            free(fichier);

        } else if (choix == 0) {
            printf("Au revoir  \n");
        } else {
            printf("Votre choix n'est pas valide \n");
        }
    }
}
