#ifndef CELLULEVIVANTE_H
#define CELLULEVIVANTE_H

#include "Cellule.h"  // Inclusion de l'en-tête de la classe Cellule

// Classe représentant une cellule vivante, dérivée de la classe Cellule
class CelluleVivante : public Cellule {
public:
    CelluleVivante();  // Constructeur

    // Retourne l'état actuel de la cellule (vivante)
    bool getEtatActuel() const override;

    // Modifie l'état actuel de la cellule
    void setEtatActuel(bool etat) override;
};

#endif // CELLULEVIVANTE_H
