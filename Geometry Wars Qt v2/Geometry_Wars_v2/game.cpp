#include "game.h"


//Default Constructor
game::game()
{
    //Creates window of screen width x screen height size and string printed
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Geometry Wars Clone by G. Taylor McClamroch");
    window.setFramerateLimit(FRAME_LIMIT);                                         //Sets frame limit for window
    border.setSize(sf::Vector2f(BORDER,BORDER));                                   //Creates a game border
    border.setFillColor(sf::Color::Transparent);                                   //Sets border with transparent background
    border.setOutlineThickness(10);                                                //Border outline thickness 10px
    border.setOutlineColor(sf::Color::White);                                      //Border outline color
    border.setPosition(Bx,By);                                                     //Set border position
    playerCenter.setSize(cameraWidth,cameraHeight);                                //Creates player view port
    playerCenter.setCenter(_player.getPos());                                      //Centers view port on player
    window.setView(playerCenter);                                                  //Sets window to this viewport
    backgroundImage.loadFromFile("../Geometry_Wars_v2/textures/background.jpg");   //Loads in background image from file
    background.setTexture(backgroundImage, true);                                  //Sets background to background image
    background.setPosition(sf::Vector2f(-BORDER/2,-BORDER/2));                     //Sets background to position
    weaponType = 1;                                                                //Initializes weapon type to weapon 1
    bullet1.loadFromFile("../Geometry_Wars_v2/textures/bullet1.png");              //Initializes bullet textures
    bullet2.loadFromFile("../Geometry_Wars_v2/textures/bullet2.png");
    bullet3.loadFromFile("../Geometry_Wars_v2/textures/bullet3.png");
    enemyBlue.loadFromFile("../Geometry_Wars_v2/textures/blue.png");               //Initializes enemy textures
    enemyPurple.loadFromFile("../Geometry_Wars_v2/textures/purple.png");
    enemyGreen.loadFromFile("../Geometry_Wars_v2/textures/green.png");
    enemyPink.loadFromFile("../Geometry_Wars_v2/textures/pink.png");
    enemysmallPink.loadFromFile("../Geometry_Wars_v2/textures/smallpink.png");
    weapon1b.loadFromFile("../Geometry_Wars_v2/sounds/weapon1.wav");              //Initializes sounds, music, and buffers
    weapon1.setBuffer(weapon1b);
    wallCollisionb.loadFromFile("../Geometry_Wars_v2/sounds/wallCollision.wav");
    wallCollision.setBuffer(wallCollisionb);
    spawnEnemyb.loadFromFile("../Geometry_Wars_v2/sounds/spawnEnemy.wav");
    spawnEnemy.setBuffer(spawnEnemyb);
    enemyHitb.loadFromFile("../Geometry_Wars_v2/sounds/enemyHit.wav");
    enemyHit.setBuffer(enemyHitb);
    shipexplodeb.loadFromFile("../Geometry_Wars_v2/sounds/shipexplode.wav");
    shipexplode.setBuffer(shipexplodeb);
    shipspawnb.loadFromFile("../Geometry_Wars_v2/sounds/shipspawn.wav");
    shipspawn.setBuffer(shipspawnb);
    backgroundMusic.openFromFile("../Geometry_Wars_v2/sounds/backgroundMusic.wav");
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50);
    endgameMusic.openFromFile("../Geometry_Wars_v2/sounds/endgamemusic.wav");
    endgameMusic.setLoop(true);
    fireRate.restart();                                                            //game clocks initialized
    spawnClock.restart();
    frameClock.restart();
    timedSpawn.restart();
    score = 0;                                                                     //Initializes all game state values
    multiplier = 1;
    nextMult = 3000;
    tonextMult = 0;
    nextWeaponSwitch = 2500;
    tonextWeaponSwitch = 0;
    eventIterations = 0;
    timedEvent = false;
    spawnTime = 2000;
    gameOver = false;
    lives = 3;
    fireReady = true;
    spawnReady = false;
    font.loadFromFile("../Geometry_Wars_v2/fonts/spacefr.ttf");                    //Initializes font and all texts
    displayScore.setFont(font);
    displayScore.setCharacterSize(25);
    displayScore.setColor(sf::Color::Green);
    displayLives.setFont(font);
    displayLives.setCharacterSize(25);
    displayLives.setColor(sf::Color::Green);
    gameOverText1.setFont(font);
    gameOverText1.setCharacterSize(50);
    gameOverText1.setColor(sf::Color::Green);
    gameOverText2.setFont(font);
    gameOverText2.setCharacterSize(25);
    gameOverText2.setColor(sf::Color::Green);
    gameOverText1.setString("GAME OVER");
    gameOverText2.setString("Press [Space] to play again");
    multiplierMessage.setFont(font);
    multiplierMessage.setCharacterSize(20);
    multiplierMessage.setColor(sf::Color::Red);    
    srand(time(0));                                                               //Seeds rand() function
}
//Draws everything to window
void game::Draw()
{    
    window.draw(background);                      //Draws background first
    window.draw(border);                          //Then the border
    for(int i = 0; i < bullets.size(); i++)       //Then bullets so they don't appear from top of ship
    {
        window.draw(bullets[i].Draw());
    }
    window.draw(_player.Draw());                  //Then player
    for(int i = 0; i < livingEnemies.size(); i++) //then enemies
    {        
        window.draw(livingEnemies[i].Draw());
    }
    for(int i = 0; i < explosions.size(); i++)    //then explosion particles
    {
        window.draw(explosions[i].particle);
        window.draw(explosions[i].pointValue);
    }
    if(showMultiplier == true)                    //Show multiplier message if needed
    {
        window.draw(multiplierMessage);
    }
    window.draw(displayScore);                    //Draw overlay elements
    window.draw(displayLives);
}

