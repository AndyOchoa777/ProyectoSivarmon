#include "header.h"

string GenerateHPBar(int currentHP, int maxHP) {
    SetConsoleOutputCP(CP_UTF8);
    //Set the health bar measures
    int barWidth = 20;
    float ratio = static_cast<float>(currentHP) / maxHP;
    int filled = min(static_cast<int>(ratio * barWidth), barWidth);
    int empty = barWidth - filled;
    
    //Set an empty string as a health bar
    string bar = "";
    char fullChar = (ratio <= 0.3f) ? '*' : ' ';
    //Fill the health bar to the current HP 
    for (int i = 0; i < filled; i++) {
        bar += fullChar;
    }
    //Fill the rest
    for (int i = 0; i < empty; i++) {
        bar += ".";
    }
    return bar; //Return the complete health bar
}

void PrintLifeBar(int HP, int maxHP) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)1, (SHORT)5 });
    //Set the position where the health life is going to be printed

    string hpBar = GenerateHPBar(HP, maxHP);
    string hpColor = (HP > maxHP) ? FG_VIOLET : (HP < maxHP) ? FG_RED : FG_BLACK;
    
    //First print the beging
    cout << NEGRITA << BG_WHITE << FG_ORANGE << " HP: " << RESET;
    cout << NEGRITA << BG_WHITE << FG_BLACK << "[" << RESET;
    
    if(HP>maxHP){
        cout << BG_MAGENTA << FG_MAGENTA << string(20, ' ') << RESET;
    }
    else{
        //Print the health bar
        for (char c : hpBar) {
            if (c == ' ') {
                cout << BG_GREEN << FG_GREEN << c;
            }
            else if (c == '*') {
                cout << BG_RED << FG_WHITE << " ";
            }
            else {
                cout << RESET << BG_WHITE << FG_WHITE << " ";
            }
        }
    }
    
    //And print the current and total health diference
    cout << RESET << NEGRITA << BG_WHITE << FG_BLACK << "] " << HP << "/" << maxHP << RESET;
}

void PrintLifeEnemy(int HP, int maxHP) {
    SetConsoleOutputCP(CP_UTF8);
    int rows, cols;
    GetConsoleSize(rows, cols);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)(cols - 40), (SHORT)5 });
    string hpBar = GenerateHPBar(HP, maxHP);

    //First print the beging
    cout << NEGRITA << BG_WHITE << FG_ORANGE << " HP: " << RESET;
    cout << NEGRITA << BG_WHITE << FG_BLACK << "[" << RESET;

    if(HP>maxHP){
        cout << BG_MAGENTA << FG_MAGENTA << string(20, ' ') << RESET;
    }
    else{
        //Print the health bar
        for (char c : hpBar) {
            if (c == ' ') {
                cout << BG_GREEN << FG_GREEN << c;
            }
            else if (c == '*') {
                cout << BG_RED << FG_WHITE << " ";
            }
            else {
                cout << RESET << BG_WHITE << FG_WHITE << " ";
            }
        }
    }

    cout << RESET << NEGRITA << BG_WHITE << FG_BLACK << "] " << HP << "/" << maxHP << RESET;
    cout << BACK_BLUE << string (20, ' ') << flush;
}

