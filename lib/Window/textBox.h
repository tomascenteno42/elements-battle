#ifndef TEXT_BOX
#define TEXT_BOX

#include "../../src/main.h"

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox(int size, sf::Color color, bool sel, sf::Font &font);

	// Make sure font is passed by reference:
	void setFont(sf::Font &fonts);
	void setPosition(sf::Vector2f point);

	// Set char limits:
	void setLimit(bool ToF);

	void setLimit(bool ToF, int lim);

	// Change selected state:
	void setSelected(bool sel);

	void setText(std::string text);

	std::string getText();

	void drawTo(sf::RenderWindow &window);

	// Function for event loop:
	void typedOn(sf::Event input);
private:

	sf::Text text;

	std::ostringstream textStream;

	bool isSelected = false;
	bool hasLimit = false;
	unsigned int limit = 0;

	// Delete the last character of the text:
	void deleteLastChar()
  {
		std::string t = textStream.str();

		std::string newT = "";
		for (unsigned int i = 0; i < t.length() - 1; i++)
			newT += t[i];

		textStream.str("");
		textStream << newT;
		text.setString(textStream.str() + "_");
	}

	// Get user input:
	void inputLogic(int charTyped)
  {
		// If the key pressed isn't delete, or the two selection keys, then append the text with the char:
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
			textStream << static_cast<char>(charTyped);

		// If the key is delete, then delete the char:
		else if (charTyped == DELETE_KEY)
    {
			if (textStream.str().length() > 0)
				deleteLastChar();
		}
		// Set the textbox text:

		text.setString(textStream.str() + "_");
	}
};

#endif
