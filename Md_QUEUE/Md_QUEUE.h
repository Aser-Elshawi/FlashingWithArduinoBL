/*
 * QUEUE.h
 *
 *  Created on: Jan 29, 2024
 *      Author: aser_
 */

#ifndef MD_QUEUE_MD_QUEUE_H_
#define MD_QUEUE_MD_QUEUE_H_

#include <stddef.h>
template <typename T>
class element{
public:
	element(T value):val(value),prev(nullptr),next(nullptr){}
	T val;
	element * next;
	element * prev;
};

template <typename T>
class Md_queue{
public:
	Md_queue(): len(0), head(nullptr), tail(nullptr){}
	Md_queue(T val);
	void enqueue(T val);
	T dequeue(void);
	int size(void)const { return this->len;}
private:
	int len;
	element<T> * head;
	element<T> * tail;

};



template <typename T>
Md_queue<T>::Md_queue(T val): len(1){
	head = tail = new element<T>(val);
}

template <typename T>
void Md_queue<T>::enqueue(T val){
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
		return (T)0;
	else if(len == 1){
	    tmp = tail->val;
	    delete(tail);
	    tail = head = nullptr;
	    len = 0;
	}else{
    	tmp = tail->val;
    	tail = tail->prev;
    	delete(tail->next);
    	tail->next = nullptr;
    	len--;
	}
	return tmp;
}

#endif /* MD_QUEUE_MD_QUEUE_H_ */
