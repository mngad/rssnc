#include <stdio.h>
#include <ncurses.h>
#include "dlxml.h"
#include "feed.h"
#include "Item.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main()
{
	Dlxml dlxml;
	std::vector<Feed> feedVector = dlxml.init();
	//std::vector<Feed> fe =  dlxml.getFeedVec();


    WINDOW * mainwin, * childwin;
    int      ch;

    if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }
    

    int      width = 50, height = 7;
    int      rows  = LINES, cols   = COLS;
    int      x = (cols - width)  / 2;
    int      y = (rows - height) / 2;


    /*  Switch of echoing and enable keypad (for arrow keys)  */

    noecho();
    keypad(mainwin, TRUE);


    /*  Make our child window, and add
	a border and some text to it.   */

	
	childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 4, feedVector[0].GetName().c_str());
    mvwaddstr(childwin, 2, 4, feedVector[0].GetItem(2).GetTitle().c_str());


    refresh();

	//vwaddstr(my_win,startx, starty, "feedVector[0].GetName().c_str()");
	//addstr(feedVector[0].GetName().c_str());
    ch = getch();
	   /*  Clean up after ourselves  */

    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
	}