// Mikhail Rudakov, BS19-02
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Hello! I am SJF scheduler\nPlease enter number of processes:\n");
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
    int currentTime = -1; // Time of completion of last process we executed - we initailly set it to 0
    for (int i = 0; i < n; i++){
        // choose process that we did not complete yet with minimum burst time ,
        // whose arrival time is less or equal than currentTime
        // if there is no such process, choose one that starts later than currentTime
        int leastBurstIndex = -1;
        int leastBurst = -1;
        for (int j = 0; j < n; j++){
            if (currentTime >= a[j] && done[j] == 0 && (leastBurstIndex == -1 || leastBurst > b[j])){
                leastBurst = b[j];
                leastBurstIndex = j;
            }
        }
        if (leastBurst == -1){
            // no pending jobs now
            // choose minimum arrival time to be currentTime from jobs that are not done
            currentTime = -1;
            for (int j = 0; j < n; j++){
                if (done[j] == 0 && (currentTime == -1 || currentTime > a[j]))
                    currentTime = a[j];
                }
            for (int j = 0; j < n; j++){
                if (currentTime >= a[j] && done[j] == 0 && (leastBurstIndex == -1 || leastBurst > b[j])){
                    leastBurst = b[j];
                    leastBurstIndex = j;
                }
        }
        }
        // process number leastTimeIndex is now to execute
        int proc = leastBurstIndex;
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