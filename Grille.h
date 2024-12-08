#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.h"        // Inclusion de la classe de base Cellule
#include "CelluleMorte.h"   // Inclusion de la classe CelluleMorte
#include "CelluleVivante.h" // Inclusion de la classe CelluleVivante
#include <vector>          // Inclusion de la bibliothèque vector pour utiliser des tableaux dynamiques

// Classe représentant une grille de cellules
class Grille {
private:
    int largeur; // Largeur de la grille
    int hauteur; // Hauteur de la grille
    bool torique; // Indique si la grille est torique (wrap-around)
    
    // Matrice de pointeurs vers les cellules (vivantes ou mortes)
    std::vector<std::vector<Cellule*>> cellules; 
    
    // Matrice pour stocker les états suivants des cellules
    std::vector<std::vector<bool>> etatsSuivants; 

    // Méthode utilitaire pour gérer les coordonnées dans une grille torique
    int coordonneeTorique(int coord, int max) const;

    // Méthode pour calculer l'état suivant d'une cellule donnée
    void calculerEtatSuivant(int x, int y);

public:
    // Constructeur qui initialise la grille avec une largeur, une hauteur et un paramètre torique
    Grille(int largeur, int hauteur, bool torique);
    
    // Destructeur pour libérer la mémoire allouée pour les cellules
    ~Grille();

    // Méthodes d'accès pour obtenir la largeur et la hauteur de la grille
    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }

    // Méthodes pour l'évolution de la grille
    void next();                        // Calcule les états suivants des cellules
    void afficherConsole() const;       // Affiche la grille dans la console

    // Compte le nombre de cellules vivantes voisines d'une cellule donnée
    int compterVoisinesVivantes(int x, int y) const;

    // Manipuler les cellules de la grille
    void setCellule(int x, int y, Cellule* cellule); // Définit une cellule à une position donnée
    Cellule* getCellule(int x, int y) const;        // Obtient une cellule à une position donnée
};

#endif // GRILLE_H
