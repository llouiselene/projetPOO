#include "FichierTexte.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <random>

// Constructeur
FichierTexte::FichierTexte() {}

// Lire le contenu d'un fichier texte et le retourner sous forme de chaîne
std::string FichierTexte::lireFichierTexte(const std::string& chemin) {
    std::ifstream fichier(chemin); // Ouvre le fichier en lecture
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + chemin); // Lève une exception si le fichier ne peut pas être ouvert
    }

    std::ostringstream contenu; // Utilise un ostringstream pour stocker le contenu du fichier
    contenu << fichier.rdbuf();  // Lit le contenu du fichier dans le ostringstream
    return contenu.str();        // Retourne le contenu sous forme de chaîne
}

// Écrire une chaîne dans un fichier texte
void FichierTexte::ecrireFichierTexte(const std::string& chemin, const std::string& contenu) {
    std::ofstream fichier(chemin); // Ouvre le fichier en écriture
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier pour écriture : " + chemin); // Lève une exception si le fichier ne peut pas être ouvert
    }

    fichier << contenu; // Écrit le contenu dans le fichier
}

// Charger une grille depuis un fichier texte
void FichierTexte::charger(const std::string& chemin, Grille& grille) {
    std::string contenu = lireFichierTexte(chemin); // Lit le contenu du fichier
    std::istringstream flux(contenu); // Crée un flux à partir du contenu lu

    int largeur = grille.getLargeur(); // Obtient la largeur de la grille
    int hauteur = grille.getHauteur();  // Obtient la hauteur de la grille

    int y = 0; // Initialise l'index de ligne
    std::string ligne; // Variable pour stocker chaque ligne du fichier
    while (std::getline(flux, ligne) && y < hauteur) { // Lit chaque ligne jusqu'à la hauteur de la grille
        for (int x = 0; x < largeur && x < static_cast<int>(ligne.size()); ++x) {
            Cellule* nouvelleCellule = nullptr; // Pointeur vers la nouvelle cellule

            // Création de la cellule en fonction des caractères du fichier
            if (ligne[x] == '1') {
                nouvelleCellule = new CelluleVivante();  // Crée une cellule vivante
                nouvelleCellule->setEtatActuel(true);    // Définit l'état actuel à vivant
            } else {
                nouvelleCellule = new CelluleMorte();    // Crée une cellule morte
                nouvelleCellule->setEtatActuel(false);   // Définit l'état actuel à mort
            }

            // Remplace la cellule existante pour éviter les fuites mémoire
            grille.setCellule(x, y, nouvelleCellule);
        }
        ++y; // Passe à la ligne suivante
    }
}

// Sauvegarder une grille dans un fichier texte
void FichierTexte::sauvegarder(const std::string& chemin, const Grille& grille) {
    int largeur = grille.getLargeur(); // Obtient la largeur de la grille
    int hauteur = grille.getHauteur();  // Obtient la hauteur de la grille

    std::ostringstream contenu; // Utilise un ostringstream pour construire le contenu à écrire

    for (int y = 0; y < hauteur; ++y) { // Pour chaque ligne de la grille
        for (int x = 0; x < largeur; ++x) { // Pour chaque cellule de la ligne
            contenu << (grille.getCellule(x, y)->getEtatActuel() ? '1' : '0'); // Écrit '1' si la cellule est vivante, sinon '0'
        }
        contenu << '\n'; // Ajoute un retour à la ligne à la fin de chaque ligne de la grille
    }

    ecrireFichierTexte(chemin, contenu.str()); // Écrit le contenu dans le fichier
}

// Créer une grille aléatoire et la sauvegarder dans un fichier texte
void FichierTexte::genererGrilleAleatoire(const std::string& chemin, int largeur, int hauteur) {
    std::ofstream fichier(chemin); // Ouvre le fichier en écriture
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible de créer le fichier : " + chemin); // Lève une exception si le fichier ne peut pas être ouvert
    }

    std::random_device rd;  // Pour obtenir une graine aléatoire
    std::mt19937 gen(rd()); // Générateur de nombres aléatoires
    std::uniform_int_distribution<> distrib(0, 1); // Distribution uniforme entre 0 et 1

    for (int y = 0; y < hauteur; ++y) { // Pour chaque ligne de la grille
        for (int x = 0; x < largeur; ++x) { // Pour chaque cellule de la ligne
            // Générer aléatoirement '1' ou '0' pour chaque cellule
            fichier << distrib(gen); // Écrit '1' ou '0' dans le fichier
        }
        fichier << '\n';  // Ajouter un retour à la ligne à la fin de chaque ligne de la grille
    }

    std::cout << "Fichier généré avec une grille aléatoire : " << chemin << std::endl; // Affiche un message de confirmation
}
