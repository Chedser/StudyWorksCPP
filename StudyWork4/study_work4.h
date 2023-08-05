#ifndef STUDY_WORK4
#define STUDY_WORK4

#define M_PI ((float)3.141592653589793)
#define M_PI12 (M_PI/12.F)
#define M_PI6 (M_PI/6.F)
#define M_PI2 (M_PI/2.F)
#define SQRT3 ((float)1.732050807569)

#include <iostream>

using namespace std;

/* Перечисление для определения вида функции */
enum RangeType { First, Second, Third } rangeType;

namespace Vectorflex {
    /* Возведение в степень */
    double raiseToPow(double x, int power) {
    if (x == 0 && power == 0) { throw 1; }
        double result = 1.0;
        for (int i = 1; i <= power; i++) {
            result = result * x;
        }
        return result;
    }

    /* Арктангенс */
    float arctan(float x) {
        int sta = 0, sp = 0;
        float x2, a;
        if (x < 0.F) { x = -x; sta |= 1; }
           if (x > 1.F) { x = 1.F / x; sta |= 2; }
        while (x > M_PI12) {
            sp++; a = x + SQRT3; a = 1.F / a; x *= SQRT3; x -= 1.F; x *= a;
        }
        x2 = x * x; a = x2 + 1.4087812F; a = 0.55913709F / a; a += 0.60310579F;
        a -= 0.05160454F * x2; a *= x;
        while (sp > 0) { a += M_PI6; sp--; }
        if (sta & 2) a = M_PI2 - a;
        if (sta & 1) a = -a;
        return(a);
    }
    
    /* Абсолютное значение */
    double abs(double digit) {
        if (digit < 0) {
              digit = -digit;
        }
        return digit;
    }

    /* Косинус */
    double cosinus(double x){
        double k = 0;
        double e = 0.1, d = 1, s = 1;
  
        while (31.416 < x) {
            x = x - 31.416;
        }
        while (x < -31.416) {
            x = x + 31.416;
        }

        while (e < abs(d)) {
            k = k + 1;
            d = (-d) * x * x / ((2 * k - 1) * (2 * k));
            s = s + d;
        }
        return s;
    }

    /* Минимальное значение */
    double min(double x, double y) {
        double min = x;
        if (x > y) {
              min = y;
        }
        return min;
    }

    /* Заплнение интервала аргументов функции*/
    void FillRange(double* arr, double initX, double endX, double step = 0.1) {
        int j = 0;
        for (double i = initX; i <= endX; i += step) {
             arr[j] = i;
            ++j;
        }
    }

    /* Количество элементов в интервале */
    int GetCountOfElementsInRange(double initX, double endX, double step = 0.1) {
        int j = 0;
        for (double i = initX; i <= endX; i += step) {
            ++j;
        }
       return j;
    }

    /* Две перегруженные функции отображения интервала */
    void ShowRange(double initX, double endX, double step = 0.1) {
        for (double i = initX; i <= endX; i += step) {
            cout << i << "\n";
        }
     }
    
void ShowRange(double* arr, int count) {
          for (int i = 0; i < count; i++) {
            cout << arr[i] << "\n";
        }
    }

    /* Вычисление значений функции */
    void SetValues(double* range, int count, double* values, RangeType rangeType = Third) {
        double value = 0.0;
        if (rangeType == First) {
          for (int i = 0; i < count; i++) {
                  values[i] = arctan(range[i]);
            }
        }
        else if (rangeType == Second) {
             for (int i = 0; i < count; i++) {
               values[i] = cosinus(range[i]);
            }
        }
        else {
            for (int i = 0; i < count; i++) {
               values[i] = min(arctan(range[i]), cosinus(range[i]));
            }
          }
    }

    /* Отображение значений функции */
    void ShowValues(double* range, double* values, int count) {
        for (int i = 0; i < count; i++) {
            printf("%d : %3.1f : %3.3f\n", (i + 1), range[i], values[i]);
        }
    }

    /* Определение монотонности функции */
    int IsRising(double* values, int count) {
        int result = 0;
        int risingCount = 0;
        int lowingCount = 0;
     
        for (int i = 1; i < count; i++) {
             if (values[i] > values[i - 1]) {
                ++risingCount;
           }
            else if (values[i] < values[i - 1]) {
               ++lowingCount;
            }
        }

        if (risingCount > 0 && lowingCount == 0) {
                  result = 1;
        }
        else if(risingCount == 0 && lowingCount > 0) {
            result = 0;
        }
        else {
           result = 2;
        }
        return result;
    }

    /* Отображение сообщения о монотоности функции */
    void CheckRising(double* values, double* range, int count) {
       int result = IsRising(values, count);

        if (result == 1) {
           cout << "Функция монотонно возрастает на промежутке [" << range[0] << "," << range[count - 1] << "]\n";
        }
        else if(result == 0) {
            cout << "Функция монотонно убывает на промежутке [" << range[0] << "," << range[count - 1] << "]\n";
        }
        else {
                    cout << "Функция не монотонна на промежутке [" << range[0] << "," << range[count - 1] << "]\n";
        }
        cout << "\n";
    }
}
#endif
