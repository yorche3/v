# Hello, User! — V

Implementación de la especificación [02_Hello_User](https://yorche3.github.io/programming_languages/core/foundations/02_Hello_User/) en **V**, con un enfoque manual y minimalista.

Solicita un nombre mediante la entrada estándar y muestra un saludo personalizado.

---

## 📂 Archivos y estructura / Files & Structure

| Archivo | Propósito |
|---------|-----------|
| [`hello_user.v`](hello_user.v) | Código fuente: solicita un nombre, lee una línea y muestra un saludo. |
| [`.gitignore`](.gitignore) | Ignora los ejecutables generados por V. |

**Estructura de directorios esperada:**

```text
hellouser/
├── hello_user.v  # Código fuente
├── .gitignore    # Artefactos ignorados
└── README.md     # Este archivo
```

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** El proyecto se creó manualmente, sin gestores de paquetes ni herramientas de scaffolding. El archivo `.v` usa `os.get_line()` para leer desde la entrada estándar y `println` para escribir el prompt y el saludo.

**EN:** The project was created manually, without package managers or scaffolding tools. The `.v` file uses `os.get_line()` to read from standard input and `println` to write the prompt and greeting.

### Inicialización / Initialization

1. Crear la estructura de directorios:

   ```bash
   mkdir -p v/core/foundations/hellouser
   ```

2. Escribir el archivo `hello_user.v` con el código fuente.

3. Ejecutarlo con `v run` o compilarlo con `v`.

---

## 📄 Archivos de configuración clave / Key Configuration Files

No se requieren archivos de configuración para este ejercicio.

```v
import os

fn main() {
    println('Enter your name: ')
    name := os.get_line()
    println("Hello, ${name}!")
}
```

| Elemento | Propósito |
|----------|-----------|
| `import os` | Importa las funciones de entrada estándar de V. |
| `fn main()` | Define el punto de entrada del ejecutable. |
| `os.get_line()` | Lee una línea desde la entrada estándar. |
| `println(...)` | Escribe texto y añade un salto de línea. |
| `${name}` | Interpola el nombre dentro del saludo. |

> **ES:** El prompt usa `println`, por lo que termina con un salto de línea antes de leer el nombre.
> **EN:** The prompt uses `println`, so it ends with a newline before the name is read.

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
cd v/core/foundations/hellouser
printf 'Ada\n' | v run hello_user.v
```

### Compilar y ejecutar / Compile and run

```bash
cd v/core/foundations/hellouser
v -o hello_user hello_user.v
printf 'Ada\n' | ./hello_user
```

### Salida esperada / Expected output

Con la entrada `Ada`, la salida verificada es:

```text
Enter your name: 
Hello, Ada!
```

La ejecución como script y la ejecución del binario compilado fueron verificadas con V 0.5.2 en Linux/WSL2.

Both script execution and the compiled binary were verified with V 0.5.2 on Linux/WSL2.

---

## 📝 Notas de implementación / Implementation Notes

- **ES:** V requiere una función `main` como punto de entrada del ejecutable.
- **EN:** V requires a `main` function as the executable entry point.
- **ES:** `os.get_line()` devuelve el contenido de la línea sin el salto de línea final.
- **EN:** `os.get_line()` returns the line contents without the final newline.
- **ES:** `println` añade saltos de línea tanto al prompt como al saludo.
- **EN:** `println` appends newlines to both the prompt and the greeting.
- **ES:** El ejecutable generado es un artefacto de compilación y queda excluido por `.gitignore`.
- **EN:** The generated executable is a build artifact excluded by `.gitignore`.

---

## 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://github.com/yorche3/programming_languages)*
