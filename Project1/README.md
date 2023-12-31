Задание:

Реализовать функции преобразования из числа в строку и из строки в число.

Условия:

При реализации алгоритмов преобразований не должны использоваться никакие библиотечные функции. Нельзя использовать типы данных размером больше int (например, long long).

1) Функция 
int strtoi (const char *str, char **p, int *ret)
анализирует строку str, преобразует её в число типа int, которое возвращается по указателю ret. В случае успеха функция возвращает 1, в случае ошибки - 0. Функция должна проверять корректность символов в строке. По указателю p (если он не нулевой) возвращается указатель на первый символ строки, содержащий некорректное значение.
Ошибкой считается случай задания строкой числа (до нулевого символа или до первого некорректного символа), не помещающегося в int. Т.е. функция должна обнаруживать переполнение int и возвращать в этом случае 0.
Систему счисления необходимо определять из вида строки:
если строка начинается с "0x", то шестнадцатиричная;
если строка начинается с "0", то восьмиричная;
если строка начинается с "b", то двоичная;
в остальных случаях десятичная.

2) Функция
int my_itoa (char *buf, int bufSize, int value, int p)
переводит переданное число value в строку символов в p-ичной системе счисления, которую записывает в буфер buf размером bufSize. Возвращает количество записанных в буфер символов (не больше bufSize). Если аргумент buf равен нулю, то необходимо подсчитать необходимый размер буфера и вернуть его.

Написать программу, демонстрирующую работу этих функций.