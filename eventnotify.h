#ifndef _EVENTNOTIFY_H
#define _EVENTNOTIFY_H
#include "core/data_struct/corelist.h"
#define MAX_NAME_SIZE 30//規定最長的消息名。


typedef struct message message;

typedef struct subscriber subscriber;

typedef void(*message_handler)(message *msg,void *context);

typedef struct subscriber
{
    char name[MAX_NAME_SIZE];
    void *context;
    message_handler msghandler;
    ListHead link;
}subscriber;

typedef struct message
{
    char name[MAX_NAME_SIZE];
    void *priv;//私有值。
    uint8_t data_len;    
    ListHead link;
}message;

typedef struct message_bus
{
    ListHead message;
    ListHead subscriber;
}message_bus;//用于定义一大类的消息，例如遥控，陀螺仪，底盘。

uint8_t message_publish(message_bus *bus,message *msg,const char *name);

void message_subscribe(message_bus *msg,subscriber *sub,const char *name,message_handler msghandler,void *context);

uint8_t message_dispatch(message_bus *bus);//处理所有被订阅的消息。

uint8_t message_bus_register(message_bus *bus);

void notify_bus_register(void);

extern message_bus telecontrol;//调试用。
#endif
