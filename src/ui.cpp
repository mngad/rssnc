#include <stdio.h>
#include <ncurses.h>
#include "dlxml.h"
#include "feed.h"
#include "Item.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
std::vector<Feed> feedVector;

void printFeed(WINDOW *childwin, int feedNum){

	box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 4, feedVector[feedNum].GetName().c_str());
    int count = 2;
    for(Item item : feedVector[feedNum].GetItemArray()){

    	mvwaddstr(childwin, count, 2, item.GetTitle().c_str());
    	mvwaddstr(childwin, count+1, 2, item.GetUrl().c_str());
    	mvwaddstr(childwin, count+2, 2, item.GetDate().c_str());

    	//mvwaddstr(childwin, count + 1, 2, item.GetDescr().c_str());
    	count += 4;
    }


}

int main()
{
	Dlxml dlxml;
	feedVector = dlxml.init();
	//std::vector<Feed> fe =  dlxml.getFeedVec();


    WINDOW * mainwin, * childwin;
    std::string      ch;

    if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }
    

    int      width = COLS -2, height = LINES -2;
    int      rows  = LINES, cols   = COLS;
    int      x = (cols - width)  / 2;
    int      y = (rows - height) / 2;


    /*  Switch of echoing and enable keypad (for arrow keys)  */

    noecho();
    keypad(mainwin, TRUE);


    /*  Make our child window, and add
	a border and some text to it.   */

	
	childwin = subwin(mainwin, height, width, y, x);
    int feednum = 0;
	printFeed(childwin, feednum);
    refresh();

	//vwaddstr(my_win,startx, starty, "feedVector[0].GetName().c_str()");
	//addstr(feedVector[0].GetName().c_str());
    ch = " ";
    while(ch != "q"){
    	ch = getch();

		if(ch == "n" && (feednum + 1)<=feedVector.size()-1){
			feednum++;

		}
		if(ch=="p" && (feednum-1)>=0){
			feednum--;
			
		}
		
	   /*  Clean up after ourselves  */
		delwin(childwin);
		childwin = subwin(mainwin, height, width, y, x);
		printFeed(childwin, feednum);
    	refresh();

    }

    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
	}