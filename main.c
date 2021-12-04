// #include "image.h"
#include "menu.h"
// #include "LAURETTA_PERONNE_menu.h"

//------------------------------------------------------------------------------
// Code source pour le projet d'UE035
//
// Nom : LAURETTA-PERONNE
// Prenom : Aymerick
//
// Ce programme inclut deux header : image.h et menu.h (qui porte le même préfixe suite à la consigne de l'UE035)
// Tel que : #include "LAURETTA_PERONNE_menu.h" pour inclure le menu et #include "LAURETTA_PERONNE_image.h" pour inclure les fonctions de l'image
//
// |!| Important |!|
// Afin de pouvoir utiliser ce programme, il faut créer un dossier "res" dans lequel se trouvera les résultats (les fichiers .bmp)
// Tel que : "./res/LAURETTA-PERONNE_1.bmp" par exemple.
// |!| Important |!|
//
// L'image de base est "Lena.bmp"
// Une deuxième est utilisée qui est "Paysage.bmp"
//
// |!| Important |!|
// L'image choisie par l'utilisateur doit être à la racine du dossier du programme.
// Tel que : "Lena.bmp" par exemple.
// |!| Important |!|
//
//-------------------------------------
//
// description : (les fonctions sont définit dans image.h)
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
//
// void imageNegative(struct fichierimage *fichier)
// permet de creer une image en mémoire de négatif, la fonction prend en
// parametre un pointeur de type : struct fichierimage *
// la fonction ne retourne rien
//
// void rotation(struct fichierimage *fichier, int angle)
// permet de creer une image en mémoire de rotation, la fonction prend en
// parametre un pointeur de type : struct fichierimage * et un angle
// la fonction ne retourne rien
//
// void seuillage(struct fichierimage *fichier, int seuil)
// permet de creer une image en mémoire de seuillage, la fonction prend en
// parametre un pointeur de type : struct fichierimage * et un seuil
// la fonction ne retourne rien
//
// void symettrie(struct fichierimage *fichier)
// permet de creer une image en mémoire de symétrie, la fonction prend en
// parametre un pointeur de type : struct fichierimage *
// la fonction ne retourne rien
//
// void inversionCouleur(struct fichierimage *fichier)
// permet de creer une image en mémoire d'inversion de couleur, la fonction prend en
// parametre un pointeur de type : struct fichierimage *
// la fonction ne retourne rien
//
// void reductionImage(struct fichierimage *fichier, int echelle)
// permet de creer une image en mémoire est la réduit la fonction prend en
// parametre un pointeur de type : struct fichierimage * et une échelle de type int
// la fonction ne retourne rien
//
// void agrandissementImage(struct fichierimage *fichier, int echelle)
// permet de creer une image en mémoire est la agrandit la fonction prend en
// parametre un pointeur de type : struct fichierimage * et une échelle de type int
// la fonction ne retourne rien
//
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

    menu_principal(fichier, fichier2, fichier3);

    return 0;
}
