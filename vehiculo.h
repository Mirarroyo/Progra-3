/*
* Proyecto Estacionamiento 
 * Progra 3
 */

 /*
 * Clase Vehiculo - clase base abstracta
    * Subclases: Auto, Moto, Camioneta
 * Define artibutos y metodos comuenes al igual que 
 * implementa getTipo() y to_string() como
 *  metodos virtuales puros.
 */

#ifndef VEHICULO_H_
#define VEHICULO_H_

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// Clase base abstracta: Vehiculo

class Vehiculo {

//Declaracion de variables de instancia
protected:
    string placa; 
    string marca; 
    string color; 

// Declaracion de metodos del objeto 
public:
    Vehiculo() : placa(""), marca(""), color("") {} 

/** 
 * Constructor recibe valores para llenar las variables de instancia
 *
 * Inicializa placa, marca y color con los valores recibidos.
 *
 * @param string pla: placa del vehículo
 * @param string mar: marca del vehículo
 * @param string col: color del vehículo
 * @return objeto Vehiculo
 */
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
/** 
 * Clase Auto hereda de Vehiculo y representa un automóvil. Agrega el
 * atributo numPuertas e implementa getTipo() y to_string() para
 * cumplir con los métodos virtuales puros de la clase base.
 *
 */

 // Declaracion de la clase Auto que hereda de Vehiculo
class Auto : public Vehiculo {

//Declaracion de variables de instancia
private:
    int numPuertas;

// Declaracion de metodos del objeto
public:

/**
 * Constructor por default
 *
 * Llama al constructor por default de Vehiculo e inicializa
 * numPuertas en 4 como valor por default.
 *
 * @param
 * @return Objeto Auto
 */
    Auto() : Vehiculo(), numPuertas(4) {}

/**
 * Constructor recibe valores para llenar las variables de instancia
 *
 * Llama al constructor parametrizado de Vehiculo con placa, marca
 * y color, e inicializa numPuertas con el valor recibido.
 *
 * @param string pla: placa del vehículo
 * @param string mar: marca del vehículo
 * @param string col: color del vehículo
 * @param int puertas: número de puertas del auto
 * @return objeto Auto
 */
    Auto(string pla, string mar, string col, int puertas)
        : Vehiculo(pla, mar, col), numPuertas(puertas) {}

    /**
     * getter numPuertas
     *
     * Regresa el número de puertas del auto.
     * 
     * @param @return int: número de puertas
    */

    int getNumPuertas() { return numPuertas; }

    /**
    * getTipo sobreescribe el método virtual puro de Vehiculo
    *
    * Identifica este objeto como tipo "auto". Se usa de forma
    * polimórfica cuando se trabaja con un puntero Vehiculo*
    *
    * @param
    * @return string: "auto"
    */

    string getTipo() { return "auto"; }
    /**
    * to_string sobreescribe el método virtual puro de Vehiculo
    *
    * Concatena en un stringstream los atributos heredados junto 
    * con el tipo y el número de puertas propio de Auto, 
    * para regresar toda la información como un solo string.
    *
    * @param
    * @return string con los valores y texto concatenado
    */

    string to_string() {
        stringstream ss;
        ss << "Placa: "    << placa
           << " Marca: "  << marca
           << " Color: "  << color
           << " Tipo: auto"
           << " Puertas: " << numPuertas;
        return ss.str();
    }
};

// Subclase: Moto

/*
 * Clase Moto hereda de Vehiculo. 
 * Atributo sidecar e implementa getTipo() y to_string() para
 * cumplir con los métodos virtuales puros de la clase base.
 */

class Moto : public Vehiculo {

//Declaracion de variables de instancia
private:
    bool sidecar;

// Declaracion de metodos del objeto
public:
/**
 * Constructor por default
 *
 * Llama al constructor por default de Vehiculo e inicializa
 * sidecar en false como valor por default.
 *
 * @param
 * @return Objeto Moto
 */
    Moto() : Vehiculo(), sidecar(false) {}
    /**
    * Constructor recibe valores para llenar las variables de instancia
    *
    * Llama al constructor parametrizado de Vehiculo 
    * e inicializa sidecar con el valor recibido.
    *
    * @param string pla: placa del vehículo
    * @param string mar: marca del vehículo
    * @param string col: color del vehículo
    * @param bool sid: true si la moto tiene sidecar
    * @return objeto Moto
    */
    Moto(string pla, string mar, string col, bool sid)
        : Vehiculo(pla, mar, col), sidecar(sid) {}

    /**
    * getter sidecar
    *
    * Regresa true si la moto tiene sidecar.
    *
    * @param
    * @return bool: true si tiene sidecar, false si no
    */

    bool getSidecar() { return sidecar; }

    /**
     * getTipo sobreescribe el método virtual puro de Vehiculo
     *
     * Identifica este objeto como tipo "moto". Se usa de forma
     * polimórfica cuando se trabaja con un puntero Vehiculo*.
     *
     * @param
     * @return string: "moto"
    */
    string getTipo() { return "moto"; }

    /**
    * to_string sobreescribe el método virtual puro de Vehiculo
    * Concatena en un stringstream los atributos heredados junto 
    * con el tipo y la información de sidecar propia de Moto.
    * @param
    * @return string con los valores y texto concatenado
    */

    string to_string() {
        stringstream ss;
        ss << "Placa: "    << placa
           << " Marca: "  << marca
           << " Color: "  << color
           << " Tipo: moto"
           << " Sidecar: " << (sidecar ? "si" : "no");
        return ss.str();
    }
};

// Subclase: Camioneta
/*
 * Clase Camioneta hereda de Vehiculo.
 * Agrega el atributo cargaMax e implementa getTipo() y to_string()
 * para cumplir con los métodos virtuales puros de la clase base.
 *
 */
class Camioneta : public Vehiculo {

//Declaracion de variables de instancia
private:
    double cargaMax;

// Declaracion de metodos del objeto
public:
    /**
     * Constructor por default
     *
     * Llama al constructor por default de Vehiculo e inicializa
     * cargaMax en 0.0 como valor por default.
     *
     * @param
     * @return Objeto Camioneta
     */
    Camioneta() : Vehiculo(), cargaMax(0.0) {}

    /**
     * Constructor recibe valores para llenar las variables de instancia
     *
     * Llama al constructor parametrizado de Vehiculo, 
     * e inicializa cargaMax con el valor recibido.
     *
     * @param string pla: placa del vehículo
     * @param string mar: marca del vehículo
     * @param string col: color del vehículo
     * @param double carga: capacidad de carga máxima en toneladas
     * @return objeto Camioneta
     */
    Camioneta(string pla, string mar, string col, double carga)
        : Vehiculo(pla, mar, col), cargaMax(carga) {}

    /**
     * getter cargaMax
     *
     * Regresa la capacidad de carga máxima de la camioneta.
     *
     * @param
     * @return double: capacidad de carga máxima en toneladas
     */
    double getCargaMax() { return cargaMax; }

    /**
     * getTipo sobreescribe el método virtual puro de Vehiculo
     *
     * Identifica este objeto como tipo "camioneta". Se usa de forma
     * polimórfica cuando se trabaja con un puntero Vehiculo*.
     *
     * @param
     * @return string: "camioneta"
     */
    string getTipo() { return "camioneta"; }

    /**
     * to_string sobreescribe el método virtual puro de Vehiculo
     * Concatena en un stringstream los atributos heredados junto 
     * con el tipo y la información de carga máxima propia de Camioneta.
     * @param
     * @return string con los valores y texto concatenado
     */

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
