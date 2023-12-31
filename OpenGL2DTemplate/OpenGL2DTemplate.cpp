#define SDL_MAIN_HANDLED

//  Includes
#include <stdio.h>
#include <math.h>
#include <random>
#include <glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip>

#include <SDL.h>
#include <SDL_mixer.h>
//-----------------

//  Methods Signatures
void drawCircle(float centerX, float centerY, float radius, int numSegments);
void drawHexagon(float centerX, float centerY, float size);
void spe(int k, int x, int y);
void healthBar();
void collectibleCollisions();
void obstCollisions(int k);
void ufoColl();
void blackHoleColl();
void planetColl();
void drawSupernova(int x, int y);
void drawPlanet(float centerX, float centerY, float radius, int numSlices);
void drawUFO(int x, int y);
void drawEllipse(float centerX, float centerY, float radiusX, float radiusY, int numSegments);
void drawJerryCan(int centerx, int centery);
void drawAsteroid(float x, float y, float radius, int numPoints);
void Timer(int value);
void drawJet1();
int isTaken(int x, int y);
void Anim();
void Display();
//-----------------

//  Global Variables
int first = 0;
int score = 0;
int posX = 0;
int posY = 0;
float health = 100.0;
int rot = 0;
int collectibleCount = 0;
int obstCount = 0;
std::vector<int> collectibleXs;
std::vector<int> collectibleYs;
std::vector<int> obstXs;
std::vector<int> obstYs;
std::vector<int> asteroidRandoms;
std::vector<int> asteroidRandoms2x;
std::vector<int> asteroidRandoms2y;
time_t start_time;
double elapsed_time;
int lftBndMove = 0;
int rgtBndMove = 0;
int upBndMove = 0;
int dwnBndMove = 0;
int lftBndColl = 0;
int rgtBndColl = 0;
int upBndColl = 0;
int dwnBndColl = 0;
int UFOx = 0;
int UFOy = 0;
int bhx = 0;
int bhy = 0;
int planetX = 0;
int planetY = 0;
float obsGoalAnime = 0;
float ufoCanAnime = 0;
int change = 0;
std::vector<std::vector<int>> allCoords;
int timeInSeconds = 120;
int currentTimeUFO = 0;
int displayedUfoTimer = 0;
int ufoPower = 0;
int immunityPower = 0;
int disable = 0;
int currentTimeBh = 0;
int displayedBhTimer = 0;
int bhPower = 0;
int speedupPower = 0;
int win = 0;
float backAnime = 0;
int collected = 0;

Mix_Music* backgroundMusic;
Mix_Music* winMusic;
Mix_Music* lossMusic;
Mix_Chunk* obstSoundEffect;
Mix_Chunk* collectibleSoundEffect;
Mix_Chunk* ufoSoundEffect;
Mix_Chunk* bhSoundEffect;
Mix_Chunk* goalSoundEffect;

char* backgroundMusicPath = "./sounds/background.mp3";
char* obstMusicPath = "./sounds/obst.mp3";
char* winMusicPath = "./sounds/win.mp3";
char* lossMusicPath = "./sounds/loss.mp3";
char* collectibleMusicPath = "./sounds/collect.mp3";
char* ufoMusicPath = "./sounds/ufo.mp3";
char* bhMusicPath = "./sounds/bh.mp3";
char* goalMusicPath = "./sounds/goal.mp3";
//-----------------

Mix_Music* loadMusic(const char* filePath)
{
    return Mix_LoadMUS(filePath);
}

Mix_Chunk* loadSoundEffect(const char* filePath)
{
    return Mix_LoadWAV(filePath);
}

void playMusic(Mix_Music* music, int loop)
{
    Mix_PlayMusic(music, loop);
}

void playSoundEffect(Mix_Chunk* soundEffect)
{
    Mix_PlayChannel(-1, soundEffect, 0);
}

void cleanup(Mix_Music* music, Mix_Chunk* soundEffect)
{
    Mix_FreeMusic(music);
    Mix_FreeChunk(soundEffect);
    Mix_CloseAudio();
    SDL_Quit();
}


