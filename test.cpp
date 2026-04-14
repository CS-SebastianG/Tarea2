#include <iostream>
#include <vector>
#include <string>
#include "test.h"

using namespace std;

// Una clase simple para probar
class Punto {
private:
    double x, y;
public:
    Punto(double x = 0, double y = 0) : x(x), y(y) {}

    Punto operator+(const Punto& otro) const {
        return Punto(x + otro.x, y + otro.y);
    }

    Punto operator/(size_t n) const {
        return Punto(x / n, y / n);
    }

    bool operator<(const Punto& otro) const {
        return (x + y) < (otro.x + otro.y);
    }

    void print() const {
        cout << "(" << x << "," << y << ")";
    }
};

int main() {
    cout << "PRUEBAS \n\n";

    cout << "1. Probando con enteros:\n";
    vector<int> numeros = {1, 2, 3, 4, 5};

    cout << "   Suma: " << sum(numeros) << endl;
    cout << "   Media: " << mean(numeros) << endl;
    cout << "   Varianza: " << variance(numeros) << endl;
    cout << "   Maximo: " << max(numeros) << endl;

    cout << "\n2. Probando con doubles:\n";
    vector<double> decimales = {1.5, 2.5, 3.5, 4.5};

    cout << "   Suma: " << sum(decimales) << endl;
    cout << "   Media: " << mean(decimales) << endl;
    cout << "   Maximo: " << max(decimales) << endl;

    cout << "\n3. transform_reduce (suma de cuadrados):\n";
    auto cuadrados = transform_reduce(decimales, [](double x) {
        return x * x;
    });
    cout << "   Resultado: " << cuadrados << endl;

    cout << "\n4. Funciones variadicas:\n";
    cout << "   sum_variadic: " << sum_variadic(1, 2, 3, 4) << endl;
    cout << "   mean_variadic: " << mean_variadic(1, 2, 3, 4) << endl;
    cout << "   variance_variadic: " << variance_variadic(1, 2, 3, 4) << endl;
    cout << "   max_variadic: " << max_variadic(1, 2, 3, 4) << endl;

    cout << "\n5. if constexpr:\n";
    cout << "   procesar(5): " << procesar(5) << endl;
    cout << "   procesar(5.5): " << procesar(5.5) << endl;

    auto procesados = procesar_contenedor(numeros);
    cout << "   Vector procesado: ";
    for (int v : procesados) {
        cout << v << " ";
    }
    cout << endl;

    cout << "\n6. Probando con clase Punto:\n";
    vector<Punto> puntos = {Punto(1,2), Punto(3,4), Punto(5,6)};

    cout << "   Suma: ";
    sum(puntos).print();
    cout << endl;

    cout << "   Media: ";
    mean(puntos).print();
    cout << endl;

    cout << "\n(Los ejemplos que deben compilar y no lo hacen están comentados)\n\n";

    // Casos que deben compilar y NO compilar
    /*
    // CASO 1: string no se puede sumar
    vector<string> palabras = {"Hola", "Mundo"};
    auto error1 = sum(palabras);  // ERROR: string no tiene operador +

    // CASO 2: string no se puede dividir
    auto error2 = mean(palabras);  // ERROR: string no tiene operador /

    // CASO 3: int no es iterable
    int x = 5;
    auto error3 = sum(x);  // ERROR: int no tiene begin/end

    // CASO 4: Clase sin operador <
    class Prueba {
        int valor;
    };
    vector<Prueba> pruebas;
    auto error4 = max(pruebas);  // ERROR: Prueba no tiene operador <
    */

    cout << "Pruebas completadas\n";

    return 0;
}