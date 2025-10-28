#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Juego del Gato - Proyecto Final
// Implementacion completa con interfaz de consola
// Modos: Jugador vs Jugador, Jugador vs CPU

class Gato {
private:
    vector<vector<char>> tablero;
    char jugadorActual;
    bool modoJuego;
    int victoriasX;
    int victoriasO;
    int empates;
    
public:
    Gato() {
        tablero = vector<vector<char>>(3, vector<char>(3, ' '));
        jugadorActual = 'X';
        modoJuego = true;
        victoriasX = 0;
        victoriasO = 0;
        empates = 0;
        srand(time(0));
    }
    
    void mostrarTablero() {
        system("clear");
        
        cout << "\n===== JUEGO DEL GATO =====" << endl;
        cout << "Puntuacion: X=" << victoriasX << " | O=" << victoriasO << " | Empates=" << empates << endl;
        cout << "Turno del jugador: " << jugadorActual << "\n" << endl;
        
        cout << "  " << tablero[0][0] << "  |  " << tablero[0][1] << "  |  " << tablero[0][2] << "  " << endl;
        cout << "_____|_____|_____" << endl;
        cout << "  " << tablero[1][0] << "  |  " << tablero[1][1] << "  |  " << tablero[1][2] << "  " << endl;
        cout << "_____|_____|_____" << endl;
        cout << "  " << tablero[2][0] << "  |  " << tablero[2][1] << "  |  " << tablero[2][2] << "  " << endl;
        
        cout << "\nReferencia de posiciones:" << endl;
        cout << "  1  |  2  |  3  " << endl;
        cout << "_____|_____|_____" << endl;
        cout << "  4  |  5  |  6  " << endl;
        cout << "_____|_____|_____" << endl;
        cout << "  7  |  8  |  9  " << endl;
        cout << endl;
    }
    
    bool esMovimientoValido(int posicion) {
        if (posicion < 1 || posicion > 9) {
            return false;
        }
        
        int fila = (posicion - 1) / 3;
        int columna = (posicion - 1) % 3;
        
        return tablero[fila][columna] == ' ';
    }
    
    void hacerMovimiento(int posicion, char jugador) {
        int fila = (posicion - 1) / 3;
        int columna = (posicion - 1) % 3;
        tablero[fila][columna] = jugador;
    }
    
    char verificarGanador() {
        for (int i = 0; i < 3; i++) {
            if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != ' ') {
                return tablero[i][0];
            }
        }
        