int SDL_main(int argc, char** argr) {

    glutInit(&argc, argr);

    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(150, 150);

    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    backgroundMusic = loadMusic(backgroundMusicPath);
    obstSoundEffect = loadSoundEffect(obstMusicPath);
    winMusic = loadMusic(winMusicPath);
    lossMusic = loadMusic(lossMusicPath);
    collectibleSoundEffect = loadSoundEffect(collectibleMusicPath);
    ufoSoundEffect = loadSoundEffect(ufoMusicPath);
    bhSoundEffect = loadSoundEffect(bhMusicPath);
    goalSoundEffect = loadSoundEffect(goalMusicPath);

    playMusic(backgroundMusic, -1);
    

    std::vector<int> arrPlayer = { 500, 300 };
    allCoords.push_back(arrPlayer);

    
    planetX = 65;
    planetY = 65;
    std::vector<int> arrp = { planetX, planetY };
    allCoords.push_back(arrp);

    srand(time(0));
    int temp1u = 50 + rand() % 900;
    int temp2u = 50 + rand() % 400;
    while (isTaken(temp1u, temp2u) == 1) {
        temp1u = 50 + rand() % 900;
		temp2u = 50 + rand() % 400;
    }
    UFOx = temp1u;
    UFOy = temp2u;
    std::vector<int> arru = { temp1u, temp2u };
    allCoords.push_back(arru);

    int temp1b = 50 + rand() % 900;
    int temp2b = 50 + rand() % 400;
    while (isTaken(temp1b, temp2b) == 1) {
        temp1b = 50 + rand() % 900;
        temp2b = 50 + rand() % 400;
    }
    bhx = temp1b;
    bhy = temp2b;
    std::vector<int> arrb = { temp1b, temp2b };
    allCoords.push_back(arrb);

    obstCount = 5 + rand() % 2;
    for (int i = 0; i < obstCount; i++)
    {
        int temp1 = 50 + rand() % 900;
        int temp2 = 50 + rand() % 400;
        while (isTaken(temp1, temp2) == 1) {
			temp1 = 50 + rand() % 900;
			temp2 = 50 + rand() % 400;
		}
        obstXs.push_back(temp1);
        obstYs.push_back(temp2);
        std::vector<int> arr = { temp1, temp2 };        
        allCoords.push_back(arr);
    }
    for (int i = 0; i < 20; i++)
    {
        float variation = 5 * 0.2; 
        float randomRadius = 5 + (rand() % (int)(2 * variation)) - variation;
        asteroidRandoms.push_back(randomRadius);
    }

    for (int i = 0; i <= 10; i++)
    {
        float lineVariance = 5 * 1.2;
        float randomOffsetX = (rand() % (int)(2 * lineVariance)) - lineVariance;
        float randomOffsetY = (rand() % (int)(2 * lineVariance)) - lineVariance;
        asteroidRandoms2x.push_back(randomOffsetX);
        asteroidRandoms2y.push_back(randomOffsetY);
    }
    

    
    collectibleCount = 5 + rand() % 5;
    for (int i = 0; i < collectibleCount; i++)
    {
        int temp1 = 50 + rand() % 900;
        int temp2 = 50 + rand() % 400;
        while (isTaken(temp1, temp2) == 1) {
			temp1 = 50 + rand() % 900;
			temp2 = 50 + rand() % 400;
		}
        collectibleXs.push_back(temp1);
        collectibleYs.push_back(temp2);
        std::vector<int> arr = { temp1, temp2 };
        allCoords.push_back(arr);
    }

    glutCreateWindow("Space Adventure");
    glutDisplayFunc(Display);
    glutSpecialFunc(spe);			
    glutIdleFunc(Anim);
    glutTimerFunc(0, Timer, 0); 


    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(1, 1, 1, 0);
    gluOrtho2D(0, 1000, 0, 600);


    glutMainLoop();

    return 0;
}

