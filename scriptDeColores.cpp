// <<<<<<< HEAD
#include <iostream>
#include <iomanip>

int main() {
    for (int i = 0; i < 256; ++i) {
        std::cout << "\033[48;5;" << i << "m "  // Fondo de color
                  << std::setw(4) << i          // Número del color
                  << " \033[0m ";               // Reset estilo
        std:: cout<< std:: endl;
        // Salto de línea cada 8 colores
        // if ((i + 1) % 8 == 0)
        //     std::cout << std::endl;
    }
    return 0;
}
// =======
// #include <iostream>
// #include <iomanip>

// int main() {
//     for (int i = 0; i < 256; ++i) {
//         std::cout << "\033[48;5;" << i << "m "  // Fondo de color
//                   << std::setw(4) << i          // Número del color
//                   << " \033[0m ";               // Reset estilo
//         std:: cout<< std:: endl;
//         // Salto de línea cada 8 colores
//         // if ((i + 1) % 8 == 0)
//         //     std::cout << std::endl;
//     }
//     return 0;
// }
// >>>>>>> b24246e3e883794983a0826bc2556d8f5c528b44
