#include "FightBackground.h"
#include "DataBaseOutput.h"

int lines, bottomline;
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

//print enemies
void PrintBattleEnemies(int SivarmonSelected, int Enemy){
    SetConsoleOutputCP(CP_UTF8);
    enableANSIColors();                      
    system("cls");           
    drawBackgroundWithOvals();  
    SpritesDataBase OP_SPRITE = SpritesCall(SivarmonSelected);
    SpritesDataBase CPU_SPRITE = SpritesCall(Enemy);
    //call the sprite from the data base
    SetConsoleOutputCP(CP_UTF8);
    //use this funtion to make all character avaliables
    int consoleRows, consoleCols;
    GetConsoleSize(consoleRows, consoleCols);
    //look for the maximum row on both sprites
    int maxLeftWidth = 0, maxRightWidth = 0;
    for (const auto& line : OP_SPRITE.Sprite){
        maxLeftWidth = max(maxLeftWidth, (int)line.size());
    }
    for (const auto& line : CPU_SPRITE.Sprite){
        maxRightWidth = max(maxRightWidth, (int)line.size());
    }
    //Oval coordenates declared on  fight background
    int half = consoleRows / 2;
    int c1_x = half + half / 2; 
    int c1_y = consoleCols / 4; 
    int c2_x = c1_x;             
    int c2_y = 3 * consoleCols / 4;
    int centerY = half + half / 2 - 7;
    //set new variables for the sprites positions
    int centerX1 = consoleCols / 3;
    int ovalRightStartX = c2_y; 

    int centerX2 = ovalRightStartX;
    //offsets are to move vertical and horizontal between distances for the sprites
    int offsetY = -1; 
    int offsetX = 10; 

    int sprite1_height = OP_SPRITE.Sprite.size(); // to get both sprtites height
    int sprite2_height = CPU_SPRITE.Sprite.size();

    int leftStartX = centerX1 - maxLeftWidth / 2 + offsetX;
    int leftStartY = centerY - sprite1_height + 1 + offsetY;

    int spacing =( (maxLeftWidth + maxRightWidth) + 3 > consoleCols) ? 2:7 ; //spacing between sprites
    int rightStartX = leftStartX + maxLeftWidth + spacing;
    int rightStartY = centerY - sprite2_height + 1 + offsetY;
    //coordenates to start printing
    int lines = max(sprite1_height, sprite2_height);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //a for util the longest line to make the sprites alight from the bottom
    for (int i = 0; i < lines; i++) {
        if (i < sprite1_height) {
            const string& line = OP_SPRITE.Sprite[i];
            COORD pos = { (SHORT)leftStartX, (SHORT)(leftStartY + i) };
            SetConsoleCursorPosition(hConsole, pos);
            for (char ch : line) {
                if (ch != ' ') {
                    cout << "\033[48;5;" << spritesID[ch] << "m " << RESET; //if is not an empty space just print it
                } else {
                    cout << "\033[C"; //move the cursor to the next space
                }
            }
        }
        //an move the cursor each of the

        if (i < sprite2_height) {
            const string& line = CPU_SPRITE.Sprite[i];
            COORD pos = { (SHORT)rightStartX, (SHORT)(rightStartY + i) };
            SetConsoleCursorPosition(hConsole, pos);
            for (char ch : line) {
                if (ch != ' ') {
                    cout << "\033[48;5;" << spritesID[ch] << "m " << RESET; //same as before
                } else {
                    cout << "\033[C"; //same as before
                }
            }
        }
    }
    int leftEndY = leftStartY + sprite1_height;
    int rightEndY = rightStartY + sprite2_height;
    bottomline = max(leftEndY, rightEndY);
}


int PrintSelectionMenu(const vector<string>& names, const vector<string>& typeNames, int boxLeftCol, int boxTopRow, int boxWidth) {
    int consoleRows, consoleCols;
    GetConsoleSize(consoleRows, consoleCols);
    //print the white dialog
    int dialogueHeight = 10;
    int selectedIndex = 0;
    int startCol = boxLeftCol + 4;
    int startRow = boxTopRow + 2;
    int colSpacing = 25;
    int rowSpacing = 3;
    //show the menu options
    auto printOptions = [&]() {
        for (int i = 0; i < names.size(); i++) {
            int row = startRow + (i / 2) * rowSpacing;
            int col = startCol + (i % 2) * colSpacing;
            cout << "\033[" << row << ";" << col << "H";

            string name = names[i].substr(0, 25); 
            int padding = max(0, 14 - (int)name.size());
            string paddedName = name + string(padding, ' ');

            if (i == selectedIndex)
                cout << BG_GREEN << FG_WHITE << "> " << paddedName << RESET;
            else
                cout << BG_WHITE << FG_BLACK << "  " << paddedName << RESET;
        }
    };

    printOptions();

    while (true) {
        //print the descriptions to the right
        int typeBoxCol = boxLeftCol + boxWidth + 60;
        if (typeBoxCol + 30 >= consoleCols) {
            typeBoxCol = consoleCols - 30;
        }
        int typeBoxRow = boxTopRow;

        for (int i = 0; i < dialogueHeight; i++) {
            cout << "\033[" << (typeBoxRow + i) << ";" << typeBoxCol << "H";
            cout << BG_WHITE << string(28, ' ') << RESET;
        }

        cout << "\033[" << (typeBoxRow + 2) << ";" << (typeBoxCol + 2) << "H";
        cout << BG_WHITE << FG_BLACK << "TYPE: " << typeNames[selectedIndex] << RESET;

        int key = _getch();
        if (key == 224) {
            int arrow = _getch();
            if (arrow == 72 && selectedIndex >= 2) selectedIndex -= 2;
            else if (arrow == 80 && selectedIndex + 2 < names.size()) selectedIndex += 2;
            else if (arrow == 75 && selectedIndex % 2 == 1) selectedIndex--;
            else if (arrow == 77 && selectedIndex % 2 == 0 && selectedIndex + 1 < names.size()) selectedIndex++;
        } else if (key == '\r') {
            break;
        }

        printOptions();
    }

    return selectedIndex;
}


