/**
 * Написать программу, в которой определить две параллельные области, каждая из которых
 * содержит итерационную конструкцию for выполняющую инициализацию элементов
 * одномерных массивов целых чисел a[12], b[12] и c[12]. Число нитей перед первой областью
 * задать равным 3, перед второй – равным 4. Первая параллельная область выполняет
 * инициализацию элементов массивов a и b с использованием статического распределения
 * итераций, размер порции итераций выбрать самостоятельно, вторая параллельная область
 * выполняет инициализацию элементов массива c по следующему правилу c[i] = a[i] + b[i], с
 * использованием динамического распределения итераций, размер порции итераций выбрать
 * самостоятельно. В каждой области определить и выдать на экран количество нитей, номер
 * нити и результат выполнения цикла. Убедиться в правильности работы программы.
 */

#include <cstdio>
#include <omp.h>

int main() {

    int a[12];
    int b[12];
    int c[12];
    omp_set_num_threads(3);

#pragma omp parallel for shared(a, b) schedule (static, 5)
    for (int i = 0; i < 12; i++) {
        a[i] = i + 1;
        b[i] = i + 1;
        printf("number of threads: %d thread number: %d a[%d] = %d b[%d] = %d\n", omp_get_num_threads(),
               omp_get_thread_num(), i, a[i], i, b[i]);
    }

    omp_set_num_threads(4);

#pragma omp parallel for shared(a, b, c) schedule (dynamic, 4)
    for (int i = 0; i < 12; i++) {
        c[i] = a[i] + b[i];
        printf("number of threads: %d  thread number: %d c[%d] = %d\n", omp_get_num_threads(), omp_get_thread_num(), i,
               c[i]);
    }
    return 0;
}