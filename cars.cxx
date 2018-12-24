	// небольшие покатушки на машинках
	
	// TODO сделать, чтобы машинки не выезжали за край карты
	
	#include <SFML/Graphics.hpp>
	#include <cmath>
	#include <string>

	const int N = 5;
	const int Weight = 640; // 960
	const int Height = 480; // 720
	
	// chackpoints
	const int num = 8;
	int points[num][2] = { 
		300, 200,
		660, 230,
		720, 1260,
		960, 1280,
		980, 860,
		1260, 850,
		1260, 1530,
		210, 1650
	};
	
	struct Car {
		std::string name;
		float x, y, speed, angle;
		int n;
		
		Car() {
			name = "car";
			speed = 2.0;
			angle = 0.0;
			n = 0;
		}
		
		void move() {
			x += sin(angle) * speed;
			y -= cos(angle) * speed;
			// angle += 0.08;
			
			float tx = points[n][0];
			float ty = points[n][1];
			
			// плавный поворот
			float beta = angle - atan2(tx - x, -ty + y);
			if (sin(beta) < 0) 
				angle += 0.08;
			else
				angle -= 0.08;
			
			if ((x - tx) * (x - tx) + (y - ty) * (y -ty) < 25 * 25)
				n = (n + 1) % num;
		}
		
	};

	struct Bullet {
		std::string name;
		float x, y, speed, angle;
		
		Bullet () {
			name = "bullet";
			speed = 6.0;
			angle = 0.0;
		}
		
	};

	int main() {
		
		sf::RenderWindow app(sf::VideoMode(Weight, Height), "ROCK'N'ROLL RACING (not BLIZZARD)");
		
		app.setFramerateLimit(60);
		
		// загружаем текстуры
		sf::Texture tBackground, tCar, tExplosion;
		tBackground.loadFromFile("images/background.png");
		tCar.loadFromFile("images/car.png");
		tExplosion.loadFromFile("images/explosion.png");
		
		// создаем спрайты
		sf::Sprite sBackground(tBackground);
		sf::Sprite sCar(tCar);
		sf::Sprite sExplosion(tExplosion);
		
		// параметры спрайтов
		sExplosion.setPosition(300, 200);
		sCar.setPosition(300, 300);
		
		
		
		// центр всех преобразований фигуры
		sCar.setOrigin(22, 22);
		
		Car car[N];
		
		for (int i = 0; i < N; i++) {
			car[i].x = 300 + i * 50;
			car[i].y = 1700 + i * 80;
			car[i].speed = 7 + i;
		}
		
		
		// float x = 300.0, y = 300.0;
		float speed = 0.0, angle = 0.0;
		float maxSpeed = 12.0;
		float acc = 0.2, dec = 0.3;
		float turnSpeed = 0.08;
		
		int offsetX = 0, offsetY = 0;
		
		float Frame = 0;
		float animSpeed = 0.3;
		int frameCount = 20;
		
		while (app.isOpen()) {
			sf::Event e;
			
			while (app.pollEvent(e)) {
				if (e.type == sf::Event::Closed) 
					app.close();
			}
			
			// пример анимации спрайта
			Frame += animSpeed;
			if (Frame > frameCount) 
				Frame -= frameCount;
				
			sExplosion.setTextureRect(sf::IntRect(int(Frame) * 256, 0, 256, 256));
			
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
			
			// x += sin(angle) * speed;
			// y -= cos(angle) * speed;
			
			
			// управление машинкой
			// car[0].speed = speed;
			// car[0].angle = angle;
			
			for (int i = 0; i < N; i++) 
				car[i].move();
				
			float R = 22;
			
			// столкновения
			for (int i = 0; i < N; i++) 
				for (int j = 0; j < N; j++) {
					int dx = car[i].x - car[j].x;
					int dy = car[i].y - car[j].y;
					
					if (dx * dx + dy * dy < 4 * R * R) {
						car[i].x += dx / 10;
						car[i].x += dy / 10;
						car[j].x -= dx / 10;
						car[j].y -= dy / 10;
					}
				}
			
			// чтобы экран не вылезал за границы
			if (car[0].x > 320) offsetX = car[0].x - 320;
			if (car[0].y > 240) offsetY = car[0].y - 240;
						
			// draw
			app.clear(sf::Color::White);
			sBackground.setPosition(-offsetX, -offsetY);
			app.draw(sBackground);
			
			sf::Color colors[10] = {
				sf::Color::Red,
				sf::Color::Green, 
				sf::Color::Magenta,
				sf::Color::Blue,
				sf::Color::White
			};
			
			for (int i = 0; i < N; i++) {
				sCar.setPosition(car[i].x - offsetX, car[i].y - offsetY);
				sCar.setRotation(car[i].angle * 180 / 3.141592);
				sCar.setColor(colors[i]);
				app.draw(sCar);
			}
			
			app.draw(sExplosion);
			
			app.display();	
		}
		
		return 0;
	}
