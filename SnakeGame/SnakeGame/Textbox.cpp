#include "Textbox.h"

Textbox::Textbox()
{
	setup(5, 9, 200, sf::Vector2f(0, 0));
}

Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox()
{
	clear();
}

void Textbox::setup(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	numVisible = visible;

	sf::Vector2f offset(2.0f, 2.0f);

	font.loadFromFile("arial.ttf");
	content.setFont(font);
	content.setString("");
	content.setCharacterSize(charSize);
	content.setFillColor(sf::Color::White);
	content.setPosition(screenPos + offset);

	backdrop.setSize(sf::Vector2f(width, (visible * (charSize * 1.2f))));
	backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	backdrop.setPosition(screenPos);
}

void Textbox::add(std::string message)
{
	messages.push_back(message);
	if (messages.size() < 6) { return; }
	messages.erase(messages.begin());
}

void Textbox::clear()
{
	messages.clear();
}

void Textbox::render(sf::RenderWindow& wind)
{
	std::string con;

	for (auto &itr : messages)
		con.append(itr + "\n");

	if (con != "")
	{
		content.setString(con);
		wind.draw(backdrop);
		wind.draw(content);
	}
}



