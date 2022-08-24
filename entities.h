#ifndef _ENTITIES_H
#define _ENTITIES_H 

//===================classes==============================================================================================
class Nave
{
public:
  int y;

  int energia;
  
  Nave(int y)
  {
    this->y = y;
    this->energia = 100;
  }

  void up()
  {
    y = 0;
  }

  void down()
  {
    y = 1;
  }

  void recharge()
  {
    energia = 100;
  }

  void process(bool btup, bool btdown, LiquidCrystal lcd)
  {
    energia--;

    if (btup)
    {
      up();
    }
    if (btdown)
    {
      down();
    }
    render(lcd);
  }

  void restart()
  {
    recharge();
  }

private:
  void render(LiquidCrystal lcd)
  {
    lcd.setCursor(0, y);
    lcd.write(1);
  }
};
///////////////////////////////////////////////////////
class Asteroide
{
public:
  int x, y;
  int sprite = 3, timer = 0;
  bool dead = false;
  Asteroide(int y)
  {
    this->x = 16;
    this->y = y;
  }

  void forward()
  {
    x--;
    if (x < 0)
    {
      x = 16;
      y = random(2);
    }
  }

  void process(LiquidCrystal lcd)
  {
    if (!dead)
    {
      forward();
    }
    else
    {
      timer++;
      if (timer > 4)
      {
        timer = 0;
        dead = false;
        x = 16;
        y = random(2);
        sprite = 3;
      }
    }
    if (x < 14)
    {
      render(lcd);
    }
  }

  void explode()
  {
    dead = true;
    sprite = 5;
  }

private:
  void render(LiquidCrystal lcd)
  {
    lcd.setCursor(x,y);
    lcd.write(sprite);
  }
};
///////////////////////////////////////////////////////////
class Cell
{
public:
  int x, y;

  Cell(int y)
  {
    this->y = y;
    this->x = 16;
  }

  void forward()
  {
    x--;
    if (x < 0)
    {
      restart();
    }
  }

  void process(LiquidCrystal lcd)
  {
    forward();
    if (x < 14)
    {
      render(lcd);
    }
  }

  void restart()
  {
    x = random(45,90);
    y = random(2);
  }

private:
  void render(LiquidCrystal lcd)
  {
    lcd.setCursor(x,y);
    lcd.write(4);
  }
};
////////////////////////////////////////////////////////
class Bala
{
public:
  int x, y;
  bool runn;

  // the constructor
  Bala(int y)
  {
    this->y = y;
    this->x = -3;
    runn = false;
  }

  // goes forward
  void forward()
  {
    x++;
    if (x > 15)
    {
      wait();
    }
  }

  // the fuction called to shoot
  bool call(int y)
  {
    if (!runn)
    {
      runn = true;
      x = 1;
      this->y = y;
      return true;
    }
    return false;
  }

  // the function to put the shot in wait
  void wait()
  {
    runn = false;
    x = -3;
  }

  void process(LiquidCrystal lcd)
  {
    if (runn)
    {
      forward();
      if (x < 14)
      {
        render(lcd);
      } 
    } 
  }

private:
  void render(LiquidCrystal lcd)
  {
    // position the cursor on the coordinates of the entity and renders it
    lcd.setCursor(x, y);
    lcd.write(2);
  }
};

#endif
//========================================================================================================================