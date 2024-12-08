#include "CelluleMorte.h"

// Constructeur de la classe CelluleMorte
CelluleMorte::CelluleMorte() {
    etatActuel = false;  // Une cellule morte est initialement morte
}

// Retourne l'état actuel de la cellule
bool CelluleMorte::getEtatActuel() const {
    return etatActuel;
}

// Modifie l'état actuel de la cellule
void CelluleMorte::setEtatActuel(bool etat) {
    etatActuel = etat;  // Met à jour l'état avec la valeur fournie
}
