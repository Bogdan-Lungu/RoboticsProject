#include <TFT_eSPI.h>
#include <math.h>  // Pentru cos() și sin()
 
// ==================== [ 1. CONFIGURĂRI GENERALE ] ==========================

#include <Arduino.h>

// dac pins for esp32
#define DAC_PIN 25
#define LED_R 27  // Red
#define LED_G 26  // Green
#define LED_B 21  // Blue


// note structure 
struct Note {
  float frequency; 
  int duration;    
};
//colors for space invades 
uint16_t colors[] = {TFT_RED, TFT_ORANGE, TFT_YELLOW, TFT_GREEN, TFT_BLUE};

Note melody[] = {
  {659.25, 416}, // NOTE_E5, 4
  {493.88, 208}, // NOTE_B4, 8
  {523.25, 208}, // NOTE_C5, 8
  {587.33, 416}, // NOTE_D5, 4
  {523.25, 208}, // NOTE_C5, 8
  {493.88, 208}, // NOTE_B4, 8
  {440.00, 416}, // NOTE_A4, 4
  {440.00, 208}, // NOTE_A4, 8
  {523.25, 208}, // NOTE_C5, 8
  {659.25, 416}, // NOTE_E5, 4
  {587.33, 208}, // NOTE_D5, 8
  {523.25, 208}, // NOTE_C5, 8
  {493.88, 624}, // NOTE_B4, -4
  {523.25, 208}, // NOTE_C5, 8
  {587.33, 416}, // NOTE_D5, 4
  {659.25, 416}, // NOTE_E5, 4
  {523.25, 416}, // NOTE_C5, 4
  {440.00, 416}, // NOTE_A4, 4
  {440.00, 208}, // NOTE_A4, 8
  {440.00, 416}, // NOTE_A4, 4
  {493.88, 208}, // NOTE_B4, 8
  {523.25, 208}, // NOTE_C5, 8

  {587.33, 624}, // NOTE_D5, -4
  {698.46, 208}, // NOTE_F5, 8
  {880.00, 416}, // NOTE_A5, 4
  {783.99, 208}, // NOTE_G5, 8
  {698.46, 208}, // NOTE_F5, 8
  {659.25, 624}, // NOTE_E5, -4
  {523.25, 208}, // NOTE_C5, 8
  {659.25, 416}, // NOTE_E5, 4
  {587.33, 208}, // NOTE_D5, 8
  {523.25, 208}, // NOTE_C5, 8
  {493.88, 416}, // NOTE_B4, 4
  {493.88, 208}, // NOTE_B4, 8
  {523.25, 208}, // NOTE_C5, 8
  {587.33, 416}, // NOTE_D5, 4
  {659.25, 416}, // NOTE_E5, 4
  {523.25, 416}, // NOTE_C5, 4
  {440.00, 416}, // NOTE_A4, 4
  {440.00, 416}, // NOTE_A4, 4
  {0, 416},      // REST, 4

  {659.25, 416}, // NOTE_E5, 4
  {493.88, 208}, // NOTE_B4, 8
  {523.25, 208}, // NOTE_C5, 8
  {587.33, 416}, // NOTE_D5, 4
  {523.25, 208}, // NOTE_C5, 8
  {493.88, 208}, // NOTE_B4, 8
  {440.00, 416}, // NOTE_A4, 4
  {440.00, 208}, // NOTE_A4, 8
  {523.25, 208}, // NOTE_C5, 8
  {659.25, 416}, // NOTE_E5, 4
  {587.33, 208}, // NOTE_D5, 8
  {523.25, 208}, // NOTE_C5, 8
  {493.88, 624}, // NOTE_B4, -4
  {523.25, 208}, // NOTE_C5, 8
  {587.33, 416}, // NOTE_D5, 4
  {659.25, 416}, // NOTE_E5, 4
  {523.25, 416}, // NOTE_C5, 4
  {440.00, 416}, // NOTE_A4, 4
  {440.00, 208}, // NOTE_A4, 8
  {440.00, 416}, // NOTE_A4, 4
  {493.88, 208}, // NOTE_B4, 8
  {523.25, 208}, // NOTE_C5, 8

  {587.33, 624}, // NOTE_D5, -4
  {698.46, 208}, // NOTE_F5, 8
  {880.00, 416}, // NOTE_A5, 4
  {783.99, 208}, // NOTE_G5, 8
  {698.46, 208}, // NOTE_F5, 8
  {659.25, 624}, // NOTE_E5, -4
  {523.25, 208}, // NOTE_C5, 8
  {659.25, 416}, // NOTE_E5, 4
  {587.33, 208}, // NOTE_D5, 8
  {523.25, 208}, // NOTE_C5, 8
  {493.88, 416}, // NOTE_B4, 4
  {493.88, 208}, // NOTE_B4, 8
  {523.25, 208}, // NOTE_C5, 8
  {587.33, 416}, // NOTE_D5, 4
  {659.25, 416}, // NOTE_E5, 4
  {523.25, 416}, // NOTE_C5, 4
  {440.00, 416}, // NOTE_A4, 4
  {440.00, 416}, // NOTE_A4, 4
  {0, 416},      // REST, 4

  {659.25, 1000}, // NOTE_E5, 2
  {523.25, 1000}, // NOTE_C5, 2
  {587.33, 1000}, // NOTE_D5, 2
  {493.88, 1000}, // NOTE_B4, 2
  {523.25, 1000}, // NOTE_C5, 2
  {440.00, 1000}, // NOTE_A4, 2
  {415.30, 1000}, // NOTE_GS4, 2
  {493.88, 416},  // NOTE_B4, 4
  {0, 208},       // REST, 8
  {659.25, 1000}, // NOTE_E5, 2
  {523.25, 1000}, // NOTE_C5, 2
  {587.33, 1000}, // NOTE_D5, 2
  {493.88, 1000}, // NOTE_B4, 2
  {523.25, 416},  // NOTE_C5, 4
  {659.25, 416},  // NOTE_E5, 4
  {880.00, 1000}, // NOTE_A5, 2
  {830.61, 1000}, // NOTE_GS5, 2
};


