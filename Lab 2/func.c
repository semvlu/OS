#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "func.h"

double avgTurnaround(double timeTable[2][50], int n) {
    double total = 0;
    for (int i = 0; i < n; i++) {
        double subTurn = (double) timeTable[i][1] - timeTable[i][0]; 
        total += subTurn;
    }

    double avg = (double) total / n;
    return avg;
}

int fifoPgFault(int n, int pg[50], int ref[100]) {
    
    int faultCnt = 0;
    int oldPos = 0; // var to detect oldest pos in the frame

    for (int i = 0; i < 100; i++) { // put the ref in to check
        bool subFault = false; // false when fault occurs

        for (int j = 0; j < n; j++) { // check the frames
            if (ref[i] == pg[j])
                subFault = true;
        }

        if (subFault == false) {
            // insert the ref elem into the frame
            pg[oldPos] = ref[i];
            if (oldPos + 1 == n) 
                oldPos = 0;
            else
                oldPos++;
            
            faultCnt++;
        }
    }
    return faultCnt;
}

int clkPgFault(int n, int pg[50], int ref[100]) {
    int faultCnt = 0;
    int oldPos = 0; // var to detect oldest pos in the frame
    int *r; // R-bit
    r = (int *) malloc(n);

    for (int i = 0; i < 100; i++) { // put the ref in to check
        bool subFault = false; // false when fault occurs
        
        for (int j = 0; j < n; j++) { // check the frames
            if (ref[i] == pg[j]) {
                subFault = true;
                r[j] = 1;
            }
        }

        if (subFault == false) {
            // insert the ref elem into the frame
            bool ins = false;
            for (int j = oldPos; j < n; j++) {
                if (r[j] == 0) {
                    pg[j] = ref[i];
                    ins = true;
                    if (oldPos + 1 == n) 
                        oldPos = 0;
                    else
                        oldPos++;
                }
            }
            if (ins == false) {
                for (int j = 0; j < oldPos; j++) {
                    if (r[j] == 0) {
                        pg[j] = ref[i];
                        ins = true;
                        oldPos = j;
                    }
                }
            }
            faultCnt++;
        }
    }
    return faultCnt;
}