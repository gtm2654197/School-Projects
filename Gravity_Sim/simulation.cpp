#include "simulation.h"
#include "constants.h"
#include <cstdlib>
#include "math.h"
#include <iostream>
#include <SFML/Window/Mouse.hpp>

using namespace std;


Simulation::Simulation()
{
    window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Gravity Simulator");
    window.setFramerateLimit(60);    
//    zoomX = SCREEN_WIDTH;
//    zoomY = SCREEN_HEIGHT;
//    view.setSize(sf::Vector2f(zoomX, zoomY));
//    view.setCenter((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2));
}

void Simulation::Draw()
{
    //cycles through each particle and draws them
    int i;
    for(i = 0; i < particles.size(); i++)
    {
        window.draw(particles[i].circle);
    }
}

void Simulation::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                //Right mouse button pressed
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    int collision = mouseCollision(event.mouseButton.x, event.mouseButton.y);
                    //if the mouse is not over an existing particle
                    if(collision == -1)
                    {
                        //save initial mouse position
                        double initialX, initialY, finalX, finalY;
                        initialX = sf::Mouse::getPosition(window).x;
                        initialY = sf::Mouse::getPosition(window).y;

                        //draw line while choosing direction of new particle and save final mouse position
                        while(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            cout << "Start while loop" << endl;
                            sf::RectangleShape line;
                            line.setPosition(initialX, initialY);
                            finalX = sf::Mouse::getPosition(window).x;
                            finalY = sf::Mouse::getPosition(window).y;
                            double distance = sqrt((pow(finalX-initialX,2)) + (pow(finalY-initialY,2)));
                            line.setSize(sf::Vector2f(distance,2));
                            line.setFillColor(sf::Color::Cyan);
                            double angle = atan((finalY-initialY)/(finalX-initialX));
                            double pi = 4 * atan(1);
                            angle = angle*(180/pi);
                            if(finalX < initialX)
                            {
                                angle += 180;
                            }
                            line.setRotation(angle);
                            window.clear();
                            update();
                            Draw();
                            window.draw(line);
                            window.display();
                        }
                        cout << "End while loop" << endl;
                        //Calculate velocity of new particle
                        double deltaX, deltaY;
                        deltaX = (finalX-initialX)/50;
                        deltaY = (finalY-initialY)/50;

                        int random = rand() % 6;
                        //create new particle with above parameters
                        Particle newParticle;
                        newParticle.setSize(5);
                        newParticle.setColor(random);
                        newParticle.setPosition(initialX,initialY);
                        newParticle.setVelocity(deltaX,deltaY);
                        particles.push_back(newParticle);
                    }
                }
                break;
            }
        \
            case sf::Event::MouseButtonReleased:
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    int collision = mouseCollision(event.mouseButton.x, event.mouseButton.y);
                    //Mouse over existing particle
                    if(collision > -1)
                    {
                        //get x and y locations, and radius of particle and mouse
                        double particleX, particleY, radius;
                        particleX = particles[collision].circle.getPosition().x;
                        particleY = particles[collision].circle.getPosition().y;
                        radius = particles[collision].circle.getRadius();

                        //get mouse position
                        int mouseX = sf::Mouse::getPosition(window).x;
                        int mouseY = sf::Mouse::getPosition(window).y;

                        //calculate new velocity based on where the particle is clicked
                        double deltaX, deltaY;
                        deltaX = (mouseX - particleX)/radius;
                        deltaY = (mouseY - particleY)/radius;

                        //set new velocity
                        particles[collision].velocityX = deltaX;
                        particles[collision].velocityY = deltaY;
                    }
                    //Mouse over empty space;
                    else
                    {
                        //create new particle at mouse position
                        Particle newParticle;
                        newParticle.setSize(5);
                        int random = rand() % 6;
                        newParticle.setColor(random);
                        int mouseX = sf::Mouse::getPosition(window).x;
                        int mouseY = sf::Mouse::getPosition(window).y;
                        newParticle.setPosition(mouseX, mouseY);
                        particles.push_back(newParticle);
                    }
                }
                break;
            }
            case sf::Event::MouseWheelScrolled:
            {
                //save mouse position
                int mouseX = sf::Mouse::getPosition(window).x;
                int mouseY = sf::Mouse::getPosition(window).y;
                int collision = mouseCollision(mouseX, mouseY);
                //if mouse is over existing particle
                if(collision > -1)
                {
                    cout << "Collision detected" << endl;
                    //if scroll wheel up, increase size
                    if(event.mouseWheelScroll.delta > 0)
                    {
                        cout << "Mousewheel up" << endl;
                        int radius = particles[collision].circle.getRadius();
                        particles[collision].setSize(radius + 1);
                    }
                    //if scroll wheel down, decrease size
                    else
                    {
                        cout << "Mousewheel down" << endl;
                        int radius = particles[collision].circle.getRadius();
                        if(radius > 0)
                        {
                            particles[collision].setSize(radius - 1);
                        }
                    }
                }
                break;
            }
        case sf::Event::KeyPressed:
        {
            cout << "Key Pressed" << endl;
            //if key R is pressed
            if(event.key.code == sf::Keyboard::R)
            {
                cout << "R Pressed" << endl;
                //create 10 randomly positioned particles within window space
                for(int i = 0; i < 10; i++)
                {
                    int posX, posY, color, sign;
                    posX = rand() % SCREEN_WIDTH;
                    posY = rand() % SCREEN_WIDTH;
                    color = rand() % 7;
                    Particle temp;
                    temp.setPosition(posX,posY);
                    temp.setColor(color);
                    temp.setSize(5);
                    particles.push_back(temp);
                }
            }
//            if(event.key.code == sf::Keyboard::Dash)
//            {
//                zoomX += 100;
//                zoomY += 100;
//                view.setSize(sf::Vector2f(zoomX, zoomY));
//            }
//            if(event.key.code == sf::Keyboard::Equal)
//            {
//                zoomX -= 100;
//                zoomY -= 100;
//                view.setSize(sf::Vector2f(zoomX, zoomY));
//            }
            break;
        }
            default:
            {
                break;
            }
        }
    }
}

