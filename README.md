# **Trabajo Práctico 1:** Control de periféricos externos con puertos E/S.

## Introducción
En el presente documento se muestran de manera detallada los pasos seguidos para resolver un problema que haga uso del MCU y su integración con periféricos externos mediante la conexión de estos en algunos de sus puertos.

En la primera sección se definen los objetivos que se esperan que asimilar luego de finalizar este trabajo práctico.

Luego se define el problema que se tuvo que resolver. En esta sección se plantean distintas problemáticas para que con el fin de poder reflexionar y plantear la mejor solución posible.

Seguido de esto, se deja una sección completa donde se explica de manera detallada la interpretación del problema planteado anteriormente.

Además, se explica de manera detallada y coherente el raciocinio que ha seguido para resolver cada uno de los incisos planteados.

También, se adjunta documentación que valida que la solución planteada realmente resuelve el problema y cumple con los requisitos solicitados. Para terminar, se anexa el código de la solución.

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
1. Lo primero que se deberá hacer es armar el esquema eléctrico de cómo se conectará cada uno de los LEDs al puerto B de nuestro MCU. Para ello, se decidió conectar 2 LEDs azules a los pines PB0 y PB7 (a los extremos), 2 LEDs verdes a los pines PB1 y PB2, LEDs amarillos en PB2 y PB5 y por último, 2 LEDs rojos en PB3 y PB4. Todos estos conectados con cátodo común a tierra, para que dichos LEDs se enciendan con voltaje positivo. Esto se puede observar con mayor detalle en la siguiente imagen.

    ![Esquema eléctrico de conexión de los LEDs con cátodo común](images/image1.png "image_tooltip")
    \
    **Figura 1:** Esquema eléctrico de conexión de los LEDs con cátodo común.

    Con el esquema establecido, es necesario determinar el valor de las resistencias a utilizar, para ello, se hará uso de la Ley de Ohm, que establece que “La diferencia de potencial (tensión) U entre los terminales de un elemento de resistencia pura es **directamente proporcional a la intensidad de la corriente** i que circula a través de esta”.
  
    ![equation](http://latex.codecogs.com/gif.latex?u=iR)

    Donde R es la resistencia eléctrica del elemento.

    Por lo tanto, dado que se conoce tensión suminastrada por cada pin (5V) y la tensión que requiere cada color de LED (rojo=1.8V, verde=2.2V, amarillo=2.0V azul=3.0V) y se conoce la corriente que circulará por dicho elemento, se puede resolver para R la ecuación anterior. 

    Por lo tanto, aplicando la ecuación anterior a los datos disponibles se obtiene que el valor de las resistencias a colocar a cada uno de los LEDs rojos, verdes, amarillos y azules tendrían que ser de 320 Ω, 280 Ω, 300Ω y 200Ω respectivamente.

2. Para continuar, deberá incorporarse un pulsador al esquema planteado anteriormente, el cual se conectará en un extremo como entrada al PINC0 y el otro se conectará a GND.

    Además, para evitar la lectura de valores erróneos debido a factores externos en el estado de reposo del pulsador se habilitará el pull-up interno del MCU (vea el punto 3 para más detalles).

    ![Esquema eléctrico de conexión de los LEDs y pulsador](images/image2.png "image_tooltip")
    \
    **Figura 2:** Esquema eléctrico de conexión de los LEDs y pulsador.

    Ahora, la pregunta es, ¿qué es el efecto rebote? Se le llama así al efecto que se produce cuando se presiona un pulsador mecánico, dónde 2 conductores metálicos se unen. Para el usuario, el contacto se produce de manera inmediata, pero esto no es del todo cierto, debido a que dentro del pulsador hay partes móviles. Cuando se presiona el interruptor, las partes metálicas “rebotan” entre “contacto” y “no en contacto”. Es decir, “cuando el interruptor se cierra, los 2 contactos en realidad se separan y se vuelven a conectar, por lo general, de 10 a 100 veces durante aproximadamente 1ms” (Horowitz & Hill, 2a edición, pág. 506).

    Por lo general, el procesamiento del MCU es más rápido que el rebote, por lo que este interpreta dicho efecto cómo si el interruptor se ha presionado varias veces.

    ![alt_text](images/image3.png "image_tooltip")
     \
    **Figura 3:** Rebote de interruptor típico, sin mitigación.

    Este efecto puede ser mitigado mediante el uso de hardware y software.

    En el caso de la mitigación mediante hardware, es necesario convertir nuestro circuito en uno R-C, agregando un capacitor cerámico a este. 

    ![alt_text](images/image4.png "image_tooltip")
     \
    **Figura 4:** Circuito R-C para mitigar el efecto de rebote mediante hardware.

    En el capacitor se almacenarán cargas, lo que nos permitirá, de cierta manera “suavizar” (o filtrar) los saltos producidos por el efecto rebote.

    ![alt_text](images/image5.png "image_tooltip")
     \
    **Figura 5:** Mitigación del efecto rebote mediante hardware.

    La mitigación de este efecto mediante hardware tiene como desventaja que implica aumentar un poco la complejidad del circuito al agregar un componente más y lo que a su vez implica un aumento de los costos. Es por ello que se tiene la mitigación mediante software.

    La forma más fácil, sería agregando un tiempo de espera de Xms luego de recibido el primer rebote, así se ignoran las lecturas siguientes producidas por dicho efecto. La desventaja de esta solución es que se obliga al MCU a permanecer pausado mientras finaliza el período de espera.

    La solución más eficiente para manejar dicho problema sería haciendo uso de interrupciones para manejar el rebote del interruptor, siempre y cuando se tenga en cuenta que dicha interrupción se puede disparar tanto en el flanco de subida, como en el de bajada, lo cuál puede provocar que el MCU apile interrupciones en espera.

## Conclusiones

## Author
- [@JandroMejia97](https://www.github.com/JandroMejia97)
