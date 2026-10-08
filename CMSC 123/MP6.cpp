#include <iostream>
using namespace std;

// #include // using namespace std;
// int divide(int,int);
// int main(){
// int a,b;
// cin>>a>>b;
// try{
// cout< // }
// catch(const char* msg){
// cout< // }
// return 0;
// }

// int divide(int x, int y){
// if(y != 0)
// return x/y;
// else
// throw "Division by Zero";
// }

class Vector{
private:
    int *items;
    int size;
    int max;
public:
    Vector(){
        max = 5;
        size = 0;
        items = new int[max];
    }
    ~Vector(){
        delete[] items;
    }
    int get(int p){
        if (p >= 0 && p < size)
            return items[p];
        else
            return 0;
    }
    int set(int x, int p){
        int temp;
        if(p >= 0 && p < size){
            temp = items[p];
            items[p] = x;
            return temp;
        }
        else
            return 0;
    }
    bool insert(int x, int p){
        if (p < 0 || p > size)
        return false;

        if (size == max){
            max += 5;

        int* newv = new int[max];

        for (int i = 0; i < size; i++)
            newv[i] = items[i];

        delete[] items;
        items = newv;
        }

        for (int i = size; i > p; i--)
            items[i] = items[i - 1];

        items[p] = x;
        size++;

        return true;
    }

    bool push_front(int x){
        return insert(x, 0);
    }
    bool push_back(int x){
        return insert(x, size);
    }
    int getSize(){
        return size;
    }
    void display(){
        for (int i = 0; i < size; i++)
            cout << items[i] << " ";
    }
    int erase(int p){
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

bool isSorted(Vector& v){
    int i;
    for (i = 0; i < v.getSize() - 1; i++){
        if (v.get(i) > v.get(i+1))
            return false;
    }
    return true;
}

void deleteDuplicates(Vector& v){
    for (int i = 0; i < v.getSize(); i++){
        for (int j = i + 1; j < v.getSize(); ){
            if (v.get(i) == v.get(j))
                v.erase(j);
            else
                j++;
        }
    }
    v.display();
}


int main(){
    int tests, test, operation, num, nums, myItem, opara, x, p, tempf;
    cin >> tests;

    for (test = 1; test <= tests; test++){
        Vector v;
        operation = 0;
        cin >> nums;

        for (num = 0; num < nums; num++){
            cin >> myItem;
            v.push_back(myItem);
        }

        cin >> operation;

        switch (operation){
            case 1:
                cin >> opara;
                if (v.push_back(opara))
                v.display();
                else
                cout << "\n" << "OPERATION FAILED\n";
                break;

            case 2:
                cin >> opara;
                if (v.push_front(opara))
                v.display();
                else
                cout << "\n" << "OPERATION FAILED\n";
                break;

            case 3:
                cin >> x >> p;
                if (v.insert(x, p))
                v.display();
                else
                cout << "OPERATION FAILED\n";
                break;

            case 4:
                cin >> opara;
                tempf = v.erase(opara);
                if (tempf != -1){
                cout << "\n" << tempf << "\n";
                v.display();
                } else if (tempf == -1)
                cout << "OPERATION FAILED\n";
                break;

            case 5:
                cin >> opara;
                tempf = v.get(opara);
                if (tempf){
                cout << "\n" << tempf << "\n";
                v.display();
                } else
                cout << "OPERATION FAILED\n";
                break;

            case 6:
                cin >> x >> p;
                tempf = v.set(x, p);
                if (tempf){
                cout << tempf << "\n";
                v.display();
                } else
                cout << "OPERATION FAILED\n";
                break;

            case 7:
                if (isSorted(v))
                cout << "SORTED\n";
                else
                cout << "NOT SORTED\n";
                break;

            case 8:
                deleteDuplicates(v);
            break;
        }
    }

    return 0;
}