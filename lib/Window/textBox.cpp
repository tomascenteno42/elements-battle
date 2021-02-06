#include "../../src/main.h"

Textbox::Textbox(int size, sf::Color color, bool sel, sf::Font &font)
{
	text.setCharacterSize(size);
	text.setFillColor(color);
	isSelected = sel;

	// Check if the textbox is selected upon creation and display it accordingly:
	if (isSelected)
		text.setString("_");
	else
		text.setString("");

	setFont(font);
	setPosition({30, 625});
}

void Textbox::setFont(sf::Font &fonts)
{
	text.setFont(fonts);
}

void Textbox::setPosition(sf::Vector2f point)
{
	text.setPosition(point);
}

// Set char limits:
void Textbox::setLimit(bool ToF)
{
	hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim)
{
	hasLimit = ToF;
	limit = lim - 1;
}

// Change selected state:
void Textbox::setSelected(bool sel)
{
	isSelected = sel;

	// If not selected, remove the '_' at the end:
	if (!sel)
  {
		std::string t = textStream.str();
		std::string newT = "";
    
		for (unsigned int i = 0; i < t.length(); i++)
			newT += t[i];
    
		text.setString(newT);
	}
}

void Textbox::setText(std::string text)
{
	textStream.str(text);
	this->text.setString(textStream.str() + "_");
}

std::string Textbox::getText()
{
	return textStream.str();
}

void Textbox::drawTo(sf::RenderWindow &window)
{
	window.draw(text);
}

// Function for event loop:
void Textbox::typedOn(sf::Event input)
{
	if (isSelected)
  {
		unsigned int charTyped = input.text.unicode;

		// Only allow normal inputs:
		if (charTyped < 128)
    {
			if (hasLimit)
      {
				// If there's a limit, don't go over it:

				if (textStream.str().length() <= limit)
					inputLogic(charTyped);
				// But allow for char deletions:
				else if (textStream.str().length() > limit && charTyped == DELETE_KEY)
					deleteLastChar();
        
			}
			// If no limit exists, just run the function:
			else
				inputLogic(charTyped);
		}
	}
}