//Handles processing of user inputs
void game::processEvents()
{
    sf::Event event;
    window.pollEvent(event);                             //polls window for events
    if(event.type == sf::Event::Closed) window.close();  //if that event is the window closing, then close the window
    processMovement();                                   //Processes user input for movement
    processFire();                                       //Processes user input for firing
}
//Updates all positions, checks for collisions, and handles them
void game::update()
{
    _player.updatePos();                               //Updates player position
    sf::Vector2f playerPos = _player.getPos();         //gets player position to pass to enemy updates
    for(int i = 0; i < bullets.size(); i++)            //Updates all bullet positions
    {
        bullets[i].updatePos();
    }
    bool bulletinRadius;
    for(int i = 0; i < livingEnemies.size(); i++)      //Updates all enemies
    {
        if(livingEnemies[i].getType() == "Green")
        {
            if(bullets.size() == 0)
            {
                livingEnemies[i].updatePos(playerPos);
            }
            else
            {
                bulletinRadius = false;
                int j;
                for(j = 0; j < bullets.size() && bulletinRadius == false; j++)
                {
                    bulletinRadius = livingEnemies[i].bulletinRadius(bullets[j].getPosition());
                }
                if(bulletinRadius) livingEnemies[i].greenUpdate(bullets[j].getPosition());
                else livingEnemies[i].updatePos(playerPos);
            }
        }
        else livingEnemies[i].updatePos(playerPos);
    }
    playerCenter.setCenter(playerPos);                 //Updates camera
    window.setView(playerCenter);                      //Sets camera to window
    enemyEvent();                                      //Spawns enemies
    for(int i = 0; i < bullets.size(); i++)            //Checks for bullet collision first
    {
        if(bullets[i].borderCollision())
        {
            bullets.erase(bullets.begin()+i);
            i--;
            wallCollision.play();
        }
    }
    //Checks and handles bullet-enemy collisions
    bool exitJ = false, exitI = false;
    sf::Vector2f enemyPos;    
    for(int i = 0; i < bullets.size() && exitI == false; i++)
    {
        exitJ = false;
        for(int j = 0; j < livingEnemies.size() && exitJ == false; j++)
        {
            enemyPos = livingEnemies[j].getPos();
            if(bullets[i].enemyCollision(enemyPos))
            {                
                enemyHit.play();
                if(livingEnemies[j].getType() == "Pink")
                {
                    livingEnemies.push_back(smallPink(enemyPos, enemysmallPink));
                    livingEnemies.push_back(smallPink(enemyPos, enemysmallPink));
                }                
                float increase = (livingEnemies[j].getPoints() * multiplier);
                tonextMult += increase;
                score += increase;
                tonextWeaponSwitch += increase;
                for(int k = 0; k < 20; k++)
                {
                    explosions.push_back(ExpParticles(livingEnemies[j].getType(), livingEnemies[j].getPos(), (k*18.f), font, increase));
                }
                livingEnemies.erase(livingEnemies.begin()+j);
                if(i >= bullets.size()) exitI = true;
                exitJ = true;                
            }
        }
    }
    //Handles setting multiplier message, increasing multiplier
    if(tonextMult >= nextMult)
    {
        tonextMult -= nextMult;
        nextMult *= 2;
        multiplier++;
        showMultiplier = true;
        multiplierMessage.setString("Multiplier x" + to_string(multiplier));
        multiplierMessage.setPosition(sf::Vector2f((_player.getPos().x + 20.f), (_player.getPos().y + 20.f)));
        multiplierClock.restart();
    }
    //Fades out multiplier message after certain time interval
    if(showMultiplier == true)
    {
        int elapsedTime = multiplierClock.getElapsedTime().asMilliseconds();
        if(elapsedTime > 1000) showMultiplier = false;
        else
        {
            multiplierMessage.setColor(sf::Color(255,0,0,255));
            if(elapsedTime > 750) multiplierMessage.setColor(sf::Color(255,0,0,(1000-elapsedTime)));
        }
    }
    //Handles weapon switching at certain score interval
    weaponSwitch();
    //Check for enemies colliding with one another and resolve
    for(int i = 0; i < livingEnemies.size(); i++)
    {
        for(int j = i+1; j < livingEnemies.size(); j++)
        {
            livingEnemies[i].enemyCollision(livingEnemies[j].getPos());
        }
    }
    //Move explosion particles and fade out and delete after time interval
    for(int i = 0; i < explosions.size(); i++)
    {
        int elapsedTime = explosions[i].time.getElapsedTime().asMilliseconds();
        if(elapsedTime > 1000) explosions.erase(explosions.begin() + i);
        else
        {
            if(elapsedTime > 750)
            {
                if(explosions[i].a > 0) explosions[i].a -= 20;
                if(explosions[i].a < 0) explosions[i].a = 0;
                explosions[i].particle.setFillColor(sf::Color(explosions[i].r, explosions[i].g, explosions[i].b, explosions[i].a));
                explosions[i].pointValue.setColor(sf::Color(explosions[i].r, explosions[i].g, explosions[i].b, explosions[i].a));
            }
            explosions[i].particle.move(explosions[i].velocity);
        }
    }
    //Update text for overlay
    updateOverlay();
    //Handle player collision with enemies
    PlayerCollision();
}
//Handles window display of game elements
void game::render()
{
    window.clear();
    Draw();
    window.display();
}
//Run loop for update, render, processEvents
void game::run()
{
    backgroundMusic.play();
    //Runs while window is open
    while(window.isOpen())
    {
        //Locks updates to 60 Hz
        if(frameClock.getElapsedTime().asMilliseconds() > 16.667f)
        {
            update();
            render();
            processEvents();
            //Handle game over event
            if(gameOver)
            {
                gameOverhandler();
            }
            frameClock.restart();
        }
    }
}

