# **Trabajo Práctico 1:** Control de periféricos externos con puertos E/S.


Hernández Mejía, Carlos Alejandro \
11 de abril del 2022

## Introducción

## Objetivos


### Objetivo general
Caracterizar los componentes de hardware y software de un sistema embebido, así como también las arquitecturas de los microcontroladores y  microprogramación de la CPU y sus periféricos.

### Objetivos específicos
* Manejar el lenguaje C para programar un MCU y su relación con el lenguaje ensamblador.
* Manejar las herramientas para hacer un nuevo proyecto, editar, compilar, reconocer errores y bajar a la placa o simular. Depurar, ejecutar paso a paso, corregir errores de funcionamiento. 
* Conocer la arquitectura del MCU y cómo trabajar con los puertos entrada-salida.
* Comprender la temporización de un programa mediante retardos bloqueantes y cómo afecta al tiempo de respuesta de los eventos respecto al usuario.
* Comprender los problemas típicos de interconexión de los puertos con periféricos externos digitales o analógicos.
* Comprender cómo desarrollar una interfaz de usuario mínima para interactuar con el MCU (Leds y pulsadores).

## Problema
1. Se desea conectar 8 diodos LED de diferentes colores al puerto B del MCU y encenderlos con una corriente de 10mA en cada uno. Realice el esquema eléctrico de la conexión en Proteus. Calcule la resistencia serie para cada color teniendo en cuenta la caída de tensión VLED (rojo=1.8V, verde=2.2V amarillo=2.0V azul=3.0V) Verifique que la corriente por cada terminal del MCU no supere la capacidad de corriente de cada salida y de todas las salidas del mismo puerto en funcionamiento simultáneo.
2. Se desea conectar un pulsador a una entrada digital del MCU y detectar cuando el usuario presiona y suelta el pulsador. Muestra el esquema de conexión y determina la configuración del MCU que corresponda. Investigue sobre el efecto de rebote que producen los pulsadores e implemente un método para eliminar este efecto en su algoritmo de detección (puede encontrar información útil en la bibliografía)
3. Realice el programa para que el MCU encienda los LEDs del puerto B con la siguiente secuencia repetitiva: b0 y b7 – b1 y b6 – b2 y b5 – b3 y b4. Luego, cuando el usuario presione y suelte el pulsador debe cambiar a la secuencia: b3 y b4 – b2 y b5 – b1 y b6 – b0 y b7. Si presiona y suelta nuevamente vuelve a la secuencia original y así sucesivamente. Elija un retardo adecuado para la visualización. Justifique.
4. Saque conclusiones sobre el funcionamiento del programa, sobre las ventajas y desventajas de utilizar un retardo bloqueante y cómo este afecta el tiempo de respuesta del programa ¿qué sucede si se deja presionado constantemente el pulsador?

## Interpretación

Respecto al punto 1 de la sección anterior, se solicita que se arme el esquema eléctrico de cómo se deben conectar dichos LEDs al puerto B del MCU. Además, se pide que se hagan los cálculos necesarios para determinar el valor de las resistencias a usar en cada LED, para que la corriente suministrada por el MCU no supere el nivel de corriente de salida tolerado por cada LED, el cuál depende de la caída de tensión que estos necesitan para mostrar un color en particular VLED (rojo=1.8V, verde=2.2V, amarillo=2.0V azul=3.0V)

En el punto 2, se pide conectar un pulsador a una entrada digital del MCU (a diferencia del punto anterior, no se especifica el puerto a usar, quedando esto a discreción del alumno). Al igual que el punto anterior, se solicita mostrar el diagrama con el esquema de conexión correspondiente. Por último, se solicita investigar en qué consiste el efecto “rebote” que producen dichos pulsadores, así como los métodos para mitigarlo y se pide que se implemente alguno de ellos.

Mientras que en el punto 3, se pide implementar un algoritmo que permita encender las LEDs que se conectaron según el esquema definido en el punto uno, y que dicho encendido siga un patrón que encienda y apague los LEDs, comenzando desde los extremos hasta llegar a los LEDs del medio, volviendo a iniciar la secuencia (b0 y b7 – b1 y b6 – b2 y b5 – b3 y b4).

Luego, si se llegase a presionar (y soltar) el pulsador, se tendrá que invertir dicho patrón, comenzando por encender y apagar las LEDs del medio hasta llegar a los extremos (b3 y b4 – b2 y b5 – b1 y b6 – b0 y b7). Volviendo al patrón original si el usuario presiona nuevamente el pulsador y viceversa. 

## Resolución
1. Lo primero que se deberá hacer es armar el esquema eléctrico de cómo se conectará cada uno de los LEDs a nuestro MCU. Para ello, se decidió conectar cada LED a cada uno de los pines correspondientes a PB. 


## Conclusiones
