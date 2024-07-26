#include <iostream>
#include <sfml/graphics.hpp>
#include <sfml/system.hpp>
#include <sfml/window.hpp>
#include <sfml/audio.hpp>
#include <sfml/network.hpp>
#include <cstdlib>
#include <cstring>

int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1024, 1080), "Space Lurker", sf::Style::Default);
	sf::Image topIcon;
	topIcon.loadFromFile("Textures/startrek.png");
	// Set the window icon
	window.setIcon(topIcon.getSize().x, topIcon.getSize().y, topIcon.getPixelsPtr());
	window.setFramerateLimit(60);

	//Background
	/*sf::Texture backTex;
	backTex.loadFromFile("Textures/Background.png");

	sf::Sprite Background;
	Background.setTexture(backTex);
	Background.setPosition(0,0);*/

	//Player
	bool Mousemove = false;
	sf::Texture playerTex;
	playerTex.loadFromFile("Textures/Spaceship.png");

	sf::Sprite Player;
	Player.setTexture(playerTex);
	Player.setScale(sf::Vector2f(0.3f,0.3f));
	//sf::RectangleShape Player(sf::Vector2f(50.f, 50.f));
	//Player.setFillColor(sf::Color::Magenta);
	Player.setPosition(sf::Vector2f(window.getSize().x / 2 - Player.getGlobalBounds().width / 2, window.getSize().y - Player.getGlobalBounds().height * 2));
	sf::Vector2f Playercenter;
	
	
	//Player Score and Health // Variable stuffs
	int shootTimer = 0;
	int PlayerHealth = 15;
	int PlayerScore = 0;

	//Pojectile
	//sf::CircleShape Projectile(5.f);
	//Projectile.setFillColor(sf::Color::Red);
	sf::Texture Bullet;
	Bullet.loadFromFile("Textures/Bullet.png");

	sf::Sprite Projectile;
	Projectile.setTexture(Bullet);
	Projectile.setScale(sf::Vector2f(0.4f,0.4f));

	//Enemy
	//sf::RectangleShape Enemy(sf::Vector2f(30.f,30.f));
	//Enemy.setFillColor(sf::Color(54, 66, 143));
	sf::Texture enemyTex;
	enemyTex.loadFromFile("Textures/enemy.png");

	sf::Sprite Enemy;
	Enemy.setTexture(enemyTex);
	Enemy.setScale(sf::Vector2f(1.f,1.f));
	int EnemySpawnTimer = 5;

	//Vector of Enemies and Projectiles
	std::vector <sf::Sprite> Projectiles;
	Projectiles.push_back(sf::Sprite(Projectile));

	std::vector <sf::Sprite> Enemies;
	Enemies.push_back(sf::Sprite(Enemy));

	//Font
	sf::Font font;
	font.loadFromFile("Fonts/Fluff.ttf");

	//Game Over Text
	sf::Text text;
	bool gameOver = false;
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setString("GAME OVER!");
	text.setCharacterSize(70);

	//Final Score Text
	sf::Text finalScoreText;
	finalScoreText.setFont(font);
	finalScoreText.setCharacterSize(50);
	finalScoreText.setFillColor(sf::Color(75, 25, 145));
	finalScoreText.setOutlineColor(sf::Color::White);
	finalScoreText.setOutlineThickness(1);

	//Replay Text
	sf::Text replayText;
	replayText.setFont(font);
	replayText.setCharacterSize(45);
	replayText.setFillColor(sf::Color::White);
	//replayText.setOutlineColor(sf::Color::White);
	//replayText.setOutlineThickness(1);

	//UI Text for Score
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setPosition(10.0f, 10.0f);

	//UI Text for Health
	sf::Text healthText;
	healthText.setFont(font);
	healthText.setCharacterSize(20);
	healthText.setFillColor(sf::Color::Green);
	healthText.setPosition(10.0f, 40.0f);

	//Get the local bounds of the text (width and height)
	sf::FloatRect textRect = text.getGlobalBounds();

	//Calculate the position to center the text
	text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	text.setPosition(sf::Vector2f(window.getSize().x / 2 , window.getSize().y / 2));

	
	//Game Running / Closing Loop
	while (window.isOpen())
	{
		while (!gameOver && window.isOpen())
		{ 
			sf::Event event;
			while (window.pollEvent(event))
			{ 
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				else if (event.type == sf::Event::Resized)
				{
					// Update the view to the new window size
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));

					// Recalculate positions of UI elements
					//Background.setPosition(0, 0);
					text.setPosition(event.size.width / 2.0f, event.size.height / 2.0f - 50);
					finalScoreText.setPosition(event.size.width / 2.0f - finalScoreText.getLocalBounds().width / 2.0f, event.size.height / 2.0f - 200.f);
					replayText.setPosition(event.size.width / 2.0f - replayText.getLocalBounds().width / 2.0f, event.size.height / 2.0f + 120);
					healthText.setPosition(10.0f, 40.0f);
					scoreText.setPosition(10.0f, 10.0f);
				}
			}

			//////Update Player / Enemy / Projectile //////
			//UpdatePlayer
			if (!Mousemove)
			{
				Player.setPosition(sf::Mouse::getPosition(window).x, Player.getPosition().y);
			}
			//Player collision by X-axis wall
			if (Player.getPosition().x <= 0)
			{
				Player.setPosition(0, Player.getPosition().y);
			}
			if (Player.getPosition().x + Player.getGlobalBounds().width >= window.getSize().x)
			{
				Player.setPosition(window.getSize().x - Player.getGlobalBounds().width, Player.getPosition().y);
			}

			//Update Projectile / SHOOTING
			Playercenter = sf::Vector2f(Player.getPosition().x + Player.getGlobalBounds().width / 2 - Projectile.getGlobalBounds().width / 2, Player.getPosition().y + Player.getGlobalBounds().height / 2 - Projectile.getGlobalBounds().height / 2);
			if (shootTimer < 5)
			{
				shootTimer++;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 5) ////SHOOT
			{
				Projectile.setPosition(Playercenter);
				Projectiles.push_back(sf::Sprite(Projectile));
			
				shootTimer = 0;
			}

			for (size_t i = 0; i < Projectiles.size(); i++)
			{
				Projectiles[i].move(0, -10.f);

				if (Projectiles[i].getPosition().y <= 0)
				{
					Projectiles.erase(Projectiles.begin() + i);
				}
			}

			//Update Enemies
			if (PlayerHealth != -1)
			{
				if (EnemySpawnTimer < 8)
				{
					EnemySpawnTimer++;
				}
				if (EnemySpawnTimer >= 8)
				{
					Enemy.setPosition(rand() % int(window.getSize().x - Enemy.getGlobalBounds().width), 0);
					Enemies.push_back(sf::Sprite(Enemy));

					EnemySpawnTimer = 0;
				}
				for (size_t i = 0; i < Enemies.size(); i++)
				{
					Enemies[i].move(0, 6.f);
					if (PlayerScore >= 250)
					{
						Enemies[i].move(0, 1.f);
					}
					if (PlayerScore >= 500)
					{
						Enemies[i].move(0, 1.f);
					}
					if (PlayerScore >= 800)
					{
						Enemies[i].move(0, 1.f);
					}
					if (PlayerScore >= 1000)
					{
						Enemies[i].move(0, 1.f);
					}
					if (PlayerScore >= 1300)
					{
						Enemies[i].move(0, 1.f);
					}
					if (PlayerScore >= 1600)
					{
						Enemies[i].move(0, 1.f);
					}
					if (PlayerScore >= 2000)
					{
						Enemies[i].move(0, 2.f);
					}
					if (Enemies[i].getPosition().y + Enemies[i].getGlobalBounds().height >= window.getSize().y)
					{
						Enemies.erase(Enemies.begin() + i);
						PlayerHealth -= 1;
						std::cout << "Health: " << PlayerHealth << "\n";
					}
				}
			}
		

			//Projectile and Enemy Collision
			for (size_t i = 0; i < Projectiles.size(); i++)
			{
				for (size_t j = 0; j < Enemies.size(); j++)
				{
					if (Projectiles[i].getGlobalBounds().intersects(Enemies[j].getGlobalBounds()))
					{
						Projectiles.erase(Projectiles.begin() + i);
						Enemies.erase(Enemies.begin() + j);
						PlayerScore += 5;
						std::cout << "Score: " << PlayerScore << "\n";
						break;
					}
				}
			}

			//Player and Enemies Collission
			for (size_t i = 0; i < Enemies.size(); i++)
			{
				if (Enemies[i].getGlobalBounds().intersects(Player.getGlobalBounds()))
				{
					PlayerHealth -= 1;
					Enemies.erase(Enemies.begin() + i);
					std::cout << "Health: " << PlayerHealth << "\n";
				}
			}

			//GAME OVER LOOP
			for (size_t i = 0; i < Enemies.size(); i++)
			{
				if (PlayerHealth <= 0)
				{
					Enemies.clear();
					Projectiles.clear();
					gameOver = true;
				}
			}

			//UI Text for Score and Health
			scoreText.setString("Score: " + std::to_string(PlayerScore));
			healthText.setString("Health: " + std::to_string(PlayerHealth));

			//Clear
			window.clear();

			//Draw
			//window.draw(Background);
			window.draw(scoreText);										
			window.draw(healthText);

			if (gameOver == true)
			{
				window.draw(text);
			}

			for (size_t i = 0; i < Enemies.size(); i++)
			{
				window.draw(Enemies[i]);
			}

			for (size_t i = 0; i < Projectiles.size(); i++)
			{
				window.draw(Projectiles[i]);
			}
			if (!gameOver)
			{
				window.draw(Player);
			}
		

			//Display
			window.display();
		}

		// Replay Game Logic after Game over state
		while (gameOver && window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
				{
					gameOver = false;  // Reset the game
					Player.setPosition(sf::Vector2f(window.getSize().x / 2 - Player.getGlobalBounds().width / 2, window.getSize().y - Player.getGlobalBounds().height * 2));  // Reset player position
					PlayerHealth = 10;  // Reset player health
					PlayerScore = 0;	//Reset Player score
					Enemies.clear();  // Clear all enemies
				}
				else if (event.type == sf::Event::Resized)
				{
					// Update the view to the new window size
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));

					// Recalculate positions of UI elements
					//Background.setPosition(0, 0);
					text.setPosition(event.size.width / 2.0f, event.size.height / 2.0f - 50);
					finalScoreText.setPosition(event.size.width / 2.0f - finalScoreText.getLocalBounds().width / 2.0f, event.size.height / 2.0f -200.f);
					replayText.setPosition(event.size.width / 2.0f - replayText.getLocalBounds().width / 2.0f, event.size.height / 2.0f + 120);
					healthText.setPosition(10.0f, 10.0f);
					scoreText.setPosition(10.0f, 40.0f);
				}
			}

			// Update final score text
			finalScoreText.setString("Final Score: " + std::to_string(PlayerScore));
			finalScoreText.setPosition(window.getSize().x / 2.0f - finalScoreText.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f -200.f);

			// Replay text
			replayText.setString("Press ENTER To Replay. \n Press ESCAPE To Exit.");
			replayText.setPosition(window.getSize().x / 2.0f - replayText.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f + 120);

			window.clear();
			//window.draw(Background);
			window.draw(text);  // Draw the "GAME OVER" text
			window.draw(finalScoreText);
			window.draw(replayText);
			window.display();
		}
	}

	return 0;
}