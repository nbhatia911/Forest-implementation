#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>

//public api
void add_node(int child, int parent);
void remove(int *list, int n);
void print_forest(const char *str);

//forest data struct
typedef struct node_s node_t;
typedef struct forest_s forest_t;

struct node_s {
    int val;
    struct node_s *parent;
    struct node_s *next_sibling;
    struct node_s *firstchild;
    struct node_s *next_root;
};

struct forest_s {
    struct node_s *roots;
};

//internal implementation
forest_t *F;

node_t *new_node(int n)
{
    node_t *N = (node_t*)malloc(sizeof(node_t));
    memset(N, 0, sizeof(node_t));
    N->val = n;
    return N;
}

// We are using DFS to search in root
node_t *find_node_in_root(node_t *N, int n)
{
    if (N->val == n) return N;

    if (!N->firstchild) return NULL;

    node_t *child = N->firstchild;

    while (child)
    {
        if (child->val == n) return child;

        N = find_node_in_root(child, n);
        if (N) return N;
        child = child->next_sibling;
    }

    return NULL;
}

node_t *find_node_in_forest(int n)
{
    node_t *roots = F->roots;
    node_t *N;
    while (roots)
    {
        //printf("Finding node %d in root %d\n", n, roots->val);
        N = find_node_in_root(roots, n);
        if (N) 
        { 
            //printf("node found\n");
            return N;
        }
        roots = roots->next_root;
    }
    return NULL;
}

void add_node(int child, int parent)
{
    node_t *P,*C;

    //printf("Adding child %d for parent %d\n", child, parent);

    C = new_node(child);
    if (parent == -1)
    {
        //add to root node in forest list
        C->next_root = F->roots;
        F->roots = C;
        return;
    }

    P = find_node_in_forest(parent);
    if (P == NULL)
    {
        printf("Error: Add parent %d first returning\n", parent);
        return;
    }

    //printf("Parent found %d\n", P->val);
    //add new child in parent list
    C->next_sibling = P->firstchild;
    P->firstchild = C;
    C->parent = P;
}

//We are using BFS to print root and each level is
//on new line
void print_root(node_t *N)
{
    std::queue<node_t *> Q;
    int nchild = 1, nchild2 = 0;

    Q.push(N);

    int level = 1;
    printf("\nLevel %d: ", level);
    while (!Q.empty())
    {
        N = Q.front(); Q.pop();
        printf("[%d,%d] ", N->val, N->parent ? N->parent->val:-1); 
        N = N->firstchild;
        while (N)
        {
            nchild2++;
            Q.push(N);
            N = N->next_sibling;
        }

        nchild--;
        if (nchild == 0)
        {
            level++;
            if (nchild2)
            printf("\nLevel %d: ", level);
            nchild = nchild2;
            nchild2 = 0;
        }
    }

    printf("\n");
}

void print_forest(const char *str)
{
    node_t *roots = F->roots;
    node_t *N;
    printf("\n####### Printing Forest (%s)\n", str!=NULL ?str:" ");
    while (roots)
    {
        printf("------ Printing root %d\n", roots->val);
        print_root(roots);
        roots = roots->next_root;
    }
}

void del_node_from_parent_list(node_t *parent, int n)
{
    node_t *node = parent->firstchild;
    node_t *prev;

    if (node->val == n)
    {
        parent->firstchild = node->next_sibling;
        printf("node %d removed from parent list head\n", n);
        return;
    }

    prev = node;
    node = node->next_sibling;
    while (node)
    {
        if (node->val == n)
        {
            prev->next_sibling = node->next_sibling;
            printf("node %d removed from parent list \n", n);
            return;
        }

        prev = node;
        node = node->next_sibling;
    }
}

void connect_children_to_parent(node_t *N)
{
    if (N->firstchild == NULL) return;

    node_t *node = N->parent->firstchild;

    if (node == NULL)
    {
        N->parent->firstchild = N->firstchild;
        return;
    }

    while (node)
    {
        if (node->next_sibling == NULL)
        {
            node->next_sibling = N->firstchild;
            //change parent pointers in children
            node_t *T = N->firstchild;

            T->parent = N->parent;
            T = T->next_sibling;
            while (T)
            {
                T->parent = N->parent;
                T = T->next_sibling;
            }

            return;
        }

        node = node->next_sibling;
    }
}

void erase_node(node_t *N)
{
    free(N);
}

void remove_root_from_forest(node_t *N)
{
    node_t *roots = F->roots;

    if (roots == N)
    {
        F->roots = roots->next_root;
        return;
    }

    while (roots)
    {
        if (roots->next_root != NULL && roots->next_root == N)
        {
            roots->next_root = roots->next_root->next_root;
            return;
        }
        roots = roots->next_root;
    }
}

void make_all_children_as_forest_root(node_t *N)
{
    node_t *C = N->firstchild;
    node_t *prev;

    //add to root node in forest list
    C->next_root = F->roots;
    F->roots = C;
    C->parent = NULL;

    prev = C;
    C = C->next_sibling;
    prev->next_sibling = NULL;

    while (C)
    {
        //add to root node in forest list
        C->next_root = F->roots;
        F->roots = C;
        C->parent = NULL;

        prev = C;
        C = C->next_sibling;
        prev->next_sibling = NULL;
    }
}

void delnode(int i)
{
    node_t *N = find_node_in_forest(i);
    
    if (N == NULL) printf("Error: node %d doesn't exist\n", i);

    if (N->parent)
    {
        del_node_from_parent_list(N->parent, i);
        connect_children_to_parent(N);
    }
    else
    {
        printf("Deleting root node %d\n", i);
        remove_root_from_forest(N);
        make_all_children_as_forest_root(N);
    }

    erase_node(N);
}

void remove(int *list, int n)
{
    int i = 0;

    printf("\n###### Removing nodes from forest\n");
    while (i < n)
    {
        printf("Removing node %d\n", list[i]);
        delnode(list[i]);
        i++;
    }
}

void test_forest_1()
{
    forest_t F1 = {.roots = NULL};

    F = &F1;

    add_node(0, -1);
    add_node(1, 0);
    add_node(2, -1);
    add_node(3, 1);
    add_node(4, 2);
    add_node(5, 2);
    add_node(6, 3);
    add_node(7, 3);
    add_node(8, 5);
    add_node(9, 6);
    add_node(10, 7);

    print_forest("Forest1");

    int remove_list[] = {1,2,6};
    int n = sizeof(remove_list)/sizeof(int);

    remove(remove_list, n);
    print_forest("Forest1 after removal");
}

void test_forest_2()
{
    forest_t F2 = {.roots = NULL};

    F = &F2;

    add_node(0, -1);
    add_node(1, 0);
    add_node(2, 0);
    add_node(3, 0);
    add_node(4, 0);
    add_node(5, 1);
    add_node(6, 1);
    add_node(7, 1);
    add_node(8, 2);
    add_node(9, 2);
    add_node(10, 2);
    add_node(12, 3);
    add_node(13, 3);
    add_node(14, 3);
    add_node(11, 3);
    add_node(15, 4);
    add_node(18, 11);
    add_node(17, 11);
    add_node(16, 11);
    add_node(19, 12);
    add_node(20, 12);

    print_forest("Forest2");

    int remove_list[] = {0, 3, 11};
    int n = sizeof(remove_list)/sizeof(int);

    remove(remove_list, n);
    print_forest("Forest2 after removal");
}

int main ()
{
    test_forest_1();
    test_forest_2();
}
