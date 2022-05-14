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

    ![Esquema eléctrico de conexión de los LEDs con cátodo común](https://drive.google.com/uc?id=1Ph4TPi9YqpqtM0wc0RvTMYnveNQPNMmc)
    \
    **Figura 1:** Esquema eléctrico de conexión de los LEDs con cátodo común.

    Con el esquema establecido, es necesario determinar el valor de las resistencias a utilizar, para ello, se hará uso de la Ley de Ohm, que establece que “La diferencia de potencial (tensión) U entre los terminales de un elemento de resistencia pura es **directamente proporcional a la intensidad de la corriente** i que circula a través de esta”.

    ![equation](http://latex.codecogs.com/gif.latex?u=iR)

    Donde R es la resistencia eléctrica del elemento.


    Por lo tanto, dado que se conoce tensión suminastrada por cada pin (5V) y la tensión que requiere cada color de LED (rojo=1.8V, verde=2.2V, amarillo=2.0V azul=3.0V) y se conoce la corriente que circulará por dicho elemento, se puede resolver para R la ecuación anterior.

    ![equation](http://latex.codecogs.com/gif.latex?R=u/i)

    Por lo tanto, aplicando la ecuación anterior a los datos disponibles se obtiene que el valor de las resistencias a colocar a cada uno de los LEDs rojos, verdes, amarillos y azules tendrían que ser de 320 Ω, 280 Ω, 300Ω y 200Ω respectivamente.

2. Para continuar, deberá incorporarse un pulsador al esquema planteado anteriormente, el cual se conectará en un extremo como entrada al PINC0 y el otro se conectará a GND.

    Además, para evitar la lectura de valores erróneos debido a factores externos en el estado de reposo del pulsador se habilitará el pull-up interno del MCU (vea el punto 3 para más detalles).

    ![Esquema eléctrico de conexión de los LEDs y pulsador](https://drive.google.com/uc?id=1fzm9AWcW6gioLq-dgDV1dPlo3xC2TnpX)
    \
    **Figura 2:** Esquema eléctrico de conexión de los LEDs y pulsador.

    Ahora, la pregunta es, ¿qué es el efecto rebote? Se le llama así al efecto que se produce cuando se presiona un pulsador mecánico, dónde 2 conductores metálicos se unen. Para el usuario, el contacto se produce de manera inmediata, pero esto no es del todo cierto, debido a que dentro del pulsador hay partes móviles. Cuando se presiona el interruptor, las partes metálicas “rebotan” entre “contacto” y “no en contacto”. Es decir, “cuando el interruptor se cierra, los 2 contactos en realidad se separan y se vuelven a conectar, por lo general, de 10 a 100 veces durante aproximadamente 1ms” (Horowitz & Hill, 2a edición, pág. 506).

    Por lo general, el procesamiento del MCU es más rápido que el rebote, por lo que este interpreta dicho efecto cómo si el interruptor se ha presionado varias veces.

    ![Rebote de interruptor típico, sin mitigación.](https://drive.google.com/uc?id=1QvZ5QJXsUMuJdpHrVd8LKUCCVfwGb0FB)
     \
    **Figura 3:** Rebote de interruptor típico, sin mitigación.

    Este efecto puede ser mitigado mediante el uso de hardware y software.

    En el caso de la mitigación mediante hardware, es necesario convertir nuestro circuito en uno R-C, agregando un capacitor cerámico a este. 

    ![Circuito R-C para mitigar el efecto de rebote mediante hardware.](https://drive.google.com/uc?id=1fNn__CYsecopoJKTr0kFwVYveCfGhfhA)
    \
    **Figura 4:** Circuito R-C para mitigar el efecto de rebote mediante hardware.

    En el capacitor se almacenarán cargas, lo que nos permitirá, de cierta manera “suavizar” (o filtrar) los saltos producidos por el efecto rebote.

    ![Mitigación del rebote mediante hardware.](https://drive.google.com/uc?id=14qj-VRDvcmfcEFvwmyV09q6ByP1uuHqu)
    \
    **Figura 5:** Mitigación del efecto rebote mediante hardware.

    La mitigación de este efecto mediante hardware tiene como desventaja que implica aumentar un poco la complejidad del circuito al agregar un componente más y lo que a su vez implica un aumento de los costos. Es por ello que se tiene la mitigación mediante software.

    La forma más fácil, sería agregando un tiempo de espera de Xms luego de recibido el primer rebote, así se ignoran las lecturas siguientes producidas por dicho efecto. La desventaja de esta solución es que se obliga al MCU a permanecer pausado mientras finaliza el período de espera.

    La solución más eficiente para manejar dicho problema sería haciendo uso de interrupciones para manejar el rebote del interruptor, siempre y cuando se tenga en cuenta que dicha interrupción se puede disparar tanto en el flanco de subida, como en el de bajada, lo cuál puede provocar que el MCU apile interrupciones en espera.

    Para nuestro caso en particular, haremos uso del retardo, debido a qué por ahora no se tienen los conocimientos necesarios para implementar un vector de interrupciones en C.



3. Para resolver este problema, se deberán seguir los siguientes pasos
    1. **Configurar los puertos a usar:**
        1. Establecer todos los pines del puerto B cómo salida, lo cuál se logra poniendo unos en **DDRB**.
        2. Establecer el **PINC0 **cómo entrada, lo cuál se logra poniendo un cero en **DDRC0**, para este caso, se optó por establecer todo el puerto C como entrada (poner ceros en **DDRC**).
        3. Habilitar el pull-up del pin **PINC0**, esto se logra poniendo un uno en dicho registro.
    2. **Definir las secuencias:**
        4. Para mostrar la secuencia inicial  (b0 y b7 – b1 y b6 – b2 y b5 – b3 y b4) es necesario considerar que encender **b0 y b7** implica asignarle el valor **0x81 **en **PORTB**, mientras que para **b1 y b6, b2 y b5, b3 y b4**, se tendrían que asignar en dicho puerto los valores** 0x42, 0x24 y 0x18** respectivamente.
        5. Es necesario que cada uno de estos valores se mantengan en memoria, es por ello que se creará un vector con los valores mencionados anteriormente.
        6. Para asignar cada uno de los valores en **PORTB** será necesario ir recorriendo el vector que contiene la secuencia desde la posición cero, hasta la posición final.
        7. Dado que los valores asignados en **PORTB** para mostrar la secuencia **b3 y b4, b2 y b5, b1 y b6, b0 y b7** son los mismos de la secuencia inicial, pero con el orden invertido, se hará uso del mismo vector del punto anterior, pero se recorrerá desde el último elemento hasta el primero. 
        8. Para mostrar la secuencia se requerirá conocer el sentido de la secuencia y la posición del valor a mostrar en nuestro vector con la secuencia inicial.
    3. **Verificar si el estado del PINC0 es igual a cero:**
        9. Si es así (se seleccionó pull-up), se hace una espera de 10ms mientras se estabiliza el valor de la entrada por el efecto de rebote.
        10. Se deberá retener el flujo mientras el valor del **PINC0** sea cero, ya que esto implica que el pulsador se mantiene presionado.
        11. Luego que se ha liberado el pulsador, se hace nuevamente una espera de 10ms.
        12. Se cambia el flag que indica el sentido de la secuencia y se restablece la posición a mostrar.
    4. **Caso contrario:**
        13. Se incrementa la posición a mostrar del vector de secuencias
        14. Para no sobrepasar los límites del arreglo se tendrá que obtener el resto de dividir la posición entre la longitud del arreglo.
4. Cómo se mencionó anteriormente, la ventaja de usar el retardo bloqueante (o tiempo de espera) es que no se requiere de hardware para mitigar el efecto de rebote, pero dicho método tiene como desventaja que obliga al MCU a permanecer pausado mientras finaliza el período de espera, quedando la CPU inutilizada y desperdiciando tiempo en el que se podrían realizar otras operaciones.

    En el caso de mantener presionado el pulsador, esto se mitiga con lo mencionado en el punto 3.c.

## Validación

La simulación arranca ejecutando inicialmente la secuencia  b0 y b7, b1 y b6, b2 y b5, b3 y b4. A continuación se muestran capturas de pantallas del funcionamiento.

![Secuencia inicial, LEDs b0 y b7 activos.](https://drive.google.com/uc?id=1K7F0onQyKPhy8aFoeSe9VWtEGJGQw3og)
 \
**Figura 6:** Secuencia inicial, LEDs b0 y b7 activos.

![Secuencia inicial, LEDs b1 y b6 activos.](https://drive.google.com/uc?id=1zs8LfeJDp0R3z_jUdnh4bMD5xzyEONTS)
 \
**Figura 7:** Secuencia inicial, LEDs b1 y b6 activos.

![Secuencia inicial, LEDs b2 y b5 activos.](https://drive.google.com/uc?id=1jfg6uYZ-cd4cVyOhcEPvD0XXC0J0jsET)
 \
**Figura 8:** Secuencia inicial, LEDs b2 y b5 activos.

![Secuencia inicial, LEDs b3 y b4 activos.](https://drive.google.com/uc?id=1UrjyQpdziYhZ03KhTMpCGkCB_euOc8Dd)
 \
**Figura 9:** Secuencia inicial, LEDs b3 y b4 activos.

Al presionar el pulsador la secuencia mostrada se invierte, a continuación capturas de pantalla:

![Secuencia inicial, LEDs b3 y b4 activos.](https://drive.google.com/uc?id=1pbiHx-Dpq_SQX66HUdFQr2I_OgCCdLwk)
 \
**Figura 10:** Secuencia inicial, LEDs b3 y b4 activos.

![Secuencia inicial, LEDs b2 y b5 activos.](https://drive.google.com/uc?id=1jgF119y2QdxTDR8fD1r4jTAKdkEW6YJd)
 \
**Figura 11:** Secuencia inicial, LEDs b2 y b5 activos.

![Secuencia inicial, LEDs b1 y b6 activos.](https://drive.google.com/uc?id=1PMGnf8jZ3LuZ3LcEiv-9iW1AwZ98W-h_)
 \
**Figura 12:** Secuencia inicial, LEDs b1 y b6 activos.

![Secuencia inicial, LEDs b0 y b7 activos.](https://drive.google.com/uc?id=1Z1QP2G7AzGllnCYl_dHdk5poAQbfCXE4)
 \
**Figura 13:** Secuencia inicial, LEDs b0 y b7 activos.

## Bibliografía

* Display de 7 segmentos ánodo y cátodo común. Disponible en: [Display 7 Segmentos ánodo y cátodo común - HETPRO/TUTORIALES (hetpro-store.com)](https://hetpro-store.com/TUTORIALES/display-7-segmentos-anodo-catodo-comun/)
* Resistencia de LED, Cómo calcularla en función a la corriente. Disponible en: [Resistencia de LED, Como calcularla en función a la corriente - HeTPro (hetpro-store.com)](https://hetpro-store.com/TUTORIALES/resistencia-de-led/)
* Resistencia pull-up y pull-down. Disponible en: [Resistencia pull up y pull down con Arduino, para qué sirven (programarfacil.com)](https://programarfacil.com/blog/arduino-blog/resistencia-pull-up-y-pull-down/)Switch Bounce and How to Deal with it. Disponible en: [Switch Bounce and How to Deal with It - Technical Articles (allaboutcircuits.com)](https://www.allaboutcircuits.com/technical-articles/switch-bounce-how-to-deal-with-it/)

## Author
- [@JandroMejia97](https://www.github.com/JandroMejia97)
