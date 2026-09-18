# Contribuir a Talleres de Estructuras de Datos

Este repositorio se utiliza para organizar los talleres de la asignatura **Estructuras de Datos** durante el periodo **2026-30**.

El objetivo es que el trabajo del equipo quede organizado por corte y por taller, manteniendo separados el código, la documentación y los entregables finales.

---

## 1. Integrantes

Los nombres que se deben utilizar en ramas y ejemplos son:

```text
isabella
saul
alejandro
```

Siempre se debe utilizar uno de estos nombres para identificar quién está trabajando en una tarea.

---

## 2. Organización general

La estructura principal del repositorio es:

```text
Talleres Estructuras/
├── talleres1corte/
├── talleres2corte/
└── talleres3corte/
```

Cada corte puede contener varios talleres.

Ejemplo:

```text
talleres2corte/
├── taller_3_arboles/
├── taller_4_huffman/
└── taller_5_grafos/
```

Cada taller debe mantenerse en su propia carpeta.

---

## 3. Estructura de cada taller

Siempre que sea posible, cada taller debe organizarse así:

```text
taller_numero_tema/
├── codigo/
├── documentacion/
└── entregable/
```

### `codigo/`

Contiene los archivos necesarios para desarrollar y ejecutar el taller.

Por ejemplo:

```text
.cpp
.cxx
.h
.hxx
.txt
```

No se deben guardar aquí archivos compilados como:

```text
.o
a.out
.exe
```

### `documentacion/`

Contiene material relacionado con el taller, por ejemplo:

```text
.pdf
.docx
.xlsx
imagenes
enunciados
analisis
```

### `entregable/`

Contiene únicamente el archivo final que realmente se entrega.

Por ejemplo:

```text
Taller_3.zip
```

Una vez entregado, ese ZIP debe conservarse como evidencia y no modificarse posteriormente.

---

## 4. Nombres de carpetas

Los talleres deben nombrarse con este formato:

```text
taller_numero_tema
```

Ejemplos:

```text
taller_3_arboles
taller_4_huffman
taller_5_grafos
```

Reglas:

- escribir en minúsculas;
- no usar tildes;
- no usar espacios;
- separar palabras con `_`;
- conservar el número real del taller.

---

## 5. Dónde trabajar

El trabajo principal debe realizarse en **Ubuntu**.

Ruta principal:

```bash
~/Universidad/Estructura de Datos/Talleres Estructuras
```

Para entrar:

```bash
cd ~/Universidad/"Estructura de Datos"/"Talleres Estructuras"
```

Para abrir todo el repositorio en Visual Studio Code:

```bash
code .
```

Windows se utiliza como copia organizada para consultar archivos y conservar acceso desde la otra partición.

Ruta en Windows:

```text
C:\Users\Usuario\Desktop\Estructura de Datos\Talleres Estructuras
```

Desde Ubuntu, esa misma carpeta se ve como:

```bash
~/Windows-Desktop/"Estructura de Datos"/"Talleres Estructuras"
```

---

## 6. Crear un taller nuevo

Antes de crear un taller, entrar a la raíz del repositorio:

```bash
cd ~/Universidad/"Estructura de Datos"/"Talleres Estructuras"
```

Ejemplo para crear el taller 3 del segundo corte:

```bash
mkdir -p talleres2corte/taller_3_nombre_del_tema/{codigo,documentacion,entregable}
```

Ejemplo:

```bash
mkdir -p talleres2corte/taller_3_arboles/{codigo,documentacion,entregable}
```

Después se puede abrir directamente ese taller:

```bash
code talleres2corte/taller_3_arboles
```

---

## 7. Rama principal

La rama principal es:

```text
main
```

`main` representa la versión estable del repositorio.

No se debe trabajar directamente sobre `main`.

Los cambios deben realizarse en ramas separadas y después integrarse mediante Pull Request.

---

## 8. Flujo antes de comenzar una tarea

Siempre comenzar desde `main` actualizado.

Primero entrar al repositorio:

```bash
cd ~/Universidad/"Estructura de Datos"/"Talleres Estructuras"
```

Luego:

```bash
git switch main
git pull origin main
```

Después crear una rama para la tarea.

---

## 9. Nombres de ramas

Toda rama debe indicar:

1. el tipo de trabajo;
2. la persona responsable;
3. la tarea.

Formato:

```text
tipo/nombre-tarea
```

### Nueva funcionalidad

```text
feature/nombre-tarea
```

Ejemplos:

```text
feature/isabella-taller3
feature/saul-punto2
feature/alejandro-arboles
```

### Correcciones

```text
fix/nombre-tarea
```

