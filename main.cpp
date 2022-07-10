#include <iostream>
#include <string.h>
#include <time.h>


using namespace std;

//DEFINICION DE TIPOS DE DATOS
typedef char t_cadena[50];
typedef struct t_jugador{
    t_cadena nombre;
    t_cadena alias;
    int partidasJugadas=0;
    int puntaje=0;
};
const int LIMITE = 50;
typedef t_jugador t_vector[LIMITE];
const int FILAS = 2, COLUMNAS = 4;
typedef int t_tablero[FILAS][COLUMNAS];
const int digitos = 6;
typedef int t_numero[digitos];
// MENU PRINCIPAL
void administracionJugadores(t_vector jugadores, int &ocupado);
void generarTablero(t_tablero &tableroJuego);
void jugar(t_tablero tableroJuego, int &intentos);


//SUBMENUS
//Submenu de administracion de jugadores
void registrarJugador(t_vector jugadores, int &ocupado);
void modificarDatosJugador(t_vector jugadores, int ocupado);
void listarJugadores(t_vector jugadores, int ocupado);
//Submenu jugar
void probarDigitos(t_tablero tableroJuego, int intentos);
void solicitarPista(t_tablero tableroJuego);
//void arriesgarSolucion(t_tablero tableroJuego);
//MODULOS COMPLEMENTARIOS
bool determinarPrimo(int numero);
bool perteneceFibo(int numero);
bool multiplo11(int num);
bool multiploTres(int numero);
bool determinarCapicua(int numero);
bool digitosDistintos(int numero);
bool determinarPar(int numero);
int generarNumero6Cifras();
int generarNumero5Cifras();
int busquedaJugador(t_vector a, int ocupado, t_cadena buscado);
bool verificarNumeroGenerado(int numero, int x, int i, bool &existeFibo, bool &existeCapicua, bool &existePrimo);
bool verificarTablero(t_tablero tableroJuego);
void ocultarNumero(int numeroJugado, t_numero &numeroOriginal, t_numero numeroOculto);
void verificarDigito(t_numero numeroJugado, t_numero numeroOculto, int ocupado, int digitoJugado);
void revelarNumero(t_numero numeroOriginal, t_numero numeroOculto, int ocupado, int posicionAcertada, int digitoJugado);
bool control(t_numero numeroOriginal, t_numero numeroOculto, int ocupado);

main(){
    srand(time(NULL));
    t_vector jugadores; int ocupado = -1;
    t_tablero tableroJuego; int intentos=5;
    int opcionElegida;
    do{
        system("cls");
        cout << "********* A H O R C A D I T O *********" << endl;
        cout << "1. Administrar jugadores" << endl;
        cout << "2. Generar tablero de juego" << endl;
        cout << "3. Jugar" << endl;
        cout << "4. Ranking de jugadores" << endl;
        cout << "5. Salir" << endl;
        cout << "***************************************" << endl;
        cout << "Elija una opcion: ";
        cin >> opcionElegida;
        switch(opcionElegida){
            case 1:
                administracionJugadores(jugadores, ocupado);
                break;
            case 2:
                generarTablero(tableroJuego);
                for (int i=0; i<FILAS; i++){
                    for (int j=0; j<COLUMNAS; j++){
                        cout << tableroJuego[i][j] << ", ";
                    }
                    cout<<endl;
                }
                system("pause");
                break;
            case 3:
                jugar(tableroJuego, intentos);
                break;
            case 5:
                cout << "Fin de juego" << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                system("pause");
                break;
        }
    }while (opcionElegida != 5);
}

/* ---------- MODULOS ---------- */

