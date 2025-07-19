//Creation of the necessary libraries.
#ifndef DATABASEOUTPUT_H
#define DATABASEOUTPUT_H

#include "header.h"
//The order of the structures, is the order of how each group of data is in its respective txt.
//Function to call the information of a specific Sivarmon
SivarmonDataBase SivarmonesCall(int eleccion){
    //Define variables.
    SivarmonDataBase Salida;
    ifstream sivarmons("src/DataBase/Sivarmons.txt");
    //check if the file is open
    if (sivarmons.is_open())
    {
        //Assign the data in each variable correspondingly
        while (sivarmons >> Salida.id >> Salida.nombre >> Salida.idTipo >> Salida.vida >>
             Salida.defensa >> Salida.velocidad >> Salida.idMovimientos[0] >> Salida.idMovimientos[1]
             >> Salida.idMovimientos[2] >> Salida.idMovimientos[3] >> Salida.idSprite)
        {
            //if the id of the Sivarmon matches with the variable that receives the fuction return the struct with the data.
            if (Salida.id == eleccion)
            {
                sivarmons.close();
                return Salida;
            }
        }
        //and if didnt find a variable that matches just return a empty struct
        return SivarmonDataBase{};
        
    }else
    {
        //if didnt open the file return error and a empty struct
        cout<<"Error!";
        return SivarmonDataBase{};
    }
    
    return SivarmonDataBase{};
}


//Function to call the information of a specific move.
MovimientosDataBase MovimientosCall(int eleccion) {
    //Define variables.
    MovimientosDataBase Salida;
    ifstream movimientos("src/DataBase/Movements.txt");

    //check if the file open
    if (movimientos.is_open()) {
         while (movimientos >> Salida.id >> Salida.nombre >> Salida.idTipo >> Salida.accion >> Salida.numero) {

        //Ignore the next character.
        movimientos.ignore(); 

        //define 2 temporaly variables
        string linea, descripcionTotal;

        //We asign lines of text into the variables
        while (getline(movimientos, linea)) {
            //and if find an empty line the loop ends
            if (linea.empty()) 
            {
                break;
            }
            //saves all the lines in one variable
            descripcionTotal += linea + '\n';
        }

        //asign the full text into one of the variables of the structure
        Salida.descripcion = descripcionTotal;

        //When the id matches with the that receives the function, returns the struct with the data and close the file.
        if (Salida.id == eleccion) {
            movimientos.close();
            return Salida;
        }
    }

    //case if doesnt match any id
    cout << "No se encontró el movimiento con ID " << eleccion << endl;
    return {};
    }else
    {
        //case if the file didnt open.
        cout << "Error al abrir el archivo.\n";
        return {};
    }
    

   
}

//Function to call the information for a specific type
TiposDataBase TiposCall(int seleccion){
    //Define variables
    TiposDataBase Salida;
    TiposDataBase TipoDefault; //In the case there a error with the id we are looking for
    bool encontradoDefault = false;
    ifstream Tipos("src/DataBase/Types.txt");
    
    //Check if the file open.
    if (Tipos.is_open())
   {
    //We make a loop to travel all the file and asign the information.
    while (Tipos >> Salida.id >> Salida.nombre) {
        //if the id matches with variable that receives the function then return the information
        if (!encontradoDefault)
        {
            TipoDefault = Salida;
            encontradoDefault = true;
        }
        if (seleccion == Salida.id)
        {
                return Salida;
        }
        
    }
    //Case if the the id doesnt match
    //cout<<"No se encontro el movimiento. ";
        return TipoDefault;
    }
    //Any other case
    return TipoDefault;
    
}

//Function to call a specific sprite from a file
SpritesDataBase SpritesCall(int seleccion){
    //Define variables and set the terminal in UTF8
    SpritesDataBase Salida;
    ifstream Sprites("src/DataBase/Sprites.txt");
    SetConsoleOutputCP(CP_UTF8);

    //Check if the file is open
    if (Sprites.is_open())
    {
        //define some temporaly variable
        string linea;
        string lineaGuardada;
        bool usarGuardada = false;

        while (true) {
            //Check if the lecture reach the final of the file
            if (!usarGuardada) {
                //Also we save the line in the variable
                if (!getline(Sprites, linea)){
                    break;
                }
            } 
            //If the boolean variable if true then means we have alredy another id so we asign
            //that id we save into the variable "linea"
            else {
                linea = lineaGuardada;
                usarGuardada = false;
            }

            //Checks if the line is empty and if the char is numeric
            if (!linea.empty() && linea.find_first_not_of("0123456789") == string::npos)
            {
                //Then we save the line that we check in the variable "IdObtenido"
                //Then we define a vector that is where we gonna temporaly store the sprite
                int idObtenido = stoi(linea);
                vector<string> spriteTemporal;

                //We get the sprite line by line with this loop
                while (getline(Sprites, linea))
                {
                    //If the line if empty means that we reach the end of the sprite so we break the loop
                    if (linea.empty())
                    {
                        break;
                    }

                    //And if the line is a digit then means that we reach other sprite so
                    //we save the number of line and makes true the boolean variable for the 
                    //previus conditions.
                    if (!linea.empty() && linea.find_first_not_of("0123456789") == string::npos)
                    {
                       lineaGuardada = linea;
                        usarGuardada = true;
                        break;
                    }

                    //If anything of that happends then just save the line in the vector
                     spriteTemporal.push_back(linea);
                    
                }

                //After the loop ends we check if the id we get matches with the one that the function get
                //if that happends we asign to a structure the data we get from the file.
                if (seleccion == idObtenido)
                {
                    Salida.id = idObtenido;
                    Salida.Sprite = spriteTemporal;
                    break;
                }
                

                             
            }
            
        }

        //Finally we return the struct with the data.
        return Salida;


        
    }else //case if the file didnt open.
    {
        cout<<"No se abrio archivo";
        return SpritesDataBase{};
    }    
}

