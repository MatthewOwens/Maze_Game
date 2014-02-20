#include "Level.h"
#include <fstream>
#include <sstream>

// Constructor, ImageManager is not const as it needs to be manipulated
Level::Level(const std::string& filepath, ImageManager &imageManager)
{
    // Loading this level's tilesheet
    imageManager.loadImage(filepath + "/tilesheet.png");

    // Loading the map
    loadMap(filepath, imageManager);

    // Loading the items
    loadItems(filepath, imageManager);
}

// Loading the tiles, this method is called in the constructor
void Level::loadMap(const std::string& filepath, ImageManager &imageManager)
{
    std::ifstream file;
    int counter = 0;    // Used for navigating the file
    std::string line;

    // Opening the map file
    file.open(filepath + "/map.txt");

    // Ensuring that the map file was opened correctly
    if (file.good())
    {
        // Parsing the map file
        while(std::getline(file, line))
        {
            for (int i = 0; i < 10; i++)
            {
                if(line[i] != 's')
                    tiles[i][counter] = Tile(imageManager.getImage(filepath + "/tilesheet.png"),
                                             tileSize, line[i] - '0', i, counter);
                else
                {
                    tiles[i][counter] = Tile(imageManager.getImage(filepath + "/tilesheet.png"),
                                            tileSize, 0, i, counter);
                    playerSpawn = sf::Vector2i(i * tileSize, counter * tileSize);
                }
                std::cout << line[i];
            }
            counter++;
            std::cout << std::endl;
        }
    }
    else    // You done goofed.
    {
        std::cout << "Map file at '" << filepath << "/map.txt' was not found!" << std::endl;
    }
    // Closing the map file
    file.close();
}

// Loading items, this method should be called only by the constructor
void Level::loadItems(const std::string& filepath, ImageManager &imageManager)
{
    std::ifstream file(filepath + "/items.txt");
    int counter = 0;
    std::string line;
    std::string subString;
    std::istringstream convert;
    std::stringstream ss;

    int tempX;
    int tempY;
    std::string tempID;

    if (file.good())
    {
        while(std::getline(file, line))
        {
            ss.str(line);
            std::cout << "Item Values: ";
            ss.clear();
            while(std::getline(ss, subString, ','))
            {
                switch(counter)
                {
                case 0:
                    convert.str(subString);
                    convert >> tempID;
                    //std::cout << "substring: " << subString << std::endl;
                    std::cout << tempID << " ";
                    convert.clear();
                    break;
                case 1:
                    convert.str(subString);
                    convert >> tempX;
                    std::cout << tempX << " ";
                    convert.clear();
                    break;
                case 2:
                    convert.str(subString);
                    convert >> tempY;
                    std::cout << tempY;
                    convert.clear();
                    break;
                }
                counter++;
            }
            counter = 0;
            std::cout << std::endl;
            items.push_back(Item(tempID, tempX, tempY, tileSize));
        }

        std::list<Item>::iterator itr_item;
        for(itr_item = items.begin(); itr_item != items.end(); ++itr_item)
            itr_item->sprite.setTexture(imageManager.getImage(itr_item->id));
    }
    else
    {
        std::cout << "Items file at '" << filepath << "/items.txt' was not found!" << std::endl;
    }
    file.close();
}

// Update method, called every loop and is used to change tile colours for the most part.
void Level::update(std::list<sf::Vector2i> p_visibleTiles)
{
    // Iterators for iterating
    std::list<sf::Vector2i>::iterator itr_vector2i;
    std::list<Item>::iterator itr_item;

    // Reverting the tile colours from last time
    revertTileColors();

    // Reverting the item flags from last time
    revertItemFlags();

    // Iterating through the tiles the player can see
    for(itr_vector2i = p_visibleTiles.begin(); itr_vector2i != p_visibleTiles.end(); ++itr_vector2i)
    {
        // Changing the color of tiles that the player can see
        tiles[itr_vector2i->x][itr_vector2i->y].sprite.setColor(sf::Color::White);

        // Changing the flags of the items that the player can see
        for(itr_item = items.begin(); itr_item != items.end(); ++itr_item)
        {
            if ( itr_item->getGridLoc(tileSize).x == itr_vector2i->x
               &&itr_item->getGridLoc(tileSize).y == itr_vector2i->y)
            {
                itr_item->seen = true;
                itr_item->visible = true;
            }
        }
    }

    /// TODO: GET ITEM VISIBILITY WORKING CORRECTLY.

    // Setting the colours of items based on their flags
    // (doing this above would have it done multiple times per frame as it was nested)
    for(itr_item = items.begin(); itr_item != items.end(); ++itr_item)
    {
        if (itr_item->visible)
            itr_item->sprite.setColor(sf::Color::White);
        else if (itr_item->seen)
            itr_item->sprite.setColor(sf::Color(128,128,128));
        else
            itr_item->sprite.setColor(sf::Color::Transparent);
    }
}

// Draw method, takes a const reference to the window
void Level::draw(sf::RenderWindow& window)
{
    std::list<Item>::iterator itr_item;
    // Drawing the tiles
    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            window.draw(tiles[i][j].getSprite());
        }
    }

    // Drawing the items
    for(itr_item = items.begin(); itr_item != items.end(); ++itr_item)
        window.draw(itr_item->sprite);
}

// Changes the colour of tiles to what they were originally
void Level::revertTileColors()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            tiles[i][j].sprite.setColor(sf::Color(128,128,128));
        }
    }
}

// Resets the visiblity flag on items
void Level::revertItemFlags()
{
    std::list<Item>::iterator itr_item;
    for (itr_item = items.begin(); itr_item != items.end(); ++itr_item)
        itr_item->visible = false;
}

Level::~Level()
{
    //dtor
}

// Accessor methods
Level::TilePtr Level::getTiles()
{
    return tiles;
}
Tile Level::getTile(int x, int y) { return tiles[x][y]; }
sf::Vector2i Level::getSpawn() { return playerSpawn; }
const int Level::getTileSize() { return tileSize; }
