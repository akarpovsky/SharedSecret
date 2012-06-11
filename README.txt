COMPILACIÓN:

1. Posicionarse en la carpeta ./src
2. Ejecutar el comando "make"

EJECUCIÓN

El programa solo acepta el formato de BMP que utiliza chformat.jar.

Por lo tanto, las imagenes a utilizar deben ser todas pasadas por
este programa.
Para esto se cuenta con el programa de bash: formatImages.sh el cual
dado un directorio, cambia el formato de las imagenes BMP al utilizado.

Ejemplo:
./formatImages.sh images

Una vez compilado el programa. Se obtiene el ejecutable con el nombre "shasec".

Ejemplo de distribución:

./shasec -d --secret images/secrets/Gustavo.bmp -k 3 - n 4 --dir ./images/cover

Ejemplo de recuperación:

./shasec -r --secret images/recover/resultado.bmp -k 3 --dir ./images/cover

Cualquier duda sobre los comandos, el programa cuenta con --help.

También para la distribución y recupera posee la opción --verbose, el cual 
indica una barra de progreso.
