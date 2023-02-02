#pragma once
#include <iostream>
#include <queue>

using std::cout;
using std::cin;
using std::endl;

template<typename T>
struct TreeNode
{
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : left(nullptr), right(nullptr) {}
    TreeNode(T x, TreeNode* left = nullptr, TreeNode* right = nullptr) : data(x), left(left), right(right) {}
    ~TreeNode() {}
};

template<typename T>
class BinaryTree {
public:
	TreeNode<T>* root;

    BinaryTree() { root = NULL; };
    BinaryTree(TreeNode<T>* root) { this->root = root; };

    TreeNode<T>* insertTreeNode(TreeNode<T>* root, T data)
    {
        if (!root) {
            // insertTreeNode the first node, if root is NULL.
            return new TreeNode<T>(data);
        }

        // insertTreeNode data.
        if (data.main_search_key > root->data.main_search_key) {
            // insertTreeNode right node data, if the 'data' to be inserted is greater than 'root' node data.

            // Process right nodes.
            root->right = insertTreeNode(root->right, data);
        }
        else if (data.main_search_key < root->data.main_search_key) {
            // insertTreeNode left node data, if the 'data' to be inserted is smaller than 'root' node data.

            // Process left nodes.
            root->left = insertTreeNode(root->left, data);
        }

        // Return 'root' node, after insertion.
        return root;
    }

    template<typename T1>
    TreeNode<T>* deleteTreeNode(TreeNode<T>* root, T1 key)
    {
        TreeNode<T>* curr = root;
        TreeNode<T>* prev = NULL;

        // Check if the data is actually present in the BST. The variable prev points to the parent of the data to be deleted.
        while (curr != NULL && curr->data.main_search_key != key) {
            prev = curr;
            if (key < curr->data.main_search_key)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (curr == NULL) {
            cout << "Node with " << key << " not found in the"
                << " provided BST.\n";
            return root;
        }

        // Check if the node to be deleted has atmost one child.
        if (curr->left == NULL || curr->right == NULL) {

            // newCurr will replace the node to be deleted.
            TreeNode<T>* newCurr;

            // if the left child does not exist.
            if (curr->left == NULL)
                newCurr = curr->right;
            else
                newCurr = curr->left;

            // check if the node to be deleted is the root.
            if (prev == NULL)
                return newCurr;

            // check if the node to be deleted is prev's left or right child and then replace this with newCurr
            if (curr == prev->left)
                prev->left = newCurr;
            else
                prev->right = newCurr;

            // free memory of the node to be deleted.
            delete curr;
        }

        // node to be deleted has two children.
        else {
            TreeNode<T>* p = NULL;
            TreeNode<T>* temp;

            // Compute the inorder successor
            temp = curr->right;
            while (temp->left != NULL) {
                p = temp;
                temp = temp->left;
            }

            // check if the parent of the inorder successor is the curr or not(i.e. curr=
            // the node which has the same data as the given data by the user to be
            // deleted). if it isn't, then make the the left child of its parent equal to the inorder successor'd right child.
            if (p != NULL)
                p->left = temp->right;

            // if the inorder successor was the curr (i.e. curr = the node which has the
            // same data as the given data by the user to be deleted), then make the
            // right child of the node to be deleted equal to the right child of the inorder successor.
            else
                curr->right = temp->right;

            curr->data = temp->data;
            delete temp;
        }
        return root;
    }

    void inOrderTraversal(TreeNode<T>* root)
    {
        if (root == NULL)
        {
            return;
        }

        inOrderTraversal(root->left);
        cout << root->data.main_search_key << " ";
        inOrderTraversal(root->right);
    }

    template<typename T1>
    TreeNode<T>* searchByKey(TreeNode<T>* root, T1 key)
    {
        std::queue<TreeNode<T>*> q;
        if (root == NULL)
        {
            return NULL;
        }
        q.push(root);
        while (!q.empty())
        {
            TreeNode<T>* temp = q.front();
            if (key == temp->data.main_search_key)
            {
                return temp;
            }
            q.pop();
            if (temp->left != NULL)
            {
                q.push(temp->left);
            }
            if (temp->right != NULL)
            {
                q.push(temp->right);
            }
        }
        return NULL;
    }

    template<typename T1>
    std::vector<TreeNode<T>*> searchByBookKey(TreeNode<T>* root, T1 key)
    {
        std::queue<TreeNode<T>*> q;
        std::vector<TreeNode<T>*> vect;
        if (root == NULL)
        {
            return vect;
        }
        q.push(root);
        while (!q.empty())
        {
            TreeNode<T>* temp = q.front();
            if (key == temp->data.book_search_key)
            {
                vect.push_back(temp);
            }
            q.pop();
            if (temp->left != NULL)
            {
                q.push(temp->left);
            }
            if (temp->right != NULL)
            {
                q.push(temp->right);
            }
        }
        return vect;
    }

    void setBookKey(TreeNode<T>* root, string key)
    {
        if (root == NULL)
        {
            return;
        }

        setBookKey(root->left, key);

        if (key == "title")
        {
            root->data.book_search_key = root->data.getTitle();
        }

        else if (key == "author")
        {
            root->data.book_search_key = root->data.getAuthor();
        }

        else if (key == "category")
        {
            root->data.book_search_key = root->data.getCategory();
        }

        setBookKey(root->right, key);
    }

    int findMaxID()
    {
        int ID = -1;

        std::queue<TreeNode<T>*> q;
        if (root == NULL)
        {
            return NULL;
        }
        q.push(root);
        while (!q.empty())
        {
            TreeNode<T>* temp = q.front();
            if (temp->data.getID() > ID)
            {
                ID = temp->data.getID();
            }
            q.pop();
            if (temp->left != NULL)
            {
                q.push(temp->left);
            }
            if (temp->right != NULL)
            {
                q.push(temp->right);
            }
        }
        return ID;
    }

    void updateTreeByNode(TreeNode<T>* root, TreeNode<T>* match)
    {
        if (root == NULL)
        {
            return;
        }

        updateTreeByNode(root->left, match);
        if (root->data.main_search_key == match->data.main_search_key)
        {
            root->data = match->data;
            return;
        }
        updateTreeByNode(root->right, match);
    }

    void updateTreeByData(TreeNode<T>* root, T data)
    {
        if (root == NULL)
        {
            return;
        }

        updateTreeByData(root->left, data);
        if (root->data.main_search_key == data.main_search_key)
        {
            root->data = data;
            return;
        }
        updateTreeByData(root->right, data);
    }
};

template<typename T>
class BinaryTreePtr {
public:
    TreeNode<T>* root;

