/*
 * QUEUE.cpp
 *
 *  Created on: Jan 29, 2024
 *      Author: aser_
 */
#include "Md_QUEUE.h"

template <typename T>
Md_queue<T>::Md_queue(T val): len(1){
	head = tail = new element<T>(val);
}

template <typename T>
void Md_queue<T>::enque(T val){
	element<T> * tmp = new element<T>(val);
	len+=1;
	tmp->next = head;
	tmp->prev = nullptr;
	if(head != nullptr){
		head->prev = tmp;
	}else{
		tail = tmp;
	}
	head = tmp;
}
template <typename T>
T Md_queue<T>::dequeue(void){
	T tmp;
	if(len == 0)
		return 0;
	tmp = tail->val;
	tail = tail->prev;
	free(tail->next);
	tail->next = nullptr;
	len--;
	return tmp;
}

