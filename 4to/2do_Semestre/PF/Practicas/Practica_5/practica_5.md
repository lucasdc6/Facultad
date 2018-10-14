# Practica 5

## Punto 3

Siempre se puede asegurar que una función definida por recursión estructural termina. Esto es porque todo tipo definido por recursión cuenta con elementos finitos, por lo que la recursión, tarde o temprano va a llegar a un elemento atómico que corte la recursión.
La diferencia es que en este caso, se puede utilizar las propiedades de un conjunto definido por recursión estructural.

## Punto 4

### A

Si la variable xs es del tipo lista de listas, es una expresión válida.
De ser una variable del tipo lista, no lo es.

### B

Si la variable xs es una lista, o lista de listas, es una expresión válida.
De ser una variable de un tipo diferente a lista, no lo es.

### C

No hay tipo posible de xs para que quede tal valor.
Esto se debe a que aunque xs fuese del tipo lista de listas, al concatenar (operador ++), siempre tiene que existir el elemento `[]`

### D

No hay tipo posible de xs para que quede tal valor.
Para algo similar al insiso anterior, aunque xs fuese una lista de listas, y se permita apendear la lista vacía a la variable xs, siempre tiene que existir en el inicio de la nueva lista, el elemento `[]`

### E

No hay tipo posible de xs para que quede tal valor.
De igual manera que con el insiso C, aunque xs fuese una lista de elementos, la concatenación siempre daría como resultado una lista que contenga ambos elementos, es decir, que tiene que estar presente `[]`