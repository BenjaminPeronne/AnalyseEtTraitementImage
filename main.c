#include "image.h"

//------------------------------------------------------------------------------
// nom : LAURETTA-PERONNE
// prenom : Aymerick
//
// Code source pour le projet d'UE035
// description : (les fonctions sont d�finit dans image.h)
//
// les pointeurs images dans ce code sont de type : struct fichierimage *
//
// fonction struct fichierimage * charger(char *)
// permet de charger une image presente sur le disque en memoire vive, la fonction
// renvoie un pointeur de type : struct fichierimage *
//
// fonction int enregistrer(struct fichierimage *,char *)
// permet d'enregistrer une image sur le disque sous le nom donn� en arg2, cette
// image est contenue dans une pointeur de type : struct fichierimage * fournit en arg1
//
// fonction struct fichierimage * nouveau(int,int)
// permet de creer une image en memoire de largeur arg1 et de hauteur arg2, la fonction
// retourne un pointeur de type : struct fichierimage *
//
// fonction void imageVersNiveauDeGris(struct fichierimage *fichier)
// permet de creer une image en memoire de niveau de gris, la fonction prend en
// parametre un pointeur de type : struct fichierimage *
// la fonction ne retourne rien
//
// void imageVersMirroir(struct fichierimage *fichier)
// permet de creer une image en mémoire de miroir, la fonction prend en parametre
// un pointeur de type : struct fichierimage *
// la fonction ne retourne rien
//
// void pivoterImageDroit(struct fichierimage *fichier)
// permet de creer une image en mémoire de pivoter à droite, la fonction prend en
// parametre un pointeur de type : struct fichierimage *
// la fonction ne retourne rien
//
// void pivoterImageGauche(struct fichierimage *fichier)
// permet de creer une image en mémoire de pivoter à gauche, la fonction prend en
// parametre un pointeur de type : struct fichierimage *
// la fonction ne retourne rien
//
// void convolution(struct fichierimage *fichier, int matrice[3][3], int diviseur)
// permet de creer une image en mémoire de convolution, la fonction prend en
// parametre un pointeur de type : struct fichierimage *, une matrice de convolution
// et un diviseur
// la fonction ne retourne rien
//------------------------------------------------------------------------------

