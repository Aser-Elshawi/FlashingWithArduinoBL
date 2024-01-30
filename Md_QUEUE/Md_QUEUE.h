/*
 * QUEUE.h
 *
 *  Created on: Jan 29, 2024
 *      Author: aser_
 */

#ifndef MD_QUEUE_MD_QUEUE_H_
#define MD_QUEUE_MD_QUEUE_H_

template <typename T>
class element{
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
	void enque(T val);
	T dequeue(void);
	int size(void)const { return this->len;}
private:
	int len;
	element<T> * head;
	element<T> * tail;

};



#endif /* MD_QUEUE_MD_QUEUE_H_ */
