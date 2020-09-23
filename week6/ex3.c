// Mikhail Rudakov, BS19-02
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Hello! I am Round Robin scheduler\nPlease enter number of processes:\n");
    scanf("%d", &n);
    int* a = (int*) malloc(sizeof(int) * n); // arrival time array
    int* b = (int*) malloc(sizeof(int) * n); // burst time array
    int* done = (int*) malloc(sizeof(int) * n); // indicates whether we did the process or not: 0 for no, 1 for yes
    int* remainingTime = (int*) malloc(sizeof(int) * n); // Completion Time for each process
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
        remainingTime[i] = b[i];
    }
    printf("Enter the time quantum:\n");
    int quantum = 0;
    scanf("%d", &quantum);
    for (int i = 0; i < n; i++){
        done[i] = 0;
    }
    int currentTime = 0; // Time of completion of last process we executed - we initailly set it to 0
    int undone = n; // number of processes that are not done yet
    while (undone != 0){
        // sequentially go through each process, giving it a chance to be executed
        int somethingdone = 0;
        for (int i = 0; i < n; i++){
            // check whether we should execute this process or not now:
            // it should be unfinished and already arrived by the currentTime
            if (done[i] == 0 && a[i] <= currentTime){
                somethingdone = 1;
                int proc = i;
                if (remainingTime[proc] <= quantum){
                    currentTime += remainingTime[proc];
                    remainingTime[proc] = 0;
                    done[proc] = 1;
                    undone--;
                    completionTime[proc] = currentTime;
                    turnAroundTime[proc] = completionTime[proc] - a[proc];
                    waitingTime[proc] = turnAroundTime[proc] - b[proc];
                    averageTAT += turnAroundTime[proc];
                    averageWT += waitingTime[proc];       
                } else {
                    remainingTime[proc] -= quantum;
                    currentTime += quantum;
                }           
            }
        }
        if (somethingdone == 0){
            // no pending jobs at currentTime: then we should increase the time
            currentTime++;
        }
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

/*
    Comparison of algorithms section

    Same input for all programs:
    5
    0 4
    1 2
    1 3
    4 4
    3 5

    FIFO algorithm output:
    P##   AT   BT   CT  TAT   WT
    P 0    0    4    4    4    0
    P 1    1    2    6    5    3
    P 2    1    3    9    8    5
    P 3    4    4   18   14   10
    P 4    3    5   14   11    6
    Average WT: 4.80
    Average TAT: 8.40

    SJF algorithm output:
    P##   AT   BT   CT  TAT   WT
    P 0    0    4    4    4    0
    P 1    1    2    6    5    3
    P 2    1    3    9    8    5
    P 3    4    4   13    9    5
    P 4    3    5   18   15   10
    Average WT: 4.60
    Average TAT: 8.20

    Round Robin algorithm with quantum=1 output:
    P##   AT   BT   CT  TAT   WT
    P 0    0    4   14   14   10
    P 1    1    2    6    5    3
    P 2    1    3   11   10    7
    P 3    4    4   17   13    9
    P 4    3    5   18   15   10
    Average WT: 7.80
    Average TAT: 11.40

    Round Robin algorithm with quantum=2 output:
    P##   AT   BT   CT  TAT   WT
    P 0    0    4   12   12    8
    P 1    1    2    4    3    1
    P 2    1    3   13   12    9
    P 3    4    4   15   11    7
    P 4    3    5   18   15   10
    Average WT: 7.00
    Average TAT: 10.60

    Round Robin algorithm with quantum=4 output:
    P##   AT   BT   CT  TAT   WT
    P 0    0    4    4    4    0
    P 1    1    2    6    5    3
    P 2    1    3    9    8    5
    P 3    4    4   13    9    5
    P 4    3    5   18   15   10
    Average WT: 4.60
    Average TAT: 8.20

    Comparison:
    As we see, for this particular case RR(q=4) and SJF performed equally well, while other approaches showed
    higher AWT and ATAT. RR(q=1) has the highest AWT and ATAT, which seems reasonable as tasks are constantly switching.
    Of course, all algorithms have similar last completion time since there is no unnecessary idle time in any of them - they
    differ just in what processes they choose to execute first.
*/