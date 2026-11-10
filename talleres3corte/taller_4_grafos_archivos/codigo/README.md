
# Taller 4 de Grafos - Misión Lázaro

## Organización del código

El programa está organizado en tres TAD:

- **Planeta:** guarda el nombre, las coordenadas y el factor temporal de cada planeta
- **Grafo:** almacena los planetas, los pesos de las conexiones y cuáles son peligrosas
- **SistemaExploracionLazaro:** carga los datos, calcula el combustible, realiza la exploración y genera los resultados

El archivo `main.cxx` se encarga de iniciar la ejecución utilizando el TAD principal.

## Compilación

Desde la carpeta `codigo/`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
    main.cxx SistemaExploracionLazaro.cxx Grafo.cxx Planeta.cxx \
    -o programa
```

## Ejecución

```bash
./programa
```

Cuando el programa solicite el archivo de entrada, escribir, por ejemplo:

```text
pruebas/prueba_01_basica.txt
```

El programa genera estos archivos:

- `detalle_recorrido.txt`: información de cada desplazamiento
- `resumen.txt`: recorrido y estadísticas finales

## Pruebas

Los archivos de entrada están en `pruebas/`.

Para probar las conexiones peligrosas:

```bash
./programa
```

Ingresar:

```text
pruebas/prueba_03_peligros.txt
```

Para compilar la prueba independiente del grafo:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
    pruebas/prueba_grafo.cxx Grafo.cxx Planeta.cxx \
    -o pruebas/prueba_grafo

./pruebas/prueba_grafo
```

Para compilar la prueba independiente de lectura:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
    pruebas/prueba_lectura.cxx \
    -o pruebas/prueba_lectura

./pruebas/prueba_lectura
```
