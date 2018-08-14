● Número de problema: 1
● Descripción del problema: RIP versión 1
● Lugar donde ocurre: n1
● Solución: Pasar protocolo a versión 2.
  $ vtysh
  $ conf t
  $ router rip
  $ version 2
● Evidencia de que la solución funciona adecuadamente: Ahora el router n1,
actualiza las rutas en su tabla de ruteo.
--------------------------------------------------------------------------
● Número de problema: 2
● Descripción del problema: Router no expone network 10.0.7.0/24
● Lugar donde ocurre: n6
● Solución: Agregar network 10.0.7.0/24 a RIP
  $ vtysh
  $ conf t
  $ router rip
  $ network 10.0.7.0/24
● Evidencia de que la solución funciona adecuadamente: El resto de los router
actualizan sus tablas de rutas con la red 10.0.7.0/24
--------------------------------------------------------------------------
● Número de problema: 3
● Descripción del problema: Ruta estática configurada
● Lugar donde ocurre: n4
● Solución: Eliminar ruta estática para evitar loop.
  $ vtysh
  $ conf t
  $ no ip route 10.0.7.0/24 10.0.5.2
● Evidencia de que la solución funciona adecuadamente: Ahora el router pasa los
paquetes al router n6
