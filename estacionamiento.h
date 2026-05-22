/*
 // Proyecto progra 3
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
// Agregagación de un vehiculo 

class Cajon {

private:
    int     numero;
    bool    ocupado;
    Vehiculo* vehiculo;   // puntero — agregación
    // Checar si sí es así 

public:
    // Constructor 
    Cajon() : numero(0), ocupado(false), vehiculo(0) {}

    // Constructor con parámetros
    Cajon(int num) : numero(num), ocupado(false), vehiculo(0) {}

    // Getters
    int  getNumero()  { return numero; }
    bool getOcupado() { return ocupado; }

    // Cajón está disponible?
    bool estaLibre() { return !ocupado; }

    // Asigna un vehículo al cajón
    void asignar(Vehiculo* v) {
        vehiculo = v;
        ocupado  = true;
    }

    // Libera el cajón
    void liberar() {
        vehiculo = 0;
        ocupado  = false;
    }

    // Muestra estado del cajón
    string to_string() {
        stringstream ss;
        ss << "Cajon " << numero
           << (ocupado ? " [OCUPADO]" : " [LIBRE]");
        return ss.str();
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
    // Constructor
    Boleto() : id(""), horaEntrada(0), idVehiculo(""), activo(false) {}

    // Constructor con parámetros
    Boleto(string bid, int hora, string idVeh)
        : id(bid), horaEntrada(hora), idVehiculo(idVeh), activo(true) {}

    // Getters
    string getId()         { return id; }
    int    getHoraEntrada(){ return horaEntrada; }
    string getIdVehiculo() { return idVehiculo; }
    bool   isActivo()      { return activo; }

    // Calcula horas 
    //tbd
    }

    // Cierra el boleto
    void cerrar() { activo = false; }

    string to_string() {
        stringstream ss;
        ss << "Boleto " << id
           << " | Vehiculo: " << idVehiculo
           << " | Entrada: " << horaEntrada
           << (activo ? " [ACTIVO]" : " [CERRADO]");
        return ss.str();
    }
};


// Clase: Costo

class Costo {
// Ver cual puedo hacer protected
private:
    double precioPorHora;
    string tipoVehiculo;

public:
    // Constructor 
    Costo() : precioPorHora(0.0), tipoVehiculo("") {}

    // Constructor con parámetros
    Costo(double precio, string tipo)
        : precioPorHora(precio), tipoVehiculo(tipo) {}

    // Getters
    double getPrecioPorHora() { return precioPorHora; }
    string getTipoVehiculo()  { return tipoVehiculo; }

    // Calcula el monto total
    double calcular(int horas) {
        return precioPorHora * horas;
    }

    // Sobrecarga (posiblemente - probablemente mal)
    double calcular(int horas, double descuento) {
        double total = precioPorHora * horas;
        return total - (total * descuento / 100.0);
    }

    string to_string() {
        stringstream ss;
        ss << "Tarifa " << tipoVehiculo
           << ": $" << precioPorHora << "/hora";
        return ss.str();
    }
};

// Clase: Cobro

class Cobro {

private:
    Boleto* ticket;   // puntero a agregación..
    Costo*  costo;    // puntero a agregación..
    double  monto;
    int     horaSalida;

public:
    // Constructor 
    Cobro() : ticket(0), costo(0), monto(0.0), horaSalida(0) {}

    // Constructor con parámetros
    Cobro(Boleto* t, Costo* c, int salida)
        : ticket(t), costo(c), monto(0.0), horaSalida(salida) {}

    // Getter
    double getMonto() { return monto; }

    // Calcula y registra el pago
    //tbd

    // Genera texto del recibo
    //tbd  


// Clase: Sensor
// Detecta llegada de un vehículo.

/* class Estacionamiento;    forward declaration

class Sensor {

private:
    bool   activo;
    Estacionamiento* estado;   // puntero a agregación..

public:
    Sensor() : activo(false), estado(0) {}
    
    bool isActivo() { return activo; }


// Clase: Estacionamiento

class Estacionamiento {

private:
    Cajon  cajones[MAX_CAJONES];   
    string nombre;
    int    capacidad;
    int    totalBoletos;

public:
    // Constructor 
    Estacionamiento() : nombre(""), capacidad(0), totalBoletos(0) {}

    // Constructor con parámetros 
    Estacionamiento(string nom, int cap) : nombre(nom), capacidad(cap), totalBoletos(0) {
        for (int i = 0; i < cap && i < MAX_CAJONES; i++)
            cajones[i] = Cajon(i + 1);
    }

    // Getter
    string getNombre()       { return nombre; }
    int    getCapacidad()    { return capacidad; }

    // Cajones están libres
    //TBD
    }



   //TBD

    // Muestra estado de todos los cajones
    void mostrarCajones() {
        for (int i = 0; i < capacidad; i++)
            cout << cajones[i].to_string() << endl;
    }
};


// Clase: PanelIDControl
// tbd 
*/
};
#endif // ESTACIONAMIENTO_H_
