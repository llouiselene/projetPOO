#ifndef SIMULATION_H
#define SIMULATION_H

#include "Grille.h"
#include "FichierTexte.h"
#include <string>

// Classe gérant une simulation d'automate cellulaire
class Simulation {
private:
    Grille* grille;            // Pointeur vers la grille utilisée dans la simulation
    int nombreIterations;      // Nombre total d'itérations de la simulation
    FichierTexte* fichierTexte; // Pointeur vers l'objet de gestion des fichiers

public:
    // Constructeur de la simulation
    Simulation(int largeur, int hauteur, bool torique, int nombreIterations);

    // Destructeur
    ~Simulation();

    // Démarre la simulation
    void demarrer();

    // Charge un état initial depuis un fichier
    void chargerEtatInitial(const std::string& cheminFichier);

    // Sauvegarde l'état courant dans un fichier
    void sauvegarderEtatCourant(const std::string& cheminFichier);

    // Getter pour la grille
    Grille* getGrille() const { return grille; }

    // Setter pour la grille
    void setGrille(Grille* nouvelleGrille);
};

#endif
