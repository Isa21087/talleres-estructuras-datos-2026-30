# Árbol General

Esta carpeta conserva las dos formas de implementación de Árbol General trabajadas a partir de los videos y material del profesor.

Las dos variantes implementan las mismas operaciones y producen el mismo comportamiento. La diferencia principal está en el lugar donde se realiza la recursión.

Se conservan ambas como material de estudio y como plantillas generales para trabajos posteriores.

## Organización

```text
arbol_general/
├── README.md
├── recursion_en_arbol/
│   ├── ArbolGeneral.h
│   ├── ArbolGeneral.hxx
│   ├── NodoGeneral.h
│   └── NodoGeneral.hxx
└── recursion_en_nodo/
    ├── ArbolGeneral.h
    ├── ArbolGeneral.hxx
    ├── NodoGeneral.h
    └── NodoGeneral.hxx
```

## Variante 1: recursión en el árbol

Carpeta:

`recursion_en_arbol/`

En esta implementación, las operaciones recursivas se encuentran en `ArbolGeneral`.

El árbol tiene métodos auxiliares protegidos que reciben un apuntador a `NodoGeneral<T>` y realizan la recursión recorriendo los hijos.

Entre estos métodos se encuentran:

- inserción;
- eliminación;
- búsqueda;
- altura;
- tamaño;
- preorden;
- posorden.

`NodoGeneral` se encarga principalmente de almacenar el dato, la lista de hijos y las operaciones básicas sobre esa lista.

## Variante 2: recursión en el nodo

Carpeta:

`recursion_en_nodo/`

En esta implementación, `ArbolGeneral` maneja los casos generales del árbol y delega las operaciones recursivas a la raíz.

Las operaciones recursivas se encuentran en `NodoGeneral`.

Cada nodo trabaja sobre el subárbol que tiene como raíz y llama la misma operación sobre sus hijos.

Entre estas operaciones se encuentran:

- inserción;
- eliminación;
- búsqueda;
- altura;
- tamaño;
- preorden;
- posorden.

El recorrido por niveles permanece en `ArbolGeneral` porque se realiza de forma iterativa utilizando una cola.

## Validación

Las dos variantes fueron compiladas con C++17 utilizando:

`-Wall -Wextra -pedantic`

Ambas compilaron sin advertencias.

Se verificaron con el mismo programa de prueba:

- inserción de la raíz;
- inserción en varios niveles;
- búsqueda;
- altura;
- tamaño;
- preorden;
- posorden;
- recorrido por niveles;
- eliminación de un nodo con descendientes.

Las dos variantes produjeron exactamente la misma salida.

## Conservación de variantes

Las dos implementaciones se mantienen porque corresponden a formas distintas de distribuir la responsabilidad de la recursión entre `ArbolGeneral` y `NodoGeneral`.

No se elimina una variante en favor de la otra.

## Uso posterior

Estas implementaciones se conservan como plantillas generales de la materia.

Para un taller o proyecto específico se deberá trabajar sobre una copia o adaptación, manteniendo intactas estas versiones base.