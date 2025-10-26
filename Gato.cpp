#include <iostream>
#include <vector>

using namespace std;

class Gato {
private:
    vector<vector<char>> tablero;
    char jugadorActual;
    
public:
    Gato() {
        tablero = vector<vector<char>>(3, vector<char>(3, ' '));
        jugadorActual = 'X';
    }
    
    void mostrarTablero() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << "\n";
            if (i < 2) {
                cout << "---|---|---\n";
            }
        }
        cout << "\nPosiciones:\n";
        cout << " 1 | 2 | 3 \n";
        cout << "---|---|---\n";
        cout << " 4 | 5 | 6 \n";
        cout << "---|---|---\n";
        cout << " 7 | 8 | 9 \n\n";
    }
    
    bool esMovimientoValido(int pos) {
        if (pos >= 1 && pos <= 9) {
            int fila = (pos - 1) / 3;
            int columna = (pos - 1) % 3;
            return tablero[fila][columna] == ' ';
        }
        return false;
    }
    
    void hacerMovimiento(int pos) {
        int fila = (pos - 1) / 3;
        int columna = (pos - 1) % 3;
        tablero[fila][columna] = jugadorActual;
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
    
    void cambiarTurno() {
        if (jugadorActual == 'X') {
            jugadorActual = 'O';
        } else {
            jugadorActual = 'X';
        }
    }
    
    void reiniciarJuego() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                tablero[i][j] = ' ';
            }
        }
        jugadorActual = 'X';
    }
    
    int pedirMovimiento() {
        int posicion = 0;
        cout << "Turno del jugador " << jugadorActual << ". Elige posicion (1-9): ";
        cin >> posicion;
        
        while (!esMovimientoValido(posicion)) {
            cout << "Movimiento no valido. Intenta de nuevo: ";
            cin >> posicion;
        }
        
        return posicion;
    }
    
    void jugar() {
        char ganador = ' ';
        
        while (ganador == ' ' && !tableroLleno()) {
            mostrarTablero();
            int pos = pedirMovimiento();
            hacerMovimiento(pos);
            ganador = verificarGanador();
            
            if (ganador == ' ') {
                cambiarTurno();
            }
        }
        
        mostrarTablero();
        
        if (ganador != ' ') {
            cout << "¡El jugador " << ganador << " ha ganado!\n";
        } else {
            cout << "¡Es un empate!\n";
        }
    }
};

bool jugarOtraVez() {
    char respuesta;
    cout << "\n¿Quieres jugar otra vez? (s/n): ";
    cin >> respuesta;
    return (respuesta == 's' || respuesta == 'S');
}

int main() {
    cout << "=== JUEGO DEL GATO ===\n";
    
    Gato juego;
    
    do {
        juego.reiniciarJuego();
        juego.jugar();
    } while (jugarOtraVez());
    
    cout << "¡Gracias por jugar!\n";
    
    return 0;
}