void Simulation::update()
{
    int i,j;
    for(i = 0; i < particles.size(); i++)
    {
        //get i particle position here so it doesn't loop through in next for loop, just does it once for each particle
        double positionXi, positionYi;
        positionXi = particles[i].circle.getPosition().x;
        positionYi = particles[i].circle.getPosition().y;

        //get mass for i particle
        double massi = particles[i].getMass();

        //initialize change in velocity variables, so we can pass it once after all changes are made
        double deltaVx = 0; double deltaVy = 0;
        for(j = 0; j < particles.size(); j++)
        {
            //skip instances when i == j
            if(i != j)
            {
                int collision = particleCollision(i,j);
                //if particle i does not collide with particle j
                if(collision == -1)
                {
                    //get j particle position and mass
                    double positionXj, positionYj, massj;
                    massj = particles[j].getMass();
                    positionXj = particles[j].circle.getPosition().x;
                    positionYj = particles[j].circle.getPosition().y;
                    //calculate distance between particle i and particle j
                    double distance = sqrt((pow(positionXi - positionXj, 2)) + (pow(positionYi - positionYj, 2)));

                    //calculate change in velocity and add to deltaVx and deltaVy for each particle j
                    deltaVx += ((massj/massi)/pow(distance,2)) * ((positionXj - positionXi)/distance);
                    deltaVy += ((massj/massi)/pow(distance,2)) * ((positionYj - positionYi)/distance);
                }
                //collision occurs between particles i and j
                else
                {
                    double radiusI, radiusJ;
                    //get radius of each particle
                    radiusI = particles[i].circle.getRadius();
                    radiusJ = particles[j].circle.getRadius();

                    //determine which particle is bigger and absorb the small into the big
                    if(radiusI >= radiusJ)
                    {
                        particleAbsorb(i,j);
                        if(j<i)
                        {
                            i--;
                        }
                    }
                    else
                    {
                        particleAbsorb(j,i);
                        i--;
                    }

                }
            }
        }
        //Change i particle value with deltaVx and deltaVy, calculated above
        particles[i].changeVelocity(deltaVx, deltaVy);
        double newVx, newVy;
        newVx = particles[i].velocityX;
        newVy = particles[i].velocityY;
        particles[i].circle.move(newVx, newVy);
    }

}

void Simulation::render()
{
    window.clear();
//    window.setView(view);
    Draw();
    window.display();
}

