#include "matrix_header.h"

/**
		determinant						calculates the determinant of EDGE x EDGE matrix
		@param[out]			matrix		pointer to the array of numbers (input matrix)
		@param				EDGE		size of matrix

		@par							Function uses Gauss method of calculating determinant. It build the lower triangle of zeros, turning the matrix like
										
										a1 b1 c1 d1				e1 f1 g1 h1
										a2 b2 c2 d2    into		0  f2 g2 h2
										a3 b3 c3 d3				0  0  g3 h3
										a4 b4 c4 d4				0  0  0  h4

										The determinant of the second matrix is e1 * f2 * g3 * h4

		@par							There's a main cycle in the body. It passes all columns.
										- If matrix[i][i] element is zero, it searches for non-zero elements below and increases i-string by found string.
										If there's no such strings, that means that one of factors of main diagonal is zero => return 0
										- The matrix[i][i] is non-zero, we're decreasing lower strings to make the lower column made of zeros
										- Calculating the determinant and return it
		
		@return							Determinant of matrix
**/
double determinant(double** matrix, const int EDGE)
{
	ASSERT(matrix);

	
	if (!(EDGE)) return 0.0;

	CREATE_MATRIX(copy_matrix, EDGE);
	ASSERT(copy_matrix);
	COPY_MATRIX(copy_matrix, matrix, EDGE);
    
    for (int i = 0; i < EDGE; ++i)
    {
        ASSERT(i >= 0); ASSERT(i < EDGE);
		if (copy_matrix[i][i] == 0)
            {
                for (int j = i+1; j < EDGE; ++j)
				{
					ASSERT(j >= 0); ASSERT( j < EDGE);
					
					if (copy_matrix[j][i] != 0)
                    {
                        for (int k = 0; k < EDGE; ++k) copy_matrix[i][k] += copy_matrix[j][k];
						DEBUG_OUT PRINT_MATRIX(copy_matrix, EDGE);
						break;
                    }
					return 0.0;
				}
                
				DEBUG_OUT PRINT_MATRIX(copy_matrix, EDGE);
            }
		
		double local_factor = 0;
        for (int j = i + 1; j < EDGE; ++j)
        {
            ASSERT(i >= 0); ASSERT(i < EDGE); ASSERT(j >= 0); ASSERT( j < EDGE);    
			local_factor = copy_matrix[j][i] / copy_matrix[i][i];
            
			for (int k = 0; k < EDGE; ++k) copy_matrix[j][k] -= copy_matrix[i][k] * local_factor;
            DEBUG_OUT PRINT_MATRIX(copy_matrix, EDGE);
        }
    }
    double determinant = 1;
    DEBUG_OUT PRINT_MATRIX(copy_matrix, EDGE);
    for (int i = 0; i < EDGE; ++i) determinant *= copy_matrix[i][i];
    free(copy_matrix);
	if DBL_IS_ZERO(determinant) determinant = 0.0;
    return determinant;
}