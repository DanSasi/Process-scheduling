
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning (disable: 4996)

typedef struct Processes {

    int arrival_time;
    int burst_time;
    int wait_time;
    int finish_time;
    int priority;
    int tat;

}process;

void sortByArrival(process p[], int num)
{
    process temp;
    int i, j;
    for (i = 0; i < num; i++)
    {
        for (j = i + 1; j < num; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

float FCFS(process p[], int num) {

    int i;
    p[0].finish_time = p[0].arrival_time + p[0].burst_time;
    int TAT = p[0].burst_time;
    for (i = 1; i < num; i++) {

        if (p[i].burst_time == 0) {}
        if (p[i - 1].finish_time > p[i].arrival_time) {
            if (p[i - 1].finish_time != 0) {
                p[i].finish_time = p[i - 1].finish_time + p[i].burst_time;
                TAT += p[i].finish_time - p[i].arrival_time;
            }
            else
            {
                p[i].finish_time = p[i].arrival_time + p[i].burst_time;
                TAT += p[i].burst_time;
            }
        }
        else
        {
            p[i].finish_time = p[i].arrival_time + p[i].burst_time;
            TAT += p[i].burst_time;
        }
    }
    float result = (float)TAT / num;
    return result;
}

float LCFS_NP(process p[], int num) {
    int ar[10], bt[10];
    int i;
    for (i = 0; i < num; i++)
    {
        ar[i] = p[i].arrival_time;
        bt[i] = p[i].burst_time;
    }
    int finishtime = ar[0] + bt[0]; //keeps when we finished a process
    int tat = finishtime - ar[0]; // first tat
    for (i = num - 1; i != 0; i--)
    {
        if (bt[i] == 0) {
            finishtime = ar[i];
        }
        if (finishtime > ar[i]) {
            if (finishtime != 0) {
                finishtime = finishtime + bt[i];
                tat += finishtime - ar[i];
            }
            else
            {
                finishtime = ar[i] + bt[i];
                tat += bt[i];
            }
        }
        else
        {
            finishtime = ar[i] + bt[i];
            tat += bt[i];
        }
    }
    float sul = (float)tat / num;
    return sul;
}

float RnR(process p[], int num) {

    int i = 0, j = 0, t = 0, stop = num, aT[8], bT[8], TQ = 2, totexe = 0, totwt = 0, flag = 0;
    for (j = 0; j < num; j++) {

        aT[j] = p[j].arrival_time;
        bT[j] = p[j].burst_time;
    }
    for (j = 0; j < num; j++) {
        if (aT[j] + bT[j] >= aT[j + 1] && aT[j] + bT[j] > 0)
        {
            t = j;
            break;
        }
        if (aT[j] + bT[j] < aT[j + 1])
        {
            totwt += bT[j];
            stop--;
            if ((j + 1) == num - 1) {
                totwt += bT[j + 1];
                stop = 0;
                break;
            }
        }
    }
    while (stop != 0) {

        for (i = t; i < num; i++) {


            if (bT[i] > 0) {

                if (bT[i] < TQ && bT[i] > 0) {

                    totexe += bT[i];
                    bT[i] --;
                    flag = 1;
                }
                else {
                    bT[i] -= TQ;
                    totexe += TQ;
                    if (bT[i] == 0) {
                        flag = 1;
                    }
                }
            }
            if (flag == 1 && bT[i] == 0)
            {
                totwt += totexe - aT[i];
                flag = 0;
                stop--;
            }
        }
    }

    float result = (float)(totwt / num);

    return result;
}

float SJF(process p[], int num) {
    int at[10], bt[10], temp[10], Temp[8];
    int i, smallest, count = 0, time, limit = num;
    double wait_time = 0, turnaround_time = 0, end;
    float average_waiting_time, average_turnaround_time;

    for (i = 0; i < limit; i++)
    {
        at[i] = p[i].arrival_time;
        bt[i] = p[i].burst_time;
        temp[i] = bt[i];
    }
    if (bt[0] == 0 && bt[1] == 0) {
        at[0] = at[2];
        bt[0] = bt[2];
        at[1] = at[3];
        bt[1] = bt[3];
        limit = (num - 2);
    }
    bt[9] = 9999;
    for (time = 0; count != limit; time++)
    {

        smallest = 9;
        for (i = 0; i < limit; i++)
        {
            if (at[i] <= time && bt[i] < bt[smallest] && bt[i] > 0)
            {
                smallest = i;
            }
        }
        bt[smallest]--;
        if (bt[smallest] == 0)
        {
            count++;
            end = time + 1;
            wait_time = wait_time + end - at[smallest] - temp[smallest];
            turnaround_time = turnaround_time + end - at[smallest];
        }
    }
    average_waiting_time = wait_time / num;
    average_turnaround_time = turnaround_time / num;

    return average_turnaround_time;
}




float LCFS_P(process p[], int num) {

    int ar[10], bt[10], i;
    for (i = 0; i < num; i++) {
        ar[i] = p[i].arrival_time;
        bt[i] = p[i].burst_time;
    }
    float Wt = bt[num - 1];
    float tot_time = Wt;
    float temp = 0;
    if (num == 2) {
        if (ar[0] + bt[0] < ar[1]) {
            tot_time += bt[0];
        }
        else {
            tot_time += bt[0] + bt[1] + bt[1];
        }

    }
    else
    {
        for (i = num - 2; i > -1; i--) {
            if (ar[i] + bt[i] < ar[i + 1])
            {
                if (bt[i] == 0) {}
                else {
                    temp = tot_time + bt[i];
                    tot_time += temp;
                }
            }
            else {
                temp = Wt + bt[i];
                Wt = temp;
                tot_time += temp;
            }
        }

    }
    return tot_time / num;
}


int main(int argc , char* argv[]) {
    FILE* readfile;
    int i;
    if ((readfile = fopen(argv[1], "r")) == NULL)
    {
        printf("The file Temps failed to open\n");
    }

    int var;
    fscanf(readfile, "%d", &var);
    int ar[10];
    int bt[10];
    for (i = 0; i < var; i++)
    {
        fscanf(readfile, "%d, %d", ar + i, bt + i);

    }
    if (fclose(readfile) == EOF) //close the file.
    {
        printf("The file failed to close.\n");
    }
    process pro[10];
    for (int i = 0; i < var; i++)
    {
        pro[i].arrival_time = ar[i];
        pro[i].burst_time = bt[i];
    }
    sortByArrival(pro, var);
    float result = FCFS(pro, var);
    printf("FCFS:  mean tunraround = %.2f\n", result);
    result = LCFS_NP(pro, var);
    printf("LCFS_NP: mean tunraround = %.2f\n", result);
    result = LCFS_P(pro, var);
    printf("LCFS_P: mean tunraround = %.2f\n", result);
    result = RnR(pro, var);
    printf("RnR: mean tunraround = %.2f\n", result);
    result = SJF(pro, var);
    printf("SJF: mean tunraround = %.2f\n", result);


    return 0;

}