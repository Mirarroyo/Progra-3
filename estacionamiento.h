/*
 *Proyecto Estacionamiento 
 *Progra 3
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

    //getters 
    int  getNumero()  { return numero;  }
    bool getOcupado() { return ocupado; }

    bool estaLibre()  { return !ocupado; }
    Vehiculo* getVehiculo() { return vehiculo; }

    void asignar(Vehiculo* v) {
         vehiculo = v; 
         ocupado = true;  
    }
    void liberar() { 
        vehiculo = 0; 
        ocupado = false; 
    }

};

// Clase: Boleto

class Boleto {

private:
    string id;
    int    horaEntrada;
    string idVehiculo;
    bool   activo;

public:
    //constuctor defaut
    Boleto() : id(""), horaEntrada(0), idVehiculo(""), activo(false) {}

    //Constructor parametrizado
    Boleto(string bid, int hora, string idVeh)
        : id(bid), horaEntrada(hora), idVehiculo(idVeh), activo(true) {}

    //getters
    string getId()          { return id; }
    int    getHoraEntrada() { return horaEntrada; }
    string getIdVehiculo()  { return idVehiculo; }
    bool   isActivo()       { return activo; }

    int getHoras(int horaSalida) {
        int diff = (horaSalida / 100) - (horaEntrada / 100);
        return (diff > 0) ? diff : 1;
    }

    void cerrar() { activo = false; }
};
// Clase: Cobro

class Cobro {

private:
    Boleto*   ticket;       //agregacion 
    Vehiculo* vehiculo;   // polimorfismo
    double    monto;
    int       horaSalida;

    double tarifaPorHora() {
        if (vehiculo == 0) return 0.0;
        string tipo = vehiculo->getTipo();   
        if (tipo == "auto")      return 25.0;
        if (tipo == "moto")      return 15.0;
        if (tipo == "camioneta") return 40.0;
        return 20.0; // tarifa base
    }

public:
    //constructor default
    Cobro() : ticket(0), vehiculo(0), monto(0.0), horaSalida(0) {}

    //constructor parametrizado
    Cobro(Boleto* t, Vehiculo* v, int salida)
        : ticket(t), vehiculo(v), monto(0.0), horaSalida(salida) {}

    //getter
    double getMonto() { return monto; }

    bool procesarPago(double descuento = 0.0) {
        if (ticket == 0 || vehiculo == 0) return false; 
        monto = tarifaPorHora() * ticket->getHoras(horaSalida);
        if (descuento > 0.0) {
            monto = monto - (monto * descuento / 100.0);
        }
        
        ticket->cerrar();
        return true;
    }

    // generarer recibo
    string generarRecibo() {
        stringstream ss;
        ss << "RECIBO "
           << "\nBoleto:   " << ticket->getId()
           << "\nVehiculo: " << ticket->getIdVehiculo()
           << "\nTipo:     " << vehiculo->getTipo()   
           << "\nHoras:    " << ticket->getHoras(horaSalida)
           << "\nTarifa:   $" << tarifaPorHora() << "/hr"
           << "\nTotal:    $" << monto
           << "\n";
        return ss.str();
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
    //constructor default
    Estacionamiento() : nombre(""), capacidad(0), totalBoletos(0) {}

    //constructor parametrizado
    Estacionamiento(string nom, int cap)
        : nombre(nom), capacidad(cap), totalBoletos(0) {
        for (int i = 0; i < cap && i < MAX_CAJONES; i++)
            cajones[i] = Cajon(i + 1);
    }

    //getters
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

    Boleto entrada(Vehiculo* v, int hora) {
        int indiceLibre = buscarCajonLibre();
        if (indiceLibre != -1) {
            cajones[indiceLibre].asignar(v);
            totalBoletos++;
            // Generamos un ID simple para el boleto: B1, B2, etc.
            string idBoleto = "B" + to_string(totalBoletos); 
            cout << "[Entrada] " << v->getTipo() << " con placa " << v->getPlaca() 
                 << " asignado al Cajon " << (indiceLibre + 1) << endl;
            return Boleto(idBoleto, hora, v->getPlaca());
        } else {
            cout << "No hay cajones disponibles para la placa: " << v->getPlaca() << endl;
            return Boleto(); // Boleto inactivo
        }
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
    void mostrarCajones() {
        for (int i = 0; i < capacidad; i++) {
            cout << "Cajon " << i + 1 << ": ";
            if (cajones[i].estaLibre()) {
                cout << "Libre" << endl;
            } else {
                cout << cajones[i].getVehiculo()->to_string() << endl;
            }
        }
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
