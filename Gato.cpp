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
        cout << "\nNumeros de posicion:\n";
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
    
    void cambiarTurno() {
        if (jugadorActual == 'X') {
            jugadorActual = 'O';
        } else {
            jugadorActual = 'X';
        }
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
        int movimientos = 0;
        
        while (movimientos < 9) {
            mostrarTablero();
            int pos = pedirMovimiento();
            hacerMovimiento(pos);
            cambiarTurno();
            movimientos++;
        }
        
        mostrarTablero();
        cout << "Fin del juego!\n";
    }
};

int main() {
    cout << "=== JUEGO DEL GATO ===\n";
    cout << "Version inicial\n";
    
    Gato juego;
    juego.jugar();
    
    return 0;
}