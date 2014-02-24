#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <map>
#include <SFML/Window/Keyboard.hpp>

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        void update();
        void setPreviousValues();
        std::string getInput();
        bool getBooleanValues(std::string key);
    private:
        std::map<std::string, bool> booleanValues;
        std::map<std::string, bool> previousValues;
        std::string input;
};

#endif // INPUTMANAGER_H
