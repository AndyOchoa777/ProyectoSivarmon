#include <iostream>
#include <cmath>
#include <windows.h>

// Códigos ANSI para colores de fondo
#define RESET      "\033[0m"
#define BG_BLUE    "\033[44m"
#define BG_GREEN   "\033[42m"
#define BG_WHITE   "\033[47m"

// Activar soporte ANSI en la consola de Windows
void habilitarANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo;
    GetConsoleMode(hOut, &modo);
    modo |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, modo);
}

// Obtener tamaño de la consola en filas y columnas
void obtenerTamanoTerminal(int &filas, int &columnas) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columnas = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    filas = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Determinar si una coordenada está dentro de un óvalo alargado en X
bool esParteDelOvalado(int x, int y, int cx, int cy, int radioX, int radioY) {
    float dx = float(x - cx) / radioY;  // eje vertical normalizado
    float dy = float(y - cy) / radioX;  // eje horizontal normalizado
    return (dx * dx + dy * dy) <= 1.0f;
}

// Dibuja el fondo completo con óvalos blancos en la pradera
void fondoConOvalos() {
    int filas, columnas;
    obtenerTamanoTerminal(filas, columnas);

    int mitad = filas / 2;

    int radioY = std::min(filas, columnas) / 16;  // eje vertical (menor)
    int radioX = std::min(filas, columnas) / 6;   // eje horizontal (mayor)

    // Colocar los óvalos en la mitad de la pradera (parte inferior)
    int c1_x = mitad + mitad / 2;   // vertical, más arriba en la pradera
    int c2_x = c1_x;
    int c1_y = columnas / 3;
    int c2_y = 2 * columnas / 3;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i < mitad) {
                std::cout << BG_BLUE << " ";  // Cielo
            } else {
                if (esParteDelOvalado(i, j, c1_x, c1_y, radioX, radioY) ||
                    esParteDelOvalado(i, j, c2_x, c2_y, radioX, radioY)) {
                    std::cout << BG_WHITE << " ";  // Óvalos blancos
                } else {
                    std::cout << BG_GREEN << " ";  // Pradera
                }
            }
        }
        std::cout << RESET << std::endl;
    }
}

int main() {
    habilitarANSI(); // Activar códigos ANSI en Windows 10+
    std::cout << "\033[2J\033[1;1H";  // Limpiar pantalla
    fondoConOvalos();
    std::cout << RESET << "\n🌿 Presiona Enter para salir...";
    std::cin.get();
    return 0;
}