Ejemplos:

```text
fix/isabella-punto1
fix/saul-compilacion
fix/alejandro-lectura-archivo
```

### Documentación

```text
docs/nombre-tarea
```

Ejemplos:

```text
docs/isabella-informe-taller3
docs/saul-analisis
docs/alejandro-enunciado
```

### Organización

```text
chore/nombre-tarea
```

Ejemplos:

```text
chore/isabella-crear-taller3
chore/saul-organizar-archivos
```

---

## 10. Crear una rama

Ejemplo:

```bash
git switch -c feature/isabella-taller3
```

Para documentación:

```bash
git switch -c docs/isabella-informe-taller3
```

Para correcciones:

```bash
git switch -c fix/isabella-punto2
```

No se deben usar espacios ni tildes en los nombres de las ramas.

---

## 11. Commits

Cada commit debe representar un cambio claro.

Formato:

```text
tipo(modulo): descripcion
```

Tipos recomendados:

```text
feat
fix
docs
test
refactor
chore
```

Ejemplos:

```text
feat(taller3): implementar punto 1
```

```text
fix(taller3): corregir lectura de archivo
```

```text
docs(taller3): completar informe
```

```text
test(taller3): agregar casos de prueba
```

```text
chore(repo): organizar estructura del taller
```

Evitar mensajes como:

```text
cambios
arreglos
update
ahora si
final
```

Antes de crear un commit:

```bash
git status
```

---

## 12. Guardar cambios

Después de revisar `git status`:

```bash
git add .
```

Luego:

```bash
git commit -m "tipo(modulo): descripcion"
```

Ejemplo:

```bash
git commit -m "feat(taller3): implementar punto 1"
```

---

## 13. Subir una rama

La primera vez:

```bash
git push -u origin nombre-de-la-rama
```

Ejemplo:

```bash
git push -u origin feature/isabella-taller3
```

Después de eso, para nuevos commits en la misma rama:

```bash
git push
```

---

## 14. Pull Requests

Los cambios se integran a:

```text
main
```

mediante Pull Request.

Flujo:

```text
rama de trabajo
        ↓
Pull Request
        ↓
main
```

Antes del Pull Request:

- revisar los archivos modificados;
- comprobar que el código compile;
- comprobar que no se incluyan archivos compilados;
- ejecutar las pruebas necesarias;
- revisar la documentación;
- comprobar que el cambio corresponda a la tarea.

El Pull Request debe explicar brevemente:

- qué se hizo;
- qué archivos principales cambiaron;
- qué parte del taller corresponde;
- qué queda pendiente, si existe algo.

---

## 15. Después de hacer merge

Después de integrar un Pull Request:

```bash
git switch main
git pull origin main
```

Antes de empezar otra tarea, siempre repetir:

```bash
git switch main
git pull origin main
```

y luego crear una nueva rama.

---

## 16. Compilar

Entrar primero a la carpeta de código del taller.

Ejemplo:

```bash
cd ~/Universidad/"Estructura de Datos"/"Talleres Estructuras"/talleres2corte/taller_3_arboles/codigo
```

Para archivos `.cpp`:

```bash
g++ -std=c++17 *.cpp
```

Para archivos `.cxx`:

```bash
g++ -std=c++17 *.cxx
```

Si existen ambos tipos:

```bash
g++ -std=c++17 *.cpp *.cxx
```

Ejecutar:

```bash
./a.out
```

Si el taller utiliza otro comando de compilación indicado por el profesor, se debe utilizar ese comando.

---

## 17. Archivos compilados

No se deben subir archivos generados por la compilación.

Por ejemplo:

```text
*.o
a.out
*.exe
programa
```

Estos archivos pueden volver a generarse compilando el código.

---

## 18. `.gitignore`

El archivo `.gitignore` debe permanecer en la raíz del repositorio.

Actualmente se utiliza para ignorar archivos como:

```text
*.o
*.out
*.exe
a.out
~$*
*.tmp
*.bak
*.swp
.DS_Store
Thumbs.db
desktop.ini
.vscode/
```

Si aparece un nuevo tipo de archivo generado automáticamente, se debe revisar si conviene agregarlo al `.gitignore`.

---

## 19. Ubuntu y Windows

### Ubuntu

Ubuntu es la ubicación principal de trabajo.

Ruta:

```bash
~/Universidad/"Estructura de Datos"/"Talleres Estructuras"
```

Aquí se debe:

- programar;
- compilar;
- usar Git;
- crear ramas;
- hacer commits;
- generar entregables.

### Windows

Windows se utiliza como copia organizada.

Ruta:

