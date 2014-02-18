/// The ImageManager class is responsible for loading images from a file and
/// storing them in SFML2 texture objects. This is done using a map with the
/// image's filename as the key for the texture object. As an alternative,
/// a seperate key can be specified along with the filename

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
