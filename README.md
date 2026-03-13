# Library Management System (ECPG)

Консольное приложение для управления библиотекой на C с использованием ECPG (Embedded SQL in C) для работы с PostgreSQL.

## О проекте

Проект представляет собой консольную систему управления библиотекой, которая позволяет:

* Подключаться к существующей базе данных PostgreSQL
* Создавать новую базу данных
* Просматривать, добавлять, редактировать и удалять книги
* Искать книги по названию, автору или жанру
* Создавать новых пользователей с разными ролями (admin/guest)
* Вести лог всех действий в файл

## Роли пользователей

* Administrator - полный доступ ко всем функциям
* Guest - только просмотр и поиск книг

## Технологии

* Язык: C (стандарт C17)
* База данных: PostgreSQL 18
* Взаимодействие с БД: ECPG (Embedded SQL in C)
* Сборка: Visual Studio 2022 / MSBuild
* Логирование: Файловая система (app.log)

## Функциональность

### Управление базой данных

* Подключение к существующей БД
* Создание новой БД
* Проверка существования БД
* Инициализация структуры БД (таблицы, процедуры, роли)

### Работа с книгами

* Просмотр всех книг
* Поиск по названию
* Поиск по автору
* Поиск по жанру
* Добавление новой книги (admin)
* Редактирование книги (admin)
* Удаление книги по ID (admin)
* Очистка всей таблицы (admin)

### Управление пользователями

* Создание новых пользователей (admin)
* Назначение ролей (admin_role / guest_role)
* Автоматическая проверка прав при входе

### Логирование

* Запись всех действий с временными метками
* Логирование ошибок SQL
* Запись успешных и неудачных операций
* Файл `app.log` в директории программы

## Что такое ECPG?

ECPG (Embedded SQL in C) — это препроцессор для встраивания SQL-запросов непосредственно в код на C/C++.

### Как это работает

1. Препроцессинг: Файлы с расширением `.pgc` обрабатываются утилитой `.exe`
2. Генерация кода: ECPG преобразует SQL-запросы в вызовы специальных функций
3. Компиляция: Сгенерированный C-код компилируется обычным компилятором
4. Линковка: Программа линкуется с библиотеками PostgreSQL (`libpq.lib`, `libecpg.lib`)

### Пример ECPG-кода

```c
EXEC SQL BEGIN DECLARE SECTION;
    char username[64];
    char password[64];
EXEC SQL END DECLARE SECTION;

// Встраиваемый SQL-запрос
EXEC SQL CONNECT TO :dbname USER :username USING :password;

// Вызов хранимой процедуры
EXEC SQL CALL sp_add_book(:title, :author, :genre, :year);
```

### Преимущества ECPG

* SQL-код пишется прямо в C-программе
* Проверка синтаксиса SQL на этапе препроцессинга
* Поддержка курсоров, подготовленных запросов, транзакций
* Безопасная работа с параметрами (защита от SQL-инъекций)

## Сборка проекта

### Требования

1. Visual Studio 2022 (или новее) с компонентами:

   * Разработка классических приложений на C++
   * Windows 11 SDK

2. PostgreSQL 18 с компонентами:

   * PostgreSQL Server
   * Development Libraries (для ECPG и libpq)

### Настройка окружения

1. Установите PostgreSQL с официального сайта
2. Убедитесь, что в папке `C:\Program Files\PostgreSQL\18\lib\` есть файлы:

   * `libpq.lib`
   * `libecpg.lib`

### Настройка проекта в Visual Studio

1. Создайте новый проект (Console Application)
2. Добавьте файл `main.pgc` в проект
3. Настройте свойства проекта:

**C/C++ → General → Additional Include Directories:**

```
C:\Program Files\PostgreSQL\18\include
```

**Linker → General → Additional Library Directories:**

```
C:\Program Files\PostgreSQL\18\lib
```

**Linker → Input → Additional Dependencies:**

```
libpq.lib;libecpg.lib
```

**Build Events → Pre-Build Event → Command Line:**

```cmd
if not exist "$(ProjectDir)generated" mkdir "$(ProjectDir)generated"
"c:\Program Files\PostgreSQL\18\bin\ecpg.exe" -I "c:\Program Files\PostgreSQL\18\include" -o "$(ProjectDir)generated\main.c" "$(ProjectDir)main.pgc"
```

### Сборка

1. Добавьте сгенерированный файл `generated\main.c` в проект (через "Show All Files")
2. Нажмите `Ctrl+Shift+B` для сборки
3. Запустите `F5` для отладки или `Ctrl+F5` без отладки

## Структура проекта

```
ECPG/
├── main.pgc              # Исходный код с ECPG
├── generated/            # Сгенерированные файлы
│   └── main.c            # Сгенерированный C-код
├── x64/                  # Скомпилированные файлы
│   └── Debug/
│       └── ECPG.exe      # Исполняемый файл
├── app.log               # Файл с логами
└── ECPG.sln              # Файл решения Visual Studio
```

## Структура базы данных

### Таблицы

```sql
books (
    id SERIAL PRIMARY KEY,
    title VARCHAR(255),
    author VARCHAR(255),
    genre VARCHAR(255),
    year INT
)
```

### Роли

* `admin_role` - полные права на таблицу books
* `guest_role` - только SELECT

### Хранимые процедуры

* `sp_add_book` - добавление книги
* `sp_update_book` - обновление книги
* `sp_delete_by_id` - удаление книги по ID
* `sp_clear_table` - очистка таблицы
* `sp_create_db_user` - создание нового пользователя

### Функции

* `sp_get_all_books` - получение всех книг
* `sp_find_by_title` - поиск по названию
* `sp_find_by_author` - поиск по автору
* `sp_find_by_genre` - поиск по жанру

## Особенности реализации

### Управление транзакциями

* Каждая операция выполняется в отдельной транзакции
* Автоматический COMMIT при успехе
* ROLLBACK при ошибке

### Обработка ошибок

* Функция `print_sql_error()` для вывода ошибок SQL
* Логирование всех ошибок в `app.log`
* Восстановление после ошибок (возможность вернуться в меню)

### Навигация

* Возможность вернуться в главное меню на любом этапе (ввод 0)
* Опция "Disconnect and go back to start" в основном меню

### Логирование

* Временные метки в формате `[YYYY-MM-DD HH:MM:SS]`
* Запись начала и завершения действий
* Логирование успешных и неудачных операций
* Логирование ошибок SQL

## Пример использования

```bash
=== Main Menu ===
1. Connect to existing database
2. Create new database
0. Exit
Choice: 1

=== PostgreSQL Server Connection ===
Host [localhost]: localhost
Port [5433]: 5433
Superuser [postgres]: postgres
Superuser password: admin

=== Connect to Existing Database ===
Database name: library

=== User Login ===
Username: admin_user
Password: admin123

=== Menu ===
1. Show all books
2. Search books
3. Add new book
4. Update book
5. Delete book by ID
6. Clear table
7. Create new user
8. Disconnect and go back to start
0. Exit
```
