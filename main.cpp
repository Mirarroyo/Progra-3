/*
 * Proyecto Estacionamiento
 * Progra 3
 * Miranda Arroyo Velázquez 
 * A01710117
 */

 

#include <iostream>
#include "vehiculo.h"
#include "estacionamiento.h"
using namespace std;


// Opcion 1 del menu: muestra cuantos lugares libres hay y de
// cuantos en total, delegando todo a Estacionamiento.
void verDisponibilidad(Estacionamiento& parking) {
    parking.mostrarDisponibilidad();
}

// Opcion 2 del menu: registra la entrada de un vehiculo.
// 1) Pide la placa al usuario.
// 2) Busca esa placa dentro del catalogo.
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

// Opcion 3 del menu: registra la salida de un vehiculo y calcula su cobro.
//
// 1) Pide la placa al usuario y busca su indice en el catalogo.
// 2) Si el vehiculo encontrado tiene un boleto activo:
// Pide la hora de salida y el porcentaje de descuento
// Crea un objeto Cobro asociado a ese boleto y vehiculo
// procesarPago() calcula el monto y cierra el boleto 
// Se llama a parking.salida() para liberar el cajon
// 3) Si el boleto NO esta activo, el vehiculo no estaba dentro, se avisa.
// 4) Si la placa no existe en el catalogo, se muestra error.

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

                // Procesam el cobro
            
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

// Opcion 4 del menu: muestra el "mapa" de cajones, indicando cuales
// estan libres y cuales ocupados.
void verCajones(Estacionamiento& parking) {
    cout << "Estado actual de cajones" << endl;
    parking.mostrarCajones();
}

// Opcion 5 del menu: imprime todos los vehiculos registrados en el
// sistema.
void mostrarCatalogo(Vehiculo* catalogo[], int totalVehiculos) {
    cout << "Vehiculos registrados en el sistema" << endl;
    for (int i = 0; i < totalVehiculos; i++) {
        cout << "Tipo: " << catalogo[i]->getTipo() << " | "
             << catalogo[i]->to_string() << endl;
    }
}
 

// Menu principal
//
// Crea un arreglo de Boletos paralelo al catalogo. 
// Despues entra en un ciclo que muestra el menu,
// lee la opcion del usuario y llama a la funcion correspondiente,
// hasta que el usuario elige la opcion 6 (Salir).
void ejecutarMenu(Estacionamiento& parking, Vehiculo* catalogo[], int totalVehiculos) {
    int opcion = 0;
    bool continuar = true;
 
    // Arreglo de boletos, uno por cada vehiculo del catalogo.
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

    // Catalogo de vehiculos: arreglo de PUNTEROS a Vehiculo.
    // Cada elemento apunta a un objeto Auto, Moto o
    // Camioneta creado dinamicamente con "new". 
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
