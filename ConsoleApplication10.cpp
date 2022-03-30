﻿#include <iostream>
//#include <locale>
#include <clocale>
using namespace std;

//wcin.imbue(locale("en_US.UTF-8"));
//wcout.imbue(locale("en_US.UTF-8"));




struct Node
{
    string word;
    int value;
    struct Node* left_node;
    struct Node* right_node;
    struct Node* parent;

};

struct Node* search_node(Node* (&tree), int k)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (tree->value == k)
    {
        return tree;
    }
    if (tree->value < k)
    {
        return search_node(tree->right_node, k);
    }
    if (tree->value > k)
    {
        return search_node(tree->left_node, k);
    }

}

struct Node* search_node1(Node* (&tree), int k)
{
    if (tree == NULL)
    {
        cout << "NO\n";
        return 0;
    }
    if (tree->value == k)
    {
        cout << "YES\n";
        return tree;
    }
    if (tree->value < k)
    {
        return search_node1(tree->right_node, k);
    }
    if (tree->value > k)
    {
        return search_node1(tree->left_node, k);
    }

}

struct Node* search_min(Node* (&tree))
{
    if (tree->left_node == NULL)
    {
        return tree;
    }
    else
    {
        return search_min(tree->left_node);
    }
}

struct Node* search_max(Node* (&tree))
{
    if (tree->right_node == NULL)
    {
        return tree;
    }
    else
    {
        return search_max(tree->right_node);
    }
}

void print_tree(Node* node)
{
    if (node != NULL) {
        print_tree(node->left_node);
        cout << node->value << " ";
        print_tree(node->right_node);
    }
    return;
}

struct Node* nextiter(Node* (&tree), int k)
{
    if (tree->value > k)
    {
        return nextiter(tree->left_node, k);
    }
    else
    {
        return tree;
    }
}


void printBT(const string& prefix, Node* (&tree), bool isLeft)
{
    if (tree)
    {
        cout << prefix;

        wcout << (isLeft ? L"├──" : L"└──");

        wcout << tree->value << endl;

        printBT(prefix + (isLeft ? "|   " : "    "), tree->left_node, true);
        printBT(prefix + (isLeft ? "|   " : "    "), tree->right_node, false);
    }
}

void Print_tree(Node* (&tree))
{
    printBT("", tree, false);
}


void add_node(Node* (&tree), int k)
{
    if (tree == NULL) {
        tree = new Node;
        tree->value = k;
        tree->left_node = NULL;
        tree->right_node = NULL;
        tree->parent == NULL;
    }

    if (k < tree->value)
    {
        add_node(tree->left_node, k);
        tree->left_node->parent = tree;
    }
    if (k > tree->value)
    {
        add_node(tree->right_node, k);
        tree->right_node->parent = tree;
    }
}

void delete_node(Node* (&tree), int k)
{
    struct Node* element = search_node(tree, k);
    if (element == tree)
    {
        if (tree->left_node == NULL && tree->right_node == NULL)
        {
            delete(tree);
            tree = NULL;
        }
        else if (tree->left_node != NULL && tree->right_node == NULL)
        {
            tree = tree->left_node;
        }
        else if (tree->left_node == NULL && tree->right_node != NULL)
        {
            tree = tree->right_node;
        }
        else
        {
            struct Node* element_min = search_min(tree->right_node);
            int d = tree->value;
            tree->value = element_min->value;
            element_min->value = d;
            delete_node(element->right_node, d);
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (element->left_node == NULL && element->right_node == NULL)
    {
        
        if(element->parent->left_node != NULL && element->parent->left_node->value == element->value)
        {
            element->parent->left_node = NULL;
        }
        if (element->parent->right_node != NULL && element->parent->right_node->value == element->value)
        {
            element->parent->right_node = NULL;
        }

        delete (element);
        
    }
    else if (element->left_node != NULL && element->right_node == NULL)
    {
        if (element->parent->left_node != NULL && element->parent->left_node->value == element->value)
        {
            element->left_node->parent = element->parent;
            element->parent->left_node = element->left_node;
        }
        if (element->parent->right_node != NULL && element->parent->right_node->value == element->value)
        {
            element->left_node->parent = element->parent;
            element->parent->right_node = element->left_node;
        }
        delete(element);
    }
    else if (element->left_node == NULL && element->right_node != NULL)
    {
        if (element->parent->right_node != NULL && element->value == element->parent->right_node->value)
        {
            element->right_node->parent = element->parent;
            element->parent->right_node = element->right_node;
        }
        else if (element->parent->left_node != NULL && element->parent->left_node->value == element->value)
        {
            element->right_node->parent = element->parent;
            element->parent->left_node = element->right_node;
        }
        delete(element);
    }
    else
    {
        struct Node* element_min = search_min(element->right_node);
        //if (element->parent->right_node != NULL && element->value == element->parent->right_node->value)
        //{
        //    element->parent->right_node = element_min;
        //    element->left_node->parent = element_min;
        //    element->right_node->parent = element_min;
        //    element_min->left_node = element->left_node;
        //    element_min->right_node = element->right_node;
        //}
        //else if (element->parent->left_node != NULL && element->parent->left_node->value == element->value)
        //{
        //    element->parent->left_node = element_min;
        //    element->left_node->parent = element_min;
        //    element->right_node->parent = element_min;
        //    element_min->left_node = element->left_node;
        //    element_min->right_node = element->right_node;
        //}
        //delete(element);
        int d = element->value;
        element->value = element_min->value;
        element_min->value = d;
        delete_node(element->right_node, d);
        return;
    }
}




int main()
{

    setlocale(LC_ALL, "");
    struct Node* root;
    root = NULL;
    string choose;
    while (true)
    {
        cin >> choose;
        if (choose == "add")
        {
            int k;
            cin >> k;
            add_node(root, k);
        }
        else if (choose == "help")
        {
            cout << "Command:\nadd <key>\ndelete <key>\nprint\nmin\nmax\nsearch <key>\n";
        }
        else if (choose == "print")
        {
            Print_tree(root);
            cout << endl;
        }
        else if (choose == "delete")
        {
            int k;
            cin >> k;
            delete_node(root, k);
        }
        else if (choose == "min")
        {
            cout << search_min(root)->value;
            cout << endl;
        }
        else if (choose == "max")
        {
            cout << search_max(root)->value;
            cout << endl;
        }
        else if (choose == "search")
        {
            int k;
            cin >> k;
            search_node1(root, k);

        }
        else {
            break;
        }
    }
}


//add 8
//add 10
//add 9
//add 15
//add 13