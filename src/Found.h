#include "header.h"

vector<string> FoundMessage = {
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                      @@@@@      @@@@   @@@@    @@@@@  @@@     @@@@@            ",
    "       @@@@@@@@     @@@@@@@@@    @@@@   @@@@    @@@@@  @@@     @@@@@@@@@        ",
    "       @@@@@@@@    @@@@  @@@@    @@@@   @@@@    @@@@@  @@@     @@@@ @@@@@       ",
    "       @@@@        @@@@   @@@@   @@@@   @@@@    @@@@@  @@@     @@@@  @@@@       ",
    "       @@@@        @@@@   @@@@   @@@@   @@@@    @@@@@  @@@     @@@@  @@@@       ",
    "       @@@@@@@@    @@@@   @@@@   @@@@   @@@@    @@@@@@@@@@     @@@@  @@@@       ",
    "       @@@@@@@@     @@@   @@@@   @@@@   @@@@    @@@@ @@@@@    @@@@   @@@@       ",
    "        @@@         @@@   @@@@   @@@@   @@@@    @@@@ @@@@@    @@@@   @@@@       ",
    "        @@@@        @@@@  @@@@   @@@@   @@@@    @@@@ @@@@@    @@@@   @@@        ",
    "        @@@@        @@@@  @@@@    @@@@ @@@@     @@@@ @@@@@    @@@@  @@@@        ",
    "        @@@@         @@@@@@@@     @@@@@@@@      @@@  @@@@    @@@@@@@@@@         ",
    "        @@@@          @@@@@          @@@       @@@@  @@@@    @@@@@@@@@          "
};

map<char, int> FoundIDColor = {
    {'@', 196},
    {' ', 232}
};

void FoundBackground() {
    cout << BG_BLACK;
    cout << "\033[2J";
    cout << "\033[H";        
}

void printFoundMessage(){
    //We print the text center with the colors assigned on the map
    SetConsoleOutputCP(CP_UTF8);
    int rows, cols;
    GetConsoleSize(rows, cols);
    //we do it for each line, and we print the black background if is not a character assigned
    for (const string &line : FoundMessage) {
        int padding = (cols - (int)line.length()) / 2;
        if (padding < 0) padding = 0;
        cout << BG_BLACK << string(padding, ' ');
        cout << RESET;
        for (char ch : line) {
            int color = FoundIDColor.count(ch) ? FoundIDColor[ch] : 232;
            cout << "\033[48;5;" << FoundIDColor[ch] << "m "; 
        }
        cout << RESET << endl;
    }
    cout<<endl;
}

void PrintFoundSprite(){
    int rows, cols;
    GetConsoleSize(rows, cols);
    SetConsoleOutputCP(CP_UTF8);
    //Set the rows and columns 
    //Set the sprite of the missing character
    vector<string> cabanas = {
        "▒▒▓▓▓▓    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      ",
        "▒▒▒▒▓▓▓▓    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    ",
        "    ▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    ",
        " ▒▒▒▒▒▒▒█████▓▓▓▓▓▓█▓▓▓▓▓▓▓▓▓▓▓▓    ",
        "▒▒▒▒   ▓▓▓▓▓▓▓▓▓▓▓▓▓████▓▓▓▓████    ",
        "     ▓▓▓▓▓▓▓▓▓▓▓░░░░████░░░░████    ",
        "    █▓▓▓▓▓▓▓▓▓▓▓░░░░████░░░░████    ",
        "        ▓▓▓▓░░░░░░░░░░░░░░░░░░░░    ",
        "        ▓▓▓▓░░░░░░░░░░░░░░░░░░░░    ",
        "    ░░░░▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░    ",
        "    ░░░░▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░    ",
        "        ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░    ",
        "        ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░",
        "        ░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
        "        ░░░░░░░░░░░░░░░░░░░░░░░░    ",
        "        ░░░░░░░░░░░░░░░░░░░░░░░░    ",
        "        ░░░░                ░░░░    "
    };
    int spriteHeight = cabanas.size();
    int startRow = FoundMessage.size() + 2;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //we print it on the center of the console
    for (int i = 0; i < spriteHeight; i++) {
        const string& line = cabanas[i];
        int padding = 60;
        if (padding < 0) padding = 0;

        COORD pos = { (SHORT)padding, (SHORT)(startRow + i) };
        SetConsoleCursorPosition(hConsole, pos);
        for (char ch : line) {
            if (ch != ' ') {
                cout << ch;
            } else {
                cout << BG_BLACK << " "; 
                //if it is an empty space we print the black backgrounf again
            }
        }
    }
}

void FOUND_ED(){
    system("cls");
    FoundBackground();
    printFoundMessage();
    PrintFoundSprite();
    //call all the funtions to set the background, the text and the sprite
}
