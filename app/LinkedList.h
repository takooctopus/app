#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>

#ifndef NULL
#define NULL 0
#endif

//��ʾ����ڵ�Ľṹ��
template<class N>
struct Node {
	//�ڵ�ֵ
	N value;
	//ָ����һ���ڵ��ָ��
	Node *next;
};

template<class N>
class LinkedList {
private:
	//������
	int Length;
	//ͷ�ڵ�
	Node<N> *head;

	//��ȡָ��λ�õĽڵ�
	Node<N>* __GetNode(int);
public:
	LinkedList();
	~LinkedList();
	//������β�����һ���ڵ�
	bool Add(N);
	//�Ƴ�ָ��λ�õĽڵ�
	bool Remove(int);
	//��ȡָ��λ�õ�ֵ
	N* GetValue(int);
	//��ȡĳ�ڵ������ֵ��λ�ã�
	int GetIndex(N);
	//��ȡ������
	int GetLength();
	//��ȡͷ�ڵ�
	Node<N>* GetHead();
	//��ָ����λ����ӽڵ�
	bool Add(int, N);
	//�ͷ���������
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
* �������ĩβ���һ��ֵ
* @param value Ҫ��ӽ������ֵ
* @return �ɹ������棬���򷵻ؼ�
*/
template<typename N>
bool LinkedList<N>::Add(N value) {
	try {
		//�����ǰ����Ϊ��
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
* �Ƴ�������ָ��λ�õĽڵ�
* @param index Ҫ�Ƴ��Ľڵ��λ��
* @return ����ɹ������棬���򷵻ؼ�
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
* ��ָ����λ�����һ��ֵ�����indexС��0���������λ�����index�����������������β��
* @param index Ҫ��ӵ�λ��
* @param value Ҫ��ӵ�ֵ
* @return �ɹ���������򷵻ؼ�
*/
template<typename N>
bool LinkedList<N>::Add(int index, N value) {
	try {
		if (index <= 0) {
			//�嵽��һ��
			Node<N> *node = new Node<N>();
			node->value = value;
			node->next = this->head;
			this->head = node;
			this->Length++;
			return true;

		}
		else if (index == this->Length || index > this->Length) {
			//�嵽ĩβ
			return this->Add(value);

		}
		else {
			//�嵽�м�

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
* ��ȡ����ĳ���
* @return ��������ĳ���
*/
template<typename N>
int LinkedList<N>::GetLength() {
	return this->Length + 1;
}

/*
* ��ȡͷָ��
* @return
*/
template<typename N>
Node<N>* LinkedList<N>::GetHead() {
	return this->head;
}

/*
* ��ȡָ��λ�ýڵ�
* @param index ����λ��
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
* ��ȡָ��ָ��λ�ýڵ��ֵ��ָ��
* @param index Ҫ��ȡ�Ľڵ�λ��
* @return �ڵ�ֵ
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
* ��ȡָ��ֵ�������е�λ��
* @param value Ҫ�ҵ�ֵ
* @return ����ҵ�����λ�ã�û�ҵ�����-1
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