# Práctica 2
## Sistemas Paralelos - UNLP

En este directorio podemos encontrar los ejercicios resueltos de la prácticas 2 de la materia Sistemas Paralelos.

Para compilar todos los puntos, se debe contar con el comando `make`, y ejecutar:

```bash
$ make
```

Todos los compilados se van a encontrar en `bin`

## Templates

Para probar el funcionamiento de `pthreads`, se puede modificar y compilar los archivos de `templates`

Se cuenta con 2 archivos base, `simple` y `struct`

Para compilar, se debe ejecutar:

```bash
$ make templates
```

### simple

En este archivo, se cuenta con el funcionamiento más básico de pthreads. Cada thread va a contar con solamente su id como parámetro.

### struct

En este caso, cada archivo va a contar con una estrutura definida de antemano (`options`), donde se le van a poder pasar varios parámetros a cada thread.

## Makefile

Para compilar un nuevo archivo, no hace falta agregarlo a las reglas del Makefile. Con agregarlo en alguna de los directorios `src` o `templates`, automáticamente se compilaran en la siguiente ejecución de `make` o `make templates` respectivamente.