int main(int argc, char** argv)
{
    return SDL_main(argc, argv);
}

void drawEllipse(float centerX, float centerY, float radiusX, float radiusY, int numSegments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.14159 * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radiusX * cos(theta);
        float y = radiusY * sin(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}

void drawJerryCan(int centerx, int centery) {

    int halfwidth = 20;
    int halfheight = 25;

    // Body
    glPushMatrix();
    glTranslatef(centerx, centery, 0.0);
    glRotatef(ufoCanAnime, 0.0f, 0.0f, 1.0f);
    glTranslatef(-centerx, -centery, 0.0);
    glColor3f(1, 0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(centerx- halfwidth, centery- halfheight);
    glVertex2f(centerx+ halfwidth, centery- halfheight);
    glVertex2f(centerx+ halfwidth, centery+ halfheight);
    glVertex2f(centerx- halfwidth, centery+ halfheight);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(centerx - halfwidth, centery + halfheight);
    glVertex2f(centerx - halfwidth + 15, centery + halfheight);
    glVertex2f(centerx - halfwidth + 15, centery + halfheight + 8);
    glVertex2f(centerx - halfwidth, centery + halfheight + 8);
    glEnd();

    glColor3f(1, 0, 0.0);
    glLineWidth(3);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    glVertex2f(centerx - halfwidth + 15, centery + halfheight);
    glVertex2f(centerx - halfwidth + 15 + 8, centery + halfheight + 8);

    glVertex2f(centerx - halfwidth + 15 + 8, centery + halfheight + 8);
    glVertex2f(centerx + halfwidth - 3, centery + halfheight + 8);

    glVertex2f(centerx + halfwidth - 3, centery + halfheight + 8);
    glVertex2f(centerx + halfwidth - 3, centery + halfheight);
    glEnd();
    glPopMatrix();
}

void drawJet1() {

    int x = 500 + posX;
    int y = 300 + posY;
    int r = 15;
    int bigR = 40;

    int triHeight = 15;

    rgtBndColl = x + r + triHeight;
    lftBndColl = x - r - triHeight;
    upBndColl = y + bigR;
    dwnBndColl = y - bigR - 7;

    rgtBndMove = x + bigR;
    lftBndMove = x - bigR;
    upBndMove = y + bigR;
    dwnBndMove = y - bigR;

    // Body
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(rot, 0.0, 0.0, 1.0);
    glTranslatef(-x, -y, 0.0);

   /* glColor3f(0.5, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(lftBndColl, upBndColl);
    glVertex2f(rgtBndColl, upBndColl);
    glVertex2f(rgtBndColl, dwnBndColl);
    glVertex2f(lftBndColl, dwnBndColl);*/

    glColor3f(0.5f, 0.5f, 0.5f);  
    drawEllipse(x, y, r, bigR, 50);

    // Cockpit 
    glColor3f(0, 0, 0);  
    drawCircle(x, y, r, 50);

    // Wings
    glColor3f(0.5f, 0.5f, 0.5f);  
    glBegin(GL_TRIANGLES);
    glVertex2f(x + r - 2, y + 18);
    glVertex2f(x + r - 2, y - 18);
    glVertex2f(x + r + triHeight, y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x - r + 2, y + 18);
    glVertex2f(x - r + 2, y - 18);
    glVertex2f(x - r - triHeight, y);
    glEnd();

    // Tail
    int halfWidth = 20;
    int halfHeight = 7;
    glColor3f(0.5f, 0.5f, 0.5f); 
    glBegin(GL_QUADS);
    glVertex2f(x + halfWidth, y - bigR + halfHeight);
    glVertex2f(x - halfWidth, y - bigR + halfHeight);
    glVertex2f(x - halfWidth, y - bigR - halfHeight);
    glVertex2f(x + halfWidth, y - bigR - halfHeight);
    glEnd();

    /*rgtBndColl = x + r + 25;
    lftBndColl = x - r - 25;
    upBndColl = y + bigR;
    dwnBndColl = y - bigR - halfHeight;

    rgtBndMove = x + bigR;
    lftBndMove = x - bigR;
    upBndMove = y + bigR;
    dwnBndMove = y - bigR;*/

    


    glPopMatrix();

    
}

void healthBar() {
    glColor3f(0.2, 0.2, 0.2); 
    glBegin(GL_POLYGON);
    glVertex2f(20, 20 + 500+10);
    glVertex2f(20 + 340, 20 + 500 + 10);
    glVertex2f(20 + 340, 70 + 500 + 10);
    glVertex2f(20, 70 + 500 + 10);
    glEnd();

    glColor3f(0.0, 1.0, 0.0); 
    glBegin(GL_POLYGON);
    glVertex2f(20, 20 + 500 + 10);
    glVertex2f(20 + health * 3.4, 20 + 500 + 10);
    glVertex2f(20 + health * 3.4, 70 + 500 + 10);
    glVertex2f(20, 70 + 500 + 10);
    glEnd();
}

void drawCircle(float centerX, float centerY, float radius, int numSegments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);  // Center of the circle
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.14159 * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}

void drawHalfCircle(float centerX, float centerY, float radius, int numSegments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);  
    for (int i = 0; i <= numSegments / 2; i++) {
        float theta = 3.14159 * static_cast<float>(i) / static_cast<float>(numSegments / 2);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}

void collectibleCollisions() {
    for (int i = 0; i < collectibleCount; i++) {
        if (rgtBndColl >= collectibleXs[i] - 20 && lftBndColl <= collectibleXs[i] + 20 &&
            upBndColl >= collectibleYs[i] - 25 && dwnBndColl <= collectibleYs[i] + 25 + 8 &&
            collectibleXs[i] != -1000 && collectibleYs[i] != 1000) {
            collectibleXs[i] = -1000;
            collectibleYs[i] = -1000;
            score += 10;
            playSoundEffect(collectibleSoundEffect);
            collected++;
            break;
        }
    }
}

void obstCollisions(int k) {
    for (int i = 0; i < obstCount; i++) {
        if (rgtBndColl >= obstXs[i] - 20 && lftBndColl <= obstXs[i] + 20 &&
            upBndColl >= obstYs[i] - 20 && dwnBndColl <= obstYs[i] + 20 &&
            obstXs[i] != -1000 && obstYs[i] != 1000) {
            /*obstXs[i] = -1000;
            obstYs[i] = -1000;*/
            if (k == GLUT_KEY_UP) {
                posY -= 10;
            }
            else if (k == GLUT_KEY_DOWN) {
                posY += 10;
            }
            else if (k == GLUT_KEY_LEFT) {
                posX += 10;
            }
            else if (k == GLUT_KEY_RIGHT) {
                posX -= 10;
            }
            if (immunityPower == 0)
            {
                health -= 20;
                playSoundEffect(obstSoundEffect);
            }
            break;
        }
    }
}

//void obstCollisions(int k) {
//    for (int i = 0; i < obstCount; i++) {
//        if (rgtBndColl >= obstXs[i] - 10 && lftBndColl <= obstXs[i] + 10 &&
//            upBndColl >= obstYs[i] - 10 && dwnBndColl <= obstYs[i] + 10 &&
//            obstXs[i] != -1000 && obstYs[i] != 1000) {
//            /*obstXs[i] = -1000;
//            obstYs[i] = -1000;*/
//            if (k == GLUT_KEY_UP) {
//                posY -= 10;
//            }
//            else if (k == GLUT_KEY_DOWN) {
//				posY += 10;
//			}
//            else if (k == GLUT_KEY_LEFT) {
//				posX += 10;
//			}
//            else if (k == GLUT_KEY_RIGHT) {
//				posX -= 10;
//			}
//            if(immunityPower == 0)
//            {
//                health -= 20;
//                playSoundEffect(obstSoundEffect);
//            }
//            break;
//        }
//    }
//}

void ufoColl() {
    if (rgtBndColl >= UFOx - 25 && lftBndColl <= UFOx + 25 &&
        upBndColl >= UFOy - 15 && dwnBndColl <= UFOy + 20 &&
        UFOx != -1000 && UFOy != 1000) {
        UFOx = -1000;
        UFOy = -1000;
        // powerup
        currentTimeUFO = timeInSeconds;
        ufoPower = 1;
        playSoundEffect(ufoSoundEffect);
    }
}

void blackHoleColl() {
    if (rgtBndColl >= bhx - 25 && lftBndColl <= bhx + 25 &&
        upBndColl >= bhy - 25 && dwnBndColl <= bhy + 25 &&
        bhx != -1000 && bhy != 1000) {
        bhx = -1000;
        bhy = -1000;
        // powerup
        currentTimeBh = timeInSeconds;
        bhPower = 1;
        playSoundEffect(bhSoundEffect);
    }
}

void planetColl() {
    if (rgtBndColl >= planetX - 40 && lftBndColl <= planetX + 40 &&
        upBndColl >= planetY - 40 && dwnBndColl <= planetY + 40 &&
        planetX != -1000 && planetY != 1000 && collected == collectibleCount) {
        planetX = -1000;
        planetY = -1000;
        // goal
        win = 1;
        playSoundEffect(goalSoundEffect);
    }
}

int isTaken(int x, int y) {
    for (int i = 0; i < allCoords.size(); i++)
    {
        if (x < allCoords[i][0] + 60 && x> allCoords[i][0] - 60 &&
            y < allCoords[i][1] + 60 && y> allCoords[i][1] - 60) {
            return 1;
        }
    }
    return 0;
}

void spe(int k, int x, int y)
{
    int speed = 1;
    if(speedupPower == 1)
		speed = 5;
    if (k == GLUT_KEY_RIGHT && rgtBndMove <= 975 && disable == 0)
    {
        if (rgtBndMove < 975) {
            posX+=speed;
			  
        }
        else {
            if (immunityPower == 0)
            {
                health -= 20;
                playSoundEffect(obstSoundEffect);
            }
        }
        rot = 270;
    }
    if (k == GLUT_KEY_RIGHT && rgtBndMove > 975 && disable == 0) {
        if (immunityPower == 0)
        {
            health -= 20;
            playSoundEffect(obstSoundEffect);
        }
    }
    if (k == GLUT_KEY_LEFT && lftBndMove >= 20 && disable == 0)
    {
        if(lftBndMove > 20)
        {
            posX-=speed;
            
        }
        else {
            if (immunityPower == 0)
            {
                health -= 20;
                playSoundEffect(obstSoundEffect);
            }
		}
        rot = 90;
    }
    if (k == GLUT_KEY_LEFT && lftBndMove < 20 && disable == 0) {
        if (immunityPower == 0)
        {
            health -= 20;
            playSoundEffect(obstSoundEffect);
        }
    }
    if (k == GLUT_KEY_UP && upBndMove <= 505 && disable == 0)
    {
        if(upBndMove < 505)
        {
            posY+=speed;
            
        }
        else {
            if (immunityPower == 0)
            {
                health -= 20;
                playSoundEffect(obstSoundEffect);
            }
        }
        rot = 0;
    }
    if (k == GLUT_KEY_UP && upBndMove > 505 && disable == 0) {
        if (immunityPower == 0)
        {
            health -= 20;
            playSoundEffect(obstSoundEffect);
        }
    }
    if (k == GLUT_KEY_DOWN && dwnBndMove >= 20 && disable == 0)
    {
        if (dwnBndMove > 20)
        {
			posY-=speed;
			
		}
        else {
            if (immunityPower == 0)
            {
                health -= 20;
                playSoundEffect(obstSoundEffect);
            }
		}
        rot = 180;
    }
    if (k == GLUT_KEY_DOWN && dwnBndMove < 20 && disable == 0) {
        if (immunityPower == 0)
        {
            health -= 20;
            playSoundEffect(obstSoundEffect);
        }
    }
    collectibleCollisions();
    obstCollisions(k);
    ufoColl();
    blackHoleColl();
    planetColl();
    glutPostRedisplay();
}

void Timer(int value) {
    if (ufoPower == 1)
    {
        immunityPower = 1;
        displayedUfoTimer = 20 - (currentTimeUFO - timeInSeconds);
	}

    if (displayedUfoTimer <= 0)
    {
		ufoPower = 0;
        immunityPower = 0;
	}

    if (bhPower == 1)
    {
		speedupPower = 1;
		displayedBhTimer = 20 - (currentTimeBh - timeInSeconds);
	}

    if (displayedBhTimer <= 0)
    {
        bhPower = 0;
        speedupPower = 0;
    }

    if (timeInSeconds > 0 && disable == 0) {
        timeInSeconds--;
        glutPostRedisplay();
    }

    if (timeInSeconds > 0 && disable == 0) {
        glutTimerFunc(1000, Timer, 0);
    }

    glutPostRedisplay();
}

//void drawAsteroid(float x, float y, float radius, int numPoints) {
//    glColor3f(0.588, 0.11, 0.149);
//
//    glPushMatrix();
//    glTranslatef(x, y, 0);
//    glRotatef(obsGoalAnime, 0.0f, 0.0f, 1.0f);
//    glTranslatef(-x, -y, 0);
//    glBegin(GL_POLYGON);
//    for (int i = 0; i < numPoints; i++) {
//        float angle = 2.0 * 3.14159 * i / numPoints;
//        float offsetX = radius * cos(angle);
//        float offsetY = radius * sin(angle);
//
//        float randomRadius = asteroidRandoms[i];
//
//        glVertex2f(x + offsetX * randomRadius, y + offsetY * randomRadius);
//    }
//    glEnd();
//
//    int numLineSegments = 10; 
//    float lineLength = radius * 1.2; 
//    float lineVariance = radius * 1.2; 
//    glColor3f(0.969, 0.408, 0.024);
//    glBegin(GL_LINE_STRIP);
//    for (int i = 0; i <= numLineSegments; i++) {
//        float t = static_cast<float>(i) / numLineSegments;
//        float angle = 2.0 * 3.14159 * t;
//        float offsetX = lineLength * cos(angle);
//        float offsetY = lineLength * sin(angle);
//
//        float randomOffsetX = asteroidRandoms2x[i];
//        float randomOffsetY = asteroidRandoms2y[i];
//
//        glVertex2f(x + offsetX + randomOffsetX, y + offsetY + randomOffsetY);
//    }
//    glEnd();
//    glPopMatrix();
//}

void drawAsteroid(float x, float y, float radius, int numPoints) {
    

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(ufoCanAnime, 0.0f, 0.0f, 1.0f);
    glTranslatef(-x, -y, 0);
    glColor3f(0.588, 0.11, 0.149);
    glBegin(GL_POLYGON);
    glVertex3f(x+radius, y+radius, 0);
    glVertex3f(x - radius, y + radius, 0);
    glVertex3f(x - radius, y - radius, 0);
    glVertex3f(x + radius, y - radius, 0);
    glEnd();
    //drawCircle(x, y, radius, numPoints);

    glColor3f(0.969, 0.408, 0.024);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y+5);
    glVertex2f(x + 5, y - 5);
    glVertex2f(x - 5, y-5);
    glEnd();
    glPopMatrix();
}

