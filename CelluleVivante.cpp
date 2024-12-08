#include "CelluleVivante.h"

// Constructeur de la classe CelluleVivante
CelluleVivante::CelluleVivante() {
    etatActuel = true;  // Une cellule vivante est initialement vivante
}

// Retourne l'état actuel de la cellule
bool CelluleVivante::getEtatActuel() const {
    return etatActuel;
}

// Modifie l'état actuel de la cellule
void CelluleVivante::setEtatActuel(bool etat) {
    etatActuel = etat;  // Met à jour l'état avec la valeur fournie
}
