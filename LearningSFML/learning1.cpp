//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//
//int main() {
//
//	//Render Window
//	sf::RenderWindow window(sf::VideoMode(800, 600), "learn", sf::Style::Default);
//	window.setFramerateLimit(60);
//
//	//Make circle shape
//	sf::CircleShape circle(50.f,3);
//	circle.setPosition(sf::Vector2f(100.f, 100.f));
//	circle.setFillColor(sf::Color(230,150,87,150));
//	circle.setOrigin(sf::Vector2f(50.f, 50.f));
//	circle.setOutlineColor(sf::Color::Black);
//	circle.setOutlineThickness(4.f);
//
//	//Make rectangle shape
//	sf::RectangleShape rectangle(sf::Vector2f(50.f, 65.f));
//	rectangle.setPosition(sf::Vector2f(700.f, 350.f));
//	rectangle.setFillColor(sf::Color::Magenta);
//	rectangle.setOrigin(sf::Vector2f(25.f, 32.5f));
//
//	//Make a line
//	sf::Vertex line[] = { sf::Vertex(sf::Vector2f(400.f,150.f)), sf::Vertex(sf::Vector2f(400.f, 500.f)) };
//
//	//Make a convex shape
//	sf::ConvexShape convex(5);
//	convex.setPosition(sf::Vector2f(200.f, 250.f));
//	//Define points
//	convex.setPoint(0, sf::Vector2f(200.f, 50.f));
//	convex.setPoint(1, sf::Vector2f(250.f, 70.f));
//	convex.setPoint(2, sf::Vector2f(150.f, 150.f));
//	convex.setPoint(3, sf::Vector2f(50.f, 120.f));
//	convex.setPoint(4, sf::Vector2f(180.f, 69.f));
//
//
//	//Window open  / close loop
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
//			{
//				window.close();
//			}
//			
//		}
//
//		//Update
//		circle.move(0.5f, 0.f);
//		circle.rotate(50.f);
//		rectangle.move(-0.5f, 0.f);
//		rectangle.rotate(20.f);
//		convex.rotate(2.f);
//		
//		
//		//Clear
//		window.clear(sf::Color(34, 67, 165));
//
//		//Draw
//		window.draw(rectangle);
//		window.draw(circle);
//		window.draw(line, 2, sf::Lines);
//		window.draw(convex);
//
//
//		//Display
//		window.display();
//	}
//
//	return 0;
//}