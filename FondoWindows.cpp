#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;
// Códigos ANSI para colores de fondo
#define RESET "\033[0m"
#define BG_BLUE "\033[44m"
#define BG_GREEN "\033[42m"
#define BG_WHITE "\033[47m"

// Activar soporte ANSI en la consola de Windows
void habilitarANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo;
    GetConsoleMode(hOut, &modo);
    modo |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, modo);
}

// Obtener tamaño de la consola en filas y columnas
void obtenerTamanoTerminal(int &filas, int &columnas)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columnas = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    filas = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Determinar si una coordenada está dentro de un óvalo alargado en X
bool esParteDelOvalado(int x, int y, int cx, int cy, int radioX, int radioY)
{
    float dx = float(x - cx) / radioY; // eje vertical normalizado
    float dy = float(y - cy) / radioX; // eje horizontal normalizado
    return (dx * dx + dy * dy) <= 1.0f;
}

// Dibuja el fondo completo con óvalos blancos en la pradera
vvoid fondoConOvalos()
{
    int filas, columnas;
    obtenerTamanoTerminal(filas, columnas);

    int mitad = filas / 2;

    int radioY = min(filas, columnas) / 16; // eje vertical (menor)
    int radioX = min(filas, columnas) / 3;  // eje horizontal (mayor)

    int c1_x = mitad + mitad / 2;
    int c2_x = c1_x;
    int c1_y = columnas / 4;
    int c2_y = 3 * columnas / 4;

    for (int i = 0; i < filas; ++i)
    {
        for (int j = 0; j < columnas; ++j)
        {
            if (i < mitad)
            {
                cout << BG_BLUE << " "; // Cielo
            }
            else
            {
                if (esParteDelOvalado(i, j, c1_x, c1_y, radioX, radioY) ||
                    esParteDelOvalado(i, j, c2_x, c2_y, radioX, radioY))
                {
                    cout << BG_WHITE << " "; // Óvalos blancos
                }
                else
                {
                    cout << BG_GREEN << " "; // Pradera
                }
            }
        }
        cout << RESET << endl;
    }
}

int main()
{
    habilitarANSI();
    cout << "\033[2J\033[1;1H"; // Limpiar pantalla
    fondoConOvalos();
    cout << RESET << "\n Presiona Enter para salir...";
    cin.get();
    return 0;
}
