# eads_m4_ejercicio2_cpp_gtest
Para la realización de esta práctica se ha utlizado el código de la pŕactica del módulo 2. Se ha modificado los makefiles generados por eclipse para compilar en linux. Actualmente solo compila los test y no genera la aplicación compilando con el main.cpp

El proyecto contiene un script compile_test que compila y ejecuta los test con la opción adecuada para almacenar el resultado de la prueba en disco:

```
cd Testing
make
cd ..
./Testing/AnalizarNoticiasLinux_test --gtest_output=xml:gtestresults.xml

```

Para realizar el test, ejecutar el siguiente comando desde el directorio raíz del proyecto:

```
  docker run --rm -v "$PWD":/home/myapp -w /home/myapp jramed/gcc-cmake-gtest170 ./compile_test.sh
```
  
Con este comando se añade el directorio actual, que es la raíz del proyecto, como un volumen al container, y pone ese directorio como el directorio de trabajo. Después ejecuta el script de compilación y se ejecuta el binario y los test que contine. A parte de monstrarse el resultado de la pruebas en consolo tambien se almacena el resultado de las pruebas en el fichero gtestresults.xml dentro del mismo volumen.

