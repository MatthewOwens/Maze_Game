#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <SFML/Graphics.hpp>
#include <map>


class ImageManager
{
    public:
        ImageManager();
        virtual ~ImageManager();

        void loadImage(const std::string& fileName);
        void loadImage(std::string fileName, std::string key);
        sf::Texture& getImage(std::string key);
    private:
        std::map<std::string, sf::Texture> images;
};

#endif // IMAGEMANAGER_H
