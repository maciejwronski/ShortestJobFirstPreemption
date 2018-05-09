#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#define N 5
#define MAXTIME 10
#define INTERVAL 1

using namespace std;

typedef struct myStruct {
    int p_id;
    int p_bt;
    int p_btcp;
    int p_at;

    int p_ft;
} myStruct;

void initializeStruct(struct myStruct *process, int maxProcess){
    for(int i=0; i<maxProcess; i++){
        process[i].p_id = i;
        process[i].p_bt = (rand()%MAXTIME)+1;
        process[i].p_btcp = process[i].p_bt;
        process[i].p_at = rand()%10;
        process[i].p_ft = NULL;
    }
}
void showIntitialValues(struct myStruct *process, int maxProcess){
    for(int i=0; i<maxProcess; i++){
        if(i==0)
            cout << "ID  NADEJSCIE  WYKONANIE" << endl;
            cout << process[i].p_id << "      " << process[i].p_at << "       " << process[i].p_bt << endl;
    }
}
void showResult(struct myStruct *process, int maxProcess){
    double averageWaitTime = 0;
    for(int i=0; i<maxProcess; i++){
        if(i==0)
        cout << "ID  NADEJSCIE  WYKONANIE           CZAS UKONCZENIA         CZAS OCZEKIWANIA" << endl;
            cout << process[i].p_id << "      " << process[i].p_at << "       " << process[i].p_bt << "                              " << process[i].p_ft << "         " << process[i].p_ft-process[i].p_btcp <<  endl;
        averageWaitTime += (process[i].p_ft-process[i].p_btcp);
    }
    averageWaitTime /=maxProcess;
    cout << "Sredni czas zakonczenia:  " << averageWaitTime << endl;
}
int findFirstID(struct myStruct* process, int maxProcess){
    int fastestProcess = 0;
    for(int i=1;i<maxProcess; i++){
        if(process[i].p_at < process[fastestProcess].p_at){
            fastestProcess = i;
        }
    }
    for(int j=0; j<maxProcess; j++){
            if(process[j].p_at == process[fastestProcess].p_at && process[j].p_bt < process[fastestProcess].p_bt)
                fastestProcess = j;
    }
    return fastestProcess;
}
int* findNewID(struct myStruct* process, int maxProcess){
        int num = 9999;
        int* fastestProcess = &num;
        for(int j=0; j<maxProcess; j++){
            if(process[j].p_bt < *fastestProcess && process[j].p_bt > 0)
                fastestProcess = &process[j].p_bt;
        }
        return fastestProcess;
}


int main()
{
    srand(time(NULL));
    myStruct process[N];
    initializeStruct(process, N);
    showIntitialValues(process, N);

    int firstProcess = findFirstID(process, N);
    int* minID = &process[firstProcess].p_bt;
    int numberOfProcess = N;

    int summ = 0;

    cout << "Starting from process " << *(minID-1) << endl;
    while(numberOfProcess!=0){
        cout << "Decreasing " <<  *(minID) <<  " to ";
        *minID -= INTERVAL;
        summ+=INTERVAL;
        cout << *minID << endl;
        for(int i=0; i<N; i++){
            if(process[i].p_bt < *minID && process[i].p_bt > 0 && process[i].p_at == summ){
                cout << "Changing current process " <<  *(minID-1) <<  " to " << process[i].p_id << endl;
                minID = &process[i].p_bt;
            }
        }
        if(*minID == 0){
            cout << "Process " <<  *(minID-1) <<  " is finished(" << *minID << ") Searching for new value. " << endl;
            process[*(minID-1)].p_ft = summ;
            minID = findNewID(process, N);

            numberOfProcess--;
            if(numberOfProcess > 0)
                cout << "new process: " << *(minID-1) << endl;
        }
    }

    showResult(process, N);
    return 0;
}
