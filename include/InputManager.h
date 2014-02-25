#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <map>
#include <SFML/Graphics.hpp>

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        void update(sf::RenderWindow &window);
        void setPreviousValues();
        std::string getInput();
        bool getBooleanValues(std::string key);
    private:
        std::map<std::string, bool> booleanValues;
        std::map<std::string, bool> previousValues;
        std::string input;
};

#endif // INPUTMANAGER_H
