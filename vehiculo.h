/*
 * Proyecto progra 3
 */

#ifndef VEHICULO_H_
#define VEHICULO_H_

#include <string>
#include <sstream>
using namespace std;


// Clase base: Vehiculo

class Vehiculo {

protected:
    string placa;
    string marca;
    string color;

public:
    // Constructor
    Vehiculo() : placa(""), marca(""), color("") {}

    // Constructor ya con parámetros
    Vehiculo(string pla, string mar, string col)
        : placa(pla), marca(mar), color(col) {}

    // Getters
    string getPlaca() { return placa; }
    string getMarca() { return marca; }
    string getColor() { return color; }

    // getTipo será sobreescrito por cada subclase (sobrescritura)
    string getTipo() { return "vehiculo"; }

  
};


// Subclase: Auto  (herencia de vehiculo)

class Auto : public Vehiculo {

private:
    int numPuertas;

public:
    // Constructor p
    Auto() : Vehiculo(), numPuertas(4) {}

    // Constructor con parámetros 
    Auto(string pla, string mar, string col, int puertas)
        : Vehiculo(pla, mar, col), numPuertas(puertas) {}

    // Getter propio
    int getNumPuertas() { return numPuertas; }

    // Sobreescritura de getTipo
    string getTipo() { return "auto"; }

};


// Subclase: Moto  (herencia de vehiculo)

class Moto : public Vehiculo {

private:
    bool sidecar;

public:
    // Constructor
    Moto() : Vehiculo(), sidecar(false) {}

    // Constructor con parámetros
    Moto(string pla, string mar, string col, bool sid)
        : Vehiculo(pla, mar, col), sidecar(sid) {}

    // Getter 
    bool getSidecar() { return sidecar; }

    // Sobreescritura de getTipo
    string getTipo() { return "moto"; }

};


// Subclase: Camioneta  (herencia de vehiculo)
class Camioneta : public Vehiculo {

private:
    double cargaMax;

public:
    // Constructor por default
    Camioneta() : Vehiculo(), cargaMax(0.0) {}

    // Constructor con parámetros
    Camioneta(string pla, string mar, string col, double carga)
        : Vehiculo(pla, mar, col), cargaMax(carga) {}

    // Getter propio
    double getCargaMax() { return cargaMax; }

    // Sobreescritura de getTipo
    string getTipo() { return "camioneta"; }

};

#endif // VEHICULO_H_
