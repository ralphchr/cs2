#include <iostream>
#include <string>

using namespace std;

class Node{
    public:
        string value;
        Node* left;
        Node* right;

        Node(string x){
            value = x;
            left = NULL;
            right = NULL;
        }


};

int getRoot(string s){
    for (int i = s.length() - 1; i >= 0; i--){
        if (s[i] == '+' || s[i] == '-')
            return i;
    }

    for (int i = s.length() - 1; i >= 0; i--){
        if (s[i] == '*' || s[i] == '/')
            return i;
    }

    return -1;
}

Node* tree(string s){
    int pos = getRoot(s);

    if (pos == -1)
        return new Node(s);

    string temp = "";
    temp += s[pos];
    Node* root = new Node(temp);

    string left = s.substr(0, pos);
    string right = s.substr(pos + 1);

    root->left = tree(left);
    root->right = tree(right);

    return root;


}

void prefix(Node* root){
    if (root == NULL)
        return;

    cout << root->value << " ";
    prefix(root->left);
    prefix(root->right);
}

long long postfix(Node* root){
    if (root == NULL)
        return 0;

    if (root->left == nullptr){
        cout << root->value << " ";
        return stoi(root->value);
}

    long long l = postfix(root->left);
    long long r = postfix(root->right);

    cout << root->value << " ";

    if (root->value == "+")
        return l + r;
    else if (root->value == "-")
        return l - r;
    else if (root->value == "*")
        return l * r;
    else if (root->value == "/")
        return l / r;

    return stoll(root->value);;
}

int main(){
    string s;
    cin >> s;

    Node* root = tree(s);

    prefix(root);
    cout << "\n";

    long long post = postfix(root);
    cout << "\n";

    cout << post;
}
