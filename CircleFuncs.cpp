#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;

int mainCircRad = 128;
int mainCircOutline = 2;
int centerDotRad = 8;
int outlinePointRad = 8;
int winWid = 800, winHig = 800;

int main() {
	sf::RenderWindow window(sf::VideoMode(winWid, winHig), "Circle Functions");
	window.setFramerateLimit(60);

	sf::VertexArray grid(sf::Lines, 4);
	grid[0].position = sf::Vector2f(winWid / 2, 0);
	grid[1].position = sf::Vector2f(winWid / 2, winHig);
	grid[2].position = sf::Vector2f(0, winHig / 2);
	grid[3].position = sf::Vector2f(winWid, winHig / 2);

	sf::CircleShape mainCirc(mainCircRad, 64);
	mainCirc.setFillColor(sf::Color::Transparent);
	mainCirc.setOutlineColor(sf::Color::White);
	mainCirc.setOutlineThickness(mainCircOutline);
	mainCirc.setPosition(sf::Vector2f(winWid / 2 - mainCirc.getRadius(), winHig / 2 - mainCirc.getRadius()));

	sf::CircleShape centerDot(centerDotRad);
	centerDot.setFillColor(sf::Color::Red);
	centerDot.setPosition(sf::Vector2f(winWid / 2- centerDot.getRadius(), winHig / 2 - centerDot.getRadius()));

	sf::CircleShape outlinePoint(outlinePointRad);
	outlinePoint.setFillColor(sf::Color::Red);

	sf::VertexArray radLine(sf::LineStrip, 2);
	radLine[0] = sf::Vector2f(winWid / 2, winHig / 2);
	radLine[0].color = sf::Color::Red;
	radLine[1].color = sf::Color::Red;

	sf::VertexArray sinLine(sf::LineStrip, 2);
	sinLine[0].color = sf::Color::Blue;
	sinLine[1].color = sf::Color::Blue;

	sf::VertexArray cosLine(sf::LineStrip, 2);
	cosLine[0].color = sf::Color::Red;
	cosLine[1].color = sf::Color::Red;

	sf::VertexArray tanLine(sf::LineStrip, 2);
	tanLine[0].color = sf::Color::Yellow;
	tanLine[1].color = sf::Color::Yellow;
	tanLine[0].position = sf::Vector2f(winWid / 2 + mainCirc.getRadius(), winHig / 2);

	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("Minecraft.ttf")) {
		cout << "Error loading font.\n";
	}
	text.setFillColor(sf::Color::White);
	text.setFont(font);
	text.setCharacterSize(25);
	text.setPosition(sf::Vector2f(25, 25));
	string txt;

	float currRadians = 0.0f;
	float deltaRad = 6.28f / 420.0f;

	while (window.isOpen()) {
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
		}

		outlinePoint.setPosition(sf::Vector2f(winWid / 2 + cosf(currRadians) * mainCirc.getRadius() - outlinePoint.getRadius(),
												winHig / 2 + sinf(currRadians) * mainCirc.getRadius() - outlinePoint.getRadius()));
		radLine[1].position = sf::Vector2f(outlinePoint.getPosition().x + outlinePoint.getRadius(),
											outlinePoint.getPosition().y + outlinePoint.getRadius());
		sinLine[0].position = sf::Vector2f(winWid / 2 + cosf(currRadians) * mainCirc.getRadius(), winHig / 2);
		sinLine[1].position = radLine[1].position;

		cosLine[0].position = sf::Vector2f(winWid / 2, winHig / 2 + sinf(currRadians) * mainCirc.getRadius());
		cosLine[1].position = radLine[1].position;

		tanLine[1].position = sf::Vector2f(winWid / 2 + mainCirc.getRadius(), winHig / 2 + tanf(currRadians) * mainCirc.getRadius());
		int degAngle = (int)(-currRadians * 57.295f) % 360;

		txt = "Trigonometry Functions\nTheta: " + to_string(degAngle) + " degrees\nSin: " + to_string(-sinf(currRadians)) +
			"\nCos: " + to_string(cosf(currRadians)) + "\nTan: " + to_string(-tanf(currRadians));

		text.setString(txt);

		
		window.clear();
		window.draw(grid);
		window.draw(mainCirc);
		window.draw(centerDot);
		window.draw(sinLine);
		window.draw(cosLine);
		window.draw(tanLine);
		window.draw(outlinePoint);
		window.draw(radLine);
		window.draw(text);
		window.display();

		currRadians -= deltaRad;
	}

	return 0;
}