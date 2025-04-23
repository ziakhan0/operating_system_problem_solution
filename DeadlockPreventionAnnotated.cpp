#include <iostream>
#include <cstring>
using namespace std;

const int NUM_PROCESSES = 6;

const char* processNames[NUM_PROCESSES] = { "P1", "P2", "P3", "P4", "P5", "P6" };
char holding[NUM_PROCESSES][3] = { "R1", "R2", "R3", "R4", "R5", "R6" };
char requesting[NUM_PROCESSES][3] = { "R2", "R3", "R4", "R5", "R6", "R1" };

void showState(const char* title) {
    cout << "\n--- " << title << " ---\n";
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        cout << processNames[i] << ": holds " << holding[i]
            << ", requests " << requesting[i] << "\n";
    }
}

void applyMutualExclusion() {
    cout << "\nMutual Exclusion: Some resources like printers or files must be exclusive.\n";
    cout << "Prevention is often impossible, but awareness and resource pooling can help.\n";
}

void applyHoldAndWaitPrevention() {
    cout << "\nHold and Wait Prevention: Prevent processes from holding while requesting.\n";
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        strcpy(holding[i], "");
    }
}

void applyNoPreemptionPrevention() {
    cout << "\nNo Preemption: If request can't be granted, preempt all held resources.\n";
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        if (strcmp(requesting[i], "") != 0) {
            strcpy(holding[i], "");
        }
    }
}

void applyCircularWaitPrevention() {
    cout << "\nCircular Wait Prevention: Enforce global ordering on resource acquisition.\n";
    const char* orderedResources[NUM_PROCESSES] = { "R1", "R2", "R3", "R4", "R5", "R6" };

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        int hIdx = -1, rIdx = -1;
        for (int j = 0; j < NUM_PROCESSES; ++j) {
            if (strcmp(holding[i], orderedResources[j]) == 0) hIdx = j;
            if (strcmp(requesting[i], orderedResources[j]) == 0) rIdx = j;
        }

        if (hIdx != -1 && rIdx != -1 && rIdx < hIdx) {
            cout << "    " << processNames[i] << " violates resource order. Request denied.\n";
            strcpy(requesting[i], "");
        }
    }
}

int main() {
    showState("Initial State");

    applyMutualExclusion();
    applyHoldAndWaitPrevention();
    showState("After Hold and Wait Prevention");

    applyNoPreemptionPrevention();
    showState("After No Preemption Prevention");

    applyCircularWaitPrevention();
    showState("After Circular Wait Prevention");
    cout << "\nAll deadlock prevention strategies applied.\n";
    system("pause");
    return 0;
}
