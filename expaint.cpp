// paint.cpp
//
// this program allows the user to "paint" using the mouse
// the user can change the pen color and its thickness (1-9)
// thickness of 1 is a point; 2-9 is a circle of that radius
// (note that the points drawn are not connected, and how far 
// they're separated is affected by how fast you move the mouse;
//   if you want to connect the points, it's an easy fix where 
//   you'd use gfx_line to connect each point with the previous one;
//   similar concept if you want to connect the circles (2-9) )
//
// press r, g, b, w, y, c, m to change the pen color (see below)
// press 1 - 9 to change the pen thickness
// press the ESC key to clear the screen

#include "gfx3.h"

void showmenu();

int main()
{
  char c;         // identify which mouse button or which key is used
  int event;      // identify which event is taking place
  int thick = 1;  // initial pen thickness 
  bool isclicked = false;  // flag for mouse event

  gfx_open(800, 600, "My Paint Window"); 
  gfx_clear();
  gfx_color(255,255,255);   // start with color white

  gfx_changefont((char *) "6x10");
  gfx_changecursor(XC_pencil);

  while(true) { 
    event = gfx_event_waiting();
    if (event != 0) { 
      showmenu();
      c = gfx_wait();

      // clear the window when ESC is hit
      if (c == 27) gfx_clear();

      // mouse click or release 
      if (c == 1 || c == 2 || c == 3) { 
        if (event == 3) isclicked = true;
        else if (event == 4) isclicked = false;
      }

      // mouse motion
      if (event == 5) {
        if (isclicked) {  // paint if mouse is pressed down
          if (thick == 1) gfx_point(gfx_xpos(), gfx_ypos());
          else gfx_fill_circle(gfx_xpos(), gfx_ypos(), thick);
        }
      }

      // change the pen's thickness 
      if (c >= '1' && c <= '9') thick = c - '0';

      // change the pen's color
      if (c == 'r') gfx_color(255,0,0);     // red
      if (c == 'g') gfx_color(0,255,0);     // green
      if (c == 'b') gfx_color(0,0,255);     // blue
      if (c == 'w') gfx_color(255,255,255); // white
      if (c == 'y') gfx_color(255,255,0);   // yellow
      if (c == 'c') gfx_color(0,255,255);   // cyan
      if (c == 'm') gfx_color(255,0,255);   // magenta

      // exit the loop
      if (c == 'q')  break;
    }

    gfx_flush();
  }

  return 0;
}

void showmenu()
{
  gfx_text(20, 30, "r: red  g: green  b: blue  w: white");
  gfx_text(20, 40, "y: yellow  c: cyan  m: magenta");
  gfx_text(20, 50, "1-9: pen thickness  q: quit");
  gfx_text(20, 60, "ESC: clear screen");
}

