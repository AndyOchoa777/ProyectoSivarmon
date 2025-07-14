#include "DataBaseOutput.h"
using namespace std;

int main()
{
    //Prueba de que funciona
    int prueba = 21;
    cin>>prueba;

    TiposDataBase Jugador = TiposCall(prueba);

    cout<<" --- " << Jugador.id << " - " << Jugador.nombre;

    return 0;
}