void drawSupernova(int x, int y) {

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(obsGoalAnime, 0.0f, 0.0f, 1.0f);
    glColor3f(0,0,0); 
    float radius = 25;
    int numSegments = 100;
    drawCircle(0, 0, radius, numSegments);
    

    // Inner Circle 
    glBegin(GL_LINE_LOOP);
    glColor3f(0.9176, 0.4706, 0.0275);
    radius = 13;
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * 3.14159 * i / numSegments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.9176, 0.4706, 0.0275);
    radius = 25;
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * 3.14159 * i / numSegments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.9176, 0.4706, 0.0275);
    glVertex2f(-35, 0.0f);
    glVertex2f(35, 0.0f);
    glEnd();

    glPopMatrix();
}

void drawPlanet(float centerX, float centerY, float radius, int numSlices) {
    glColor3f(0.0f, 0.5f, 1.0f); 

    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(obsGoalAnime, 0.0f, 0.0f, 1.0f);
    glTranslatef(-centerX, -centerY, 0.0f);
    drawCircle(centerX, centerY, radius, numSlices);
    
    int numContinentSlices = 50; 
    float continentRadius = radius * 0.5f; 
    glColor3f(0.2f, 0.8f, 0.2f); 
    drawCircle(centerX, centerY, continentRadius, numContinentSlices);
    

    glColor3f(0.0f, 0.0f, 0.0f); 

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= numSlices; i++) {
        float angle = i * 2.0f * 3.14159 / numSlices;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    int numCraters = 5; 
    float craterRadius = radius * 0.1f; 
    glColor3f(0.5f, 0.5f, 0.5f); 
    for (int i = 0; i < numCraters; i++) {
        float angle = i * 2.0f * 3.14159 / numCraters;
        float x = centerX + radius * 0.8f * cos(angle);
        float y = centerY + radius * 0.8f * sin(angle);

        drawCircle(x, y, craterRadius, numSlices);
    }
    glPopMatrix();
}

