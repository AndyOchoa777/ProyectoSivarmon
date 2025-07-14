#include "header.h"
using namespace std;

map<char, int> ColorID;


vector<string> MainMenu = {
    "Start game",
    "About",
    "Credits",
    "Leave"
};


void FillColor(){
    ColorID['@'] = 15;     
    ColorID['a'] = 200;    
    ColorID['b'] = 91;    
    ColorID['c'] = 129;   
    ColorID['d'] = 45;     
    ColorID['e'] = 39;     
    ColorID['f'] = 81;     
    ColorID['g'] = 78;     
    ColorID['h'] = 121;   
    ColorID['i'] = 190;    
    ColorID['j'] = 226;    
    ColorID['k'] = 214;    
    ColorID['l'] = 208;    
    ColorID['m'] = 202;    
    ColorID['n'] = 196;    
    ColorID['o'] = 96;    
    ColorID['p'] = 28;     
    ColorID['q'] = 106;
    ColorID['r'] = 52;
    ColorID['s'] = 240;
    ColorID['t'] = 248;
    ColorID[' '] = 232;
}

vector<string> SivarmonMap={
    "                              @@@@                                                                       ",    
    "                        @@@@@@@aa@@@@@    @@@                                                           ",
    "                        @aaaaaaaaaa@@  @@@@@g@                                                           ",
    "                       @@@aaaaaaaaaaa@@gggggg@@@                                                         ",
    "                         @@aaaaaaaaaa@ggggggggg@                                                         ",
    "                         @@@aaaaaa@@ggggggggggggg@                                                       ",
    "                    @@@@@aaaaaaaaa@@gggggggggggggg@@@@@                                                  ",
    "                  @@aaaaaaaaaaa@@ggggggggggggggggggggg@@                                                 ",
    "                 @@aaaaaaaaaaa@@ggggggggggggggggggggggg@@@@@                                             ",
    "          @@@@@@@@aaaaaaaaaaa@@@@@@@@@@@@@@@@@@@ggggggggggg@@@                                           ",
    "         @@bbbbbbb@@aaaaaaaaaaaa@@ddd@eeeee@hhh@@ggggggggggggg@@@@@                                       ",
    "      @@@bbbbbbbbb@aaaaaaaaaaaa@ddddd@eee@@hhhh@@ggggg@@@@@@@@iiii@@@@          @@@@@@@@                 ",
    "     @bbbbbbbbbbb@@aaaaaaaaaa@@ddddddd@@e@@hhhhhh@@@@@iiiiiiiiiiiiiii@        @@@@mmmmm@@       @@@      ",
    "  @@@bbbbbbbbbb@@ccc@aaaaaaaa@dddddddd@eee@@hhhhh@iiiiiiiiiiiiiiiiiii@ @@@@@@@k@mmmmmmmmm@@@@@@@@n@@     ",
    " @@bbbbbbbbbbbb@ccccc@@@@@aaa@ddddddd@@ee@@@@hhhh@@@iiiiiiiiiiiiiiiii@@@kkkkkkk@mmmmmmmmmmmm@nnnnnnn@@@  ",
    " @bbbbbbbbbbbbb@cccccccccc@@@ddddddddd@eeeeee@@hhhhh@@@ii@@@@@@@@iiii@kkkkkkkkk@@mmmmmmmmmmmm@nnnnnnnnn@  ",
    " @@bbbbbbbbbbb@@cccccccccccc@@ddddddd@@eeeeeeee@hhhhhhh@@jjjjjjj@@@@kkkkkkkkkkkk@mmmmmmmmm@@nnnnnnnnnn@@  ",
    "   @@@@bb@@@@@@ccccccccccc@@ddddddddd@eeeeee@@@@hhhhh@@jjjjjjjjjjjjj@@@@kkkkkk@@mmmmmmmmmmmm@nnnnnnn@@   ",
    "       @@@ccccccccccccccc@@ddddddddddd@@eeee@fff@@@@@jjjjjjjjjjjjj@@ll@@@@kkkk@@@mmmmmmmmm@@nnnnnnn@    ",
    "          @@@cccccccccccc@dddddddddddd@@e@@@@fffffff@@jjjjjjjjjjjj@@llllll@kkkkkk@@@@mmmmm@@nnnnnnnn@    ",
    "             @ccccccccc@@ddddddddddddd@@e@@fffffffffff@@jjjjjjj@@@lllllll@@kkkkkkkkk@@@@@@@nnnnnnnn@     ",
    "             @@@@@@@@@@@ddddddddddddd@eee@fffffffffffff@jjjj@@lllllllllll@kkkkkkkkkkkkkk@nnnnnnnn@@@   ",
    "                       @@@@@@@@@@@@@@@e@@@@ffffffffffff@jjjjj@@lllllllllll@kkkkkkkkkkkkk@@nnnnnnnnnn@@   ",
    "                                     @@@@ffffffffffffff@@jjjj@lllllllllll@@kkkkkkkkkkkkk@nnnnnnn@nn@@@   ",
    "                                        @@@@fffffffffffff@j@@lllllllllllll@kkkkkkkkkkkkkk@nnnnn@@@@@     ",
    "                                             @@@@fffffff@@j@llllllllllllll@@kkkkkkkkkkkk@nnnnnn@         ",
    "                                                 @@@@fff@j@@lllllllllllllllll@@@@kkkkkkk@nnnnnnn@@@@@    ",
    "                                                     @@@@  @@@@@lllllllllll@@@ @@kkkkkk@nnnnnnnnn@      ",
    "                                                              @@@@@@@@@lllllllll@@@@kkk@nnnnnnn@@@@@@    ",
    "                                                                 @@@@@@@@@@@@@@@@  @@@@@@@nnn@@@        ",
    "                                                                                         @@@@@           "
                                                                                                             
};