void Simulation::run()
{
    while(window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

//Checks if mouse is hovering over existing particle,
//returns -1 if over empty space
//returns index of particle in particle vector, otherwise
int Simulation::mouseCollision(float mouseX, float mouseY)
{
    int collision = -1;
    int i;
    for(i = 0; i < particles.size() && collision == -1; i++)
    {
        double distance;
        double deltaX, deltaY;
        deltaX = mouseX - particles[i].circle.getPosition().x;
        cout << "MouseX: " << mouseX << endl;
        deltaY = mouseY - particles[i].circle.getPosition().y;
        cout << "DeltaX: " << deltaX << ", Delta Y: " << deltaY << endl;
        distance = sqrt((pow(deltaX, 2)) + (pow(deltaY, 2)));
        cout << "Distance: " << distance;
        double radius = particles[i].circle.getRadius();
        cout << "Radius: " << radius;
        if(distance <= radius)
        {
            collision = i;
        }
    }
    cout << collision << endl;
    return collision;
}

//Checks for particle collision between two particles
//returns -1 if no collision
//returns 1 if collision
int Simulation::particleCollision(int particle1, int particle2)
{
    int collision = -1;
    double distance, particle1X, particle1Y, particle2X, particle2Y, deltaX, deltaY;
    //get x and y positions of each particle and calcultate difference
    particle1X = particles[particle1].circle.getPosition().x;
    particle1Y = particles[particle1].circle.getPosition().y;
    particle2X = particles[particle2].circle.getPosition().x;
    particle2Y = particles[particle2].circle.getPosition().y;

    deltaX = particle2X - particle1X;
    deltaY = particle2Y - particle1Y;

    //calculate distance between two particles
    distance = sqrt((pow(deltaX,2)) + (pow(deltaY,2)));

    //get sum of the radii of both particles
    double radius1, radius2, sumRadii;
    radius1 = particles[particle1].circle.getRadius();
    radius2 = particles[particle2].circle.getRadius();

    sumRadii = radius1 + radius2;

    //compare the sum with the distance do see if collision occurs
    if(distance <= sumRadii)
    {
        collision = 1;
    }
    return collision;
}

//When particle collision occurs, particle absorb is called to
//absorb the smaller particles size into the bigger particle
//and then deletes smaller particle
void Simulation::particleAbsorb(int bigParticle, int smallParticle)
{
    //Calculate the resulting radius of the absorbtion
    double radiusBig, radiusSmall, radiusNew, areaBig, areaSmall, areaNew;
    radiusBig = particles[bigParticle].circle.getRadius();
    radiusSmall = particles[smallParticle].circle.getRadius();
    areaBig = pow(radiusBig,2) * (4*atan(1));
    areaSmall = pow(radiusSmall,2) * (4*atan(1));
    areaNew = areaBig + areaSmall;
    radiusNew = sqrt(areaNew/(4*atan(1)));

    //If not first particle in index
    if(smallParticle > 0)
    {
        //Delete the small particle        
        particles.erase(particles.begin()+smallParticle);

        //give Big particle new radius
        if(smallParticle<bigParticle)
        {
            particles[bigParticle-1].setSize(radiusNew);
        }
        else
        {
            particles[bigParticle].setSize(radiusNew);
        }
    }
    //small particle is at position 0 in index
    else
    {
        sf::Color bigColor;
        double vxBig, vyBig, posxBig, posyBig;
        vxBig = particles[bigParticle].getVelocityX();
        vyBig = particles[bigParticle].getVelocityY();
        posxBig = particles[bigParticle].circle.getPosition().x;
        posyBig = particles[bigParticle].circle.getPosition().y;
        particles[smallParticle].circle.setFillColor(particles[bigParticle].circle.getFillColor());
        particles.erase(particles.begin() +bigParticle);
        if(smallParticle > bigParticle)
        {
            particles[smallParticle-1].setSize(radiusNew);
            particles[smallParticle-1].setPosition(posxBig, posyBig);
            particles[smallParticle-1].setVelocity(vxBig, vyBig);
        }
        else
        {
            particles[smallParticle].setSize(radiusNew);
            particles[smallParticle].setPosition(posxBig, posyBig);
            particles[smallParticle].setVelocity(vxBig, vyBig);
        }
    }
}
