/*
 * element.h
 *
 *  Created on: Jan 30, 2024
 *      Author: aser_
 */

#ifndef MD_QUEUE_ELEMENT_H_
#define MD_QUEUE_ELEMENT_H_

class element{
public:
	element(char value):val(value),prev(nullptr),next(nullptr){}
	char val;
	element * next;
	element * prev;
};



#endif /* MD_QUEUE_ELEMENT_H_ */
