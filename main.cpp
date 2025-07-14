#include "src/game.cpp"

int main() {
    BACK_BLACK;
    system("cls");
    system("chcp 850 > nul");

    vector<string> MainMenu = {
        "Start game",
        "About",
        "Credits",
        "Leave"
    };
    FillColor();
    int choice = 0;
    char key;
    mainPageLogo();
    system("cls");

    while (true) {
        mostrarMenu(MainMenu, choice);
        key = getch();

        if (key == -32) {
            key = getch();
            if (key == 72) choice = (choice - 1 + MainMenu.size()) % MainMenu.size(); // ↑
            if (key == 80) choice = (choice + 1) % MainMenu.size(); // ↓
        } else if (key == 'w' || key == 'W') {
            choice = (choice - 1 + MainMenu.size()) % MainMenu.size();
        } else if (key == 's' || key == 'S') {
            choice = (choice + 1) % MainMenu.size();
        } else if (key == '\r') {
            BACK_BLACK;
            system("cls");
            switch(choice){
                case 0: GameStart(); break;
                case 1: About(); break;
                case 2: Credits(); break;
                case 3: return 0;
            }
        }
    }

    sleep_for(chrono::milliseconds(5000));
    system("cls");
    return 0;
}
