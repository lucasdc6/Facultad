## Simple FTP

Se probee una implementacion de un FTP server con los siguientes comandos:

- `add` o `write`: Agrega un archivo desde el path definido en `--src` en el filesystem del servidor, en el path `store/<dest>`, definido por `--dest`
- `get` o `read`: Lee un archivo desde el path del servidor, definido en `--src`, en el filesystem local definido por `--dest`
- `list` o `ls`: Lista los archivos en el directorio definido en `--src`
