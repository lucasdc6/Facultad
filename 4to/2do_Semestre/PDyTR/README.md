## Usando el ambiente de PDyTR

El ambiente de trabajo para la materia se encuentra
[dockerizado](https://hub.docker.com/r/gmaron/pdytr/)

Para utilizar el ambiente completo, es necesario tener instalado las siguientes
cosas:

- Docker
- Direnv


Para hacer más cómodo el ambiente, se cuenta con un archivo `envrc` en el
directorio del ambiente. El mismo agrega al PATH, el directorio bin, para la
utilización del script `pdytr`

Dicho script cuenta con 3 funcionalidades básicas:

- `pdytr`: Entra en el ambiente en modo terminal.
- `pdytr start`: Inicia el ambiente en modo `simple`
- `pdytr start view`: Inicia el ambiente en modo visual. Se cuenta con las url
 `http://localhost:6901/?password=vncpassword` para el uso visual. (También
disponible mediante VNC)
- `pdytr stop`: Cierra el ambiente.

Dentro del ambiente, se cuenta con `gcc` y `javac` para la compilación de las
prácticas.

Todo el ambiente de trabajo se encuentra en el directorio `/pdytr`
