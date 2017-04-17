#ifndef CONSTANTS
#define CONSTANTS

const int SCREEN_WIDTH = 1200;          //Window Width
const int SCREEN_HEIGHT = 900;          //Window Height
const int FRAME_LIMIT = 60;             //Framerate limit for window
const float BORDER = 1000;              //Game border size
const float Bx = 0;                     //Game border x-pos
const float By = 0;                     //Game border y-pos
const float cameraWidth = 800.f;        //Width of view port
const float cameraHeight = 800.f;       //Height of view port
const float playerOffset = 25.f;        //Radius of player for collision checking
const float bulletOffset = 5.f;         //Radius of bullet for collision checking
const float enemyOffset = 14.f;         //Radius of enemy for collision checking
const float smallPinkOffset = 8.f;      //Radius of small pink enemy
const float maxVelocity = 5.f;          //Maximum player velocity          
const float maxPurpleVel = 2.f;         //Maximum enemy velocities
const float maxBlueVel = 3.f;
const float maxGreenVel = 4.0f;
const float maxPinkVel = 4.5f;
const float maxsmallPinkVel = 4.0f;
const float bulletVelocity = 15.f;      //Velocity of bullets
const float blueAccel = .1f;            //Acceleration of enemy units
const float greenAccel = .2f;
const float pinkAccel = .3f;
const float smallpinkAccel = .15f;
const float dodgeAccel = 8.f;           //Green acceleration away from bullet
const float greenBulletRadius = 100.f;  //Distance from bullet green enemy will start dodging
const float spawnRadius = 300.f;        //Acceptable spawn radius of enemy units to player
const int WT1ROF = 125;                 //Weapon type 1 rate of fire (allow fire in ms, so higher value is slower rate of fire)
const int WT2ROF = 75;                  //Weapon type 2 rate of fire (allow fire in ms, so higher value is slower rate of fire)
const int WT3ROF = 150;                 //Weapon type 3 rate of fire (allow fire in ms, so higher value is slower rate of fire)
const float RadtoDeg = 57.29578;        //Radian to degree, calculated here once to save performance (45/atan(1) or 180/pi);
const float pi = 3.141593f;             //Pi to prevent unneeded calculations

#endif // CONSTANTS