    BinaryTreePtr() { root = NULL; };
    BinaryTreePtr(TreeNode<T>* root) { this->root = root; };

    TreeNode<T>* insertTreeNode(TreeNode<T>* root, T data)
    {
        if (!root) {
            // insertTreeNode the first node, if root is NULL.
            return new TreeNode<T>(data);
        }

        // insertTreeNode data.
        if (data->main_search_key > root->data->main_search_key) {
            // insertTreeNode right node data, if the 'data' to be inserted is greater than 'root' node data.

            // Process right nodes.
            root->right = insertTreeNode(root->right, data);
        }
        else if (data->main_search_key < root->data->main_search_key) {
            // insertTreeNode left node data, if the 'data' to be inserted is smaller than 'root' node data.

            // Process left nodes.
            root->left = insertTreeNode(root->left, data);
        }

        // Return 'root' node, after insertion.
        return root;
    }

    template<typename T1>
    TreeNode<T>* deleteTreeNode(TreeNode<T>* root, T1 key)
    {
        TreeNode<T>* curr = root;
        TreeNode<T>* prev = NULL;

        // Check if the data is actually present in the BST. The variable prev points to the parent of the data to be deleted.
        while (curr != NULL && curr->data->main_search_key != key) {
            prev = curr;
            if (key < curr->data->main_search_key)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (curr == NULL) {
            cout << "Node with " << key << " not found in the"
                << " provided BST.\n";
            return root;
        }

        // Check if the node to be deleted has atmost one child.
        if (curr->left == NULL || curr->right == NULL) {

            // newCurr will replace the node to be deleted.
            TreeNode<T>* newCurr;

            // if the left child does not exist.
            if (curr->left == NULL)
                newCurr = curr->right;
            else
                newCurr = curr->left;

            // check if the node to be deleted is the root.
            if (prev == NULL)
                return newCurr;

            // check if the node to be deleted is prev's left or right child and then replace this with newCurr
            if (curr == prev->left)
                prev->left = newCurr;
            else
                prev->right = newCurr;

            // free memory of the node to be deleted.
            delete curr;
        }

        // node to be deleted has two children.
        else {
            TreeNode<T>* p = NULL;
            TreeNode<T>* temp;

            // Compute the inorder successor
            temp = curr->right;
            while (temp->left != NULL) {
                p = temp;
                temp = temp->left;
            }

            // check if the parent of the inorder successor is the curr or not(i.e. curr=
            // the node which has the same data as the given data by the user to be
            // deleted). if it isn't, then make the the left child of its parent equal to the inorder successor'd right child.
            if (p != NULL)
                p->left = temp->right;

            // if the inorder successor was the curr (i.e. curr = the node which has the
            // same data as the given data by the user to be deleted), then make the
            // right child of the node to be deleted equal to the right child of the inorder successor.
            else
                curr->right = temp->right;

            curr->data = temp->data;
            delete temp;
        }
        return root;
    }

    void inOrderTraversal(TreeNode<T>* root)
    {
        if (root == NULL)
        {
            return;
        }

        inOrderTraversal(root->left);
        cout << root->data->main_search_key << "(" << root->data->getClassName() << ") " << " ";
        inOrderTraversal(root->right);
    }

    template<typename T1>
    TreeNode<T>* searchByKey(TreeNode<T>* root, T1 key)
    {
        std::queue<TreeNode<T>*> q;
        if (root == NULL)
        {
            return NULL;
        }
        q.push(root);
        while (!q.empty())
        {
            TreeNode<T>* temp = q.front();
            if (key == temp->data->main_search_key)
            {
                return temp;
            }
            q.pop();
            if (temp->left != NULL)
            {
                q.push(temp->left);
            }
            if (temp->right != NULL)
            {
                q.push(temp->right);
            }
        }
        return NULL;
    }

    void updateTreeByData(TreeNode<T>* root, T data)
    {
        if (root == NULL)
        {
            return;
        }

        updateTreeByData(root->left, data);
        if (root->data->main_search_key == data->main_search_key)
        {
            root->data = data;
            return;
        }
        updateTreeByData(root->right, data);
    }
};
