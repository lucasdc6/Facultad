# Entrega

Autor: Lucas Di Cunzolo
Legajo: 13572/5

## Punto 4

Ya se solucionaron todos los problemas anteriormente planteados.

La idea general de la MT es la siguiente:

Se cuenta con las MT anteriormente planteadas, una MT que realiza corrimientos
a la derecha, agregando un 1 en la posición actual.

Una MT que realiza un corrimiento a la izquierda, pisando el valor de la celda actual.

Para buscar los estados a cambiar, en principio, se plantea un estado que se detiene
en la tercer componente de la quintupla (estado a verificar), y comprueba si se trata
de un estado con el cual se tena que operar (qa o qr), para esto existen estados
qsa y qsr.
De ser uno de los estados buscados, lo marca.

Luego realiza la acción necesaria dependiendo el caso.
Si es un qa, realiza la inserción del valor 1, corriendo todos los valores a la derecha.
De ser un qr, realiza un corrimiento a izquierda sobre dicho estado, para eliminar un valor 1.
Cualquier otro estado será ignorado.

Con esto, se asegura que la salida de la MT será la misma MT que ingresó, solo que con los estados
qa y qr cambiados.