/// The item class defines an item within the game that teh player can collect
/// for an additional bonus.
///
/// Every item has a value that is added to the player's score upon collection,
/// if this value is zero, the item will either incriment the player's lives by
/// one or end the level.

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <SFML/Graphics.hpp>

class Item
{
    friend class Level;

    public:
        Item(); // Default constructor.
        Item(std::string identifier, int x, int y, const int tileSize);
        sf::Vector2i getGridLoc(const int tileSize);
        virtual ~Item();

    private:
        sf::Sprite sprite;  // The item image
        int value;          // How many points the player gets upon collection
        bool collected;     // If the item has been collected
        bool seen;          // If the item has been seen before
        bool visible;       // If the item can currently be seen
        std::string id;     // What type of item this is

        // Only the level shourld be able access these functions
        void reset();
        void setTexture(sf::Texture &texure);
};

#endif // ITEM_H
