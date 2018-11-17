# Compilación de los puntos

Para compilar, se cuenta con un makefile con su regla por default.

```bash
$ make
```

__Nota: Para que funcione, se debe contar con el jar de JADE__
__situado en la carpeta `lib`, en el directorio raiz del proyecto__

Luego, simplemente se debe levantar JADE.

Esto puede hacerse haciendo uso del makefile, con la regla `start-gui`

```bash
$ make start-gui
```

Por último, se debe correr algúno de los puntos.

Para los primeros 2 se cuenta con reglas de make

```bash
$ make run-punto1
$ make run-punto2
```

Para el tercer punto, se cuenta con un script bash dentro del directorio `punto3`, llamado `run`

En el script se cuenta con una sección de ayuda, simplemente ejecutando

```bash
$ ./run -h
# o bien
$ ./run --help
# o bien
$ ./run
```