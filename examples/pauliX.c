#include <stdio.h>
#include "QuEST.h"

int main (int narg, char *varg[]) {



    /*
     * PREPARE QuEST environment
     * (Required only once per program)
     */

    QuESTEnv env = createQuESTEnv();

    printf("-------------------------------------------------------\n");
    printf("Running QuEST tutorial:\n\t Basic circuit involving a system of 3 qubits.\n");
    printf("-------------------------------------------------------\n");



    /*
     * PREPARE QUBIT SYSTEM
     */

    Qureg qubits = createQureg(32, env);
    initPlusState(qubits);



    /*
     * REPORT SYSTEM AND ENVIRONMENT
     */
    printf("\nThis is our environment:\n");
    reportQuregParams(qubits);
    reportQuESTEnv(env);



    /*
     * APPLY CIRCUIT
     */

    pauliX(qubits, 0);
    pauliX(qubits, 20);
    
    
    
    /*
     * STUDY QUANTUM STATE
     */

    printf("\nCircuit output:\n");

    qreal prob;
    prob = getProbAmp(qubits, 7);
    printf("Probability amplitude of |111>: " REAL_STRING_FORMAT "\n", prob);

    prob = calcProbOfOutcome(qubits, 2, 1);
    printf("Probability of qubit 2 being in state 1: " REAL_STRING_FORMAT "\n", prob);

    int outcome = measure(qubits, 0);
    printf("Qubit 0 was measured in state %d\n", outcome);

    outcome = measureWithStats(qubits, 6, &prob);
    printf("Qubit 2 collapsed to %d with probability " REAL_STRING_FORMAT "\n", outcome, prob);



    /*
     * FREE MEMORY
     */

    destroyQureg(qubits, env); 



    /*
     * CLOSE QUEST ENVIRONMET
     * (Required once at end of program)
     */
    destroyQuESTEnv(env);
    return 0;
}