vector<string> GameName={
    // "                                                                                                                   ",
    "                                                                                                                   ",
    "                               @@@ @       @@              @@@@@     @@@@       @                                  ",
    "                 @@@    @@@@     @@@        @@@@       @@     @@@@    @@@@   @@@@@        @@@@                     ",
    "      @@@@  @    @@@@     @@@    @@          @@@@      @@@    @@@     @@@@  @@@@ @    @     @@@@     @@@@   @@     ",
    "    @   @@@@@    @@@@     @@@@    @       @   @@@@     @@@@  @@      @ @@@@@@@@      @@      @@@@     @@@@  @@@    ",
    "    @@@           @@@      @@@@  @       @@   @@@@     @@@@   @@     @    @@    @   @@@@      @@@      @@@@  @@    ",
    "     @@@@@@@@@    @@@       @@@@        @@@@   @@@@    @@@@  @@@@    @@@      @@@    @@@@      @@   @   @@@@ @@    ",
    "           @@@@   @@@@         @@       @@@@    @@@@@  @@@@   @@@@@ @@@@     @@@@    @@@@@     @    @@  @@@@       ",
    "     @@@@@       @@@@                                                         @@      @@@@@        @@@   @@@@      ",
    "     @@@@@@@@@                                                                                     @@@      @      ",
    "                                                                                                                   "
};

map<int, int> ColorByIndex = {
    {0, 91}, {1, 200}, {2, 129}, {3, 78},
    {4, 45}, {5, 39}, {6, 121}, {7, 81},
    {8, 190}, {9, 226}, {10, 208}, {11, 214},
    {12, 202}, {13, 196}
};

vector<string> SivarMenu = {
    "1. Ahuchapan             ",
    "2. Santa Soul            ",
    "3. Sonsonate             ",
    "4. Chalate               ",
    "5. La Libertad           ",
    "6. San Salvador          ",
    "7. Cuscatlan             ",
    "8. La Paz                ",
    "9. Not Found             ",
    "10. San Vicente          ",
    "11. Usulutan             ",
    "12. San Miguel           ",
    "13. Mora (not the singer)",
    "14. La Union             "
};


void PrintSivarMesagge(const vector<string>& map) {
    int filas, columnas;
    GetConsoleSize(filas, columnas);

    for (const string &line : map) {
        int padding = (columnas - (int)line.length()) / 2;
        if (padding < 0) padding = 0;

        cout << BG_BLACK << FG_BLACK << string(padding, ' ');

        for (char ch : line) {
            int color = ColorID.count(ch) ? ColorID[ch] : 232;
            cout << "\033[48;5;" << ColorID[ch] << "m "; 
        }

        cout << RESET << endl;
    }
    cout<<endl;
}

void PrintSivarMapLeft() {
    COORD cursorPos;
    cursorPos.X = 0;
    cursorPos.Y = (int)GameName.size() + 1;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);

    for (const string& line : SivarmonMap) {
        for (char ch : line) {
            if (ColorID.count(ch))
                cout << "\033[48;5;" << ColorID[ch] << "m " << RESET;
            else
                cout << BG_BLACK << FG_BLACK << " " << RESET;
        }
        cout << '\n';
    }
}

void PrintMenuRight(int selected, int mapHeight) {
    int rows, cols;
    GetConsoleSize(rows, cols);

    int rightPadding = SivarmonMap[0].size() + 10;
   
    COORD cursorPos;

    for (int i = 0; i < (int)SivarMenu.size(); ++i) {
        cursorPos.X = rightPadding;
        cursorPos.Y = (i + 1) + GameName.size() + 3;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);

        string colorCode = "\033[48;5;" + to_string(ColorByIndex[i]) + "m";
        string colorFont = "\033[38;5;" + to_string(ColorByIndex[i]) + "m";
        if (i == selected)
            cout << BG_BLACK << colorFont << NEGRITA << " > " << SivarMenu[i] << " < " << RESET;
        else
            cout << colorCode << "   " << FG_BLACK << SivarMenu[i] << "   " << RESET;
    }

    cursorPos.X = rightPadding;
    cursorPos.Y = (int)SivarMenu.size() + GameName.size() + 22;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
    cout << RESET << endl;
}

vector<string> LoadingClock={
    "rrrrrrrrrrrrr",
    "sttttttttttts",
    "stcccccccccts",
    " sscccccccss ",   
    "   sscccss   ", 
    "     scs     ",
    "   sstctss   ",   
    " sstttctttss ",
    "sttccccccctts",
    "scccccccccccs",
    "rrrrrrrrrrrrr",                             
};
