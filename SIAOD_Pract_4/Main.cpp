#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
    string data;
    int numDigits;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(string value, TreeNode* parentNode = nullptr) : data(value), numDigits(0), left(nullptr), right(nullptr), parent(parentNode) {
        for (char c : value) {
            if (isdigit(c)) {
                numDigits++;
            }
        }
    }
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, string value, TreeNode* parent = nullptr) {
        if (node == nullptr) {
            return new TreeNode(value, parent);
        }

        if (value < node->data) {
            node->left = insert(node->left, value, node);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value, node);
        }

        return node;
    }

    int countNodesWithMoreThanThreeDigits(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int count = (node->numDigits > 3) ? 1 : 0;
        count += countNodesWithMoreThanThreeDigits(node->left);
        count += countNodesWithMoreThanThreeDigits(node->right);

        return count;
    }

    TreeNode* findMaxDigitsNode(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        TreeNode* maxDigitsNode = node;
        TreeNode* leftMax = findMaxDigitsNode(node->left);
        TreeNode* rightMax = findMaxDigitsNode(node->right);

        if (leftMax != nullptr && leftMax->numDigits > maxDigitsNode->numDigits) {
            maxDigitsNode = leftMax;
        }
        if (rightMax != nullptr && rightMax->numDigits > maxDigitsNode->numDigits) {
            maxDigitsNode = rightMax;
        }

        return maxDigitsNode;
    }

    TreeNode* removeNodeWithoutDigits(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->numDigits == 0) {
            // Удаляем узел без цифр
            TreeNode* leftChild = removeNodeWithoutDigits(node->left);
            TreeNode* rightChild = removeNodeWithoutDigits(node->right);
            delete node;
            if (leftChild) leftChild->parent = nullptr;
            if (rightChild) rightChild->parent = nullptr;
            if (leftChild && rightChild) {
                leftChild->right = rightChild;
                rightChild->parent = leftChild;
                return leftChild;
            }
            return (leftChild != nullptr) ? leftChild : rightChild;
        }
        else {
            node->left = removeNodeWithoutDigits(node->left);
            node->right = removeNodeWithoutDigits(node->right);
            return node;
        }
    }

    TreeNode* copyTree(TreeNode* original, TreeNode* parent = nullptr) {
        if (original == nullptr) {
            return nullptr;
        }

        TreeNode* newNode = new TreeNode(original->data, parent);
        newNode->left = copyTree(original->left, newNode);
        newNode->right = copyTree(original->right, newNode);

        return newNode;
    }

    void printTree(TreeNode* node, int level = 0) {
        if (node != nullptr) {
            for (int i = 0; i < level; i++) {
                cout << "    ";
            }
            if (node->parent != nullptr) {
                cout << "|--" << "P: " << node->parent->data << " (" << node->parent->numDigits << " digits)";
            }
            cout << " N: " << node->data << " (" << node->numDigits << " digits)" << endl;
            printTree(node->left, level + 1);
            printTree(node->right, level + 1);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(string value) {
        root = insert(root, value);
    }

    int countNodesWithMoreThanThreeDigits() {
        return countNodesWithMoreThanThreeDigits(root);
    }

    void removeNodesWithoutDigits() {
        root = removeNodeWithoutDigits(root);
    }

    string findTextWithMaxDigits() {
        TreeNode* maxDigitsNode = findMaxDigitsNode(root);
        return maxDigitsNode ? maxDigitsNode->data : "";
    }

    BinarySearchTree copy() {
        BinarySearchTree copyTree_obj;
        copyTree_obj.root = copyTree(root);
        return copyTree_obj;
    }

    void prettyPrint() {
        printTree(root);
    }
};

int main() {
    BinarySearchTree tree;

    // Вставляем значения
    tree.insert("Hello12");
    tree.insert("World");
    tree.insert("423");
    tree.insert("C++");
    tree.insert("12345");
    tree.insert("SIAOD12");
    tree.insert("dgdfgfd");

    // Выводим дерево
    cout << "Binary Search Tree:" << endl;
    tree.prettyPrint();

    // Количество узлов с более чем 3 цифрами
    int count = tree.countNodesWithMoreThanThreeDigits();
    cout << "Nodes with more than 3 digits: " << count << endl;

    // Удаляем узлы без цифр
    tree.removeNodesWithoutDigits();
    cout << "Binary Search Tree after removing nodes without digits:" << endl;
    tree.prettyPrint();

    // Находим текст с максимальным количеством цифр
    string maxDigitsText = tree.findTextWithMaxDigits();
    cout << "Text with the maximum number of digits: " << maxDigitsText << endl;

    // Создаем копию дерева
    BinarySearchTree copyTree = tree.copy();
    cout << "Copy of the Binary Search Tree:" << endl;
    copyTree.prettyPrint();

    return 0;
}
