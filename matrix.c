#include "matrix.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Include SSE intrinsics
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <immintrin.h>
#include <x86intrin.h>
#endif

/* Below are some intel intrinsics that might be useful
 * void _mm256_storeu_pd (double * mem_addr, __m256d a)
 * __m256d _mm256_set1_pd (double a)
 * __m256d _mm256_set_pd (double e3, double e2, double e1, double e0)
 * __m256d _mm256_loadu_pd (double const * mem_addr)
 * __m256d _mm256_add_pd (__m256d a, __m256d b)
 * __m256d _mm256_sub_pd (__m256d a, __m256d b)
 * __m256d _mm256_fmadd_pd (__m256d a, __m256d b, __m256d c)
 * __m256d _mm256_mul_pd (__m256d a, __m256d b)
 * __m256d _mm256_cmp_pd (__m256d a, __m256d b, const int imm8)
 * __m256d _mm256_and_pd (__m256d a, __m256d b)
 * __m256d _mm256_max_pd (__m256d a, __m256d b)
*/

/* Generates a random double between low and high */
double rand_double(double low, double high) {
    double range = (high - low);
    double div = RAND_MAX / range;
    return low + (rand() / div);
}

/* Generates a random matrix */
void rand_matrix(matrix *result, unsigned int seed, double low, double high) {
    srand(seed);
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {
            set(result, i, j, rand_double(low, high));
        }
    }
}

/*
 * Allocates space for a matrix struct pointed to by the double pointer mat with
 * `rows` rows and `cols` columns. You should also allocate memory for the data array
 * and initialize all entries to be zeros. `parent` should be set to NULL to indicate that
 * this matrix is not a slice. You should also set `ref_cnt` to 1.
 * You should return -1 if either `rows` or `cols` or both have invalid values, or if any
 * call to allocate memory in this function fails. Return 0 upon success.
 */
int allocate_matrix(matrix **mat, int rows, int cols) {
    /* TODO: YOUR CODE HERE */
    // Check if we have valid "rows" and "cols".
    if ((rows <= 0) || (cols <= 0)) {
        return -1;
    } 

    // Dynamically allocate space for the matrix struct.
    *mat = (matrix*) malloc(sizeof(matrix));
    
    // Check if we have successufully allocated memory for the struct. 
    if ((*mat) == NULL) {
        printf("Memory not allocated successfully for the matrix struct.\n");
        return -2;
    }

    // Dynamically allocate space for the data attribute. 
    (*mat)->data = (double*) calloc(rows * cols, sizeof(double));

    // Check if we have successufully allocated memory for the data attribute of *mat. 
    if ((*mat) == NULL) {
        printf("Memory not allocated successfully for the data attribute.\n");
        return -2;
    }

    // Initializing all other attributes of the matrix pointed by *mat.
    (*mat)->cols = cols;
    (*mat)->rows = rows;
    (*mat)->ref_cnt = 1;
    (*mat)->parent = NULL;

    return 0;
}

/*
 * Allocates space for a matrix struct pointed to by `mat` with `rows` rows and `cols` columns.
 * Its data should point to the `offset`th entry of `from`'s data (you do not need to allocate memory)
 * for the data field. `parent` should be set to `from` to indicate this matrix is a slice of `from`.
 * You should return -1 if either `rows` or `cols` or both are non-positive or if any
 * call to allocate memory in this function fails. Return 0 upon success.
 */
int allocate_matrix_ref(matrix **mat, matrix *from, int offset, int rows, int cols) {
    /* TODO: YOUR CODE HERE */
    // Check if we have valid "rows" and "cols".
    if ((rows <= 0) || (cols <= 0)) {
        return -1;
    } 
	
    *mat = (matrix*) malloc(sizeof(matrix));
    	
    // Assign mat's data to the `offset`th entry of `from`'s data. 
    (*mat)->data = from->data + offset;

    // Set the 'parent' attribute of mat to 'from'.
    (*mat)->parent = from; 
    // Add one to it's parent's ref_cnt. Since parent has one more child added. 
    (*mat)->parent->ref_cnt += 1;

    // Initializing the remaining attributes of the matrix struct. 
    (*mat)->cols = cols;
    (*mat)->rows = rows;
    (*mat)->ref_cnt = 2;

    return 0;   
}

/*
 * You need to make sure that you only free `mat->data` if `mat` is not a slice and has no existing slices,
 * or if `mat` is the last existing slice of its parent matrix and its parent matrix has no other references
 * (including itself). You cannot assume that mat is not NULL.
 */
void deallocate_matrix(matrix *mat) {
    /* TODO: YOUR CODE HERE */
    // Check if mat is NULL.
    if (mat ==  NULL) {
        printf("Cannot deallocate NULL.\n");
    }

    if ((mat->parent == NULL) && (mat->ref_cnt == 1)) {
        free(mat->data);
        free(mat);
    } else if ((mat->parent != NULL) && (mat->parent->ref_cnt == 1)) {
        free(mat->parent->data);
        free(mat->parent);
        free(mat);
    } else if ((mat->parent == NULL) && (mat->ref_cnt > 1)) {
        mat->ref_cnt -= 1;
    } else {
        mat->parent->ref_cnt -= 1;
        free(mat);
    } 
}

/*
 * Returns the double value of the matrix at the given row and column.
 * You may assume `row` and `col` are valid.
 */
double get(matrix *mat, int row, int col) {
    /* TODO: YOUR CODE HERE */
    return mat->data[row * mat->cols + col];
}