// MENU PRINCIPAL
void administracionJugadores(t_vector jugadores, int &ocupado){
    int opcionElegida;
    do{
        system("cls");
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
void generarTablero(t_tablero &tableroJuego){
    /* Este procedimiento cumple la funcion de generar el tablero
       de juego, incorporando la creacion de numeros aleatorios
       que pasaran por una verificacion para comprobar si el numero
       generado es adecuado para el juego.*/
    int aleatorio, c1=0, c2=0;
    bool existeFibo2=false, existeCapicua2=false, existePrimo2=false;
    for (int x=0; x<2; x++){
        for (int i=0; i<4; i++){
            aleatorio = rand() % 2 + 1;
            /* Estos condicionales se encargan de que
               se generen 4 numeros de 6 cifras y otros
               4 numeros de 5 cifras*/
            if (aleatorio == 1){
                if (c1 > 3)
                    aleatorio = 2;
                else
                    c1++;
            }
            else if(aleatorio == 2){
                if (c2 > 3)
                    aleatorio = 1;
                else
                    c2++;
            }
            do{
                /* Dependiendo del numero aleatorio se generara uno
                   de 5 cifras o de 6 cifras*/
                if (aleatorio == 1)
                    tableroJuego[x][i] = generarNumero5Cifras();
                else if (aleatorio == 2)
                    tableroJuego[x][i] = generarNumero6Cifras();
            }while(verificarNumeroGenerado(tableroJuego[x][i], x, i, existeFibo2, existeCapicua2, existePrimo2) == false);
        }
    }
}
void jugar(t_tablero tableroJuego, int &intentos){
    int opcionElegida;
    do{
        system("cls");
        cout << "************* JUGAR *************" << endl;
        cout << "1. Probar digitos" << endl;
        cout << "2. Solicitar pistas" << endl;
        cout << "3. Arriesgar solucion" << endl;
        cout << "4. Salir" << endl;
        cout << "*********************************" << endl;
        cout << "Elija una opcion: ";
        cin >> opcionElegida;
        switch(opcionElegida){
            case 1:
                //probarDigitos(numeroJugado);
                break;
            case 2:
                //solicitarPista(tableroJuego);
                break;
            case 3:
                //arriesgarSolucion(tableroJuego);
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


//SUBMENUS
//Submenu de administracion de jugadores
void registrarJugador(t_vector jugadores, int &ocupado){
    if (ocupado == LIMITE-1){
        cout << "Ya no se pueden registrar mas jugadores" << endl;
        system("pause");
    }
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
        system("pause");
    }
}
void modificarDatosJugador(t_vector jugadores, int ocupado){
    if (ocupado == -1)
        cout << "No hay jugadores registrados" << endl;
    else{
        t_cadena jugadorBuscado;
        cout << "Ingrese alias del jugador a modificar datos" << endl;
        fflush(stdin);
        cin >> jugadorBuscado;
        char eleccion;
        int i = busquedaJugador(jugadores, ocupado, jugadorBuscado);
        if(i != -1){
            cout << "Se encontro el jugador con los siguientes datos" << endl;
                cout << "Nombre: " << jugadores[i].nombre << endl;
                cout << "Alias: " << jugadores[i].alias << endl;
                cout << "Partidas Jugadas: " << jugadores[i].partidasJugadas << endl;
                cout << "Puntaje: " << jugadores[i].puntaje << endl;
                cout << "Desea modificarlo? s/n" << endl;
                do{
                    cin >> eleccion;
                    if (eleccion != 's' && eleccion != 'n')
                        cout << "Por favor, ingrese una opcion valida" << endl;
                }while (eleccion != 's' && eleccion != 'n');
                if (eleccion == 's'){
                    cout << "INGRESE LOS NUEVOS DATOS" << endl;
                    cout << "Nombre: ";
                    fflush(stdin);
                    cin >> jugadores[i].nombre;
                    cout << "Alias: ";
                    fflush(stdin);
                    cin >> jugadores[i].alias;
                    cout << "EDICION REALIZADO CON EXITO" << endl;
                }
                else
                    cout << "Volviendo al menu anterior" << endl;
        }
        else
            cout << "No hay coincidencias" << endl;
    }
    system("pause");
}
void listarJugadores(t_vector jugadores, int ocupado){
    if (ocupado == -1)
        cout << "No hay jugadores registrados" << endl;
    else{
        cout << "LISTA DE JUGADORES" << endl;
        cout << "ALIAS   NOMBRE     PARTIDAS JUGADAS    PUNTAJE" << endl;
        cout << "-----   ------     ----------------    -------" << endl;
        for(int i=0; i<=ocupado; i++){
            cout << jugadores[i].alias << "   " << jugadores[i].nombre << "            " << jugadores[i].partidasJugadas << "                  " << jugadores[i].puntaje << endl; 
        }
        
    }
    system("pause");
}
//Submenu jugar
void probarDigitos(int numeroJugado){
    t_numero numeroOriginal, numeroOculto;
    int ocupado = 4;
    char eleccion;
    ocultarNumero(numeroJugado, numeroOriginal, numeroOculto);
    int digitoJugado;
    do{
        cout << "Ingrese numero: ";
        cin >> digitoJugado;
        verificarDigito(numeroOriginal, numeroOculto, ocupado, digitoJugado);
        cout << "Desea probar otro numero? s/n" << endl;
        do{
            cin >> eleccion;
            if (eleccion != 's' && eleccion != 'n')
                cout << "Por favor, seleccione una opcion valida" << endl;
        }while(eleccion != 's' && eleccion != 'n');

    }while(eleccion == 's');
}
void solicitarPista(int numeroJuego){
     //Numero de 5 cifras
    if (determinarPrimo(numeroJuego) == true)
        cout << "Es un numero primo" << endl;
    if (perteneceFibo(numeroJuego) == true)
        cout << "Pertenece a la serie Fibonacci" << endl;
    if (determinarCapicua(numeroJuego) == true)
        cout << "Es un numero capicua" << endl;
    if (digitosDistintos(numeroJuego) == true)
        cout << "Todos sus digitos son distintos" << endl;
    if (determinarPar(numeroJuego) == true)
        cout << "Es un numero par" << endl;
    else
        cout << "Es un numero impar" << endl;
    if (numeroJuego >= 100000){
        if (multiplo11(numeroJuego) == true)
            cout << "El numero es multiplo de 11" << endl;
        if (multiploTres(numeroJuego) == true)
            cout << "El numero es multiplo  de 3" << endl;
    }
}
/*void arriesgarSolucion(t_tablero tableroJuego){
    int numero;
    cout << "Ingrese la solucion" << endl;
    cin >> numero;
    if (numero == numeroJuego)
        cout << "Acerto" << endl;
    else
        cout << "No acerto" << endl;
}*/
//MODULOS COMPLEMENTARIOS
bool determinarPrimo(int numero){
    int cantidadDivisores = 1;
    for (int x=2; x<numero; x++){
        if (numero % x == 0)
            cantidadDivisores = cantidadDivisores + 1;
    }
    if (cantidadDivisores > 1)
        return false;
    else
        return true;
}
bool perteneceFibo(int numero){
    int limite, x1=1, x2=1, serie=1;
    limite = numero;
    for (int x = 1; x < limite; x++){
        serie = x1 + x2;
        x1 = x2;
        x2 = serie;
        if (serie == numero)
            return true;
        else if (serie > numero)
            return false;
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
bool multiploTres(int numero){
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
bool digitosDistintos(int numero){
    int digito, cociente, cociente2, numero2, digito2;
    while (numero != 0){
        digito = numero % 10;
        numero2 = numero / 10;
        numero = numero / 10;
        while(numero2 != 0){
            digito2 = numero2 % 10;
            numero2 = numero2 / 10;
            if (digito == digito2)
                return false;
        }
    }
    return true;
}
bool determinarPar(int numero){
    if (numero % 2 == 0)
        return true;
    else
        return false;
}
int generarNumero6Cifras(){
    int valor, valor2, random;
    do{
        valor = rand() % 999 + 100; //Genera entre 100 y 999
        valor2 = rand() % 999 + 100; //Genera entre 100 y 999
        random = (valor*1000)+valor2; //Une ambos valores para formar un numero de 6 cifras
        if (random <= 999999 && random > 99999){
            return random;
        }
    }while(!(random <= 999999 && random > 99999));
}
int generarNumero5Cifras(){
    int valor, valor2, random;
    do{
        valor = rand() % 99 + 10; //Genera entre 10 y 99
        valor2 = rand() % 999 + 100; //Genera entre 100 y 999
        random = (valor2*100)+valor; //Une ambos valores para formar un numero de 6 cifras
        if (random <= 99999 && random > 9999){
            return random;
        }
    }while(!(random <= 99999 && random > 9999));
}
int busquedaJugador(t_vector a, int ocupado, t_cadena buscado){
    /* La funcion recibe por parametros un vector, su variable ocupado
       y el elemento buscado. Retorna el indice del elemento cuando este
       pertenece al vector, en caso contrario retornara -1*/
    if (strcmp(buscado, a[ocupado].alias) == 0 && ocupado > -1){
        return ocupado;
    }
    else if(ocupado > -1){
        ocupado = ocupado - 1;
        return busquedaJugador(a, ocupado, buscado);
        
    }
    return -1;
}
bool verificarNumeroGenerado(int numero, int x, int i, bool &existeFibo2, bool &existeCapicua2, bool &existePrimo2){
    if (perteneceFibo(numero) == true){
        existeFibo2 = true;
        return true;
    }
    else if (x >= 1 && existeFibo2 == false){
        return false;
    }
    if (determinarCapicua(numero) == true){
        existeCapicua2 = true;
        return true;
    }
    else if (x >= 1 && existeCapicua2 == false){
        return false;
    }
    if (determinarPrimo(numero) == true){
        existePrimo2 = true;
        return true;
    }
    else if (x >= 1 && existePrimo2 == false){
        return false;
    }
}
bool verificarTablero(t_tablero tableroJuego){
    /* Funcion recibe un tablero para determinar si
       cumple con las condiciones propuestas, de ser asi
       retornara true. De lo contrario retornara false
        Condiciones para tablero aceptable:
        - Al menos un numero primo debe existir
        - Al menos un numero capicua debe existir
        - Al menos un numero perteneciente a serie Fibonacci debe existir
    */
    bool  existePrimo=false, existeCapicua=false, existeFibo=false;
    for (int x=0; x<2; x++){
        for (int i=0; i<4; i++){
            if (determinarPrimo(tableroJuego[x][i]) == true){
                existePrimo = true;
            }
            if (determinarCapicua(tableroJuego[x][i]) == true){
                existeCapicua = true;
            }
            if (perteneceFibo(tableroJuego[x][i]) == true){
                existeFibo = true;
            }
        }
    }
    
    if (existePrimo == true && existeFibo == true && existeCapicua == true)
        return true;
    else
        return false;
}
void ocultarNumero(int numeroJugado, t_numero &numeroOriginal, t_numero numeroOculto){
    /* Este procedimiento coloca los digitos en un vector para ir mostrandolos
       uno por uno una vez acertados, mediante el calculo del
       inverso y digito*/
    int digito, numeroInverso=0, i=-1;
    do{
        digito = numeroJugado % 10;
        numeroInverso = (numeroInverso*10)+digito;
        numeroJugado = numeroJugado/ 10;
    }while(numeroJugado != 0);
    while (numeroInverso != 0){
        digito = numeroInverso % 10;
        numeroInverso = numeroInverso / 10;
        i++;
        numeroOriginal[i] = digito;
        
    }
    for (int x=0; x<=i; x++){
        numeroOculto[x] = '_';
        cout << "_ ";
    }
    cout <<endl;
}
void verificarDigito(t_numero numeroJugado, t_numero numeroOculto, int ocupado, int digitoJugado){
    /* Este procedimiento verificará posicion por posicion si existe una coincidencia
       en el numero oculto (numero en juego) con el digito que introdujo el jugador.
       En caso de verdadero llamara al procedimiento revelarNumero, de lo contrario
       mostrara un mensaje de que fallo y regresara al procedimiento anterior*/
    bool acertado=false;
    int x=0;
    while(x<=ocupado){
        if (digitoJugado == numeroJugado[x]){
            cout << "Has acertado un digito" << endl;
            revelarNumero(numeroJugado, numeroOculto, ocupado, x, digitoJugado);
            acertado = true;
        }
        else if(x == ocupado && acertado == false)
            cout << "No has acertado ningun digito" << endl;
        x++;
    }
    

}
void revelarNumero(t_numero numeroOriginal, t_numero numeroOculto, int ocupado, int posicionAcertada, int digitoJugado){
    /* Este procedimiento recibira 4 argumentos, 2 de ellos muy importantes, el digito que el jugador
       indico y la posicion donde fue acertado el digito para asi mostrarlo en el numeroOculto
       reemplanzado los "_" (representados por su codigo ASCII) por el digito acertado.
       Adiccionalmente este llama a un procedimiento encargado de comprobar si el numero fue acertado
       en su totalidad */
    numeroOculto[posicionAcertada] = digitoJugado;
    for (int x=0; x<=ocupado; x++){
        if (numeroOculto[x] == 95)
            cout << "_ ";
        else
            cout << numeroOculto[x] << " ";
    }
    cout << endl;
    if (control(numeroOriginal, numeroOculto, ocupado) == true){
        cout << "Genial, has acertado el numero" << endl;
        cout << "Introduce 'n' para saltar al siguiente numero" << endl;
    }
}
bool control(t_numero numeroOriginal, t_numero numeroOculto, int ocupado){
    /* Este procedimiento cumple la funcion de verificar si el numero en juego
       fue acertado por el jugador*/
    bool numeroCompletado=true;
    for (int x=0; x<=ocupado; x++){
        if (numeroOriginal[x] != numeroOculto[x])
            numeroCompletado = false;
    }
    if (numeroCompletado == true)
        return true;
    else
        return false;
}