// melody lenght 
const int MELODY_LENGTH = sizeof(melody) / sizeof(Note);

// song speed
float speedMultiplier = 0.55; 

// play the melody on loop
void melodyTask(void *parameter) {
  while (true) {
    for (int i = 0; i < MELODY_LENGTH; i++) {
      int duration = melody[i].duration * speedMultiplier; 
      if (melody[i].frequency > 0) {
        playSquareWave(melody[i].frequency, duration);
      } else {
        noTone(DAC_PIN); 
      }
      delay(duration * 0.8); 
    }
    delay(500); 
  }
}

// generate the signal
void playSquareWave(float frequency, int durationMs) {
  if (frequency == 0) {
    delay(durationMs);
    return;
  }
  int halfPeriodMicrosec = (int)(1e6 / (2 * frequency)); 
  int volume = 1; // set volume 0 - 255

  unsigned long endTime = millis() + durationMs;
  while (millis() < endTime) {
    dacWrite(DAC_PIN, volume);       
    delayMicroseconds(halfPeriodMicrosec);
    dacWrite(DAC_PIN, 0);            
    delayMicroseconds(halfPeriodMicrosec);
  }
}


// TFT 
TFT_eSPI tft = TFT_eSPI();

// screen size
#define SCREEN_WIDTH  480
#define SCREEN_HEIGHT 320

// Pinuri 
#define JOY_X_PIN  33
#define JOY_Y_PIN  32
#define JOY_SW_PIN 12  

// current game variable
// -1 = no game
//  0 = Space Invaders
//  1 = Breakout
//  2 = Dino
int currentGame = -1;

// Space invaders 

// ship 
#define SHIP_WIDTH  30
#define SHIP_HEIGHT 10
int shipX = SCREEN_WIDTH/2 - SHIP_WIDTH/2;
int shipY = SCREEN_HEIGHT - SHIP_HEIGHT - 10;

// enemy/ship bullet
#define BULLET_WIDTH  5
#define BULLET_HEIGHT 10
bool bulletActive      = false;
bool enemyBulletActive = false;
int bulletX, bulletY;
int enemyBulletX, enemyBulletY;

// enemy
#define ENEMY_WIDTH   15
#define ENEMY_HEIGHT  10
#define ENEMY_ROWS    5
#define ENEMY_COLS    7
#define ENEMY_SPACING 15
bool enemies[ENEMY_ROWS][ENEMY_COLS];
int enemyX[ENEMY_ROWS][ENEMY_COLS];
int enemyY[ENEMY_ROWS][ENEMY_COLS];
int enemyDirection = 1;  

// speeds 
int shipSpeed        = 5;
int bulletSpeed      = 10;
int enemySpeed       = 3;
int enemyBulletSpeed = 5;

// enemy shoot interval 
unsigned long lastEnemyShot    = 0;
const unsigned long enemyShotInterval = 1000; 

// global score, also used by breakout
int score = 0;


// Breakout


// player
#define PADDLE_WIDTH  60
#define PADDLE_HEIGHT 10
#define BALL_SIZE     8

// initial positions 
int paddleX = SCREEN_WIDTH/2 - PADDLE_WIDTH/2;
int paddleY = SCREEN_HEIGHT - 30;
int ballX   = paddleX + PADDLE_WIDTH/2;
int ballY   = paddleY - BALL_SIZE/2;

// ball direction 
float ballDirectionX = 0;
float ballDirectionY = 0;

int ballSpeed = 60;

// brick
#define BRICK_COLS       10
#define BRICK_ROWS       5
#define BRICK_WIDTH      (SCREEN_WIDTH/BRICK_COLS)
#define BRICK_HEIGHT     20
#define BRICK_TOP_MARGIN 50
bool bricks[BRICK_ROWS][BRICK_COLS];

