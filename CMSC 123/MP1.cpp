/*Given an array A with size n, determine whether there is an element in A[i] equal to the index i. In this problem, it is assumed that the elements of A are sorted in increasing order.

Produce two solutions, the first one linear and the other sub-linear. This means implementing 2 separate functions calling them one after another in the main function. You are not allowed to use global variables. You are to print the number of comparisons made (how many times A[i]==i was executed) and whether it's a yes or no, i.e. whether there is an A[i] equal to i.

The first input is a number t. This number is the number of test cases to be solved. t test cases will follow.

For each test case, a number n should be read. This represents the size of A. This is the range of n: 5<=n<=20 (declare an array with capacity size 20). Then n integers will follow.

Output:

For each test case, there should be 2 lines of output. The first line is for the linear solution and the second is for the sub-linear solution. For each line, print YES, if there is an A[i] equal to i, followed by the number of comparisons made. If there is no such A[i] equal to i, print NO, followed by the number of comparisons made. There should be 2t lines of output for the t test cases. NO PRINTING IN THE FUNCTIONS ARE ALLOWED EXCEPT THE MAIN.



Sample Input:

2
5
0 1 2 3 4
5
1 2 3 4 5


Sample Output:

YES 1
YES 1
NO 1
NO 2
 */


#include <iostream>
using namespace std;



int linear(int array[], int size){
    int ctr = 0;
    for (int i = 0; i < size; i++){
        ctr++;

        if (array[i] > i)
            return -ctr;

        if (array[i] == i)
            return ctr;
    }
}

int binary(int array[], int size){
    int ctr = 0;
    int start = 0, end = size - 1, mid;
    while (start <= end){
        ctr++;
        mid = (start + end) / 2;

        if (array[mid] == mid)
            return ctr;
        else if (array[mid] > mid)
            end = mid - 1;
        else if (array[mid] < mid)
            start = mid + 1;
    }
    return -ctr;
}

int main(){
    int tests;

    cin >> tests;

    for (int test = 1; test <= tests; test++){
        int size;
        int array[20];
        cin >> size;

        for (int i = 0; i < size; i++){
            cin >> array[i];
        }

        if (linear(array, size) > 0){
            cout << "YES " << linear(array, size);
        }
        else{
            cout << "NO " << -linear(array, size);
        }

        cout << "\n";

        if (binary(array, size) > 0){
            cout << "YES " << binary(array, size);
        }
        else{
            cout << "NO " << -binary(array, size);
        }

        cout << "\n";
    }

}