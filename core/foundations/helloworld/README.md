# Hello, World! — V

Implementación de la especificación [01_Hello_World](https://yorche3.github.io/programming_languages/core/foundations/01_Hello_World/) en **V**, con un enfoque manual y minimalista.

---

## 📂 Archivos y estructura / Files & Structure

| Archivo | Propósito |
|---------|-----------|
| [`hello_world.v`](hello_world.v) | Código fuente: imprime `"Hello, World! from VLang"` en la salida estándar. |

**Estructura de directorios esperada:**

```text
helloworld/
├── hello_world.v  # Código fuente
└── README.md      # Este archivo
```

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** El proyecto se creó manualmente, sin gestores de paquetes ni herramientas de scaffolding. Un único archivo `.v` es suficiente: V puede ejecutar el archivo directamente o compilarlo a un ejecutable nativo.

**EN:** The project was created manually, without package managers or scaffolding tools. A single `.v` file is enough: V can run the file directly or compile it into a native executable.

### Inicialización / Initialization

1. Crear la estructura de directorios:

   ```bash
   mkdir -p v/core/foundations/helloworld
   ```

2. Escribir el archivo `hello_world.v` con el código fuente.

3. Ejecutarlo con `v run` o compilarlo con `v`.

---

## 📄 Archivos de configuración clave / Key Configuration Files

No se requieren archivos de configuración para este ejercicio.

```v
println('Hello, World! from VLang')
```

| Elemento | Propósito |
|----------|-----------|
| `println(...)` | Escribe la cadena en la salida estándar y añade un salto de línea. |
| `'Hello, World! from VLang'` | Literal de cadena que se muestra al usuario. |

> **ES:** V admite código de nivel superior en un archivo ejecutable, por lo que no se necesita declarar una función `main` para este ejemplo.
> **EN:** V supports top-level code in an executable file, so no `main` function is required for this example.

---

## 🚀 Compilación y ejecución / Build & Run

### Requisitos / Requirements

- **V 0.5.2**.
- El ejecutable `v` disponible en el `PATH`.

Verificar la instalación:

```bash
v version
```

Salida verificada:

```text
V 0.5.2 76c0d94
```

En este entorno, V se instaló en `$HOME/.local/share/vlang` y esa ruta se añadió al `PATH` desde `.bashrc`.

In this environment, V is installed under `$HOME/.local/share/vlang`, and that path is added to `PATH` through `.bashrc`.

### Ejecutar directamente / Run directly

```bash
cd v/core/foundations/helloworld
v run hello_world.v
```

### Compilar y ejecutar / Compile and run

```bash
cd v/core/foundations/helloworld
v -o hello_world hello_world.v
./hello_world
```

### Salida esperada / Expected output

```text
Hello, World! from VLang
```

La salida fue verificada con V 0.5.2 en Linux/WSL2.

The output was verified with V 0.5.2 on Linux/WSL2.

---

## 📝 Notas de implementación / Implementation Notes

- **ES:** V no requiere una función `main` para este script de nivel superior.
- **EN:** V does not require a `main` function for this top-level script.
- **ES:** `println` añade un salto de línea automáticamente.
- **EN:** `println` automatically appends a newline.
- **ES:** El ejecutable generado por la compilación es un artefacto local y no forma parte del código fuente del ejercicio.
- **EN:** The compiled executable is a local build artifact and is not part of the exercise source code.

---

## 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://github.com/yorche3/programming_languages)*
