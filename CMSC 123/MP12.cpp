#include <iostream>
#include <cmath>

using namespace std;

class node {
public:
    int item, height, balance, child;
    node *left, *right, *parent;
    node() {
        left = right = parent = NULL;
        height = 0;
        balance = 0;
    }
    node(int x) {
        item = x;
        left = right = parent = NULL;
        height = 0;
        balance = 0;
    }
};

class avl {
private:
    node *root;
    void leftrotate(node *n) {
        node *p = n->parent;
        node *r = n->right;
        node *l = r->left;

        r->parent = p;
        r->child = n->child;
        if (p == NULL)
            root = r;
        else if (n->child == 1)
            p->right = r;
        else
            p->left = r;

        r->left = n;
        n->parent = r;
        n->child = -1;

        n->right = l;
        if (l != NULL) {
            l->parent = n;
            l->child = 1;
        }

        n->height = 1 + max(height(n->left), height(n->right));
        r->height = 1 + max(height(r->left), height(r->right));
    }
    void rightrotate(node *n) {
        node *p = n->parent;
        node *l = n->left;
        node *r = l->right;

        l->parent = p;
        l->child = n->child;

        if (p == NULL)
            root = l;
        else if (n->child == 1)
            p->right = l;
        else
            p->left = l;

        l->right = n;
        n->parent = l;
        n->child = 1;

        n->left = r;
        if (r != NULL) {
            r->parent = n;
            r->child = -1;
        }

        n->height = 1 + max(height(n->left), height(n->right));
        l->height = 1 + max(height(l->left), height(l->right));
    }

    void leftrightrotate(node *n) {
    }

    void rightleftrotate(node *n) {
    }

    int height(node *n) {
        if (n == NULL)
            return -1;
        else
            return n->height;
    }
public:
    avl() {
        root = NULL;
    }
    void insert(int x) {
        node *n = new node(x);
        if (root == NULL)
            root = n;
        else {
            node *tmp = root, *prev;
            while (tmp != NULL) {
                prev = tmp;
                if (x < tmp->item)
                    tmp = tmp->left;
                else
                    tmp = tmp->right;
            }
            n->parent = prev;
            if (x < prev->item) {
                prev->left = n;
                n->child = -1;
            }
            else {
                prev->right = n;
                n->child = 1;
            }

            node *curr = n;
            do {
                int rh = height(curr->right);
                int lh = height(curr->left);

                curr->height = 1 + max(lh, rh);

                if (lh > rh)
                    curr->balance = -1;
                else if (rh > lh)
                    curr->balance = 1;
                else
                    curr->balance = 0;

                int dh = abs(lh - rh);
                if (dh > 1) {
                    if (prev->balance == 1 && curr->balance == 1)
                        leftrotate(curr);
                    else if (prev->balance == -1 && curr->balance == -1)
                        rightrotate(curr);
                    else if (prev->balance == -1 && curr->balance == 1) {
                        rightrotate(prev);
                        leftrotate(curr);
                    }
                    else if (prev->balance == 1 && curr->balance == -1) {
                        leftrotate(prev);
                        rightrotate(curr);
                    }
                }
                prev = curr;
                curr = curr->parent;
            } while (curr != NULL);
        }
    }
    int search(int x) {
        int ctr = 0;
        node *curr = root;
        while (curr) {
            ctr++;
            if (curr->item == x)
                return ctr;
            else if (curr->item < x)
                curr = curr->right;
            else
                curr = curr->left;
        }

        return -ctr;
    }
};

int main() {
    int n;
    cin >> n;
    avl t;
    while (n--) {
        int item;
        cin >> item;
        t.insert(item);
    }
    cin >> n;
    t.search(n) > 0 ? cout << t.search(n) << " FOUND\n" : cout << -t.search(n) << " !FOUND\n";
    return 0;
}