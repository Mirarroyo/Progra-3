/*
 * Proyecto Estacionamiento
 * Progra 3
 */

#include <iostream>
#include "vehiculo.h"
#include "estacionamiento.h"
using namespace std;


void verDisponibilidad(Estacionamiento& parking) {
    parking.mostrarDisponibilidad();
}

void registrarEntrada(Estacionamiento& parking, Vehiculo* catalogo[], Boleto boletos[], int totalVehiculos) {
    string placaBuscada;
    int horaEntrada;
    bool encontrado = false;

    cout << "Placas en el sistema: ABC-123, XYZ-999, DEF-456, GHI-321" << endl;
    cout << "Ingrese la placa del vehiculo: ";
    cin >> placaBuscada;

    for (int i = 0; i < totalVehiculos; i++) {
        if (catalogo[i]->getPlaca() == placaBuscada) {
            encontrado = true;
            
            if (boletos[i].isActivo()) {
                cout << "El vehiculo con placa " << placaBuscada << " ya esta dentro." << endl;
            } else {
                cout << "Ingrese la hora de entrada (Formato 24hrs, ej. 0900): ";
                cin >> horaEntrada;
                boletos[i] = parking.entrada(catalogo[i], horaEntrada);
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "Error: La placa '" << placaBuscada << "' no existe." << endl;
    }
}

void registrarSalida(Estacionamiento& parking, Vehiculo* catalogo[], Boleto boletos[], int totalVehiculos) {
    string placaBuscada;
    int horaSalida;
    double descuento = 0.0;
    bool encontrado = false;

    cout << "Ingrese la placa del vehiculo: ";
    cin >> placaBuscada;

    for (int i = 0; i < totalVehiculos; i++) {
        if (catalogo[i]->getPlaca() == placaBuscada) {
            encontrado = true;

            if (boletos[i].isActivo()) {
                cout << "Ingrese la hora de salida (Formato 24hrs (ej. 1400)): ";
                cin >> horaSalida;
                cout << "Opcion de descuento (0 si no): ";
                cin >> descuento;

                // Procesamos el cobro
                Cobro c(&boletos[i], catalogo[i], horaSalida);
                c.procesarPago(descuento);
                
                cout << endl << c.generarRecibo() << endl;
                parking.salida(placaBuscada);
            } else {
                cout << "El vehiculo: " << placaBuscada << " no esta en el estacionamiento." << endl;
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "Error: Placa no valida." << endl;
    }
}

void verCajones(Estacionamiento& parking) {
    cout << "Estado actual de cajones" << endl;
    parking.mostrarCajones();
}

void mostrarCatalogo(Vehiculo* catalogo[], int totalVehiculos) {
    cout << "Vehiculos registrados en el sistema" << endl;
    for (int i = 0; i < totalVehiculos; i++) {
        cout << "Tipo: " << catalogo[i]->getTipo() << " | "
             << catalogo[i]->to_string() << endl;
    }
}
 

// Menu principal

void ejecutarMenu(Estacionamiento& parking, Vehiculo* catalogo[], int totalVehiculos) {
    int opcion = 0;
    bool continuar = true;
 
    Boleto boletos[totalVehiculos];

    while (continuar) {
        cout << "\n   SISTEMA: " << parking.getNombre() << endl;
        cout << "1. Ver disponibilidad" << endl;
        cout << "2. Registrar entrada" << endl;
        cout << "3. Registrar salida y cobro" << endl;
        cout << "4. Ver mapa de cajones" << endl;
        cout << "5. Mostrar Catálogo" << endl;
        cout << "6. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: 
                verDisponibilidad(parking); 
                break;
            case 2: 
                registrarEntrada(parking, catalogo, boletos, totalVehiculos);  
                break;
            case 3: 
                registrarSalida(parking, catalogo, boletos, totalVehiculos);   
                break;
            case 4: 
                verCajones(parking);        
                break;
            case 5: 
                mostrarCatalogo(catalogo, totalVehiculos);
                break;
            case 6: 
                cout << "Hasta luego." << endl; 
                continuar = false; 
                break;
            default: 
                cout << "Opcion invalida. Intenta de nuevo." << endl;
        }
    }
}

int main() {
   const int TOTAL_VEHICULOS = 4;
    Vehiculo* catalogo[TOTAL_VEHICULOS] = {
        new Auto     ("ABC-123", "Toyota", "Rojo",   4),
        new Moto     ("XYZ-999", "Honda",  "Negro",  false),
        new Camioneta("DEF-456", "Ford",   "Blanco", 2.5),
        new Auto     ("GHI-321", "Nissan", "Azul",   2)
    };
 
    // Inicializa el estacionamiento con 5 cajones de capacidad
    Estacionamiento parking("Parking Central", 5);
 
    // Menu interactivo
    ejecutarMenu(parking, catalogo, TOTAL_VEHICULOS);
    
    return 0;
}