//Function to call information of a specific objet.
ObjetosDataBase ObjetosCall(int seleccion){

    //Define variables
    ObjetosDataBase Salida;
    ifstream Objetos("src/DataBase/Objets.txt");

    //Check if the file open
    if (Objetos.is_open()) {
        
        //Create a loop that last until the file ends
        while (Objetos >> Salida.id >> Salida.nombre >> Salida.accion >> Salida.numero) {
        //ignore the \n
        Objetos.ignore();

        //Define temporaly variables
        string linea, descripcionTotal;

        //Get the lines of text and store it in one variable
        while (getline(Objetos, linea)) {

            //if the line is empty means that we reach the end of the group of text, meaning that we break the loop
            if (linea.empty()){
                break;
            }
            descripcionTotal += linea + '\n';
        }

        //We save the text into the structure
        Salida.descripcion = descripcionTotal;

        //if the id matches with variable that receives the function then return the information that we save into the structure.
        if (Salida.id == seleccion) {
            Objetos.close();
            return Salida;
        }
    }

    //Case if the id doesnt match
    cout << "No se encontró el movimiento con ID " << seleccion << endl;
    return {};
    }
    //Case if the file didnt open
    else
    {
        cout << "Error al abrir el archivo.\n";
        return {};
    }

}

void Tabla(PlayerNick User){
    ifstream Clasificacion("src/DataBase/Tabla.txt");
    int puesto = 1;
    bool sos = true;
    if (Clasificacion.is_open())
    {
        PuntuajesDataBase Viejos;
        ofstream tempo("src/DataBase/temp.txt");


        while(Clasificacion >> Viejos.orden >> Viejos.nickname >> Viejos.puntos){
           
            if (User.puntos > Viejos.puntos && sos)
            {
                sos = false;
                tempo << puesto << " " << User.nick << " " << User.puntos << endl;
                puesto++;
            }
            
           if(Viejos.nickname != User.nick){
             tempo << puesto << " " << Viejos.nickname << " " << Viejos.puntos << endl;
                puesto++;
            }
                        
        }

        if (sos)
        {
             tempo << puesto << " " << User.nick << " " << User.puntos << endl;
        }

        Clasificacion.close();
        tempo.close();

        remove("src/DataBase/Tabla.txt");
        rename("src/DataBase/temp.txt", "src/DataBase/Tabla.txt");


    }else
    {
        ofstream Creacion("src/DataBase/Tabla.txt");
        if (Creacion.is_open())
        {
            PuntuajesDataBase nuevo;
            nuevo.orden = 1;
            nuevo.nickname = User.nick;
            nuevo.puntos = User.puntos;

            Creacion << nuevo.orden << " " << nuevo.nickname << " " << nuevo.puntos << endl;
            Creacion.close();
        }
        
    }
    
    
}

vector<PuntuajesDataBase> TablaCall(){
    PuntuajesDataBase subjeto;
    vector<PuntuajesDataBase> Tabloide;
    ifstream Tablon("src/DataBase/Tabla.txt");

    if (Tablon.is_open())
    {
        while (Tablon >> subjeto.orden >> subjeto.nickname >> subjeto.puntos)
        {
            Tabloide.push_back(subjeto);
        }

        return Tabloide;



    }
    
    return {};
}

void EliminarAlguien(int nicksito){
    ifstream archivo("src/DataBase/Tabla.txt");
    ofstream tempor("src/DataBase/Temporal.txt");

    PuntuajesDataBase S;
    int puesto = 1;
    if (archivo.is_open() && tempor.is_open()){
        while (archivo >> S.orden >> S.nickname >> S.puntos){
            if (S.orden != nicksito){
            tempor << puesto << " " << S.nickname << " " << S.puntos << endl;
            puesto++;
            }
            
        }

        archivo.close();
        tempor.close();

        remove("src/DataBase/Tabla.txt");
        rename("src/DataBase/Temporal.txt", "src/DataBase/Tabla.txt");

        
    }else{
        //cout<<"nombe ija";
    }
    
}
#endif