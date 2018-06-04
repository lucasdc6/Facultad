● Número de problema: 1
● Descripción del problema: Los routers tienen diferentes claves en sus interfaces para comunicarse en el área 5.
● Lugar donde ocurre: router n20 y n21
● Solución: Cambiar la comunicación entre los routers a texto plano o a md5(ambos tienen que tener la misma):
En el router n20
  $ vtys
  $ conf t
  $ interface eth0
  $ no ip ospf message-digest-key 1
  $ ip ospf authentication-key clave
● Evidencia de que la solución funciona adecuadamente
Al configurar correctamente el router n20, el área 5 se sincroniza.
--------------------------------------------------------------------------
● Número de problema: 2
● Descripción del problema: Las estáticas configuradas tienen una vía
inexistente. En cuanto a la estática hacia la red "10.0.4.0/24", se
prefiere utilizar el protocolo RIP para conseguir el camino hacia dicha red.
● Lugar donde ocurre: router n2
● Solución: Corregir las rutas estáticas
  $ vtys
  $ conf t
  $ no ip route 10.0.16.0/24 10.0.3.3
  $ ip route 10.0.16.0/24 10.0.3.2
● Evidencia de que la solución funciona adecuadamente
Ahora se puede llegar a las redes 10.0.16.0/24
-------------------------------------------------------------------------
● Número de problema: 3
● Descripción del problema: Falta ruta por defecto en el host n16.
● Lugar donde ocurre: host n16
● Solución: Agregar ruta por defecto
  $ ip route add default via 10.0.15.1
● Evidencia de que la solución funciona adecuadamente
Ahora es posible llegar fuera de la red.
-------------------------------------------------------------------------
● Número de problema: 4
● Descripción del problema: El enlace entre n3 y n4 tiene perdida de paquetes
● Lugar donde ocurre: Enlace entre n3 y n4
● Solución: Forzar a utilizar una ruta por zona "Bosque"
Para esto se tiene que forzar desde ambos lados, desde el área "este" y desde "backbone"
Configuración desde área backbone.
Primero se debe permitir injectar rutas rip en el área Bosque, para redistribuirlas en el área backbone con menor métrica que ospf.
Para esto, se cambia tipo de área de "stub" a "nssa"
  $ vtys
  $ conf t
  $ router ospf
  $ no area 2 stub
  $ area 2 nssa translate-always
(Eso se debe hacer en cada router del área)
Luego, en el ABR del área "Bosque-Este", se debe redistribuir rip con menor métrica que OSPF(20 por defecto).
  $ vtysh
  $ conf t
  $ router ospf
  $ redistribute rip metric 20
Luego, se verá que se empiezan a redistribuir las rutas hacia la red 10.0.4.0/24 por el área "Bosque"
El área "Este", irá automáticament por el el área "Bosque", al éste último convertirse en NSSA, ya que comenzará a publicar rutas OSPF en el área RIP.
● Evidencia de que la solución funciona adecuadamente
Ahora los ping no tienen perdida de paquetes.
-------------------------------------------------------------------------
● Número de problema: 5
● Descripción del problema: Falta una ruta estática en el router n8, para llegar a la red.
● Lugar donde ocurre: router n8.
● Solución: Se puede agregar una ruta por hacia la red 10.0.0.0/8 via el ABR del área.

● Evidencia de que la solución funciona adecuadamente
Ahora se puede llegar a la red desde el área de internet.

