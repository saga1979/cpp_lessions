#ifndef __DLINK_H__
#define __DLINK_H__

typedef struct _LiteList LiteList;

typedef int (*LIST_DATA_FUN)(void*);


LiteList*	dlist_new();

void		dlist_data_free_fun(LiteList*, LIST_DATA_FUN);
void		dlist_free(LiteList* );
LiteList*	dlist_remove(LiteList* , void* data);
/**
 * 在指定位置插入数据
 * 
 * @author Administrator (2016/10/10)
 * 
 * @param pos 要插入位置的索引
 * @param data 要插入的数据
 * 
 * @return LiteList*  链表对象
 */
LiteList*	dlist_insert_before(LiteList *, int pos, void *data);
LiteList*	dlist_insert_after(LiteList *, int pos, void *data);
LiteList*	dlist_append(LiteList* , void*data);
void*		dlist_data(LiteList*, int pos );
int			dlist_size(LiteList*);
void		dlist_foreach(LiteList*, LIST_DATA_FUN);

#endif
