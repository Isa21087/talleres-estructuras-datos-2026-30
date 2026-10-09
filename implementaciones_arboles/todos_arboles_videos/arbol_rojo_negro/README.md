# Árbol Rojo-Negro

Esta carpeta conserva los ejemplos trabajados a partir de los videos y material del profesor para Árbol Rojo-Negro.

En este tema no se implementa manualmente una clase `ArbolRN` ni un `NodoRN`.

El trabajo se realiza utilizando los contenedores de la STL mostrados en clase:

- `std::set`
- `std::multiset`
- `std::map`
- `std::multimap`

Según el enfoque trabajado en el material de la materia, estos contenedores permiten utilizar las operaciones de una estructura ordenada y balanceada sin implementar manualmente los cambios de color y las rotaciones del Árbol Rojo-Negro.

## Propiedades estudiadas

En el material se revisan las propiedades del Árbol Rojo-Negro:

1. cada nodo tiene color rojo o negro;
2. la raíz y las hojas nulas son negras;
3. un nodo rojo no puede tener padre rojo;
4. un nodo rojo tiene hijos negros;
5. todas las rutas desde un nodo hasta sus hojas nulas contienen la misma cantidad de nodos negros.

También se estudia que, al modificar el árbol, pueden ser necesarios cambios de color y rotaciones.

En los ejemplos de esta carpeta estas operaciones internas son realizadas por los contenedores de la STL.

## `std::set`

Archivo:

`ejemploSet.cpp`

El `set` almacena elementos únicos y mantiene los datos ordenados.

En el ejemplo se trabajan:

- `insert`
- `size`
- `begin` y `end`
- `rbegin` y `rend`
- `find`
- `count`
- `erase`
- `clear`
- `empty`

El recorrido desde `begin()` hasta `end()` muestra los datos de menor a mayor.

Al intentar insertar un elemento repetido, el `set` no crea una segunda copia.

## `std::multiset`

Archivo:

`ejemploMultisetMultimap.cpp`

El `multiset` conserva el comportamiento ordenado de `set`, pero permite datos repetidos.

En el ejemplo se trabajan:

- inserción de valores repetidos;
- `count`;
- eliminación de todas las copias con `erase(valor)`;
- eliminación de una sola copia mediante un iterador.

## `std::map`

Archivo:

`ejemploMap.cpp`

El `map` almacena parejas:

`llave -> valor`

La estructura se organiza utilizando la llave.

Las llaves son únicas.

En el ejemplo se trabajan:

- inserción y consulta mediante `[]`;
- búsqueda con `find`;
- iteradores;
- acceso mediante `first` y `second`;
- sobrescritura del valor de una llave existente;
- eliminación mediante `erase`.

También se muestra un comparador propio para utilizar `const char*` como llave.

## `std::multimap`

Archivo:

`ejemploMultisetMultimap.cpp`

El `multimap` también almacena parejas:

`llave -> valor`

A diferencia de `map`, permite varias entradas con la misma llave.

En el ejemplo se trabajan:

- `insert`;
- `count`;
- `equal_range`;
- recorrido de todos los valores asociados a una misma llave.

## Clases propias y `operator<`

Archivos:

- `Carro.h`
- `ejemploCarros.cpp`

Para utilizar una clase propia como dato de un `set`, la estructura necesita una forma de comparar los objetos.

En `Carro` se define:

`operator<`

La comparación se realiza utilizando la placa.

Por eso los carros quedan ordenados por placa y dos carros con la misma placa se consideran equivalentes para el `set`.

El ejemplo también muestra:

- `std::set<Carro>`;
- búsqueda y eliminación utilizando la placa;
- `std::map<std::string, Carro>`;
- acceso a llave y valor mediante `first` y `second`.

## Diferencias entre las cuatro opciones

### `set`

Un dato por elemento.

No permite repetidos.

### `multiset`

Un dato por elemento.

Sí permite repetidos.

### `map`

Parejas llave-valor.

La llave es única.

### `multimap`

Parejas llave-valor.

Una llave puede aparecer varias veces.

## Validación

Los ejemplos fueron compilados con C++11 utilizando:

`-Wall -Wextra -pedantic`

Se verificaron los cuatro programas:

- `ejemploSet.cpp`;
- `ejemploMap.cpp`;
- `ejemploMultisetMultimap.cpp`;
- `ejemploCarros.cpp`.

Todos compilaron sin advertencias y se ejecutaron correctamente.

## Variantes y material de clase

Se conservan todos los ejemplos disponibles del tema porque cada uno representa una forma diferente trabajada en los videos o material de clase.

No se reemplazan por una única implementación.

Si posteriormente se identifica otra variante enseñada por el profesor, se añadirá como otro ejemplo en lugar de eliminar los existentes.

## Uso posterior

Estas implementaciones se conservan como plantillas y ejemplos generales de la materia.

Cuando un taller o proyecto necesite alguno de estos contenedores, se realizará una copia o adaptación para ese trabajo específico, manteniendo intactos estos ejemplos base.
