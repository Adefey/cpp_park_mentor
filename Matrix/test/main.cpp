/*
Необходимо разработать классы для работы с вещественными числами, векторами
(строками размерности 1xN и столбцами размерности Nx1) и матрицами размерности
MxN и реализовать операции над ними: 1) обращение по индексам к элементам,
извлечение диагонали, строки или столбца - 1б (после модификации исходной
матрицы извлечённые элементы меняться не должны); 2) возможность создания
матрицы из векторов или чисел, вектора из чисел - 1б; 3) поэлементное
сложение/вычитание/умножение объектов одинаковой размерности - 1б; 4) умножение
числа на матрицу, вектора на матрицу, матрицы на вектор и матрицы на матрицу -
1б; 5) суммирование/вычитание числа и вектора/матрицы, матрицы и вектора (с
возможностью выбора - по строкам/по столбцам) - 1б; 6) получение
транспонированной и обратной матриц - 1б; 7) подсчёт определителя матрицы - 1б.

Все основные операции должны быть реализованы через перегрузку операторов
(операторы могут быть модифицирующие (+= и др.) и немодифицирующие (+ и др.)).

Доп. баллы:
- поддержка "слайсов, как в питоне" (на уровне методов, т.к. операторы такой
синтаксис не поддерживают). В качестве примерного интерфейса можно опираться на
то, как это сделано в " аналоге numpy на C++"
https://github.com/dpilger26/NumCpp -1б;
- размерность матриц может задаваться с помощью шаблонных параметров -2б;

Для сдачи необходимо развернуть базовый CI, в котором будут осуществляться
автоматическая сборка и тестирование проекта (хотя бы один интеграционный тест,
показывающий работоспособность всех реализованных пунктов). Без покрытия тестами
каждый пункт оценивается в 50% стоимости.
*/

#include <doublearray.hpp>
#include <doublematrix.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(VectorTest, EmptyConstructorTest) {
  DoubleArray arr1;
  DoubleArray arr2(0);
  DoubleArray arr3 = arr1;
  EXPECT_EQ(arr1, arr2);
  EXPECT_EQ(arr2, arr3);
  EXPECT_EQ(arr3, arr1);
}

TEST(VectorTest, MassiveConstructorTest) {
  DoubleArray arr1 = {1.0, 2, 3, 4, 5, 6};
  DoubleArray arr2(6);
  DoubleArray arr2i = {0, 0, 0, 0, 0, 0};
  EXPECT_EQ(arr2, arr2i);
  DoubleArray arr3 = arr1;
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr2.size(), arr3.size());
  EXPECT_EQ(arr3, arr1);
}

TEST(VectorTest, SetGetTest) {
  DoubleArray arr1 = {1.0, 2, 3, 4, 5, 6};
  DoubleArray arr2 = {1.0, 2, 9, 4, 5, 6};
  DoubleArray arr3 = {1.0, 2, 5, 4, 5, 6};
  arr1[2] = 9;
  EXPECT_EQ(arr1[2], 9);
  EXPECT_EQ(arr1, arr2);
  EXPECT_EQ(arr1[2] - 4, arr3[2]);
}

TEST(VectorTest, AddTest) {
  DoubleArray arr1 = {1.0, 2, 3, 4, 5, 6};
  DoubleArray arr2 = {10.0, 20, 30, 40, 50, 60};
  DoubleArray arr3 = {11.0, 22, 33, 44, 55, 66};
  DoubleArray arr4 = arr1 + arr2;
  EXPECT_EQ(arr3, arr4);
}

TEST(VectorTest, SubstractTest) {
  DoubleArray arr1 = {1.0, 2, 3, 4, 5, 6};
  DoubleArray arr2 = {10.0, 20, 30, 40, 50, 60};
  DoubleArray arr3 = {-9.0, -18, -27, -36, -45, -54};
  DoubleArray arr4 = arr1 - arr2;
  EXPECT_EQ(arr3, arr4);
}

TEST(VectorTest, MultiplyTest) {
  DoubleArray arr1 = {1.0, 2, 3, 4, 5, 6};
  DoubleArray arr2 = {10.0, 20, 30, 40, 50, 60};
  DoubleArray arr3 = {10.0, 40, 90, 160, 250, 360};
  DoubleArray arr4 = arr1 * arr2;
  EXPECT_EQ(arr3, arr4);
}

TEST(VectorTest, AddDoubleTest) {
  DoubleArray arr1 = {1.0, 2, 3, 4, 5, 6};
  DoubleArray arr2 = {2, 3, 4, 5, 6, 7};
  DoubleArray arr3 = arr1 + 1;
  EXPECT_EQ(arr3, arr2);
}

TEST(VectorTest, SubstractDoubleTest) {
  DoubleArray arr1 = {1.0, 2, 3, 4, 5, 6};
  DoubleArray arr2 = {2, 3, 4, 5, 6, 7};
  DoubleArray arr3 = arr2 - 1;
  EXPECT_EQ(arr3, arr1);
}

TEST(MatrixTest, EmptyConstructorTest) {
  DoubleMatrix arr1;
  DoubleMatrix arr2(0, 0);
  DoubleMatrix arr3 = arr1;
  EXPECT_EQ(arr1, arr2);
  EXPECT_EQ(arr2, arr3);
  EXPECT_EQ(arr3, arr1);
}

