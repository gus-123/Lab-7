/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

//연결 리스트의 노드 구조를 구조체로 정의
typedef struct Node {
	int key;
	struct Node* llink;  //왼쪽(이전) 노드에 대한 링크
	struct Node* rlink;  //오른쪽(다음) 노드에 대한 링크
} listNode;


//리스트 시작을 나타내는 Head 노드를 구조체로 정의
typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	printf("[----- [김현민]  [2018038088] -----]\n");
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	//headNode가 공백이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(*h != NULL) {
		freeList(*h);
	}
	//headNode에 대한 메모리를 할당하여 다시 리턴
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	*h = temp;

	return 1;
}

int freeList(headNode* h){
	listNode* p = h->first;  //p는 head가 가리키는 노드를 할당

	listNode* prev = NULL;  //prev 노드를 초기화
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);  //prev의 메모리 할당 해제
	}
	free(h); //h의 메모리 할당 해제
    
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* temp;  //연결리스트의 마지막 노드를 찾아서 참조하기 위해 노드를 할당
	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 새로운 노드의 동적 메모리 할당
	node->key = key; //새로운 노드의 데이터필드에 key 저장
    
	node->rlink = NULL;  //새로운 노드의 rlink는 null을 할당하여 연결을 해제

	if(h->first == NULL) {  //head 노드가 null인 경우
		h->first = node;  //head 노드가 새로운 노드를 참조

		return 0;
	}
	
	temp = h->first;  //temp 노드가 head를 참조
	while(temp->rlink != NULL) {  //temp 노드의 rlink가 null이 아닌 경우
		temp = temp->rlink;  //temp는 temp의 rlink를 참조하도록 함
	}
	temp->rlink = node;  //temp의 rlink가 새로운 노드를 참조하도록함
	
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* preNode;
    	listNode* temp;
        
    	if(h->first == NULL) {  //head 노드가 null인 경우 모든 노드가 삭제 되었으므로 리턴
	
		return 0;
    	}
    
	if(h->first->rlink == NULL) {  //head 노드의 rlink가 null인 경우
		h->first = NULL;  //head에 null을 할당하여 남은 노드와의 연결을 해제
    	} 
	else {  //head 노드의 rlink가 null이 아닌 경우
		preNode = h->first; //preNode는 head가 가리키는 노드를 할당
        	temp = h->first->rlink;  //preNode의 다음 노드를 할당     
            
        	while(temp->rlink != NULL) { //temp의 rlink가 null이 아닐 때 까지 한 노드씩 다음 노드로 이동
			preNode = temp;  //preNode는 temp를 할당
            		temp = temp->rlink;  //temp는 temp의 다음 노드를 할당
        	}
        	preNode->rlink = NULL;  //preNode의 다음 노드인 temp로의 연결 해제
    	}
	free(temp); //temp의 메모리 할당 해제
	
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 새로운 노드의 동적 메모리 할당
	node->key = key; //새로운 노드의 데이터필드에 key 저장

	if(h->first==NULL) {  //head 노드가 null인 경우
		h->first = node; //새로운 노드의 주소를 head 노드에 저장

		return 0;
	}
	node->rlink=h->first;  //head 노드를 새로운 노드의 rlink에 저장
	h->first->llink=node;  //새로운 노드의 주소를 head 노드의 llink에 저장
	h->first = node;  ////새로운 노드의 주소를 head 노드에 저장
	
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp; //temp는 head가 가리키는 노드를 할당
	
	if(h->first== NULL) { //head 노드가 공백인 경우 리턴

		return 0;
	}
	else { //head 노드가 공백이 아닌 경우
		temp = h->first;
		h->first = h->first->rlink;  //head는 head의 다음 노드를 참조 함 
	}
	free(temp); //temp의 메모리 할당 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* nextNode = h->first; //head가 참조하는 첫번째 노드를 할당
	listNode* currentNode = NULL;  //현재 위치를 참조하는 할당
	listNode* preNode = NULL;  //이전 위치를 참조하는 할당

	while (nextNode!= NULL) {  //head가 참조하는 첫번째 노드가 null이 아닌 경우
		preNode = currentNode;  //preNode는 currentNode 위치로 이동
		currentNode = nextNode;  //currentNode 위치로 이동
		nextNode = nextNode->rlink;  //nextNode는 다음 노드 위치로 이동
		currentNode->rlink = preNode;  //currentNode의 rlink에 preNode를 할당하여 역순 만듦
	}
	h->first = currentNode;  //currentNode가 마지막 노드를 가리킬 때, head는 currentNode를 참조 함
	
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* preNode = h->first; //head가 가리키는 노드를 할당
    	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 새로운 노드의 동적 메모리 할당
	node->key = key; //새로운 노드의 데이터필드에 key 저장

    	node->rlink = NULL;  //새로운 노드의 rlink는 null을 할당하여 연결을 해제

    	if (h->first == NULL) { //head 노드가 null인 경우
        	h->first = node;  //head 노드가 새로운 노드를 참조
    	}
    	else { //head 노드가 null이 아닌 경우
		if (node->key < h->first->key) { //삽입할 위치가 맨 앞인 경우
			node->rlink = h->first->rlink;  //head는 head의 다음 노드를 참조하도록 함
            		h->first->rlink = node;  //head의 rlink가 다음 노드를 참조하도록 함
        	}
        	else {
            		while (preNode->rlink) { //preNode 노드의 rlink인 경우
				if (node->key < preNode->rlink->key) {  //삽입할 위치 찾기
					break;
				}
                		preNode = preNode->rlink; //preNode는 preNode의 다음 노드를 할당
            		}
            		node->rlink = preNode->rlink;  //새로운 노드의 rlink가 preNode의 다음 노드를 참조하도록 함
            		preNode->rlink = node; //preNode의 rlink가 새로운 노드를 참조하도록 함
        	}
    	}
	
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* preNode = h->first; //head가 가리키는 노드를 할당
	listNode* temp = h->first->rlink; //head가 가리키는 노드의 다음 노드를 할당

	if (key == preNode->key) { //첫번째 노드의 데이터와 일치하는 경우
		h->first = preNode->rlink; //head가 preNode의 다음 노드를 참조하도록 함
		preNode->rlink = NULL; //preNode의 rlink는 null을 할당하여 연결을 해제
	}
	else {
		while (temp != NULL) { //temp가 null일 때까지 반복하여 탐색
            		if (key == preNode->rlink->key) {  //삭제할 위치 찾기
                		preNode->rlink = temp->rlink;  //preNode의 rlink는 temp의 다음 노드를 참조
                
                		return 0;
            		}
            		preNode = preNode->rlink;  //preNode에 preNode에 다음 노드를 할당
        	}
	}
	free(temp); //temp의 메모리 할당 해제
	
	return 1;
}
