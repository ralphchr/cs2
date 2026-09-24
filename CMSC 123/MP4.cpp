//IM SORRY IF MY CODE LOOKS BRUTE FORCED OR UNOPTIMIZED TT

#include <iostream>
#define MAX 20

using namespace std;

class Array{
private:
    int items[MAX], size;
public:
    Array(){
        size = 0;
    }

    int getitems(int p){
        return items[p];
    }

    bool setitems(int x, int p){
        if (p < 0 || p >= MAX)
            return false;
        else {
            items[p] = x;
            return true;
        }
    }

    bool insert(int x, int p){
        if (p < 0 || p > getSize() || getSize() >= MAX)
            return false;
        else {
            for (int i = getSize() - 1; i >= p; i--){
                items[i+1] = items[i];
            }
            items[p] = x;
            size++;
            return true;
        }
    }

    bool append(int x){
        if (getSize() < 0 || getSize() >= MAX)
            return false;
        else {
            items[getSize()] = x;
            size++;
            return true;
        }
    }
    bool insertFront(int x){
        if (getSize() < 0 || getSize() >= MAX)
            return false;
        else {
            for (int i = getSize() - 1; i >= 0; i--){
                items[i+1] = items[i];
            }
            items[0] = x;
            size++;
            return true;
        }
    }
    int getSize(){
        return size;
    }
    void display(){
        for (int i = 0; i < size; i++){
            cout << items[i] << " ";
        }
    }
    int removee(int p){ //renamed this to removee with an extra e since there's an exisiting cpp function called "remove";
        if (p < 0 || p >= size)
            return -1;

        int removed = items[p];
        for (int i = p; i < size - 1; i++){
            items[i] = items[i+1];
        }
        size--;
        return removed;
    }
};


int main(){
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++){
        Array arr;
        int size = 0;
        cin >> size;
        for (int n = 0; n < size; n++){
            int val = 0;
            cin >> val;
            arr.append(val);
        }

        int mode = 0;
        cin >> mode;

        int x = -1, p = -1;
        switch (mode){
            case 1:
                cin >> x;
                arr.append(x);
                break;
            case 2:
                cin >> x;
                arr.insertFront(x);
                break;
            case 3:
                cin >> x;
                cin >> p;
                arr.insert(x, p);
                break;
            case 4:
                cin >> p;
                if (p < 0 || p >= size)
                    break;
                arr.removee(p);
                break;
        }
        arr.display();
        cout << "\n";
    }
}