/*
 * Sets the value at the given row and column to val. You may assume `row` and
 * `col` are valid
 */
void set(matrix *mat, int row, int col, double val) {
    /* TODO: YOUR CODE HERE */
    mat->data[row * mat->cols + col] = val;
}

/*
 * Sets all entries in mat to val
 */
void fill_matrix(matrix *mat, double val) {
    /* TODO: YOUR CODE HERE */
    for (int i = 0; i < (mat->rows) * (mat->cols); i++) {
        mat->data[i] = val;
    }
}

/*
 * Store the result of adding mat1 and mat2 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int add_matrix(matrix *result, matrix *mat1, matrix *mat2) {
    /* TODO: YOUR CODE HERE */
    // Nonvalid input checking.
    if (result == NULL || mat1 == NULL || mat2 == NULL) {
        return -1;
    } 
    if ((mat1->rows * mat1->cols) != (mat2->rows * mat2->cols)) {
        return -1;
    }
    if ((result->cols * result->rows) !=  (mat1->rows * mat1->cols)) {
        return -1;
    }

    for (int i = 0; i < result->rows * result->cols; i++) {
        result->data[i] = mat1->data[i] + mat2->data[i];
    }

    return 0;
}

/*
 * Store the result of subtracting mat2 from mat1 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int sub_matrix(matrix *result, matrix *mat1, matrix *mat2) {
    /* TODO: YOUR CODE HERE */
   
    if (result == NULL || mat1 == NULL || mat2 == NULL) {
        return -1;
    } 
    if ((mat1->rows * mat1->cols) != (mat2->rows * mat2->cols)) {
        return -1;
    }
    if ((result->cols * result->rows) !=  (mat1->rows * mat1->cols)) {
        return -1;
    }

    for (int i = 0; i < result->rows * result->cols; i++) {
        result->data[i] = mat1->data[i] - mat2->data[i];
    }

    return 0;    

}

/*
 * Store the result of multiplying mat1 and mat2 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 * Remember that matrix multiplication is not the same as multiplying individual elements.
 */
int mul_matrix(matrix *result, matrix *mat1, matrix *mat2) {
    /* TODO: YOUR CODE HERE */
    // Invalid result checking.
    if (result == NULL || mat1 == NULL || mat2 == NULL) {
        return -1;
    }    
    if (mat1->cols != mat2->rows) {
        return -1;
    } 
    if (result->rows != mat1->rows || result->cols != mat2->cols) {
        return -1;
    }

    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {
            double result_i_j = 0;
            int num_col = result->cols;
            for (int k = 0; k < mat1->cols; k++) {
                result_i_j += mat1->data[i * num_col + k] * mat2->data[k * num_col + j];
            }
            result->data[i * result->rows + j] = result_i_j; 
        }
    }
    return 0;
}

/*
 * Store the result of raising mat to the (pow)th power to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 * Remember that pow is defined with matrix multiplication, not element-wise multiplication.
 */
int pow_matrix(matrix *result, matrix *mat, int pow) {
    /* TODO: YOUR CODE HERE */
    // Check invalid input. 
    if (result == NULL || mat == NULL) {
        return -1;
    } 
    if (mat->cols != mat->rows) {
        return -1;
    }
    if (result->cols != result->rows) {
        return -1;
    }
    if (pow < 0) {
        return -1;
    }

    if (pow == 0) {
        for (int i = 0; i < result->rows; i++) {
            for (int j = i * result->cols; j < (i + 1) * result->cols; j++) {
                if (i == (j - i * result->cols)) {
                    result->data[j] = 1;
                } else {
                    result->data[j] = 0;
                }
            }
        }
    } else if (pow == 1) {
        for (int i = 0; i < result->rows; i++) {
            for (int j = i * result->cols; j < (i + 1) * result->cols; j++) {
                result->data[j] = mat->data[j];
            }
        }       
    } else {
        matrix* middle_result = (matrix*) malloc(sizeof(matrix));
        middle_result->data = (double*) calloc(result->cols * result->rows, sizeof(double));
	    middle_result->cols = result->cols;
	    middle_result->rows = result->rows;
        mul_matrix(result, mat, mat);
        for (int i = 2; i < pow; i++) {
            mul_matrix(middle_result, result, mat);
            for (int j = 0; j < result->cols * result->rows; j++) {
                result->data[j] = middle_result->data[j];
            }
        }
        free(middle_result->data);
	    free(middle_result);
    }
    return 0;
}

/*
 * Store the result of element-wise negating mat's entries to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int neg_matrix(matrix *result, matrix *mat) {
    /* TODO: YOUR CODE HERE */
    if (result == NULL || mat == NULL) {
        return -1;
    } 
    if ((result->cols * result->rows) != (mat->cols * mat->rows)) {
        return -1;
    }
    for (int i = 0; i < result->cols * result->rows; i++) {
        result->data[i] = (-1) * mat->data[i];
    }

    return 0;
}

/*
 * Store the result of taking the absolute value element-wise to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int abs_matrix(matrix *result, matrix *mat) {
    /* TODO: YOUR CODE HERE */
    if (result == NULL || mat == NULL) {
        return -1;
    } 
    if ((result->cols * result->rows) != (mat->cols * mat->rows)) {
        return -1;
    }
    for (int i = 0; i < result->cols * result->rows; i++) {
        if (mat->data[i] < 0) {
            result->data[i] = (-1) * mat->data[i];
        } else {
            result->data[i] = mat->data[i];
        }  
    }
    return 0;    

}

