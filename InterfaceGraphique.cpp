#include "InterfaceGraphique.h"
#include "Grille.h"

// Constructeur de la classe InterfaceGraphique
InterfaceGraphique::InterfaceGraphique(int width, int height, int cellSize, Simulation* sim)
    : cellSize(cellSize), simulation(sim), 
      window(sf::VideoMode(width * cellSize, height * cellSize), "Jeu de la Vie") {
    // Initialisation de la fenêtre avec les dimensions spécifiées et le titre
    window.setFramerateLimit(60); // Limite le nombre de frames par seconde
}

// Affiche la grille dans la fenêtre
void InterfaceGraphique::afficherGrille() {
    window.clear(sf::Color::Black); // Efface la fenêtre avec un fond noir
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1)); // Rectangle pour représenter une cellule

    Grille* grille = simulation->getGrille(); // Accède à la grille via l'objet Simulation
    for (int x = 0; x < grille->getLargeur(); ++x) {
        for (int y = 0; y < grille->getHauteur(); ++y) {
            cell.setPosition(x * cellSize, y * cellSize); // Positionne la cellule
            // Définit la couleur de la cellule en fonction de son état
            cell.setFillColor(grille->getCellule(x, y)->getEtatActuel() ? sf::Color::White : sf::Color::Black);
            window.draw(cell); // Dessine la cellule dans la fenêtre
        }
    }
    window.display(); // Affiche le contenu de la fenêtre
}

// Met à jour l'affichage de la grille
void InterfaceGraphique::mettreAJourAffichage() {
    afficherGrille(); // Appelle la méthode pour afficher la grille
}

// Gère les interactions de l'utilisateur
void InterfaceGraphique::gererInteractionsUtilisateur() {
    sf::Event event;
    while (window.pollEvent(event)) { // Récupère les événements de la fenêtre
        if (event.type == sf::Event::Closed) // Vérifie si la fenêtre est fermée
            window.close(); // Ferme la fenêtre
        // D'autres interactions utilisateur peuvent être ajoutées ici
    }
}

// Démarre l'interface graphique
void InterfaceGraphique::demarrer() {
    window.clear(sf::Color::Black); // Efface la fenêtre
    window.display(); // Affiche le contenu actuel de la fenêtre
}

// Arrête l'interface graphique
void InterfaceGraphique::arreter() {
    window.close(); // Ferme la fenêtre
}

// Vérifie si la fenêtre est ouverte
bool InterfaceGraphique::estOuverte() const {
    return window.isOpen(); // Retourne l'état de la fenêtre
}
