#include <iostream>
#include <iomanip>

int main() {
    for (int i = 0; i < 256; ++i) {
        std::cout << "\033[48;5;" << i << "m "  // Fondo de color
                  << std::setw(4) << i          // Número del color
                  << " \033[0m ";               // Reset estilo

        // Salto de línea cada 8 colores
        if ((i + 1) % 8 == 0)
            std::cout << std::endl;
    }
    return 0;
}
