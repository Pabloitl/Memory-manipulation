#include <stdio.h>
#include <stdlib.h>

/* Declaración de métodos*/
void enterData();
int* initializeMatrix(int Mrows, int Mcolumns);
void enterMatrix(int *M, int Mrows, int Mcolumns);
void multiplyMatrices();
void displayResult();
void display(int *M, int Mrows, int Mcolumns);
void cleanMemory();

/*Declaración de variables*/
int *A, *B, *C;
int Arows, Acolumns, Brows, Bcolumns;

int main() {
    enterData(); /* Definición de las variables */
    multiplyMatrices(); /* Multiplicación */
    displayResult(); /* Resultados */
    cleanMemory(); /* Limpieza de memoria */

    return 0;
}

/* Entrada de datos por teclado */
void enterData() {
	/* Se restringe la dimensión de las matrices para que las filas de A
	   tengan la misma dimensión que las columnas de B*/
	do {
		printf("Ingrese filas y columnas para la matriz A: ");
		scanf("%d %d", &Arows, &Acolumns);
		printf("Ingrese filas y columnas para la matriz B: ");
		scanf("%d %d", &Brows, &Bcolumns);
	} while (Acolumns != Brows); 	

    	/* Se definen las dimensiones de las matrices A, B y la Resultante C */
    	 A = initializeMatrix(Arows, Acolumns);
   	 B = initializeMatrix(Brows, Bcolumns);
   	 C = initializeMatrix(Arows, Bcolumns);

	/* Se poblan las matrices con enterMatrix */
	printf("\nIngrese los elementos de A\n");
        enterMatrix(A, Arows, Acolumns);

	printf("\nIngrese los elementos de B\n");
        enterMatrix(B, Brows, Bcolumns);
}

/* Llenado de los campos de las matrices */
void enterMatrix(int *M, int Mrows, int Mcolumns) {
	/* Se llena la matriz M de arriba a abajo y de izquierda a derecha */
	for(int row = 0; row < Mrows; ++row)
		for(int column = 0; column < Mcolumns; ++column) {
			printf("Ingrese elemento [%d,%d]: ", row + 1, column + 1);
                scanf("%d", M + row * Mcolumns + column);
		}
}

/* Método que regresa una matriz con Mrows filas y Mcolumns columnas */
int* initializeMatrix(int Mrows, int Mcolumns) {
    /* Aloja la matriz en la memoria */
    return calloc(Mrows * Mcolumns, sizeof(int));
}

/* Método que realiza la multiplicación */
void multiplyMatrices()
{
	/* A11*B11 + A21*B12 + A31* B31... */ 
	for(int row = 0; row < Arows; ++row) {
		for(int column = 0; column < Bcolumns; ++column) {
			for(int k=0; k < Acolumns; ++k) {
                *(C + row * Bcolumns + column) += (
                    *(A + row * Acolumns + k) * *(B + k * Bcolumns + column)
                );
			}
		}
	}
}

/* Método para mostrar resultados */
void displayResult() {
    printf("\nMatriz A\n");
    display(A, Arows, Acolumns);
    printf("Matriz B\n");
    display(B, Brows, Bcolumns);
    printf("Matriz C (Resultado)\n");
    display(C, Arows, Bcolumns);
}

/* Método que da formato a los datos contenidos en una matriz
   para mostrarla de forma ordenada */
void display(int *M, int Mrows, int Mcolumns)
{
	for(int row = 0; row < Mrows; ++row) {
        printf("\t");
		for(int column = 0; column < Mcolumns; ++column)
			printf("%2d ", *(M + row * Mcolumns + column));
        printf("\n");
	}
}

/* Método que libera la memoria */
void cleanMemory() {
    /* Desaloja la memoria ocupada cuando se llamó calloc */
    free(A); 
    free(B);
    free(C);
}
