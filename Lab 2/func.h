#ifndef FUNC_H
#define FUNC_H

// timeTable: clmn0 = arriveTime, clmn1=completionTime  max. 50 proc
// n: #proc
double avgTurnaround(double timeTable[2][50], int n);

// n: #phys mem frames
int fifopgFault(int n, int pg[50], int ref[100]);
int clkpgFault(int n, int pg[50], int ref[100]);

#endif
