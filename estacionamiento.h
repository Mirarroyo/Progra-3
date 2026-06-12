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

// Numero maximo de cajones que puede tener cualquier
const int MAX_CAJONES = 50;

// Clase: Cajon
// Representa un espacio fisico de estacionamiento. 

class Cajon {

private:
    int       numero;
    bool      ocupado;
    Vehiculo* vehiculo;   // polimorfismo

public:
    // Constructor por default: cajon "vacio" sin numero asignado.
    Cajon() : numero(0), ocupado(false), vehiculo(0) {}
    // Constructor parametrizado: crea el cajon con su numero,
    // inicialmente libre y sin vehiculo.
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
// Representa el boleto que se genera cuando un vehiculo entra al
// estacionamiento. Guarda la hora de entrada y si sigue activo

class Boleto {

private:
    string id;
    int    horaEntrada;
    string idVehiculo;
    bool   activo;

public:

    Boleto() : id(""), horaEntrada(0), idVehiculo(""), activo(false) {}

    //Constructor parametrizado

    Boleto(string bid, int hora, string idVeh)
        : id(bid), horaEntrada(hora), idVehiculo(idVeh), activo(true) {}

    //getters
    string getId()          { return id; }
    int    getHoraEntrada() { return horaEntrada; }
    string getIdVehiculo()  { return idVehiculo; }
    bool   isActivo()       { return activo; }

    // getHoras: calcula cuantas horas estuvo el vehiculo dentro,
    // a partir de la hora de salida.
    int getHoras(int horaSalida) {
        int diff = (horaSalida / 100) - (horaEntrada / 100);
        return (diff > 0) ? diff : 1;
    }

    void cerrar() { activo = false; }
};

// Clase: Cobro
// Se encarga de calcular cuanto debe pagar un vehiculo al salir,
// y de generar el recibo correspondiente.

class Cobro {

private:
    Boleto*   ticket;       
    Vehiculo* vehiculo;     
    double    monto;
    int       horaSalida;

    // tarifaPorHora(): define el precio por hora segun el tipo de
    // vehiculo, consultando getTipo() de forma polimorfica
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
    // Recibe un puntero al boleto que se va a cerrar, el vehiculo
    // correspondiente y la hora de salida.
    Cobro(Boleto* t, Vehiculo* v, int salida)
        : ticket(t), vehiculo(v), monto(0.0), horaSalida(salida) {}

    //getter
    double getMonto() { return monto; }

    // procesarPago(): calcula el monto a pagar = tarifa por hora *
    // numero de horas, aplica el descuento y cierra el
    // boleto
    // Regresa false si no hay boleto o vehiculo validos
    bool procesarPago(double descuento = 0.0) {
        if (ticket == 0 || vehiculo == 0) return false; 
        monto = tarifaPorHora() * ticket->getHoras(horaSalida);
        if (descuento > 0.0) {
            // descuento viene como porcentaje 
            monto = monto - (monto * descuento / 100.0);
        }
        
        ticket->cerrar();
        return true;
    }

    // generarRecibo(): construye un string con el detalle del cobro
    //  para mostrarselo al usuario.
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
// Clase principal: representa el estacionamiento completo, con un
// arreglo de cajones y la logica para registrar entradas y salidas.

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
    // recibe el nombre y la capacidad, y crea/numera los cajones
    // del 1 al limite
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

    // entrada(): registra el ingreso de un vehiculo.
    // 1) Busca un cajon libre.
    // 2) Si encuentra uno, asigna el vehiculo a ese cajon, genera
    //    un nuevo Boleto activo 
    // 3) Si NO hay cajones libres, avisa y regresa un Boleto()
    //    "vacio".
    Boleto entrada(Vehiculo* v, int hora) {
        int indiceLibre = buscarCajonLibre();
        if (indiceLibre != -1) {
            cajones[indiceLibre].asignar(v);
            totalBoletos++;
            // ID simple para el boleto: B1, B2, etc...
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
            if (!cajones[i].estaLibre() &&
                cajones[i].getVehiculo()->getPlaca() == placa) {
                cajones[i].liberar();
                cout << "[Salida] Cajon " << i + 1
                     << " liberado (" << placa << ")" << endl;
                return;
            }
        }
        cout << "Placa no encontrada: " << placa << endl;
    }

    // mostrarCajones(): imprime el estado de cada cajon: "Libre" o,
    // si esta ocupado, la informacion completa del vehiculo
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

    // mostrarDisponibilidad(): imprime el nombre del estacionamiento
    // y cuantos lugares libres hay de la capacidad total. Si ya no
    // quedan lugares, agrega un aviso de "lleno".
    void mostrarDisponibilidad() {
        cout << nombre
             << " Lugares libres: " << getLugaresLibres()
             << " / " << capacidad << endl;
        if (getLugaresLibres() == 0)
            cout << "Estacionamiento lleno." << endl;
    }

};

#endif // ESTACIONAMIENTO_H_
