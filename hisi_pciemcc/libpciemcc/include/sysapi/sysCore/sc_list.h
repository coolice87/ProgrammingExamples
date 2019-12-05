/***********************************************************************
  * Copyright (c) 2016, HzGosun Co.,Ltd. All rights reserved.
  *
  * Description: sc_list.h 
  * Revisions  : Created on 2017-06-12
  * Author: xu_longfei
  *
  **********************************************************************/

#ifndef __SC_LIST_H__
#define __SC_LIST_H__


#ifdef __cplusplus
extern "C" {
#endif


#define SC_LIST_NODE_NULL  NULL	/*节点空*/

/* 链表头 */
typedef struct SC_ListHead
{
	struct SC_ListHead *next;
	struct SC_ListHead *prev;
} SC_ListHead;


/* 链表静态定义和初始化 */
#define SC_LIST_HEAD(name) \
	SC_ListHead name = { &(name), &(name) }


/* 链表动态初始化 */
static inline void SC_listHeadInit(SC_ListHead *list)
{
	list->next = list;
	list->prev = list;
}


/* 通用添加成员的接口，需指定队列的前节点和后节点。*/
static inline void __SC_listAdd(SC_ListHead *newList, SC_ListHead *prev, SC_ListHead *next)
{
	next->prev = newList;
	newList->next = next;
	newList->prev = prev;
	prev->next = newList;
}


/* 添加成员的接口，head的next指向队尾，head的prev指向下一个元素。*/
static inline void SC_listAdd(SC_ListHead *newList, SC_ListHead *head)
{
	__SC_listAdd(newList, head, head->next);
}


/* 添加成员的接口，head的next指向下一个元素，head的prev指向队尾。*/
static inline void SC_listAddTail(SC_ListHead *newList, SC_ListHead *head)
{
	__SC_listAdd(newList, head->prev, head);
}


/* 从链表中删除成员的通用接口，指定该成员的队头和队尾。*/
static inline void __SC_listDel(SC_ListHead * prev, SC_ListHead * next)
{
	next->prev = prev;
	prev->next = next;
}


/* 从链表中删除成员的通用接口，指定该成员。*/
static inline void SC_listDel(SC_ListHead *entry)
{
	__SC_listDel(entry->prev, entry->next);
	entry->next = (SC_ListHead *)SC_LIST_NODE_NULL;
	entry->prev = (SC_ListHead *)SC_LIST_NODE_NULL;
}


/* 判断链表是否为空的接口。*/
static inline int SC_listEmpty(const SC_ListHead *head)
{
	return head->next == head;
}


/* 通过链表成员获取包裹结构体的首地址。*/ 
#define SC_listEntry(ptr, type, member) \
	SC_getStructHead(ptr, type, member)


/* 遍历链表，过程中获得的节点不可被删除。*/ 
#define SC_listForEach(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/* 遍历链表，过程中获得的节点可安全删除。tmp为临时节点指针。*/
#define SC_listForEachSafe(pos, tmp, head) \
    for (pos = (head)->next, tmp = pos->next; pos != (head); \
         pos = tmp, tmp = pos->next)


#ifdef __cplusplus
}
#endif
    
    
#endif /* end __SC_LIST_H__ */
