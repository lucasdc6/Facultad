2)
  a) La imagen pesa 79.6MB. No, no es un container aún.
  b) docker run --rm ubuntu:latest ls -l

  total 64
  drwxr-xr-x   2 root root 4096 Apr 26 21:17 bin
  drwxr-xr-x   2 root root 4096 Apr 24 08:34 boot
  drwxr-xr-x   5 root root  340 May 16 01:43 dev
  drwxr-xr-x  32 root root 4096 May 16 01:43 etc
  drwxr-xr-x   2 root root 4096 Apr 24 08:34 home
  drwxr-xr-x   8 root root 4096 Apr 26 21:16 lib
  drwxr-xr-x   2 root root 4096 Apr 26 21:16 lib64
  drwxr-xr-x   2 root root 4096 Apr 26 21:16 media
  drwxr-xr-x   2 root root 4096 Apr 26 21:16 mnt
  drwxr-xr-x   2 root root 4096 Apr 26 21:16 opt
  dr-xr-xr-x 228 root root    0 May 16 01:43 proc
  drwx------   2 root root 4096 Apr 26 21:17 root
  drwxr-xr-x   5 root root 4096 Apr 27 23:28 run
  drwxr-xr-x   2 root root 4096 Apr 27 23:28 sbin
  drwxr-xr-x   2 root root 4096 Apr 26 21:16 srv
  dr-xr-xr-x  13 root root    0 May 16 01:38 sys
  drwxrwxrwt   2 root root 4096 Apr 26 21:17 tmp
  drwxr-xr-x  11 root root 4096 Apr 26 21:16 usr
  drwxr-xr-x  13 root root 4096 Apr 26 21:17 var

  c) Se ejecuta el programa /bin/bash en modo no interactivo, por lo que muere
al instante
    I) docker run -it --rm ubuntu /bin/bash
    II) touch so2018
  d) No existe, ya que el container se crea al ejecutar docker run, y muere al
salir. Para ver el archivo se debería levantar el MISMO container que se
encuentra en estado Exited.

  e) docker start -ia `docker ps -a | grep ubuntu | awk '{print $1}'`
    I) Se obtiene ejecutando docker ps -a
    II) Si, se encuentra donde lo cree (yey!).
  f) Ninguno. Se encuentran en estado "Exited"
  g) docker ps -a | grep ubuntu | awk '{print $1}' | xargs docker rm

3)
  a) docker run -it --name ubuntu ubuntu bash
  b) Instalado
  c) docker commit <hash> (o en mi caso, ubuntu)
     Se genera con el nombre y tag <none>
  d) docker tag <hash> apache2:v1
  f) docker run --rm -v /apachedata:/var/www/html -p 8080:80 apache2:v1
/usr/sbin/apache2ctl -D FOREGROUND
  g) No es necesario reinicar el container
  h) Es necesario, ya que al terminar de ejecutar el comando, bash termina su
ejecución, deteniendo el container de no tener un proceso a quien dejar en
foreground

4) b) docker build --tag apache2:so2018 .

5) Es un tipo especial de filesystem que permite formar el sistema de archivos
mediante la unión de otros sistemas de archivos.
Docker utiliza aufs y overlay (y también su versión overlay2)

6) Los containers tienen direcciones ip del tipo 172.17..0.x
  Por defecto, para referenciar a la máquina host desde un container, se cuenta
con la dirección 172,17.0.1

7) docker puede utilizar cualquiera de los siguientes tipos de redes:
  - bridge (por defecto utiliza este tipo de redes para la comunicación
    host-container)
  - host
  - overlay
  - macvlan
  - none