int main() {
    // variable permettant le parcours d'une image
    int i, j;

    // exemple de déclarion d'un pointeur image
    struct fichierimage *fichier = NULL;
    struct fichierimage *fichier2 = NULL;
    struct fichierimage *fichier3 = NULL;

    // modification ou lecture de pixels d'une image
    /*
    fichier = nouveau(100, 100);
    for (i = fichier->entetebmp.hauteur; i >= 0; i--)
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier->image[i][j].r = 0;
            fichier->image[i][j].g = 255;
            fichier->image[i][j].b = 255;
        }

    enregistrer("resultat.bmp", fichier);
    free(fichier);
    */

    // Effectue un copie coller d'une image dans un nouveau fichier .bmp
    /*
    fichier=charger("LAURETTA_PERONNE_Paysage.bmp"); // Charge mon Image .bmp télécharger depuis le web
    enregistrer("./res/LAURETTA_PERONNE_resultat_Paysage.bmp",fichier); // Enregistre l'image télécharger sous un notre fichier
    free(fichier); // Libère la mémoire
    */

    // Menu de selection et affichage d'une image
    int choix = 20;
    while (choix != 0) {
        printf("Merci de bien voulori choisir l'action à effectuer");
        printf("\n  1. Une image en niveau de gris");
        printf("\n  2. Une image miroir");
        printf("\n  3. Une image symétrie");
        printf("\n  4. Une image pivot gauche");
        printf("\n  5. Une image pivot droite");
        printf("\n  6. Passage d'une image RGB à TSL");
        printf("\n  7. Passage d'une image TSL à RGB");
        printf("\n  8. Calcul du pourcentage de couleur");
        printf("\n  9. Création d'une image négative");
        printf("\n  10. Seuillage d'une image"); // Seuillage d'une image
        printf("\n  11. Inversion des couleurs d'une image");
        printf("\n  12. Réduction d'une image (changement d'échelle)");
        printf("\n  13. Agrandissement d'une image (changement d'échelle)");
        printf("\n  14. Convolution de l'image");
        printf("\n  0. Quitter");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            // Niveau de gris

            // Entrer le nom du fichier à charger
            char nom[100];                                   // nom du fichier
            printf("Entrer le nom du fichier à charger : "); // Demande le nom du fichier à charger
            scanf("%s", nom);                                // Récupère le nom du fichier à charger

            // Charger l'image
            fichier = charger(nom); // Charge mon Image .bmp télécharger depuis le web
            // fichier = charger("LAURETTA_PERONNE_Lena.bmp"); // Charge mon Image .bmp télécharger depuis le web
            imageVersNiveauDeGris(fichier);                                                // Convertit l'image en niveau de gris
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_NiveauDeGris.bmp", fichier); // Enregistre l'image modifié sous un notre fichier
            system("./res/LAURETTA_PERONNE_resultat_Lena_NiveauDeGris.bmp");               // Ouverture de du fichier image dans la visionneuse
            free(fichier);                                                                 // On Libère la mémoire
        } else if (choix == 2) {
            // Image Miroir

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            imageVersMirroir(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Miroir.bmp", fichier);
            system("./res/LAURETTA_PERONNE_resultat_Lena_Miroir.bmp");
            free(fichier);
        } else if (choix == 3) {
            // Image symétrie

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            imageVersSymetrie(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Symetrie.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Symetrie.bmp");
            free(fichier);

        } else if (choix == 4) {
            // Image Pivot Gauche

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            pivoterImageDroit(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_PivotDroit.bmp", fichier);
            system("./res/LAURETTA_PERONNE_resultat_Lena_PivotDroit.bmp");
            free(fichier);
        } else if (choix == 5) {
            // Image Pivot Droite

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            pivoterImageGauche(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_PivotGauche.bmp", fichier);
            system("./res/LAURETTA_PERONNE_resultat_Lena_PivotGauche.bmp");
            free(fichier);
        } else if (choix == 6) {
            // Image RGB vers TSL

            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            // imageRGBVersTSL(fichier);
            // // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_RGV.bmp", fichier);
            // // system("./res/LAURETTA_PERONNE_resultat_Lena_RGV.bmp");
            // free(fichier);

        } else if (choix == 7) {
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

        } else if (choix == 8) {
            // Calcul du pourcentage de couleur

            // fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            // calculerPourcentageCouleur(fichier);
            // enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_PourcentageCouleur.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_PourcentageCouleur.bmp");
            // free(fichier);
        } else if (choix == 9) {
            // Image négative

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            imageNegative(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Negatif.bmp", fichier);
            system("./res/LAURETTA_PERONNE_resultat_Lena_Negatif.bmp");
            free(fichier);

        } else if (choix == 10) {
            // Seuillage de l'image
            int seuil = 0;
            char nomEnregistrement[100];

            printf("Entrer le seuil : ");
            scanf("%d", &seuil);

            sprintf(nomEnregistrement, "./res/LAURETTA_PERONNE_resultat_Lena_Seuillage_%d.bmp", seuil);

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            seuillage(fichier, seuil);
            enregistrer(nomEnregistrement, fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Seuillage.bmp");
            free(fichier);
        } else if (choix == 11) {
            // Inversion des couleurs d'une image

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            inversionCouleur(fichier);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_InversionCouleur.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_InversionCouleur.bmp");
            free(fichier);
        } else if (choix == 12) {
            // Réduction de l'image

            int echelle = 0;
            printf("Entrer l'échelle : ");
            scanf("%d", &echelle);

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");
            reductionImage(fichier, echelle);
            enregistrer("./res/LAURETTA_PERONNE_resultat_Lena_Reduction.bmp", fichier);
            // system("./res/LAURETTA_PERONNE_resultat_Lena_Reduction.bmp");
            free(fichier);
        } else if (choix == 13) {
            // Agrandissement de l'image

            fichier = charger("LAURETTA_PERONNE_Lena.bmp");

        } else if (choix == 14) {
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
