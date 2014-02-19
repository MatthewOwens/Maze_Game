#include "Level.h"

// Constructor, ImageManager is not const as it needs to be manipulated
Level::Level(const std::string& filename, ImageManager &imageManager)
{
    std::istringstream convert;
    std::ifstream file;
    int counter = 0;    // Used for navigating the files
    std::string line;

    // Loading this level's tilesheet
    imageManager.loadImage(filename + "/tilesheet.png");

    // Opening the map file
    file.open(filename + "/map.txt");

    // Parsing the map file
    while(std::getline(file, line))
    {
        for (int i = 0; i < 10; i++)
        {
            if(line[i] != 's')
                tiles[i][counter] = Tile(imageManager.getImage(filename + "/tilesheet.png"), tileSize, line[i] - '0', i, counter);
            else
            {
                tiles[i][counter] = Tile(imageManager.getImage(filename + "/tilesheet.png"), tileSize, 0, i, counter);
                playerSpawn = sf::Vector2i(i * tileSize, counter * tileSize);
            }
            std::cout << line[i];
        }
        counter++;
        std::cout << std::endl;
    }
}

// Draw method, takes a const reference to the window
void Level::draw(sf::RenderWindow& window)
{
    // Drawing the tiles
    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            window.draw(tiles[i][j].getSprite());
        }
    }
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