void drawBoundary1() {
    glColor3f(0,0,0); 

    glBegin(GL_QUADS);
    glVertex2f(15, 15); 
    glVertex2f(20, 15); 
    glVertex2f(20, 510); 
    glVertex2f(15, 510); 
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(15, 15); 
    glVertex2f(980, 15); 
    glVertex2f(980, 20); 
    glVertex2f(15, 20); 
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(980, 20); 
    glVertex2f(980, 510); 
    glVertex2f(975, 510); 
    glVertex2f(975, 20); 
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(20, 510); 
    glVertex2f(15, 505); 
    glVertex2f(975, 505); 
    glVertex2f(975, 510); 
    glEnd();



    glBegin(GL_QUADS);
    glVertex2f(5, 10); 
    glVertex2f(10, 10); 
    glVertex2f(10, 520);
    glVertex2f(5, 520); 
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(5, 5); 
    glVertex2f(990, 5); 
    glVertex2f(990, 10); 
    glVertex2f(5, 10); 
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(990, 10); 
    glVertex2f(990, 520); 
    glVertex2f(985, 520); 
    glVertex2f(985, 10);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(10, 520); 
    glVertex2f(5, 515); 
    glVertex2f(985, 515);
    glVertex2f(985, 520); 
    glEnd();

}

