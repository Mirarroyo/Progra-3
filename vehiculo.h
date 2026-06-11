/*
* Proyecto Estacionamiento 
 * Progra 3
 */

#ifndef VEHICULO_H_
#define VEHICULO_H_

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// Clase base abstracta: Vehiculo

class Vehiculo {

protected:
    string placa;
    string marca;
    string color;

public:
    Vehiculo() : placa(""), marca(""), color("") {}

    Vehiculo(string pla, string mar, string col)
        : placa(pla), marca(mar), color(col) {}

    // getters
    string getPlaca() { return placa; }
    string getMarca() { return marca; }
    string getColor() { return color; }

    virtual string getTipo()   = 0;
    virtual string to_string() = 0;

};


// Subclase: auto 

class Auto : public Vehiculo {

private:
    int numPuertas;

public:
    Auto() : Vehiculo(), numPuertas(4) {}

    Auto(string pla, string mar, string col, int puertas)
        : Vehiculo(pla, mar, col), numPuertas(puertas) {}

    int getNumPuertas() { return numPuertas; }

    string getTipo() { return "auto"; }
    //
    string to_string() {
        stringstream ss;
        ss << "Placa: "    << placa
           << " | Marca: "  << marca
           << " | Color: "  << color
           << " | Tipo: auto"
           << " | Puertas: " << numPuertas;
        return ss.str();
    }
};
// Subclase: Moto
class Moto : public Vehiculo {

private:
    bool sidecar;

public:
    Moto() : Vehiculo(), sidecar(false) {}

    Moto(string pla, string mar, string col, bool sid)
        : Vehiculo(pla, mar, col), sidecar(sid) {}

    bool getSidecar() { return sidecar; }

    string getTipo() { return "moto"; }

    string to_string() {
        stringstream ss;
        ss << "Placa: "    << placa
           << " | Marca: "  << marca
           << " | Color: "  << color
           << " | Tipo: moto"
           << " | Sidecar: " << (sidecar ? "si" : "no");
        return ss.str();
    }
};
// Subclase: Camioneta
class Camioneta : public Vehiculo {

private:
    double cargaMax;

public:
    Camioneta() : Vehiculo(), cargaMax(0.0) {}

    Camioneta(string pla, string mar, string col, double carga)
        : Vehiculo(pla, mar, col), cargaMax(carga) {}

    double getCargaMax() { return cargaMax; }

    string getTipo() { return "camioneta"; }

    string to_string() {
        stringstream ss;
        ss << "Placa: "        << placa
           << " | Marca: "      << marca
           << " | Color: "      << color
           << " | Tipo: camioneta"
           << " | Carga max: "  << cargaMax << " ton";
        return ss.str();
    }
};

#endif // VEHICULO_H_
