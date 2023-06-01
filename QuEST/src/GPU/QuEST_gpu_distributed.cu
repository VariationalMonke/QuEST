/** @file
 * An implementation of the backend in ../QuEST_internal.h for a Multi-GPU environment.
 * 
 *  @author Jin Bai
*/

# include "QuEST.h"
# include "QuEST_precision.h"
# include "QuEST_validation.h"
# include "QuEST_internal.h"    // purely to resolve getQuESTDefaultSeedKey
# include "mt19937ar.h"

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define REDUCE_SHARED_SIZE 512
# define DEBUG 0

// createQuESTEnv

// in single-GPU, 1. GPUExists to check if gpu existed, can potentially extends to return the number of nodes
//                2. Secondly declare an instance of QuESTEnv
//                3. Assign QuESTEnv->rank and QuESTEnv->numRanks
//                4. Assign QuESTEnv->seeds and QuESTEnv->numSeeds, or call seedQuESTDefault()
//                5. Return the QuESTEnv

// in multi-CPU,  1. Declare int variables rank, numRanks, initialized
//                2. Call MPI_Initialized() with address of initialized, see if MPI already initialized
//                3. If MPI not initialized, call MPI_Init, and assign rank and numRanks with MPI_Comm_rank and MPI_Comm_size
//                4. Assign QuESTEnv->rank and QuESTEnv->numRanks
//                5. Call validateNumRanks(), determine if numRanks is power of 2
//                6. Assign QuESTEnv->seeds and QuESTEnv->numSeeds, or call seedQuESTDefault()
//                7. Return the QuESTEnv

// in multi-GPU,  1. Declare int numGPU, rank, numRanks, initialized


int GPUExists(int *numGPU){
    int deviceCount, device;
    int gpuDeviceCount = 0;
    struct cudaDeviceProp properties;
    cudaError_t cudaResultCode = cudaGetDeviceCount(&deviceCount);
    if (cudaResultCode != cudaSuccess) deviceCount = 0;
    /* machines with no GPUs can still report one emulation device */
    for (device = 0; device < deviceCount; ++device) {
        cudaGetDeviceProperties(&properties, device);
        if (properties.major != 9999) { /* 9999 means emulation only */
            ++gpuDeviceCount;
        }
    }
    *numGPU = gpuDeviceCount;  // pass the number of gpu in cuda
    if (gpuDeviceCount) return 1;
    else return 0;
}