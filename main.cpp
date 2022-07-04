#include <iostream>
#include <string.h>

using namespace std;

//DEFINICION DE TIPOS DE DATOS
typedef char t_cadena[50];
typedef struct t_jugador{
    t_cadena nombre;
    t_cadena alias;
    int partidasJugadas=0;
    int puntaje=0;
};
const int limite = 50;
typedef t_jugador t_vector[limite];

// MENU PRINCIPAL
void administracionJugadores(t_vector jugadores, int &ocupado);
void generarTablero();

//SUBMENUS
//Submenu de administracion de jugadores
void registrarJugador(t_vector jugadores, int &ocupado);
void modificarDatosJugador(t_vector jugadores, int ocupado);
void listarJugadores(t_vector jugadores, int ocupado);

//MODULOS COMPLEMENTARIOS
bool determinarPrimo(int numero);
bool perteneceFibo(int numero);
bool multiplo11(int num);
bool mutiploTres(int numero);
bool determinarCapicua(int numero);

main(){
    int opcionElegida;
    cout << "********* A H O R C A D I T O *********" << endl;
    cout << "1. Administrar jugadores" << endl;
    cout << "2. Generar tablero de juego" << endl;
    cout << "3. Jugar" << endl;
    cout << "4. Ranking de jugadores" << endl;
    cout << "5. Salir" << endl;
    cout << "***************************************" << endl;
    cout << "Elija una opcion: ";
    cin >> opcionElegida;
}

/* ---------- MODULOS ---------- */

