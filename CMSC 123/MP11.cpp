#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* parent, *left, *right;

    Node() {
        value = 0;
        parent = left = right = NULL;
    }

    Node(int x) {
        value = x;
        parent = left = right = NULL;
    }
};

class Tree {
public:
    Node* root;

    Tree() {
        root = NULL;
    }

    void insert(Node*& curr, int x, Node* prnt = NULL) {
        if (curr == NULL) {
            curr = new Node(x);
            curr->parent = prnt;
        }
        else {
            if (x < curr->value)
                insert(curr->left, x, curr);
            else if (x > curr->value)
                insert(curr->right, x, curr);
        }
    }

    Node* search(Node* curr, int x) {
        Node* temp = curr;

        while (temp != NULL) {
            if (x == temp->value)
                return temp;
            else if (x < temp->value)
                temp = temp->left;
            else if (x > temp->value)
                temp = temp->right;
        }

        return NULL;
    }

    bool ancestor(int a, int b) {
        if (a == b)
            return false;
        Node* curr = root;
        bool foundA = false;
        bool foundB = false;
        while (curr != NULL && curr->value != a) {
            if (a < curr->value)
                curr = curr->left;
            else if (a > curr->value)
                curr = curr->right;
        }

        if (curr == NULL)
            return false;

        while (curr != NULL) {
            if (curr->value == b)
                return true;
            else if (curr->value > b)
                curr = curr->left;
            else if (curr->value < b)
                curr = curr->right;
        }

        return false;
    }

    bool descendant(int a, int b) {
        return (ancestor(b, a));
    }

    int successor(int a) {
        Node* curr = search(root, a);

        if (curr == NULL)
            return a;

        while (curr->right != NULL) {
            curr = curr->right;

            while (curr->left != NULL)
                curr = curr->left;

            return curr->value;
        }
        Node* temprnt = curr->parent;

        while (temprnt != NULL && curr == temprnt->right) {
            curr = temprnt;
            temprnt = temprnt->parent;
        }

        if (temprnt == NULL)
            return a;

        return temprnt->value;
    }

    int predecessor(int a) {
        Node* curr = search(root, a);

        if (curr == NULL)
            return a;

        while (curr->left != NULL) {
            curr = curr->left;

            while (curr->right != NULL)
                curr = curr->right;

            return curr->value;
        }
        Node* temprnt = curr->parent;

        while (temprnt != NULL && curr == temprnt->left) {
            curr = temprnt;
            temprnt = temprnt->parent;
        }

        if (temprnt == NULL)
            return a;

        return temprnt->value;
    }
};

int main() {
    int n;
    cin >> n;
    Tree bst;

    for (int i = 1; i <= n; i++) {
        int items;
        cin >> items;
        bst.insert(bst.root, items);
    }

    int a1, b1;
    cin >> a1 >> b1;
    bst.ancestor(a1, b1) ? cout << "Laozi" : cout << "Mushu";
    cout << "\n";

    int a2, b2;
    cin >> a2 >> b2;
    bst.descendant(a2, b2) ? cout << "Mulan" : cout << "Mushu";
    cout << "\n";

    int a3, b3;
    cin >> a3 >> b3;
    int x = bst.successor(a3);
    int y = bst.predecessor(b3);
    if (x != a3)
        cout << x << "\n";
    else
        cout << "Li Shang" << "\n";

    if (y != b3)
        cout << y << "\n";
    else
        cout << "Li Shang" << "\n";
    // (a3 != bst.successor(a3)) ? cout << bst.successor(a3) << "\n": cout << "Li Shang" << "\n";
    // (b3 != bst.predecessor(b3)) ? cout << bst.predecessor(b3) << "\n": cout << "Li Shang" << "\n";

    cout << "\n";
}