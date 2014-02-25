#include "InputManager.h"

InputManager::InputManager()
{
    // Clearing the maps
    booleanValues.clear();
    previousValues.clear();
}

InputManager::~InputManager()
{
    //dtor
}


void InputManager::update(sf::RenderWindow &window)
{
    booleanValues.clear();
    sf::Event event;

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case (sf::Event::Closed):
                booleanValues["WindowClosed"] = true;
                break;
            case (sf::Event::KeyPressed):
                booleanValues["QPressed"] = (event.key.code == sf::Keyboard::Q);
                booleanValues["WPressed"] = (event.key.code == sf::Keyboard::W);
                booleanValues["EPressed"] = (event.key.code == sf::Keyboard::E);
                booleanValues["RPressed"] = (event.key.code == sf::Keyboard::R);
                booleanValues["TPressed"] = (event.key.code == sf::Keyboard::T);
                booleanValues["YPressed"] = (event.key.code == sf::Keyboard::Y);
                booleanValues["UPressed"] = (event.key.code == sf::Keyboard::U);
                booleanValues["IPressed"] = (event.key.code == sf::Keyboard::I);
                booleanValues["OPressed"] = (event.key.code == sf::Keyboard::O);
                booleanValues["PPressed"] = (event.key.code == sf::Keyboard::P);
                booleanValues["APressed"] = (event.key.code == sf::Keyboard::A);
                booleanValues["SPressed"] = (event.key.code == sf::Keyboard::S);
                booleanValues["DPressed"] = (event.key.code == sf::Keyboard::D);
                booleanValues["FPressed"] = (event.key.code == sf::Keyboard::F);
                booleanValues["GPressed"] = (event.key.code == sf::Keyboard::G);
                booleanValues["HPressed"] = (event.key.code == sf::Keyboard::H);
                booleanValues["JPressed"] = (event.key.code == sf::Keyboard::J);
                booleanValues["KPressed"] = (event.key.code == sf::Keyboard::K);
                booleanValues["LPressed"] = (event.key.code == sf::Keyboard::L);
                booleanValues["ZPressed"] = (event.key.code == sf::Keyboard::Z);
                booleanValues["XPressed"] = (event.key.code == sf::Keyboard::X);
                booleanValues["CPressed"] = (event.key.code == sf::Keyboard::C);
                booleanValues["VPressed"] = (event.key.code == sf::Keyboard::V);
                booleanValues["BPressed"] = (event.key.code == sf::Keyboard::B);
                booleanValues["NPressed"] = (event.key.code == sf::Keyboard::N);
                booleanValues["MPressed"] = (event.key.code == sf::Keyboard::M);
                booleanValues["EscapePressed"] = (event.key.code == sf::Keyboard::Escape);
                booleanValues["EnterPressed"] = (event.key.code == sf::Keyboard::Return);
                break;
        }
    }
}

std::string InputManager::getInput()
{
    if(booleanValues["QPressed"] && !previousValues["QPressed"])
        input += "q";
    if(booleanValues["WPressed"] && !previousValues["WPressed"])
        input += "w";
    if(booleanValues["EPressed"] && !previousValues["EPressed"])
        input += "e";
    if(booleanValues["RPressed"] && !previousValues["RPressed"])
        input += "r";
    if(booleanValues["TPressed"] && !previousValues["TPressed"])
        input += "t";
    if(booleanValues["YPressed"] && !previousValues["YPressed"])
        input += "y";
    if(booleanValues["UPressed"] && !previousValues["UPressed"])
        input += "u";
    if(booleanValues["IPressed"] && !previousValues["IPressed"])
        input += "i";
    if(booleanValues["OPressed"] && !previousValues["OPressed"])
        input += "o";
    if(booleanValues["PPressed"] && !previousValues["PPressed"])
        input += "p";
    if(booleanValues["APressed"] && !previousValues["APressed"])
        input += "a";
    if(booleanValues["SPressed"] && !previousValues["SPressed"])
        input += "s";
    if(booleanValues["DPressed"] && !previousValues["DPressed"])
        input += "d";
    if(booleanValues["FPressed"] && !previousValues["FPressed"])
        input += "f";
    if(booleanValues["GPressed"] && !previousValues["GPressed"])
        input += "g";
    if(booleanValues["HPressed"] && !previousValues["HPressed"])
        input += "h";
    if(booleanValues["JPressed"] && !previousValues["JPressed"])
        input += "j";
    if(booleanValues["KPressed"] && !previousValues["KPressed"])
        input += "k";
    if(booleanValues["LPressed"] && !previousValues["LPressed"])
        input += "l";
    if(booleanValues["ZPressed"] && !previousValues["ZPressed"])
        input += "z";
    if(booleanValues["XPressed"] && !previousValues["XPressed"])
        input += "x";
    if(booleanValues["CPressed"] && !previousValues["CPressed"])
        input += "c";
    if(booleanValues["VPressed"] && !previousValues["VPressed"])
        input += "v";
    if(booleanValues["BPressed"] && !previousValues["BPressed"])
        input += "b";
    if(booleanValues["NPressed"] && !previousValues["NPressed"])
        input += "n";
    if(booleanValues["MPressed"] && !previousValues["MPressed"])
        input += "m";

    return input;
}

bool InputManager::getBooleanValues(std::string key) {return booleanValues[key];}
bool InputManager::getPreviousValues(std::string key) {return previousValues[key];}
void InputManager::setPreviousValues() {previousValues = booleanValues; }
