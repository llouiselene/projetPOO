#ifndef FICHIER_TEXTE_H
#define FICHIER_TEXTE_H

#include <string>
#include "Grille.h"

class FichierTexte {
public:
    // Constructeur
    FichierTexte();

    // Charge une grille depuis un fichier texte
    void charger(const std::string& chemin, Grille& grille);

    // Sauvegarde une grille dans un fichier texte
    void sauvegarder(const std::string& chemin, const Grille& grille);

    // Crée un fichier avec une grille aléatoire
    void genererGrilleAleatoire(const std::string& chemin, int largeur, int hauteur);

private:
    // Méthodes utilitaires pour manipuler des fichiers texte brut
    std::string lireFichierTexte(const std::string& chemin);
    void ecrireFichierTexte(const std::string& chemin, const std::string& contenu);
};

#endif // FICHIER_TEXTE_H
