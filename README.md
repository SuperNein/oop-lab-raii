# Класс с ручным управлением памятью

**Лабораторная работа 2**

---

**Тема:** Базовый интерфейс класса, RAII, правило пяти, copy-and-swap

**Вариант:** Матрица на одномерном динамическом массиве. Проверка симметричности

**Стандарт языка:** C++20  
**Система сборки:** CMake 3.16+  
**Тестирование:** Google Test

**Ограничения:**
Запрещено использовать `std::string`, `std::vector`, `std::array`, умные указатели - только ручное управление памятью (`new[]` / `delete[]`).

---

## Сборка и запуск

### Требования

* Компилятор C++20
* CMake 3.16+

### 1. Конфигурация проекта

Создание папки сборки `build` и установка зависимостей:

```Bash
cmake -B build
```

### 2. Компиляция

Собрать сразу весь проект (основная программа `app` и тесты `app_tests`):

```Bash
cmake --build build
```

- Только основную интерактивную программу:

```Bash
cmake --build build --target app
```

- Только тесты:

```Bash
cmake --build build --target app_tests
```

### 3. Запуск

#### Основная программа

- **Linux / macOS:**

```Bash
./build/lab
```
    
- **Windows (PowerShell / cmd):**

```PowerShell
.\build\lab.exe
# Или для конфигурации Visual Studio:
.\build\Debug\lab.exe
```

#### Запуск тестов Google Test

- **Linux / macOS:**

```Bash
./build/lab_tests
```

- **Windows:**

```PowerShell
.\build\lab_tests.exe
# Или для конфигурации Visual Studio:
.\build\Debug\lab_tests.exe
```

---

## Структура проекта

```text
oop-lab-raii/
├── .gitignore
├── CMakeLists.txt
├── README.md
├── include/
│   └── matrix.hpp       # Объявления класса Matrix
├── src/
│   ├── matrix.cpp       # Реализация методов Matrix
│   └── main.cpp         # Интерактивное текстовое меню
└── tests/
    └── test.cpp         # Google Tests
```

---

Объектно-ориентированное программирование

Семестр 3. Лабораторная работа 2
