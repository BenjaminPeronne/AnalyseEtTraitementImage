#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure d'entete du fichier
struct entete_fichier {
    char idformat[2];
    int taille_fichier;
    int reserve;
    int debut;
};

// structure d'entete de l'image
struct entete_bmp {
    int taille_image;
    int largeur;
    int alignement;
    int hauteur;
    short plans;
    short profondeur;
    int compression;
    int taille_image_totale;
    int resolutionh;
    int resolutionv;
    int nbrcouleur;
    int nbrcouleuri;
};

// structure d'un pixel
struct pixels {
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

// structure du fichier
struct fichierimage {
    struct entete_fichier entetefichier;
    struct entete_bmp entetebmp;
    struct pixels image[5000][5000];
};

struct fichierimage *charger(char *nom) {
    FILE *f;
    int i, j, k;
    unsigned char zero;
    unsigned char *buffer;
    int position = 0;
    int longueur = 0;
    struct fichierimage *fichier = (struct fichierimage *)malloc(sizeof(struct fichierimage));

    f = fopen(nom, "rb");
    fseek(f, 0, SEEK_END);
    longueur = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = (unsigned char *)malloc(longueur * sizeof(unsigned char));
    fread((unsigned char *)buffer, 1, longueur, f);
    fclose(f);

    // lecture de l'entete du fichier
    memcpy(&fichier->entetefichier.idformat, (buffer + position), 2);
    position += 2;
    memcpy(&fichier->entetefichier.taille_fichier, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetefichier.reserve, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetefichier.debut, (buffer + position), 4);
    position += 4;

    /*
    printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
    printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
    printf("reserve                  :%d\n",fichier->entetefichier.reserve);
    printf("debut                    :%d\n",fichier->entetefichier.debut);
    */

    // lecture de l'entete de l'image
    memcpy(&fichier->entetebmp.taille_image, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.largeur, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.hauteur, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.plans, (buffer + position), 2);
    position += 2;
    memcpy(&fichier->entetebmp.profondeur, (buffer + position), 2);
    position += 2;
    memcpy(&fichier->entetebmp.compression, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.taille_image_totale, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.resolutionh, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.resolutionv, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.nbrcouleur, (buffer + position), 4);
    position += 4;
    memcpy(&fichier->entetebmp.nbrcouleuri, (buffer + position), 4);
    position += 4;

    /*
    printf("taille image             :%d\n",fichier->entetebmp.taille_image);
    printf("largeur                  :%d\n",fichier->entetebmp.largeur);
    printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
    printf("plans                    :%d\n",fichier->entetebmp.plans);
    printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
    printf("compression              :%d\n",fichier->entetebmp.compression);
    printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
    printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
    printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
    printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
    printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
    */

    if (fichier->entetebmp.plans != 1 || fichier->entetebmp.profondeur != 24 || fichier->entetebmp.compression != 0 || fichier->entetebmp.nbrcouleur != 0 || fichier->entetebmp.nbrcouleuri != 0) {
        printf("Impossible de charger l'image\n");
        free(fichier);
        free(buffer);
        return 0;
    }

    // mise de l'image en memoire
    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            memcpy(&fichier->image[i][j].b, (buffer + position), 1);
            position += 1;
            memcpy(&fichier->image[i][j].g, (buffer + position), 1);
            position += 1;
            memcpy(&fichier->image[i][j].r, (buffer + position), 1);
            position += 1;
        }
        for (k = 0; k < fichier->entetebmp.largeur % 4; k++) {
            memcpy(&zero, (buffer + position), 1);
            position += 1;
        }
    }

    free(buffer);
    return fichier;
}

int enregistrer(char *nom, struct fichierimage *fichier) {
    FILE *f;
    int i, j, k;
    unsigned char zero = (unsigned char)0;
    unsigned char *buffer;
    int position = 0;
    int longueur = 14 + fichier->entetefichier.taille_fichier;
    buffer = (unsigned char *)malloc(longueur * sizeof(unsigned char));

    // ecriture de l'entete du fichier

    /*
    printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
    printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
    printf("reserve                  :%d\n",fichier->entetefichier.reserve);
    printf("debut                    :%d\n",fichier->entetefichier.debut);
    */

    memcpy((buffer + position), &fichier->entetefichier.idformat, 2);
    position += 2;
    memcpy((buffer + position), &fichier->entetefichier.taille_fichier, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetefichier.reserve, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetefichier.debut, 4);
    position += 4;

    // ecriture de l'entete de l'image

    /*
    printf("taille image             :%d\n",fichier->entetebmp.taille_image);
    printf("largeur                  :%d\n",fichier->entetebmp.largeur);
    printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
    printf("plans                    :%d\n",fichier->entetebmp.plans);
    printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
    printf("compression              :%d\n",fichier->entetebmp.compression);
    printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
    printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
    printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
    printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
    printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
    */

    memcpy((buffer + position), &fichier->entetebmp.taille_image, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.largeur, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.hauteur, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.plans, 2);
    position += 2;
    memcpy((buffer + position), &fichier->entetebmp.profondeur, 2);
    position += 2;
    memcpy((buffer + position), &fichier->entetebmp.compression, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.taille_image_totale, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.resolutionh, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.resolutionv, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.nbrcouleur, 4);
    position += 4;
    memcpy((buffer + position), &fichier->entetebmp.nbrcouleuri, 4);
    position += 4;

    if (fichier->entetebmp.plans != 1 || fichier->entetebmp.profondeur != 24 || fichier->entetebmp.compression != 0 || fichier->entetebmp.nbrcouleur != 0 || fichier->entetebmp.nbrcouleuri != 0) {
        printf("Impossible d'enregistrer l'image\n");
        free(buffer);
        return 0;
    }

    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            memcpy((buffer + position), &fichier->image[i][j].b, 1);
            position += 1;
            memcpy((buffer + position), &fichier->image[i][j].g, 1);
            position += 1;
            memcpy((buffer + position), &fichier->image[i][j].r, 1);
            position += 1;
        }
        for (k = 0; k < fichier->entetebmp.largeur % 4; k++) {
            memcpy((buffer + position), &zero, 1);
            position += 1;
        }
    }
    f = fopen(nom, "wb");
    fwrite((unsigned char *)buffer, 1, longueur, f);
    fclose(f);
    free(buffer);
    return 1;
}

struct fichierimage *nouveau(int largeur, int hauteur) {
    int i, j;
    struct fichierimage *fichier;
    int longueur;

    if (largeur > 5000 || hauteur > 5000 || largeur <= 0 || hauteur <= 0) {
        return (NULL);
    }

    longueur = 14 + 40 + 3 * largeur * hauteur + (largeur % 4) * hauteur;
    fichier = (struct fichierimage *)malloc(sizeof(struct fichierimage));

    // ecriture de l'entete du fichier

