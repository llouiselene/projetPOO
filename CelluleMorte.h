#ifndef CELLULEMORTE_H
#define CELLULEMORTE_H

#include "Cellule.h"  // Inclusion de l'en-tête de la classe Cellule

// Classe représentant une cellule morte, dérivée de la classe Cellule
class CelluleMorte : public Cellule {
public:
    CelluleMorte();  // Constructeur

    // Retourne l'état actuel de la cellule (morte)
    bool getEtatActuel() const override;

    // Modifie l'état actuel de la cellule
    void setEtatActuel(bool etat) override;
};

#endif // CELLULEMORTE_H
