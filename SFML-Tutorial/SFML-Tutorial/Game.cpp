#include "Game.h"

//Private function
void Game::initVariables()
{
	//Game logic
	this->startGame = false;
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("BR/background.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initWindow()
{
	this->videoMode.height = 900;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Click", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::Failed to load font!" << "\n";
	}
}

void Game::initText()
{
	// Point Text
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(30);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
	//Over Text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	//this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(130.f, 300.f);
	//Start text
	this->startGameText.setFont(this->font);
	this->startGameText.setCharacterSize(70);
	this->startGameText.setFillColor(sf::Color::Red);
	this->startGameText.setString("Press Space to start game !");
	this->startGameText.setPosition(50.f, 300.f);
	//Play Again Text
	this->playAgainText.setFont(this->font);
	this->playAgainText.setCharacterSize(60);
	this->playAgainText.setFillColor(sf::Color::Red);
	this->playAgainText.setString("Press Space to play again!!");
	this->playAgainText.setPosition(100.f, 400.f);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	//this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
}

//Constructors / Destructors
Game::Game()
{
	this->initWorld();

	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}
const bool Game::getStartGame() const
{
	return this->startGame;
}
//Function
void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getGlobalBounds().height)), 0.f);
	//Randomiz enemy type
	int type = rand() % (1+ 5);
	switch (type)
	{
	case 0:
		//this->enemy.setSize(sf::Vector2f(60.f, 60.f));
		this->enemy.setRadius(36.f);
		this->enemy.setPointCount(3);
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		//this->enemy.setSize(sf::Vector2f(65.f, 65.f));
		this->enemy.setRadius(40.f);
		this->enemy.setPointCount(4);
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		//this->enemy.setSize(sf::Vector2f(40.f, 40.f));
		this->enemy.setRadius(36.f);
		this->enemy.setPointCount(3);
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		//this->enemy.setSize(sf::Vector2f(45.f, 45.f));
		this->enemy.setRadius(43.f);
		this->enemy.setPointCount(6);
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case 4:
		//this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setRadius(38.f);
		this->enemy.setPointCount(10);
		this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		//this->enemy.setSize(sf::Vector2f(45.f, 45.f));
		this->enemy.setRadius(35.f);
		this->enemy.setPointCount(15);
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}
	//Spawm the enemy
	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	//Event poling
	/*while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyReleased:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}*/
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Space)
			this->startGame = true;
		if (getEndGame()) {
			if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Space)
			{
				this->replayGame();
			}
		}
	}
}
void Game::replayGame()
{
	this->initVariables();
	this->clearEnemies();
	this->initEnemies();
	this->startGame = true;
}
void Game::clearEnemies() {
	this->enemies.clear();
}
void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosWiew = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateWorld()
{

}

void Game::updateGameOver()
{

}

void Game::updateText()
{
	std::stringstream ss;
	std::stringstream point;
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n";
	point << "Game Over, Points: " << this->points;
	this->gameOverText.setString(point.str());
	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	//Updating the timer for enemy spawing
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 5.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
		}
	}

	//Check if clicked upon	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosWiew))
				{
					//Gain points
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 4;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 2;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 8;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 6;
					std::cout << "Points: " << this->points << "\n";

					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}

			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	if (this->endGame == false)
	{
		this->updateWorld();
		this->updateMousePositions();
		this->updateText();
		this->updateEnemies();
	}
	//EndGame condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderGameOver()
{
	this->window->draw(this->gameOverText);
	this->window->draw(this->playAgainText);
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{

	this->window->clear();
	this->renderWorld();
	//Draw game
	this->renderEnemies(*this->window);

	this->renderText(*this->window);
	if (!this->getStartGame()) {
		this->window->draw(this->startGameText);
	}
	//Game over screen
	if (this->health <= 0)
		this->renderGameOver();

	this->window->display();
}