    fichier->entetefichier.idformat[0] = 'B';
    fichier->entetefichier.idformat[1] = 'M';
    fichier->entetefichier.taille_fichier = 40 + 3 * largeur * hauteur + (largeur % 4) * hauteur;
    fichier->entetefichier.reserve = 0;
    fichier->entetefichier.debut = 54;

    // ecriture de l'entete de l'image

    fichier->entetebmp.taille_image = 40;
    fichier->entetebmp.largeur = largeur;
    fichier->entetebmp.hauteur = hauteur;
    fichier->entetebmp.plans = 1;
    fichier->entetebmp.profondeur = 24;
    fichier->entetebmp.compression = 0;
    fichier->entetebmp.taille_image_totale = 40 + 3 * largeur * hauteur + (largeur % 4) * hauteur;
    fichier->entetebmp.resolutionh = 1;
    fichier->entetebmp.resolutionv = 1;
    fichier->entetebmp.nbrcouleur = 0;
    fichier->entetebmp.nbrcouleuri = 0;

    // lecture de l'ente du fichier

    /*
    printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
    printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
    printf("reserve                  :%d\n",fichier->entetefichier.reserve);
    printf("debut                    :%d\n",fichier->entetefichier.debut);
    */

    // lecture de l'ente de l'image

    /*
    printf("taille image             :%d\n",fichier->entetebmp.taille_image);
    printf("largeur                  :%d\n",fichier->entetebmp.largeur);
    printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
    printf("plans                    :%d\n",fichier->entetebmp.plans);
    printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
    printf("compression              :%d\n",fichier->entetebmp.compression);
    printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
    printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
    printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
    printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
    printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
    */

    // mise de l'image en memoire

    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier->image[i][j].b = 0;
            fichier->image[i][j].g = 0;
            fichier->image[i][j].r = 0;
        }
    }

    return fichier;
}
// #############################################

// fonction permetant de mettre une image en niveau de gris
void imageVersNiveauDeGris(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100]; // nom de l'image enregistrer
    char extension[5] = ".bmp";  // extension de l'image enregistrer
    // --------------------------------------------------
    int i, j;   // compteur
    int niveau; // niveau de gris

    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--) {                                          // parcours de l'image
        for (j = 0; j < fichier->entetebmp.largeur; j++) {                                           // parcours de l'image
            niveau = (fichier->image[i][j].r + fichier->image[i][j].g + fichier->image[i][j].b) / 3; // calcul du niveau de gris de l'image (moyenne des 3 couleurs)
            fichier->image[i][j].r = niveau;
            fichier->image[i][j].g = niveau;
            fichier->image[i][j].b = niveau;
        }
    }
    // Enregistrement de l'image et affichage de l'image
    sprintf(nomEnregistrement, "./res/%s_image_niveauDeGris%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_niveauDeGris%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_niveauDeGris%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// fonction permetant de cr??er une image miroir horizontal
void imageVersMirroir(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    int niveau;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur / 2; j++) {
            // on inverse les couleurs
            niveau = fichier->image[i][j].r;                                                  // on recupere la couleur rouge
            fichier->image[i][j].r = fichier->image[i][fichier->entetebmp.largeur - 1 - j].r; // on met la couleur rouge de l'image en bas a gauche
            fichier->image[i][fichier->entetebmp.largeur - 1 - j].r = niveau;                 // on met la couleur rouge de l'image en haut a droite
            niveau = fichier->image[i][j].g;                                                  // on recupere la couleur verte
            fichier->image[i][j].g = fichier->image[i][fichier->entetebmp.largeur - 1 - j].g; // on met la couleur verte de l'image en bas a gauche
            fichier->image[i][fichier->entetebmp.largeur - 1 - j].g = niveau;                 // on met la couleur verte de l'image en haut a droite
            niveau = fichier->image[i][j].b;                                                  // on recupere la couleur bleue
            fichier->image[i][j].b = fichier->image[i][fichier->entetebmp.largeur - 1 - j].b; // on met la couleur bleue de l'image en bas a gauche
            fichier->image[i][fichier->entetebmp.largeur - 1 - j].b = niveau;                 // on met la couleur bleue de l'image en haut a droite
        }
    }
    // Enregistrement de l'image et affichage de l'image
    sprintf(nomEnregistrement, "./res/%s_image_mirroir%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_mirroir%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_mirroir%s", nom, extension);
    system(nomEnregistrement);
}

