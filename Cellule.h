#ifndef CELLULE_H
#define CELLULE_H

// Classe abstraite représentant une cellule dans un automate cellulaire
class Cellule {
protected:
    bool etatActuel;  // État de la cellule (true pour vivante, false pour morte)

public:
    // Méthode virtuelle pure qui retourne l'état actuel de la cellule
    virtual bool getEtatActuel() const = 0;

    // Méthode virtuelle pure qui modifie l'état actuel de la cellule
    virtual void setEtatActuel(bool etat) = 0;

    // Destructeur virtuel par défaut pour assurer la destruction correcte des sous-classes
    virtual ~Cellule() = default;
};

#endif // CELLULE_H
