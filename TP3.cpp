#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <memory>

// Classe de base Card
class Card {
protected:
    std::string cardName; // Nom de la carte

public:
    // Constructeur
    Card(const std::string& name) : cardName(name) {}

    // Méthode virtuelle pure pour afficher les informations
    virtual void displayInfo() const = 0;

    // Getter pour le nom de la carte
    std::string getName() const { return cardName; }
};

// Classe PokemonCard qui hérite de Card
class PokemonCard : public Card {
private:
    std::string pokemonType; // Type du Pokémon
    std::string familyName;  // Famille du Pokémon
    int evolutionLevel;      // Niveau d'évolution
    int maxHP;               // Points de vie maximum
    int hp;                  // Points de vie actuels
    std::vector<std::tuple<int, int, std::string, int>> attacks; // Attaques

public:
    // Constructeur
    PokemonCard(const std::string& name, const std::string& type, const std::string& family,
                int evolution, int maxHealth, int currentHP,
                const std::tuple<int, int, std::string, int>& attack1,
                const std::tuple<int, int, std::string, int>& attack2)
        : Card(name), pokemonType(type), familyName(family), evolutionLevel(evolution),
          maxHP(maxHealth), hp(currentHP) {
        attacks.push_back(attack1); // Ajoute la première attaque
        attacks.push_back(attack2); // Ajoute la seconde attaque
    }

    // Redéfinition de displayInfo
    void displayInfo() const override {
        std::cout << "Nom du Pokémon : " << cardName << "\n";
        std::cout << "Type : " << pokemonType << "\n";
        std::cout << "Famille : " << familyName << "\n";
        std::cout << "Niveau d'évolution : " << evolutionLevel << "\n";
        std::cout << "HP : " << hp << " / " << maxHP << "\n";

        for (size_t i = 0; i < attacks.size(); ++i) {
            std::cout << "Attaque " << i + 1 << " :\n";
            std::cout << "  Coût en énergie : " << std::get<0>(attacks[i]) << "\n";
            std::cout << "  Coût en énergie actuel : " << std::get<1>(attacks[i]) << "\n";
            std::cout << "  Description : " << std::get<2>(attacks[i]) << "\n";
            std::cout << "  Dégâts : " << std::get<3>(attacks[i]) << "\n";
        }
    }

    // Méthode pour restaurer les HP au maximum
    void restoreHP() {
        hp = maxHP;
    }
};

// Classe EnergyCard qui hérite de Card
class EnergyCard : public Card {
private:
    std::string energyType; // Type d'énergie

public:
    // Constructeur
    EnergyCard(const std::string& type) : Card("Energy"), energyType(type) {}

    // Redéfinition de displayInfo
    void displayInfo() const override {
        std::cout << "Nom de la carte : " << cardName << "\n";
        std::cout << "Type d'énergie : " << energyType << "\n";
    }
};

// Classe TrainerCard qui hérite de Card
class TrainerCard : public Card {
private:
    std::string trainerEffect; // Effet de l'entraîneur

public:
    // Constructeur
    TrainerCard(const std::string& trainerName)
        : Card(trainerName), trainerEffect("heal all your action pokemon") {}

    // Redéfinition de displayInfo
    void displayInfo() const override {
        std::cout << "Nom de l'entraîneur : " << cardName << "\n";
        std::cout << "Effet de l'entraîneur : " << trainerEffect << "\n";
    }

    // Applique l'effet de soin à tous les Pokémon en action
    void applyEffect(std::vector<PokemonCard*>& activePokemon) const {
        for (auto& pokemon : activePokemon) {
            pokemon->restoreHP(); // Rétablit les HP au maximum
            std::cout << "Les HP de " << pokemon->getName() << " ont été restaurés au maximum.\n";
        }
    }
};

// Classe Player
class Player {
private:
    std::string playerName;                      // Nom du joueur
    std::vector<Card*> benchCards;              // Cartes en réserve
    std::vector<PokemonCard*> actionCards;      // Cartes d'action Pokémon

public:
    // Constructeur
    Player(const std::string& name) : playerName(name) {}

    // Ajout d'une carte à la réserve
    void addToBench(Card* card) {
        benchCards.push_back(card);
    }

    // Ajout d'une carte Pokémon à l'action
    void addToAction(PokemonCard* pokemonCard) {
        actionCards.push_back(pokemonCard);
    }

    // Afficher les cartes en réserve
    void displayBench() const {
        std::cout << "Cartes en réserve pour " << playerName << " :\n";
        for (size_t i = 0; i < benchCards.size(); ++i) {
            std::cout << "Carte " << i + 1 << " : ";
            benchCards[i]->displayInfo();
            std::cout << "\n";
        }
    }

    // Afficher les cartes d'action
    void displayActionCards() const {
        std::cout << "Cartes d'action pour " << playerName << " :\n";
        for (size_t i = 0; i < actionCards.size(); ++i) {
            std::cout << "Carte " << i + 1 << " : ";
            actionCards[i]->displayInfo();
            std::cout << "\n";
        }
    }
};

// Fonction principale
int main() {
    // Création des attaques
    std::tuple<int, int, std::string, int> attaque1 = {3, 2, "Lancer de flammes", 50};
    std::tuple<int, int, std::string, int> attaque2 = {2, 1, "Griffure", 30};

    // Création des cartes
    PokemonCard* pikachu = new PokemonCard("Pikachu", "Électrique", "Pikachu", 1, 60, 50, attaque1, attaque2);
    EnergyCard* energyCard = new EnergyCard("Électrique");
    TrainerCard* trainer = new TrainerCard("Professeur X");

    // Création du joueur
    Player player("Ash");

    // Ajout des cartes
    player.addToBench(energyCard);
    player.addToBench(trainer);
    player.addToAction(pikachu);

    // Affichage des cartes
    player.displayBench();
    std::cout << "\n";
    player.displayActionCards();

    // Utilisation de l'effet de soin
    std::vector<PokemonCard*> activePokemon = {pikachu};
    trainer->applyEffect(activePokemon);

    // Nettoyage
    delete pikachu;
    delete energyCard;
    delete trainer;

    return 0;
}