// fonction permettant de cr??er une image symetrique
void imageVersSymetrie(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100]; // nom de l'image enregistrer
    char extension[5] = ".bmp";  // extension de l'image enregistrer
    // --------------------------------------------------
    int i, j; // compteur

    for (int i = 0; i < fichier->entetebmp.largeur; i++) {
        for (int j = 0; j < fichier->entetebmp.hauteur; j++) {
            fichier->image[i][j].r = fichier->image[i][fichier->entetebmp.hauteur - j].r;
            fichier->image[i][j].g = fichier->image[i][fichier->entetebmp.hauteur - j].g;
            fichier->image[i][j].b = fichier->image[i][fichier->entetebmp.hauteur - j].b;
        }
    }
    // Enregistrement de l'image et affichage de l'image
    sprintf(nomEnregistrement, "./res/%s_image_symetrie%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_symetrie%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_symetrie%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// fonction permetant de pivoter une image de 90?? ?? gauche
void pivoterImageGauche(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    struct pixels pixel;

    for (i = 0; i < fichier->entetebmp.largeur / 2; i++) {
        for (j = 0; j < fichier->entetebmp.hauteur / 2; j++) {
            pixel = fichier->image[i][j];
            fichier->image[i][j] = fichier->image[j][fichier->entetebmp.largeur - i];
            fichier->image[j][fichier->entetebmp.largeur - i] = fichier->image[fichier->entetebmp.largeur - i][fichier->entetebmp.hauteur - j];
            fichier->image[fichier->entetebmp.largeur - i][fichier->entetebmp.hauteur - j] = fichier->image[fichier->entetebmp.largeur - j][i];
            fichier->image[fichier->entetebmp.largeur - j][i] = pixel;
        }
    }

    sprintf(nomEnregistrement, "./res/%s_image_pivoter_gauche%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_pivoter_gauche%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_pivoter_gauche%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// fonction permetant de pivoter une image de 90?? ?? droite
void pivoterImageDroite(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    struct pixels pixel;

    for (i = 0; i < fichier->entetebmp.largeur / 2; i++) {
        for (j = 0; j < fichier->entetebmp.hauteur / 2; j++) {
            pixel = fichier->image[i][j]; //
            fichier->image[i][j] = fichier->image[fichier->entetebmp.largeur - j][i];
            fichier->image[fichier->entetebmp.largeur - j][i] = fichier->image[fichier->entetebmp.largeur - i][fichier->entetebmp.hauteur - j];
            fichier->image[fichier->entetebmp.largeur - i][fichier->entetebmp.hauteur - j] = fichier->image[j][fichier->entetebmp.largeur - i];
            fichier->image[j][fichier->entetebmp.largeur - i] = pixel;
        }
    }

    sprintf(nomEnregistrement, "./res/%s_image_pivoter_droite%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_pivoter_droite%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_pivoter_droite%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Calcul du pourcentage de couleur d'une image (RVB), teine, saturation et luminance

// Cr??ation d'une image n??gative
void imageNegative(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier->image[i][j].r = 255 - fichier->image[i][j].r;
            fichier->image[i][j].g = 255 - fichier->image[i][j].g;
            fichier->image[i][j].b = 255 - fichier->image[i][j].b;
        }
    }

    sprintf(nomEnregistrement, "./res/%s_image_negative%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_negative%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_negative%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Seuillage d'une image
void seuillage(struct fichierimage *fichier, char nom[50], int seuil) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            if (fichier->image[i][j].r < seuil) {
                fichier->image[i][j].r = 0;
            } else {
                fichier->image[i][j].r = 255;
            }

            if (fichier->image[i][j].g < seuil) {
                fichier->image[i][j].g = 0;
            } else {
                fichier->image[i][j].g = 255;
            }

            if (fichier->image[i][j].b < seuil) {
                fichier->image[i][j].b = 0;
            } else {
                fichier->image[i][j].b = 255;
            }
        }
    }

    sprintf(nomEnregistrement, "./res/%s_image_seuillage%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_seuillage%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_seuillage%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Inversion des couleurs d'une image
void inversionCouleur(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;

    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier2->image[i][j].r = fichier->image[i][j].b;
            fichier2->image[i][j].g = fichier->image[i][j].r;
            fichier2->image[i][j].b = fichier->image[i][j].g;
        }
    }

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier->image[i][j].r = fichier2->image[i][j].r;
            fichier->image[i][j].g = fichier2->image[i][j].g;
            fichier->image[i][j].b = fichier2->image[i][j].b;
        }
    }

    sprintf(nomEnregistrement, "./res/%s_image_inversion_couleur%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_inversion_couleur%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_inversion_couleur%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// R??duction d'une image (changement d'??chelle)
void reductionImage(struct fichierimage *fichier, char nom[50], int echelle) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur / echelle, fichier->entetebmp.largeur / echelle);

    for (i = 0; i < fichier->entetebmp.hauteur; i += echelle) {
        for (j = 0; j < fichier->entetebmp.largeur; j += echelle) {
            fichier2->image[i / echelle][j / echelle].r = fichier->image[i][j].r;
            fichier2->image[i / echelle][j / echelle].g = fichier->image[i][j].g;
            fichier2->image[i / echelle][j / echelle].b = fichier->image[i][j].b;
        }
    }
    sprintf(nomEnregistrement, "./res/%s_image_reduction_echelle_%d%s", nom, echelle, extension);
    enregistrer(nomEnregistrement, fichier2);
    // sprintf(nomEnregistrement, "open ./res/%s_image_reduction_echelle_%d%s", nom, echelle,extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_reduction_echelle_%d%s", nom, echelle, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Agrandissement d'une image (changement d'??chelle)
void agrandissementImage(struct fichierimage *fichier, char nom[50], int echelle) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur * echelle, fichier->entetebmp.largeur * echelle);

    for (i = 1; i < fichier->entetebmp.hauteur; i++) {
        for (j = 1; j < fichier->entetebmp.largeur; j++) {

            for (int k = 0; k < echelle; k++) {
                for (int l = 0; l < echelle; l++) {
                    fichier2->image[i * echelle + k][j * echelle + l].r = fichier->image[i][j].r;
                    fichier2->image[i * echelle + k][j * echelle + l].g = fichier->image[i][j].g;
                    fichier2->image[i * echelle + k][j * echelle + l].b = fichier->image[i][j].b;
                }
            }
        }
    }
    sprintf(nomEnregistrement, "./res/%s_image_agrandissement_echelle_%d%s", nom, echelle, extension);
    enregistrer(nomEnregistrement, fichier2);
    // sprintf(nomEnregistrement, "open ./res/%s_image_agrandissement_echelle_%d%s", nom, echelle, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_agrandissement_echelle_%d%s", nom, echelle, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Transformation d'une image en monochrome.
void monochromeImage(struct fichierimage *fichier, char nom[50], char couleur) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;

    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            if (couleur == 'r' || couleur == 'R') {
                fichier2->image[i][j].r = fichier->image[i][j].r;
                fichier2->image[i][j].g = 0;
                fichier2->image[i][j].b = 0;
            } else if (couleur == 'g' || couleur == 'v' || couleur == 'G' || couleur == 'V') {
                fichier2->image[i][j].r = 0;
                fichier2->image[i][j].g = fichier->image[i][j].g;
                fichier2->image[i][j].b = 0;
            } else if (couleur == 'b' || couleur == 'B') {
                fichier2->image[i][j].r = 0;
                fichier2->image[i][j].g = 0;
                fichier2->image[i][j].b = fichier->image[i][j].b;
            }
        }
    }
    sprintf(nomEnregistrement, "./res/%s_image_monochrome_%c%s", nom, couleur, extension);
    enregistrer(nomEnregistrement, fichier2);
    // sprintf(nomEnregistrement, "open ./res/%s_image_monochrome_%c%s", nom, couleur, extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_monochrome_%c%s", nom, couleur, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Convolutions d'une image avec un masque de convolution.
void convolution(struct fichierimage *fichier, char nom[50], int matrice[3][3], int diviseur) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j, k, l;
    int niveau;
    int niveauR, niveauG, niveauB;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            niveauR = 0;
            niveauG = 0;
            niveauB = 0;
            for (k = -1; k <= 1; k++) {
                for (l = -1; l <= 1; l++) {
                    if (i + k >= 0 && i + k < fichier->entetebmp.hauteur && j + l >= 0 && j + l < fichier->entetebmp.largeur) {
                        niveauR += fichier->image[i + k][j + l].r * matrice[k + 1][l + 1];
                        niveauG += fichier->image[i + k][j + l].g * matrice[k + 1][l + 1];
                        niveauB += fichier->image[i + k][j + l].b * matrice[k + 1][l + 1];
                    }
                }
            }

            // Normalisation de l'image en fonction de la matrice de convolution
            niveauR = niveauR / diviseur;
            niveauG = niveauG / diviseur;
            niveauB = niveauB / diviseur;

            // Affectation des niveaux de l'image
            fichier->image[i][j].r = niveauR;
            fichier->image[i][j].g = niveauG;
            fichier->image[i][j].b = niveauB;
        }
    }
    sprintf(nomEnregistrement, "./res/%s_image_convolution_%d%s", nom, matrice[1][1], extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_convolution_%d%s", nom, matrice[1][1], extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_convolution_%d%s", nom, matrice[1][1], extension);
    system(nomEnregistrement);
    free(fichier);
}

