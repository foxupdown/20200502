#ifndef _screen
#define _screen
#include <iostream>
#include <ncurses.h>
#include "LivingArea.h"
#include "Snake.h"
class Screen
{
  public:
         Screen();
         Screen(WINDOW *pwin);
         int refresh();
         void draw();
  private:
         Snake snake;
         WINDOW *win;
          
};
#endif
