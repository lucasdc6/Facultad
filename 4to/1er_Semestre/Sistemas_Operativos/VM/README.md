## SSH a la vm

Para poder utilizar SSH contra la máquina virtual, es necesario seguir los
siguientes pasos:

1- Agregarle una red de tipo "Host-Only" a la VM.

2- Configurar dicha interfaz con una configuración por defecto (puede utilizarse
como ejemplo, el archivo en `etc/network/interfaces`, de este directorio)

3- Instalar el paquete `openssh-server`

Si todo salió bien, se debería poder entrar por ssh a la máquina virtual a
utilizando la dirección configurada en `/etc/network/interfaces`

__nota: Se puede agregar la clave publica para un acceso más simple__

__Para eso, ejecutar `ssh-ssh-copy-id so@<ip>`__
