#ifndef OPTIONSTABLE_H
#define OPTIONSTABLE_H
#include "header.h"
// #include "utils.cpp"
// #include "MenuUtils.h"
// #include "DataBaseOutput.h"

int OptionsTable(const vector<string>& nombres) {
    const int tableWidth = 40; 
    int selected = 0;
    int total = nombres.size();

    while (true) {

        int rows, cols;
        GetConsoleSize(rows, cols);

        int startRow = ((rows - total) / 2) + 15;
        int startCol = (cols - tableWidth) / 2;

        for (int i = 0; i < total; ++i) {
            string nombre = nombres[i];

            int paddingLeft = (tableWidth - nombre.length()) / 2;
            int paddingRight = tableWidth - nombre.length() - paddingLeft;

            string entry = string(paddingLeft, ' ') + nombre + string(paddingRight, ' ');

            COORD pos = {(SHORT)startCol, (SHORT)(startRow + i)};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

            if (i == selected) {
                cout << BG_ORANGE << FG_BLACK << entry << RESET; 
            } else {
                cout << entry;
            }
        }

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) {
                selected = (selected - 1 + total) % total;
            } else if (key == 80) {
                selected = (selected + 1) % total;
            }
        } else if (key == 13) {
            return selected;
        }
    }
}

int NavegateUsers(const vector<PuntuajesDataBase> &Users){
    const int tableWidth = 40; 
    int selected = 0;
    int total = Users.size();

    while (true) {
        int rows, cols;
        GetConsoleSize(rows, cols);

        int startRow = (rows - total) / 2;
        int startCol = (cols - tableWidth) / 2;

        for (int i = 0; i < total; ++i) {
            // Construir línea alineada
            string nombre = Users[i].nickname;
            string valor = to_string(Users[i].puntos);

            int padding = tableWidth - nombre.length() - valor.length();
            if (padding < 1) padding = 1;

            string entry = nombre + string(padding, ' ') + valor;

            COORD pos = {(SHORT)startCol, (SHORT)(startRow + i)};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

            if (i == selected) {
                cout << BG_WHITE << FG_BLACK << entry << RESET;
            }
            else {
                cout << entry;
            }
        }

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) { 
                selected = (selected - 1 + total) % total;
            } else if (key == 80) {
                selected = (selected + 1) % total;
            }
        } else if (key == 13) {
            return selected;
        }
    }
}


void HighestScores(const vector<PuntuajesDataBase> &Users) {
    int rows, cols;
    GetConsoleSize(rows, cols);
    int startRow = GameName.size() + 2;
    string title = "TOP 5 HIGHEST SCORES";
    int titleCol = (cols - (int)title.length()) / 2;
    cout << BG_BLACK << string(titleCol, ' ') << FG_RED << title << RESET << endl;

    for (int i = 0; i < 5 && i < Users.size(); ++i) {
        string name = Users[i].nickname;
        string score = to_string(Users[i].puntos);
        string line = name + string(40-(int)(name.size()+score.size()), ' ') + score;
        int padding = (cols - (int)line.length()) / 2;
        cout << BG_BLACK << string(padding, ' ') << FG_WHITE << line << RESET << endl;
    }
}

void Aviso(const string line){
    system("cls");
    BACK_BLACK;
    system("cls");
    PrintSivarMesagge(GameName);
    int rows, cols;
    GetConsoleSize(rows, cols);
    for(int i=0; i<GameName.size()+5;i++) cout<<endl;
    cout <<  BG_BLACK << string((cols-line.size())/2, ' ') << FG_CYAN << line << RESET << endl;
    sleep_for(2s);
    system("cls");
    BACK_BLACK;
    system("cls");
}
string AddUser(){
    for(int i=0;i<GameName.size()+5;i++) cout<<endl;
    int rows, cols;
    GetConsoleSize(rows, cols);
    string line = "TYPE THE NEW PROFILE NAME/NICKNAME", nickname;
    cout <<  BG_BLACK << string((cols-line.size())/2, ' ') << FG_CYAN << line << RESET << endl;
    cout << BG_BLACK << string((cols-30)/2, ' ') << FG_VIOLET << "Nickname: " << RESET;
    getline(cin, nickname);
    // cin.ignore();
    return nickname;
}   


PlayerNick PLAYER() {
    system("cls");
    BACK_BLACK;
    system("cls");
    FillColor();
    PrintSivarMesagge(GameName);
    vector<PuntuajesDataBase> Users = TablaCall();
    sort(Users.begin(), Users.end(), [](const PuntuajesDataBase &a, const PuntuajesDataBase &b) {
        return a.puntos > b.puntos;
    });
    HighestScores(Users);
    vector<string> opciones = {
        "Create Profile",
        "Select Profile",
        "Delete Profile"
    };
    int opcione = 2, EleID=0;
    PlayerNick niki;
    string name;
    do{
        Users = TablaCall();
        sort(Users.begin(), Users.end(), [](const PuntuajesDataBase &a, const PuntuajesDataBase &b) {
            return a.puntos > b.puntos;
        });
        opcione=OptionsTable(opciones);
        system("cls");
        BACK_BLACK;
        system("cls");
        PrintSivarMesagge(GameName);
        switch(opcione){
            case 0:
                name = AddUser();
                niki = {name, 0};
                Tabla(niki);
                Aviso("PROFILE CREATED SUCESSFULLY");
                break;
            case 1:
                EleID=NavegateUsers(Users);
                niki = {Users[EleID].nickname, Users[EleID].puntos};
                break;
            case 2:
                EleID=NavegateUsers(Users);
                EliminarAlguien(Users[EleID].orden);
                Aviso("PROFILE DELETED SUCESSFULLY");
                break;
            default:
                break; 
        
        }
    }while(opcione==2);
    return niki;
}

// int main(){
//     PlayerNick aux = PLAYER();
//     cout<<endl<<aux.nick<<endl; 
// }
#endif