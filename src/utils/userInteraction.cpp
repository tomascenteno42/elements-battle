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