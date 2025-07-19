#include "BattleInterface.h"
// #include <random>
using namespace std;

float Efectividades(int& ataque, int& defensa){
     map<pair<int, int>, float> efectividad = {
        {{2, 3}, 1.5f},  // agua vs fuego
        {{2, 4}, 0.5f},  // agua vs planta
        {{2, 5}, 0.3f},  // agua vs psiquico
        {{3, 2}, 0.5f},  // fuego vs agua
        {{3, 4}, 1.5f},  // fuego vs planta
        {{3, 5}, 0.3f},  // fuego vs psiquico
        {{4, 2}, 1.5f},  // planta vs agua
        {{4, 3}, 0.5f},  // planta vs fuego
        {{4, 5}, 0.3f},  // planta vs psiquico
        {{5, 2}, 1.3f},  // psiquico vs agua
        {{5, 3}, 1.3f},  // psiquico vs fuego
        {{5, 4}, 1.3f},  // psiquico vs planta
        
    };

    auto it  = efectividad.find({ataque, defensa});

    
    if (ataque == 1 && defensa == 1){
        return 0.0f;
    }
    if (it != efectividad.end()){
        return it->second;
    }
    return 1.0f; 
}

int randomNumber(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis1(0, 3);
    return dis1(gen);
}

bool EvaluarVida(int& vida){
   if (vida < 1)
    {
        return true;
    }else
    {
        return false;
    }
}

void combate(SivarmonDataBase& J1, SivarmonDataBase& E1, vector<MovimientosDataBase>& J1_MoveSet,
             vector<MovimientosDataBase>& E_MoveSet, vector<ObjetosDataBase>& Obj, int& mov_used,
             bool& turno, float& modif, float& Emodif, bool& exterior, int (&cant)[4],
             bool& loose, bool& Win, bool& SuperWin, int& V1) {

    int EnemyMove = randomNumber();
    int damage_modif = 0;
    int total_damage = 0;

    auto aplicarAccion = [&](SivarmonDataBase& atk, SivarmonDataBase& def, MovimientosDataBase& move,
                             float& atkModif, float& defModif) {
        switch (move.accion) {
            case 1:
                atkModif += Efectividades(move.idTipo, def.idTipo);
                damage_modif = move.numero + (move.numero * atkModif);
                total_damage = damage_modif - (damage_modif * def.defensa);
                total_damage = (total_damage < 0.0) ? 0.5f : total_damage;
                def.vida -= total_damage;

                atkModif = 0;
                break;
            case 2:
                atkModif += move.numero;
                break;
            case 3:
                atk.defensa += move.numero;
                break;
            case 4:
                atk.velocidad += atk.velocidad * move.numero;
                break;
            case 5:
                defModif = max(0.0f, defModif - move.numero);
                break;
            case 6:
                def.defensa = max(0.0f, def.defensa - move.numero);
                break;
            case 7:
                def.velocidad -= def.velocidad * move.numero;
                break;
        }
    };

    auto aplicarObjeto = [&](int idx) {
        if (cant[idx] > 0) {
            cant[idx]--;
            switch (Obj[idx].accion) {
                case 1: J1.vida += Obj[idx].numero; break;
                case 2: J1.defensa += Obj[idx].numero; break;
                case 3: J1.velocidad += Obj[idx].numero; break;
                case 4: modif += Obj[idx].numero; break;
            }
        }
    };

    // Orden de ataque según velocidad
    bool jugadorPrimero = (J1.velocidad >= E1.velocidad);

    if (jugadorPrimero) {
        if (turno) {
            for (auto& move : J1_MoveSet) {
                if (move.id == mov_used) {
                    aplicarAccion(J1, E1, move, modif, Emodif);
                    break;
                }
            }
        } else {
            aplicarObjeto(mov_used);
        }

        if (EvaluarVida(E1.vida)) {
            cout << "Lo mataste";
            exterior = false;
            SuperWin = (J1.vida > V1 * 0.7);
            Win = !SuperWin;
            return;
        }

        aplicarAccion(E1, J1, E_MoveSet[EnemyMove], Emodif, modif);

        if (EvaluarVida(J1.vida)) {
            cout << "Te mataron";
            exterior = false;
            loose = true;
            return;
        }

    } else {
        aplicarAccion(E1, J1, E_MoveSet[EnemyMove], Emodif, modif);

        if (EvaluarVida(J1.vida)) {
            cout << "Te mataron";
            exterior = false;
            loose = true;
            return;
        }

        if (turno) {
            for (auto& move : J1_MoveSet) {
                if (move.id == mov_used) {
                    aplicarAccion(J1, E1, move, modif, Emodif);
                    break;
                }
            }
        } else {
            aplicarObjeto(mov_used);
        }

        if (EvaluarVida(E1.vida)) {
            cout << "Lo mataste";
            exterior = false;
            SuperWin = (J1.vida > V1 * 0.7);
            Win = !SuperWin;
            return;
        }
    }
}

void Battlebucle(int& selected, bool& BattleStill, bool& ItIsMove, float& modificador, float& Enemy_modificador, int (&CantObjetos)[4],
SivarmonDataBase& J1, SivarmonDataBase& E, bool& loose, bool& win, bool& SuperWin, int& VidaOr){

    

    vector<MovimientosDataBase> Jugador_Movimientos(4);
    for (int i = 0; i < 4; i++)
    {
        Jugador_Movimientos[i] = MovimientosCall(J1.idMovimientos[i]);
    }

    vector<MovimientosDataBase> Enemy_Movimientos(4);
    for (int i = 0; i < 4; i++)
    {
        Enemy_Movimientos[i] = MovimientosCall(E.idMovimientos[i]);
    }

    vector<ObjetosDataBase> Objetos(4);
    for (int i = 0; i < 4; i++)
    {
        Objetos[i] = ObjetosCall(i+1);
    }

   if(ItIsMove){
     selected = J1.idMovimientos[selected]; // convertir índice en ID real
   }
    

    
        combate(J1, E,Jugador_Movimientos, Enemy_Movimientos, Objetos,
        selected, ItIsMove, modificador, Enemy_modificador, BattleStill, CantObjetos, loose, win, SuperWin, VidaOr);
    
}
