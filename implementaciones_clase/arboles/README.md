# Implementaciones de Árboles

Esta carpeta reúne las implementaciones y ejemplos de árboles trabajados durante la asignatura de Estructuras de Datos.

Se conservan como material de estudio y como plantillas generales que podrán copiarse o adaptarse posteriormente para talleres y proyectos específicos.

## Criterio para conservar las implementaciones

Cuando el profesor presenta más de una forma de implementar una estructura, se conservan todas las variantes trabajadas.

Si el profesor recomienda explícitamente una de ellas, puede señalarse como principal o recomendada, pero las demás variantes enseñadas no se eliminan.

## Fuentes de referencia

Para construir y revisar estas plantillas se sigue principalmente este orden:

1. Código desarrollado siguiendo los videos del profesor y trabajo directo realizado durante la clase.
2. Indicaciones y aclaraciones directas del profesor.
3. Diapositivas y demás material de la asignatura.
4. Talleres o enunciados específicos cuando corresponda.
5. Recursos y enlaces proporcionados por el profesor.
6. Código y decisiones ya confirmadas dentro del repositorio.
7. Recomendaciones externas, diferenciándolas del material del curso.

Si dos fuentes entran en conflicto, la diferencia debe revisarse explícitamente antes de modificar una implementación.

## Organización actual

```text
arboles/
├── README.md
├── arbol_general/
│   ├── README.md
│   ├── recursion_en_arbol/
│   └── recursion_en_nodo/
├── arbol_binario/
│   └── README.md
├── arbol_binario_ordenado/
│   ├── README.md
│   ├── recursion_en_arbol/
│   └── recursion_en_nodo/
├── arbol_avl/
│   └── README.md
├── arbol_rojo_negro/
│   └── README.md
└── monticulos/
    └── README.md
```

## Árbol General

Se conservan dos variantes:

- recursión realizada en `ArbolGeneral`;
- recursión realizada en `NodoGeneral`.

## Árbol Binario

Contiene la implementación general de un árbol binario.

No debe confundirse con un Árbol Binario Ordenado.

## Árbol Binario Ordenado

Se conservan dos variantes:

- recursión realizada en el árbol;
- recursión realizada en el nodo.

## Árbol AVL

Contiene la implementación de Árbol AVL trabajada en el material.

Incluye el cálculo del factor de balance y las rotaciones necesarias.

## Árbol Rojo-Negro

Se conserva mediante los ejemplos con contenedores de la STL trabajados en el material:

- `set`;
- `multiset`;
- `map`;
- `multimap`;
- objetos personalizados mediante `operator<`.

No se añadió una implementación manual de Árbol Rojo-Negro porque no corresponde a la forma trabajada en el material utilizado como base.

## Montículos

Se conservan dos formas:

- implementación manual;
- algoritmos de montículo de la STL.

La versión manual permite estudiar los procesos de subir y bajar elementos.

La versión STL muestra operaciones como `push_heap`, `pop_heap`, `make_heap` e `is_heap`.

## Validación

Antes de considerar una implementación como plantilla válida se debe:

1. compilarla con las opciones de advertencia correspondientes;
2. ejecutar casos de prueba;
3. comparar el resultado esperado con el obtenido;
4. comprobar las variantes entre sí cuando implementen el mismo comportamiento.

Que un archivo compile no es suficiente para afirmar que la implementación funciona correctamente.

## Uso en talleres

Cuando un taller necesite alguna de estas estructuras, se debe copiar o adaptar la implementación correspondiente dentro de la carpeta del taller.

Las versiones almacenadas en `implementaciones_clase` deben mantenerse como referencia general del curso.