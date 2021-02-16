#include "../main.h"

std::string getUserInput(GameWindow* window)
{   
    std::string input;
    sf::Event event;
    bool stop = false;
    while (!stop)
    {
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::TextEntered:
                window->menu->textbox->typedOn(event);
                if (event.text.unicode == ENTER_KEY)
                {
                    stop = true;
                    input = window->menu->textbox->getText();
                    window->menu->textbox->setText("");
                }
                break;

            default:
                break;
            }
        }
        window->clear();
        drawScreen(window);
        window->display();
    }
    return input;
}


std::string getCharElementFromUser(GameMenu* menu)
{
    menu->setRequest("Enter element of character to add (air/earth/fire/water)");
    std::string element;
    bool validElement = false;
    while (!validElement)
    {
        element = getUserInput(menu->window);
        std::transform(element.begin(), element.end(), element.begin(), [](unsigned char c){ return std::tolower(c); });
        if (element == "air" || element == "earth" || element == "fire" || element == "water")
            validElement = true;
        else
            menu->setRequest("Invalid element. Enter element of character to add (air/earth/fire/water)");
    }
    return element;
}


std::string getCharNameFromUser(GameMenu* menu)
{
    menu->setRequest("Enter name of character to add");
    std::string name;
    bool validName = false;
    while (!validName)
    {
        name = getUserInput(menu->window);
        if (name != "")
            validName = true;
        else
            menu->setRequest("Character must have a name");
    }
    return name;
}


std::string getCharLifeFromUser(GameMenu* menu)
{
    menu->setRequest("Enter max HP of character to add (10-100)");
    std::string life;
    bool validLife = false;
    while (!validLife)
    {
        life = getUserInput(menu->window);
        if (stringIsNumeric(life) && stoi(life) >= 10 && stoi(life) <= 100)
            validLife = true;
        else
            menu->setRequest("Invalid max HP value. Valid values are 10 to 100");
    }
    return life;
}


std::string getCharShieldFromUser(GameMenu* menu)
{
    menu->setRequest("Enter shield of character to add (0/1/2)");
    std::string shield;
    bool validShield = false;
    while (!validShield)
    {
        shield = getUserInput(menu->window);
        if (shield == "0" || shield == "1" || shield == "2")
            validShield = true;
        else
            menu->setRequest("Invalid shield value. Valid values are 0, 1, and 2");
    }
    return shield;
}


sf::Vector2f getPositionFromUser(GameMenu* menu)
{
    std::string input;
    sf::Vector2f position;
    bool validPos = false;
    while (!validPos)
    {
        input = getUserInput(menu->window);
        if (!validPosition(input))        
            menu->setRequest("Invalid position. Enter X,Y with X and Y between 0 and 7");
        else
        {
            position = parseStringToVector2f(input);
            validPos = true;
        }
    }
    return position;
}


sf::Vector2f getDestinationFromUser(GameMenu* menu)
{
    Character* character = menu->window->world->currentCharacter;
    menu->setRequest("Enter where you would like to move: (ex: 2,5)");
    sf::Vector2f destination;
    bool validDest = false;
    while (!validDest)
    {
        destination = getPositionFromUser(menu);
        validDest = validMoveDestination(menu, character, destination);
    }
    return destination;
}