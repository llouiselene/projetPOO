#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "FichierTexte.h"
#include "Grille.h"
#include "Cellule.h"

int main() {
    int largeur = 10, hauteur = 10, nombreIterations = 10;
    bool torique = false;

    Simulation simulation(largeur, hauteur, torique, nombreIterations);
    FichierTexte fichierTexte;

    std::string cheminFichier = "GrilleInitiale.txt";
    std::ifstream fichier(cheminFichier);

    if (!fichier.is_open()) {
        std::cout << "Le fichier " << cheminFichier << " n'existe pas. Génération d'une grille aléatoire.\n";
        try {
            fichierTexte.genererGrilleAleatoire(cheminFichier, largeur, hauteur);
            std::cout << "Grille générée et sauvegardée dans " << cheminFichier << ".\n";
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors de la génération de la grille : " << e.what() << std::endl;
            return 1;
        }
    }

    try {
        fichierTexte.charger(cheminFichier, *simulation.getGrille());
        std::cout << "État initial chargé depuis " << cheminFichier << ".\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement de la grille : " << e.what() << std::endl;
        return 1;
    }

    char choixInterface;
    std::cout << "Voulez-vous utiliser l'interface graphique (G) ou la console (C) ? ";
    std::cin >> choixInterface;

    if (choixInterface == 'G' || choixInterface == 'g') {
        sf::RenderWindow window(sf::VideoMode(largeur * 20, hauteur * 20), "Jeu de la Vie");
        sf::RectangleShape cellule(sf::Vector2f(18, 18));

        int iterationActuelle = 0;
        while (window.isOpen() && iterationActuelle < nombreIterations) {
            sf::Event event;
            bool nextIteration = false;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed) {
                    nextIteration = true;
                }
            }

            if (nextIteration) {
                simulation.getGrille()->next();
                iterationActuelle++;
            }

            window.clear(sf::Color::White);
            for (int x = 0; x < largeur; x++) {
                for (int y = 0; y < hauteur; y++) {
                    cellule.setPosition(x * 20 + 1, y * 20 + 1);
                    cellule.setFillColor(simulation.getGrille()->getCellule(x, y)->getEtatActuel() ? sf::Color::Green : sf::Color::Black);
                    window.draw(cellule);
                }
            }
            window.display();
        }
    } else {
        std::cout << "Simulation en mode console...\n";

        char choixTest;
        std::cout << "Voulez-vous effectuer un test unitaire (O/N) ? ";
        std::cin >> choixTest;
        std::cin.ignore();

        bool modeTest = (choixTest == 'O' || choixTest == 'o');

       for (int i = 0; i < nombreIterations; ++i) {
    std::cout << "Itération " << i + 1 << " :\n";

    // Affichage de l'état actuel de la grille
    simulation.getGrille()->afficherConsole();

    // Sauvegarde de l'état actuel de la grille dans un fichier
    std::string nomFichier = "Etat_Iteration_" + std::to_string(i + 1) + ".txt";
    try {
        fichierTexte.sauvegarder(nomFichier, *simulation.getGrille());
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la sauvegarde de l'état de l'itération : " << e.what() << std::endl;
    }

    // Calcul de l'état suivant
    simulation.getGrille()->next();

    if (modeTest) {
        std::string nomFichierTest = "Etat_Iteration_test_" + std::to_string(i + 1) + ".txt";
        
        try {
            std::ifstream fichierGenere(nomFichier);
            std::ifstream fichierTest(nomFichierTest);
            
            if (!fichierGenere.is_open() || !fichierTest.is_open()) {
                throw std::runtime_error("Impossible d'ouvrir les fichiers de comparaison");
            }

            bool identique = true;
            std::string ligneGeneree, ligneTest;
            while (std::getline(fichierGenere, ligneGeneree) && std::getline(fichierTest, ligneTest)) {
                if (ligneGeneree != ligneTest) {
                    identique = false;
                    break;
                }
            }

            if (identique && !std::getline(fichierGenere, ligneGeneree) && !std::getline(fichierTest, ligneTest)) {
                std::cout << "Test de l'itération " << i + 1 << " réussi." << std::endl;
            } else {
                std::cout << "Test de l'itération " << i + 1 << " échoué." << std::endl;
                std::cout << "Grille attendue :" << std::endl;
                fichierTest.clear();
                fichierTest.seekg(0);
                while (std::getline(fichierTest, ligneTest)) {
                    std::cout << ligneTest << std::endl;
                }
                std::cout << "Grille obtenue :" << std::endl;
                fichierGenere.clear();
                fichierGenere.seekg(0);
                while (std::getline(fichierGenere, ligneGeneree)) {
                    std::cout << ligneGeneree << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors de la comparaison des fichiers : " << e.what() << std::endl;
        }
    }

    if (!modeTest) {
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.ignore();
    }
}

    std::string fichierFinal = "GrilleFinale.txt";
    try {
        fichierTexte.sauvegarder(fichierFinal, *simulation.getGrille());
        std::cout << "État final sauvegardé dans '" << fichierFinal << "'.\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la sauvegarde de l'état final : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
}