#include <iostream>
#include <sched.h>
#include <stdio.h>
using namespace std;

int main() {

    int pol = sched_getscheduler(0);
    struct sched_param params;

    if (pol == -1) {

        perror("Error");

        return -1;

    }

    if (sched_getparam(0, &params) == -1) {

        perror("Error");

        return -1;

    }

    switch(pol) {

        case 0:
        cout << "Politica de planificacion: SCHED_OTHER\n";
        break;

        case 1:
        cout << "Politica de planificacion: SCHED_FIFO\n";
        break;

        case 2:
        cout << "Politica de planificacion: SCHED_RR\n";
        break;

        case 3:
        cout << "Politica de planificacion: SCHED_BATCH\n";
        break;
        
        case 5:
        cout << "Politica de planificacion: SCHED_IDLE\n";
        break;

        default:
        cout << "Unknown\n";
        break;

    }

    cout << "Prioridad: " << params.sched_priority << '\n';
    cout << "Valor max: " << sched_get_priority_max(pol) << "; Valor min: " << sched_get_priority_min(pol) << '\n';
    
    return 0;

}