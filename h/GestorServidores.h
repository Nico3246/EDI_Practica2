//
// Created by nicob on 15/05/2025.
//

#ifndef EDI_PRACTICA2_GESTORSERVIDORES_H
#define EDI_PRACTICA2_GESTORSERVIDORES_H
#include "cabeceras.h"
#include "Servidor.h"


class GestorServidores{

    Servidor *primerServidor; //puntero al primer elemento/servidor dentro de la estructura de nodos
    //enlazados/objetos de la clase Servidor, representativa del conjunto de servidores utilizados para
    //gestionar las partidas multijugador online de los distintos juegos de la compañía.

    int numServidores; //número de servidores de juego desplegados gobernados por el gestor.
    Servidor *getPunteroServidor(int pos);//
public:
    GestorServidores();//
    //método constructor que inicializará convenientemente los atributos de la clase a los valores por
    //defecto convenidos.
    ~GestorServidores();//
    //método destructor que liberará la memoria reservada para los artefactos dinámicos que integran
    //la estructura de nodos enlazados correspondiente al conjunto de servidores.
    int getNumServidores();//
    //devuelve el valor del atributo numServidores.
    bool desplegarServidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG);//
    //desplegará un nuevo servidor de juego en el sistema. Para ello, creará un objeto de la clase
    //Servidor, cuya dirección/hostname será dS, el juego ejecutado nJ, su identificador i, el máximo de
    //jugadores que puede alojar será mxL, y el máximo de jugadores que pueden estar en espera de conexión
    //mxC; su puerto de escucha será p, y el nombre del país en donde está físicamente instalado lG.
    //Este nuevo objeto será integrado en la estructura del nodos, y su estado por defecto será INACTIVO.
    //Estos nodos están ordenados por orden alfabético ascendente según el nombre del país en el que cada
    //servidor está ubicado (atributo localizacionGeografica). El nuevo nodo será añadido en dicha
    //estructura respetando este requisito. El método devolverá true si el despliegue del nuevo nodo es
    //completado con éxito; false en caso contrario, bien porque no haya sido posible reservar memoria
    //para crear el nuevo objeto, o bien porque ya existiese en la estructura de nodos otro Servidor con
    //el mismo nombre, o bien el mismo identificador que el nuevo elemento a integrar en la estructura.

    bool desconetarServidor(cadena dS);
    //el método intentará desconectar (poner en estado INACTIVO) el servidor cuya dirección/hostname
    //coincide con el valor indicado en el parámetro de entrada dS. Si el servidor a desactivar estaba
    //ACTIVO, será necesario expulsar a los jugadores que estaban en espera, y redirigir a los que estaban
    //ya alojados en el servidor a otros nodos activos del sistema con el mismo juego instalado. El
    //proceso de redistribución de los jugadores priorizará aquellos con menor tiempo de respuesta (ping).
    //La distribución se realizará de forma equitativa entre los distintos servidores activos del sistema,
    //esto es, cada jugador considerado será alojado en el servidor con el mayor número de espacios
    //disponibles en su correspondiente lista de jugadores conectados. El mismo criterio se seguirá en
    //caso de no poder alojar al jugador que toca al alguno de los servidores al estar todos llenos, y
    //tener que incluirlo en alguna cola de espera. Aquellos jugadores para los que no haya espacios
    //disponibles en alguno de los servidores, ni en ninguna de las colas de espera, serán expulsados
    //del sistema.

    bool conectarServidor(cadena dS);
    //el método permite activas (poner en estado ACTIVO) el servidor cuya dirección/hostname coincide
    //con el valor indicado en el parámetro de entrada dS. Devolverá true en caso de activar exitosamente
    //el servidor indicado; false en caso contrario, bien porque el servidor ya estaba activo, o bien
    //porque directamente no existía ningún nodo con la dirección/hostname indicado.

    bool realizarMantenimiento(cadena dS);
    //el método permite poner en estado MANTENIMIENTO el servidor cuya dirección/hostname coincide con
    //el valor indicado en el parámetro de entrada dS. Devolverá true en caso de poner exitosamente el
    //servidor indicado en mantenimiento; false en caso contrario, bien porque el servidor ya estaba en
    //dicho estado, o bien porque directamente no existía ningún nodo con la dirección/hostname indicado.

    bool eliminarServidor(cadena dS);
    //el método eliminará de la estructura de nodos enlazados el servidor cuya dirección/hostname coincide
    //con el valor indicado en el parámetro de entrada dS. Este método es aplicable solamente sobre
    //aquellos servidores en estado INACTIVO o MANTENIMIENTO. El método devolverá true en caso de
    //eliminarse de forma exitosa el servidor indicado; falso en caso contrario, esto es, cuando no
    //exista ningún nodo con la dirección/hostname indicado, o bien el servidor afectado no esté INACTIVO
    //o en MANTENIMIENTO.

    bool alojarJugador(Jugador j, cadena nomJuego, cadena host, bool &enEspera);//
    //el método intentará alojar al jugador (tipo Jugador) j en algún servidor ACTIVO para el juego de
    //nombre nomJuego. Si no se encuentra ningún servidor activo del juego indicado, el método finalizará
    //devolviendo false, además de otro false a través del parámetro por referencia enEspera. En caso
    //contrario, criterio será el de alojar al jugador en el servidor cuya diferencia entre el número
    //máximo de jugadores soportado y el número de usuarios actualmente conectados sea la mayor. Si se
    //encuentra algún servidor con conexiones disponible el jugador será alojado en éste añadiéndolo a
    //la lista jugadoresConectados correspondiente. El método finalizará devolviendo true, junto con la
    //dirección/hostname del servidor a través del parámetro de entrada/salida host. Si por contra no
    //hay espacio disponible en ninguno de los servidores, se intentará añadir al jugador a alguna de
    //las colas de espera. El criterio será el de añadir al jugador a aquella cola para la que la
    //diferencia entre el número máximo de jugadores que pueden estar en espera, y el número de elementos
    //ya encolados es la mayor. En caso de encolar al jugador en alguna cola de espera, el método
    //devolverá un false, además de un true a través del parámetro por referencia enEspera, indicando
    //así que el jugador no ha podido ser alojado en alguno de los servidores, y que se encuentra a la
    //espera de poder conectarse a alguno. Además, en ese caso se indicará el nombre/dirección del
    //servidor dónde está encolado a través del parámetro de entrada/salida host. Si el jugador no ha
    //podido ser conectado ni encolado en una estructura de espera, el método finalizará nuevamente
    //devolviendo un false, junto con otro false a través del parámetro por referencia enEspera.

    bool expulsarJugador(cadena nJ, cadena host);
    //el método expulsará al jugador de nombre nJ de cualquier servidor o cola de espera del sistema
    //en la que esté ubicado. El método devolverá true en caso de localizar y expulsar al jugador
    //indicado, devolviendo además la dirección/hostname del servidor en el que estaba conectado o bien
    //a la espera de acceso al mismo; false en caso contrario, al no encontrarse en el sistema el jugador
    //indicado. Si el jugador en cuestión estaba conectado a un servidor, al ser expulsado habrá que
    //garantizar que, en caso de haber jugadores en cola de espera para acceder al mismo, el primero de
    //dicha estructura pase a ser alojado en este servidor de forma automática.

    int getPosicionServidor(cadena dS);//
    //el método devolverá la posición en la que se encuentra el servidor cuya dirección/hostname es igual
    //a dS dentro de la secuencia que forman el conjunto de nodos enlazados, siendo el primer nodo el
    //que ocupa la posición 1. Si no hay en la estructura de nodos enlazados ningún servidor con la
    //dirección indicada, el método devolverá un -1.

    void mostrarInformacionServidores(int pos);
    //muestra por pantalla información del servidor que se encuentra en la posición indicada por el
    //parámetro pos dentro de la secuencia de nodos-servidores, dónde el primer servidor es el situado
    //en la posición 1. Si la posición indicada está fuera de rango, deberá informarse al usuario de tal
    //circunstancia a través de un mensaje de error. Si la posición indicada a través de pos es -1,
    //deberá mostrarse por pantalla información sobre la totalidad de los servidores contenidos en la
    //estructura de nodos enlazados. Para servidores activos, será también necesario mostrar por pantalla
    //los datos de los jugadores conectados, así como la de aquellos que estén en la cola de acceso al
    //mismo.

    bool jugadorConectado(cadena nJ, cadena dS);
    //el método devolverá true si el jugador con nombre nJ está conectado al servidor con
    //dirección/hostname dS; false en caso contrario.

    bool jugadorEnEspera(cadena nJ, cadena dS);
    //el método devolverá true si el jugador con nombre nJ está en la cola de espera del servidor con
    //dirección/hostname dS; false en caso contrario.

    bool jugadorConectado(cadena nJ);
    //el método devolverá true si el jugador con nombre nJ está conectado a alguno de los servidores
    //activos del sistema.

    bool jugadorEnEspera(cadena nJ);
    //el método devolverá true si el jugador con nombre nJ está en la cola de espera de alguno de los
    //servidores activos del sistema.
};

#endif //EDI_PRACTICA2_GESTORSERVIDORES_H
