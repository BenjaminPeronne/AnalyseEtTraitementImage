// #include "image.h"
#include "menu.h"
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

    menu_principal(fichier, fichier2, fichier3);

    return 0;
}
