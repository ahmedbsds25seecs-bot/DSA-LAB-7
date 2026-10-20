#include <iostream>
#include <string>

using namespace std;
//stack implementation
struct StackNode {
    struct Node* data;
    StackNode* next;
    StackNode(struct Node* val) {
        data = val;
        next = nullptr;
    }
};
class NodeStack {
    StackNode* topNode;
public:
    NodeStack() {
        topNode = nullptr;
    }
    void push(struct Node* val) {
        StackNode* newNode = new StackNode(val);
        newNode->next = topNode;
        topNode = newNode;
    }
    struct Node* pop() {
        if (!topNode) return nullptr;
        StackNode* temp = topNode;
        struct Node* val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }
    bool isEmpty() { return topNode == nullptr; }
};
struct CharStackNode {
    char data;
    CharStackNode* next;
    CharStackNode(char val) {
        data = val;
        next = nullptr;
    }
};
class CharStack {
    CharStackNode* topNode;
public:
    CharStack() {
        topNode = nullptr;
    }
    void push(char val) {
        CharStackNode* newNode = new CharStackNode(val);
        newNode->next = topNode;
        topNode = newNode;
    }
    char pop() {
        if (!topNode) return '\0';
        CharStackNode* temp = topNode;
        char val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }
    char top() {
        if (!topNode) return '\0';
        return topNode->data;
    }
    
    bool isEmpty() { return topNode == nullptr; }
};
struct StringStackNode {
    string data;
    StringStackNode* next;
    StringStackNode(string val) {
        data = val;
        next = nullptr;
    }
};
class StringStack {
    StringStackNode* topNode;
public:
    StringStack() {
        topNode = nullptr;
    }
    void push(string val) {
        StringStackNode* newNode = new StringStackNode(val);
        newNode->next = topNode;
        topNode = newNode;
    }
    string pop() {
        if (!topNode) return "";
        StringStackNode* temp = topNode;
        string val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }
    string top() {
        if (!topNode) return "";
        return topNode->data;
    }
    
    bool isEmpty() { return topNode == nullptr; }
};
//Node Structure for Binary Tree
struct Node {
    string val;
    Node* left;
    Node* right;
    
    Node(string v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};
//Generating Binary Tree from String
Node* parseTree(string s) {
    if (s.empty()) return nullptr;
    
    int idx = 0;
    while (idx < s.length() && s[idx] != '(') idx++;
    
    string val = s.substr(0, idx);
    Node* root = new Node(val);
    
    if (idx >= s.length()) return root;
    
    string content = s.substr(idx + 1, s.length() - idx - 2);
    
    int balance = 0;
    int commaIdx = -1;
    for (int i = 0; i < content.length(); i++) {
        if (content[i] == '(') balance++;
        else if (content[i] == ')') balance--;
        else if (content[i] == ',' && balance == 0) {
            commaIdx = i;
            break;
        }
    }
    string leftStr, rightStr;
    if (commaIdx == -1) {
        leftStr = content;
        rightStr = "";
    } else {
        leftStr = content.substr(0, commaIdx);
        rightStr = content.substr(commaIdx + 1);
    }
    root->left = parseTree(leftStr);
    root->right = parseTree(rightStr);
    return root;
}
//Preorder Form 
string preorderRecursive(Node* root) {
    if (!root) return "";
    string res = root->val;
    string left = preorderRecursive(root->left);
    string right = preorderRecursive(root->right);
    
    if (!left.empty() || !right.empty()) res += "(" + left + "," + right + ")";
    return res;
}
//Inorder Form 
string inorderIterative(Node* root) {
    NodeStack st;
    Node* curr = root;
    string result = "";
    
    while (curr != nullptr || !st.isEmpty()) {
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.pop();
        result += curr->val + " ";
        curr = curr->right;
    }
    return result;
}
//Postorder Form 
string postorderIterative(Node* root) {
    if (!root) return "";
    NodeStack st;
    StringStack output;
    st.push(root);
    
    while (!st.isEmpty()) {
        Node* curr = st.pop();
        output.push(curr->val);
        
        if (curr->left) st.push(curr->left);
        if (curr->right) st.push(curr->right);
    }
    string result = "";
    while (!output.isEmpty()) result += output.pop() + " ";
    return result;
}
//Validate the Tree String Without Building the Tree
bool validateTreeString(string s) {
    CharStack st;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') st.push('(');
        else if (s[i] == ')') {
            if (st.isEmpty() || st.top() != '(') return false;
            st.pop();
        } 
        else if (s[i] == ',' && st.isEmpty()) return false;
    }
    return st.isEmpty();
}
//TASK 6: Calculate the Height and Depth of the Tree
int myMax(int a, int b) {
    return (a > b) ? a : b;
}
int treeHeight(Node* root) {
    if (!root) return -1;
    return 1 + myMax(treeHeight(root->left), treeHeight(root->right));
}
string getNodeDepths(Node* root, int depth) {
    if (!root) return "";
    string current = "   Node " + root->val + " -> Depth: " + to_string(depth) + "\n";
    string leftStr = getNodeDepths(root->left, depth + 1);
    string rightStr = getNodeDepths(root->right, depth + 1);
    return current + leftStr + rightStr;
}
//Main function
int main() {
    // Tasks 1-6 use the predefined string from the document
    string treeStr = "a(b(d,e),c(,f(g,)))";
    cout << "--- LAB TASKS DEMONSTRATION ---\n";
    cout << "Given Tree String: " << treeStr << "\n\n";

    Node* root = parseTree(treeStr);
    cout << "1. Binary Tree successfully built from string.\n\n";

    cout << "2. Preorder (Recursive): " << preorderRecursive(root) << "\n\n";

    cout << "3. Inorder (Iterative): " << inorderIterative(root) << "\n\n";

    cout << "4. Postorder (Iterative): " << postorderIterative(root) << "\n\n";

    bool isValid = validateTreeString(treeStr);
    cout << "5. Is tree string valid? " << (isValid ? "Yes" : "No") << "\n\n";

    cout << "6. Tree Height: " << treeHeight(root) << "\n";
    cout << "   Node Depths:\n";
    cout << getNodeDepths(root, 0) << "\n";

    return 0;
}