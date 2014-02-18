#include "ImageManager.h"
#include <iostream>

ImageManager::ImageManager()
{
    //ctor
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
    tempTexture.loadFromFile(fileName);

    // Adding the texture to the map
    images[key] = tempTexture;
}

sf::Texture& ImageManager::getImage(std::string key)
{
    return images[key];
    std::cout << images[key].getSize().x << " " << images[key].getSize().y << std::endl;
}
