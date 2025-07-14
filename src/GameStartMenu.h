#include "menu.h"
#include "utils.cpp"
int SelecterCharacter = 0;

void StartGameMenu(){
    //print menu after clicking on start game
    system("cls");
    PrintSivarMesagge(GameName); // print the game name
    int rows, cols;
    GetConsoleSize(rows, cols);

    string CharElection = "CHOOSE YOUR CHARACTER";

    COORD cursorPos;
    cursorPos.X = (cols - CharElection.size()) / 2;
    cursorPos.Y = (int)GameName.size();
    //print after the game name  print choose you character
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
    cout << FLICKERING << NEGRITA << BG_BLACK << FG_WHITE  << CharElection << RESET << flush;
    cout<<endl;
    //all centered using the header definitions
}

void NotFoundMessage(){
    int col, row;
    GetConsoleSize(row, col);
    //in the case cabanas is selected show a message of not found character since it cannot be picked
    string ErrorMessage="THE CURRENT CHARACTER CANNOT BE SELECTED O IS NOT FOUND, PLEASE CHOOSE ANOTHER ONE";
    cout<<string((col-ErrorMessage.size())/2, ' ')<< NEGRITA << FG_RED << ErrorMessage << RESET << endl;
    sleep_for(4s);
    system("cls");
}

void RunInteractiveMenu() {
    BACK_BLACK;
    StartGameMenu();
    PrintSivarMapLeft();
    PrintMenuRight(SelecterCharacter, (int)SivarmonMap.size());
    //Run all previos funtions and show the sivamon map
    while (true) { //a while to show the character options menu
        if (_kbhit()) {
            int key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 72) SelecterCharacter = (SelecterCharacter - 1 + (int)SivarMenu.size()) % SivarMenu.size(); // ARRIBA
                if (key == 80) SelecterCharacter = (SelecterCharacter + 1) % SivarMenu.size(); // ABAJO
            } else if (key == 13) {
                if (SelecterCharacter == 8) {
                    StartGameMenu(); 
                    NotFoundMessage();
                    StartGameMenu(); 
                    PrintSivarMapLeft();
                    PrintMenuRight(SelecterCharacter, (int)SivarmonMap.size());
                    continue;
                }
                SelecterCharacter++;
                return;
            }
            PrintMenuRight(SelecterCharacter, (int)SivarmonMap.size());
        }
    }
    SelecterCharacter++;
    //change selected to indexed-1 to make an easy access on the files
}

void RunCharacterMenu(){
    system("cls");
    FillColor();
    int col, row, Id=0;
    GetConsoleSize(row, col);
    //print a sand clock as waiting screen
    for(int i=0;i<(row/2)-LoadingClock.size();i++) cout<<'\n';
    PrintSivarMesagge(LoadingClock);
    vector<string> GameStatus={"GAME STARTING", "LOADING"};
    for(int i=0;i<6;i++){ 
        Id^=1; //switch between 0 and 1 for printing on the game status index
        cout << '\r' << BG_BLACK << FG_BLACK << string(col, ' ') << '\r'; 
        cout << string((col - GameStatus[Id].size()) / 2, ' ') << FG_WHITE << GameStatus[Id] << RESET << flush; //and print centered cleaning for the enxt lines

        sleep_for(1s);
        
    }
    StartGameMenu(); //run the game start
    RunInteractiveMenu(); //run the iterative menu
    // cout<<"Aqui si llega\n";
    sleep_for(600ms);
    // system("cls");
}
