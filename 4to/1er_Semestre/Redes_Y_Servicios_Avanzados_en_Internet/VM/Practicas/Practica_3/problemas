router n6 publica red 10.0.4.0/24 en area 1

solucion:
vtysh
conf t
router ospf
no network 10.0.4.0/24 area 1
network 10.0.4.0/24 area 0

funcona, porque ahora en "sh ip opsf route" completa con las redes vecinas.

router n1, tiempo Hello no igual al resto de los routers(en 20s)
solucion, ponerlo en valor estandar: 10s
vtysh
conf t
interface eth0
ospf hello-interval

funciona porque aparecen el vecino en la interface eth0


n2, hello(12) en interface eth0

n4,hello (12) y dead (60) eth1

n6, hello(12), y dead(60) eth0
