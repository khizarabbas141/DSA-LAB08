#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
struct MinHeapNode {
    char  data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) {
        left = right = nullptr;
        this->data =  data;
        this->freq = freq;
     }
};

struct Compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq >  r->freq);
    }
};


void printPreorderCodes(MinHeapNode* root, string str) {
    if (!root)
        return;

    if (!root->left && !root->right)
        cout << root->data << ": " << str << "\n";

    printPreorderCodes(root->left,  str + "0");
    printPreorderCodes(root->right, str + "1");
}

void buildHuffmanTree(vector<char>& data, vector<int>& freq) {
    struct MinHeapNode *left, *right, *top ;
    priority_queue<MinHeapNode* , vector<MinHeapNode*>, Compare> minHeap;

    for (size_t i = 0; i <  data.size(); ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    while (minHeap.size() != 1) {

        left = minHeap.top();
        minHeap.pop() ;
        right = minHeap.top();
        minHeap.pop();


        top = new MinHeapNode('$',left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
     }

    printPreorderCodes(minHeap.top(), "");
}

int main() {
    vector<char> arr = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freq = {5, 9, 12, 13, 16, 45};
    

    cout << "Huffman Codes in Preorder Traversal:\n";
    buildHuffmanTree(arr, freq);

    return 0;
}