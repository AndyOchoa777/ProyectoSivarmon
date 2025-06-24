// #include <iostream>
// #include <vector>
// #include <string>
// #include <termios.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <cstdlib>
// #include <ctime>

// using namespace std;

// struct Character {
//     string name;
//     int hp, maxHp;
//     bool defending = false;
// };

// // Mover cursor a (x, y)
// void moveCursor(int x, int y) {
//     cout << "\033[" << (y+1) << ";" << (x+1) << "H";
// }

// // Limpiar pantalla
// void clearScreen() {
//     cout << "\033[2J\033[H";
// }

// // Leer tecla sin echo y sin bloqueo
// int getch_noblock() {
//     struct termios oldt{}, newt{};
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;
//     newt.c_lflag &= ~(ICANON | ECHO);
//     newt.c_cc[VMIN] = 0;
//     newt.c_cc[VTIME] = 0;
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);

//     int ch = getchar();

//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     return ch;
// }

// // Pausar x milisegundos
// void sleepMs(int ms) {
//     usleep(ms * 1000);
// }

// void drawAsciiArt(const vector<string>& art, int x, int y) {
//     for (size_t i = 0; i < art.size(); ++i) {
//         moveCursor(x, y + i);
//         cout << art[i];
//     }
// }

// void drawHealth(const Character& c, int x, int y) {
//     moveCursor(x, y);
//     cout << c.name << ": ";
//     for (int i = 0; i < c.hp; i += 10) cout << "[x]";
//     for (int i = c.hp; i < c.maxHp; i += 10) cout << "[ ]";
// }

// void drawMenu(int cursorX, int cursorY) {
//     vector<vector<string>> options = {
//         {"Tackle", "Bite", "Tail Whip"},
//         {"Defend", "Use Item", "Run"}
//     };
//     moveCursor(0, 20);
//     cout << "\nChoose your action:\n\n";

//     for (int y = 0; y < 2; ++y) {
//         for (int x = 0; x < 3; ++x)
//             cout << "+------------+  ";
//         cout << "\n";
//         for (int x = 0; x < 3; ++x) {
//             cout << "| ";
//             if (cursorX == x && cursorY == y) cout << "> ";
//             else cout << "  ";
//             cout << options[y][x];
//             for (size_t i = options[y][x].size(); i < 10; ++i) cout << " ";
//             cout << "|  ";
//         }
//         cout << "\n";
//         for (int x = 0; x < 3; ++x)
//             cout << "+------------+  ";
//         cout << "\n";
//     }
// }

// void enemyTurn(Character& player, Character& enemy) {
//     int action = rand() % 3;
//     if (action == 0) {
//         cout << "\nEnemy attacks!";
//         if (!player.defending) player.hp -= 10;
//         else cout << " But you defended!";
//     } else if (action == 1) {
//         cout << "\nEnemy defends!";
//         enemy.defending = true;
//     } else {
//         cout << "\nEnemy uses item!";
//         enemy.hp = min(enemy.maxHp, enemy.hp + 10);
//     }
//     fflush(stdout);
//     sleepMs(500);
// }

// int main() {
//     srand(time(nullptr));

//     Character player = {"Raccoon", 30, 30};
//     Character enemy  = {"Wild Cat", 30, 30};

//     vector<string> raccoon_ascii = {
//         "  /\\___/\\   ",
//         " ( o   o )  ",
//         " (  =^=  )  ",
//         " (        ) ",
//         " (         )",
//         " (___||___) "
//     };

//     vector<string> enemy_ascii = {
//         "  |\\___/|   ",
//         " (=^.^=)    ",
//         " (  > <  )  ",
//         "  )     (   ",
//         " (       )  ",
//         " (___||___) "
//     };

//     int cursorX = 0, cursorY = 0;

//     while (player.hp > 0 && enemy.hp > 0) {
//         clearScreen();

//         drawAsciiArt(raccoon_ascii, 2, 2);
//         drawAsciiArt(enemy_ascii, 50, 2);
//         drawHealth(player, 2, 10);
//         drawHealth(enemy, 50, 10);
//         drawMenu(cursorX, cursorY);

//         int input = 0;
//         while (!(input == 'w' || input == 's' || input == 'a' || input == 'd' || input == '\n')) {
//             input = getch_noblock();
//             // mapeo: w=UP, s=DOWN, a=LEFT, d=RIGHT, enter=SELECT
//         }

//         if (input == 'w')        cursorY = max(0, cursorY - 1);
//         else if (input == 's')   cursorY = min(1, cursorY + 1);
//         else if (input == 'a')   cursorX = max(0, cursorX - 1);
//         else if (input == 'd')   cursorX = min(2, cursorX + 1);
//         else if (input == '\n') {
//             player.defending = false;
//             int action = cursorY * 3 + cursorX;
//             switch (action) {
//                 case 0:
//                     cout << "\nYou used Tackle!"; enemy.hp -= 10; break;
//                 case 1:
//                     cout << "\nYou used Bite!"; enemy.hp -= 12; break;
//                 case 2:
//                     cout << "\nYou used Tail Whip!"; enemy.hp -= 8; break;
//                 case 3:
//                     cout << "\nYou defend!"; player.defending = true; break;
//                 case 4:
//                     cout << "\nYou used a potion!"; player.hp = min(player.maxHp, player.hp + 10); break;
//                 case 5:
//                     cout << "\nYou fled the battle!"; return 0;
//             }
//             fflush(stdout);
//             sleepMs(1000);