// Filtrage de l'image par un masque de convolution (matrice 3x3)
void filtreImage(struct fichierimage *fichier, char nom[50], int masque[3][3]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j, k, l;
    int sommeR, sommeG, sommeB;
    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    for (i = 1; i < fichier->entetebmp.hauteur - 1; i++) {
        for (j = 1; j < fichier->entetebmp.largeur - 1; j++) {
            sommeR = 0;
            sommeG = 0;
            sommeB = 0;

            for (k = -1; k <= 1; k++) {
                for (l = -1; l <= 1; l++) {
                    sommeR += masque[k + 1][l + 1] * fichier->image[i + k][j + l].r;
                    sommeG += masque[k + 1][l + 1] * fichier->image[i + k][j + l].g;
                    sommeB += masque[k + 1][l + 1] * fichier->image[i + k][j + l].b;
                }
            }

            if (sommeR > 255) {
                fichier2->image[i][j].r = 255;
            } else if (sommeR < 0) {
                fichier2->image[i][j].r = 0;
            } else {
                fichier2->image[i][j].r = sommeR;
            }

            if (sommeG > 255) {
                fichier2->image[i][j].g = 255;
            } else if (sommeG < 0) {
                fichier2->image[i][j].g = 0;
            } else {
                fichier2->image[i][j].g = sommeG;
            }

            if (sommeB > 255) {
                fichier2->image[i][j].b = 255;
            } else if (sommeB < 0) {
                fichier2->image[i][j].b = 0;
            } else {
                fichier2->image[i][j].b = sommeB;
            }
        }
    }

    sprintf(nomEnregistrement, "./res/%s_image_filtre_%d%s", nom, masque[1][1], extension);
    enregistrer(nomEnregistrement, fichier2);
    // sprintf(nomEnregistrement, "open ./res/%s_image_filtre_%d%s", nom, masque[1][1], extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_filtre_%d%s", nom, masque[1][1], extension);
    system(nomEnregistrement);
    free(fichier);
}

// Supperposition d'images (fusion de deux images)
void supperposition(struct fichierimage *fichier1, struct fichierimage *fichier2, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    struct fichierimage *fichier3 = nouveau(fichier1->entetebmp.hauteur, fichier1->entetebmp.largeur);

    //
    for (i = 0; i < fichier1->entetebmp.hauteur; i++) {                                        // i = ligne
        for (j = 0; j < fichier1->entetebmp.largeur; j++) {                                    // j = colonne
            fichier3->image[i][j].r = (fichier1->image[i][j].r + fichier2->image[i][j].r) / 2; // moyenne des niveaux de rouge
            fichier3->image[i][j].g = (fichier1->image[i][j].g + fichier2->image[i][j].g) / 2; // moyenne des niveaux de vert
            fichier3->image[i][j].b = (fichier1->image[i][j].b + fichier2->image[i][j].b) / 2; // moyenne des niveaux de bleu
        }
    }

    sprintf(nomEnregistrement, "./res/%s_supperposition%s", nom, extension);
    enregistrer(nomEnregistrement, fichier3);
    // sprintf(nomEnregistrement, "open ./res/%s_supperposition%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_supperposition%s", nom, extension);
    system(nomEnregistrement);
}

// Supperposition d'une image sur une autre (fusion de deux images) Cette fonction est pas appel?? dans le main
void superpositionImage(struct fichierimage *fichier, struct fichierimage *fichier2, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;

    struct fichierimage *fichier3 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    // On parcourt les pixels de l'image
    for (i = 0; i < fichier->entetebmp.hauteur; i++) {     // Parcours de l'image
        for (j = 0; j < fichier->entetebmp.largeur; j++) { // Parcours de l'image
            // On calcule la superposition des niveaux de l'image
            fichier3->image[i][j].r = fichier->image[i][j].r; // On affecte les niveaux de l'image 1
            fichier3->image[i][j].g = fichier->image[i][j].g;
            fichier3->image[i][j].b = fichier->image[i][j].b;
        }
    }

    // On parcourt les pixels de l'image2
    for (i = 0; i < fichier2->entetebmp.hauteur; i++) {     // Parcours de l'image
        for (j = 0; j < fichier2->entetebmp.largeur; j++) { // Parcours de l'image
            // On calcule la superposition des niveaux de l'image2
            fichier3->image[i][j].r = fichier2->image[i][j].r; // On affecte les niveaux de l'image 2
            fichier3->image[i][j].g = fichier2->image[i][j].g;
            fichier3->image[i][j].b = fichier2->image[i][j].b;
        } // Fin de la boucle de parcours de l'image
    }     // Fin de la boucle de parcours de l'image

    // On enregistre l'image
    sprintf(nomEnregistrement, "./res/%s_sup                    erpositionImage%s", nom, extension);
    enregistrer(nomEnregistrement, fichier3);
    // sprintf(nomEnregistrement, "open ./res/%s_superpositionImage%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_superpositionImage%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Rotation d'une image d'un angle donn?? en degr??s
void rotationImage(struct fichierimage *fichier, char nom[50], int angle) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;

    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier2->image[i][j].r = fichier->image[i][j].r;
            fichier2->image[i][j].g = fichier->image[i][j].g;
            fichier2->image[i][j].b = fichier->image[i][j].b;
        }
    }

    double angleRad = angle * M_PI / 180;

    double cosinus = cos(angleRad);
    double sinus = sin(angleRad);

    double x, y;
    int x2, y2;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            x = i - (fichier->entetebmp.hauteur / 2);
            y = j - (fichier->entetebmp.largeur / 2);

            x2 = (x * cosinus) - (y * sinus) + (fichier->entetebmp.hauteur / 2);
            y2 = (x * sinus) + (y * cosinus) + (fichier->entetebmp.largeur / 2);

            if (x2 < 0 || x2 >= fichier->entetebmp.hauteur || y2 < 0 || y2 >= fichier->entetebmp.largeur) {
                fichier2->image[i][j].r = 0;
                fichier2->image[i][j].g = 0;
                fichier2->image[i][j].b = 0;
            } else {
                fichier2->image[i][j].r = fichier->image[x2][y2].r;
                fichier2->image[i][j].g = fichier->image[x2][y2].g;
                fichier2->image[i][j].b = fichier->image[x2][y2].b;
            }
        }
    }

    sprintf(nomEnregistrement, "./res/%s_rotation_%d??%s", nom, angle, extension);
    enregistrer(nomEnregistrement, fichier2);
    // sprintf(nomEnregistrement, "open ./res/%s_rotation_%d??%s", nom, angle, extension);
    sprintf(nomEnregistrement, "start ./res/%s_rotation_%d??%s", nom, angle, extension);
    system(nomEnregistrement);
    free(fichier2);
}

