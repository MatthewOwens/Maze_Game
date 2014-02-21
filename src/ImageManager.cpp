#include "ImageManager.h"
#include <iostream>

ImageManager::ImageManager()
{
    // Loading images that will be used throughout the program
    loadImage("assets/playerSprite.png", "playerSprite");
    loadImage("assets/diamondSprite.png", "diamond");
    loadImage("assets/rubySprite.png", "ruby");
    loadImage("assets/necklaceSprite.png", "necklace");
    loadImage("assets/ingotSprite.png", "ingot");
    loadImage("assets/guardSprite.png", "guardSprite");
    loadImage("assets/weaponSprite.png", "weaponSprite");
}

ImageManager::~ImageManager()
{
    //dtor
}

void ImageManager::loadImage(const std::string& fileName)
{
    // Loading the texture
    sf::Texture tempTexture;
    if (!tempTexture.loadFromFile(fileName))
        std::cout << "Error loading " << fileName << std::endl;

    // Adding the texture to the map
    images[fileName] = tempTexture;
}

void ImageManager::loadImage(std::string fileName, std::string key)
{
    // Loading the texture
    sf::Texture tempTexture;
    if (!tempTexture.loadFromFile(fileName))
        std::cout << "Error loading " << fileName << std::endl;

    // Adding the texture to the map
    images[key] = tempTexture;
}

sf::Texture& ImageManager::getImage(std::string key)
{
    return images[key];
    std::cout << images[key].getSize().x << " " << images[key].getSize().y << std::endl;
}
