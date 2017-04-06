#include "graph.h"

//Default Constructor for Graph
Graph::Graph(Calculator *thisCalc)
{    
    defaultX = 10;
    defaultY = 10;
    window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Graph");
    window.setFramerateLimit(60);
    view.setSize(sf::Vector2f(defaultY, defaultX));
    view.setCenter(sf::Vector2f(0, 0));
    window.setView(view);
    calc = thisCalc;
}
//Draws all objects on screen
void Graph::Draw()
{    
    //Draw X and Y axis
    sf::Vector2f ViewSize = view.getSize();
    float sizeDomain = ViewSize.x;
    float sizeRange = ViewSize.y;
    sf::RectangleShape X_AXIS, Y_AXIS;
    X_AXIS.setSize(sf::Vector2f(200000, (sizeDomain/200)));
    Y_AXIS.setSize(sf::Vector2f((sizeRange/200), 200000));
    X_AXIS.setOrigin(sf::Vector2f(100000, (sizeDomain/400)));
    Y_AXIS.setOrigin(sf::Vector2f((sizeRange/400), 100000));
    X_AXIS.setPosition(sf::Vector2f(0, 0));
    Y_AXIS.setPosition(sf::Vector2f(0, 0));
    window.draw(X_AXIS);
    window.draw(Y_AXIS);
    int i;
    //Draw Grid marks for x-axis
    for(i = ((sizeDomain/2)*-1); i <= (sizeDomain/2); i++)
    {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f((sizeDomain/600), (sizeDomain/40)));
        line.setOrigin(sf::Vector2f((sizeDomain/1200), (sizeDomain/80)));
        line.setPosition(sf::Vector2f(i, 0));
        line.setFillColor(sf::Color::Red);
        window.draw(line);
    }
    //Draw Grid marks for y-axis
    for(i = ((sizeRange/2)*-1); i <= (sizeRange/2); i++)
    {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f((sizeRange/600), (sizeRange/40)));
        line.setOrigin(sf::Vector2f((sizeRange/1200), (sizeRange/80)));
        line.setPosition(sf::Vector2f(0,i));
        line.rotate(90);
        line.setFillColor(sf::Color::Red);
        window.draw(line);
    }
    //Draw in points evaluated from the calculator
    int size = points.size();
    for(i = 0; i < size; i++)
    {
        sf::CircleShape point;
        point.setRadius(sizeDomain/200);
        point.setOrigin(sf::Vector2f((sizeDomain/200),(sizeRange/200)));
        point.setPosition(points.at(i));
        point.setFillColor(sf::Color::Green);
        window.draw(point);
    }
//    sf::Text equation;
//    sf::Font myFont;
//    myFont.loadFromFile("arial.tff");
//    equation.setString(infix);
//    equation.setFont(myFont);
//    equation.setColor(sf::Color::Red);
//    equation.setCharacterSize(sizeDomain);
//    equation.setPosition(sf::Vector2f(0,0));
//    window.draw(equation);
}
//Run function incorporates all other functions to run continuously until window is closed
void Graph::run()
{
    while(window.isOpen())
    {
        update();
        render();
        processEvents();
    }
}
//Checks for user input (Close Window, Zoom In, Zoom Out, Default View)
void Graph::processEvents()
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
            case sf::Event::KeyPressed:
            {
                if(event.key.code == sf::Keyboard::I)
                {
                    sf::Vector2f ViewSize = view.getSize();
                    float sizeDomain = ViewSize.x;
                    float sizeRange = ViewSize.y;
                    view.setSize(sf::Vector2f((sizeDomain*.75),(sizeRange*.75)));
                    window.setView(view);
                }
                else if(event.key.code == sf::Keyboard::O)
                {
                    sf::Vector2f ViewSize = view.getSize();
                    float sizeDomain = ViewSize.x;
                    float sizeRange = ViewSize.y;
                    view.setSize(sf::Vector2f((sizeDomain*(4.0/3.0)),(sizeRange*(4.0/3.0))));
                    window.setView(view);
                }
                else if(event.key.code == sf::Keyboard::D)
                {
                    view.setSize(sf::Vector2f(defaultY,defaultX));
                    window.setView(view);
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
}
void Graph::update()
{
    createGraph();
}
void Graph::render()
{    
    window.clear();
    Draw();
    window.display();
}
//Creates a vector of sf::Vector2f that contains the point for the graph
void Graph::createGraph()
{
    sf::Vector2f ViewSize = view.getSize();
    float sizeDomain = ViewSize.x;
    float sizeRange = ViewSize.y;
    sizeDomain = sizeDomain/2;
    sizeRange = sizeRange/2;
    float x;
    float y;
    //The number divided into the domain determines number of points to be drawn
    for(x = (sizeDomain*-1); x < sizeDomain; x+=(sizeDomain/500))
    {        
        y = calc->EvaluateGraph(x);
        if(!calc->Error())
        {            
            points.push_back(sf::Vector2f(x,y*-1));
        }
    }
    infix = calc->getInfix();
}

