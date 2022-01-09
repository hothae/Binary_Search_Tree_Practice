/*
���� Ž�� Ʈ�� ����

���� �ڽ� ����� ���� �θ� ��庸�� �� ���� ���� ������, ������ �ڽ� ����� ���� �θ� ��庸�� �� ū ���� ������ Ʈ��
Ž�� : Ʈ���� ��Ʈ ������ ��ȸ�ϸ� ã�°��� ��Ʈ ��庸�� ū ��� ������ �ڽ��� �湮, ���� ��� ���� �ڽ��� �湮. ������ Ž�� ����
�湮�� ��尡 NULL �� ������ ã�� ���ϸ� �ش� Ʈ���� ã���� �ϴ� ���� ����
���� : �����ϴ� ���� ��Ʈ ��庸�� ũ�� ������, ������ ���� NULL�� ��带 ������ �ش� ��ġ�� ���� ���� �� ����
���� : �ش� ����� ���� �ִ� ��忡 �ڽĳ�尡 �Ѵ� �ִ� ���, ������ Ʈ���� �������� ���� ��������� ������Ʈ���� ���� NULL�� ��ü�Ѵ�
		�ڽ��� �Ѵ� ���� ���, NULL�� ��ȯ�Ѵ�
		�ڽ��� �ϳ��ִ°�� �� ���� ������ �ش� �ڽĳ���� ���� NULL�� ��ü�Ѵ�
���� ���� ���� ã�� : ���� ���� Ʈ���� �ִ� ���� �ּҰ�.
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* left;
	struct node* right;
} NODE;

NODE* root = NULL;

NODE* BST_insert(NODE* root, int data) {
	if (root == NULL) {
		root = (NODE*)malloc(sizeof(NODE*));
		root->left = root->right = NULL;
		root->data = data;
		return root;
	}
	else {
		if (root->data > data)	root->left = BST_insert(root->left, data);	//�̹� ��忡 �ִ� ���� ����ִ� ������ ũ��
		else root->right = BST_insert(root->right, data);								//�̹� ��忡 �ִ� ���� ����ִ� ������ ������
	}
	return root;
}

NODE* findmin(NODE* root) {
	NODE* tmp = root;
	while (tmp->left != NULL) tmp = tmp->left;	//���� ���� ��带 ã�� ����
	return tmp;
}

NODE* BST_delete(NODE* root, int data) {
	NODE* tnode = NULL;

	if (root == NULL) return NULL;		//���ʿ� ��尡 ��������� ��������� ��ȯ

	if (root->data > data) root->left = BST_delete(root->left, data);		//�����Ϸ��� ���� ����� ������ ������ ���� Ʈ�� �湮, �ٽ� �����۾� �ݺ�
	else if (root->data < data) root->right = BST_delete(root->right, data);

	else {	//�����Ϸ��� ���� ��忡�ִ� ���� ������ ��, �ش� ��带 �����ؾ� �� ��
		if ((root->right != NULL) && (root->left != NULL)) {
			/*
			�ش� ����� �ڽ� ��尡 �Ѵ� ������ �ش� ����� ��ġ�� �ڽĳ����
			������ �ڽ� ����� ���� �ش� ���� ��ü�Ǹ�,
			������ �ڽĳ��� ������� ��
			����Ʈ���� ��� �θ����� ������ ���� ���� �����ڽĳ�忡, ū���� �������ڽĳ�忡 ���� ����
			*/
			tnode = findmin(root->right);	//�ش� ��忡 ����� ������ �ڽ� ����� �ּڰ��� ã�� ����
			root->data = tnode->data;		//�� �ּڰ��� �����(������ ���)��ġ�� ����
			root->right = BST_delete(root->right, tnode->data);	//������ �ڽĳ���� �ּڰ��� �������
		}
		else {
			/*
			�ڽ� ����� ���߿� �ϳ��� ���������, �� ����ְų�, ���߿� �ϳ��� ����ְų�
			���� �ڽ� ��尡 ���������, ������ �ڽĳ��� �ݵ�� �������
			���� �ڽĳ�尡 ������ ��, �� ���� ��带 ������ ����� ��ġ�� ���� ����
			*/
			tnode = (root->left == NULL) ? root->right : root->left;		//��������� root->right�� ���� NULL �̹Ƿ� NULL����ȯ �Ѵ�
			free(root);		//���� �Ҵ� ���� : �ش� ����� �ڽĳ�� ���� ����
			return tnode;
		}
	}

	return root;
}

NODE* BST_search(NODE* root, int data) {
	if (root == NULL) return NULL;		//ã�� ��ġ�� ��尡 ��������� NULL ��ȯ
	if (root->data == data) return root;	//ã�� ��ġ�� ��忡 ã�����ϴ� ���� �� ������ ��ȯ
	else if (root->data > data) return BST_search(root->left, data);		//ã�����ϴ� ���� ��Ʈ��忡 �ִ� ������ ������ ����Ʈ���� �湮�Ͽ� �ٽ� ã��
	else return BST_search(root->right, data);			//ã���� �ϴ� ���� ��Ʈ��忡 �ִ� ������ ũ�� ����Ʈ���� �湮�Ͽ� �ٽ� ã��
}

void preorder(NODE* root) {	//������ȸ ��Ʈ��� ���� �湮 �� ���� ���, ������ ��� �湮
	if (root == NULL) return;

	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);
}

void inorder(NODE* root) {		//���� ��ȸ �����ڽĳ�� ���� �湮 �� ��Ʈ��� �湮, ���� ������ ��� �湮
	if (root == NULL) return;

	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

void postorder(NODE* root) {		//������ȸ �������ڽĳ��, ��Ʈ���, �����ڽĳ�� ������ �湮
	if (root == NULL) return;
	postorder(root->right);
	postorder(root->left);
	printf("%d ", root->data);
}



int main() {
	root = BST_insert(root, 5);
	root = BST_insert(root, 3);
	root = BST_insert(root, 7);
	root = BST_insert(root, 1);
	root = BST_insert(root, 9);
	root = BST_insert(root, 6);

	preorder(root);
	printf("\n");
	inorder(root);
	printf("\n");
	postorder(root);

}

