# TestingTP4
TP4 Testing de Software en SE

Trabajo Práctico N4 - TSSE

 Se realizan pruebas unitarias para la librería "mq2.h"
 Utilicé esta librería anteriormente para sensar concentracion de humo con el sensor MQ2.
 
 Tuve problemas al momento de usar la libreria math.h, el programa al compilar no linkeaba (usando ceedling),
 por lo que tuve que dejar de usar las funciones pow() y log() para hallar valores verdaderos de concentracion de gas.
 
Requisitos:
    *El sistema debe poder calibrar el sensor de concentracion de gas exponiendolo
     a aire limpio (no contaminado)
    *El sistema debe poder sensar la concentracion de gas licuado de petroleo (LPG)
    *El sistema debe poder sensar la concentracion de CO 
    *El sistema debe poder sensar la concentracion de Humo (Smoke)
