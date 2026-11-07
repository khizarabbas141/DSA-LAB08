#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    int size;

    Node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
        size = 1;
    }
};

int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int size(Node* N) {
    if (N == nullptr)
        return 0;
    return N->size;
}

int getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

void updateNode(Node* N) {
    N->height = 1 + max(height(N->left), height(N->right));
    N->size = 1 + size(N->left) + size(N->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateNode(y);
    updateNode(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateNode(x);
    updateNode(y);

    return y;
}

Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    updateNode(node);

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key <node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    updateNode(root);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void getTopKUtil(Node* root, int& count, int k, vector<int>& result) {
    if (root == nullptr || count >= k)
        return;

    getTopKUtil(root->right, count, k, result);

    if (count < k) {
        result.push_back(root->key);
        count++;
    }

    getTopKUtil(root->left, count, k, result);
}

vector<int> getTopK(Node* root, int k) {
    vector<int> result;
    int count = 0;
    getTopKUtil(root, count, k, result);
    return result;
}

void printTree(Node* root, string indent = "", bool last = true) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "RT--";
            indent += "   ";
        } else {
            cout << "LT--";
            indent += "|  ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main() {
    Node* root = nullptr;
    int n;
    cout << "Enter number of elements to insert into AVL tree: ";
    cin >> n;

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        root = insert(root, val);
        cout << "Tree after inserting " << val << ":\n";
        printTree(root);
    }

    int k;
    cout << "Enter value of k for top k elements: ";
    cin >> k;

    vector<int> topK = getTopK(root, k);
    cout << "Top " << k << " elements: ";
    for (int val : topK) {
        cout << val << " ";
    }
    cout << endl;

    cout << "\nDeleting top " << k << " elements from the tree:\n";
    for (int val : topK) {
        root = deleteNode(root, val);
        cout << "Tree after deleting " << val << ":\n";
        printTree(root);

    }

    return 0;
}