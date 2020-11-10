#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define USER_INPUT false

int main(){
    int M = 2; // number of resource classes
    int N = 3; // number of processes
    FILE* input = fopen("input.txt","r");
    FILE* output = fopen("output.txt", "w");
    // if needed, M and N are also provided in input.txt
    if (USER_INPUT){
        fscanf(input, "%d %d", &M, &N);
    }
    // allocate and input everything
    int* E = (int*)malloc(sizeof(int) * M); // existing resource vector
    for (int i = 0; i < M; i++)
        fscanf(input, "%d", &E[i]);
    int* A = (int*)malloc(sizeof(int) * M); // available  resource vector
    for (int i = 0; i < M; i++)
        fscanf(input, "%d", &A[i]);
    int** C = (int**) malloc(sizeof(int*) * N); // current allocation matrix
    for (int i = 0; i < N; i++){
        C[i] = (int*) malloc(sizeof(int) * M);
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            fscanf(input, "%d", &C[i][j]);
        }
    }
    int** R = (int**) malloc(sizeof(int*) * N); // request matrix
    for (int i = 0; i < N; i++){
        R[i] = (int*) malloc(sizeof(int) * M);
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            fscanf(input, "%d", &R[i][j]);
        }
    }
    bool* marked = (bool*) malloc(sizeof(bool) * N); // marking for processes, false by default
    for (int i = 0; i < N; i++){
        marked[i] = false;
    }
    // now apply algorithm
    // N iterations for trying to run some process till completion is enough
    int possible_to_run = 0;
    for (int i = 0; i < N; i++){
        // find unmarked process which requests <= system currently can provide
        int process_to_run = -1;
        for (int j = 0; j < N; j++){
            if (!marked[j]){
                bool ok = true; // r[j][k] <= a[k] for all k
                for (int k = 0; k < M; k++)
                    ok &= R[j][k] <= A[k];
                if (ok){
                    // found feasible process, break
                    process_to_run = j;
                    break;
                }
            }
        }
        if (process_to_run == -1){
            // no process can run now, deadlock
            break;
        }
        marked[process_to_run] = true;
        possible_to_run++;
        for (int j = 0; j < M; j++){
            A[j] += C[process_to_run][j]; // release processes's resources
        }
    }
    if (possible_to_run == N){
        fprintf(output, "Execution scenario without deadlocks exist.\n");
    } else {
        fprintf(output, "Deadlock with %d processes involved can occur.\n", N - possible_to_run);
    }
    return 0;
}
