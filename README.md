# Описание #

Класс для вычисления простых математических выражений на С++

# Методы класса #

**double solve()** //возвращает значение выражения, переданного классу, меняя это выражение

**double solved()** //возвращает значение выражения, не меняя его

**Expression& multiply(double num)** //умножение каждого числа выражения на число num

**Expression& divide(double num)** //деление каждого числа выражения на число num

**Expression& subtract(double num)** //вычитание из каждого числа выражения число num

**Expression& add(double num)** //прибавление к каждому числу выражения число num

**void set_expr(string exprStr)** //передает выражение exprStr классу

**void set_value(int index, string val)** //заменяет элемент выражения по индексу index на значение val (можно заменить как и число, так и оператор выражения. Важно, чтобы замена не нарушала чередования чисел и операторов)

**int size()** //возвращает длину выражения (количество чисел и операторов)

**string at(int index)** //возвращает элемент выражения по индексу index

**vector<string> get_vector()** //возращает вектор элементов выражения (нужно учитывать, что значения в скобках вычисляются на этапе передачи выражения классу)

**vector<string> get_brackets()** //возвращает вектор из выражений, записанных в скобках

**void print_vector()** //выводит в консоль вектор выражения

**void print_brackets()** //выводит в консоль значения в скобках

**void print_string()** //выводит в консоль выражение в строковом виде

# Примечания #

**Синтаксис ввода**

Ввод осуществляется передачей выражения в строковом виде в конструктор при создании объекта класса или в функцию set_expr() как параметр. Синтаксис строки, передаваемой в класс, почти идентичен функции eval() из Python и так же не восприимчив к пробелам между действиями 
```
Expression expr("2 + 2 * 2");
std::cout << expr.solved(); // 6	
```
Такой же код на Python:
```
print(eval("2 + 2 * 2")) // 6
```

**Разница между solve() и solved()**

Главное отличие функции solve() от solved() - это изменение выражения в классе при его решении, тогда как solved() только возвращает результат решения примера, не меняя самого выражения

```
Expression expr("2+2*2");

std::cout << expr.solved() << " <> "; //применятся функция solved()
expr.print_vector();
```
Вывод: 6 <> [2] [+] [2] [*] [2]
```
Expression expr("2+2*2");

std::cout << expr.solve() << " <> "; //применятся функция solve()
expr.print_vector();
```
Вывод: 6 <> [6]

**Возможность строить цепочки вызовов функций**

Математические функции класса позволяют строить цепочки из функций, значительно сокращая код

```
Expression expr("2+2*2");

expr.add(4).divide(3).subtract(10);
expr.print_vector();
```
Вывод: [-8] [+] [-8] [*] [-8]

**Функции вывода выражения**

Эти функции позволяют вывести в терминал выражение в различных видах

```
Expression expr("2+2*(2+15)");

expr.print_string();
expr.print_vector();
expr.print_brackets();
```

Вывод: 	

2+2*(2+15)

[2] [+] [2] [*] [17]

(2+15)

**Допустимые действия**

Возможно использование только операторов умножения(*), деления(/), сложения(+), вычитания(-), возведения в степень(^), деления с остатком(%)

# Пример использования #

```
#include <iostream>
#include "Expression.h" 

int main() {
	Expression expr("2+2*2+14"); 
	std::cout << expr.solve() << "\n"; 
}
```
