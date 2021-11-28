#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

// fonction permetant de mettre une image en niveau de gris
void imageVersNiveauDeGris(struct fichierimage *fichier) {
    int i, j;
    int niveau;

    for (i = fichier->entetebmp.hauteur - 1; i >= 0; i--) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            niveau = (fichier->image[i][j].r + fichier->image[i][j].g + fichier->image[i][j].b) / 3;
            fichier->image[i][j].r = niveau;
            fichier->image[i][j].g = niveau;
            fichier->image[i][j].b = niveau;
        }
    }
}

// fonction permetant de créer une image miroir horizontal
void imageVersMirroir(struct fichierimage *fichier) {
    int i, j;
    int niveau;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur / 2; j++) {
            niveau = fichier->image[i][j].r;
            fichier->image[i][j].r = fichier->image[i][fichier->entetebmp.largeur - 1 - j].r;
            fichier->image[i][fichier->entetebmp.largeur - 1 - j].r = niveau;
            niveau = fichier->image[i][j].g;
            fichier->image[i][j].g = fichier->image[i][fichier->entetebmp.largeur - 1 - j].g;
            fichier->image[i][fichier->entetebmp.largeur - 1 - j].g = niveau;
            niveau = fichier->image[i][j].b;
            fichier->image[i][j].b = fichier->image[i][fichier->entetebmp.largeur - 1 - j].b;
            fichier->image[i][fichier->entetebmp.largeur - 1 - j].b = niveau;
        }
    }
}

// fonction permettant de créer une image symetrique
void imageVersSymetrie(struct fichierimage *fichier) {
    int i, j;

    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.largeur, fichier->entetebmp.hauteur);

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = fichier->entetebmp.largeur / 2; j >= 0; j--) {
            fichier2->image[i][j].r = fichier->image[i][j].r;
            fichier2->image[i][j].g = fichier->image[i][j].g;
            fichier2->image[i][j].b = fichier->image[i][j].b;

            fichier2->image[i][fichier->entetebmp.hauteur - j - 1].r = fichier->image[i][j].r;
            fichier2->image[i][fichier->entetebmp.hauteur - j - 1].g = fichier->image[i][j].g;
            fichier2->image[i][fichier->entetebmp.hauteur - j - 1].b = fichier->image[i][j].b;
        }
    }

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier->image[i][j].r = fichier2->image[i][j].r;
            fichier->image[i][j].g = fichier2->image[i][j].g;
            fichier->image[i][j].b = fichier2->image[i][j].b;
        }
    }

    // enregistrer("./res/LAURETTA_PERONNE_Symetrie.bmp", fichier2);
    // free(fichier2);
}

// fonction permetant de pivoter une image de 90° à gauche
void pivoterImageDroit(struct fichierimage *fichier) {
    int i, j;
    struct fichierimage *fichier2;

    fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier2->image[i][j].r = fichier->image[j][i].r;
            fichier2->image[i][j].g = fichier->image[j][i].g;
            fichier2->image[i][j].b = fichier->image[j][i].b;
        }
    }

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier->image[i][j].r = fichier2->image[i][j].r;
            fichier->image[i][j].g = fichier2->image[i][j].g;
            fichier->image[i][j].b = fichier2->image[i][j].b;
        }
    }
    free(fichier2);
}

// fonction permetant de pivoter une image de 90° à droite
void pivoterImageGauche(struct fichierimage *fichier) {
    int i, j;
    struct pixels pixel;

    for (i = 0; i < fichier->entetebmp.hauteur / 2; i++) {
        for (j = 0; j < fichier->entetebmp.largeur / 2; j++) {
            pixel = fichier->image[i][j];
            fichier->image[i][j] = fichier->image[fichier->entetebmp.hauteur - 1 - j][i];
            fichier->image[fichier->entetebmp.hauteur - 1 - j][i] = fichier->image[fichier->entetebmp.hauteur - 1 - i][fichier->entetebmp.largeur - 1 - j];
            fichier->image[fichier->entetebmp.hauteur - 1 - i][fichier->entetebmp.largeur - 1 - j] = fichier->image[j][fichier->entetebmp.hauteur - 1 - i];
            fichier->image[j][fichier->entetebmp.hauteur - 1 - i] = pixel;
        }
    }
}

// Calcul du pourcentage de couleur d'une image (RVB), teine, saturation et luminance

// Création d'une image négative
void imageNegative(struct fichierimage *fichier) {
    int i, j;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier->image[i][j].r = 255 - fichier->image[i][j].r;
            fichier->image[i][j].g = 255 - fichier->image[i][j].g;
            fichier->image[i][j].b = 255 - fichier->image[i][j].b;
        }
    }
}

// Seuillage d'une image
void seuillage(struct fichierimage *fichier, int seuil) {
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
}

// Inversion des couleurs d'une image
void inversionCouleur(struct fichierimage *fichier) {
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

    // enregistrer("./res/LAURETTA_PERONNE_inversionCouleur.bmp", fichier2);
    free(fichier2);
}

