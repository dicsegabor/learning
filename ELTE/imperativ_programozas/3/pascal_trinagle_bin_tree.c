#include <stdio.h>
#include <stdlib.h>

// This cannot work

struct node
{
    int data;
    struct node *left, *right;
};

struct node *new_node(int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data        = data;
    temp->left = temp->right = NULL;

    return temp;
}

void create_tree(struct node *root, int depth)
{
    // Creating the lef, only if it doesn't exist
    if (root->left == NULL) root->left = new_node(0);
    root->left->data += root->data;

    root->right = new_node(root->data);

    if (--depth > 1)
    {
        create_tree(root->left, depth);
        create_tree(root->right, depth);
    }
}

void printGivenLevel(struct node *root, int level)
{
    if (root == NULL) return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1)
    {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

void display_level_by_level(struct node *root, int level_count)
{
    for (int i = 0; i <= level_count; i++)
    {
        printGivenLevel(root, i);
        printf("\n");
    }
}

int main()
{
    printf("Adja meg, hogy hány sort íratna ki!\n");
    int r;
    scanf("%d", &r);

    struct node *root = new_node(1);
    create_tree(root, r);

    display_level_by_level(root, r);

    return 0;
}