/*For this machine problem, you are given 2 sorted lists of strings.

Your goal is to merge the two sorted lists into one sorted list.

Implement the following function:

int merge(string A[], string B[], string C[], int n, int m);
Assume A has n elements, B has m elements, and that C can accommodate n + m elements.

Your goal is to merge the sorted elements of A and B into C and make sure that they stay sorted.

The function merge should also return the number of comparisons made when merging A and B into C.

In case of duplicates, take the string from A first.

Samples
Input:

4 cayennepepper ginger tarragon turmeric
4 celeryseed marjoram saffron whitepepper
Output:

7
cayennepepper celeryseed ginger marjoram saffron tarragon turmeric
Apart from printing the contents of C, the number of string comparisons is printed. In the sample above, 7 string comparisons were made. The comparisons were for the following:

"cayennepepper" with "celeryseed"
"ginger" with "celeryseed"
"ginger" with "marjoram"
"marjoram" with "tarragon"
"saffron" with "tarragon"
"tarragon" with "whitepepper"
"turmeric" with "whitepepper"
Input:

3 coriander dill nutmeg
3 thyme vanillabean wormwood
Output:

3
coriander dill nutmeg thyme vanillabean wormwood
Here, only 3 string comparisons were made:

"coriander" with "thyme"
"dill" with "thyme"
"nutmeg" with "thyme"
No more string comparisons were made, since A has run out of strings.
*/

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