// Réduction d'une image (changement d'échelle)
void reductionImage(struct fichierimage *fichier, int echelle) {
    char nomEnregistrement[100];
    int i, j;
    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur / echelle, fichier->entetebmp.largeur / echelle);

    for (i = 0; i < fichier->entetebmp.hauteur; i += echelle) {
        for (j = 0; j < fichier->entetebmp.largeur; j += echelle) {
            fichier2->image[i / echelle][j / echelle].r = fichier->image[i][j].r;
            fichier2->image[i / echelle][j / echelle].g = fichier->image[i][j].g;
            fichier2->image[i / echelle][j / echelle].b = fichier->image[i][j].b;
        }
    }

    // enregistrer("./res/LAURETTA_PERONNE_reductionImage.bmp", fichier2);
    sprintf(nomEnregistrement, "./res/LAURETTA_PERONNE_reductionImage_echelle_%d.bmp", echelle);
    enregistrer(nomEnregistrement, fichier2);
    free(fichier2);
}

// Agrandissement d'une image (changement d'échelle)
void agrandissementImage(struct fichierimage *fichier, int echelle) {
    char nomEnregistrement[100];
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

    sprintf(nomEnregistrement, "./res/LAURETTA_PERONNE_agrandissementImage_echelle_%d.bmp", echelle);
    enregistrer(nomEnregistrement, fichier2);
    free(fichier2);
}

// Transformation d'une image en monochrome.
void monochromeImage(struct fichierimage *fichier, char couleur) {
    char nomEnregistrement[100];
    int i, j;

    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            if (couleur == 'r') {
                fichier2->image[i][j].r = fichier->image[i][j].r;
                fichier2->image[i][j].g = 0;
                fichier2->image[i][j].b = 0;
            } else if (couleur == 'g' || couleur == 'v') {
                fichier2->image[i][j].r = 0;
                fichier2->image[i][j].g = fichier->image[i][j].g;
                fichier2->image[i][j].b = 0;
            } else if (couleur == 'b') {
                fichier2->image[i][j].r = 0;
                fichier2->image[i][j].g = 0;
                fichier2->image[i][j].b = fichier->image[i][j].b;
            }
        }
    }

    sprintf(nomEnregistrement, "./res/LAURETTA_PERONNE_monochromeImage_couleur_%c.bmp", couleur);
    enregistrer(nomEnregistrement, fichier2);
    free(fichier2);
}

void convolution(struct fichierimage *fichier, int matrice[3][3], int diviseur) {
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

            // Limitation des valeurs de l'image
            // if (niveauR < 0) {
            //     niveauR = 0;
            // }
            // if (niveauR > 255) {
            //     niveauR = 255;
            // }
            // if (niveauG < 0) {
            //     niveauG = 0;
            // }
            // if (niveauG > 255) {
            //     niveauG = 255;
            // }
            // if (niveauB < 0) {
            //     niveauB = 0;
            // }
            // if (niveauB > 255) {
            //     niveauB = 255;
            // }

            // Affectation des niveaux de l'image
            fichier->image[i][j].r = niveauR;
            fichier->image[i][j].g = niveauG;
            fichier->image[i][j].b = niveauB;
        }
    }
}

// Supperposition d'une image sur une autre
void superpositionImage(struct fichierimage *fichier, struct fichierimage *fichier2) {
    int i, j;

    struct fichierimage *fichier3 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier3->image[i][j].r = fichier->image[i][j].r;
            fichier3->image[i][j].g = fichier->image[i][j].g;
            fichier3->image[i][j].b = fichier->image[i][j].b;
        }
    }

    for (i = 0; i < fichier2->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier2->entetebmp.largeur; j++) {
            fichier3->image[i][j].r = fichier2->image[i][j].r;
            fichier3->image[i][j].g = fichier2->image[i][j].g;
            fichier3->image[i][j].b = fichier2->image[i][j].b;
        }
    }

    enregistrer("./res/LAURETTA_PERONNE_supperposition.bmp", fichier3);
    free(fichier3);
}

// Rotation d'une image d'un angle donné en degrés
void rotationImage(struct fichierimage *fichier, int angle) {
    char nomEnregistrement[100];
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

    sprintf(nomEnregistrement, "./res/LAURETTA_PERONNE_rotation_%d°.bmp", angle);
    enregistrer(nomEnregistrement, fichier2);
    free(fichier2);
}

// réduire le bruit de l'image 
void reductionBruite(struct fichierimage *fichier) {
    int i, j;
    int niveauR, niveauG, niveauB;

    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

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

    enregistrer("./res/LAURETTA_PERONNE_reduireBruit.bmp", fichier2);
    free(fichier2);
}

// Fonction permettant de réalisé un filtrage de l'image
void filtreImage(struct fichierimage *fichier) {
    struct fichierimage *fichier2 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);

    int i, j;

    for (i = 0; i < fichier->entetebmp.hauteur; i++) {
        for (j = 0; j < fichier->entetebmp.largeur; j++) {
            fichier2->image[i][j].r = fichier->image[i][j].r + (fichier->image[i][j].r * 0.1);
            fichier2->image[i][j].g = fichier->image[i][j].g + (fichier->image[i][j].g * 0.1);
            fichier2->image[i][j].b = fichier->image[i][j].b + (fichier->image[i][j].b * 0.1);
        }
    }

    enregistrer("./res/LAURETTA_PERONNE_filtre.bmp", fichier2);
    free(fichier2);
}