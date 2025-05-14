#ifndef EDI_PRACTICA2_SERVIDOR_H
#define EDI_PRACTICA2_SERVIDOR_H
#include "cabeceras.h"

class Servidor{
    cadena direccionServidor; //direccion IP/hostname del servidor de juegos.
    cadena nombreJuego; //nombre del juego jugado en el servidor.
    int id; //código numérico (entero positivo) utilizado en el ámbito interno de la compañía para
    //identificar de forma unívoca cada servidor que ésta gestiona.
    Servidor *siguienteServidor; //puntero al siguiente servidor del sistema.
    int maxJugadoresConectados; //número máximo de jugadores que pueden ser alojados en el servidor.
    int maxJugadoresEnEspera; //número máximo de jugadores que pueden estar en espera para acceder al
    //servidor.
    lista jugadoresConectados; //lista de jugadores alojados en el servidor. Los jugadores aparecen
    //ordenados en la lista según su puntuación, y de forma ascendente en
    //relación al valor de ésta.
    cola jugadoresEnEspera; //cola de jugadores en espera de poder acceder al servidor.
    cadena estado; //estado actual del servidor. Para este atributo sólo son posibles los valores que
    //siguen: ACTIVO, INACTIVO o MANTENIMIENTO.
    int puerto; //número del puerto de escucha del servidor;
    cadena localizacionGeografica; //país en el que se encuentra ubicado físicamente el servidor.
public:
    ~Servidor();
    Servidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG);
    //método constructor que inicializa los atributos direccionServidor, nombreJuego, id,
    //maxJugadoresConectados, maxJugadoresEnEspera, puerto y localizacionGeografica con,
    //respectivamente, dS, nJ, i, mxL, mxC, p y lG. Además, inicializa el atributo estado a “INACTIVO”.

    int getId();
    //devuelve el valor del atributo id.
    void getDireccionServidor(cadena dS);
    //devuelve el valor de direccionServidor a través del parámetro de entrada/salida dS.
    void setSiguienteServidor(Servidor *pS);
    //asigna el valor recibido como parámetro al atributo siguienteServidor.

    Servidor* getSiguienteServidor();
    //devuelve el valor del atributo siguienteServidor.

    bool conectarJugador(Jugador j);
    //aloja al jugador j en el servidor, esto es, lo añade a la lista listaConectados siempre y cuando
    //no se haya alcanzado el número máximo de jugadores. Devolverá true si el jugador finalmente es
    //alojado en el servidor; false en caso contrario. Los jugadores se almacenan en la lista por
    //puntuación ascendente, por lo que el jugador deberá ser añadido a aquella posición para la que
    //se garantice el cumplimiento de esta regla de negocio.

    bool ponerJugadorEnEspera(Jugador j);
    //encola al jugador j en la cola de espera jugadoresEnEspera, comprobando previamente que el servidor
    //ha alcanzado el número máximo de conexiones, y de que por otra parte no se ha alcanzado el número
    //máximo de jugadores que pueden estar en espera para acceder al servidor. Devolverá true en caso de
    //enconlar exitosamente al jugador; false en caso contrario.

    void mostrarJugadoresConectados();
    //muestra por pantalla el nombre, el identificador numérico, el ping(latencia), la puntuación global
    //y el país desde el que se conecta cada uno de los jugadores alojados en el servidor.

    void mostrarJugadoresEnEspera();
    //muestra por pantalla el nombre, el identificador numérico, el ping(latencia) y la puntuación global
    //y el país desde el que se conecta cada uno de los jugadores que se encuentran esperando poder
    //acceder al servidor.
    bool estaActivo();
    //devuelve true si el estado del servidor es ACTIVO; false en caso contrario.

    bool activar(); //activa un servidor en estado INACTIVO o MANTENIMIENTO. Si el servidor ya estaba
    //activado, el método devolverá false; true en caso contrario, confirmando así que el servidor ha
    //sido activado.

    bool desactivar();
    //desactiva un servidor en estado ACTIVO o MANTENIMIENTO. Si el servidor ya estaba desactivado, el
    //método devolverá false; true en caso contrario, confirmando así que el servidor ha sido desactivado.
    //Si el servidor a desactivar está previamente activo, será necesario vaciar tanto la lista de
    //jugadores conectados como la cola de aquellos que están esperando poder conectarse.

    bool ponerEnMantenimiento();
    //pone un servidor en MANTENIMIENTO. Sólo es posible pasar al estado MANTENIMIENTO para aquellos
    //servidores que están INACTIVOS. El método devolverá true en caso de poder poner al servidor en
    //MANTENIMIENTO; false en caso contrario, esto es, cuando el servidor está previamente ACTIVO, o bien
    //ya está en MANTENIMIENTO.

    void mostrarInformacion();
    //muestra por pantalla información de interés del servidor. En concreto, muestra la dirección y el
    //identificador del servidor, su estado, la relación entre el máximo de jugadores que puede alojar y
    //el número real de jugadores conectados. También mostrará el número máximo de jugadores que pueden
    //estar esperando acceso, junto con el número de elementos tipo Jugador encolados en jugadoresEnEspera
    //con dicho propósito. Finalmente, también mostrará el puerto de escucha del servidor y la latencia
    //media de los jugadores conectados, y la localización geográfica del servidor (país).

    bool expulsarJugador(cadena nombre);
    //expulsa el jugador cuyo nombreJugador coincide con el parámetro nombre de la lista de conectados,
    //o bien de la cola de espera, en función de dónde esté contenida la instancia de tipo Jugador
    //correspondiente. Si el jugador es localizado en alguna de estas estructuras y convenientemente
    //eliminado el método devolverá true; false en caso contrario. Si el jugador a expulsar es localizado
    //en la lista de jugadores conectados, tras eliminarlo, será necesario comprobar si hay alguien en
    //la lista de espera. En caso positivo, el primero de la cola será automáticamente conectado
    //al servidor, pasando a la lista de conectados.

    void getNombreJuego(cadena nJ);
    //devuelve el valor del atributo nombreJuego a través del parámetro de entrada/salida nJ.

    int getPuerto();
    //devuelve el valor del atributo puerto.
    void getLocalizacionGeografica(cadena lG);
    //devuelve el valor del atributo localizacionGeografica a través del parámetro de entrada/salida lG.

    int getMaxJugadoresConectados();
    //devuelve el valor del atributo maxJugadoresConectados.

    int getMaxJugadoresEnEspera();
    //devuelve el valor del atributo maxJugadoresEnEspera.

    int getNumJugadoresConectados();
    //devuelve el número de jugadores conectados al servidor.

    int getNumJugadoresEnEspera();
    //devuelve el número de jugadores en la cola de espera de acceso al servidor.

    void exportarJugadoresConectados(Jugador *conectados);
    //el método copiara todos los jugadores alojados en el servidor en el vector dinámico accesible desde
    //el puntero conectados, parámetro de entrada.

    void exportarJugadoresEnEspera(Jugador *enEspera);
    //el método copiara todos los jugadores que están en la cola de espera para el acceso al servidor en
    //el vector dinámico accesible desde el puntero conectados, parámetro de entrada.
};


#endif //EDI_PRACTICA2_SERVIDOR_H
