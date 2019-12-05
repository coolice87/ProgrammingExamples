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


#define SC_LIST_NODE_NULL  NULL	/*�ڵ��*/

/* ����ͷ */
typedef struct SC_ListHead
{
	struct SC_ListHead *next;
	struct SC_ListHead *prev;
} SC_ListHead;


/* ����̬����ͳ�ʼ�� */
#define SC_LIST_HEAD(name) \
	SC_ListHead name = { &(name), &(name) }


/* ����̬��ʼ�� */
static inline void SC_listHeadInit(SC_ListHead *list)
{
	list->next = list;
	list->prev = list;
}


/* ͨ����ӳ�Ա�Ľӿڣ���ָ�����е�ǰ�ڵ�ͺ�ڵ㡣*/
static inline void __SC_listAdd(SC_ListHead *newList, SC_ListHead *prev, SC_ListHead *next)
{
	next->prev = newList;
	newList->next = next;
	newList->prev = prev;
	prev->next = newList;
}


/* ��ӳ�Ա�Ľӿڣ�head��nextָ���β��head��prevָ����һ��Ԫ�ء�*/
static inline void SC_listAdd(SC_ListHead *newList, SC_ListHead *head)
{
	__SC_listAdd(newList, head, head->next);
}


/* ��ӳ�Ա�Ľӿڣ�head��nextָ����һ��Ԫ�أ�head��prevָ���β��*/
static inline void SC_listAddTail(SC_ListHead *newList, SC_ListHead *head)
{
	__SC_listAdd(newList, head->prev, head);
}


/* ��������ɾ����Ա��ͨ�ýӿڣ�ָ���ó�Ա�Ķ�ͷ�Ͷ�β��*/
static inline void __SC_listDel(SC_ListHead * prev, SC_ListHead * next)
{
	next->prev = prev;
	prev->next = next;
}


/* ��������ɾ����Ա��ͨ�ýӿڣ�ָ���ó�Ա��*/
static inline void SC_listDel(SC_ListHead *entry)
{
	__SC_listDel(entry->prev, entry->next);
	entry->next = (SC_ListHead *)SC_LIST_NODE_NULL;
	entry->prev = (SC_ListHead *)SC_LIST_NODE_NULL;
}


/* �ж������Ƿ�Ϊ�յĽӿڡ�*/
static inline int SC_listEmpty(const SC_ListHead *head)
{
	return head->next == head;
}


/* ͨ�������Ա��ȡ�����ṹ����׵�ַ��*/ 
#define SC_listEntry(ptr, type, member) \
	SC_getStructHead(ptr, type, member)


/* �������������л�õĽڵ㲻�ɱ�ɾ����*/ 
#define SC_listForEach(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/* �������������л�õĽڵ�ɰ�ȫɾ����tmpΪ��ʱ�ڵ�ָ�롣*/
#define SC_listForEachSafe(pos, tmp, head) \
    for (pos = (head)->next, tmp = pos->next; pos != (head); \
         pos = tmp, tmp = pos->next)


#ifdef __cplusplus
}
#endif
    
    
#endif /* end __SC_LIST_H__ */
