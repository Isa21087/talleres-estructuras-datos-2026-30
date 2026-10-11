# Plantillas de Árboles

Esta carpeta contiene una selección práctica de las implementaciones de árboles trabajadas en clase.

Su propósito es tener versiones directas y fáciles de consultar o copiar para talleres y ejercicios, sin eliminar ni modificar la biblioteca completa ubicada en:

`implementaciones_clase/arboles/`

## Criterio de selección

Cuando existen varias implementaciones de la misma estructura, en esta carpeta se conserva una sola versión de uso práctico.

Para Árbol General y Árbol Binario Ordenado se escogió la variante donde la recursión se realiza principalmente en el nodo, porque permite que cada nodo resuelva las operaciones correspondientes a su propio subárbol.

La biblioteca completa sigue conservando también las variantes con recursión en el árbol.

## Contenido

### Árbol General

Archivos:

- `ArbolGeneral.h`
- `ArbolGeneral.hxx`
- `NodoGeneral.h`
- `NodoGeneral.hxx`

Versión seleccionada: recursión en `NodoGeneral`.

### Árbol Binario

Archivos:

- `ArbolBinario.h`
- `ArbolBinario.hxx`
- `NodoBinario.h`
- `NodoBinario.hxx`

Se conserva la implementación general trabajada en clase.

### Árbol Binario Ordenado

Archivos:

- `ArbolBinarioOrd.h`
- `ArbolBinarioOrd.hxx`
- `NodoBinario.h`
- `NodoBinario.hxx`

Versión seleccionada: recursión en `NodoBinario` para las operaciones recursivas.

### Árbol AVL

Archivos:

- `ArbolAVL.h`
- `ArbolAVL.hxx`
- `NodoAVL.h`
- `NodoAVL.hxx`

La inserción, eliminación, balanceo y rotaciones se apoyan principalmente en `NodoAVL`.

### Árbol Rojo-Negro

Se conservan los ejemplos trabajados mediante la STL:

- `set`
- `multiset`
- `map`
- `multimap`
- objetos personalizados con `operator<`

No se incluye una implementación manual de Árbol Rojo-Negro porque no corresponde a la forma trabajada en el material utilizado como base.

### Montículos

Se conservan las dos formas trabajadas:

- implementación manual;
- algoritmos de montículo de la STL.

La versión manual permite estudiar los procesos de subir y bajar elementos, mientras que la versión STL muestra el uso de `push_heap`, `pop_heap`, `make_heap` e `is_heap`.

## Importante

Esta carpeta es una selección práctica.

Las implementaciones completas, todas las variantes y su documentación permanecen en:

`implementaciones_clase/arboles/`

Para revisar cómo fue enseñada una estructura o comparar distintas formas de implementarla, se debe consultar primero esa biblioteca completa.