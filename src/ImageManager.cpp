#include "ImageManager.h"

ImageManager::ImageManager()
{
    //ctor
}

ImageManager::~ImageManager()
{
    //dtor
}

void ImageManager::loadImage(std::string fileName)
{
    // Loading the texture
    sf::Texture tempTexture;
    tempTexture.loadFromFile(filename);

    // Adding the texture to the map
    images[filename] = tempTexture;
}

void ImageManager::loadImage(std::string fileName, std::string key)
{
    // Loading the texture
    sf::Texture tempTexture;
    tempTexture.loadFromFile(filename);

    // Adding the texture to the map
    images[key] = tempTexture;
}

sf::Texture ImageManager::getImage(std::string key)
{

}
