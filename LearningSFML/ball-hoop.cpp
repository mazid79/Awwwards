//#include <iostream>
//#include <sfml/graphics.hpp>
//#include <sfml/system.hpp>
//#include <sfml/window.hpp>
//#include <sfml/audio.hpp>
//#include <sfml/network.hpp>
//
//int main() {
//
//	sf::RenderWindow window(sf::VideoMode(800, 600), "OWN", sf::Style::Default);
//	window.setFramerateLimit(60);
//
//	//hoop
//	int dir = 0;
//	sf::CircleShape hoop(50.f);
//	hoop.setFillColor(sf::Color::Black);
//
//	//ball
//	bool isShot = false;
//	sf::CircleShape ball(30.f);
//	ball.setFillColor(sf::Color::Cyan);
//	ball.setPosition(sf::Vector2f(0, window.getSize().y - ball.getRadius()*3));
//
//	//Running / close Loop
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		if (event.type == sf::Event::Closed)
//		{
//			window.close();
//		}
//		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//		{
//			window.close();
//		}
//
//		//Update hoop position
//		if (hoop.getPosition().x <= 0)
//		{
//			dir = 0;
//		}
//		else if (hoop.getPosition().x  + hoop.getRadius()*2 >= window.getSize().x)
//		{
//			dir = 1;
//		}
//
//		if (dir == 0)
//		{
//			hoop.move(5.f, 0);
//		}
//		else
//			hoop.move(-5.f, 0);
//
//		//Update ball
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//			isShot = true;
//
//		if(!isShot)
//			ball.setPosition(sf::Mouse::getPosition(window).x, ball.getPosition().y);
//
//		if (isShot)
//		{
//			ball.move(0,-10.f);
//		}
//	
//		//Collission ball
//		if (ball.getPosition().y < 0 || ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
//		{
//			//Reset Ball
//			isShot = false;
//			ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius() * 3);
//		}
//
//		//Ball Collission to wall on X-axis
//		if (ball.getPosition().x <= 0)
//		{
//			ball.setPosition(0, ball.getPosition().y);
//		}
//		else if (ball.getPosition().x + ball.getRadius() * 2 >= window.getSize().x)
//		{
//			ball.setPosition(window.getSize().x - ball.getRadius()*2, ball.getPosition().y);
//		}
//
//		//clear
//		window.clear(sf::Color(30, 79, 89));
//
//		//Draw
//		window.draw(hoop);
//		window.draw(ball);
//
//		//Display
//		window.display();
//
//	}
//
//	return 0;
//}