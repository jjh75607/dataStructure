//
//  12week.c
//  데구실습
//
//  Created by 정순재 on 2023/05/23.
//

#include <stdio.h>
#include <stdlib.h>

#define max(a,b)  (((a) > (b)) ? (a) : (b))

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
}TreeNode;

void printInorder(TreeNode* root) {
    if(root != NULL) {
        printInorder(root->left);
        printf("[%d] ", root->data);
        printInorder(root->right);
    }
}

void printPreorder(TreeNode* root) {
    if(root != NULL) {
        printf("[%d] ", root->data);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

void printPostorder(TreeNode* root) {
    if(root != NULL) {
        printPostorder(root->left);
        printPostorder(root->right);
        printf("[%d] ", root->data);
    }
}

void addNodeData(TreeNode* root) {
    if(root != NULL) {
        root->data++;
        addNodeData(root->left);
        addNodeData(root->right);
    }
}

TreeNode* findMaxData(TreeNode* root) {
    if (root != NULL) {
        TreeNode* maxNode = root;
        TreeNode* left = findMaxData(root->left);
        TreeNode* right = findMaxData(root->right);

        if (left != NULL && left->data > maxNode->data) {
            maxNode = left;
        }

        if (right != NULL && right->data > maxNode->data) {
            maxNode = right;
        }

        return maxNode;
    }
    return NULL;
}


int get_height(TreeNode *node)  {
    int height=0;
    if( node != NULL )
        height = 1 + max(get_height(node->left), get_height(node->right));
    
    return height;
}

int checkBalanced(TreeNode* root) {
    if(root == NULL) {
        return 1;
    }
    
    int result = get_height(root->left) - get_height(root->right); // -1 < r < 1
    
    if(result < -1 || result > 1) { //균형트리가 아닐때
        return 0;
    }
    
    return checkBalanced(root->left) && checkBalanced(root->right);
}

int equals(TreeNode* t1, TreeNode* t2) {
    if((t1 == NULL && t2 == NULL)) { //둘다 비어있으면 같은것
        return 1;
    } else if((t1 != NULL && t2 != NULL && equals(t1->left, t2->left) && equals(t1->right, t2->right) && (t1->data == t2->data))) {
        return 1;
    }
    return 0;
}

TreeNode* duplicationTree(TreeNode* root) {
    if(root == NULL) {
        return NULL;
    }
    TreeNode* newRoot = (TreeNode*)malloc(sizeof(TreeNode));
    
    newRoot->data = root->data;
    newRoot->left = duplicationTree(root->left);
    newRoot->right = duplicationTree(root->right);
    
    return newRoot;
}

int main() {
    TreeNode n1 = {1,NULL,NULL};
    TreeNode n2 = {24, NULL, NULL};
    TreeNode n3 = {123, NULL, NULL};
    TreeNode n4 = {34, &n2, &n1};
    TreeNode n5 = {54, NULL, NULL};
    TreeNode n6 = {3, NULL, NULL};
    TreeNode n7 = {2, &n3, NULL};
    TreeNode n8 = {9, &n5, &n4};
    TreeNode n9 = {4, &n7, &n6};
    TreeNode n10 = {321, &n9, &n8};
    TreeNode* t1 = &n10;
    
    TreeNode i1 = {327, NULL, NULL};//i
    TreeNode i2 = {9248, &i1, NULL};//h
    TreeNode i3 = {28, NULL, &i2};//g
    TreeNode i4 = {32, NULL, &i3};//f
    TreeNode i5 = {8383, NULL, NULL};//e
    TreeNode i6 = {12, NULL, NULL};//d
    TreeNode i7 = {0, &i5, &i4};//c
    TreeNode i8 = {83, &i6, NULL};//b
    TreeNode i9 = {7, &i8, &i7};//a
    TreeNode* t2 = &i9;
    
    TreeNode j1 = {93, NULL, NULL};//k
    TreeNode j2 = {8, &j1, NULL};//j
    TreeNode j3 = {4, NULL, NULL};//i
    TreeNode j4 = {12, &j2, NULL};//h
    TreeNode j5 = {423, NULL, &j3};//g
    TreeNode j6 = {1, &j5, &j4};//f
    TreeNode j7 = {23, NULL, NULL};//e
    TreeNode j8 = {9, NULL, &j6};//d
    TreeNode j9 = {546, &j7, NULL};//c
    TreeNode j10 = {43, &j9, &j8};//b
    TreeNode j11 = {453, &j10, NULL};//a
    TreeNode* t3 = &j11;
    
    printf("inorder \n");
    printInorder(t1);
    printf("\n");
    printInorder(t2);
    printf("\n");
    printInorder(t3);

    printf("\npreorder \n");
    printPreorder(t1);
    printf("\n");
    printPreorder(t2);
    printf("\n");
    printPreorder(t3);

    printf("\npostorder \n");
    printPostorder(t1);
    printf("\n");
    printPostorder(t2);
    printf("\n");
    printPostorder(t3);
    printf("\n");

    printf("t1트리에 1더하기\n");
    printInorder(t1);
    printf("\n");
    addNodeData(t1);
    printInorder(t1);
    printf("\n");


    printf("t1트리 중 가장 큰 값 : %d\n", findMaxData(t1)->data);
    printf("t2트리 중 가장 큰 값 : %d\n", findMaxData(t2)->data);
    printf("t3트리 중 가장 큰 값 : %d\n", findMaxData(t3)->data);

    checkBalanced(t1) ? printf("t1트리는 균형트리 입니다.\n") : printf("t1은 균형트리가 아닙니다\n");
    checkBalanced(t2) ? printf("t2트리는 균형트리 입니다.\n") : printf("t2은 균형트리가 아닙니다\n");
    checkBalanced(t3) ? printf("t3트리는 균형트리 입니다.\n") : printf("t3은 균형트리가 아닙니다\n");

    equals(t1, t2) ? printf("t1은 t2와 같습니다\n"):printf("t1은 t2와 다릅니다.\n");
    equals(t1, t3) ? printf("t1은 t3와 같습니다\n"):printf("t1은 t3와 다릅니다.\n");
    equals(t2, t3) ? printf("t2은 t3와 같습니다\n"):printf("t2은 t3와 다릅니다.\n");

    printf("t1 복사\n");
    TreeNode* temp = duplicationTree(t1);
    printf("\nInorder t1 복사본\n");
    printInorder(temp);
    printf("\n");
    equals(t1, temp) ? printf("t1은 temp와 같습니다\n"):printf("t1은 temp와 다릅니다.");
}

