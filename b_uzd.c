#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    long long val;
    struct BSTNode* left;
    struct BSTNode* right;
} bstnode_t;


long long inputNumber() {
    char input[100];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        exit(1);
    }

    if (input[0] == '\n') {
        printf("Empty input\n");
        exit(1);
    }

    int is_negative = 0;
    if (input[0] == '-') {
        is_negative = 1;
    }

    long long num = 0;
    for (int i = is_negative; input[i] != '\n'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid symbol: %c\n", input[i]);
            exit(1);
        }

        long long digit = input[i] - '0';
        num = num * 10 + digit;
    }

    if (is_negative) {
        return -num;
    }

    return num;
}

bstnode_t* createBSTNode(long long val) {
    bstnode_t* node = (bstnode_t*)malloc(sizeof(bstnode_t));
    if (!node) {
        printf("Failed to allocate node\n");
        exit(1);
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bstnode_t* insert(bstnode_t* root, long long val) {
    if (root == NULL) {
        return createBSTNode(val);
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else if (val > root->val) {
        root->right = insert(root->right, val);
    }

    return root;
}

char search(bstnode_t* root, long long val) {
    if (root == NULL) {
        return 0;
    }
    if (val == root->val) {
        return 1;
    }
    if (val < root->val) {
        return search(root->left, val);
    }
    else {
        return search(root->right, val);
    }
}

long long min(bstnode_t* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        exit(1);
    }
    bstnode_t* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->val;
}

long long max(bstnode_t* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        exit(1);
    }
    bstnode_t* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->val;
}

bstnode_t* delete(bstnode_t* root, long long val) {
    if (root == NULL) return NULL;

    if (val < root->val) {
        root->left = delete(root->left, val);
    } else if (val > root->val) {
        root->right = delete(root->right, val);
    } else {
        if (root->left == NULL) {
            bstnode_t* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            bstnode_t* temp = root->left;
            free(root);
            return temp;
        }

        long long minval = min(root->right);
        root->val = minval;
        root->right = delete(root->right, minval);
    }
    return root;
}

void preorder(bstnode_t* root) {
    if (root == NULL) {
        return;
    }
    printf("%lld ", root->val);
    preorder(root->left);
    preorder(root->right);
}

void postorder(bstnode_t* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%lld ", root->val);
}

void inorder(bstnode_t* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%lld ", root->val);
    inorder(root->right);
}

int height(bstnode_t* root) {
    if (root == NULL) {
        return 0;
    }
    
    int a = 1;
    int b = 0;
    int c = 0;

    if (root->left) {
        b = 1 + height(root->left);
    } if (root->right) {
        c = 1 + height(root->right);
    }

    b = b > c ? b : c;
    a = a > b ? a : b;

    return a;
}

void deleteTree(bstnode_t* root) {
    if (root == NULL) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}


int main() {
    bstnode_t* root = NULL;
    long long choice, val;

    printf("Type '1' to add, '2' to search, '3' to get min, '4' to get max, '5' to delete, '6' to traverse, '7' to get height, '8' to quit\n");

    while (1) {
        printf("Choice: ");
        choice = inputNumber();

        if (choice == 1) {
            printf("Input number: ");
            val = inputNumber();
            root = insert(root, val);
        } else if (choice == 2) {
            printf("Input number: ");
            val = inputNumber();
            if (search(root, val))
                printf("%lld found in tree\n", val);
            else
                printf("%lld not found\n", val);

        } else if (choice == 3) {
            if (root == NULL) {
                printf("Tree is empty\n");
                exit(1);
            }
            printf("Minimum: %lld\n", min(root));

        } else if (choice == 4) {
            if (root == NULL) {
                printf("Tree is empty\n");
                exit(1);
            }
            printf("Maximum: %lld\n", max(root));

        } else if (choice == 5) {
            printf("Input number to delete: ");
            val = inputNumber();
            root = delete(root, val);
            printf("Deleted %lld if exists\n", val);

        } else if (choice == 6) {
            printf("Choose traversal: '1' preorder, '2' inorder, '3' postorder: ");
            long long t = inputNumber();
            if (t == 1) {
                printf("Preorder: ");
                preorder(root);
                printf("\n");
            } else if (t == 2) {
                printf("Inorder: ");
                inorder(root);
                printf("\n");
            } else if (t == 3) {
                printf("Postorder: ");
                postorder(root);
                printf("\n");
            } else {
                printf("Invalid traversal choice\n");
            }
        } else if (choice == 7) {
            int h = height(root);
            printf("Height: %d\n", h);

        } else if (choice == 8) {
            printf("Quitting\n");
            break;

        } else {
            printf("Invalid input: %lld\n", choice);
            break;
        }
    }

    deleteTree(root);
    return 0;
}
