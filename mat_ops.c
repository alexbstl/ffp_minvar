#include "mat_ops.h"

// Initialize global seed used for xorshift96
static uint32_t seed = 1;

// Convenient ways. Not recommended. 
int easy_rand(int min, int max){
    srand(time(0));
    return rand() % (max + 1 - min) + min;
}

/*  Modified Marsaglia's xorshift random number generator:
    http://www.jstatsoft.org/v08/i14/paper
    Great algorithm. Return pseudo random uint32_t number with longer period of 2^96-1
*/
void s_xorshift96(uint32_t usr_def_seed){
    seed = usr_def_seed;
}


uint32_t xorshift96(int min, int max){
	uint32_t reg_y = seed << 1, reg_z = 521288629;
	uint32_t reg_t = (seed ^ (seed << 10)); 
    seed = reg_y; 
    reg_y = reg_z; 
    reg_z = (reg_z^(reg_z>>26))^(reg_t ^ (reg_t >> 5));
    return reg_z % (max + 1 - min) + min;
}


// Need to pass by reference
void free_ptr(int r, double **p){
    for(int i=0; i<r; i++){
        free(p[i]);
    }
    free(p);
}


// Create Matrix of Zeros
double** mat_zeros(int row, int col){
    double **mat = (double **)malloc(row * sizeof(double*));
    for (int i=0; i<row; i++) 
         mat[i] = (double *)malloc(col * sizeof(double)); 
    return mat;
}


// Create Matrix of Ones
double** mat_ones(int row, int col){
    double **mat = (double **)malloc(row * sizeof(double*));
    for (int i=0; i<row; i++) 
         mat[i] = (double *)malloc(col * sizeof(double)); 
    for (int i=0; i<row; i++) 
        for(int j=0; j<col;j++)
            mat[i][j] = 1.0;
    return mat;
}


// initialize with random value under max
double** mat_rand(int row, int col, double min, double max){
    double **mat = (double **)malloc(row * sizeof(double*));
    for (int i=0; i<row; i++) 
         mat[i] = (double *)malloc(col * sizeof(double)); 
    for (int i=0; i<row; i++) 
        for(int j=0; j<col;j++)
            mat[i][j] = min + (rand() /(RAND_MAX / (max - min)));
    return mat;
}


// Matrix Multiplication
double** mat_mul(int m, int p, int n, double** mat_l, double** mat_r)
{
    double** product = mat_zeros(m, n);
    // Require: mat_l is m x p and mat_r is p x n.
    int i, j, k;
    // matrix multiplication
    for (i = 0; i < m; i++ )
        for (j = 0; j < n; j++ )
            for (k = 0; k < p; k++ )
                product[i][j] += mat_l[i][k] * mat_r[k][j];
    return product;
}


// Matrix Transpose
double** mat_trans(int row, int col, double** mat_old)
{
    double** mat_new = mat_zeros(col, row);
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            mat_new[j][i] = mat_old[i][j];
        }
    }
    return mat_new;
}


// Construct diagonal matrix from vector
double** mat_diag(int col, double** arr)
{
    double** mat = mat_zeros(col, col);
    for(int i=0; i<col; i++){           
        mat[i][i] = arr[0][i];
    }
    return mat;
}


double** mat_add(int m, int n, double** mat1, double** mat2)
{
    double** result = mat_zeros(m, n);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    return result;
}


void print_mat(int r, int c, double** mat){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%0.32f  ",  mat[i][j]);
        }
        printf("\n");
    }
}

// both dimension of **new should be greater than **old
void copy_mat(int r, int c, double** new, double** old){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            new[i][j] = old[i][j];
        }
    }
}


bool check_nonzero_row(int current, int dim, double** mat){
    for(int i=current+1; i<dim; i++){
        for(int j=0; j<dim; j++){
            if(mat[i][j] !=0){
                return true;
            }
        }
    }
    return false;
}


