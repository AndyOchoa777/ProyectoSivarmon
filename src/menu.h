#include "MenuUtils.h"

void mainPageLogo(){
    int rows, columns;
    //print the main page with the game name
    GetConsoleSize(rows, columns);
    PrintSivarMesagge(GameName);
    
    string message = "PRESS ANY KEY TO START";
    int messageX = max(0, (columns - (int)message.length()) / 2);
    int messageY = GameName.size()+3;
    
    vector<string> colores = {
        FG_RED, FG_YELLOW, FG_GREEN, FG_CYAN, FG_BLUE, FG_MAGENTA, FG_WHITE, FG_PINK
    };
    //the vector are the color avaliable for the printing
    int colorIndex = 0;
    
    cout << BG_BLACK << FG_BLACK << string((rows/2)+2, ' ') << RESET;
    cout << BG_BLACK << FG_BLUE << NEGRITA << "2025 TO->MATE INC" <<RESET << endl;
    while (!_kbhit()) {
        COORD coord;
        coord.X = messageX;
        coord.Y = messageY;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << colores[colorIndex % colores.size()] << FLICKERING << NEGRITA << message << RESET << flush;
        //print based on the color mod the size of the array
        colorIndex++;
        sleep_for(300ms);
    }
    getch(); 
}
    
 
void mostrarMenu(const vector<string>& MainMenu, int choice) {
    int rows, columns;
    GetConsoleSize(rows, columns);
    // print the main menu centerd
    int BoxWide = 80;
    int BoxHeight = MainMenu.size();

    int x = (columns - BoxWide) / 2;
    int y = (rows - BoxHeight) / 2;

    system("cls");

    for (int i = 0; i < y; ++i) cout << endl;

    for (int i = 0; i < MainMenu.size(); ++i) {
        string message = (i == choice ? "> " : "  ") + MainMenu[i];
        message += string(BoxWide - message.length(), ' ');

        cout << string(x, ' ');
        
        if (i == choice) {
            cout << BG_WHITE << FG_VIOLET << NEGRITA << message << RESET << endl;
        } else {
            cout << BG_WHITE << FG_BLACK << message << RESET << endl;
        }
    } // and show the background white while not selected 
}
