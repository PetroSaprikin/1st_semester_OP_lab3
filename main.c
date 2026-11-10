#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float float_number_check()
{
    float number = 0.f;
    char ch = 0;

    while (1)
    {
        if (scanf("%f%c", &number, &ch) == 2 && ch == '\n')
        {
            return number;
        }
        printf("Invalid input. Enter a real number: ");
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

int integer_number_check()
{
    int number;
    char ch;

    while (1)
    {
        if (scanf("%d%c", &number, &ch) == 2 && ch == '\n')
        {
            return number;
        }
        printf("Invalid input. Enter an integer: ");
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

int has_zero_diagonal(float **A, const int N)
{
    for (int i = 0; i < N; i++)
    {
        if (A[i][i] == 0)
        {
            return 1;
        }
    }
    return 0;
}

int has_diagonal_dominance(float **A, const int N)
{
    for (int i = 0; i < N; i++)
    {
        float sum = 0.f;
        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                sum += fabsf(A[i][j]);
            }
        }
        if (fabsf(A[i][i]) <= sum)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{

    while (1) {
        printf("System of Linear Equations Solver\n\n");

        printf("A11X1 + A12X2 + ... + A1nXn = B1\n"
               "A21X1 + A22X2 + ... + A2nXn = B2\n"
               "................................\n"
               "An1X1 + An2X2 + ... + AnnXn = Bn\n");

        printf("Enter the number of equations: ");
        int N = integer_number_check();

        while (N <= 0)
        {
            printf("Number of equations must be positive: ");
            N = integer_number_check();
        }

        printf("Enter epsilon: ");
        float epsilon = float_number_check();

        while (epsilon <= 0)
        {
            printf("Epsilon must be positive: ");
            epsilon = float_number_check();
        }

        float **A = malloc(N * sizeof(float*));
        for (int i = 0; i < N; i++)
        {
            A[i] = malloc(N * sizeof(float));
        }

        printf("Enter coefficients of equations: \n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                printf("A%d%d: ", i + 1, j + 1);
                A[i][j] = float_number_check();
            }
        }

        if (has_zero_diagonal(A, N))
        {
            printf("Error: zero element on main diagonal.\n");
            for (int i = 0; i < N; i++)
            {
                free(A[i]);
            }

            free(A);
            continue;
        }

        if (!has_diagonal_dominance(A, N))
        {
            printf("Error: no diagonal dominance.\n");
            for (int i = 0; i < N; i++)
            {
                free(A[i]);
            }

            free(A);
            continue;
        }

        float *B = malloc(N * sizeof(float));

        printf("Enter free members of equations: \n");

        for (int i = 0; i < N; i++)
        {
            printf("B%d: ", i + 1);
            B[i] = float_number_check();
        }

        printf("\nYour System of Linear Equations:\n\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                printf("%f*X%d", A[i][j], j + 1);
                if (j < N - 1)
                {
                    printf(" + ");
                }
            }
            printf(" = %f\n", B[i]);
        }

        float *X = malloc(N * sizeof(float));
        float *x_prev = malloc(N * sizeof(float));

        for (int i = 0; i < N; i++)
        {
            x_prev[i] = B[i] / A[i][i];
        }

        while (1)
        {
            char converged = 1;

            for (int i = 0; i < N; i++)
            {
                float sum = 0.f;
                for (int j = 0; j < N; j++)
                {
                    if (i != j)
                    {
                        sum = sum + A[i][j] * x_prev[j];
                    }
                }

                X[i] = (B[i] - sum) / A[i][i];

                if (fabsf(X[i] - x_prev[i]) > epsilon)
                {
                    converged = 0;
                }
            }

            if (converged)
            {
                break;
            }

            for (int i = 0; i < N; i++)
            {
                x_prev[i] = X[i];
            }
        }
        printf("\nSolution:\n");

        for (int i = 0; i < N; i++)
        {
            printf("X%d = %.6f\n", i + 1, X[i]);
        }

        free(X);
        free(x_prev);
        free(B);
        for (int i = 0; i < N; i++)
        {
            free(A[i]);
        }
        free(A);

        char choice;

        printf("\nPress 'y' to solve another system or any other key to exit: ");
        scanf(" %c", &choice);

        if (choice != 'y' && choice != 'Y')
        {
            break;
        }
    }
}
