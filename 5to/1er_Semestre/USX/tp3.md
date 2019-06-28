# Accesibilidad y las aplicaciones Ajax

Lucas Di Cunzolo, 13572/5

## Introducción

Utilizando la técnica AJAX, nuestras aplicaciones pasan a ser mucho mas interactivas, y con esto, se plantea un uso mucho más cercano al usuario.

Se buscan analizar rápidamente las posibles aplicaciones de AJAX utilizando las tecnologías actuales, para el desarrollo de aplicaciones en diferentes plataformas, teniendo en cuenta el estado del arte, y su aplicación con diferentes frameworks y librerías actuales.

## Definición de AJAX

De sus siglas, `Asynchronous Javascript and XML`, es una técnica para implementar páginas interactivas. Para esto, hace uso de varias tecnologías, como lo son el lenguajes `JavaScript` y `XML` (o actualmente `JSON`)

Se hace uso del lenguaje `JavaScript` ya que es necesario que esta técnica se ejecute en el cliente, para proveer una manera de comunicación más guiada por el usuario.

Para esto, `JavaScript` utiliza varias tecnologías, como lo pueden ser `Promises` para el manejo del asincronismo, `JSON` para la lectura y el envío de datos, y `Selectors`, `jQuery`, `React`, `Vue` o cualquier tecnología que nos permita manejar el `DOM` para su eventual actualización.

Actualmente se empezó a utilizar el estándar `JSON`, puesto que es la notación nativa de `JavaScript`.

## Donde se puede aplicar AJAX

### AJAX aplicado a formularios

Para plantear un formulario más interactivo, se puede ir consultando los datos requeridos por el formulario a medida que se van necesitando.

Por ejemplo, al momento de cargar paises, provincias y ciudades, se puede acotar mucho el conjunto de datos de provincias si se consultan solo las del país seleccionado. De igual manera se aplican a las ciudades de una provincia.

Esto no solo reduce el tamaño de la consulta para mostrar el HTML, sino que también mejora la navegabilidad del formulario.

### AJAX aplicado a listados

Para plantear listados de grantes cantidades de datos, se puede utilizar AJAX para manejar un paginado del lado del servidor (asistido por la base de datos de ser necesrio), esto mejora de manera considerable la velocidad de carga de una página. Con esta técnica, simplemente se consultan `n` cantidad de datos, pudiendo consultar los siguientes o los anteriores, pisando los actuales. Esto puede que muestre una baja en la performance entre los campos de páginas, pero la primer carga debería ser mucho más rapida.

### AJAX aplicado a búsquedas

Otra de las funcionalidades interesantes desarrollables utilizando AJAX, es la posibilidad de búsquedas en "tiempo real", buscando en el total (o un subconjunto) de los datos. Cada caso va a utilizar los datos de la manera que mejor lo crea.

### AJAX aplicado a refresco en "tiempo real"

También se podría contar con una suerte de "timer" que nos marque cada cuando se debe refrescar ciertos datos en una pantalla. Esto solo cambiaría los datos de una sección en específico.

### AJAX aplicaciones vs páginas

Con AJAX, se puede brindar una experiencia de uso similar a lo que es un programa nativo del sistema operativo. Esto se puede lograr, ya que no es necesario el recargo de toda la página cuando nos movemos entre secciones, simplemente se consulta los datos de esa sección, y se cambia el contenido de la misma.

Esto se puede aplicar tanto a SPA (Single Page Aplicactions), como a aplicaciones más complejas. Podemos ver ejemplos en la web, como por ejemplo Whatsapp Web, Telegram Web, etc

### AJAX y los frameworks de forntend

Los frameworks **React**, **Angular** y **Vue**, que son los framework para frontend que más se estan usando actualmente, usan AJAX para brindar una experiencia de uso similar a la descripta anteriormente.

### AJAX y las aplicaciones hibridas

Otra aplicacion de AJAX, es cuando se trata de aplicaciones que van a ser usadas como programas en un sistema operativo (Linux, Widnows, Mac, BSD, Android, etc).

Esto se posible gracias a herramientas como `electron` o `ionic`, que nos permiten contar con toda la estructura de un navegador "escondida", para su instalación en estos sistemas operativos. Utilizando AJAX de las maneras que vimos anteriormente, se puede llegar a crear toda una aplicación con librerías web, sin que el usuario final lo sepa. Ejemplos de programas que hagan esto, `Atom`, `VSCode`, etc

## Concluciones

Como vimos anteriormente, AJAX se puede aplicar desde pequeñas secciones, como es el caso de un input en un formulario, como en toda la página para brindar un uso más fluido. Esta tecnología fue evolucionando con el tiempo, desde el uso de XML hasta JSON, y desde aplicaciones usando jQuery o Javascript Vanilla, hasta el uso en frameworks y librerías de frontend, permitiendonos construir tanto aplicaciones web, como aplicaciones nativas que se instalen en Linux, Windows, Mac o hasta Android o iOS. Desde luego, el uso de AJAX no se encuentra atado a ningún tipo de framework/librería, ni de un lenguaje como es el caso de Javascript, en este análisis se utilizó este lenguaje porque es de común conocimiento para el desarrollo de aplicaciones web, pero tranquilamente se puede aplicar AJAX usando Java en Android, objective-C o swift en iOS, como cualquier lenguaje que pueda surgir para frontend en la web.

Hoy en día, y dada la que el desarrollo de servicios en la web se vio profundamente influenciado por arquitecturas tipo API REST, el uso de AJAX en nuestras aplicaciones es simple, y nos brinda una gran flexibilidad a la hora de ofrecer aplicaciones usables por usuarios finales.