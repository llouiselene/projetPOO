#ifndef INTERFACE_GRAPHIQUE_H
#define INTERFACE_GRAPHIQUE_H

#include <SFML/Graphics.hpp> // Inclusion de la bibliothèque SFML pour les graphiques
#include "Simulation.h"       // Inclusion de la classe Simulation

// Déclaration de la classe InterfaceGraphique
class InterfaceGraphique {
private:
    sf::RenderWindow window; // Fenêtre de rendu pour l'interface graphique
    const int cellSize;      // Taille d'une cellule dans l'affichage
    Simulation* simulation;  // Pointeur vers l'objet Simulation

public:
    // Constructeur de la classe InterfaceGraphique
    InterfaceGraphique(int width, int height, int cellSize, Simulation* sim);

    // Méthode pour afficher la grille
    void afficherGrille();
    // Méthode pour mettre à jour l'affichage
    void mettreAJourAffichage();
    // Méthode pour gérer les interactions de l'utilisateur
    void gererInteractionsUtilisateur();
    // Méthode pour démarrer l'interface graphique
    void demarrer();
    // Méthode pour arrêter l'interface graphique
    void arreter();

    // Vérifie si la fenêtre est ouverte
    bool estOuverte() const;
};

#endif // Fin de la protection d'inclusion