// 1. Convert matrix to REF
// assumption 1: mat != 0
// assumption 2: higher row's pivot position is always to the left of lower row's pivot position
double** REF(int dim, double** mat){
    // construct augmented matrix  
    // by concatenanting identity matrix to the right of mat
    //  i.e.: {7 9 3 1 0 0}
    //        {4 6 8 0 1 0}
    //        {5 2 5 0 0 1}
    double** new = mat_zeros(dim,2*dim);
    copy_mat(dim, dim, new, mat);

    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            if(i==j){
                new[i][j+dim] = 1;
            }
            else if(i!=j){
                new[i][j+dim] = 0;
            }
        }
    }

    
    // Step 2. Determine the leftmost non-zero column
    for(int i=0; i<dim; i++){
        // find the leftmost non-zero column
        int leftmost_col_pos=dim, leftmost_row_pos=dim, r, c;
        for(r=i; r<dim; r++){
            for(c=0; c<dim; c++){
                // the "<" here guarantee we always find the topmost row of leftmost column
                if(new[r][c]!=0 && c<leftmost_col_pos){
                    leftmost_col_pos = c;
                    leftmost_row_pos = r;
                }
            }
        }

        
        // Step 3. Use elementary row operations to put a 1 in the topmost position
        // (we call this position pivot position) of this column.

        // 3.1 First you need to swap.
        // Check if the row of where the leftmost col at is the same as "i".
        // If yes, skip swapping to save computation cost. 
        // Only swap when it's not the current row
        if(leftmost_row_pos != i){
			for (int k = 0; k < 2*dim; k++){
                double temp = new[i][k];
                new[i][k] = new[leftmost_row_pos][k];
                new[leftmost_row_pos][k] = temp;
            } 
        }
        
        // Normalize the i row s.t. the pivot position is 1.
        double norm = new[i][leftmost_col_pos];
        for (int k = 0; k < 2*dim; k++){
            new[i][k] = new[i][k] / norm;                
        }
        
        // Put zeros (strictly) below the pivot position.
        for (int j = i+1; j < dim; j++){ 	
			// Excluding all i == j 
			if (new[j][leftmost_col_pos] != 0) { 
				
				// put zeros below the pivot position: 
                // R_below = R_below - 
				// echelon form(diagonal matrix) 
				double ratio = new[j][leftmost_col_pos] / new[i][leftmost_col_pos]; 

				for (int k = 0; k <= 2*dim; k++){			 
					new[j][k] = new[j][k] - (new[i][k]) * ratio;	
                }			 
			} 
		} 

        // If there are no more non-zero rows (strictly) below the pivot position,
        // the matrix is already in REF. Also for saving computational cost.
        if(check_nonzero_row(i, dim, new) == false){
            break;
        }
    }

    return new;

}


bool check_pivot_col(int pivot_col, int dim, double** mat){
    for(int i=0; i<dim; i++){
        for(int j=0; j<pivot_col; j++){
            if(mat[i][j] == 1){
                return true;
            }
        }
    }
    return false;
}



// initial value: row_bound = col_bound = dim - 1
double erase_zeros_above(int row_bound, int col_bound, int dim, double** mat){
    // 1. Determine the right most column containing a leading one
    int rightmost_col_pos=-1, rightmost_row_pos=-1;
    for(int i=row_bound; i>=0; i--){
        for(int j=0; j<=col_bound; j++){
            if(mat[i][j]!=0){
                rightmost_col_pos = j; 
                rightmost_row_pos = i;
                goto DONE;
            }
        }
    }

    DONE:
    // 2. Erase all the non-zero entries above 
    // the leading one in the pivot column.
    for(int i=rightmost_row_pos-1; i>=0; i--){
        double ratio = mat[i][rightmost_col_pos] / mat[rightmost_row_pos][rightmost_col_pos];
        for(int j=rightmost_col_pos; j<2*dim; j++){
            mat[i][j] = mat[i][j] - ratio * mat[rightmost_row_pos][j];
        }
    }

    return rightmost_col_pos;
}


// Convert REF to RREF
// pre-condition: mat is in REF
// 1. rightmost pivot already at the lowest row. 
// 2. The row above current row has a pivot column 
//    to the left of current row's pivot column
//    (bc of the no zero below pivot position requirement from previous REF)
double** RREF(int dim, double** mat){
    // 1. Determine the right most column containing a leading one

    int row_bound = dim-1, col_bound = dim-1;
    while(row_bound >= 0){
        // do 9 to 11
        double pivot_col = erase_zeros_above(row_bound, col_bound, dim, mat);
        // If there are no more columns containing leading ones to the left of
        // the pivot column, the matrix is in RREF. Done. 
        /*if(check_pivot_col(pivot_col, dim, mat) == false){
            break;
        }*/
        row_bound--;
        col_bound--;
    }
    
    double** new = mat_zeros(dim, dim);
    for(int i=0; i<dim; i++){
        for(int j=dim; j<2*dim; j++){
            new[i][j-dim] = mat[i][j];
        }
    }

    return new;
}


double** inv(int dim, double** mat){
    double** temp = REF(dim, mat);
    double** inv = RREF(dim, temp);
    free_ptr(dim, temp);
    return inv;
}