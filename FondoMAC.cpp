// #include <iostream>

// // Códigos ANSI para colores de fondo
// #define RESET      "\033[0m"
// #define BG_BLUE    "\033[44m"
// #define BG_GREEN   "\033[42m"

// void fondoAzulVerde(int filas = 24, int columnas = 80) {
//     int mitad = filas / 2;

//     for (int i = 0; i < filas; ++i) {
//         // Parte azul (cielo)
//         if (i < mitad) {
//             std::cout << BG_BLUE;
//         }
//         // Parte verde (pradera)
//         else {
//             std::cout << BG_GREEN;
//         }

//         for (int j = 0; j < columnas; ++j) {
//             std::cout << " ";
//         }
//         std::cout << RESET << std::endl;
//     }
// }

// int main() {
//     std::cout << "\033[2J\033[1;1H"; // Limpiar pantalla
//     fondoAzulVerde();
//     std::cout << "\n\033[0mPresiona Enter para salir...";
//     std::cin.get();
//     return 0;
// }

// #include <iostream>
// #include <cmath>
// #include <sys/ioctl.h>
// #include <unistd.h>

// // Códigos ANSI para colores de fondo
// #define RESET      "\033[0m"
// #define BG_BLUE    "\033[44m"
// #define BG_GREEN   "\033[42m"
// #define BG_WHITE   "\033[47m"

// // Función para detectar si una posición está dentro de un círculo
// bool esParteDelCirculo(int x, int y, int cx, int cy, int radio) {
//     int dx = x - cx;
//     int dy = y - cy;
//     return (dx * dx + dy * dy) <= (radio * radio);
// }

// // Obtener tamaño de la terminal
// void obtenerTamanoTerminal(int &filas, int &columnas) {
//     struct winsize w;
//     ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
//     filas = w.ws_row;
//     columnas = w.ws_col;
// }

// void fondoConCirculos() {
//     int filas, columnas;
//     obtenerTamanoTerminal(filas, columnas);

//     int mitad = filas / 2;
//     int radio = std::min(filas, columnas) / 10;

//     // Coordenadas de los círculos (en el pasto)
//     int c1_x = filas - radio - 2, c1_y = 2 + radio;
//     int c2_x = filas - radio - 2, c2_y = columnas - 2 - radio;

//     for (int i = 0; i < filas; ++i) {
//         for (int j = 0; j < columnas; ++j) {
//             if (i < mitad) {
//                 std::cout << BG_BLUE << " ";  // Cielo
//             } else {
//                 if (esParteDelCirculo(i, j, c1_x, c1_y, radio) ||
//                     esParteDelCirculo(i, j, c2_x, c2_y, radio)) {
//                     std::cout << BG_WHITE << " ";  // Círculo blanco
//                 } else {
//                     std::cout << BG_GREEN << " ";  // Pasto
//                 }
//             }
//         }
//         std::cout << RESET << std::endl;
//     }
// }

// int main() {
//     std::cout << "\033[2J\033[1;1H";  // Limpiar pantalla
//     fondoConCirculos();
//     std::cout << RESET << "\n🌿 Presiona Enter para salir...";
//     std::cin.get();
//     return 0;
// }


#include <iostream>
#include <cmath>
#include <sys/ioctl.h>
#include <unistd.h>

// Códigos ANSI para colores de fondo
#define RESET      "\033[0m"
#define BG_BLUE    "\033[44m"
#define BG_GREEN   "\033[42m"
#define BG_WHITE   "\033[47m"

// Obtener tamaño terminal
void obtenerTamanoTerminal(int &filas, int &columnas) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    filas = w.ws_row;
    columnas = w.ws_col;
}

// Función para verificar si un punto (x,y) está dentro de un óvalo alargado en X
bool esParteDelOvalado(int x, int y, int cx, int cy, int radioX, int radioY) {
    float dx = float(x - cx) / radioY;  // eje vertical normalizado
    float dy = float(y - cy) / radioX;  // eje horizontal normalizado
    return (dx * dx + dy * dy) <= 1.0f;
}

void fondoConOvalos() {
    int filas, columnas;
    obtenerTamanoTerminal(filas, columnas);

    int mitad = filas / 2;

    int radioY = std::min(filas, columnas) / 16;  // eje vertical (menor)
    int radioX = std::min(filas, columnas) / 6;   // eje horizontal (mayor)

    // Colocar los óvalos en la mitad de la pradera:
    // La pradera empieza en 'mitad', así que posicionamos los óvalos en mitad + mitad/2
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
                    std::cout << BG_GREEN << " ";  // Pasto
                }
            }
        }
        std::cout << RESET << std::endl;
    }
}

int main() {
    std::cout << "\033[2J\033[1;1H"; // Limpiar pantalla
    fondoConOvalos();
    std::cout << RESET << "\n🌿 Presiona Enter para salir...";
    std::cin.get();
    return 0;
}
