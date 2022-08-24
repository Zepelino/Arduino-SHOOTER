#include <LiquidCrystal.h>
#include <PCM.h>

#include "sprites.h"
#include "entities.h"
#include "button.h"
#include "sounds.h"


int musicState = 0;

LiquidCrystal lcd(7,6,5,4,3,2); // sets up the lcd display correctly

int vel = 100;
int pontos = 0;
int gameState = 0;// 0- menu; 1 - game; 2 - game over

int menuTime = 0;

//========================================================================================================================

// constructs all the entinties in the game
// due to the limited ram memory in the arduino, it's necessary to do a technique called pooling,
// that is, using a limited number of entities and put them into a "wait queue" to be re-used instead of deleting it
Nave player(1); 
Asteroide ast(0);
Cell pilha(1);
Bala tir(1);

// constructs all the buttons in the game
Button btup(8);
Button btdown(9);
Button btaction(10);

void setup() {

  // creates the special characters, the sprites, in the memory of the lcd display
  lcd.createChar(1, nave);
  lcd.createChar(2, bala);
  lcd.createChar(3, asteroide);
  lcd.createChar(4, cell);
  lcd.createChar(5, explosion);

  // initializes the lcd and the sets game state
  lcd.begin(16,2);
  lcd.clear();
  gameState = 0;

  //plays the """""music"""""
  startPlayback(sample, sizeof(sample));
}

void loop() 
{
  delay(vel); // apllies a fixed frame rate to the game
  
  

  // does all the in-game actions
  if (gameState == 1)
  {
    // clears the lcd
    lcd.clear();

    // calls all the entities process functions
    player.process(btup.pressed(), btdown.pressed(), lcd);
    tir.process(lcd);
    ast.process(lcd);
    pilha.process(lcd);

    // checks for pilha collision with player
    if (pilha.x == 0 && pilha.y == player.y)
    {
      pilha.restart();
      player.recharge();
      point(10);
      startPlayback(pilhaSound, sizeof(pilhaSound));
    }

    // checks for button pressed to shoot 
    if (btaction.just_pressed())
    {
      if (tir.call(player.y))
      {
        startPlayback(laserSound, sizeof(laserSound));
      }
    }

    // checks for collision with tir and ast, the shot and the asteroid
    if ((tir.x == ast.x || tir.x+1 == ast.x) && tir.y == ast.y)
    {
      point(2); 
      ast.explode();
      tir.wait();
    }
  
    // conditionals for game over: collision with asteroid or energy end
    if ((ast.x == 0 && ast.y == player.y) || player.energia < 0)
    {
      gameOver();
      return;
    }

    // renders the points and the remaining energy in the screen
    lcd.setCursor(13,0);
    lcd.print(pontos);
    lcd.setCursor(13,1);
    lcd.print(player.energia);
  }
  else if (gameState == 2)
  {
    // renders the game over screen
    lcd.setCursor(0, 0);
    lcd.print("SUCUMBIU!");
    lcd.setCursor(0, 1);
    lcd.print("Pontos: ");
    lcd.print(pontos);
    
    // checks for the button to restart the game
    if (btaction.just_pressed())
    {
      restart();
    }
  }
  else
  {
    // renders the main menu screen
    lcd.setCursor(4, 0);
    lcd.print("Arduino");
    lcd.setCursor(3, 1);
    lcd.print("<SHOOTER>");

    // controls the music
    musicState += vel;
    if (musicState > 1260)
    {
      musicState = 0;
      startPlayback(sample, sizeof(sample));
    }

    menuTime++;
    if (menuTime == 5 || menuTime == 8)
    {
      // blinks the display
      lcd.noDisplay();
      delay(100);
      lcd.display();
    }
    if (menuTime > 20)
    {
      menuTime = 0;
    }
    
    // checks for the action button press and changes de game state to indeed play de game
    if (btaction.just_pressed())
    {
      gameState = 1;
    }
  }
}

void point(int pts)
{
  pontos += pts;
}

void gameOver()
{
  gameState = 2;
  musicState = 1260;
  lcd.clear();
  startPlayback(explosionSound, sizeof(explosionSound));
}

void restart()
{
  // resets all the variable to the initial value
  gameState = 0;
  ast.x = 20;
  vel = 100;
  player.restart();
  pilha.restart();
  tir.wait();
  pontos = 0;
  lcd.clear();
}
