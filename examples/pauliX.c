#include <stdio.h>
#include "QuEST.h"

int main (int narg, char *varg[]) {



    /*
     * PREPARE QuEST environment
     * (Required only once per program)
     */

    QuESTEnv env = createQuESTEnv();

    int nQubit = 32;

    printf("-------------------------------------------------------\n");
    printf("Running QuEST tutorial:\n\t Basic circuit involving a system of %d qubits.\n", nQubit);
    printf("-------------------------------------------------------\n");



    /*
     * PREPARE QUBIT SYSTEM
     */

    Qureg qubits = createQureg(nQubit, env);
    //initPlusState(qubits);



    /*
     * REPORT SYSTEM AND ENVIRONMENT
     */
    printf("\nThis is our environment:\n");
    reportQuregParams(qubits);
    reportQuESTEnv(env);

    //reportStateToScreen(qubits, env,0);



    /*
     * APPLY CIRCUIT
     */

    pauliX(qubits, 0);

    //reportStateToScreen(qubits, env,0);

    pauliX(qubits, 2);
    
    //reportStateToScreen(qubits, env,0);
    
    
    /*
     * STUDY QUANTUM STATE
     */

    // printf("\nCircuit output:\n");

    qreal prob;
    prob = getProbAmp(qubits, 0);
    printf("Probability amplitude of |000>: " REAL_STRING_FORMAT "\n", prob);

    prob = calcProbOfOutcome(qubits, 2, 1);
    printf("Probability of qubit 2 being in state 1: " REAL_STRING_FORMAT "\n", prob);

    int outcome = measure(qubits, 0);
    printf("Qubit 0 was measured in state %d\n", outcome);

    outcome = measureWithStats(qubits, 2, &prob);
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
