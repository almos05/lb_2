#include <windows.h>
#include <iostream>


class vect;
class matr;

// Класс для представления математического вектора
class vect {
private:
    int dim;         // Размерность вектора
    double *v;       // Указатель на массив, содержащий элементы вектора

public:
    int num;         // Номер вектора (для отладки)
    static int count; // Статический счетчик для подсчета общего количества векторов
    // Конструкторы и деструктор
    vect();                  // Конструктор по умолчанию
    vect(int d, double *x);  // Конструктор с параметрами
    vect(vect &x);           // Конструктор копирования
    ~vect();                 // Деструктор
    // Операторы
    vect operator+(vect &r); // Оператор сложения двух векторов
    vect operator-();        // Унарный оператор минус (смена знака всех элементов вектора)
    friend vect operator-(vect l, vect r); // Дружественная функция для вычитания двух векторов
    friend vect operator*(vect l, int r);  // Дружественная функция для умножения вектора на число
    int operator*(vect &r);                // Оператор скалярного произведения двух векторов
    vect operator=(vect &r);               // Оператор присваивания
    void print();                          // Функция для вывода вектора
    friend vect operator*(matr &l, vect &r); // Дружественная функция для умножения матрицы на вектор
};

int vect::count = 0; // Инициализация статического счетчика векторов
vect::vect() {
    count++;
    num = count;
    dim = 0;
    v = NULL;
    std::cout << "  VECT_DEBUG: Создан вектор; Номер вектора: " << num << "; Всего векторов: " << count << "\n";
}
vect::vect(int d, double *x) {
    count++; num = count;
    if (d > 0) {
        dim = d;
        v = new double[dim];
        for (int i = 0; i < dim; i++) {
            v[i] = x[i];
        }
    }
    std::cout << "  VECT_DEBUG: Создан вектор; Номер вектора: " << num << "; Всего векторов: " << count << "\n";
}
vect::vect(vect &x) {
    count++; num = count;
    dim = x.dim; // this -> dim = x.dim
    v = new double [dim];
    for (int i = 0; i < dim; i++) {
        v[i] = x.v[i];
    }
    std::cout << "  VECT_DEBUG: Создан вектор; Номер вектора: " << num << "; Всего векторов: " << count << "\n";
}
vect::~vect() {
    std::cout << "  VECT_DEBUG: Уничтожен вектор; Номер вектора: " << num << "; Всего векторов: " << count << "\n";
    delete[] v;
}
vect vect::operator+(vect &r) {
    vect tmp;
    tmp.dim = dim; //(r.dim, this -> dim)
    tmp.v = new double [dim];
    for (int i = 0; i < dim; i++) {
        tmp.v[i] = (*this).v[i] + r.v[i];
    }
    std::cout << "  VECT_DEBUG: Произошло сложение векторов с номерами " << num << " и "  << r.num << "\n";
    return tmp;
}
vect operator-(vect l, vect r) {
    vect tmp;
    tmp.dim = r.dim; //(r.dim, this -> dim)
    tmp.v = new double [r.dim];
    for (int i = 0; i < r.dim; i++) {
        tmp.v[i] = l.v[i] - r.v[i];
    }
    std::cout << "  VECT_DEBUG: Произошло вычитание векторов с номерами " << l.num << " и "  << r.num << "\n";
    return tmp;
}
vect vect::operator-() {
    vect tmp;
    tmp.dim = dim;
    tmp.v = new double [dim];
    for (int i = 0; i < dim; i++) {
        tmp.v[i] = -v[i];
    }
    std::cout << "  VECT_DEBUG: Произошло унарное вычитание вектора с номером " << num << "\n";
    return tmp;
}
vect operator*(vect l, int r) {
    vect tmp;
    tmp.dim = l.dim; //(r.dim, this -> dim)
    tmp.v = new double [l.dim];
    for (int i = 0; i < l.dim; i++) {
        tmp.v[i] = l.v[i] * r;
    }
    std::cout << "  VECT_DEBUG: Произошло умножение числа на вектор с номером " << l.num << "\n";
    return tmp;
}
int vect::operator*(vect &r) {
    int tmp;
    for (int i = 0; i < dim; i++) {
        tmp += v[i] * r.v[i];
    }
    std::cout << "  VECT_DEBUG: Произошло умножение векторов с номерами " << num << " и "  << r.num << "\n";
    return tmp;
}



