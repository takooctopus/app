#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>

#ifndef NULL
#define NULL 0
#endif

//表示链表节点的结构体
template<class N>
struct Node {
	//节点值
	N value;
	//指向下一个节点的指针
	Node *next;
};

template<class N>
class LinkedList {
private:
	//链表长度
	int Length;
	//头节点
	Node<N> *head;

	//获取指定位置的节点
	Node<N>* __GetNode(int);
public:
	LinkedList();
	~LinkedList();
	//在链表尾部添加一个节点
	bool Add(N);
	//移除指定位置的节点
	bool Remove(int);
	//获取指定位置的值
	N* GetValue(int);
	//获取某节点的索引值（位置）
	int GetIndex(N);
	//获取链表长度
	int GetLength();
	//获取头节点
	Node<N>* GetHead();
	//在指定的位置添加节点
	bool Add(int, N);
	//释放整个链表
	void FreeLinkList();
};

template<class N>
LinkedList<N>::LinkedList() {
	this->head = (new Node<N>());
	this->Length = -1;
	this->head->next = NULL;
}

template<class N>
LinkedList<N>::~LinkedList() {
}
/*
* 在链表的末尾添加一个值
* @param value 要添加进链表的值
* @return 成功返回真，否则返回假
*/
template<typename N>
bool LinkedList<N>::Add(N value) {
	try {
		//如果当前链表为空
		if (this->Length == -1) {
			this->head->value = value;
			this->head->next = NULL;
			this->Length++;
			return true;
		}

		Node<N> *temp = this->head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		Node<N> *node = new Node<N>();
		node->value = value;
		node->next = NULL;
		temp->next = node;
		this->Length++;
		return true;
	}
	catch (...) {
	}
	return false;
}

/*
* 移除链表中指定位置的节点
* @param index 要移除的节点的位置
* @return 如果成功返回真，否则返回假
*/
template<typename N>
bool LinkedList<N>::Remove(int index) {
	if (index > this->Length || index < 0) {
		return false;
	}

	Node<N> *aTemp = this->head;
	Node<N> *pTemp = NULL;
	int count = 0;
	while (count <= this->Length) {
		if (count == index && index == 0) {
			this->head = aTemp->next;
			free(aTemp);
			aTemp = NULL;
			this->Length--;
			break;
		}
		if (count == index) {
			pTemp->next = aTemp->next;
			free(aTemp);
			this->Length--;
			aTemp = NULL;
			break;
		}
		pTemp = aTemp;
		aTemp = aTemp->next;
		count++;
	}
	return true;
}

/*
* 在指定的位置添加一个值。如果index小于0则添加在首位，如果index大于链表长度则添加在尾部
* @param index 要添加的位置
* @param value 要添加的值
* @return 成功返回真否则返回假
*/
template<typename N>
bool LinkedList<N>::Add(int index, N value) {
	try {
		if (index <= 0) {
			//插到第一个
			Node<N> *node = new Node<N>();
			node->value = value;
			node->next = this->head;
			this->head = node;
			this->Length++;
			return true;

		}
		else if (index == this->Length || index > this->Length) {
			//插到末尾
			return this->Add(value);

		}
		else {
			//插到中间

			Node<N> *node = this->__GetNode(index - 1);

			Node<N> *temp = new Node<N>();
			temp->value = value;
			temp->next = this->__GetNode(index);
			node->next = temp;
			this->Length++;
			return true;
		}

	}
	catch (...) {
	}
	return false;
}

/*
* 获取链表的长度
* @return 返回链表的长度
*/
template<typename N>
int LinkedList<N>::GetLength() {
	return this->Length + 1;
}

/*
* 获取头指针
* @return
*/
template<typename N>
Node<N>* LinkedList<N>::GetHead() {
	return this->head;
}

/*
* 获取指定位置节点
* @param index 链表位置
* @return
*/
template<typename N>
Node<N>* LinkedList<N>::__GetNode(int index) {
	if (index > this->Length) {
		return NULL;
	}
	else {
		int count = 0;
		for (Node<N> *temp = this->head;; temp = temp->next) {
			if (count == index) {
				return temp;
			}
			count++;
		}
	}
	return NULL;
}
/*
* 获取指向指定位置节点的值的指针
* @param index 要获取的节点位置
* @return 节点值
*/
template<typename N>
N * LinkedList<N>::GetValue(int index) {
	if (index < 0 || index > this->Length) {
		return NULL;
	}
	Node<N> * temp = this->__GetNode(index);
	if (temp != NULL) {
		return &temp->value;
	}
	return NULL;
}

/*
* 获取指定值在链表中的位置
* @param value 要找的值
* @return 如果找到返回位置，没找到返回-1
*/
template<typename N>
int LinkedList<N>::GetIndex(N value) {
	if (this->Length == -1) {
		return -1;
	}
	Node<N> *temp = this->head;
	int count = 0;
	while (count <= this->Length) {
		N v = temp->value;
		if (v == value) {
			return count;
		}
		temp = temp->next;
		count++;
	}
	return -1;
}


#endif /* LINKEDLIST_H_ */