void MovesMenu(int SivarmonSelected, int Enemy, bool& que, int& seleccion) {
    //show the moves menu
    TiposDataBase OP_TYPES = TiposCall(SivarmonSelected);
    MovimientosDataBase OP_MOVES = MovimientosCall(SivarmonSelected);
    SivarmonDataBase OP_INFO = SivarmonesCall(SivarmonSelected);
    int consoleRows, consoleCols;
    GetConsoleSize(consoleRows, consoleCols);
    //call all the files needed
    int dialogueHeight = 10;
    int boxTopRow = bottomline + 7; 
    int optionBoxWidth = 20;
    int maxLineLength = consoleCols - 35;
    int totalBoxWidth = maxLineLength + optionBoxWidth;
    int boxLeftCol = (consoleCols - totalBoxWidth) / 2;
    //show the background
    for(int i = 0; i < dialogueHeight; i++){
        cout << "    " << RESET << "\033[" << (boxTopRow + i) << ";" << boxLeftCol << "H";
        cout << RESET << BG_WHITE << string(maxLineLength, ' ') << RESET;
    }

    cout << "\033[" << (boxTopRow + 5) << ";" << (boxLeftCol + 3 )<< "H";
    cout << BG_WHITE << FG_BLACK << "What will "<< OP_INFO.nombre << " do?" << RESET;

    vector<string> options = { "ATTACK", "OBJECT" };
    int selected = 0;

    int optionBoxCol = boxLeftCol + maxLineLength;

    for (int i = 0; i < dialogueHeight; i++) {
        cout << "\033[" << (boxTopRow + i) << ";" << optionBoxCol << "H";
        cout << BG_WHITE << string(optionBoxWidth, ' ') << RESET;
    }

    int optionStartCol = optionBoxCol;
    int optionStartRow = boxTopRow;
    //show the options
    auto printOptions = [&]() {
        for (int i = 0; i < dialogueHeight; i++) {
            cout << "\033[" << (optionStartRow + i) << ";" << optionStartCol << "H";
            if (i < options.size()) {
                if (i == selected)
                    cout << BG_GREEN << FG_WHITE << "> " << options[i] << RESET;
                else
                    cout << BG_WHITE << FG_BLACK << "  " << options[i] << RESET;
            } else {
                cout << BG_WHITE << string(optionBoxWidth - 1, ' ') << RESET;
            }
        }
    };

    printOptions();

    while (true) {
        int key = _getch();
        if (key == 224) { 
            int arrow = _getch();
            if (arrow == 72) {
                selected = (selected - 1 + options.size()) % options.size();
            }
            else if (arrow == 80) {
                selected = (selected + 1) % options.size();
            }
        }
        else if (key == '\r') { 
            break;
        }
        printOptions();
    }
    //reset all by printing again
    for(int i = 0; i < dialogueHeight; i++){
       cout << "    " << RESET << "\033[" << (boxTopRow + i) << ";" << boxLeftCol << "H";
       cout << RESET << BG_WHITE << string(maxLineLength, ' ') << RESET;
    }
    cout << "\033[" << (boxTopRow + 5) << ";" << (boxLeftCol + 3 )<< "H";

    for (int i = 0; i < dialogueHeight; i++) {
        cout << "\033[" << (boxTopRow + i) << ";" << optionBoxCol << "H";
        cout << BG_WHITE << string(optionBoxWidth, ' '); 
    }
    int moveBoxLeftCol = boxLeftCol;
    int moveBoxTopRow = boxTopRow;
    int moveBoxWidth = maxLineLength;

    if (selected == 0) { //if its a move selected
        vector<string> moveNames;
        vector<string> moveTypeNames;

        for (int i = 0; i < 4; i++) {
            MovimientosDataBase move = MovimientosCall(OP_INFO.idMovimientos[i]);
            moveNames.push_back(move.nombre);

            TiposDataBase typeInfo = TiposCall(move.idTipo);
            moveTypeNames.push_back(typeInfo.nombre);
        }

        int selectedMoveIndex = PrintSelectionMenu(moveNames, moveTypeNames, moveBoxLeftCol, moveBoxTopRow, moveBoxWidth);
        seleccion = selectedMoveIndex;
        que = true;

    }
    else { //if an object is selected
        int ObjectsID[4] = {1, 2, 3, 4};
        vector<string> ObjectNames;
        vector<string> ObjectDamage;
        map<int, string> ObjectNameType = {
            {1 , "HEAL"},
            {2 , "BUFF DEFENSE"},
            {3 , "BUFF SPEED"},
            {4, "BUFF ATACK"}
        };

        for(int i=0;i<4;i++){
            ObjetosDataBase OP_OBJ = ObjetosCall(ObjectsID[i]);
            ObjectNames.push_back(OP_OBJ.nombre);
            ObjectDamage.push_back(ObjectNameType[OP_OBJ.accion]);
        }
        int selectedObjectIndex = PrintSelectionMenu(ObjectNames, ObjectDamage, moveBoxLeftCol, moveBoxTopRow, moveBoxWidth);
        seleccion = selectedObjectIndex;
        que = false;
    }
}