// r??duire le bruit de l'image
void reductionBruite(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    int niveauR, niveauG, niveauB;

    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    // On parcourt les pixels de l'image
    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            niveauR = 0;
            niveauG = 0;
            niveauB = 0;

            if (i - 1 >= 0) {
                niveauR += fichier->image[i - 1][j].r;
                niveauG += fichier->image[i - 1][j].g;
                niveauB += fichier->image[i - 1][j].b;
            }
            if (i + 1 < fichier->entetebmp.hauteur) {
                niveauR += fichier->image[i + 1][j].r;
                niveauG += fichier->image[i + 1][j].g;
                niveauB += fichier->image[i + 1][j].b;
            }
            if (j - 1 >= 0) {
                niveauR += fichier->image[i][j - 1].r;
                niveauG += fichier->image[i][j - 1].g;
                niveauB += fichier->image[i][j - 1].b;
            }
            if (j + 1 < fichier->entetebmp.largeur) {
                niveauR += fichier->image[i][j + 1].r;
                niveauG += fichier->image[i][j + 1].g;
                niveauB += fichier->image[i][j + 1].b;
            }
            if (i - 1 >= 0 && j - 1 >= 0) {
                niveauR += fichier->image[i - 1][j - 1].r;
                niveauG += fichier->image[i - 1][j - 1].g;
                niveauB += fichier->image[i - 1][j - 1].b;
            }
            if (i - 1 >= 0 && j + 1 < fichier->entetebmp.largeur) {
                niveauR += fichier->image[i - 1][j + 1].r;
                niveauG += fichier->image[i - 1][j + 1].g;
                niveauB += fichier->image[i - 1][j + 1].b;
            }
            if (i + 1 < fichier->entetebmp.hauteur && j - 1 >= 0) {
                niveauR += fichier->image[i + 1][j - 1].r;
                niveauG += fichier->image[i + 1][j - 1].g;
                niveauB += fichier->image[i + 1][j - 1].b;
            }
            if (i + 1 < fichier->entetebmp.hauteur && j + 1 < fichier->entetebmp.largeur) {
                niveauR += fichier->image[i + 1][j + 1].r;
                niveauG += fichier->image[i + 1][j + 1].g;
                niveauB += fichier->image[i + 1][j + 1].b;
            }

            fichier2->image[i][j].r = niveauR / 9;
            fichier2->image[i][j].g = niveauG / 9;
            fichier2->image[i][j].b = niveauB / 9;
        }
    }

    sprintf(nomEnregistrement, "./res/%s_reduction_bruite%s", nom, extension);
    enregistrer(nomEnregistrement, fichier2);
    // sprintf(nomEnregistrement, "open ./res/%s_reduction_bruite%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_reduction_bruite%s", nom, extension);
    system(nomEnregistrement);
    free(fichier2);
}

// modification de la luminance d'une image en couleur (0-100)
void modifLuminanceImage(struct fichierimage *fichier, char nom[50], int luminance) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    int niveauR, niveauG, niveauB;

    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            niveauR = fichier->image[i][j].r * luminance / 100;
            niveauG = fichier->image[i][j].g * luminance / 100;
            niveauB = fichier->image[i][j].b * luminance / 100;

            fichier2->image[i][j].r = niveauR;
            fichier2->image[i][j].g = niveauG;
            fichier2->image[i][j].b = niveauB;
        }
    }

    sprintf(nomEnregistrement, "./res/%s_luminance_%d_percent%s", nom, luminance, extension);
    enregistrer(nomEnregistrement, fichier2);
    // sprintf(nomEnregistrement, "open ./res/%s_luminance_%d_percent%s", nom,luminance, extension);
    sprintf(nomEnregistrement, "start ./res/%s_luminance_%d_percent%s", nom, luminance, extension);
    system(nomEnregistrement);
    free(fichier2);
}

// retourner les informations relative ?? l'image
void informationSurImage(struct fichierimage *fichier) {

    int choix = 3;

    while (choix != 0) {
        printf("\n\n Qu'elle information sur l'image voulez vous ?");
        printf("\n  1. Information sur l'entete du fichier");
        printf("\n  2. Information sur l'entete de l'image");
        printf("\n  0. Retour Menu Principal");

        printf("\n\n Choix : ");
        scanf("%d", &choix);

        system("clear");
        system("cls");
        if (choix == 1) {
            // lecture de l'ente du fichier
            int choix1 = 2;

            while (choix1 != 0) {
                printf("\n\n Quelle information sur l'entete voulez vous ?");
                printf("\n  1. Taille du fichier");
                printf("\n  0. Retour");

                printf("\n\n Choix : ");
                scanf("%d", &choix1);

                system("clear");
                system("cls");

                if (choix1 == 1) {
                    printf("\n\n Taille du fichier : %d octets", fichier->entetefichier.taille_fichier);
                    // printf("taille fichier           :%d\n", fichier->entetefichier.taille_fichier);
                } else if (choix1 == 0) {
                    printf("\n\n Retour au menu principal");
                } else {
                    printf("\n\n Choix invalide");
                }
            }
        } else if (choix == 2) {
            // lecture de l'ente de l'image
            int choix2 = 10;
            while (choix2 != 0) {
                printf("\n\n Qu'elle information sur l'image voulez vous ?");
                printf("\n  1. taille de l'image");
                printf("\n  2. largeur de l'image");
                printf("\n  3. hauteur de l'image");
                printf("\n  0. Retour");

                printf("\nVotre choix : ");
                scanf("%d", &choix2);

                system("clear");
                system("cls");

                if (choix2 == 1) {
                    // printf("taille de l'image : %d", fichier->entetebmp.taille_image);
                    printf("taille image             :%d\n", fichier->entetebmp.taille_image);
                } else if (choix2 == 2) {
                    // printf("largeur de l'image : %d", fichier->entetebmp.largeur);
                    printf("largeur                  :%d\n", fichier->entetebmp.largeur);
                } else if (choix2 == 3) {
                    // printf("hauteur de l'image : %d", fichier->entetebmp.hauteur);
                    printf("hauteur                  :%d\n", fichier->entetebmp.hauteur);
                } else if (choix2 == 0) {
                    printf("Au revoir  \n");
                } else {
                    printf("\n  erreur");
                }
            }
        } else if (choix == 0) {
            printf("Bye \n");
        } else {
            printf("Erreur de saisie \n");
        }
    }
}