void drawUFO(int x, int y) {
    // Body (Ellipse)

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(ufoCanAnime, 0.0f, 0.0f, 1.0f);
    glColor3f(0.5f, 0.5f, 0.5f); 
    float radiusX = 25;
    float radiusY = 15;
    int numSegments = 100;
    drawEllipse(0, 0, radiusX, radiusY, numSegments);
    

    // Dome 
    glColor3f(0.655, 0.78, 0.796);
    drawHalfCircle(0.0f, 13.0f, 15, 100);
    

    // Windows 
    glColor3f(0, 0, 0);
    drawCircle(0.0f, 0, 5, 100);
    drawCircle(14.0f, 0, 5, 100);
    drawCircle(-14.0f, 0, 5, 100);
    
    glPopMatrix();
}

void Anim() {

    if (obsGoalAnime < 360) {
        obsGoalAnime += 0.06;
    }
	else
		obsGoalAnime = 0;

    
    if (ufoCanAnime <= 30 && ufoCanAnime >= -30 && change == 0) {
        ufoCanAnime -= 0.06;
        if(ufoCanAnime < -29)
			change = 1;
    }
    if (ufoCanAnime <= 30 && ufoCanAnime >= -30 && change == 1) {
        ufoCanAnime += 0.06;
        if (ufoCanAnime > 29)
            change = 0;
    }
   
    glutPostRedisplay();
}

