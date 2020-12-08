#include "mat_ops.h"

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
        if(check_pivot_col(pivot_col, dim, mat) == false){
            break;
        }
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



int main(){
    clock_t begin = clock();
    double time_used;

    //---------------- Dim of 2 -------------------//
    double** mat2 = mat_zeros(2, 2);
    /*
    mat2[0][0] = 2;
    mat2[0][1] = 4;
    mat2[1][0] = 0;
    mat2[1][1] = 1;*/
    mat2[0][0] = 9;
    mat2[0][1] = 0;
    mat2[1][0] = 0;
    mat2[1][1] = 4;


    int dim2 = 2;
    double** temp2 = REF(dim2, mat2);
    double** new2 = RREF(dim2, temp2);

    print_mat(dim2, dim2, mat2);
    print_mat(dim2, dim2, new2);

    free_ptr(dim2, mat2);
    free_ptr(dim2, temp2);
    free_ptr(dim2, new2);
    

    //---------------- Dim of 3 -------------------//
    double** mat3 = mat_zeros(3, 3);
    /*
    mat3[0][0] = 0;
    mat3[0][1] = 0;
    mat3[0][2] = 1;
    mat3[1][0] = 1;
    mat3[1][1] = 0;
    mat3[1][2] = 2;
    mat3[2][0] = 0;
    mat3[2][1] = 3;
    mat3[2][2] = 0;*/
    
    /*
    mat3[0][0] = 0;
    mat3[0][1] = -3;
    mat3[0][2] = -2;
    mat3[1][0] = 1;
    mat3[1][1] = -4;
    mat3[1][2] = -2;
    mat3[2][0] = -3;
    mat3[2][1] = 4;
    mat3[2][2] = 1;*/

    mat3[0][0] = 2;
    mat3[0][1] = 0;
    mat3[0][2] = 0;
    mat3[1][0] = 0;
    mat3[1][1] = 3;
    mat3[1][2] = 0;
    mat3[2][0] = 0;
    mat3[2][1] = 0;
    mat3[2][2] = 5;

    int dim3 = 3;
    double** temp3 = REF(dim3, mat3);
    double** new3 = RREF(dim3, temp3);

    // print test: dim of 3
    print_mat(dim3, dim3, mat3);
    print_mat(dim3, dim3, new3);
    // free pointers: dim of 2
    free_ptr(dim3, mat3);
    free_ptr(dim3, temp3);
    free_ptr(dim3, new3);


    time_used = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("time used: %f\n", time_used);
}