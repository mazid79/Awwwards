//#include <iostream>
//#include <sfml/graphics.hpp>
//#include <sfml/system.hpp>
//#include <sfml/window.hpp>
//#include <sfml/audio.hpp>
//#include <sfml/network.hpp>
//
//int main() {
//
//	sf::RenderWindow window(sf::VideoMode(800, 600), "moving", sf::Style::Default);
//	window.setFramerateLimit(60);
//
//	//Function def
//	void Update(sf::CircleShape &Player, sf::CircleShape &hoop, sf::RenderWindow &window);
//	void Draw(sf::RenderWindow &window, sf::CircleShape & Player, sf::CircleShape &hoop);
//
//	//Hoop
//	int dir = 0;
//	sf::CircleShape hoop(50.f);
//	hoop.setFillColor(sf::Color::Black);
//
//	//Player
//	sf::CircleShape Player(50.f);
//	Player.setFillColor(sf::Color(230, 145, 65));
//	Player.setPosition(sf::Vector2f(400.f, 400.f));
//	Player.setOrigin(sf::Vector2f(50.f, 50.f));
//
//
//	//Game open / close loop
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//				window.close();
//
//			if (event.type == sf::Event::MouseMoved)
//			{
//				int mouseX = event.mouseMove.x;
//				int mouseY= event.mouseMove.y;
//				//std::cout << "MousePos: " << mouseX << "," << mouseY << "\n";
//
//			}
//		}
//
//		//Hoop movement
//		if (hoop.getPosition().x <= 0)
//		{
//			dir = 1;
//		}
//		else if (hoop.getPosition().x + hoop.getRadius()*2 >= window.getSize().x)
//		{
//			dir = 0;
//		}
//
//		if (dir == 1)
//		{
//			hoop.move(5.f, 0);
//		}
//		else
//		{
//			hoop.move(-5.f, 0);
//		}
//		
//		Update(Player, hoop, window);
//		window.draw(hoop);
//		Draw(window, hoop, Player);
//	}
//
//	return 0;
//}
//
////Updating
//void Update(sf::CircleShape &Player, sf::CircleShape &hoop, sf::RenderWindow &window)
//{
//	//Player Movement by keyboard
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && Player.getPosition().y - 50.f > 0)
//	{
//		Player.move(0.f, -5.f);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Player.getPosition().y + 50.f < window.getSize().y)
//	{
//		Player.move(0.f, 5.f);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Player.getPosition().x - 50.f > 0)
//	{
//		Player.move(-5.f, 0.f);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Player.getPosition().x + 50.f < window.getSize().x)
//	{
//		Player.move(5.f, 0.f);
//	}
//
//	//Player color change
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//	{
//		Player.setFillColor(sf::Color(96, 214, 202));
//	}
//	else
//		Player.setFillColor(sf::Color(230, 145, 65));
//
//	
//}
////Rendering
//void Draw(sf::RenderWindow &window, sf::CircleShape& Player, sf::CircleShape &hoop)
//{
//	window.clear(sf::Color(30, 69, 71));
//
//	//Draw stuff
//	window.draw(hoop);
//	window.draw(Player);
//	
//	window.display();
//}