```text
C:\Users\Usuario\Desktop\Estructura de Datos\Talleres Estructuras
```

Desde Ubuntu:

```bash
~/Windows-Desktop/"Estructura de Datos"/"Talleres Estructuras"
```

No se recomienda modificar simultáneamente una versión en Ubuntu y otra en Windows.

---

## 20. Sincronizar Ubuntu con Windows

Para copiar el estado actual de Ubuntu hacia Windows:

```bash
rsync -av --delete \
  --exclude='.git/' \
  --exclude='*.o' \
  --exclude='a.out' \
  --exclude='*.exe' \
  ~/Universidad/"Estructura de Datos"/"Talleres Estructuras"/ \
  ~/Windows-Desktop/"Estructura de Datos"/"Talleres Estructuras"/
```

La dirección correcta es:

```text
Ubuntu
↓
Windows
```

Windows no debe utilizarse como repositorio Git principal.

Para revisar el contenido de Windows desde Ubuntu:

```bash
ls ~/Windows-Desktop/"Estructura de Datos"/"Talleres Estructuras"
```

Para abrirlo gráficamente:

```bash
nautilus ~/Windows-Desktop/"Estructura de Datos"/"Talleres Estructuras"
```

---

## 21. Entregables

Cada taller debe conservar el archivo final realmente entregado dentro de:

```text
entregable/
```

Ejemplo:

```text
talleres2corte/
└── taller_3_arboles/
    └── entregable/
        └── Taller_3.zip
```

El contenido exacto del ZIP depende de las instrucciones del profesor para ese taller.

No se debe asumir que todos los talleres tienen el mismo formato de entrega.

Antes de crear un ZIP se debe revisar:

- qué extensiones acepta;
- si permite carpetas internas;
- si la documentación va dentro o fuera;
- qué archivos de código requiere;
- cómo debe llamarse el archivo.

Una vez entregado, el ZIP final no debe modificarse.

---

## 22. Trabajo en grupo

Antes de modificar una parte que también está trabajando otro integrante, se debe coordinar quién hará cada archivo o sección.

Evitar que dos personas modifiquen al mismo tiempo exactamente las mismas líneas cuando no sea necesario.

Cada integrante debe trabajar en su propia rama.

Ejemplo:

```text
feature/isabella-punto1
feature/saul-punto2
feature/alejandro-punto3
```

Después los cambios se integran mediante Pull Request.

---

## 23. Antes de considerar una tarea terminada

Comprobar:

- [ ] Estoy trabajando en una rama diferente de `main`.
- [ ] La rama contiene mi nombre.
- [ ] Estoy trabajando dentro del taller correcto.
- [ ] Los archivos están ubicados en la carpeta correspondiente.
- [ ] El código compila.
- [ ] Probé la parte que modifiqué.
- [ ] No incluí archivos `.o`, `a.out` o ejecutables.
- [ ] Revisé `git status`.
- [ ] El commit tiene un mensaje claro.
- [ ] Hice `git push`.
- [ ] El Pull Request tiene como destino `main`.
- [ ] Después del merge actualicé mi `main`.

---

## 24. Flujo rápido completo

Cuando llega un taller nuevo:

```bash
cd ~/Universidad/"Estructura de Datos"/"Talleres Estructuras"

git switch main
git pull origin main
```

Crear el taller:

```bash
mkdir -p talleres2corte/taller_3_nombre/{codigo,documentacion,entregable}
```

Crear rama:

```bash
git switch -c feature/isabella-taller3
```

Abrir en Visual Studio Code:

```bash
code talleres2corte/taller_3_nombre
```

Trabajar y revisar:

```bash
git status
```

Guardar:

```bash
git add .
git commit -m "feat(taller3): implementar tarea"
```

Subir:

```bash
git push -u origin feature/isabella-taller3
```

Crear Pull Request hacia:

```text
main
```

Después del merge:

```bash
git switch main
git pull origin main
```

Actualizar Windows:

```bash
rsync -av --delete \
  --exclude='.git/' \
  --exclude='*.o' \
  --exclude='a.out' \
  --exclude='*.exe' \
  ~/Universidad/"Estructura de Datos"/"Talleres Estructuras"/ \
  ~/Windows-Desktop/"Estructura de Datos"/"Talleres Estructuras"/
```

---

## 25. Prioridad ante dudas

Cuando exista una contradicción, utilizar este orden:

1. Instrucción directa y reciente del profesor.
2. Enunciado oficial del taller.
3. Material trabajado en clase.
4. Decisiones confirmadas por el equipo.
5. Esta guía.
6. Sugerencias externas.

Si todavía existe una duda, no asumir una regla sin confirmarla.