//Handles all movement inputs from user
void game::processMovement()
{
    //All possible scenarios for WASD inputs
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _player.move(0,0);   //WASD -> movement = 0
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _player.move(1,0);  //WSD  -> movement = right
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _player.move(-1,0); //WSA  -> movement = left
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _player.move(0,0); //WS   -> movement = 0
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _player.move(0,1);  //WAD  -> movement = up
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _player.move(1,1); //WD   -> movement = up-right
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _player.move(-1,1);//WA   -> movement = up-left
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _player.move(0,1);//W    -> movement = up
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _player.move(0,-1);    //SAD -> movement = down
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _player.move(-1,-1);  //SA  -> movement = down-left
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _player.move(1,-1);   //SD  -> movement = down-right
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _player.move(0,-1);  //S   -> movement = down
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _player.move(0,0);   //AD -> movement = 0
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _player.move(-1,0); //A  -> movement = left
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _player.move(1,0);  //D  -> movement = right
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _player.move(0,0);
    }
    //If joystick is connected, start polling joystick
    if(sf::Joystick::isConnected(0))
    {
        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);    //get current x-axis position of joystick
        float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);    //get current y-axis position of joystick
        if(x < 20.f && x > -20.f) x = 0;                                //set tolerances of x-y axes to ignore
        if(y < 20.f && y > -20.f) y = 0;                                //input less than 20.f
        if(!(x == 0 && y == 0))                                         //This allows for stopping
        {
            _player.joystick_move(x,y);                                 //Passes in x,y values to player's move function
        }
    }
}
//Called by processFire function to create bullets
void game::Fire(float x, float y)
{
    sf::Vector2f bulletVector;                                                                    //Creates bullet vector from x and y values
    bulletVector.x = x;
    bulletVector.y = y;
    if(weaponType == 1 && fireRate.getElapsedTime().asMilliseconds() > WT1ROF) fireReady = true;  //Checks firerate and elapsed time to see if firing is ready
    if(weaponType == 2 && fireRate.getElapsedTime().asMilliseconds() > WT2ROF) fireReady = true;  //for the weapon type currently being used
    if(weaponType == 3 && fireRate.getElapsedTime().asMilliseconds() > WT3ROF) fireReady = true;
    if(fireReady == true)           //Firing ready
    {
        fireReady = false;          //set firing ready to false
        fireRate.restart();         //restart firing clock
        //Create bullet depending on weapon type
        if(weaponType == 1)
        {
            bullets.push_back(WeaponT1(1,_player.getPos(),bulletVector,bullet1));
            weapon1.play();
        }
        if(weaponType == 2)
        {
            bullets.push_back(WeaponT2(1,_player.getPos(),bulletVector,bullet2));
            bullets.push_back(WeaponT2(2,_player.getPos(),bulletVector,bullet2));
            bullets.push_back(WeaponT2(3,_player.getPos(),bulletVector,bullet2));
            weapon1.play();
        }
        if(weaponType == 3)
        {
            bullets.push_back(WeaponT3(1,_player.getPos(),bulletVector,bullet3));
            bullets.push_back(WeaponT3(2,_player.getPos(),bulletVector,bullet3));
            bullets.push_back(WeaponT3(3,_player.getPos(),bulletVector,bullet3));
            bullets.push_back(WeaponT3(4,_player.getPos(),bulletVector,bullet3));
            bullets.push_back(WeaponT3(5,_player.getPos(),bulletVector,bullet3));
            weapon1.play();
        }
    }
}
//Checks for user input to fire weapon
void game::processFire()
{
    //Checks for firing keys and all combinations of up, down, left, right
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire(-1.f, 0.f);
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire(-1.f, 1.f);
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire( 0.f, 1.f);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire(-1.f,-1.f);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire(-1.f, 0.f);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire( 0.f,-1.f);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire(1.f,  0.f);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire(1.f, -1.f);
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&  sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  Fire(0.f, -1.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Fire(1.f,1.f);
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Fire(1.f,0.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Fire(0.f,1.f);
    //If joystick is connected, start polling joystick
    if(sf::Joystick::isConnected(0))
    {
        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::U);     //get x-y values of joystick u-r plane
        float y = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
        if(x < 20.f && x > -20.f) x = 0;                                 //sets tolerance to ignore small inputs
        if(y < 20.f && y > -20.f) y = 0;
        if(!(x == 0 && y == 0))                                          //if some value in either x or y
        {                                                                //then fire in x-y direction
            Fire(x,y);
        }
    }
}
//Called by enemyEvent to spawn enemy at random position
//outside an acceptable radius of player
void game::RandomSpawn(int enemyType)
{
    spawnReady = false;
    spawnClock.restart();
    sf::Vector2f playerPos = _player.getPos();
    int numberSet = (BORDER-(2*enemyOffset));
    float x, y, deltaX, deltaY, distance;
    bool validSpawn = false;    
    while(!validSpawn)
    {
        x = rand()%numberSet + enemyOffset;
        y = rand()%numberSet + enemyOffset;
        deltaX = x-playerPos.x;
        deltaY = y-playerPos.y;
        distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
        if(distance >= spawnRadius) validSpawn = true;
    }
    if(enemyType == 0)
    {
        livingEnemies.push_back(Purple(sf::Vector2f(x,y), enemyPurple));
    }
    if(enemyType == 1)
    {
        livingEnemies.push_back(Blue(sf::Vector2f(x,y), enemyBlue));
    }
    if(enemyType == 2)
    {
        livingEnemies.push_back(Green(sf::Vector2f(x,y), enemyGreen));
    }
    if(enemyType == 3)
    {
        livingEnemies.push_back(Pink(sf::Vector2f(x,y), enemyPink));
    }
    spawnEnemy.play();
}
//Updates overlay with current score and life count
void game::updateOverlay()
{
    displayScore.setString("Score " + to_string(score));
    displayScore.setPosition(playerCenter.getCenter().x -395.f, playerCenter.getCenter().y -400.f);
    displayLives.setString("Lives " + to_string(lives));
    displayLives.setPosition(playerCenter.getCenter().x +250.f, playerCenter.getCenter().y -400.f);
}
//Handles enemyEvents, pushes enemies to queue and to vector
void game::enemyEvent()
{
    /* 0: Purple
     * 1: Blue
     * 2: Green
     * 3: Pink
     * 4: Blue Timed
     * 5: Green Timed
     * 6: Pink Timed     
    */
    //Handles timed events, to spawn enemies at each corner
    if(timedEvent)
    {
        if(timedSpawn.getElapsedTime().asMilliseconds() > 500)
        {
            livingEnemies.push_back(eventEnemies.front());
            eventEnemies.pop();
            livingEnemies.push_back(eventEnemies.front());
            eventEnemies.pop();
            livingEnemies.push_back(eventEnemies.front());
            eventEnemies.pop();
            livingEnemies.push_back(eventEnemies.front());
            eventEnemies.pop();
            timedSpawn.restart();
            eventIterations--;
            if(eventIterations == 0)
            {
                timedEvent = false;
                if(!eventType.empty()) eventType.pop();
            }
        }
    }
    if(spawnClock.getElapsedTime().asMilliseconds() >= spawnTime) spawnReady = true;
    //Spawn new enemy event at given time interval
    if(spawnReady)
    {
        int level;
        if(score < 1000) level = 2;
        if(score < 5000 && score >= 1000) level = 4;
        if(score < 10000 && score >= 5000) level = 5;
        if(score >= 10000) level = 7;
        if(level == 2) spawnTime = 2000;
        if(level == 4) spawnTime = 1300;
        if(level == 5) spawnTime = 1000;
        if(level == 7) spawnTime = 750;        
        int randomEvent = rand()%level;
        if(randomEvent < 4) RandomSpawn(randomEvent);
        if(randomEvent == 4)
        {
            if(timedEvent == false)
            {
                spawnReady = false;
                spawnClock.restart();
                timedEvent = true;
                eventIterations = 10;
                eventType.push(randomEvent);
                for(int i = 0; i < eventIterations; i++)
                {
                    eventEnemies.push(Blue(sf::Vector2f(enemyOffset,enemyOffset), enemyBlue));
                    eventEnemies.push(Blue(sf::Vector2f(enemyOffset,BORDER-enemyOffset), enemyBlue));
                    eventEnemies.push(Blue(sf::Vector2f(BORDER-enemyOffset,enemyOffset), enemyBlue));
                    eventEnemies.push(Blue(sf::Vector2f(BORDER-enemyOffset,BORDER-enemyOffset), enemyBlue));
                }
            }
        }
        if(randomEvent == 5)
        {
            if(timedEvent == false)
            {
                spawnReady = false;
                spawnClock.restart();
                timedEvent = true;
                eventIterations = 6;
                eventType.push(randomEvent);
                for(int i = 0; i < eventIterations; i++)
                {
                    eventEnemies.push(Green(sf::Vector2f(enemyOffset,enemyOffset), enemyGreen));
                    eventEnemies.push(Green(sf::Vector2f(enemyOffset,BORDER-enemyOffset), enemyGreen));
                    eventEnemies.push(Green(sf::Vector2f(BORDER-enemyOffset,enemyOffset), enemyGreen));
                    eventEnemies.push(Green(sf::Vector2f(BORDER-enemyOffset,BORDER-enemyOffset), enemyGreen));
                }
            }
        }
        if(randomEvent == 6)
        {
            if(timedEvent == false)
            {
                spawnReady = false;
                spawnClock.restart();
                timedEvent = true;
                eventIterations = 5;
                eventType.push(randomEvent);
                for(int i = 0; i < eventIterations; i++)
                {
                    eventEnemies.push(Pink(sf::Vector2f(enemyOffset,enemyOffset), enemyPink));
                    eventEnemies.push(Pink(sf::Vector2f(enemyOffset,BORDER-enemyOffset), enemyPink));
                    eventEnemies.push(Pink(sf::Vector2f(BORDER-enemyOffset,enemyOffset), enemyPink));
                    eventEnemies.push(Pink(sf::Vector2f(BORDER-enemyOffset,BORDER-enemyOffset), enemyPink));
                }
            }
        }
    }
}
//Checks for and handles player collision with enemies
//Sets gameOver to true if no lives left
void game::PlayerCollision()
{
    bool collision = false;
    sf::Vector2f playerPos = _player.getPos();
    for(int i = 0; i < livingEnemies.size() && collision == false; i++)
    {
        sf::Vector2f enemyPos = livingEnemies[i].getPos();
        float deltaX = playerPos.x - enemyPos.x;
        float deltaY = playerPos.y - enemyPos.y;
        float distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
        if(livingEnemies[i].getType() == "smallPink")
        {
            if(distance < (smallPinkOffset + playerOffset)) collision = true;
        }
        else if(distance < (enemyOffset + playerOffset)) collision = true;
    }
    if(collision == true)
    {
        if(lives == 1)
        {
            lives--;
            gameOver = true;
        }
        else
        {
            livingEnemies.clear();
            bullets.clear();
            spawnReady = false;
            spawnClock.restart();
            playerExplosion();
            _player.reset();
            lives--;
            multiplier = 1;
            nextMult = 1000;
            tonextMult = 0;
            shipspawn.play();
        }
    }
}
//Handles game over event, plays player explosion
//displays game over message and waits for user
//input to continue, then resets all game state
//values to initial state
void game::gameOverhandler()
{
    sf::Event event;
    backgroundMusic.stop();
    endgameMusic.play();
    playerExplosion();
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        window.pollEvent(event);                             //polls window for events
        if(event.type == sf::Event::Closed) window.close();
        gameOverText1.setPosition(sf::Vector2f((playerCenter.getCenter().x - 175.f), playerCenter.getCenter().y - 225.f));
        gameOverText2.setPosition(sf::Vector2f((playerCenter.getCenter().x - 225.f), (playerCenter.getCenter().y - 150.f)));
        window.clear();
        window.draw(background);                      //Draws background first
        window.draw(border);                          //Then the border
        for(int i = 0; i < bullets.size(); i++)       //Then bullets so they don't appear from top of ship
        {
            window.draw(bullets[i].Draw());
        }
        window.draw(_player.Draw());                  //Then player
        for(int i = 0; i < livingEnemies.size(); i++) //then enemies
        {
            window.draw(livingEnemies[i].Draw());
        }
        for(int i = 0; i < explosions.size(); i++)
        {
            window.draw(explosions[i].particle);
        }
        window.draw(displayScore);
        window.draw(displayLives);
        window.draw(gameOverText1);
        window.draw(gameOverText2);
        window.display();
    }
    //Reset all game state values to initial values
    livingEnemies.clear();
    bullets.clear();
    explosions.clear();
    while(!eventEnemies.empty()) eventEnemies.pop();
    while(!eventType.empty()) eventType.pop();
    _player.reset();
    weaponType = 1;
    fireReady = true;
    spawnReady = false;
    fireRate.restart();
    spawnClock.restart();
    frameClock.restart();
    score = 0;
    multiplier = 1;
    nextMult = 1000;
    tonextMult = 0;
    timedEvent = false;
    eventIterations = 0;
    timedSpawn.restart();
    spawnTime = 2000;
    gameOver = false;
    lives = 3;
    endgameMusic.stop();
    backgroundMusic.play();
}
//Pushes explosion particles to explosion vector
//Draws player explosion for time period
//then continues with game
 void game::playerExplosion()
 {
     shipexplode.play();
     explosions.clear();
     float angle;
     for(int i = 0; i < 1000; i++)
     {
         angle = 0.f + rand()%360;
         explosions.push_back(ExpParticles(_player.getPos(), angle));
     }
     sf::Clock explosionClock;
     explosionClock.restart();
     while(explosionClock.getElapsedTime().asSeconds() < 3)
     {
         int elapsedTime = explosionClock.getElapsedTime().asMilliseconds();
         for(int i = 0; i < explosions.size(); i++)
         {
             if(elapsedTime > 2750)
             {
                 if(explosions[i].a > 0) explosions[i].a -= 20;
                 if(explosions[i].a < 0) explosions[i].a = 0;
                 explosions[i].particle.setFillColor(sf::Color(explosions[i].r, explosions[i].g, explosions[i].b, explosions[i].a));
             }
             explosions[i].particle.move(explosions[i].velocity);
         }
        window.clear();
        window.draw(background);                      //Draws background first
        window.draw(border);                          //Then the border
        for(int i = 0; i < explosions.size(); i++)
        {
            window.draw(explosions[i].particle);
        }
        window.draw(displayScore);
        window.draw(displayLives);
        window.display();
     }
     explosions.clear();
 }
//Checks if ready for weapon switch and handles changing weapons
 void game::weaponSwitch()
 {
     if(score < 2500)
     {
         weaponType = 1;
     }
     else
     {
         if(tonextWeaponSwitch > nextWeaponSwitch)
         {
             tonextWeaponSwitch -= nextWeaponSwitch;
             nextWeaponSwitch *= 2;
             if(weaponType == 1)
             {
                 weaponType = rand()%2 + 2;
             }
             else
             {
                 if(weaponType == 2) weaponType = 3;
                 if(weaponType == 3) weaponType = 2;
             }
         }
     }
 }
