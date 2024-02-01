/*
 * new.h
 *
 *  Created on: Jan 30, 2024
 *      Author: aser_
 */

#ifndef MD_QUEUE_NEW_H_
#define MD_QUEUE_NEW_H_

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void * ptr);
void operator delete[](void * ptr);


#endif /* MD_QUEUE_NEW_H_ */
