# TC1030 — Proyecto Estacionamiento

Este proyecto es un sistema de administración de espacios y cobro para un estacionamiento. Ek cual permite registrar la entrada y salida de vehículos, asignar cajones, generar boletos y calcular el monto a pagar según el tiempo y el tipo de vehículo.

---

## Funcionalidad

- Registrar la entrada de un vehículo y asignarle el primer cajón libre
- Consultar en tiempo real cuántos cajones están disponibles
- Generar un boleto con el ID del vehículo y la hora de entrada
- Calcular el costo de la estadía según el tipo de vehículo
- Aplicar descuento porcentual al cobro si aplica
- Imprimir recibo de salida con desglose de horas y tarifa



## Como compilar y correr el proyecto

**Compilar:**
```bash
g++ main.cpp -o estacionamiento
```

No requiere librerías externas. Funciona con cualquier compilador que soporte C++ estándar.

---

## Casos donde el proyecto deja de funcionar

- Si todos los cajones están ocupados, `buscarCajonLibre()` regresa `-1` y `entrada()` devuelve un `Boleto` vacío. El vehículo no queda registrado.
- Si `horaSalida < horaEntrada` en `getHoras()`, la diferencia es negativa y se cobra el mínimo de 1 hora en lugar del tiempo real.
- Si se intenta cobrar un boleto ya cerrado (ya se llamó `cerrar()`), `getHoras()` sigue funcionando pero el boleto ya no está activo.
- `Vehiculo` no puede instanciarse directamente porque tiene métodos virtuales puros — el compilador lo rechaza.
