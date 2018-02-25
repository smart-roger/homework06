#include <iostream>
#include "TMatrix.h"


int main()
{
    //  Создание двумерной матрицы
    TMatrix <int, 0> test_matrix;

    //  Заполнение диагоналей матрицы
    for(auto index=0; index<10; ++index){
        test_matrix[index][index] = index;
        test_matrix[9-index][index] = 9-index;
    }

    //  Вывод матрицы в консоль
    for(auto i=1; i<9; ++i){
        for (auto j=1; j<9; ++j)
            std::cout << test_matrix[i][j] << " " ;
        std::cout << std::endl;
    }
    //  Вывод кол-ва занятых ячеек
    std::cout << test_matrix.size() << std::endl;

    //  Обход занятых ячеек
    for(auto iter = test_matrix.cbegin();
        iter!=test_matrix.cend();
        ++iter)
            std::cout << iter <<  std::endl;
    /*
    //  Пример использования N-мерной матрицы
    TMatrix<int,-99, 5> matrix_5d;
    matrix_5d[7][6][5][4][9] = 78;
    std::cout << matrix_5d[7][6][5][4][9] << std::endl;

    try{
        std::cout << matrix_5d[25][43][73][42] << std::endl;
    }catch(...){
        std::cout << "Was something wrong? ;)" << std::endl;
    }

    std::cout << matrix_5d.size();
    matrix_5d.print();
    */
    return 0;
}
