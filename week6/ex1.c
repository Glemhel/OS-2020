// Mikhail Rudakov, BS19-02
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Hello! I am FIFO scheduler\nPlease enter number of processes:\n");
    scanf("%d", &n);
    int* a = (int*) malloc(sizeof(int) * n); // arrival time array
    int* b = (int*) malloc(sizeof(int) * n); // burst time array
    int* done = (int*) malloc(sizeof(int) * n); // indicates whether we did the process or not: 0 for no, 1 for yes
    int* completionTime = (int*) malloc(sizeof(int) * n); // Completion Time for each process
    int* turnAroundTime = (int*) malloc(sizeof(int) * n); // Turn Around Time for each process
    int* waitingTime = (int*) malloc(sizeof(int) * n); // Waiting Time for each process
    float averageTAT = 0; // average Turn Around Time 
    float averageWT = 0; // average Waiting Time
    for (int i = 0;i < n; i++){
        printf("Enter arrival time of %d-th process: \n", i + 1);
        scanf("%d", &a[i]);
        printf("Enter burst time of %d-th process: \n", i + 1);
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < n; i++){
        done[i] = 0;
    }
    int currentTime = 0; // Time of completion of last process we executed
    for (int i = 0; i < n; i++){
        // choose process that we did not complete yet with minimum arrival time
        int leastTimeIndex = -1;
        int leastTime = -1;
        for (int j = 0; j < n; j++){
            if (done[j] == 0 && (leastTimeIndex == -1 || leastTime > a[j])){
                leastTime = a[j];
                leastTimeIndex = j;
            }
        }
        // process number leastTimeIndex is now to execute
        int proc = leastTimeIndex;
        done[proc] = 1;
        if (currentTime < a[proc]) // if arrival time is later that we did, we delay it
            currentTime = a[proc];
        waitingTime[proc] = currentTime - a[proc];
        completionTime[proc] = currentTime + b[proc];
        turnAroundTime[proc] = completionTime[proc] - a[proc];
        averageTAT += turnAroundTime[proc];
        averageWT += waitingTime[proc];
        currentTime = completionTime[proc];
    }
    printf("Here is schedule I came up with!\n");
    printf("P##   AT   BT   CT  TAT   WT\n");
    for (int i = 0; i < n; i++){
      printf("P%2d%5d%5d%5d%5d%5d\n", i, a[i], b[i], completionTime[i], turnAroundTime[i], waitingTime[i]);
    }
    averageWT /= n;
    averageTAT /= n;
    printf("Average WT: %.2f\n", averageWT);
    printf("Average TAT: %.2f\n", averageTAT);
    return 0;
}