void drawHexagon(float centerX, float centerY, float size) {
    glColor3f(0.5f, 0.5f, 0.5f); 
    glPushMatrix();
    glTranslatef(backAnime, 0, 0.0f);
    float angle = 2.0f * 3.14159 / 6.0f; 
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; i++) {
        float x = centerX + size * cos(i * angle);
        float y = centerY + size * sin(i * angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int length = 5 + rand() % 15;
    for (int i = 0; i < length; i++)
    {
        int xh = 50 + rand() % 900;
        int yh = 50 + rand() % 450;
        drawHexagon(xh, yh, 5);
    }

    glColor3f(0, 0, 0);
    glRasterPos2f(400, 550 + 10);
    
    std::ostringstream oss1;
    oss1 << std::fixed << std::setprecision(2) << score;
    std::string score_str = "Score: " + oss1.str();
    for (char c : score_str) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    
    if (ufoPower == 1 && displayedUfoTimer > 0) {
        glColor3f(0, 0, 0);
		glRasterPos2f(400, 520 + 10);
        
		std::string ufo_str = "Immunity For:"+std::to_string(displayedUfoTimer) + " s";
        for (char c : ufo_str) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		}

    }

    if (bhPower == 1 && displayedBhTimer > 0) {
        glColor3f(0, 0, 0);
        glRasterPos2f(650, 520 + 10);

        std::string ufo_str = "SpeedUP For:" + std::to_string(displayedBhTimer) + " s";
        for (char c : ufo_str) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }

    }

    glColor3f(0, 0, 0);
    glRasterPos2f(650, 550 + 10);
    std::string timeString = "Time remaining: " + std::to_string(timeInSeconds) + " seconds";
    
    for (char c : timeString) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    healthBar();
    for (int i = 0; i < collectibleCount; i++)
    {
        if(collectibleXs[i] != -1000 && collectibleYs[i] != -1000)
            drawJerryCan(collectibleXs[i], collectibleYs[i]);
    }
    for (int i = 0; i < obstCount; i++)
    {
        /*if (obstXs[i] != -1000 && obstYs[i] != -1000)
            drawAsteroid(obstXs[i], obstYs[i], 5, 20);*/
        if (obstXs[i] != -1000 && obstYs[i] != -1000)
            drawAsteroid(obstXs[i], obstYs[i], 20, 20);
    }
    drawJet1();
    drawBoundary1();
    if(bhx != -1000 && bhy != -1000)
        drawSupernova(bhx, bhy);

    if (UFOx != -1000 && UFOy != -1000)
        drawUFO(UFOx, UFOy);

    if(collected == collectibleCount)
        drawPlanet(planetX, planetY, 40, 100);

    if (health == 0 || timeInSeconds == 0)
    {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		glRasterPos2f(400, 300);
		std::string gameOver = "Game Over";
        for (char c : gameOver) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		}
		glRasterPos2f(400, 250);
		std::string finalScore = "Final Score: " + std::to_string(score);
        for (char c : finalScore) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		}
		glRasterPos2f(400, 200);
        int lastT = timeInSeconds;
		std::string timeString = "Time remaining: " + std::to_string(lastT) + " seconds";
        for (char c : timeString) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		}
        disable = 1;
        if (first == 0)
        {
            first = 1;
            Mix_HaltMusic();
            playMusic(lossMusic, -1);
        }
		glFlush();
	}
    if (win == 1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0, 0, 0);
        glRasterPos2f(400, 300);
        std::string gameOver = "You Won!!!!";
        for (char c : gameOver) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
        glRasterPos2f(400, 250);
        std::string finalScore = "Final Score: " + std::to_string(score);
        for (char c : finalScore) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
        glRasterPos2f(400, 200);
        int lastT = timeInSeconds;
        std::string timeString = "Time remaining: " + std::to_string(lastT) + " seconds";
        for (char c : timeString) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
        disable = 1;
        if (first == 0)
        {
            first = 1;
            Mix_HaltMusic();
            playMusic(winMusic, -1);
        }
        glFlush();
    }

    glFlush();
}
