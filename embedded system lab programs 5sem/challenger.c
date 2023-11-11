#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>  // Added for wait

#define A(x,y) A[(u)*(x)+y]
#define PRECISION 0.0001

int u;

int is_converged(int n, float *A, float *B, float *p) {
    float *sum;
    int i, j;

    sum = (float *)malloc(n * sizeof(float));

    for (i = 0; i < n; ++i)
        sum[i] = 0;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            sum[i] += A(i, j) * p[j];

        sum[i] = fabs(B[i] - sum[i]);
    }

    for (i = 0; i < n; ++i) {
        if (sum[i] > PRECISION)
            return 0;
    }

    return 1;
}

void SOR(int n, float *A, float *B, float *p, float w) {
    float sum;
    int i, j;

    for (i = 0; i < n; ++i) {
        sum = 0;

        for (j = 0; j < i; ++j)
            sum += A(i, j) * p[j];

        for (j = i + 1; j < n; ++j)
            sum += A(i, j) * p[j];

        p[i] += w * (((B[i] - sum) / A(i, i)) - p[i]);
    }
}

int main(int argc, char *argv[]) {
    float *A, *p, *B;
    float w;
    int shmid;
    key_t key;
    int i, j;

    printf("\nPlease input the number of lines:");
    scanf("%d", &u);

    A = (float *)calloc(u * u, sizeof(float));
    B = (float *)malloc(u * sizeof(float));

    printf("Please input the matrix A(%dx%d):\n", u, u);
    for (i = 1; i <= u; ++i) {
        printf("\nPlease input line %d:", i);
        for (j = 1; j <= u; ++j)
            scanf("%f", &A(i - 1, j - 1));
    }

    printf("\nPlease input matrix B(1x%d):", u);
    for (i = 0; i < u; ++i)
        scanf("%f", &B[i]);

    key = 5678;
    if ((shmid = shmget(key, sizeof(float) * u, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((p = (float *)shmat(shmid, NULL, 0)) == (float *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("\nPlease input the start guess(1x%d):", u);
    for (i = 0; i < u; ++i)
        scanf("%f", &p[i]);

    printf("\nPlease input the relax VAR(w):");
    scanf("%f", &w);

    while (!is_converged(u, A, B, p)) {
        if (fork() == 0) {
            if ((shmid = shmget(key, sizeof(float) * u, 0666)) < 0) {
                perror("shmget");
                exit(1);
            }

            if ((p = (float *)shmat(shmid, NULL, 0)) == (float *)-1) {
                perror("shmat");
                exit(1);
            }

            SOR(u, A, B, p, w);
            exit(0);
        }
        wait(NULL);  // Updated wait
    }

    printf("The SOR solution:\n");
    for (i = 0; i < u; ++i)
        printf("x[%d]=%f\n", i + 1, p[i]);

    return 0;
}