// S??lectionner une portion de l'image avec les cordonn??es entr??es par l'utilisateur
void selectionnerZone(struct fichierimage *fichier, char nom[50], int x, int y, int x2, int y2) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    int x1, y1;

    int x4, y4;

    x1 = x;
    y1 = y;
    fichier->entetebmp.largeur = x2;
    fichier->entetebmp.hauteur = y2;

    // si x1 est plus grand que la largeur de l'image alors on met x1 ?? la largeur de l'image (pour ne pas d??passer)
    if (x1 > fichier->entetebmp.largeur) {
        x4 = x1;
        x1 = fichier->entetebmp.largeur;
        fichier->entetebmp.largeur = x4;
    }

    // si y1 est plus grand que la hauteur de l'image alors on change la hauteur de l'image par la hauteur de y1 (pour ne pas d??passer)
    if (y1 > fichier->entetebmp.hauteur) {
        y4 = y1;
        y1 = fichier->entetebmp.hauteur;
        fichier->entetebmp.hauteur = y4;
    }

    // cr??ation d'un nouveau fichier image avec les dimensions de la zone s??lectionn??e
    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur - y1, fichier->entetebmp.largeur - x1);

    for (i = y1; i < fichier->entetebmp.hauteur; i++) {                 // i = ligne
        for (j = x1; j < fichier->entetebmp.largeur; j++) {             // j = colonne
            fichier2->image[i - y1][j - x1].r = fichier->image[i][j].r; // copie de la couleur de l'image dans la nouvelle image
            fichier2->image[i - y1][j - x1].g = fichier->image[i][j].g; // copie de la couleur de l'image dans la nouvelle image
            fichier2->image[i - y1][j - x1].b = fichier->image[i][j].b; // copie de la couleur de l'image dans la nouvelle image
        }                                                               // fin de la boucle de copie
    }                                                                   // fin de la boucle for

    // rectifier la taille de l'image
    fichier2->entetebmp.largeur = fichier->entetebmp.largeur - x1;
    fichier2->entetebmp.hauteur = fichier->entetebmp.hauteur - y1;

    sprintf(nomEnregistrement, "./res/%s_selection_%d_%d_%d_%d.bmp", nom, x, y, x2, y2);
    enregistrer(nomEnregistrement, fichier2);
    // sprintf(nomEnregistrement, "open ./res/%s_selection_%d_%d_%d_%d.bmp",nom, x, y, x2, y2);
    sprintf(nomEnregistrement, "start ./res/%s_selection_%d_%d_%d_%d.bmp", nom, x, y, x2, y2);
    system(nomEnregistrement);
    free(fichier2);
}

// Calcul de l'histogramme d'une image.
void calculHistogramme(struct fichierimage *fichier) {
    int i, j;
    int r, g, b;
    int histoR[256];
    int histoG[256];
    int histoB[256];
    int maxR = 0;
    int maxG = 0;
    int maxB = 0;
    int max = 0;
    int choix = 6;

    // initialisation des tableaux ?? 0 pour les histogrammes
    for (i = 0; i < 256; i++) {
        histoR[i] = 0;
        histoG[i] = 0;
        histoB[i] = 0;
    }

    // calcul des histogrammes
    for (i = 0; i < fichier->entetebmp.hauteur; i++) {     // i = ligne
        for (j = 0; j < fichier->entetebmp.largeur; j++) { // j = colonne
            // copie de la couleur de l'image dans la nouvelle image
            r = fichier->image[i][j].r;
            g = fichier->image[i][j].g;
            b = fichier->image[i][j].b;

            // ajout d'un pixel dans le tableau de l'histogramme
            histoR[r]++;
            histoG[g]++;
            histoB[b]++;
        }
    }

    for (i = 0; i < 256; i++) { // i = ligne
        // si le nombre de pixel de l'histogramme est plus grand que le max alors on met le max ?? la valeur de l'histogramme actuel
        if (histoR[i] > maxR) {
            maxR = histoR[i];
        }
        if (histoG[i] > maxG) {
            maxG = histoG[i];
        }
        if (histoB[i] > maxB) {
            maxB = histoB[i];
        }
    }

    // on met le max ?? la valeur du max de l'histogramme de la couleur rouge (car on veut que les histogrammes soient de m??me taille)
    max = maxR;
    // si le max de l'histogramme de la couleur verte est plus grand que le max alors on met le max ?? la valeur de l'histogramme actuel
    if (maxG > max) {
        max = maxG;
    }
    // si le max de l'histogramme de la couleur bleue est plus grand que le max alors on met le max ?? la valeur de l'histogramme actuel
    if (maxB > max) {
        max = maxB;
    }

    printf("\n\n              Histogramme de l'image\n\n");

    // affichage des histogrammes
    while (choix != 0) {
        printf("Merci de bien voulori choisir l'action ?? effectuer");
        printf("\n  1. Histogramme R");
        printf("\n  2. Histogramme G");
        printf("\n  3. Histogramme V");
        printf("\n  4. Histogramme R G B");
        printf("\n  0. Retour au menu principal ");

        printf("\n\n  Votre choix : ");
        scanf("%d", &choix);

        system("clear");
        system("cls");

        printf("\n\n\n\n");

        if (choix == 1) {
            printf("\n\n R : ");
            for (i = 0; i < 256; i++) {
                printf("%d ", histoR[i]);
            }
            printf("\n\n");
        } else if (choix == 2) {
            printf("\n\n G : ");
            for (i = 0; i < 256; i++) {
                printf("%d ", histoG[i]);
            }
            printf("\n\n");
        } else if (choix == 3) {
            printf("\n\n B : ");
            for (i = 0; i < 256; i++) {
                printf("%d ", histoB[i]);
            }
            printf("\n\n");
        } else if (choix == 4) {
            printf("\n\n R : ");
            for (i = 0; i < 256; i++) {
                printf("%d ", histoR[i]);
            }
            printf("\n\n G : ");
            for (i = 0; i < 256; i++) {
                printf("%d ", histoG[i]);
            }
            printf("\n\n B : ");
            for (i = 0; i < 256; i++) {
                printf("%d ", histoB[i]);
            }
            printf("\n\n");
        } else if (choix == 0) {
            printf("\n\n Retour au menu principal \n\n");
        } else {
            printf("\n\n Choix incorrect \n\n");
        }
    }

    free(fichier);
}

