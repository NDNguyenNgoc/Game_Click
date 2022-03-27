#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
	//Variables

	//Window
	sf::RenderWindow * window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosWiew;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	sf::Text gameOverText;
	sf::Text startGameText;
	sf::Text playAgainText;
	//Game logic

	bool startGame;
	bool endGame;

	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	
	//Game objects
	std::vector<sf::CircleShape> enemies;
	sf::CircleShape enemy;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Private function
	void initWorld();


	void initText();

	void initVariables();
	void initWindow();
	void initFonts();
	void initEnemies();
	void replayGame();
	void clearEnemies();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;
	const bool getStartGame() const;
	//Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	
	void updateWorld();
	void updateGameOver();

	void updateText();
	void updateEnemies();
	void update();

	void renderWorld();
	void renderGameOver();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

