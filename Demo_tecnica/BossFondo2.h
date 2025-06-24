//Mac//

#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <unistd.h>
#include <algorithm>
#include <signal.h>


using namespace std;
int filas, columnas;

#define RESET "\033[0m"
#define BG_WHITE "\033[47m"

// Obtener tamaño terminal
void obtenerTamanoTerminal(int &filas, int &columnas)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    filas = w.ws_row;
    columnas = w.ws_col;
}

// Función para verificar si un punto (x,y) está dentro de un óvalo alargado en X
bool esParteDelOvalado(int x, int y, int cx, int cy, int radioX, int radioY)
{
    float dx = float(x - cx) / radioY; // eje horizontal normalizado
    float dy = float(y - cy) / radioX; // eje vertical normalizado
    return (dx * dx + dy * dy) <= 1.0f;
}

const int spriteHeight = 25;
const int spriteWidth = 49;

void fondoConOvalos()
{

    obtenerTamanoTerminal(filas, columnas);

    int mitad = filas / 2;

    int radioY = min(filas, columnas) / 10; // eje vertical (menor)
    int radioX = min(filas, columnas) / 2; // eje horizontal (mayor)

    int c1_x = mitad + mitad / 2;            // centro óvalo 1 (filas)
    int c2_x = c1_x;            // centro óvalo 2 (filas)
    int c1_y = columnas / 4;     // centro óvalo 1 (columnas)
    int c2_y = 3 * columnas / 4; // centro óvalo 2 (columnas)

    int color_inicio = 88; // WINE_RED
    int color_final = 93;  // Fake Purple

    for (int i = 0; i < filas; ++i)
    {
        for (int j = 0; j < columnas; ++j)
        {
            // Gradiente vertical usando los colores ANSI
            int color = color_inicio + (color_final - color_inicio) * i / (filas - 1);

            // Si el punto está dentro de alguno de los óvalos
            if (esParteDelOvalado(i, j, c1_x, c1_y, radioX, radioY) ||
                esParteDelOvalado(i, j, c2_x, c2_y, radioX, radioY))
            {
                cout << BG_WHITE << " " << RESET;
            }
            else
            {
                cout << "\033[48;5;" << color << "m " << RESET;
            }
        }
        cout << endl;
    }
}

pid_t musicPid = -1;

void playMusic() {
    if (musicPid == -1) {
        musicPid = fork();
        if (musicPid == 0) {
            // Proceso hijo: ejecuta afplay en loop
            while (true) {
                execlp("afplay", "afplay", "boss.wav", NULL);
                // Si execlp falla:
                _exit(1);
            }
        }
    }
}



// int main()
// {
//     srand(time(0));
//     playMusic();

//     cout << "\033[2J\033[1;1H"; // Limpiar pantalla
//     fondoConOvalos();
//     return 0; //Para parar el programa porque no hay una variable definida aun para detener la musica

    

// }

//fondo de jefe ya nos queda solo juntarlo con la demo y probar :)

void stopMusic() {
    if (musicPid != -1) {
        kill(musicPid, SIGKILL);
        musicPid = -1;
    }
}

//windows//

// #include <iostream>
// #include <iomanip>
// #include <windows.h>
// #include <algorithm>

// using namespace std;
// int filas, columnas;

// #define RESET "\033[0m"
// #define BG_WHITE "\033[47m"

// void habilitarANSI() {
//     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//     if (hOut == INVALID_HANDLE_VALUE) return;
//     DWORD dwMode = 0;
//     if (!GetConsoleMode(hOut, &dwMode)) return;
//     dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
//     SetConsoleMode(hOut, dwMode);
// }

// // Obtener tamaño terminal (Windows)
// void obtenerTamanoTerminal(int &filas, int &columnas) {
//     CONSOLE_SCREEN_BUFFER_INFO csbi;
//     if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
//         columnas = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//         filas = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
//     } else {
//         columnas = 80;
//         filas = 25;
//     }
// }

// // Función para verificar si un punto (x,y) está dentro de un óvalo alargado en X
// bool esParteDelOvalado(int x, int y, int cx, int cy, int radioX, int radioY) {
//     float dx = float(x - cx) / radioY; // eje horizontal normalizado
//     float dy = float(y - cy) / radioX; // eje vertical normalizado
//     return (dx * dx + dy * dy) <= 1.0f;
// }

// const int spriteHeight = 25;
// const int spriteWidth = 49;

// void fondoConOvalos() {
//     obtenerTamanoTerminal(filas, columnas);

//     int mitad = filas / 2;

//     int radioY = min(filas, columnas) / 10; // eje vertical (menor)
//     int radioX = min(filas, columnas) / 2; // eje horizontal (mayor)

//     int c1_x = mitad + mitad / 2;            // centro óvalo 1 (filas)
//     int c2_x = c1_x;            // centro óvalo 2 (filas)
//     int c1_y = columnas / 4;     // centro óvalo 1 (columnas)
//     int c2_y = 3 * columnas / 4; // centro óvalo 2 (columnas)

//     int color_inicio = 88; // WINE_RED
//     int color_final = 93;  // Fake Purple

//     for (int i = 0; i < filas; ++i) {
//         for (int j = 0; j < columnas; ++j) {
//             // Gradiente vertical usando los colores ANSI
//             int color = color_inicio + (color_final - color_inicio) * i / (filas - 1);

//             // Si el punto está dentro de alguno de los óvalos
//             if (esParteDelOvalado(i, j, c1_x, c1_y, radioX, radioY) ||
//                 esParteDelOvalado(i, j, c2_x, c2_y, radioX, radioY)) {
//                 cout << BG_WHITE << " " << RESET;
//             } else {
//                 cout << "\033[48;5;" << color << "m " << RESET;
//             }
//         }
//         cout << endl;
//     }
// }
// void playMusic() {
//     // Reproduce el archivo boss.wav en bucle y de forma asíncrona
//     PlaySound(TEXT("boss.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
// }

// void stopMusic() {
//     // Detiene la música
//     PlaySound(NULL, 0, 0);
// }

// // Música no implementada en Windows por simplicidad
// // Puedes usar PlaySound de windows.h si tienes un archivo WAV:
// // #include <mmsystem.h> y luego PlaySound(TEXT("boss.wav"), NULL, SND_FILENAME | SND_ASYNC);

// int main() {
//     // Opcional: habilitar secuencias ANSI
//     habilitarANSI();

//     system("cls"); // Limpiar pantalla en Windows
//     fondoConOvalos();
// habilitarANSI();
//     system("cls");
//     playMusic();
//     fondoConOvalos();
//     // Pausa para que puedas ver el fondo y escuchar la música (por ejemplo, espera una tecla)
//     system("pause");
//     stopMusic();
//     return 0;

//     return 0;
// }