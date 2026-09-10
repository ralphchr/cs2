//implement the merge function here

//#include "merge.h"
#include <string>
using namespace std;
int merge(string A[], string B[], string C[], int n, int m){
    int i = 0, j = 0, k = 0, c = 0;

    while (i < n && j < m){
        if (A[i] <= B[j]){
            C[k] = A[i];
            i++;
            k++;
        } else if (A[i] > B[j]){
            C[k] = B[j];
            j++;
            k++;
        }
        c++;
    }

    while (i < n){
        C[k] = A[i];
        i++;
        k++;
    }

    while (j < m){
        C[k] = B[j];
        j++;
        k++;
    }

    return c;
}