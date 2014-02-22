#include "Level.h"
#include <fstream>
#include <sstream>

// Constructor, ImageManager is not const as it needs to be manipulated
Level::Level(const std::string& filepath, ImageManager &imageManager)
{
    std::list<Guard>::iterator itr_guard;

    // Loading this level's tilesheet
    imageManager.loadImage(filepath + "/tilesheet.png");

    // Loading the map
    loadMap(filepath, imageManager);

    // Loading the items
    loadItems(filepath, imageManager);

    // Loading the guards
    loadGuards(filepath, imageManager);

    // Initilizing the collision locations of the guards

    /// ERROR
    for(itr_guard = guards.begin(); itr_guard != guards.end(); ++itr_guard)
        itr_guard->initCollisionTiles(tiles, tileSize);
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

// Loading guards, this method should only be called by the constructor
void Level::loadGuards(const std::string& filepath, ImageManager &imageManager)
{
    std::ifstream file(filepath + "/guards.txt");
    int counter = 0;
    std::string line;
    std::string subString;
    std::istringstream convert;
    std::stringstream ss;


    int tempX;
    int tempY;
    int tempSpeed;
    std::string tempDirection;

    if(file.good())
    {
        while(std::getline(file, line))
        {
            ss.str(line);
            ss.clear();
            while(std::getline(ss, subString, ','))
            {
                switch(counter)
                {
                case 3:
                    convert.str(subString);
                    convert >> tempDirection;
                    convert.clear();
                    break;
                case 0:
                    convert.str(subString);
                    convert >> tempX;
                    convert.clear();
                    break;
                case 1:
                    convert.str(subString);
                    convert >> tempY;
                    convert.clear();
                    break;
                case 2:
                    convert.str(subString);
                    convert >> tempSpeed;
                    convert.clear();
                    break;
                }
                counter++;
            }
            counter = 0;
            std::cout << "Guard values: " << tempDirection << "," << tempX << "," << tempY << "," << tempSpeed<< std::endl;
            guards.push_back(Guard(tempX * tileSize, tempY * tileSize, tempSpeed, tempDirection, imageManager.getImage("guardSprite")));

        }
    }
    else
    {
        std::cout << "Error loading " << filepath + "/guards.txt" << std::endl;
    }
}

// Update method, called every loop and is used to change tile colours and detect
// collision between the player and the items.
void Level::update(std::list<sf::Vector2i> p_visibleTiles, sf::FloatRect p_bounds, sf::FloatRect p_weaponBounds, bool p_attacking)
{
    // Iterators for iterating
    std::list<sf::Vector2i>::iterator itr_vector2i;
    std::list<Item>::iterator itr_item;
    std::list<Guard>::iterator itr_guard;

    guardCollision = false;

    sf::Vector2i p_gridLoc = sf::Vector2i((p_bounds.left + (p_bounds.width / 2)) / tileSize,
                                          (p_bounds.top + (p_bounds.height / 2)) / tileSize);

    // Reverting the tile colours from last time
    revertTileColors();

    // Reverting the item flags from last time
    revertItemFlags();

    // Reverting the guard flags from last time
    revertGuardFlags();

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

        // Changing the guard visiibilty flags
        for(itr_guard = guards.begin(); itr_guard != guards.end(); ++itr_guard)
        {
            if (itr_guard->getGridLoc(tileSize).x == itr_vector2i->x
              &&itr_guard->getGridLoc(tileSize).y == itr_vector2i->y)
            {
                itr_guard->setVisible(true);
            }
        }
    }

    // Updating the sprites
    // (doing this above would have it done multiple times per frame as it was nested)
    for(itr_item = items.begin(); itr_item != items.end(); ++itr_item)
    {
        // Checking for collision
        if (itr_item->sprite.getGlobalBounds().intersects(p_bounds)
            && !itr_item->collected)
        {
            if (itr_item->id == "diamond")
                levelComplete = true;

            itr_item->collected = true;
            levelScore += itr_item->value;
            std::cout << "level score is now " << levelScore << std::endl;
            std::cout << "complete flag is " << levelComplete << std::endl;
        }

        // Changing the colour of the sprites
        if (itr_item->visible)
            itr_item->sprite.setColor(sf::Color::White);
        else if (itr_item->seen)
            itr_item->sprite.setColor(sf::Color(128,128,128));
        else
            itr_item->sprite.setColor(sf::Color::Transparent);

        if (itr_item->collected)
            itr_item->sprite.setColor(sf::Color::Transparent);
    }

    // Updating guards
    for(itr_guard = guards.begin(); itr_guard != guards.end(); ++itr_guard)
    {
        // Only update the guard if it's alive
        if(itr_guard->getAlive())
        {
            std::list<sf::Vector2i> guardVision = itr_guard->getVisibleTiles();

            if(itr_guard->update(tiles, p_bounds, tileSize))
            {
                guardCollision = true;
                reset();
                break;
            }

            if (p_attacking && itr_guard->getBounds().intersects(p_weaponBounds))
            {
                pacifistBonus = false;
                itr_guard->setAlive(false);
                levelScore += 10;
            }

            for(itr_vector2i = guardVision.begin(); itr_vector2i != guardVision.end(); ++itr_vector2i)
            {
                //tiles[itr_vector2i->x][itr_vector2i->y].sprite.setColor(sf::Color::Cyan);
                if(itr_vector2i->x == p_gridLoc.x && itr_vector2i->y == p_gridLoc.y)
                {
                    stealthBonus = false;
                }
            }
        }
    }
}

// Reset method, called when the player dies
void Level::reset()
{
    std::list<Item>::iterator itr_items;
    std::list<Guard>::iterator itr_guard;

    for(itr_guard = guards.begin(); itr_guard != guards.end(); ++itr_guard)
        itr_guard->reset();

    for(itr_items = items.begin(); itr_items != items.end(); ++itr_items)
        itr_items->reset();

    levelScore = 0;
}


// Draw method, takes a const reference to the window
void Level::draw(sf::RenderWindow& window)
{
    std::list<Item>::iterator itr_item;
    std::list<Guard>::iterator itr_guard;
    // Drawing the tiles
    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            window.draw(tiles[i][j].sprite);
        }
    }

    // Drawing the items
    for(itr_item = items.begin(); itr_item != items.end(); ++itr_item)
        window.draw(itr_item->sprite);

    // Drawing the guards
    for(itr_guard = guards.begin(); itr_guard != guards.end(); ++itr_guard)
    {
        if(itr_guard->getAlive() && itr_guard->getVisible())
            window.draw(itr_guard->getSprite());
    }
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

// Resets the visibilty flags on guards
void Level::revertGuardFlags()
{
    std::list<Guard>::iterator itr_guard;
    for (itr_guard = guards.begin(); itr_guard != guards.end(); ++itr_guard)
        itr_guard->setVisible(false);
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
bool Level::getGuardCollision() {return guardCollision; }
