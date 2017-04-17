#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <string>
#include <queue>
#include "player.h"
#include "constants.h"
#include "enemy.h"
#include "blue.h"
#include "purple.h"
#include "green.h"
#include "pink.h"
#include "smallpink.h"
#include "weapon.h"
#include "weapont1.h"
#include "weapont2.h"
#include "weapont3.h"
#include "expparticles.h"

using namespace std;

class game
{    
public:
    game();                          //Default Constructor
    void Draw();                     //Draws all sprites to window
    void run();                      //Contains loop for update, render, draw, process
    void processEvents();            //Interprets user input and updates relevant data
    void update();                   //Updates sprite positions and performs collision checks
    void render();                   //Calls window clear, Draw() function, then display

    void processMovement();          //Called by process events to interpret movement input
    void Fire(float x, float y);     //Called by process fire to spawn bullets with direction x,y
    void processFire();              //Called by process events to interpret fire input
    void RandomSpawn(int enemyType); //Called by enemyEvent() to spawn enemy at random position
    void updateOverlay();            //Overlay for score and life count
    void enemyEvent();               //Handles all enemy spawning events
    void PlayerCollision();          //Handles and resolves player collision, set gameOver if no lives
    void gameOverhandler();          //Called if gameOver == true, displays game over screen, waits for input
    void playerExplosion();          //Inserts explosion particles into explosions vector for player collision
    void weaponSwitch();             //Handles weapon switching at different intervals

private:
    vector<Enemy> livingEnemies;     //Contains all enemies to be displayed
    vector<Weapon> bullets;          //Contains all bullets to be displayed
    vector<ExpParticles> explosions; //Current explosion particles to draw
    std::queue<Enemy> eventEnemies;  //Enemies queued and waiting to be pushed
    std::queue<int> eventType;       //Type of event to know how to push eventEnemies to livingEnemies
    bool timedEvent;                 //Tells enemyEvent whether or not to eventType is timed
    int eventIterations;             //How many iterations of a timed event for enemy spawning
    sf::Clock timedSpawn;            //Spawns enemies of timed event at regular interval
    //All textures drawn to sprites in game
    sf::Texture bullet1, bullet2, bullet3, enemyBlue, enemyPurple, enemyGreen, enemyPink, enemysmallPink;
    //All sounds effects to play for certain actions
    sf::Sound weapon1, weapon2, weapon3, spawnEnemy, wallCollision, enemyHit, shipexplode, shipspawn;
    //Sound buffer to load in sounds from file
    sf::SoundBuffer weapon1b, weapon2b, weapon3b, spawnEnemyb, wallCollisionb, enemyHitb, shipexplodeb, shipspawnb;
    //Music to be played in background depending on game state
    sf::Music backgroundMusic, endgameMusic;
    sf::RenderWindow window;         //Window to draw game
    sf::View playerCenter;           //View port for camera to follow player
    sf::Clock spawnClock;            //Clock for spawning enemies at regular interval
    bool fireReady;                  //Resolves fire rate
    sf::Clock fireRate;              //Allows firing at regular interval
    sf::Clock frameClock;            //Updates game at 60Hz
    int weaponType;                  //Current weapon type of player
    player _player;                  //Player object, contains player sprite, velocity, etc
    sf::RectangleShape border;       //Game border
    sf::Texture backgroundImage;     //Background texture for background sprite
    sf::Sprite background;           //Background drawn first
    bool spawnReady;                 //Checks if enough time has elapsed to spawn enemy
    int spawnTime;                   //Changes spawn rate as game progresses
    int score;                       //Current score
    int multiplier;                  //Multiplier accrued over time, default = 1
    int nextMult;                    //Next multiplier threshold
    int tonextMult;                  //Points accrued toward nextMult threshold
    int tonextWeaponSwitch;          //Points accrued toward nextWeaponSwitch threshold
    int nextWeaponSwitch;            //Next weapon switch threshold
    sf::Text displayScore;           //Text to display score to screen
    sf::Text displayLives;           //Text to display lives to screen
    sf::Text gameOverText1;          //Game over text "Game Over"
    sf::Text gameOverText2;          //Game over text "Press [Space] to continue"
    bool showMultiplier;             //Set to true when multiplier incremented
    sf::Text multiplierMessage;      //Displays new multiplier value if showMultiplier = true
    sf::Clock multiplierClock;       //Shows multiplier message for set amount of time
    sf::Font font;                   //Unique font used by text
    int lives;                       //Number of lives player currently has, default = 3
    bool gameOver;                   //Set to true when player lives = 0
};

#endif // GAME_H