// fonction permettant de faire un filtre laplacien
void filtreLaplacien(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100]; // nom de l'image enregistrer
    char extension[5] = ".bmp";  // extension de l'image enregistrer
    // --------------------------------------------------
    int i, j, k, l;
    int somme;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            somme = 0;
            for (k = -1; k < 2; k++) {
                for (l = -1; l < 2; l++) {
                    if (i + k >= 0 && i + k < fichier->entetebmp.hauteur && j + l >= 0 && j + l < fichier->entetebmp.largeur) {
                        somme += fichier->image[i + k][j + l].r;
                    }
                }
            }
            somme -= fichier->image[i][j].r;
            if (somme > 255) {
                fichier->image[i][j].r = 255;
            } else if (somme < 0) {
                fichier->image[i][j].r = 0;
            } else {
                fichier->image[i][j].r = somme;
            }
        }
    }
    // Enregistrement de l'image et affichage de l'image
    sprintf(nomEnregistrement, "./res/%s_filtre_laplacien%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_filtre_laplacien%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_filtre_laplacien%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Filtre moyenneur sur une image.
void filtreMoyenneur(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    int r, g, b;
    int moyenneR = 0;
    int moyenneG = 0;
    int moyenneB = 0;
    int choix = 6;
    int taille = 3;

    // initialisation des tableaux ?? 0 pour les histogrammes
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            moyenneR += fichier->image[i][j].r;
            moyenneG += fichier->image[i][j].g;
            moyenneB += fichier->image[i][j].b;
        }
    }

    moyenneR = moyenneR / (taille * taille);
    moyenneG = moyenneG / (taille * taille);
    moyenneB = moyenneB / (taille * taille);

    printf("\n\n              Filtre moyenneur\n\n");

    while (choix != 0) { // tant que l'utilisateur n'a pas choisi de retourner au menu principal
        printf("Merci de bien voulori choisir l'action ?? effectuer");
        printf("\n  1. Filtre moyenneur R");
        printf("\n  2. Filtre moyenneur G");
        printf("\n  3. Filtre moyenneur B");
        printf("\n  4. Filtre moyenneur R G B");
        printf("\n  0. Retour au menu principal ");

        printf("\n\n  Votre choix : ");
        scanf("%d", &choix);

        system("clear");
        system("cls");

        printf("\n\n\n\n");

        if (choix == 1) { // si l'utilisateur a choisi de filtrer l'image en rouge
            printf("\n\nR : %d Image filtr??e en rouge \n", moyenneR);
            // Enregistrement de l'image filtr??e
            for (i = 0; i < fichier->entetebmp.hauteur; i++) {
                for (j = 0; j < fichier->entetebmp.largeur; j++) {
                    fichier->image[i][j].r = moyenneR;
                }
            }
            sprintf(nomEnregistrement, "./res/%s_filtreMoyenneur_R%s", nom, extension);
            enregistrer(nomEnregistrement, fichier);
            // sprintf(nomEnregistrement, "open ./res/%s_filtreMoyenneur_R%s", nom, extension);
            sprintf(nomEnregistrement, "start ./res/%s_filtreMoyenneur_R%s", nom, extension);
            system(nomEnregistrement);

            // renitialisation apr??s chaque filtre moyenneur pour ??viter les erreurs de m??lange
            for (i = 0; i < taille; i++) {
                for (j = 0; j < taille; j++) {
                    moyenneR = 0;
                    moyenneG = 0;
                    moyenneB = 0;
                }
            }
        } else if (choix == 2) { // si l'utilisateur a choisi de filtrer l'image en vert
            printf("\n\nV : %d Image filtr??e en vert \n", moyenneG);
            // Enregistrement de l'image filtr??e
            for (i = 0; i < fichier->entetebmp.hauteur; i++) {
                for (j = 0; j < fichier->entetebmp.largeur; j++) {
                    fichier->image[i][j].g = moyenneG;
                }
            }
            sprintf(nomEnregistrement, "./res/%s_filtreMoyenneur_G%s", nom, extension);
            enregistrer(nomEnregistrement, fichier);
            // sprintf(nomEnregistrement, "open ./res/%s_filtreMoyenneur_G%s", nom, extension);
            sprintf(nomEnregistrement, "start ./res/%s_filtreMoyenneur_G%s", nom, extension);
            system(nomEnregistrement);

            // renitialisation apr??s chaque filtre moyenneur pour ??viter les erreurs de m??lange
            for (i = 0; i < taille; i++) {
                for (j = 0; j < taille; j++) {
                    moyenneR = 0;
                    moyenneG = 0;
                    moyenneB = 0;
                }
            }
        } else if (choix == 3) {
            printf("\n\nB : %d Image filtr??e en bleu \n", moyenneB);
            // Enregistrement de l'image filtr??e
            for (i = 0; i < fichier->entetebmp.hauteur; i++) {
                for (j = 0; j < fichier->entetebmp.largeur; j++) {
                    fichier->image[i][j].b = moyenneB;
                }
            }
            sprintf(nomEnregistrement, "./res/%s_filtreMoyenneur_B%s", nom, extension);
            enregistrer(nomEnregistrement, fichier);
            // sprintf(nomEnregistrement, "open ./res/%s_filtreMoyenneur_B%s", nom, extension);
            sprintf(nomEnregistrement, "start ./res/%s_filtreMoyenneur_B%s", nom, extension);
            system(nomEnregistrement);

            // renitialisation apr??s chaque filtre moyenneur pour ??viter les erreurs de m??lange
            for (i = 0; i < taille; i++) {
                for (j = 0; j < taille; j++) {
                    moyenneR = 0;
                    moyenneG = 0;
                    moyenneB = 0;
                }
            }
        } else if (choix == 4) { // si l'utilisateur a choisi de filtrer l'image en rouge et vert et bleu
            printf("\n\nR : %d Image filtr??e en rouge \n", moyenneR);
            printf("\n\nV : %d Image filtr??e en vert \n", moyenneG);
            printf("\n\nB : %d Image filtr??e en bleu \n", moyenneB);

            // Enregistrement de l'image filtr??e
            for (i = 0; i < fichier->entetebmp.hauteur; i++) {
                for (j = 0; j < fichier->entetebmp.largeur; j++) {
                    fichier->image[i][j].r = moyenneR;
                    fichier->image[i][j].g = moyenneG;
                    fichier->image[i][j].b = moyenneB;
                }
            }
            sprintf(nomEnregistrement, "./res/%s_filtreMoyenneur_R_G_B%s", nom, extension);
            enregistrer(nomEnregistrement, fichier);
            // sprintf(nomEnregistrement, "open ./res/%s_filtreMoyenneur_R_G_B%s", nom, extension);
            sprintf(nomEnregistrement, "start ./res/%s_filtreMoyenneur_R_G_B%s", nom, extension);
            system(nomEnregistrement);

            // renitialisation apr??s chaque filtre moyenneur pour ??viter les erreurs de m??lange
            for (i = 0; i < taille; i++) {
                for (j = 0; j < taille; j++) {
                    moyenneR = 0;
                    moyenneG = 0;
                    moyenneB = 0;
                }
            }

        } else if (choix == 0) {
            printf("\n\nRetour au menu principal");
        } else {
            printf("\n\n Choix incorrect \n\n");
        }
    }
    free(fichier);
}

