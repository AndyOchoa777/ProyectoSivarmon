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
    if (!file.is_open()) return;
    string line;
    vector<string> currentSprite;
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (isdigit(line[0])) {
            if (!currentSprite.empty()) {
                allSprites.push_back(currentSprite);
                currentSprite.clear();
            }
        } else {
            currentSprite.push_back(line);
        }
    }
    if (!currentSprite.empty()) {
        allSprites.push_back(currentSprite);
    }

    for (int i = 0; i < lines; i++) {
        if (i < sprite1_height) {
            const string& line = OP_SPRITE.Sprite[i];
            COORD pos = { (SHORT)leftStartX, (SHORT)(leftStartY + i) };
            SetConsoleCursorPosition(hConsole, pos);
            for (char ch : line) {
                if (ch != ' ') {
                    cout << ch; //if is not an empty space just print it
                } else {
                    cout << "\033[C"; //move the cursor to the next space
                }
            }
        }
    }

    file.close();
}


