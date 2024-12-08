#include "Simulation.h"
#include <iostream>
#include <thread>
#include <chrono>

// Constructeur de la classe Simulation
Simulation::Simulation(int largeur, int hauteur, bool torique, int nombreIterations)
    : nombreIterations(nombreIterations), grille(new Grille(largeur, hauteur, torique)) {
    // Alloue dynamiquement l'objet FichierTexte
    fichierTexte = new FichierTexte();
}

// Destructeur
Simulation::~Simulation() {
    delete grille;          // Libère la mémoire allouée pour la grille
    delete fichierTexte;    // Libère la mémoire allouée pour l'objet FichierTexte
}

// Setter pour la grille
void Simulation::setGrille(Grille* nouvelleGrille) {
    if (grille != nullptr) {
        delete grille;  // Libère la mémoire de l'ancienne grille
    }
    grille = nouvelleGrille; // Assigne la nouvelle grille
}

// Démarre la simulation
void Simulation::demarrer() {
    // Avance d'une étape dans la simulation
    grille->next();  // Calcul des états suivants et mise à jour de la grille

    // Affichage de la grille après mise à jour
    grille->afficherConsole();  // Affiche l'état actuel de la grille
}


// Charge un état initial depuis un fichier
void Simulation::chargerEtatInitial(const std::string& cheminFichier) {
    try {
        fichierTexte->charger(cheminFichier, *grille); // Utilisation du pointeur pour appeler la méthode
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur lors du chargement de l'état initial : " << e.what() << std::endl;
        // Si le fichier n'existe pas, crée un état initial par défaut
        std::cout << "Création d'un état initial par défaut..." << std::endl;
        fichierTexte->sauvegarder("GrilleStart.txt", *grille); // Sauvegarde l'état par défaut
    }
}

// Sauvegarde l'état courant dans un fichier
void Simulation::sauvegarderEtatCourant(const std::string& cheminFichier) {
    fichierTexte->sauvegarder(cheminFichier, *grille); // Utilisation du pointeur pour appeler la méthode
}
