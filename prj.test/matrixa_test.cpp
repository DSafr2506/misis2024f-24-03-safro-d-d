#include <matrixa/matrixa.hpp>
#include <iostream>


int main() {
    MatrixA matrix_1st(7, 2);
    MatrixA matrix_2nd(5, 9);

    for (std::ptrdiff_t i = 0; i < matrix_1st.GetRows(); ++i) {
        for (std::ptrdiff_t j = 0; j < matrix_1st.GetColumns(); ++j) {
            matrix_1st.At(i, j) = i * matrix_1st.GetColumns() + j;
        }
    }

    for (std::ptrdiff_t i = 0; i < matrix_2nd.GetRows(); ++i) {
        for (std::ptrdiff_t j = 0; j < matrix_2nd.GetColumns(); ++j) {
            matrix_2nd.At(i, j) = i * matrix_2nd.GetColumns() + j;
        }
    }

    matrix_2nd.PrintMatrix();
    std::cout << std::endl;

    matrix_2nd.PrintMatrix();
    std::cout << std::endl;

    matrix_1st = matrix_2nd;
    matrix_1st.PrintMatrix();
    std::cout << std::endl;

    MatrixA matrix_3d = matrix_1st;
    matrix_3d.PrintMatrix();
    std::cout << std::endl;
    std::cout << matrix_3d.GetRows() << std::endl << matrix_3d.GetColumns() << std::endl << std::endl;
    matrix_3d.Resize(10, 10);
    matrix_3d.PrintMatrix();
    std::cout << std::endl;

    matrix_3d.Resize(19, 18);
    matrix_3d.PrintMatrix();
    std::cout << std::endl;
}
