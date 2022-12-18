Лабораторные предметы по предмету "Архитектура компьютерной техники и операционные системы" (АКТиОС).

Варианты преимущественно 7 (либо 6, где индексация с нуля).

== ЛАБОРАТОРНАЯ РАБОТА 2 ==

Multisim. Умножение с младших разрядов со сдвигом суммы вправо. Могут быть баги с работой лампочки.

== ЛАБОРАТОРНАЯ РАБОТА 3 ==

Multisim. Умножение с младших разрядов со сдвигом суммы вправо. Автомат Мили, схема и синтез прилагаются.

== ЛАБОРАТОРНАЯ РАБОТА 4 ==

При запуске скомпилированная программа осуществляет вывод информации о железе (аналог -lspci), делая перебор по шинам, девайсам и функциям. 

Информация выводится из "матрицы", где по вертикали регистры, по горизонтали биты. Регистры считаются сверху вниз от нуля до пятнадцати, биты в них справа налево от нуля до трёх.

Запуск скомпилированной программы осуществляется через терминал: **sudo ./prog**. Аргументы не требуются, но нужны права администратора.

== ЛАБОРАТОРНАЯ РАБОТА 5 ==

1. Bash. Написать скрипт, подсчитывающий суммарный размер файлов в заданном каталоге и всех его подкаталогах (имя каталога задаётся пользователем в качестве аргумента командной строки). Скрипт выводит результаты подсчёта в файл (второй аргумент командной строки) в виде "каталог (полный путь), суммарный размер файлов число просмотренных файлов".
2. C/C++. Найти все дубликаты (с одинаковым содержимым) файлов в заданном диапазоне размеров от N1 до N2 (N1, N2 задаются в аргументах командной строки), начиная с исходного каталога и ниже. Имя исходного каталога задаётся пользователем в качестве первого аргумента командной строки.  

Пример аргументов для запуска bash-файла через терминал: **./prog ./amogus sus.txt** (файлы в папке amogus, лежащей рядом с bash-файлом; сохраняется результат в файл sus.txt рядом с башником)

Пример аргументов для запуска скомпилированной c-программы через терминал: **./prog ./amogus 0 1000** (файлы в папке amogus, лежащей рядом со скомпилированной c-программой, размерами в диапазоне от 0 до 1000; остальные файлы не учитывать)

== ЛАБОРАТОРНАЯ РАБОТА 6 ==

C/C++. Написать программу нахождения массива значений функции y[i]=sin(2\*PI\*i/N) i= [0, N-1] с использованием ряда Тейлора. Пользователь задаёт значения N и количество n членов ряда Тейлора. Для расчета каждого члена ряда Тейлора запускается отдельный процесс и его результат (член ряда) записывается в файл. Каждый процесс выводит на экран свой id и рассчитанное значение ряда. Головной процесс суммирует все члены ряда Тейлора, и полученное значение y[i] записывает в файл.

Приложено три реализации вышеизложенного условия: на потоках, на процессах и без того и другого. Важно: файл с результатами сохраняется в каталоге "Компьютер/tmp/result.txt", а не рядом с скомпилированной программой. Для корректной работы программы с потоками добавьте в линкер библиотеку pthread (в Eclipse это Properties->C/C++ Build->Settings->GCC Linker->Libraries).

Пример аргументов для запуска скомпилированной c-программы через терминал: **./prog 2 4** (четыре игрека по два приближения ряда тейлора)

== ЛАБОРАТОРНАЯ РАБОТА 7 ==

Создать дерево процессов согласно варианта индивидуального задания. Дерево процессов из таблицы 1. Последовательность обмена сигналами из таблицы 2.

Запуск скомпилированной программы осуществляется через терминал: **./prog**. Аргументы не требуются.