TEST(MatrixTest, MassiveConstructorTest) {
  DoubleMatrix mat1;
  DoubleMatrix mat2(3, 2);
  DoubleMatrix mat3 = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(mat3[1][1], 4);
  EXPECT_EQ(mat2.size(), mat3.size()); // 3==3
  DoubleMatrix mat2i = {{0, 0}, {0, 0}, {0, 0}};
  EXPECT_EQ(mat2, mat2i);
  DoubleMatrix mat4 = mat3;
  EXPECT_EQ(mat4, mat3);
}

TEST(MatrixTest, SetGetTest) {
  DoubleMatrix mat1 = {{1, 2}, {3, 4}, {5, 6}};
  DoubleMatrix mat2 = {{1, 2}, {3, 6}, {5, 6}};
  DoubleMatrix mat3 = {{3, 5}, {7, 9}, {11, 13}};
  mat1[1][1] = 6;
  EXPECT_EQ(mat1[1][1], 6);
  EXPECT_EQ(mat1, mat2);
}

TEST(MatrixTest, AddTest) {
  DoubleMatrix mat1 = {{1, 2}, {3, 4}, {5, 6}};
  DoubleMatrix mat2 = {{2, 3}, {4, 5}, {6, 7}};
  DoubleMatrix mat3 = {{3, 5}, {7, 9}, {11, 13}};
  DoubleMatrix mat4 = mat1 + mat2;
  EXPECT_EQ(mat3, mat4);
}

TEST(MatrixTest, SubstractTest) {
  DoubleMatrix mat1 = {{1, 2}, {3, 4}, {5, 6}};
  DoubleMatrix mat2 = {{2, 3}, {4, 5}, {6, 7}};
  DoubleMatrix mat3 = {{3, 5}, {7, 9}, {11, 13}};
  DoubleMatrix mat4 = mat3 - mat2;
  EXPECT_EQ(mat1, mat4);
}

TEST(MatrixTest, MultiplyTest) {
  DoubleMatrix mat1 = {{1, 2}, {3, 4}, {5, 6}};
  DoubleMatrix mat2 = {{2, 3}, {4, 5}, {6, 7}};
  DoubleMatrix mat3 = {{2, 6}, {12, 20}, {30, 42}};
  DoubleMatrix mat4 = mat1 * mat2;
  EXPECT_EQ(mat3, mat4);
}

TEST(MatrixTest, DoubleMultMatrix) {
  DoubleMatrix mat1 = {{1, 2}, {3, 4}, {5, 6}};
  double n = 3;
  DoubleMatrix mat2 = {{3, 6}, {9, 12}, {15, 18}};
  DoubleMatrix mat3 = n * mat1;
  EXPECT_EQ(mat3, mat2);
}

TEST(MatrixTest, VectorMultMatrix) {
  DoubleArray arr1 = {1, 2, 3};
  DoubleMatrix mat1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  DoubleArray arr2 = arr1 * mat1;
  DoubleArray arr3 = {30, 36, 42};
  EXPECT_EQ(arr2, arr3);
}

TEST(MatrixTest, MatrixMultVector) {
  DoubleArray arr1 = {1, 2, 3};
  DoubleMatrix mat1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  DoubleArray arr2 = mat1 * arr1;
  DoubleArray arr3 = {14, 32, 50};
  EXPECT_EQ(arr2, arr3);
}

TEST(MatrixTest, MatrixMultMatrix) {
  DoubleMatrix mat1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  DoubleMatrix mat2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  DoubleMatrix mat3 = matrix_multiply(mat1, mat2);
  DoubleMatrix mat4 = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
  EXPECT_EQ(mat3, mat4);
}

TEST(MatrixTest, AddDoubleTest) {
  DoubleMatrix mat1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  DoubleMatrix mat2 = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
  DoubleMatrix mat3 = mat1 + 1;
  EXPECT_EQ(mat3, mat2);
}

TEST(MatrixTest, SubstractDoubleTest) {
  DoubleMatrix mat1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  DoubleMatrix mat2 = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
  DoubleMatrix mat3 = mat2 - 1;
  EXPECT_EQ(mat3, mat1);
}

TEST(MatrixTest, AddArrToMatrixTest) {
  DoubleMatrix mat1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  DoubleArray arr1 = {1, 2, 3};
  DoubleMatrix mat2 = {{1, 2, 3}, {5, 7, 9}, {7, 8, 9}};
  DoubleMatrix mat3 = add_arr_to_matrix(mat1, arr1, 1, true);
  EXPECT_EQ(mat3, mat2);
  DoubleMatrix mat4 = {{1, 3, 3}, {4, 7, 6}, {7, 11, 9}};
  DoubleMatrix mat5 = add_arr_to_matrix(mat1, arr1, 1, false);
  EXPECT_EQ(mat5, mat4);
}

TEST(MatrixTest, SubstractArrFromMatrixTest) {
  DoubleMatrix mat1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  DoubleArray arr1 = {1, 2, 3};
  DoubleMatrix mat2 = {{1, 2, 3}, {3, 3, 3}, {7, 8, 9}};
  DoubleMatrix mat3 = substract_arr_from_matrix(mat1, arr1, 1, true);
  EXPECT_EQ(mat3, mat2);
  DoubleMatrix mat4 = {{1, 1, 3}, {4, 3, 6}, {7, 5, 9}};
  DoubleMatrix mat5 = substract_arr_from_matrix(mat1, arr1, 1, false);
  EXPECT_EQ(mat5, mat4);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