//             if (enemy.hp > 0) enemyTurn(player, enemy);
//         }
//     }

//     cout << (player.hp > 0 ? "\nYou win!\n" : "\nYou lost...\n");
//     return 0;
// }

#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Character {
    string name;
    int hp, maxHp;
    bool defending = false;
};

// Mover cursor a (x, y)
void moveCursor(int x, int y) {
    cout << "\033[" << (y+1) << ";" << (x+1) << "H";
}

// Limpiar pantalla
void clearScreen() {
    cout << "\033[2J\033[H";
}

// Leer tecla sin echo y sin bloqueo
int getch_noblock() {
    struct termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Configurar stdin como no bloqueante
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    // Restaurar configuración original
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
}

// Pausar x milisegundos
void sleepMs(int ms) {
    usleep(ms * 1000);
}

void drawAsciiArt(const vector<string>& art, int x, int y) {
    for (size_t i = 0; i < art.size(); ++i) {
        moveCursor(x, y + i);
        cout << art[i];
    }
}

void drawHealth(const Character& c, int x, int y) {
    moveCursor(x, y);
    cout << c.name << ": ";
    for (int i = 0; i < c.hp; i += 10) cout << "[x]";
    for (int i = c.hp; i < c.maxHp; i += 10) cout << "[ ]";
}

void drawMenu(int cursorX, int cursorY) {
    vector<vector<string>> options = {
        {"Tackle", "Bite", "Tail Whip"},
        {"Defend", "Use Item", "Run"}
    };
    moveCursor(0, 20);
    cout << "\nChoose your action:\n\n";

    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 3; ++x)
            cout << "+------------+  ";
        cout << "\n";
        for (int x = 0; x < 3; ++x) {
            cout << "| ";
            if (cursorX == x && cursorY == y) cout << "> ";
            else cout << "  ";
            cout << options[y][x];
            for (size_t i = options[y][x].size(); i < 10; ++i) cout << " ";
            cout << "|  ";
        }
        cout << "\n";
        for (int x = 0; x < 3; ++x)
            cout << "+------------+  ";
        cout << "\n";
    }
}

void enemyTurn(Character& player, Character& enemy) {
    int action = rand() % 3;
    if (action == 0) {
        cout << "\nEnemy attacks!";
        if (!player.defending) player.hp -= 10;
        else cout << " But you defended!";
    } else if (action == 1) {
        cout << "\nEnemy defends!";
        enemy.defending = true;
    } else {
        cout << "\nEnemy uses item!";
        enemy.hp = min(enemy.maxHp, enemy.hp + 10);
    }
    fflush(stdout);
    sleepMs(500);
}

// --------- EJEMPLO DE USO EN UN JUEGO PRINCIPAL -----------
// int main() {
//     srand(time(nullptr));

//     Character player = {"Raccoon", 30, 30};
//     Character enemy  = {"Wild Cat", 30, 30};

//     vector<string> raccoon_ascii = {
//         "  /\\___/\\   ",
//         " ( o   o )  ",
//         " (  =^=  )  ",
//         " (        ) ",
//         " (         )",
//         " (___||___) "
//     };

//     vector<string> enemy_ascii = {
//         "  |\\___/|   ",
//         " (=^.^=)    ",
//         " (  > <  )  ",
//         "  )     (   ",
//         " (       )  ",
//         " (___||___) "
//     };

//     int cursorX = 0, cursorY = 0;

//     while (player.hp > 0 && enemy.hp > 0) {
//         clearScreen();

//         drawAsciiArt(raccoon_ascii, 2, 2);
//         drawAsciiArt(enemy_ascii, 50, 2);
//         drawHealth(player, 2, 10);
//         drawHealth(enemy, 50, 10);
//         drawMenu(cursorX, cursorY);

//         // Leer input bloqueante y solo aceptar teclas válidas
//         int input = -1;
//         while (!(input == 'w' || input == 's' || input == 'a' || input == 'd' || input == '\n')) {
//             input = getch_noblock();
//             sleepMs(10); // Evita alto consumo de CPU
//         }

//         // Limitar valores del cursor
//         if (input == 'w')        cursorY = max(0, cursorY - 1);
//         else if (input == 's')   cursorY = min(1, cursorY + 1);
//         else if (input == 'a')   cursorX = max(0, cursorX - 1);
//         else if (input == 'd')   cursorX = min(2, cursorX + 1);
//         else if (input == '\n') {
//             player.defending = false;
//             int action = cursorY * 3 + cursorX;
//             switch (action) {
//                 case 0:
//                     cout << "\nYou used Tackle!"; enemy.hp -= 10; break;
//                 case 1:
//                     cout << "\nYou used Bite!"; enemy.hp -= 12; break;
//                 case 2:
//                     cout << "\nYou used Tail Whip!"; enemy.hp -= 8; break;
//                 case 3:
//                     cout << "\nYou defend!"; player.defending = true; break;
//                 case 4:
//                     cout << "\nYou used a potion!"; player.hp = min(player.maxHp, player.hp + 10); break;
//                 case 5:
//                     cout << "\nYou fled the battle!"; return 0;
//             }
//             fflush(stdout);
//             sleepMs(1000);

//             if (enemy.hp > 0) enemyTurn(player, enemy);
//         }
//     }

//     cout << (player.hp > 0 ? "\nYou win!\n" : "\nYou lost...\n");
//     return 0;
// }