// Histogramme de l'image et egalisation de l'image
void histogrammeEgalisation(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    int r, g, b;
    int histoR[256];
    int histoG[256];
    int histoB[256];
    int maxR = 0;
    int maxG = 0;
    int maxB = 0;
    int max = 0;
    int choix = 6;

    // initialisation des tableaux ?? 0 pour les histogrammes
    for (i = 0; i < 256; i++) {
        histoR[i] = 0;
        histoG[i] = 0;
        histoB[i] = 0;
    }

    // calcul des histogrammes
    for (i = 0; i < fichier->entetebmp.hauteur; i++) {     // i = ligne
        for (j = 0; j < fichier->entetebmp.largeur; j++) { // j = colonne
            // copie de la couleur de l'image dans la nouvelle image
            r = fichier->image[i][j].r;
            g = fichier->image[i][j].g;
            b = fichier->image[i][j].b;

            // ajout d'un pixel dans le tableau de l'histogramme
            histoR[r]++;
            histoG[g]++;
            histoB[b]++;
        }
    }

    for (i = 0; i < 256; i++) { // i = ligne
        // si le nombre de pixel de l'histogramme est plus grand que le max alors on met le max ?? la valeur de l'histogramme actuel
        if (histoR[i] > maxR) {
            maxR = histoR[i];
        }
        if (histoG[i] > maxG) {
            maxG = histoG[i];
        }
        if (histoB[i] > maxB) {
            maxB = histoB[i];
        }
    }

    // on met le max ?? la valeur du max de l'histogramme de la couleur rouge (car on veut que les histogrammes soient de m??me taille)
    max = maxR;
    // si le max de l'histogramme de la couleur verte est plus grand que le max alors on met le max ?? la valeur de l'histogramme actuel
    if (maxG > max) {
        max = maxG;
    }
    // si le max de l'histogramme de la couleur bleue est plus grand que le max alors on met le max ?? la valeur de l'histogramme actuel
    if (maxB > max) {
        max = maxB;
    }

    // Egalisation de l'histogramme de l'image
    for (i = 0; i < fichier->entetebmp.hauteur; i++) {     // i = ligne
        for (j = 0; j < fichier->entetebmp.largeur; j++) { // j = colonne
            // copie de la couleur de l'image dans la nouvelle image
            r = fichier->image[i][j].r;
            g = fichier->image[i][j].g;
            b = fichier->image[i][j].b;

            // calcul de la nouvelle valeur de l'image
            fichier->image[i][j].r = (int)((r * 255) / max);
            fichier->image[i][j].g = (int)((g * 255) / max);
            fichier->image[i][j].b = (int)((b * 255) / max);
        }
    }

    // Enregistrement de l'image ??galis??e
    sprintf(nomEnregistrement, "./res/%s_histo_egalisation%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_histo_egalisation%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_histo_egalisation%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Passage d'une image RVB ?? TSL enregistement de l'image convertie
void passageRVBTsl(struct fichierimage *fichier, char nom[50]) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    int r, g, b;
    int rTsl, gTsl, bTsl;

    // Passage d'une image RVB ?? TSL
    for (i = 0; i < fichier->entetebmp.hauteur; i++) {     // i = ligne
        for (j = 0; j < fichier->entetebmp.largeur; j++) { // j = colonne
            // copie de la couleur de l'image dans la nouvelle image
            r = fichier->image[i][j].r;
            g = fichier->image[i][j].g;
            b = fichier->image[i][j].b;

            // calcul de la nouvelle valeur de l'image
            rTsl = (int)(0.299 * r + 0.587 * g + 0.114 * b);
            gTsl = (int)(0.596 * r - 0.274 * g - 0.322 * b);
            bTsl = (int)(0.211 * r - 0.523 * g + 0.312 * b);

            // copie de la nouvelle couleur dans l'image
            fichier->image[i][j].r = rTsl;
            fichier->image[i][j].g = gTsl;
            fichier->image[i][j].b = bTsl;
        }
    }

    sprintf(nomEnregistrement, "./res/%s_RVBTsl%s", nom, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_RVBTsl%s", nom, extension);
    sprintf(nomEnregistrement, "start ./res/%s_RVBTsl%s", nom, extension);
    system(nomEnregistrement);
    free(fichier);
}

// fonction permettant le contraste de l'image en passant le de contraste en param??tre
void contrasteImage(struct fichierimage *fichier, char nom[50], int contraste) {
    char nomEnregistrement[100];
    char extension[5] = ".bmp";
    // --------------------------------------------------
    int i, j;
    int r, g, b;
    int rContraste, gContraste, bContraste;

    // Passage d'une image RVB ?? TSL
    for (i = 0; i < fichier->entetebmp.hauteur; i++) {     // i = ligne
        for (j = 0; j < fichier->entetebmp.largeur; j++) { // j = colonne
            // copie de la couleur de l'image dans la nouvelle image
            r = fichier->image[i][j].r;
            g = fichier->image[i][j].g;
            b = fichier->image[i][j].b;

            // calcul de la nouvelle valeur de l'image
            rContraste = (int)(r * (1 + (contraste / 100)));
            gContraste = (int)(g * (1 + (contraste / 100)));
            bContraste = (int)(b * (1 + (contraste / 100)));

            // copie de la nouvelle couleur dans l'image
            fichier->image[i][j].r = rContraste;
            fichier->image[i][j].g = gContraste;
            fichier->image[i][j].b = bContraste;
        }
    }

    sprintf(nomEnregistrement, "./res/%s_contraste%d%s", nom, contraste, extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_contraste%d%s", nom, contraste, extension);
    sprintf(nomEnregistrement, "start ./res/%s_contraste%d%s", nom, contraste, extension);
    system(nomEnregistrement);
    free(fichier);
}

// Fonction permettant de faire un filtrage de sobel avec un masque de 3x3 en parametre (masque de convolution)
void filtreSobel(struct fichierimage *fichier, char nom[50], int masque[3][3]) {
    char nomEnregistrement[100]; // nom de l'image enregistrer
    char extension[5] = ".bmp";  // extension de l'image enregistrer
    // --------------------------------------------------
    int i, j, k, l;
    int somme_r, somme_g, somme_b;
    int somme_r2, somme_g2, somme_b2;

    for (i = 1; i < fichier->entetebmp.hauteur - 1; i++) {     // i = ligne
        for (j = 1; j < fichier->entetebmp.largeur - 1; j++) { // j = colonne
            somme_r = 0;
            somme_g = 0;
            somme_b = 0;
            for (k = -1; k <= 1; k++) {                                               // k = ligne du masque
                for (l = -1; l <= 1; l++) {                                           // l = colonne du masque
                    somme_r += fichier->image[i + k][j + l].r * masque[k + 1][l + 1]; // somme des valeurs de l'image multipli?? par le masque
                    somme_g += fichier->image[i + k][j + l].g * masque[k + 1][l + 1];
                    somme_b += fichier->image[i + k][j + l].b * masque[k + 1][l + 1];
                }
            }
            if (somme_r > 255)    // si la somme est plus grande que 255
                somme_r = 255;    // on met la valeur a 255
            else if (somme_r < 0) // si la somme est plus petite que 0
                somme_r = 0;      // on met la valeur a 0
            if (somme_g > 255)
                somme_g = 255;
            else if (somme_g < 0)
                somme_g = 0;
            if (somme_b > 255)
                somme_b = 255;
            else if (somme_b < 0)
                somme_b = 0;
            fichier->image[i][j].r = somme_r; // copie de la nouvelle valeur dans l'image
            fichier->image[i][j].g = somme_g;
            fichier->image[i][j].b = somme_b;
        }
    }
    // Enregistrement de l'image et affichage de l'image
    sprintf(nomEnregistrement, "./res/%s_image_filtre_sobel_%d%s", nom, masque[1][1], extension);
    enregistrer(nomEnregistrement, fichier);
    // sprintf(nomEnregistrement, "open ./res/%s_image_filtre_sobel_%d%s", nom, masque[1][1], extension);
    sprintf(nomEnregistrement, "start ./res/%s_image_filtre_sobel_%d%s", nom, masque[1][1], extension);
    system(nomEnregistrement);
    free(fichier);
}
