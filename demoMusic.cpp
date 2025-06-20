
/* 
ESTE PROYECTO DEBE SER EJECUTADO DE LA SIGUIENTE MANERA
1. Revisar que el archivo battle.wav este en buen estado
2. No usar el compilador de la extension de visual
3. compilar de la siguiente forma: g++ battle_game.cpp -o battle_game.exe -lwinmm (NO SE NECESITA INSTALAR NADA ESPECIAL)

*/

#include <iostream>
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h> //  _getch() que reconocer cuando el usuario presiona una tecla (para el menu)
#include <ctime>  // <- Esta línea falta para que funcione la musica


using namespace std;

struct Character {
    string name;
    int hp;
    int maxHp;
    bool defending = false; //por motivos practicos, se inicializa la defensa como false
};

//Funcion que pone la musica, el archivo debe ser .wav (se puede transformar un mp3 a wav ONLINE y el largo del audio no importa :))
//el archivo WAV debe estar en la misma carpeta del .exe
void playMusic() {
    PlaySound(TEXT("battle.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //la musca suena en loop si se termina y el combate aun no termina
}

//Esta funcion hace que la musica pare cuando el combate termina
void stopMusic() {
    PlaySound(NULL, 0, 0);
}


void drawAsciiArt(const vector<string>& art, int x, int y) {
    for (size_t i = 0; i < art.size(); ++i) {
        COORD pos = { (SHORT)x, (SHORT)(y + i) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        cout << art[i];
    }
}

//Dibujar los [x] que representan la vida (tiene fallo)
void drawHealth(const Character& c, int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << c.name << ": ";
    for (int i = 0; i < c.hp; i += 10) cout << "[x]";
    for (int i = c.hp; i < c.maxHp; i += 10) cout << "[ ]";
}

//Dibujar el menu, cursorX y Y nos dicen la posicion en el menu 
void drawMenu(int cursorX, int cursorY) {
    string options[2][3] = {
        {"Tackle", "Bite", "Tail Whip"},
        {"Defend", "Use Item", "Run"}
    };

    COORD pos = { 0, 20 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << "\nChoose your action:\n\n";

    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 3; x++)
            cout << "+------------+  ";
        cout << "\n";
        for (int x = 0; x < 3; x++) {
            cout << "| ";
            if (cursorX == x && cursorY == y) cout << "> ";
            else cout << "  ";

            cout << options[y][x];
            for (size_t i = options[y][x].size(); i < 10; i++) cout << " ";
            cout << "|  ";
        }
        cout << "\n";
        for (int x = 0; x < 3; x++)
            cout << "+------------+  ";
        cout << "\n";
    }
}

//Se determina el movimiento del enemigo y ademas se revisa si el protagonista se cubrio y no le hara danio
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
        enemy.hp += 10;
        if (enemy.hp > enemy.maxHp) enemy.hp = enemy.maxHp;
    }
    Sleep(500);
}

int main() {
    srand(time(0));
    playMusic();

    //les damos al juagdor y al enemigo la misma vida, y un nombre
    Character player = { "Raccoon", 30, 30 };
    Character enemy = { "Wild Cat", 30, 30 };

    vector<string> raccoon_ascii = {
        "  /\\___/\\   ",
        " ( o   o )  ",
        " (  =^=  )  ",
        " (        ) ",
        " (         )",
        " (___||___) "
    };

    vector<string> enemy_ascii = {
        "  |\\___/|   ",
        " (=^.^=)    ",
        " (  > <  )  ",
        "  )     (   ",
        " (       )  ",
        " (___||___) "
    };

    int cursorX = 0, cursorY = 0; //con esto el cursor empieza en la primera posicion del menu

    while (player.hp > 0 && enemy.hp > 0) {
        system("cls"); //sirve para limpiar la consola despues de cada turno y dibujar el hud actulizado

        drawAsciiArt(raccoon_ascii, 2, 2);
        drawAsciiArt(enemy_ascii, 50, 2);

        drawHealth(player, 2, 10);
        drawHealth(enemy, 50, 10);

        drawMenu(cursorX, cursorY);

        char input = _getch();
        if (input == 72) cursorY = max(0, cursorY - 1); // Up
        else if (input == 80) cursorY = min(1, cursorY + 1); // Down
        else if (input == 75) cursorX = max(0, cursorX - 1); // Left
        else if (input == 77) cursorX = min(2, cursorX + 1); // Right
        else if (input == 13) { // Enter
            player.defending = false;
            int action = cursorY * 3 + cursorX;

            if (action == 0) {
                cout << "\nYou used Tackle!";
                enemy.hp -= 10;
            } else if (action == 1) {
                cout << "\nYou used Bite!";
                enemy.hp -= 12;
            } else if (action == 2) {
                cout << "\nYou used Tail Whip!";
                enemy.hp -= 8;
            } else if (action == 3) {
                cout << "\nYou defend!";
                player.defending = true;
            } else if (action == 4) {
                cout << "\nYou used a potion!";
                player.hp += 10;
                if (player.hp > player.maxHp) player.hp = player.maxHp;
            } else if (action == 5) {
                cout << "\nYou fled the battle!";
                break;
            }
            Sleep(1000);
            if (enemy.hp > 0) enemyTurn(player, enemy);
        }
    }

    //Se para la musica y se muestra que el combate termino
    stopMusic();
    cout << "\nBattle ended!\n";
    return 0;
}
