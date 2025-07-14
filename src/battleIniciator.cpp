#include "battle.h"
using namespace std;
int main()
{   // Definir bien los los valores de mov used
    int eleccion;
    int Movimiento_o_Objeto = 3;

    //Definir fuera del bucle
    float modificador = 0;
    float Enemy_modificador = 0;
    int CantObjetos[4] = {3, 3, 3, 3};
    

    SivarmonDataBase Jugador = SivarmonesCall(1);
    SivarmonDataBase Enemy = SivarmonesCall(3);

    vector<MovimientosDataBase> Jugador_Movimientos(4);
    for (int i = 0; i < 4; i++)
    {
        Jugador_Movimientos[i] = MovimientosCall(Jugador.idMovimientos[i]);
    }

    vector<MovimientosDataBase> Enemy_Movimientos(4);
    for (int i = 0; i < 4; i++)
    {
        Enemy_Movimientos[i] = MovimientosCall(Enemy.idMovimientos[i]);
    }

    vector<ObjetosDataBase> Objetos(4);
    for (int i = 0; i < 4; i++)
    {
        Objetos[i] = ObjetosCall(i+1);
    }
    

    

    cout<<"Goodbye jojo";
   
    

    

    return 0;
}
