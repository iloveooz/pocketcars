	// небольшие покатушки на машинках
	#include <SFML/Graphics.hpp>
	
	int main() {
		
		sf::RenderWindow app(sf::VideoMode(640, 480), "ROCK'N'ROLL RACING (not BLIZZARD)");
		app.setFramerateLimit(60);
		
		sf::Texture tBackground, tCar;
		tBackground.loadFromFile("images/background.png");
		tCar.loadFromFile("images/car.png");
		
		sf::Sprite sBackground(tBackground), sCar(tCar);
		sCar.setPosition(300, 300);
		
		while (app.isOpen()) {
			sf::Event e;
			
			while (app.pollEvent(e)) {
				if (e.type == sf::Event::Closed) 
					app.close();
			}
			
			// draw
			app.clear(sf::Color::White);
			app.draw(sBackground);
			
			sCar.setColor(sf::Color::Red);
			app.draw(sCar);
			
			app.display();	
		}
		
		return 0;
	}
