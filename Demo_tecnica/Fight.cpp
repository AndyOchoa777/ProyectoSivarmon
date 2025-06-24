#include "BossFondo2.h"
#include "SpritsDemo.h"
#include <iostream>

int main() {

    srand(time(nullptr));

    Character player = {"Raccoon", 30, 30};
    Character enemy  = {"Wild Cat", 30, 30};

    vector<string> raccoon_ascii = {
        " /\\___/\\",
        "( o   o )",
        "(  =^=  )",
        "(        )",
        "(         )",
        "(___||___)"
    };

    vector<string> enemy_ascii = {
        "  |\\___/|   ",
        " (=^.^=)    ",
        " (  > <  )  ",
        "  )     (   ",
        " (       )  ",
        " (___||___) "
    };

    // Centro del óvalo
    int ovalCenterX = 40;
    int ovalCenterY = 12;

    // Calcular ancho y alto del sprite
    int spriteHeight = raccoon_ascii.size();
    int spriteWidth = 0;
    for (const auto& line : raccoon_ascii)
        spriteWidth = max(spriteWidth, (int)line.size());

    // Calcular esquina superior izquierda para centrar el sprite en el óvalo
    int startX = ovalCenterX - spriteWidth / 2-10;
    int startY = ovalCenterY - spriteHeight / 2-10;

    // int raccoonX = 10, raccoonY = 2;
    // int enemy_asciiX = 10, enemy_asciiY = 2;
    // // Límites para el movimiento (ajusta según el tamaño del fondo/pantalla)
    // const int MAX_X = 60; // Ejemplo de límite horizontal
    // const int MAX_Y = 15; 
    // Límites para el movimiento (ajusta según el tamaño del fondo/pantalla)
    int cursorX = 0, cursorY = 0;

    cout << "\nPresiona Enter para iniciar el combate...";
    playMusic();
    cout << "\033[2J\033[1;1H"; // Limpiar pantalla
    fondoConOvalos(); // Dibuja el fondo ANTES del combate
    cin.get(); // Espera entrada

    // --- Ciclo principal del combate ---
    while (player.hp > 0 && enemy.hp > 0) {
        clearScreen();              // Limpia toda la pantalla
        fondoConOvalos();           // Dibuja el fondo PRIMERO
        drawAsciiArt(raccoon_ascii, 50, 48); // Dibuja sprites encima del fondo
        drawAsciiArt(enemy_ascii, 165, 48);
        drawHealth(player, 50, 60);
        drawHealth(enemy, 165, 60);
        drawMenu(cursorX, cursorY);

        int input = 0;
        while (!(input == 'w' || input == 's' || input == 'a' || input == 'd' || input == '\n')) {
            input = getch_noblock();
            // mapeo: w=UP, s=DOWN, a=LEFT, d=RIGHT, enter=SELECT
        }

        if (input == 'w')        cursorY = std::max(0, cursorY - 1);
        else if (input == 's')   cursorY = std::min(1, cursorY + 1);
        else if (input == 'a')   cursorX = std::max(0, cursorX - 1);
        else if (input == 'd')   cursorX = std::min(2, cursorX + 1);
        else if (input == '\n') {
            player.defending = false;
            int action = cursorY * 3 + cursorX;
            switch (action) {
                case 0:
                    std::cout << "\nYou used Tackle!"; enemy.hp -= 10; break;
                case 1:
                    std::cout << "\nYou used Bite!"; enemy.hp -= 12; break;
                case 2:
                    std::cout << "\nYou used Tail Whip!"; enemy.hp -= 8; break;
                case 3:
                    std::cout << "\nYou defend!"; player.defending = true; break;
                case 4:
                    std::cout << "\nYou used a potion!"; player.hp = std::min(player.maxHp, player.hp + 10); break;
                case 5:
                    std::cout << "\nYou fled the battle!"; return 0;
            }
            fflush(stdout);
            sleepMs(1000);

            if (enemy.hp > 0) enemyTurn(player, enemy);
        }
    }

    std::cout << (player.hp > 0 ? "\nYou win!\n" : "\nYou lost...\n");
    stopMusic(); // Detiene la música
    return 0;
}