        for (int j = 0; j < 3; j++) {
            if (tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j] && tablero[0][j] != ' ') {
                return tablero[0][j];
            }
        }
        
        if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != ' ') {
            return tablero[0][0];
        }
        
        if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != ' ') {
            return tablero[0][2];
        }
        
        return ' ';
    }
    
    bool tableroLleno() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tablero[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
    
    int obtenerEntradaJugador() {
        int posicion;
        
        while (true) {
            cout << "Jugador " << jugadorActual << ", elige tu posicion (1-9): ";
            cin >> posicion;
            
            if (cin.fail()) {
                cout << "Error: Ingresa solo numeros del 1 al 9." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            
            if (esMovimientoValido(posicion)) {
                return posicion;
            } else {
                cout << "Esa posicion ya esta ocupada o es invalida. Intenta otra!" << endl;
            }
        }
    }
    
    int obtenerMovimientoCPU() {
        cout << "CPU esta pensando..." << endl;
        
        // Intentar ganar
        for (int i = 1; i <= 9; i++) {
            if (esMovimientoValido(i)) {
                hacerMovimiento(i, 'O');
                if (verificarGanador() == 'O') {
                    int fila = (i - 1) / 3;
                    int columna = (i - 1) % 3;
                    tablero[fila][columna] = ' ';
                    return i;
                }
                int fila = (i - 1) / 3;
                int columna = (i - 1) % 3;
                tablero[fila][columna] = ' ';
            }
        }
        
        // Bloquear al oponente
        for (int i = 1; i <= 9; i++) {
            if (esMovimientoValido(i)) {
                hacerMovimiento(i, 'X');
                if (verificarGanador() == 'X') {
                    int fila = (i - 1) / 3;
                    int columna = (i - 1) % 3;
                    tablero[fila][columna] = ' ';
                    return i;
                }
                int fila = (i - 1) / 3;
                int columna = (i - 1) % 3;
                tablero[fila][columna] = ' ';
            }
        }
        
        // Tomar el centro si esta disponible
        if (esMovimientoValido(5)) {
            return 5;
        }
        
        // Tomar una esquina
        vector<int> esquinas = {1, 3, 7, 9};
        for (int esquina : esquinas) {
            if (esMovimientoValido(esquina)) {
                return esquina;
            }
        }
        
        // Tomar cualquier posicion disponible
        for (int i = 1; i <= 9; i++) {
            if (esMovimientoValido(i)) {
                return i;
            }
        }
        
        return -1;
    }
    
    void cambiarTurno() {
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }
    
    void reiniciarTablero() {
        tablero = vector<vector<char>>(3, vector<char>(3, ' '));
        jugadorActual = 'X';
    }
    
    void reiniciarJuegoCompleto() {
        reiniciarTablero();
        victoriasX = 0;
        victoriasO = 0;
        empates = 0;
    }
    
    void establecerModoJuego(bool modo) {
        modoJuego = modo;
    }
    
    void mostrarEstadisticas() {
        cout << "\nESTADISTICAS:" << endl;
        cout << "=============" << endl;
        cout << "Victorias X: " << victoriasX << endl;
        cout << "Victorias O: " << victoriasO << endl;
        cout << "Empates: " << empates << endl;
        cout << "Total partidas: " << (victoriasX + victoriasO + empates) << endl;
        
        if (victoriasX > victoriasO) {
            cout << "El jugador X va ganando!" << endl;
        } else if (victoriasO > victoriasX) {
            if (modoJuego) {
                cout << "El jugador O va ganando!" << endl;
            } else {
                cout << "La CPU va ganando!" << endl;
            }
        } else {
            cout << "Van empatados!" << endl;
        }
    }
    
    void jugar() {
        char ganador = ' ';
        int posicion;
        
        while (ganador == ' ' && !tableroLleno()) {
            mostrarTablero();
            
            if (jugadorActual == 'X' || modoJuego) {
                posicion = obtenerEntradaJugador();
            } else {
                posicion = obtenerMovimientoCPU();
                cout << "CPU eligio la posicion: " << posicion << endl;
                cout << "Presiona Enter para continuar...";
                cin.ignore();
                cin.get();
            }
            
            hacerMovimiento(posicion, jugadorActual);
            ganador = verificarGanador();
            
            if (ganador == ' ') {
                cambiarTurno();
            }
        }
        
        mostrarTablero();
        
        if (ganador != ' ') {
            if (ganador == 'X') {
                cout << "FELICIDADES! El Jugador X ha ganado!" << endl;
                victoriasX++;
            } else {
                if (modoJuego) {
                    cout << "FELICIDADES! El Jugador O ha ganado!" << endl;
                } else {
                    cout << "La CPU ha ganado!" << endl;
                }
                victoriasO++;
            }
        } else {
            cout << "Es un empate!" << endl;
            empates++;
        }
    }
};

void mostrarMenuPrincipal() {
    system("clear");
    cout << "\n=============================" << endl;
    cout << "      JUEGO DEL GATO" << endl;
    cout << "=============================" << endl;
    cout << "1. Jugador vs Jugador" << endl;
    cout << "2. Jugador vs CPU" << endl;
    cout << "3. Ver estadisticas" << endl;
    cout << "4. Reiniciar puntuacion" << endl;
    cout << "5. Salir" << endl;
    cout << "=============================" << endl;
    cout << "Selecciona una opcion (1-5): ";
}



int obtenerOpcionMenu() {
    int opcion;
    
    while (true) {
        cin >> opcion;
        
        if (cin.fail()) {
            cout << "Error: Solo numeros. Intenta de nuevo: ";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        
        if (opcion >= 1 && opcion <= 5) {
            return opcion;
        } else {
            cout << "Opcion invalida. Elige entre 1 y 5: ";
        }
    }
}

bool jugarOtraPartida() {
    char opcion;
    cout << "\nQuieres jugar otra partida? (s/n): ";
    cin >> opcion;
    return (opcion == 's' || opcion == 'S');
}

int main() {
    Gato juego;
    int opcionMenu;
    bool salirJuego = false;
    
    cout << "Bienvenido al Juego del Gato!" << endl;
    cout << "Presiona Enter para continuar...";
    cin.get();
    
    while (!salirJuego) {
        mostrarMenuPrincipal();
        opcionMenu = obtenerOpcionMenu();
        
        switch (opcionMenu) {
            case 1:
                juego.establecerModoJuego(true);
                do {
                    juego.reiniciarTablero();
                    system("clear");
                    cout << "MODO: Jugador vs Jugador" << endl;
                    juego.jugar();
                } while (jugarOtraPartida());
                break;
                
            case 2:
                juego.establecerModoJuego(false);
                do {
                    juego.reiniciarTablero();
                    system("clear");
                    cout << "MODO: Jugador vs CPU" << endl;
                    cout << "Tu eres X, la CPU es O." << endl;
                    juego.jugar();
                } while (jugarOtraPartida());
                break;
                
            case 3:
                system("clear");
                juego.mostrarEstadisticas();
                cout << "\nPresiona Enter para volver al menu...";
                cin.ignore();
                cin.get();
                break;
                
            case 4:
                juego.reiniciarJuegoCompleto();
                system("clear");
                cout << "Puntuacion reiniciada!" << endl;
                cout << "Presiona Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
                
            case 5:
                salirJuego = true;
                cout << "Gracias por jugar!" << endl;
                break;
        }
    }
    
    return 0;
}