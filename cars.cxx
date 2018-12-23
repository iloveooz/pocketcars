	// небольшие покатушки на машинках
	#include <SFML/Graphics.hpp>
	#include <cmath>
	
	int main() {
		
		sf::RenderWindow app(sf::VideoMode(640, 480), "ROCK'N'ROLL RACING (not BLIZZARD)");
		app.setFramerateLimit(60);
		
		sf::Texture tBackground, tCar;
		tBackground.loadFromFile("images/background.png");
		tCar.loadFromFile("images/car.png");
		
		sf::Sprite sBackground(tBackground), sCar(tCar);
		sCar.setPosition(300, 300);
		
		// центр всех преобразований фигуры
		sCar.setOrigin(22, 22);
		
		float x = 300.0, y = 300.0;
		float speed = 0.0, angle = 0.0;
		float maxSpeed = 12.0;
		float acc = 0.2, dec = 0.3;
		float turnSpeed = 0.08;
		
		
		
		
		
		while (app.isOpen()) {
			sf::Event e;
			
			while (app.pollEvent(e)) {
				if (e.type == sf::Event::Closed) 
					app.close();
			}
		
			bool Up = 0.0, Right = 0.0, Down = 0.0, Left = 0.0;
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    Up = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Right = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Down = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  Left = 1;
			
			// движение машинки
			if (Up && speed < maxSpeed) {
				if (speed < 0) 
					speed += dec;
				else 
					speed += acc;
			}
			
			if (Down && speed > -maxSpeed) {
				if (speed > 0) 
					speed -= dec;
				else 
					speed -= acc;
			}
			
			if (!Up && !Down) {
				if (speed - dec > 0)
					speed -= dec;
				else if (speed + dec < 0)
					speed += dec;
				else 
					speed = 0;
			}
			
			if (Right && speed != 0) 
				angle += turnSpeed * speed / maxSpeed;
			if (Left && speed != 0)
				angle -= turnSpeed * speed / maxSpeed;
			
			x += sin(angle) * speed;
			y -= cos(angle) * speed;
			
			
			// draw
			app.clear(sf::Color::White);
			app.draw(sBackground);
			
			sCar.setPosition(x, y);
			sCar.setRotation(angle * 180 / 3.141592);
			sCar.setColor(sf::Color::Red);
			app.draw(sCar);
			
			app.display();	
		}
		
		return 0;
	}