// MENU PRINCIPAL
void administracionJugadores(t_vector jugadores, int &ocupado){
    int opcionElegida;
    do{
        cout << "***** Administrar Jugadores *****" << endl;
        cout << "1. Registrar jugador" << endl;
        cout << "2. Modificar datos del jugador" << endl;
        cout << "3. Listar jugadores" << endl;
        cout << "4. Salir" << endl;
        cout << "*********************************" << endl;
        cout << "Elija una opcion: ";
        cin >> opcionElegida;
        switch(opcionElegida){
            case 1:
                registrarJugador(jugadores, ocupado);
                break;
            case 2:
                modificarDatosJugador(jugadores, ocupado);
                break;
            case 3:
                listarJugadores(jugadores, ocupado);
                break;
            case 4:
                cout << "Volviendo al menu principal" << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }while (opcionElegida != 4);
}
void generarTablero(){

}

//SUBMENUS
//Submenu de administracion de jugadores
void registrarJugador(t_vector jugadores, int &ocupado){
    if (ocupado == limite-1)
        cout << "Ya no se pueden registrar mas jugadores" << endl;
    else{
        ocupado = ocupado + 1;
        cout << "REGISTRANDO JUGADOR, INGRESE DATOS" << endl;
        cout << "Nombre: ";
        fflush(stdin);
        cin >> jugadores[ocupado].nombre;
        cout << "Alias: ";
        fflush(stdin);
        cin >> jugadores[ocupado].alias;
        cout << "REGISTRO EXITOSO" << endl;
    }
}
void modificarDatosJugador(t_vector jugadores, int ocupado){
    if (ocupado == -1)
        cout << "No hay jugadores registrados" << endl;
    else{
        t_cadena jugadorBuscado;
        cout << "Ingrese alias del jugador a modificar datos" << endl;
        cin >> jugadorBuscado;
        // Realizar busqueda secuencial
        int i=0;
        bool jugadorEncontrado = false;
        char eleccion;
        while(i<ocupado && jugadorEncontrado == false){
            if (strcmp(jugadorBuscado, jugadores[i].alias) == 0){
                /* Si el jugador se encontro en base al alias, preguntar al usuario
                si desea modificarlo o buscar otra coincidencia (esto es por la razon
                de que puede aparecer mas de un jugador con el mismo alias*/
                cout << "Se encontro el jugador con los siguientes datos" << endl;
                cout << "Nombre: " << jugadores[ocupado].nombre << endl;
                cout << "Alias: " << jugadores[ocupado].alias << endl;
                cout << "Partidas Jugadas: " << jugadores[ocupado].partidasJugadas << endl;
                cout << "Puntaje: " << jugadores[ocupado].puntaje << endl;
                cout << "¿Desea modificarlo o seguir buscando jugadores? s/n" << endl;
                do{
                    cin >> eleccion;
                    if (eleccion != 's' || eleccion != 'n')
                        cout << "Por favor, ingrese una opcion valida" << endl;
                }while (eleccion != 's' || eleccion != 'n');
                if (eleccion == 's'){
                    jugadorEncontrado = true;
                    cout << "INGRESE LOS NUEVOS DATOS" << endl;
                    cout << "Nombre: ";
                    fflush(stdin);
                    cin >> jugadores[ocupado].nombre;
                    cout << "Alias: ";
                    fflush(stdin);
                    cin >> jugadores[ocupado].alias;
                    cout << "EDICION REALIZADO CON EXITO" << endl;
                }
                else
                    i = i + 1;
            }
        }
        if (jugadorEncontrado == false)
            cout << "No se encontraron coincidencias, fin de la busqueda" << endl;
    }
}
void listarJugadores(t_vector jugadores, int ocupado){
    if (ocupado == -1)
        cout << "No hay jugadores registrados" << endl;
    else{
        cout << "LISTA DE JUGADORES" << endl;
        cout << "ALIAS          NOMBRE          PARTIDAS JUGADAS            PUNTAJE" << endl;
        for(int i=0; i<=ocupado; i++){
            cout << jugadores[i].alias << "    " << jugadores[i].nombre << "    " << jugadores[i].partidasJugadas << "    " << jugadores[i].puntaje << endl; 
        }
    }
}


//MODULOS COMPLEMENTARIOS
bool determinarPrimo(int numero){
    int cantidadDivisores = 1;
    for (int x=2; x<numero; x++){
        if (numero % x == 0)
            cantidadDivisores = cantidadDivisores + 1;
    }
    if (cantidadDivisores > 1){
        return false;
    }
    else{
        return true;
    }
}
bool perteneceFibo(int numero){
    int limite, x1=1, x2=1, serie=1;
    limite = numero;
    for (int x = 1; x < limite; x++){
        serie = x1 + x2;
        x1 = x2;
        x2 = serie;
        if (serie == numero){
            return true;
            break;
        }
        else if (serie > numero){
            return false;
            break;
        }
    }
}
bool multiplo11(int num){
    int resto = 0, cociente = 0, suma = 0, i, sumaPar = 0, sumaImpar = 0, diferencia = 0;
    bool finalizacion, unDigito;
    if (num > 9)
        unDigito = false;
    else{
        unDigito = true;
        diferencia = num;

    }
    // Reducir el numero
    while (unDigito == false){
        i = 0;
        do{
            resto = num % 10;
            cociente = num / 10;
            if (cociente == 0){
                finalizacion = true;
            }
            else{
                finalizacion = false;
            }
            num = cociente;
            suma = suma + resto;
            if (i % 2 != 0){
                sumaPar = sumaPar + resto;
            }
            else{
                sumaImpar = sumaImpar + resto;
            }
            i = i + 1;
        } while (!finalizacion);
        diferencia = abs(sumaPar - sumaImpar);
        cout << "|" << sumaPar << " - " << sumaImpar << "| = " << diferencia << endl;
        if (diferencia > 9){
            unDigito = false;
            num = diferencia;
            suma = 0;
            sumaPar = 0;
            sumaImpar = 0;
        }
        else{
            unDigito = true;
        }
    }
    if (diferencia == 0){
        return true;
    }
    else{
        return false;
    }
}
bool mutiploTres(int numero){
    bool unDigito;
    int resto=0, suma=0, cociente=0;

    if (numero > 9)
        unDigito = false;
    else{
        unDigito = true;
        suma = numero;
    }

    while (!unDigito){
        do{
            resto = numero % 10;
            cociente = numero / 10;
            numero = cociente;
            suma = suma + resto;
        }while(resto != 0);
        if (suma > 9){
            unDigito = false;
            numero = suma;
            suma = 0;
        }
        else
            unDigito = true;
    }

    if (suma == 3 || suma == 6 || suma == 9)
        return true;
    else
        return false;
}
bool determinarCapicua(int numero){
    int digito, cantidadDigitos=0, numeroInverso=0, numeroOriginal=numero;
    do{
        digito = numero % 10;
        numeroInverso = (numeroInverso*10)+digito;
        numero = numero/ 10;
        cantidadDigitos = cantidadDigitos + 1;
    }while(numero != 0);
    if (numeroOriginal == numeroInverso)
        return true;
    else
        return false;
}

