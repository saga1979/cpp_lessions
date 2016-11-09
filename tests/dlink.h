#ifndef __DLINK_H__
#define __DLINK_H__

typedef struct _LiteLink LiteLink;
typedef void(*DEL_FUN)(void*);


LiteLink*	dlink_new();
void		dlink_free(LiteLink* , DEL_FUN data_del_fun);
LiteLink*	dlink_remove_node(LiteLink* , LiteLink* node);
LiteLink*	dlink_remove_data(LiteLink* , void* data);
LiteLink*	dlink_insert_data(LiteLink *, int pos, void *data);
LiteLink*	dlink_append_data(LiteLink* , void*data);
LiteLink*	dlink_next(LiteLink* , int n);
void*		dlink_data(LiteLink* );

#endif
