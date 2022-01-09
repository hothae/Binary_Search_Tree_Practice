/*
이진 탐색 트리 구현

왼쪽 자식 노드의 값이 부모 노드보다 더 작은 값을 가지고, 오른쪽 자식 노드의 값이 부모 노드보다 더 큰 값을 가지는 트리
탐색 : 트리의 루트 노드부터 순회하며 찾는값이 루트 노드보다 큰 경우 오른쪽 자식을 방문, 작을 경우 왼쪽 자식을 방문. 같으면 탐색 종료
방문한 노드가 NULL 일 때까지 찾지 못하면 해당 트리에 찾고자 하는 값은 없다
삽입 : 삽입하는 값이 루트 노드보다 크면 오른쪽, 작으면 왼쪽 NULL인 노드를 만나면 해당 위치에 값을 삽입 후 종료
삭제 : 해당 노드의 값이 있는 노드에 자식노드가 둘다 있는 경우, 오른쪽 트리의 가장작은 값이 덮어씌워지고 오른쪽트리의 값은 NULL로 대체한다
		자식이 둘다 없는 경우, NULL을 반환한다
		자식이 하나있는경우 그 값을 덮어씌우고 해당 자식노드의 값을 NULL로 대체한다
가장 작은 값을 찾기 : 가장 왼쪽 트리에 있는 값이 최소값.
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
		if (root->data > data)	root->left = BST_insert(root->left, data);	//이미 노드에 있는 값이 집어넣는 값보다 크면
		else root->right = BST_insert(root->right, data);								//이미 노드에 있는 값이 집어넣는 값보다 작으면
	}
	return root;
}

NODE* findmin(NODE* root) {
	NODE* tmp = root;
	while (tmp->left != NULL) tmp = tmp->left;	//가장 왼쪽 노드를 찾는 과정
	return tmp;
}

NODE* BST_delete(NODE* root, int data) {
	NODE* tnode = NULL;

	if (root == NULL) return NULL;		//애초에 노드가 비어있으면 비어있음을 반환

	if (root->data > data) root->left = BST_delete(root->left, data);		//삭제하려는 값이 노드의 값보다 작으면 왼쪽 트리 방문, 다시 삭제작업 반복
	else if (root->data < data) root->right = BST_delete(root->right, data);

	else {	//삭제하려는 값이 노드에있는 값과 같으면 즉, 해당 노드를 삭제해야 할 때
		if ((root->right != NULL) && (root->left != NULL)) {
			/*
			해당 노드의 자식 노드가 둘다 있으면 해당 노드의 위치에 자식노드의
			오른쪽 자식 노드의 값이 해당 노드로 대체되며,
			오른쪽 자식노드는 비워져야 함
			이진트리의 경우 부모노드의 값보다 작은 값이 왼쪽자식노드에, 큰값이 오른쪽자식노드에 들어가기 때문
			*/
			tnode = findmin(root->right);	//해당 노드에 덮어씌울 오른쪽 자식 노드의 최솟값을 찾아 저장
			root->data = tnode->data;		//그 최솟값을 덮어씌울(삭제할 노드)위치에 저장
			root->right = BST_delete(root->right, tnode->data);	//오른쪽 자식노드의 최솟값을 비워야함
		}
		else {
			/*
			자식 노드의 둘중에 하나라도 비어있으면, 다 비어있거나, 둘중에 하나만 비어있거나
			왼쪽 자식 노드가 비어있으면, 오른쪽 자식노드는 반드시 비어있음
			왼쪽 자식노드가 차있을 때, 그 왼쪽 노드를 삭제할 노드의 위치에 덮어 씌움
			*/
			tnode = (root->left == NULL) ? root->right : root->left;		//비어있으면 root->right의 값은 NULL 이므로 NULL을반환 한다
			free(root);		//동적 할당 종료 : 해당 노드의 자식노드 생성 중지
			return tnode;
		}
	}

	return root;
}

NODE* BST_search(NODE* root, int data) {
	if (root == NULL) return NULL;		//찾는 위치의 노드가 비어있으면 NULL 반환
	if (root->data == data) return root;	//찾는 위치의 노드에 찾고자하는 값이 들어가 있으면 반환
	else if (root->data > data) return BST_search(root->left, data);		//찾고자하는 값이 루트노드에 있는 값보다 작으면 왼쪽트리를 방문하여 다시 찾음
	else return BST_search(root->right, data);			//찾고자 하는 값이 루트노드에 있는 값보다 크면 왼쪽트리를 방문하여 다시 찾음
}

void preorder(NODE* root) {	//전위순회 루트노드 먼저 방문 후 왼쪽 노드, 오른쪽 노드 방문
	if (root == NULL) return;

	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);
}

void inorder(NODE* root) {		//중위 순회 왼쪽자식노드 먼저 방문 후 루트노드 방문, 이후 오른쪽 노드 방문
	if (root == NULL) return;

	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

void postorder(NODE* root) {		//후위순회 오른쪽자식노드, 루트노드, 왼쪽자식노드 순으로 방문
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

