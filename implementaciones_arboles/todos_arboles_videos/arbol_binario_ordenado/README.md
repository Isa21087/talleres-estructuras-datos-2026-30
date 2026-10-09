# Árbol Binario Ordenado

Esta carpeta conserva las diferentes formas de implementación trabajadas a partir de los videos y material del profesor para el Árbol Binario Ordenado.

Un Árbol Binario Ordenado mantiene la siguiente organización:

- los valores menores que un nodo se encuentran en su subárbol izquierdo;
- los valores mayores se encuentran en su subárbol derecho;
- en estas implementaciones no se permiten datos repetidos.

Se conservan dos formas de implementar las operaciones recursivas.

## Forma 1: recursión en el árbol

Carpeta:

`recursion_en_arbol/`

En esta versión, `ArbolBinarioOrd` contiene métodos auxiliares que reciben un nodo para realizar la recursión.

Por ejemplo:

- `altura(NodoBinario<T>* nodo)`
- `tamano(NodoBinario<T>* nodo)`
- `preOrden(NodoBinario<T>* nodo)`
- `inOrden(NodoBinario<T>* nodo)`
- `posOrden(NodoBinario<T>* nodo)`

El nodo principalmente administra:

- el dato;
- el hijo izquierdo;
- el hijo derecho;
- sus métodos de acceso.

## Forma 2: recursión en el nodo

Carpeta:

`recursion_en_nodo/`

En esta versión, las operaciones recursivas pertenecen a `NodoBinario`.

Cada nodo resuelve la operación para su propio subárbol y delega el mismo trabajo a sus hijos.

Por ejemplo:

- `altura()`
- `tamano()`
- `preOrden()`
- `inOrden()`
- `posOrden()`

El árbol verifica los casos generales y delega el trabajo a la raíz.

Esta es la forma que se toma como recomendada para nuestro trabajo cuando sea necesario escoger una implementación, pero se conservan ambas porque las dos hacen parte de las formas estudiadas.

## Operaciones que se mantienen iguales

En las dos versiones, las siguientes operaciones conservan la misma lógica:

- `insertar`
- `eliminar`
- `buscar`
- `nivelOrden`

Estas operaciones aprovechan que el árbol está ordenado.

En inserción y búsqueda:

- si el valor es menor, se continúa por el hijo izquierdo;
- si es mayor, se continúa por el hijo derecho;
- si es igual, el dato ya existe.

## Eliminación

La implementación contempla los tres casos vistos para eliminar un nodo:

1. nodo hoja;
2. nodo con un solo hijo;
3. nodo con dos hijos.

Cuando el nodo tiene dos hijos, se utiliza el valor máximo del subárbol izquierdo como reemplazo.

## Recorridos

Se conservan los cuatro recorridos trabajados:

- preorden;
- inorden;
- posorden;
- nivel por niveles.

En un Árbol Binario Ordenado, el recorrido inorden produce los datos de menor a mayor.

## Validación

Las dos implementaciones fueron compiladas con C++17 usando:

`-Wall -Wextra -pedantic`

También fueron probadas con los mismos casos para comprobar:

- inserción;
- rechazo de duplicados;
- búsqueda;
- altura;
- tamaño;
- recorridos;
- eliminación de una hoja;
- eliminación de un nodo con un hijo;
- eliminación de un nodo con dos hijos.

Las dos versiones produjeron los mismos resultados.

## Uso posterior

Estas implementaciones se conservan como plantillas generales de la materia.

Si un taller o proyecto necesita una de ellas, se realizará una copia y los cambios específicos se harán sobre esa copia, sin modificar estas plantillas base.
