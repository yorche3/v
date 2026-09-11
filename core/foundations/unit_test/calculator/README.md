# Calculator — V

Implementación de la especificación [03_Unit_Test_Calculator](https://yorche3.github.io/programming_languages/core/foundations/03_Unit_Test_Calculator/) en **V**, usando una estructura tipo librería con `src/` y `test/`, y el framework de testing integrado de V (`v test` + `assert`).

No se requiere instalar una biblioteca externa ni usar `sudo`.

---

## 📂 Archivos y estructura / Files & Structure

| Archivo / Directorio | Propósito |
|----------------------|-----------|
| [`v.mod`](v.mod) | Manifiesto del módulo V. |
| [`src/calculator.v`](src/calculator.v) | Implementación del módulo `calculator.src`. |
| [`test/calculator_test.v`](test/calculator_test.v) | Suite de pruebas integrada de V. |
| [`.gitignore`](.gitignore) | Ignora ejecutables y artefactos nativos. |

```text
calculator/
├── v.mod
├── src/
│   └── calculator.v
├── test/
│   └── calculator_test.v
├── .gitignore
└── README.md
```

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** El proyecto se creó manualmente como un módulo V. El código de producción está separado en `src/` y la suite en `test/`. V descubre los archivos `_test.v` y las funciones `test_*` automáticamente.

**EN:** The project was created manually as a V module. Production code is separated under `src/`, and the suite is under `test/`. V automatically discovers `_test.v` files and `test_*` functions.

Las operaciones siguen la implementación educativa:

- `addition`: suma directa.
- `subtraction`: resta directa.
- `multiplication`: suma repetitiva, sin usar `*`.
- `division`: resta repetitiva, sin usar `/`.
- `modulus`: reutiliza `division` y `multiplication`, sin usar `%`.

### Inicialización / Initialization

```bash
mkdir -p v/core/foundations/unit_test/calculator/{src,test}
cd v/core/foundations/unit_test/calculator
v init
```

Después se añaden el módulo en `src/` y la suite en `test/`.

---

## 📄 Archivos de configuración clave / Key Configuration Files

### `v.mod`

```v
Module {
    name: 'calculator'
    version: '0.1.0'
    license: 'MIT'
    dependencies: []
}
```

`v.mod` identifica el paquete y permite importar `calculator.src` desde la suite; el archivo en `src/` declara el módulo `src` requerido por esa ruta.

### `test/calculator_test.v`

V usa `assert` integrado y ejecuta automáticamente las funciones cuyo nombre comienza por `test_` dentro de archivos `_test.v`.

V uses its built-in `assert` and automatically runs functions whose names begin with `test_` inside `_test.v` files.

---

## 🚀 Compilación y ejecución / Build & Run

### Requisitos / Requirements

- **V 0.5.2**.
- Framework de testing integrado (`v test`).

Verificar:

```bash
v version
```

Salida verificada:

```text
V 0.5.2 76c0d94
```

### Ejecutar las pruebas / Run tests

```bash
cd v/core/foundations/unit_test/calculator
v test test
```

### Salida esperada / Expected output

```text
Summary for all V _test.v files: 5 passed, 0 failed.
```

> **ES:** El formato exacto puede variar entre versiones de V, pero deben ejecutarse los 5 tests y producirse 0 fallos.
> **EN:** The exact format may vary across V versions, but all 5 tests must run with 0 failures.

---

## 🧠 Operaciones / Operations

| Operación | Implementación educativa |
|-----------|--------------------------|
| `addition(a, b)` | Suma directa. |
| `subtraction(a, b)` | Resta directa. |
| `multiplication(a, b)` | Suma `a` repetidamente mediante `for`. |
| `division(a, b)` | Resta `b` repetidamente mediante `for`. |
| `modulus(a, b)` | Calcula el resto reutilizando `division` y `multiplication`. |

Los cinco tests están agrupados por operación mediante funciones `test_*`.

---

## 📝 Notas de implementación / Implementation Notes

- **ES:** V incluye su propio runner y aserción `assert`, por lo que no se añade una biblioteca externa de testing.
- **EN:** V includes its own runner and `assert`, so no external testing library is added.
- **ES:** `v test` descubre automáticamente `test/calculator_test.v` por el sufijo `_test.v` y las funciones `test_*`.
- **EN:** `v test` automatically discovers `test/calculator_test.v` through the `_test.v` suffix and `test_*` functions.
- **ES:** La división por cero y los divisores no positivos quedan fuera de los casos básicos y generan un `panic` explícito.
- **EN:** Division by zero and non-positive divisors are outside the basic cases and produce an explicit `panic`.
- **ES:** El código fuente no incluye comentarios inline; la explicación se mantiene en este README.
- **EN:** The source code contains no inline comments; explanations are kept in this README.

---

## 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://github.com/yorche3/programming_languages)*