// brick colors 
uint16_t brickColors[BRICK_ROWS] = {TFT_RED, TFT_ORANGE, TFT_YELLOW, TFT_GREEN, TFT_BLUE};

// game over flag 
bool breakoutGameOverCalled = false;


// Dino

// player
#define DINO_WIDTH   20
#define DINO_HEIGHT  40
#define GROUND_Y     (SCREEN_HEIGHT - 20)
#define JUMP_HEIGHT  20
#define GRAVITY      2
#define DUCK_ACCELERATION 5

// movement 
int dinoX = 50;
int dinoY = GROUND_Y - DINO_HEIGHT;
int dinoVelocityY = 0;
bool isJumping  = false;
bool isDucking  = false;

// bricks
struct Obstacle {
  int x;
  int y;
  int width;
  int height;
  uint16_t color;
};


#define MAX_OBSTACLES  5
Obstacle obstacles[MAX_OBSTACLES];
int numObstacles   = 0;
int obstacleSpeed  = 5;
int dinoScore      = 0;

unsigned long lastObstacleTime = 0;
unsigned long obstacleInterval = 2000; 

// obstacle colors
uint16_t obstacleColors[] = {TFT_RED, TFT_ORANGE, TFT_YELLOW, TFT_GREEN, TFT_BLUE, TFT_PURPLE};
#define NUM_COLORS (sizeof(obstacleColors)/sizeof(obstacleColors[0]))


// functions prototypes

// menus 
int showMenu();
int postGameMenu();

// setup/loop
void setup();
void loop();

// Space Invaders
void initializeEnemies();
void drawShip();
void clearShip();
void moveEnemies();
void drawEnemies();
void clearEnemies();
void checkBulletCollision();
void checkEnemyBulletCollision();
void checkEnemiesReachedBottom();
void enemyShoot();
void checkVictory();
void resetGame();     
void gameOver();      

// Breakout
void resetGameBreakout();
void drawBricksBreakout();
void moveBallBreakout();
void updatePaddleBreakout();
void breakoutGameOver();
void breakoutCheckVictory();

// Dino
void resetDinosaurGame();
void dinosaurGameOver();
void drawDino();
void clearDino();
void updateDino();
bool checkCollision();
void addObstacle();
void updateObstacles();
void updateScoreAndSpeed();

// others
void drawTopMargin();
int clamp(int val, int mn, int mx);

// Different Functions
//
//   [A] FUNCȚII UZUALE / UTILE (meniuri etc.)
//   [B] SPACE INVADERS
//   [C] BREAKOUT
//   [D] DINO
//   [E] SETUP & LOOP



// General