vect vect::operator=(vect &r) {
    for (int i = 0; i < dim; i++) {
        v[i] = r.v[i];
    }
    std::cout << "  VECT_DEBUG: Произошло присваивание векторов с номерами " << num << " и "  << r.num << "\n";
    return *this;
}
void vect::print() {
    for (int i = 0; i < this->dim; i++) {
        std::cout << this->v[i] << " ";
    }
    std::cout << std::endl;
}


int ind (int n, int c, int j);
// Класс для представления математической матрицы
class matr {
    int dim; double **a; // Размер матрицы и указатель на двумерный массив элементов

public:
    // Конструкторы и деструктор
    matr();               // Конструктор по умолчанию
    matr(matr &x);        // Конструктор копирования
    matr(int n);          // Конструктор матрицы заданной размерности (без инициализации элементов)
    matr(int n, double **x); // Конструктор с инициализацией элементами
    ~matr();              // Деструктор
    // Операторы
    matr operator+(matr &r); // Сложение двух матриц
    matr operator-(matr &r); // Вычитание матриц
    matr operator-();        // Унарный минус (смена знака всех элементов матрицы)
    matr operator*(matr &r); // Умножение матриц
    friend matr operator*(double k, matr &r); // Дружественная функция для умножения матрицы на скаляр
    matr operator=(matr &r); // Оператор присваивания
    void print();            // Функция для вывода матрицы
    friend vect operator*(matr &l, vect &r); // Умножение матрицы на вектор
};

matr::matr() {
    dim = 0;
    a = NULL;
}

matr::matr(matr &x) {
    dim = x.dim;
    a = new double * [dim];
    for (int i = 0; i < dim; i++) {
        a[i] = new double [dim];
        for (int j = 0; j < dim; j++) {
            a[i][j] = x.a[i][j];
        }
    }
}

matr::matr(int n) {
    dim = n;
    a = NULL;
}

matr::matr(int n, double **x) {
    dim = n;
    a = new double * [dim];
    for (int i = 0; i < dim; i++) {
        a[i] = new double [dim];
        for (int j = 0; j < dim; j++) {
            a[i][j] = x[i][j];
        }
    }
}

matr::~matr() {
    for (int i = 0; i < dim; i++) {
        delete[] a[i];
    }
    delete[] a;
}

matr matr::operator+(matr &r) {
    matr tmp;
    tmp.dim = dim;
    tmp.a = new double * [dim];
    for (int i = 0; i < dim; i++) {
        tmp.a[i] = new double [dim];
        for (int j = 0; j < dim; j++) {
            tmp.a[i][j] = a[i][j] + r.a[i][j];
        }
    }
    return tmp;
}

matr matr::operator-(matr &r) {
    matr tmp;
    tmp.dim = dim;
    tmp.a = new double * [dim];
    for (int i = 0; i < dim; i++) {
        tmp.a[i] = new double [dim];
        for (int j = 0; j < dim; j++) {
            tmp.a[i][j] = a[i][j] - r.a[i][j];
        }
    }
    return tmp;
}

matr matr::operator-() {
    matr tmp;
    tmp.dim = dim;
    tmp.a = new double * [dim];
    for (int i = 0; i < dim; i++) {
        tmp.a[i] = new double [dim];
        for (int j = 0; j < dim; j++) {
            tmp.a[i][j] = -a[i][j];
        }
    }
    return tmp;
}

