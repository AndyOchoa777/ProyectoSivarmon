#include "header.h"

void GetConsoleSize(int &rows, int &columns) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void PrintCentered(const vector<string>& content) {
    int rows, columns;
    GetConsoleSize(rows, columns); 

    for (const string &line : content) {
        int padding = (columns - (int)line.length()) / 2;
        if (padding < 0) padding = 0;

        cout << string(padding, ' ') << line << endl;
    }
}
