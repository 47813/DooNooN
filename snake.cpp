#include <iostream>
#include <ncurses.h>
#include <vector>

using namespace std;

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    if (has_colors() == FALSE) {
        endwin();
        cout << "Your terminal does not support color" << endl;
        return 1;
    }

    start_color();
    // Define color pairs
    init_pair(1, COLOR_BLACK, COLOR_WHITE);   // Wall color: white background, black text
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);  // Corner color: yellow background, black text
    init_pair(3, COLOR_WHITE, COLOR_MAGENTA); // Snake head color: purple background, white text
    init_pair(4, COLOR_WHITE, COLOR_BLUE);    // Snake body color: blue background, white text

    const int ROWS = 21;
    const int COLS = 21;

    vector<vector<int>> array(ROWS, vector<int>(COLS, 0));

    // Set edges to 1 (representing walls)
    for (int i = 0; i < ROWS; i++) {
        array[i][0] = 1;
        array[i][COLS - 1] = 1;
    }

    for (int j = 0; j < COLS; j++) {
        array[0][j] = 1;
        array[ROWS - 1][j] = 1;
    }

    // Set corners to 2
    array[0][0] = 2;
    array[0][COLS - 1] = 2;
    array[ROWS - 1][0] = 2;
    array[ROWS - 1][COLS - 1] = 2;

    // Add walls that meet each other, excluding the top side of the inner box
    // Vertical walls
    for (int i = 6; i <= 15; i++) {
        array[i][5] = 1;
        array[i][15] = 1;
    }

    // Horizontal walls
    for (int j = 5; j <= 15; j++) {
        array[15][j] = 1;
    }

    // Set snake body parts
    array[10][10] = 3; // Snake head
    array[10][9] = 4;  // Snake body
    array[10][8] = 4;  // Snake body

    // Print the array using ncurses
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            switch (array[i][j]) {
                case 1:
                    attron(COLOR_PAIR(1));
                    mvprintw(i, j, " ");
                    attroff(COLOR_PAIR(1));
                    break;
                case 2:
                    attron(COLOR_PAIR(2));
                    mvprintw(i, j, " ");
                    attroff(COLOR_PAIR(2));
                    break;
                case 3:
                    attron(COLOR_PAIR(3));
                    mvprintw(i, j, " ");
                    attroff(COLOR_PAIR(3));
                    break;
                case 4:
                    attron(COLOR_PAIR(4));
                    mvprintw(i, j, " ");
                    attroff(COLOR_PAIR(4));
                    break;
                default:
                    mvprintw(i, j, " ");
                    break;
            }
        }
    }

    refresh();
    getch();
    endwin();

    return 0;
}
