Лабораторные предметы по предмету "Архитектура компьютерной техники и операционные системы" (АКТиОС).

Варианты преимущественно 7 (либо 6, где индексация с нуля).

<h2> ЛАБОРАТОРНАЯ РАБОТА 2 </h2> 

Умножение с младших разрядов со сдвигом суммы вправо. Для запуска нужен Multisim. Могут быть баги с работой лампочки. Для работы нужно нажимать кнопки слева в определённом порядке, порядок изложен в блок-схеме.

<h2> ЛАБОРАТОРНАЯ РАБОТА 3 </h2> 

Умножение с младших разрядов со сдвигом суммы вправо. Для запуска нужен Multisim. Автомат Мили, схема и синтез прилагаются. Для работы нужно нажать и отжать кнопку очистки, а затем много раз нажимать и отжимать такт автомата, пока не появится результат на табло справа. Фактически, автомат подаёт сигналы в том же порядке, в котором нажимались кнопки в лабораторной работе 2.

<h2> ЛАБОРАТОРНАЯ РАБОТА 4 </h2> 

Для работы потребуется любая C/C++ IDE и компилятор GCC. Программа на C компилируется и запускается при помощи команд терминала, открытого из папки со скомпилированным C-файлом. 

При запуске скомпилированная программа осуществляет вывод информации о железе (аналог -lspci), делая перебор по шинам, девайсам и функциям. 

Информация выводится из "матрицы", где по вертикали регистры, по горизонтали биты. Регистры считаются сверху вниз от нуля до пятнадцати, биты в них справа налево от нуля до трёх. Какие именно данные лежат по "координатам" регистр-бит, можно узнать в методе.

Пример команды терминала для запуска скомпилированной программы: **sudo ./prog**. Аргументы не требуются, но нужны права администратора.

<h2> ЛАБОРАТОРНАЯ РАБОТА 5 </h2> 

1. Bash. Написать скрипт, подсчитывающий суммарный размер файлов в заданном каталоге и всех его подкаталогах (имя каталога задаётся пользователем в качестве аргумента командной строки). Скрипт выводит результаты подсчёта в файл (второй аргумент командной строки) в виде "каталог (полный путь), суммарный размер файлов число просмотренных файлов".
2. C/C++. Найти все дубликаты (с одинаковым содержимым) файлов в заданном диапазоне размеров от N1 до N2 (N1, N2 задаются в аргументах командной строки), начиная с исходного каталога и ниже. Имя исходного каталога задаётся пользователем в качестве первого аргумента командной строки.  

Для работы потребуется любая C/C++ IDE и компилятор GCC. Программа на C компилируется и запускается при помощи команд терминала, открытого из папки со скомпилированным C-файлом. Скрипт на bash запускается точно так же, но его нужно предварительно сделать исполняемым при помощи команды **chmod +x prog.sh**.

Пример команды терминала для запуска bash-файла: **bash: ./prog ./amogus sus.txt** (файлы в папке amogus, лежащей рядом с bash-файлом; сохраняется результат в файл sus.txt рядом с bash-файлом)

Пример команды терминала для запуска скомпилированной c-программы: **./prog ./amogus 0 1000** (файлы в папке amogus, лежащей рядом со скомпилированной c-программой, размерами в диапазоне от 0 до 1000; остальные файлы не учитывать)

<h2> ЛАБОРАТОРНАЯ РАБОТА 6 </h2> 

1. C/C++. Написать программу нахождения массива значений функции y[i]=sin(2\*PI\*i/N) i= [0, N-1] с использованием ряда Тейлора. Пользователь задаёт значения N и количество n членов ряда Тейлора. Для расчета каждого члена ряда Тейлора запускается отдельный процесс и его результат (член ряда) записывается в файл. Каждый процесс выводит на экран свой id и рассчитанное значение ряда. Головной процесс суммирует все члены ряда Тейлора, и полученное значение y[i] записывает в файл.

Для работы потребуется любая C/C++ IDE и компилятор GCC. Программа на C компилируется и запускается при помощи команд терминала, открытого из папки со скомпилированным C-файлом. 

Приложено три реализации вышеизложенного условия: на потоках, на процессах и без того и другого. Важно: файл с результатами сохраняется в каталоге "Компьютер/tmp/result.txt", а не рядом с скомпилированной программой. Для корректной работы программы с потоками добавьте в линкер библиотеку pthread (в Eclipse это Properties->C/C++ Build->Settings->GCC Linker->Libraries).

Пример команды терминала для запуска скомпилированной программы: **./prog 2 4** (четыре игрека по два приближения ряда тейлора)

<h2> ЛАБОРАТОРНАЯ РАБОТА 7 </h2> 

Создать дерево процессов согласно варианта индивидуального задания. Дерево процессов из таблицы 1. Последовательность обмена сигналами из таблицы 2.

Для работы потребуется любая C/C++ IDE и компилятор GCC. Программа на C компилируется и запускается при помощи команд терминала, открытого из папки со скомпилированным C-файлом. 

Пример команды терминала для запуска скомпилированной программы: **./prog**. Аргументы не требуются.
