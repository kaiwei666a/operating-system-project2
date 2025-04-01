#include "types.h"
#include "stat.h"
#include "user.h"

void print_metrics(int pid, int prev_run_time) {
    int total_run_time = get_total_run_time(pid);
    if (prev_run_time > 0) {
        total_run_time -= prev_run_time;
    }
    printf(1, "Process %d metrics:\n", pid);
    printf(1, "Creation time: %d\n", get_creation_time(pid));
    printf(1, "Completion time: %d\n", get_completion_time(pid));
    printf(1, "Total run time: %d\n", total_run_time);
    printf(1, "Total ready time: %d\n", get_total_ready_time(pid));
    printf(1, "-------------------\n");
}

// Function to prevent compiler optimization
volatile int dummy = 0;

void busy_work(int iterations) {
    for(int i = 0; i < iterations; i++) {
        for(int j = 0; j < 1000000; j++) {
            dummy += j;  // This prevents compiler optimization
        }
    }
}

int main(void) {
    printf(1, "Starting FIFO scheduler test with 3 processes...\n");
    int pids[3];
    int work_sizes[3] = {1, 2, 3};  // Different workloads for each process
    int prev_run_time = 0;  // Track previous process's run time
    
    // Create three processes
    for(int i = 0; i < 3; i++) {
        pids[i] = fork();
        if(pids[i] < 0) {
            printf(1, "Fork failed\n");
            exit();
        }
        
        if(pids[i] == 0) {
            // Child process
            printf(1, "Child process %d starting work...\n", getpid());
            busy_work(work_sizes[i]);
            printf(1, "Child process %d completed work\n", getpid());
            exit();
        }
    }
    
    // Parent process waits for all children
    for(int i = 0; i < 3; i++) {
        wait();
        print_metrics(pids[i], prev_run_time);
        prev_run_time = get_total_run_time(pids[i]);
    }
    
    exit();
} 