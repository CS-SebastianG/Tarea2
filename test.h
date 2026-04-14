#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <concepts>

using namespace std;

// Para tipos que se pueden sumar
template<typename T>
concept Addable = requires(T a, T b) {
    a + b;
};

// Para tipos que se pueden dividir
template<typename T>
concept Divisible = requires(T a, size_t n) {
    a / n;
};

// Para contenedores que se pueden recorrer
template<typename C>
concept Iterable = requires(C c) {
    c.begin();
    c.end();
};

// Concept personalizado para comparar
template<typename T>
concept Comparable = requires(T a, T b) {
    a < b;
};

template<Iterable C>
auto sum(const C& container) {
    typename C::value_type resultado{};
    for (const auto& valor : container) {
        resultado = resultado + valor;
    }
    return resultado;
}

template<Iterable C>
auto mean(const C& container) {
    auto total = sum(container);

    int contador = 0;
    for (const auto& _ : container) {
        contador++;
    }

    return total / contador;
}

template<Iterable C>
auto variance(const C& container) {
    auto promedio = mean(container);

    double suma = 0;
    int contador = 0;

    for (const auto& valor : container) {
        double diff = valor - promedio;
        suma = suma + (diff * diff);
        contador++;
    }

    return suma / contador;
}

template<Iterable C>
auto max(const C& container) {
    auto it = container.begin();
    auto mayor = *it;
    ++it;

    for (; it != container.end(); ++it) {
        if (*it > mayor) {
            mayor = *it;
        }
    }
    return mayor;
}

template<Iterable C, typename Func>
auto transform_reduce(const C& container, Func func) {
    typename C::value_type resultado{};
    for (const auto& valor : container) {
        resultado = resultado + func(valor);
    }
    return resultado;
}

template<typename T>
T sum_variadic(T valor) {
    return valor;
}

template<typename T, typename... Rest>
T sum_variadic(T primero, Rest... resto) {
    return primero + sum_variadic(resto...);
}

template<typename T>
double mean_variadic(T valor) {
    return static_cast<double>(valor);
}

template<typename T, typename... Rest>
double mean_variadic(T primero, Rest... resto) {
    // Sumar todos los valores
    double suma = static_cast<double>(primero) + sum_variadic(resto...);
    int cantidad = 1 + sizeof...(resto);
    return suma / cantidad;
}

template<typename T>
double variance_variadic(T valor) {
    return 0;
}

template<typename T, typename... Rest>
double variance_variadic(T primero, Rest... resto) {
    vector<double> valores = {static_cast<double>(primero), static_cast<double>(resto)...};

    double promedio = mean_variadic(primero, resto...);

    double suma_cuadrados = 0;
    for (double v : valores) {
        double diff = v - promedio;
        suma_cuadrados = suma_cuadrados + (diff * diff);
    }

    return suma_cuadrados / valores.size();
}

template<typename T>
T max_variadic(T valor) {
    return valor;
}

template<typename T, typename... Rest>
T max_variadic(T primero, Rest... resto) {
    T max_resto = max_variadic(resto...);
    return (primero > max_resto) ? primero : max_resto;
}

template<typename T>
T procesar(T valor) {
    if constexpr (is_integral_v<T>) {
        // Si es entero, lo duplicamos
        return valor * 2;
    } else {
        // Si es decimal, lo dividimos
        return valor / 2;
    }
}

template<Iterable C>
auto procesar_contenedor(const C& contenedor) {
    vector<typename C::value_type> resultado;
    for (const auto& val : contenedor) {
        resultado.push_back(procesar(val));
    }
    return resultado;
}

#endif