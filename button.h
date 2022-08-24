#ifndef _BUTTON_H
#define _BUTTON_H 

class Button
{
public:
  int pino;
  bool change = false;

  Button(int pino)
  {
    this->pino = pino;
    pinMode(pino, INPUT);
  }

  bool pressed()
  {
    change = digitalRead(pino);
    return change;
  }

  bool just_pressed()
  {
    bool press = digitalRead(pino);
    if (press!= change)
    {
      change = pressed();
      if (change)
      {
        return true;
      }
    }
    return false;
  }

};

#endif