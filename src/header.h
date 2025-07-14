#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <map> 
#include <vector>
#include <string.h>
#include <random>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;

//Structs
struct SivarmonDataBase;
struct MovimientosDataBase;
struct TiposDataBase;
struct SpritesDataBase;
struct ObjetosDataBase;

// Funtions:
//Utils and Main menu
void GetConsoleSize(int &rows, int &columns);
void mainPageLogo();
void mostrarMenu(const vector<string>& MainMenu, int choice);
void GameStart();
void About();
void Credits();
//GameStartMenu and dialogue
void StartGameMenu();
void PrintTypewriter(const string& text);
void NotFoundMessage();
void PrintBackgroundDialogue(const string& filename, const map<char, int>& ColorMap, const string& dialogueName);
void RunCharacterMenu();
//BattleInterface
void enableANSIColors();
bool isInOval(int x, int y, int centerX, int centerY, int radiusX, int radiusY);
void drawBackgroundWithOvals();
//FightBackground
int PrintSelectionMenu(const vector<string>& names, const vector<string>& typeNames, int boxLeftCol, int boxTopRow, int boxWidth);
void PrintBattleEnemies(int SivarmonSelected, int Enemy);
void MovesMenu(int SivarmonSelected, int Enemy);
//DataBase
SivarmonDataBase SivarmonesCall(int eleccion);
MovimientosDataBase MovimientosCall(int eleccion);
TiposDataBase TiposCall(int seleccion);
SpritesDataBase SpritesCall(int seleccion);
ObjetosDataBase ObjetosCall(int seleccion);
//Battle
float Efectividades(int& ataque, int& defensa);
int randomNumber();
bool EvaluarVida(int& vida);
void combate(SivarmonDataBase& J1, SivarmonDataBase& E1, vector<MovimientosDataBase>& J1_MoveSet,vector<MovimientosDataBase>& E_MoveSet,
    vector<ObjetosDataBase>& Obj, int& mov_used, bool& turno, float& modif, float& Emodif, bool& exterior, int (&cant)[4], bool& loose, 
    bool& Win, bool& SuperWin, int& V1);
void Battlebucle(int& selected, bool& BattleStill, bool& ItIsMove, float& modificador, float& Enemy_modificador,int (&CantObjetos)[4],
SivarmonDataBase& J1, SivarmonDataBase& E, bool& loose, bool& win, bool& SuperWin, int& VidaOr);

// RESET and styles
const string RESET    = "\033[0m";
const string NEGRITA  = "\033[1m";
const string SUBRAYADO = "\033[4m";
const string INVERSO  = "\033[7m";
const string FLICKERING = "\033[5m";
const string CLEAR_LINE = "\r\033[K";

// Text colors (foreground)
const string FG_BLACK   = "\033[38;5;232m";
const string FG_RED    = "\033[31m";
const string FG_GREEN   = "\033[32m";
const string FG_YELLOW= "\033[33m";
const string FG_BLUE    = "\033[34m";
const string FG_MAGENTA = "\033[35m";
const string FG_CYAN    = "\033[36m";
const string FG_WHITE  = "\033[38;5;15m";
const string FG_VIOLET = "\033[38;5;128m";
const string FG_PINK = "\033[38;5;163m";
const string FG_LIGHTBLUE = "\033[38;5;111m";
const string FG_ORANGE ="\033[38;5;216m";
const string FG_DEEP_BLUE ="\033[38;5;17m";
// BackgroundColors(background)
const string BG_BLACK = "\033[48;5;232m";
const string BG_RED = "\033[41m";
const string BG_GREEN = "\033[42m";
const string BG_YELLOW = "\033[43m";
const string BG_BLUE = "\033[44m";
const string BG_MAGENTA = "\033[45m";
const string BG_CYAN = "\033[46m";
const string BG_WHITE = "\033[48;5;15m";
const string BG_VIOLET = "\033[48;5;128m";
const string BG_PINK = "\033[48;5;163m";
const string BG_LIGHTBLUE = "\033[48;5;111m";
const string BG_ORANGE ="\033[48;5;216m";
const string BG_DEEP_BLUE ="\033[48;5;17m";
//Battle Backgrounds colors
#define BACK_BLACK cout << "\033[48;5;232m" << string(100 * 30, ' ');
#define BACK_BLUE   "\033[48;5;75m"
#define BACK_GREEN  "\033[48;5;70m"
#define BACK_WHITE  "\033[48;5;15m"

#endif
