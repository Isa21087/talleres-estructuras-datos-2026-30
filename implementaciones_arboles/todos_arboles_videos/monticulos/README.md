# Montículos

Esta carpeta conserva las dos formas trabajadas a partir de los videos y material del profesor para montículos:

- implementación manual;
- uso de los algoritmos de la STL.

Se conservan ambas porque cada una permite estudiar una parte diferente del tema.

## Concepto

Un montículo es un árbol binario completo.

No es un Árbol Binario Ordenado: no se utiliza la regla de menores a la izquierda y mayores a la derecha.

La propiedad se establece entre cada padre y sus hijos.

### Montículo máximo

Cada padre es mayor o igual que sus hijos.

Por esta propiedad, el elemento mayor queda en la raíz.

### Montículo mínimo

Cada padre es menor o igual que sus hijos.

Por esta propiedad, el elemento menor queda en la raíz.

## Representación en un arreglo

Los montículos trabajados se representan mediante un arreglo o contenedor secuencial, sin utilizar nodos ni apuntadores.

Con la raíz en la posición `0`, para una posición `i`:

- hijo izquierdo: `2*i + 1`
- hijo derecho: `2*i + 2`
- padre: `(i - 1) / 2`

La estructura corresponde a un árbol completo: el último nivel se llena de izquierda a derecha.

## Forma 1: implementación manual

Archivo:

`ejemploMonticuloManual.cpp`

Esta versión permite observar directamente los procesos de subir y bajar un dato.

### Inserción

1. El nuevo elemento se coloca al final.
2. Se compara con su padre.
3. Mientras sea mayor que su padre, se intercambian.
4. El proceso continúa hacia arriba hasta cumplir la propiedad del montículo máximo.

Este proceso corresponde a SUBIR.

### Eliminación

En el ejemplo se elimina la raíz.

1. Se guarda el valor de la raíz.
2. El último elemento pasa a la raíz.
3. Se elimina la última posición.
4. El elemento que llegó a la raíz se compara con sus hijos.
5. Si debe bajar, se intercambia con el mayor de sus hijos.
6. Se continúa hasta recuperar la propiedad del montículo.

Este proceso corresponde a BAJAR.

La versión manual imprime los intercambios para poder seguir el procedimiento paso a paso.

## Forma 2: STL

Archivo:

`ejemploMonticuloSTL.cpp`

En la STL, los montículos se trabajan mediante algoritmos de `<algorithm>` aplicados sobre contenedores como `vector` o `deque`.

En el ejemplo se utilizan:

- `push_heap`
- `pop_heap`
- `make_heap`
- `is_heap`

## `push_heap`

Para insertar:

1. el dato se agrega al final del contenedor;
2. `push_heap` reorganiza el rango para que el nuevo dato suba hasta la posición correspondiente.

## `pop_heap`

`pop_heap` mueve la raíz al final del rango y reorganiza el resto del montículo.

El elemento todavía permanece dentro del contenedor.

Para eliminarlo realmente se consulta con `back()` y después se utiliza `pop_back()`.

## `make_heap`

Permite tomar un contenedor que ya contiene datos y reorganizarlo para que cumpla la propiedad de montículo.

También se utiliza en el ejemplo después de eliminar directamente una posición intermedia del vector.

## `is_heap`

Permite comprobar si un rango cumple la propiedad de montículo.

## Montículo máximo y mínimo

Por defecto, los algoritmos utilizados forman un montículo máximo.

Para trabajar un montículo mínimo, en el ejemplo se utiliza:

`std::greater<int>()`

De esta forma el menor elemento queda en la raíz.

## Relación entre las dos formas

La versión manual muestra directamente qué ocurre al subir y bajar los elementos.

La versión STL realiza esos procesos mediante los algoritmos de la biblioteca.

En las pruebas realizadas, al insertar:

`12, 6, 14, 2, 13`

las dos formas producen el mismo montículo máximo:

`[14 13 12 2 6]`

Después de eliminar la raíz una vez, ambas producen:

`[13 6 12 2]`

## Validación

Los dos ejemplos fueron compilados con C++11 utilizando:

`-Wall -Wextra -pedantic`

Ambos compilaron sin advertencias.

Se verificaron:

- inserción en montículo máximo;
- proceso manual de subir;
- eliminación de la raíz;
- proceso manual de bajar;
- montículo máximo con STL;
- montículo mínimo con STL;
- `push_heap`;
- `pop_heap`;
- `make_heap`;
- `is_heap`.

## Variantes

Se conservan tanto la implementación manual como la versión con STL porque las dos corresponden a formas diferentes trabajadas en el material.

Si posteriormente se identifica otra variante enseñada por el profesor, se añadirá como otra opción sin reemplazar estas implementaciones.

## Uso posterior

Estas implementaciones se conservan como plantillas y ejemplos generales de la materia.

Cuando un taller o proyecto necesite trabajar con montículos, se realizará una copia o adaptación para ese trabajo específico, manteniendo intactos estos ejemplos base.