matr matr::operator*(matr &r) {
    matr tmp;
    tmp.dim = dim;
    tmp.a = new double * [dim];
    for (int i = 0; i < dim; i++) {
        tmp.a[i] = new double [dim];
        for (int j = 0; j < dim; j++) {
            tmp.a[i][j] = 0;
            for (int k1 = 0; k1 < dim; k1++) {
                tmp.a[i][j] += a[i][k1] * r.a[k1][j];
            }
        }
    }
    return tmp;
}

matr matr::operator=(matr &r) {
    dim = r.dim; // this->dim = r.dim
    a = new double * [dim];
    for (int i = 0; i < dim; i++) {
        a[i] = new double [dim];
        for (int j = 0; j < dim; j++) {
            a[i][j] = r.a[i][j];
        }
    }
    return *this;
}

matr operator*(double k, matr &r) {
    matr tmp;
    tmp.dim = r.dim;
    tmp.a = new double * [r.dim];
    for (int i = 0; i < r.dim; i++) {
        tmp.a[i] = new double [r.dim];
        for (int j = 0; j < r.dim; j++) {
            tmp.a[i][j] = r.a[i][j] * k;
        }
    }
    return tmp;
}



vect operator*(matr &l, vect &r) {
    vect tmp;
    tmp.dim = r.dim;
    tmp.v = new double [r.dim];
    for (int i = 0; i < r.dim; i++) {
        tmp.v[i] = 0;
        for (int j = 0; j < l.dim; j++) {
            tmp.v[i] += l.a[i][j] * r.v[j];
        }
    }
    return tmp;
}

void matr::print() {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Создание векторов
    double elements[] = {1.0, 2.0, 3.0};
    vect v1(3, elements);
    vect v2(3, elements);

    // Создание матриц
    double* rows[3];
    double row1[] = {1, 2, 3};
    double row2[] = {4, 5, 6};
    double row3[] = {7, 8, 9};
    rows[0] = row1;
    rows[1] = row2;
    rows[2] = row3;
    matr m1(3, rows);
    matr m2(3, rows);

    // Вывод векторов и матриц
    std::cout << "Исходный вектор v1: ";
    v1.print();
    std::cout << "Исходный вектор v2: ";
    v2.print();
    std::cout << "Исходная матрица m1:\n";
    m1.print();
    std::cout << "Исходная матрица m2:\n";
    m2.print();

    // Применение операций над векторами
    vect v3 = v1 + v2; // Сложение векторов
    vect v4 = v1 - v2; // Вычитание векторов
    vect v5 = -v1;     // Унарный минус
    vect v6 = v1 * 2.0; // Умножение вектора на скаляр
    int i1 = v1 * v2; // Поэлементное умножение векторов

    // Применение операций над матрицами
    matr m3 = m1 + m2; // Сложение матриц
    matr m4 = m1 - m2; // Вычитание матриц
    matr m5 = -m1;     // Унарный минус матрицы
    matr m6 = m1 * m2; // Умножение матриц

    // Умножение матрицы на скаляр и вектор
    matr m7 = 2.0 * m1; // Умножение матрицы на скаляр
    vect v8 = m1 * v1;  // Умножение матрицы на вектор

    // Вывод результатов операций
    std::cout << "Результат сложения векторов v1 и v2: ";
    v3.print();
    std::cout << "Результат вычитания векторов v1 и v2: ";
    v4.print();
    std::cout << "Результат унарного минуса вектора v1: ";
    v5.print();
    std::cout << "Результат умножения вектора v1 на скаляр 2.0: ";
    v6.print();
    std::cout << "Результат поэлементного умножения векторов v1 и v2: " << i1 << std::endl;

    std::cout << "Результат сложения матриц m1 и m2:\n";
    m3.print();
    std::cout << "Результат вычитания матриц m1 и m2:\n";
    m4.print();
    std::cout << "Результат унарного минуса матрицы m1:\n";
    m5.print();
    std::cout << "Результат умножения матриц m1 и m2:\n";
    m6.print();
    std::cout << "Результат умножения матрицы m1 на скаляр 2.0:\n";
    m7.print();
    std::cout << "Результат умножения матрицы m1 на вектор v1: ";
    v8.print();

    return 0;
}
