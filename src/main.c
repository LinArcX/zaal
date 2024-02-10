#include <curses.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32 // note the underscore: without it, it's not msdn official!
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

int main(int argc, char *argv[])
{
  int ch;

  filter();
  initscr();
  raw();				          // Line buffering disabled
  keypad(stdscr, TRUE);		// We get F1, F2 etc..
  noecho();			          // Don't echo() while we do getch
  printw("Type any character to see it in bold\n");
  ch = getch();			      // If raw() hadn't been called we have to press enter before it gets to the program

  // Without keypad enabled this will
  if(ch == KEY_F(1))		
  {
  	// Without noecho() some ugly escape charachters might have been printed on screen
    printw("F1 Key pressed");
  }
  else
  {	
    printw("The pressed key is ");
    attron(A_BOLD);
    printw("%c", ch);
    attroff(A_BOLD);
  }
  refresh();  // Print it on to the real screen
  getch();		// Wait for user input
  endwin();		// End curses mode
  
  return 0;
}
