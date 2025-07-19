#include "DataBaseOutput.h"
#include "header.h"

map<char, int> spritesID = {

    {'N', 130},
    {'-', 172},
    {'D', 249},
    {'O', 0},
    {'B', 231},
    {'H', 239},
    {'#', 249},
    {'+', 231},
    {'@', 118},
    {'&', 208},
    {'$', 196},
    {'=', 166},
    {'*', 204},
    {'<', 220},
    {'%', 206},
};

vector<vector<string>> allSprites;

void CargaDeSprites(const string& filename = "src/DataBase/Sprites.txt") {
allSprites.clear();
ifstream file(filename);
if (!file.is_open()) {
    cerr << "ERROR: No se pudo abrir " << filename << endl;
    return;
}

string line;
vector<string> currentSprite;
const string reset   = "\033[0m";
const string ansiPre = "\033[38;5;";

while (getline(file, line)) {
    if (line.empty()) 
        continue;

    // Detecta encabezado de sprite (línea que empieza con dígito)
    if (isdigit(line[0])) {
        if (!currentSprite.empty()) {
            allSprites.push_back(currentSprite);
            currentSprite.clear();
        }
    }
    else {
        // Construye la línea coloreada
        string coloredLine;
        for (char c : line) {
            auto it = spritesID.find(c);
            if (it != spritesID.end()) {
                coloredLine += ansiPre
                                + to_string(it->second)
                                + "m";
            }
            // Si no está en el mapa, usa color por defecto
            coloredLine += c;
            coloredLine += reset;
        }
        currentSprite.push_back(coloredLine);
    }
}

// Agrega el último sprite si existe
if (!currentSprite.empty()) {
    allSprites.push_back(currentSprite);
}

file.close();
}
