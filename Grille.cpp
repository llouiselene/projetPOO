#include "Grille.h"
#include <iostream>

// Constructeur de la classe Grille
Grille::Grille(int largeur, int hauteur, bool torique)
    : largeur(largeur), hauteur(hauteur), torique(torique),
      cellules(largeur, std::vector<Cellule*>(hauteur, nullptr)),
      etatsSuivants(largeur, std::vector<bool>(hauteur, false)) {
    
    // Initialisation de la grille avec des cellules mortes
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            cellules[x][y] = new CelluleMorte();  // Chaque cellule est initialisée comme morte
        }
    }
}

// Destructeur de la classe Grille
Grille::~Grille() {
    // Libération de la mémoire allouée pour chaque cellule
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            delete cellules[x][y];  // Supprime chaque cellule
        }
    }
}

// Ajuste les coordonnées pour la toricité
int Grille::coordonneeTorique(int coord, int max) const {
    return (coord + max) % max; // Retourne la coordonnée ajustée pour la toricité
}

// Compte le nombre de voisines vivantes d'une cellule
int Grille::compterVoisinesVivantes(int x, int y) const {
    int count = 0; // Compteur de cellules vivantes

    // Parcours des voisins autour de la cellule (x, y)
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Ignore la cellule centrale (x, y)

            int nx = x + dx; // Coordonnée x du voisin
            int ny = y + dy; // Coordonnée y du voisin

            // Gestion des coordonnées toriques
            if (torique) {
                nx = coordonneeTorique(nx, largeur);
                ny = coordonneeTorique(ny, hauteur);
            } else if (nx < 0 || ny < 0 || nx >= largeur || ny >= hauteur) {
                continue; // Ignore les voisins hors limites si non torique
            }

            // Incrémente le compteur si la cellule voisine est vivante
            if (cellules[nx][ny]->getEtatActuel()) {
                ++count; // Incrémente le compteur
            }
        }
    }

    return count; // Retourne le nombre de voisines vivantes
}

// Calcule l'état suivant d'une cellule
void Grille::calculerEtatSuivant(int x, int y) {
    int nbVoisinesVivantes = compterVoisinesVivantes(x, y); // Compte les voisines vivantes

    // Calculer l'état suivant pour chaque cellule
    if (!cellules[x][y]->getEtatActuel()) {
        // Cellule morte devient vivante si elle a exactement 3 voisines vivantes
        if (nbVoisinesVivantes == 3) {
            etatsSuivants[x][y] = true; // La cellule devient vivante
        } else {
            etatsSuivants[x][y] = false; // Reste morte
        }
    } else {
        // Cellule vivante reste vivante si elle a 2 ou 3 voisines vivantes, sinon elle meurt
        if (nbVoisinesVivantes == 2 || nbVoisinesVivantes == 3) {
            etatsSuivants[x][y] = true; // Reste vivante
        } else {
            etatsSuivants[x][y] = false; // Devient morte
        }
    }
}

// Passe à l'état suivant de la grille
void Grille::next() {
    // Calculer les états suivants pour toutes les cellules
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            calculerEtatSuivant(x, y); // Calcule l'état suivant
        }
    }

    // Appliquer les nouveaux états aux cellules
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            // Si l'état suivant est vrai, la cellule devient vivante
            if (etatsSuivants[x][y]) {
                if (dynamic_cast<CelluleMorte*>(cellules[x][y])) {
                    delete cellules[x][y]; // Supprime la cellule morte
                    cellules[x][y] = new CelluleVivante(); // Crée une nouvelle cellule vivante
                }
            } else {
                // Sinon, elle devient morte
                if (dynamic_cast<CelluleVivante*>(cellules[x][y])) {
                    delete cellules[x][y]; // Supprime la cellule vivante
                    cellules[x][y] = new CelluleMorte(); // Crée une nouvelle cellule morte
                }
            }
        }
    }
}

// Affiche l'état actuel de la grille dans la console
void Grille::afficherConsole() const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            // Affiche '1' pour une cellule vivante, '0' pour une cellule morte
            std::cout << (cellules[x][y]->getEtatActuel() ? '1' : '0') << " ";
        }
        std::cout << '\n'; // Nouvelle ligne après chaque ligne de la grille
    }
}

// Définit une cellule à une position donnée
void Grille::setCellule(int x, int y, Cellule* cellule) {
    if (torique) {
        // Ajuste les coordonnées pour la toricité
        x = coordonneeTorique(x, largeur);
        y = coordonneeTorique(y, hauteur);
    }

    // Vérifie que les coordonnées sont dans les limites de la grille
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        delete cellules[x][y]; // Supprime la cellule existante
        cellules[x][y] = cellule; // Assigne la nouvelle cellule
    }
}

// Obtient une cellule à une position donnée
Cellule* Grille::getCellule(int x, int y) const {
    if (torique) {
        // Ajuste les coordonnées pour la toricité
        x = coordonneeTorique(x, largeur);
        y = coordonneeTorique(y, hauteur);
    }

    return cellules[x][y]; // Retourne la cellule à la position spécifiée
}
