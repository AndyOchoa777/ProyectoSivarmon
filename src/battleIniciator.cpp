#include "DataBaseOutput.h"
using namespace std;
int main()
{  


    PlayerNick probador;
    probador.nick = "loco";
    probador.puntos = 40;

    Tabla(probador);

    vector<PuntuajesDataBase> Tabloron;
    EliminarAlguien("nuevo");
    Tabloron = TablaCall();
    

    for (int i = 0; i < Tabloron.size(); i++)
    {
        cout << Tabloron[i].orden << " || " << Tabloron[i].nickname << " || " << Tabloron[i].puntos << endl;
    }
    


    cout<<"Goodbye jojo";
   
    

    

    return 0;
}
