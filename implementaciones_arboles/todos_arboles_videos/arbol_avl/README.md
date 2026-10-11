# Árbol AVL

Esta carpeta contiene la implementación general de Árbol AVL trabajada a partir de los videos y material del profesor.

La implementación parte del Árbol Binario Ordenado con recursión a nivel del nodo.

En esta versión, las operaciones propias del balanceo se realizan principalmente en `NodoAVL`.

## Relación con el Árbol Binario Ordenado

Se conservan operaciones ya trabajadas en el Árbol Binario Ordenado, como:

- consulta de dato e hijos;
- altura;
- tamaño;
- búsqueda;
- recorridos preorden, inorden, posorden y por niveles.

La diferencia principal es que en el AVL la inserción y la eliminación deben mantener el árbol balanceado.

## Propiedad AVL

Para cada nodo, las alturas de sus subárboles izquierdo y derecho pueden diferir como máximo en 1.

En esta implementación se utiliza:

`diferenciaAltura = altura izquierda - altura derecha`

Por lo tanto:

- `-1`, `0` o `1`: el nodo está balanceado;
- un valor mayor que `1`: hay desbalance hacia la izquierda;
- un valor menor que `-1`: hay desbalance hacia la derecha.

La altura de un subárbol vacío se considera `-1`.

## Balanceo a nivel del nodo

La inserción y la eliminación son recursivas.

Después de realizar una modificación, cada llamado retorna hacia arriba y se ejecuta el balanceo sobre los nodos de la ruta modificada.

Los métodos `insertar` y `eliminar` del nodo devuelven la nueva raíz de su subárbol, ya que una rotación puede cambiar qué nodo queda arriba.

## Rotaciones

Se conservan las cuatro rotaciones trabajadas:

- rotación a la derecha;
- rotación a la izquierda;
- rotación izquierda-derecha;
- rotación derecha-izquierda.

Las rotaciones dobles reutilizan las rotaciones simples.

## Eliminación

La eliminación conserva los tres casos del Árbol Binario Ordenado:

1. nodo hoja;
2. nodo con un solo hijo;
3. nodo con dos hijos.

Cuando hay dos hijos, se utiliza el máximo del subárbol izquierdo como reemplazo.

Después de eliminar, se vuelve a verificar el balance en la ruta de modificación.

## Validación

La implementación fue compilada con C++17 utilizando:

`-Wall -Wextra -pedantic`

Se probaron:

- las cuatro rotaciones;
- inserción;
- rechazo de valores repetidos;
- búsqueda;
- altura;
- tamaño;
- recorridos;
- balanceo después de eliminar.

Los diagramas de las rotaciones se conservaron como parte de la explicación, ajustando únicamente su formato de comentario para evitar advertencias del compilador.

## Variantes

En el material base disponible para esta implementación se conserva una versión de AVL, basada en recursión a nivel del nodo.

Si posteriormente se identifica en los videos otra forma enseñada por el profesor, se conservará como una variante adicional en lugar de reemplazar esta implementación.

## Uso posterior

Esta implementación se conserva como plantilla general de la materia.

Cuando un taller o proyecto necesite utilizarla, se realizará una copia y las modificaciones específicas se harán sobre esa copia, manteniendo intacta esta carpeta.
