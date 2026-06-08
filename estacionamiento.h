/*
 Proyecto Estacionamiento 
 Progra 3
 */

#ifndef ESTACIONAMIENTO_H_
#define ESTACIONAMIENTO_H_

#include <string>
#include <iostream>
#include <sstream>
#include "vehiculo.h"
using namespace std;

const int MAX_CAJONES = 50;

// Clase: Cajon

class Cajon {

private:
    int       numero;
    bool      ocupado;
    Vehiculo* vehiculo;   // polimorfismo

public:
    Cajon() : numero(0), ocupado(false), vehiculo(0) {}
    Cajon(int num) : numero(num), ocupado(false), vehiculo(0) {}

    int  getNumero()  { return numero;  }
    bool getOcupado() { return ocupado; }
    bool estaLibre()  { return !ocupado; }

    void asignar(Vehiculo* v) { vehiculo = v; ocupado = true;  }
    void liberar()            { vehiculo = 0; ocupado = false; }

    /*
    string to_string() {
        stringstream ss;
        ss << "Cajon " << numero;
        if (ocupado && vehiculo != 0)
            ss << " [OCUPADO] -> " << vehiculo->to_string();
        else
            ss << " [LIBRE]";
        return ss.str();
    }
    */
};

// Clase: Boleto

class Boleto {

private:
    string id;
    int    horaEntrada;
    string idVehiculo;
    bool   activo;

public:
    Boleto() : id(""), horaEntrada(0), idVehiculo(""), activo(false) {}

    Boleto(string bid, int hora, string idVeh)
        : id(bid), horaEntrada(hora), idVehiculo(idVeh), activo(true) {}

    string getId()          { return id; }
    int    getHoraEntrada() { return horaEntrada; }
    string getIdVehiculo()  { return idVehiculo; }
    bool   isActivo()       { return activo; }

    int getHoras(int horaSalida) {
        int diff = (horaSalida / 100) - (horaEntrada / 100);
        return (diff > 0) ? diff : 1;
    }

    void cerrar() { activo = false; }

    string to_string() {
        stringstream ss;
        ss << "Boleto " << id
           << " | Vehiculo: " << idVehiculo
           << " | Entrada: "  << horaEntrada
           << (activo ? " [ACTIVO]" : " [CERRADO]");
        return ss.str();
    }

    // Sobrecarga << — imprime el boleto con cout
    friend ostream& operator<<(ostream& os, Boleto& b) {
        os << b.to_string();
        return os;
    }

    // Sobrecarga == — compara dos boletos por su id
    bool operator==(Boleto& otro) {
        return id == otro.id;
    }
};
// Clase: Cobro

class Cobro {

private:
    Boleto*   ticket;
    Vehiculo* vehiculo;   // polimorfismo
    double    monto;
    int       horaSalida;

    double tarifaPorHora() {
        if (vehiculo == 0) return 0.0;
        string tipo = vehiculo->getTipo();   
        if (tipo == "auto")      return 25.0;
        if (tipo == "moto")      return 15.0;
        if (tipo == "camioneta") return 40.0;
        return 20.0;
    }

public:
    Cobro() : ticket(0), vehiculo(0), monto(0.0), horaSalida(0) {}

    Cobro(Boleto* t, Vehiculo* v, int salida)
        : ticket(t), vehiculo(v), monto(0.0), horaSalida(salida) {}

    double getMonto() { return monto; }

    // Sobrecarga: sin descuento
    bool procesarPago() {
        if (ticket == 0 || vehiculo == 0) return false;
        monto = tarifaPorHora() * ticket->getHoras(horaSalida);
        ticket->cerrar();
        return true;
    }

    // Sobrecarga: con descuento porcentual
    bool procesarPago(double descuento) {
        if (!procesarPago()) return false;
        monto = monto - (monto * descuento / 100.0);
        return true;
    }

    string generarRecibo() {
        stringstream ss;
        ss << "RECIBO "
           << "\nBoleto:   " << ticket->getId()
           << "\nVehiculo: " << ticket->getIdVehiculo()
           << "\nTipo:     " << vehiculo->getTipo()   // llamada polimórfica
           << "\nHoras:    " << ticket->getHoras(horaSalida)
           << "\nTarifa:   $" << tarifaPorHora() << "/hr"
           << "\nTotal:    $" << monto
           << "\n";
        return ss.str();
    }

    // Sobrecarga <<
    friend ostream& operator<<(ostream& os, Cobro& c) {
        os << c.generarRecibo();
        return os;
    }
};

// Clase: Estacionamiento

class Estacionamiento {

private:
    Cajon  cajones[MAX_CAJONES];   // composición 1..*
    string nombre;
    int    capacidad;
    int    totalBoletos;

public:
    Estacionamiento() : nombre(""), capacidad(0), totalBoletos(0) {}

    Estacionamiento(string nom, int cap)
        : nombre(nom), capacidad(cap), totalBoletos(0) {
        for (int i = 0; i < cap && i < MAX_CAJONES; i++)
            cajones[i] = Cajon(i + 1);
    }

    string getNombre()    { return nombre; }
    int    getCapacidad() { return capacidad; }

    int getLugaresLibres() {
        int libres = 0;
        for (int i = 0; i < capacidad; i++)
            if (cajones[i].estaLibre()) libres++;
        return libres;
    }

    int buscarCajonLibre() {
        for (int i = 0; i < capacidad; i++)
            if (cajones[i].estaLibre()) return i;
        return -1;
    }

    void salida(string placa) {
        for (int i = 0; i < capacidad; i++) {
            if (!cajones[i].estaLibre()) {
                cajones[i].liberar();
                cout << "[Salida] Cajon " << i + 1
                     << " liberado (" << placa << ")" << endl;
                return;
            }
        }
        cout << "Placa no encontrada: " << placa << endl;
    }

    void mostrarDisponibilidad() {
        cout << nombre
             << " Lugares libres: " << getLugaresLibres()
             << " / " << capacidad << endl;
        if (getLugaresLibres() == 0)
            cout << "Estacionamiento lleno." << endl;
    }

};

#endif // ESTACIONAMIENTO_H_