// show menu
int showMenu() {
  // Wait for joystick button release
  while (digitalRead(JOY_SW_PIN) == LOW) {
    delay(10);
  }

  tft.fillScreen(TFT_BLACK);

  // Reset BreakoutGameOver flag to avoid getting stuck
  breakoutGameOverCalled = false;

  int selectedGame = 0; 
  const char* games[] = {"Space Invaders", "   Breakout", "     Dino"};
  const int menuItems = 3;

  // led
  const int colorChangeInterval = 500; 
  unsigned long lastColorChange = millis();
  int currentColorIndex = 0; 
  const int colorSteps = 6; 

  while (true) {
    // Display game options
    for (int i = 0; i < menuItems; i++) {
      if (i == selectedGame) {
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(110, 80 + i * 40);
      tft.setTextSize(3);
      tft.println(games[i]);
    }

    delay(100);

    // Joystick movement (reversed)
    int yValue = analogRead(JOY_Y_PIN);

    if (yValue < 1000 && selectedGame < menuItems - 1) { 
      selectedGame++;
    } else if (yValue > 3000 && selectedGame > 0) { 
      selectedGame--;
    }

    // Button press selects a game
    if (digitalRead(JOY_SW_PIN) == LOW) {
      while (digitalRead(JOY_SW_PIN) == LOW) delay(10); // Wait for release
      return selectedGame;
    }

    // led change
    if (millis() - lastColorChange >= colorChangeInterval) {
      lastColorChange = millis();

      switch (currentColorIndex) {
        case 0: 
          digitalWrite(LED_R, HIGH);
          digitalWrite(LED_G, LOW);
          digitalWrite(LED_B, LOW);
          break;
        case 1: 
          digitalWrite(LED_R, LOW);
          digitalWrite(LED_G, HIGH);
          digitalWrite(LED_B, LOW);
          break;
        case 2: 
          digitalWrite(LED_R, LOW);
          digitalWrite(LED_G, LOW);
          digitalWrite(LED_B, HIGH);
          break;
        case 3: 
          digitalWrite(LED_R, HIGH);
          digitalWrite(LED_G, HIGH);
          digitalWrite(LED_B, LOW);
          break;
        case 4: 
          digitalWrite(LED_R, HIGH);
          digitalWrite(LED_G, LOW);
          digitalWrite(LED_B, HIGH);
          break;
        case 5: 
          digitalWrite(LED_R, LOW);
          digitalWrite(LED_G, HIGH);
          digitalWrite(LED_B, HIGH);
          break;
        default: 
          digitalWrite(LED_R, LOW);
          digitalWrite(LED_G, LOW);
          digitalWrite(LED_B, LOW);
          break;
      }
      currentColorIndex = (currentColorIndex + 1) % colorSteps;
    }
  }
}


// after game menu  
int postGameMenu() {
  tft.fillScreen(TFT_BLACK);

  int selectedOption = 0;
  const char* options[] = {"Play Again", "Go Back to Start Menu"};
  const int menuItems = 2;

  while (true) {
    for (int i = 0; i < menuItems; i++) {
      if (i == selectedOption) {
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(100, 100 + i * 40);
      tft.setTextSize(2);
      tft.println(options[i]);
    }

    delay(200);

    // read joystick
    int yValue = analogRead(JOY_Y_PIN);

    if (yValue < 1000 && selectedOption < menuItems - 1) { 
      selectedOption++; // down
    } else if (yValue > 3000 && selectedOption > 0) { 
      selectedOption--; // up
    }

    // button press
    if (digitalRead(JOY_SW_PIN) == LOW) {
      delay(500);
      return selectedOption;
    }
  }
}


// horizontal draw line
void drawTopMargin() {
  tft.drawLine(0, 30, SCREEN_WIDTH, 30, TFT_WHITE);
}

// clamp 
int clamp(int val, int mn, int mx) {
  if(val<mn) return mn;
  if(val>mx) return mx;
  return val;
}


// Space invaders

void drawEnemies() {
  for (int row = 0; row < ENEMY_ROWS; row++) {
    for (int col = 0; col < ENEMY_COLS; col++) {
      if (enemies[row][col]) {
        int colorIndex = (row + col) % 5; 
        tft.fillRect(enemyX[row][col], enemyY[row][col], ENEMY_WIDTH, ENEMY_HEIGHT, colors[colorIndex]);
      }
    }
  }
}


void initializeEnemies() {
  for (int row = 0; row < ENEMY_ROWS; row++) {
    for (int col = 0; col < ENEMY_COLS; col++) {
      enemies[row][col] = true;
      if(row % 2 == 0)
      {
      enemyX[row][col] = col * (ENEMY_WIDTH + ENEMY_SPACING) + 40;
      enemyY[row][col] = row * (ENEMY_HEIGHT + ENEMY_SPACING) + 40;
      }else
      {
      enemyX[row][col] = col * (ENEMY_WIDTH + ENEMY_SPACING) + 20;
      enemyY[row][col] = row * (ENEMY_HEIGHT + ENEMY_SPACING) + 40;
      }

    }
  }
}

void drawShip() {
  tft.fillRect(shipX, shipY, SHIP_WIDTH, SHIP_HEIGHT, TFT_WHITE);
}

void clearShip() {
  tft.fillRect(shipX, shipY, SHIP_WIDTH, SHIP_HEIGHT, TFT_BLACK);
}

// enemy movement
void moveEnemies() {
  bool changeDirection = false;
  for (int row=0; row<ENEMY_ROWS; row++) {
    for (int col=0; col<ENEMY_COLS; col++) {
      if (enemies[row][col]) {
        enemyX[row][col] += enemyDirection*enemySpeed;
        if(enemyX[row][col]<=0 || (enemyX[row][col] + ENEMY_WIDTH >= SCREEN_WIDTH)) {
          changeDirection = true;
        }
      }
    }
  }
  if(changeDirection) {
    enemyDirection = -enemyDirection;
    for (int row=0; row<ENEMY_ROWS; row++) {
      for (int col=0; col<ENEMY_COLS; col++) {
        enemyY[row][col] += ENEMY_HEIGHT + 20;
      }
    }
  }
}


void clearEnemies() {
  for (int row=0; row<ENEMY_ROWS; row++) {
    for (int col=0; col<ENEMY_COLS; col++) {
      if (enemies[row][col]) {
        tft.fillRect(enemyX[row][col], enemyY[row][col], ENEMY_WIDTH, ENEMY_HEIGHT, TFT_BLACK);
      }
    }
  }
}


void checkBulletCollision() {
  for(int row=0; row<ENEMY_ROWS; row++){
    for(int col=0; col<ENEMY_COLS; col++){
      if(enemies[row][col]){
        int ex = enemyX[row][col];
        int ey = enemyY[row][col];
  
        bool overlap = (bulletX + BULLET_WIDTH > ex) && (bulletX < ex + ENEMY_WIDTH) &&
                       (bulletY < ey + ENEMY_HEIGHT) && (bulletY + BULLET_HEIGHT > ey);
        if(overlap){
          bulletActive = false;
          tft.fillRect(bulletX, bulletY, BULLET_WIDTH, BULLET_HEIGHT, TFT_BLACK);
          bulletX = -1;
          bulletY = -1;

          enemies[row][col] = false;
          tft.fillRect(ex, ey, ENEMY_WIDTH, ENEMY_HEIGHT, TFT_BLACK);

          score += 10;

          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.setTextSize(2);
          tft.setCursor(5,5);
          tft.printf("Score: %d", score);
          drawTopMargin();

          return;
        }
      }
    }
  }
}

// both game overs/collision with bullet, end of game

void checkEnemyBulletCollision(){
  if(enemyBulletActive){
    bool overlap = (enemyBulletX+ BULLET_WIDTH > shipX) && (enemyBulletX < shipX+SHIP_WIDTH) &&
                   (enemyBulletY+ BULLET_HEIGHT>shipY) && (enemyBulletY <shipY+SHIP_HEIGHT);
    if(overlap){
      enemyBulletActive = false;
      tft.fillRect(enemyBulletX, enemyBulletY, BULLET_WIDTH, BULLET_HEIGHT, TFT_BLACK);
      gameOver(); 
    }
  }
}

void checkEnemiesReachedBottom(){
  for(int row=0; row<ENEMY_ROWS; row++){
    for(int col=0; col<ENEMY_COLS; col++){
      if(enemies[row][col]){
        if(enemyY[row][col]+ENEMY_HEIGHT >= shipY){
          gameOver();
        }
      }
    }
  }
}

// random shoot enemy 
void enemyShoot(){
  if(!enemyBulletActive && (millis() - lastEnemyShot > enemyShotInterval)){
    lastEnemyShot = millis();
    int row, col;
    do {
      row = random(0, ENEMY_ROWS);
      col = random(0, ENEMY_COLS);
    } while(!enemies[row][col]);

    enemyBulletX = enemyX[row][col]+ENEMY_WIDTH/2 - BULLET_WIDTH/2;
    enemyBulletY = enemyY[row][col]+ENEMY_HEIGHT;
    enemyBulletActive = true;
  }
}

// victory 
void checkVictory(){
  for(int row=0; row<ENEMY_ROWS; row++){
    for(int col=0; col<ENEMY_COLS; col++){
      if(enemies[row][col]) return; 
    }
  }
  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(100,100);
  tft.println("You Won!");
  tft.setCursor(100,140);
  tft.printf("Final Score: %d", score);
  delay(2500);

  shipX = SCREEN_WIDTH/2 - SHIP_WIDTH/2;
  shipY = SCREEN_HEIGHT- SHIP_HEIGHT-10;

  int choice = postGameMenu();
  if(choice==0){
    resetGame(); 
  } else {
    currentGame = -1; 
  }
}

// game over screen
void gameOver(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(100,100);
  tft.println("Game Over!");
  tft.setCursor(100,140);
  tft.printf("Final Score: %d", score);
  delay(2500);

  shipX = SCREEN_WIDTH/2 - SHIP_WIDTH/2;
  shipY = SCREEN_HEIGHT - SHIP_HEIGHT -10;

  int choice = postGameMenu();
  if(choice==0){
    resetGame();
  } else {
    currentGame = -1;
  }
}

void resetGame(){
  if(currentGame==0){
    // Space Invaders
    shipX         = SCREEN_WIDTH/2 - SHIP_WIDTH/2;
    bulletActive  = false;
    enemyBulletActive = false;
    score = 0;
    initializeEnemies();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(5,5);
    tft.printf("Score: %d", score);
    drawTopMargin();
    drawEnemies();

  } else if(currentGame==1){
    // Breakout
    resetGameBreakout();

  } else if(currentGame==2){
    // Dino
    resetDinosaurGame();
  }
}


// Breakout

// initialize game
void resetGameBreakout(){
  paddleX = SCREEN_WIDTH/2 - PADDLE_WIDTH/2;
  ballX   = paddleX + PADDLE_WIDTH/2;
  ballY   = paddleY - BALL_SIZE/2;

  float angle   = random(30, 150);
  float radians = angle*M_PI/180.0;

  ballDirectionX = cos(radians);
  ballDirectionY = -fabs(sin(radians));

  // reset bricks
  for(int row=0; row<BRICK_ROWS; row++){
    for(int col=0; col<BRICK_COLS; col++){
      bricks[row][col] = true;
    }
  }
  // reset score
  score = 0;

  // top margin score
  tft.fillScreen(TFT_BLACK);
  tft.drawLine(0,30, SCREEN_WIDTH,30, TFT_WHITE);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(5,5);
  tft.printf("Score: %d", score);
}

void drawBricksBreakout(){
  for(int row=0; row<BRICK_ROWS; row++){
    for(int col=0; col<BRICK_COLS; col++){
      if(bricks[row][col]){
        int x = col*BRICK_WIDTH;
        int y = BRICK_TOP_MARGIN + row*BRICK_HEIGHT;
        tft.fillRect(x, y, BRICK_WIDTH-2, BRICK_HEIGHT-2, brickColors[row]);
      }
    }
  }
}

// ball momvement breakout 
void moveBallBreakout(){
  // higher lvl of movement
  ballX += ballDirectionX*(ballSpeed/10.0f);
  ballY += ballDirectionY*(ballSpeed/10.0f);

  // collisions
  if(ballX <= BALL_SIZE/2){
    ballX = BALL_SIZE/2+1;
    ballDirectionX = -ballDirectionX;
  } else if(ballX>=SCREEN_WIDTH - BALL_SIZE/2){
    ballX = SCREEN_WIDTH - BALL_SIZE/2 -1;
    ballDirectionX = -ballDirectionX;
  }

  if(ballY <= 30+BALL_SIZE/2){
    ballY = 30 + BALL_SIZE/2 +1;
    ballDirectionY = -ballDirectionY;
  }

  // paddle collisions
  bool colPaddle = (ballY+BALL_SIZE/2 >= paddleY) &&
                   (ballX+BALL_SIZE/2 >= paddleX) &&
                   (ballX-BALL_SIZE/2 <= paddleX+PADDLE_WIDTH);
  if(colPaddle){
    ballY = paddleY - BALL_SIZE/2 -1;
    ballDirectionY = -fabs(ballDirectionY);

    // X ajustment 
    float relativeHit = (ballX - (paddleX + PADDLE_WIDTH/2)) / (PADDLE_WIDTH/2);
    ballDirectionX = relativeHit * 2.0; 

    // 90 degree angle ajustment
    if(fabs(ballDirectionX)<0.3){
      ballDirectionX = (ballDirectionX<0)? -0.3 : 0.3;
    }

    // normalization
    float mag = sqrt(ballDirectionX*ballDirectionX + ballDirectionY*ballDirectionY);
    ballDirectionX/=mag;
    ballDirectionY/=mag;
  }

  // brick collisions
  for(int row=0; row<BRICK_ROWS; row++){
    for(int col=0; col<BRICK_COLS; col++){
      if(bricks[row][col]){
        int bx = col*BRICK_WIDTH;
        int by = BRICK_TOP_MARGIN + row*BRICK_HEIGHT;
        // bounding
        bool overlap = (ballX>=bx && ballX<=bx+BRICK_WIDTH &&
                        ballY>=by && ballY<=by+BRICK_HEIGHT);
        if(overlap){
          bricks[row][col] = false;
          tft.fillRect(bx, by, BRICK_WIDTH-2, BRICK_HEIGHT-2, TFT_BLACK);

          // change direction
          ballDirectionY = -ballDirectionY;

          score +=10;

          // score update
          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.setTextSize(2);
          tft.setCursor(5,5);
          tft.printf("Score: %d", score);

        digitalWrite(LED_G, HIGH);
        delay(20); 
        digitalWrite(LED_G, LOW);

          break; 
        }
      }
    }
  }

// game over 
  if(ballY>SCREEN_HEIGHT){
    breakoutGameOver();
  }
}

// update pallet 
void updatePaddleBreakout(){
  int xValue = analogRead(JOY_X_PIN);
  if(xValue<1000){
    paddleX -= 7; // paddleSpeed
  } else if(xValue>3000){
    paddleX += 7;
  }
// constrain
  paddleX = constrain(paddleX, 0, SCREEN_WIDTH-PADDLE_WIDTH);
}

// game over breakout
void breakoutGameOver(){
  if(breakoutGameOverCalled) return;
  breakoutGameOverCalled = true;

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(100,100);
  tft.println("Game Over!");
  tft.setCursor(100,140);
  tft.printf("Final Score: %d", score);

  delay(2000);

  int choice = postGameMenu();
  if(choice==0){
    breakoutGameOverCalled = false; // reset
    resetGameBreakout();
  } else {
    currentGame = -1;
  }
}

// victory?
void breakoutCheckVictory(){
  for(int row=0; row<BRICK_ROWS; row++){
    for(int col=0; col<BRICK_COLS; col++){
      if(bricks[row][col]){
        return; 
      }
    }
  }
  // no brick -> win
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(100,100);
  tft.println("You Won!");
  tft.setCursor(100,140);
  tft.printf("Final Score: %d", score);
  delay(2500);

  int choice = postGameMenu();
  if(choice==0){
    resetGameBreakout();
  } else {
    currentGame = -1;
  }
}


// Dino

//reset game at start 
void resetDinosaurGame(){
  dinoY          = GROUND_Y - DINO_HEIGHT;
  dinoVelocityY  = 0;
  isJumping      = false;
  numObstacles   = 0;
  obstacleSpeed  = 5;
  obstacleInterval = 2000;
  dinoScore      = 0;

  tft.fillScreen(TFT_BLACK);
}

//game over screen 
void dinosaurGameOver(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(100,100);
  tft.println("Game Over!");
  tft.setCursor(100,140);
  tft.printf("Final Score: %d", dinoScore);
  delay(2500);

  int choice = postGameMenu();
  if(choice==0){
    resetDinosaurGame();
  } else {
    currentGame = -1;
  }
}


void drawDino(){
  if(isDucking){
    // ducking animation
    int rad  = DINO_WIDTH/2;
    int cx   = dinoX + DINO_WIDTH/2;
    int cy   = dinoY + DINO_HEIGHT/2;
    tft.fillCircle(cx, cy, rad, TFT_GREEN);
  } else {
    // normal player
    tft.fillRect(dinoX, dinoY, DINO_WIDTH, DINO_HEIGHT, TFT_WHITE);
  }
}


void clearDino(){
  if(isDucking){
    int rad  = DINO_WIDTH/2;
    int cx   = dinoX + DINO_WIDTH/2;
    int cy   = dinoY + DINO_HEIGHT/2;
    tft.fillCircle(cx, cy, rad, TFT_BLACK);
  } else {
    tft.fillRect(dinoX, dinoY, DINO_WIDTH, DINO_HEIGHT, TFT_BLACK);
  }
}

// jump/duck logic
void updateDino() {
  
  int joyY = analogRead(JOY_Y_PIN);

  if (joyY < 1000 && !isJumping) {
    isJumping = true;
    dinoVelocityY = -JUMP_HEIGHT;
  } else if (joyY > 3000) {
    isDucking = true;
  } else {
    // Stare normală
    isDucking = false;
  }

  if (isJumping) {
    dinoY += dinoVelocityY;
    dinoVelocityY += GRAVITY;

    if (isDucking) {
      dinoVelocityY += DUCK_ACCELERATION;
    }

    if (dinoY >= GROUND_Y - DINO_HEIGHT) {
      dinoY = GROUND_Y - DINO_HEIGHT;
      isJumping = false;
      dinoVelocityY = 0;
    }
  }
}


// collisons 
bool checkCollision(){
  for(int i=0; i<numObstacles; i++){
    int ox = obstacles[i].x;
    int oy = obstacles[i].y;
    int ow = obstacles[i].width;
    int oh = obstacles[i].height;

    if(!isDucking){
      // bounding box
      bool overlap = (dinoX < ox+ow) && (dinoX+DINO_WIDTH>ox) &&
                     (dinoY < oy+oh) && (dinoY+DINO_HEIGHT>oy);
      if(overlap) return true;
    } else {
      // circle collisions
      int rad = DINO_WIDTH/2;
      int cx  = dinoX + DINO_WIDTH/2;
      int cy  = dinoY + DINO_HEIGHT/2;

      // closest point 
      int closestX = clamp(cx, ox, ox+ow);
      int closestY = clamp(cy, oy, oy+oh);

      int distX = cx - closestX;
      int distY = cy - closestY;
      int sqDist= distX*distX + distY*distY;
      if(sqDist <= rad*rad){
        return true;
      }
    }
  }
  return false;
}

// generate new obstacolses 
void addObstacle(){
  if(millis() - lastObstacleTime >= obstacleInterval){
    if(numObstacles<MAX_OBSTACLES){
      bool isDuckObstacle = random(0,2); 
      if(isDuckObstacle){
        obstacles[numObstacles] = {
          //ducking
          SCREEN_WIDTH,
          GROUND_Y - DINO_HEIGHT -48,
          20,
          50,
          obstacleColors[random(0,NUM_COLORS)]
        };
      } else {
        //normal
        obstacles[numObstacles] = {
          SCREEN_WIDTH,
          GROUND_Y -20,
          20,
          20,
          obstacleColors[random(0,NUM_COLORS)]
        };
      }
      numObstacles++;
    }
    lastObstacleTime = millis();
  }
}

// update obs 
void updateObstacles(){
  for(int i=0; i<numObstacles; i++){
    // delete old position
    tft.fillRect(obstacles[i].x, obstacles[i].y, obstacles[i].width, obstacles[i].height, TFT_BLACK);

    obstacles[i].x -= obstacleSpeed;

    // drawn new one
    tft.fillRect(obstacles[i].x, obstacles[i].y, obstacles[i].width, obstacles[i].height, obstacles[i].color);

    // if out of bound delete
    if(obstacles[i].x + obstacles[i].width <0){
      for(int j=i; j<numObstacles-1; j++){
        obstacles[j] = obstacles[j+1];
      }
      numObstacles--;
      i--;
    }
  }
}

// score
void updateScoreAndSpeed(){
  dinoScore++;
  if(dinoScore %100==0){
    obstacleSpeed++;
    obstacleInterval = max(500UL, obstacleInterval-100);
  }
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(5,5);
  tft.printf("Score: %d", dinoScore);
  drawTopMargin();
}


// Setup/Loop

void setup() {
  // tft
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  //led
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // joystick setup
  pinMode(JOY_SW_PIN, INPUT_PULLUP);

  // start the melody playback
  xTaskCreate(
    melodyTask,       // task function
    "Melody Task",    // task name
    2048,             // stack size
    NULL,             // parameters (none needed here)
    1,                // priority
    NULL              // task handle (not used)
  );

  // show menu when started 
  int sel = showMenu();
}


void loop() {
  // just show menu 
  if(currentGame == -1){
    currentGame = showMenu();

    if(currentGame == 0){
      // space invaders
      tft.fillScreen(TFT_BLACK);
      initializeEnemies();
      score = 0;
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(5,5);
      tft.printf("Score: %d", score);
      drawTopMargin();
      drawEnemies();

    } else if(currentGame == 1){
      // Breakout
      tft.fillScreen(TFT_BLACK);
      resetGameBreakout();

    } else if(currentGame == 2){
      // Dino
      tft.fillScreen(TFT_BLACK);
      resetDinosaurGame();
    }
  } 
  // SPACE INVADERS
  else if(currentGame == 0){
    // delete ship read joystick
    clearShip();
    int xVal = analogRead(JOY_X_PIN);
    if(xVal<1000){
      shipX -= shipSpeed;
    } else if(xVal>3000){
      shipX += shipSpeed;
    }
    shipX = constrain(shipX,0,SCREEN_WIDTH-SHIP_WIDTH);
    drawShip();

    // shoot
    if(!bulletActive && digitalRead(JOY_SW_PIN)==LOW){
      bulletActive = true;
      bulletX = shipX + SHIP_WIDTH/2 - BULLET_WIDTH/2;
      bulletY = shipY - BULLET_HEIGHT;
      digitalWrite(LED_G, HIGH); // bullet fired 
      delay(10);
      digitalWrite(LED_G, LOW);
    }

    // bullet travel  
    if(bulletActive){
      // delete old position
      tft.fillRect(bulletX, bulletY, BULLET_WIDTH, BULLET_HEIGHT, TFT_BLACK);
      bulletY -= bulletSpeed;
      // out of bounds 
      if(bulletY<31){
        bulletActive = false;
        
      } else {
        // redraw 
        tft.fillRect(bulletX, bulletY, BULLET_WIDTH, BULLET_HEIGHT, TFT_RED);
      }
    }

    // enemy bullet
    if(enemyBulletActive){
      tft.fillRect(enemyBulletX, enemyBulletY, BULLET_WIDTH, BULLET_HEIGHT, TFT_BLACK);
      enemyBulletY += enemyBulletSpeed;
      if(enemyBulletY>SCREEN_HEIGHT){
        enemyBulletActive = false;
      } else {
        tft.fillRect(enemyBulletX, enemyBulletY, BULLET_WIDTH, BULLET_HEIGHT, TFT_YELLOW);
      }
    }

    // checkings
    checkVictory();
    checkBulletCollision();
    checkEnemyBulletCollision();
    checkEnemiesReachedBottom();
    enemyShoot();

    // redraw enemies 
    clearEnemies();
    moveEnemies();
    drawEnemies();

    delay(50);
  }
  // BREAKOUT
  else if(currentGame == 1){
    // game over check 
    if(breakoutGameOverCalled){
      return;
    }

    // paddle draw 
    static int oldPaddleX = paddleX;
    if(paddleX != oldPaddleX){
      tft.fillRect(oldPaddleX, paddleY, PADDLE_WIDTH, PADDLE_HEIGHT, TFT_BLACK);
      oldPaddleX = paddleX;
    }
    // update paddle 
    updatePaddleBreakout();

    // ball delete/redraw 
    tft.fillCircle(ballX, ballY, BALL_SIZE/2, TFT_BLACK);
    moveBallBreakout();
    tft.fillCircle(ballX, ballY, BALL_SIZE/2, TFT_WHITE);

    // paddle draw 
    tft.fillRect(paddleX, paddleY, PADDLE_WIDTH, PADDLE_HEIGHT, TFT_WHITE);

    // brick draw 
    drawBricksBreakout();

    // game over?
    if(ballY>SCREEN_HEIGHT){
      breakoutGameOver();
      return;
    }

    delay(10);
  }
  // DINO
  else if(currentGame == 2){
    // delete dino :(
    clearDino();

    // joystick input
    int joyY = analogRead(JOY_X_PIN);
    if(joyY<1000 && !isJumping){
      // jump
      isJumping=true;
      dinoVelocityY = -JUMP_HEIGHT;
    } else if(joyY>3000){
      // duck
      isDucking=true;
    } else {
      isDucking=false;
    }

    // updates for dino 
    updateDino();
    drawDino();

    // obstacles 
    addObstacle();
    updateObstacles();

    // collisions
    if(checkCollision()){
      dinosaurGameOver();
      return;
    }

    // score
    updateScoreAndSpeed();

    delay(50);
  }
}
