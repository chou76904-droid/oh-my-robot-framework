#include "eventnotify.h"
#include "core/data_struct/corelist.h"
#include <string.h>

static LIST_HEAD(msg_head);

static LIST_HEAD(sub_head);

//static message_bus telecontrol;
message_bus telecontrol;

uint8_t message_publish(message_bus *bus,message *msg,const char *name)
{
    if(bus != NULL && msg != NULL && name != NULL)
    {
            strncpy(msg->name,name,MAX_NAME_SIZE - 1);
            msg->name[MAX_NAME_SIZE - 1] = '\0';
            list_add_tail(&msg->link,&bus->message);
            return 0;            
    }
}

void message_subscribe(message_bus *bus,subscriber *sub,const char *name,message_handler msghandler,void *context)
{
    if(bus && name != NULL && msghandler != NULL) 
    {
            sub->msghandler = msghandler;
            sub->context = context;
            strncpy(sub->name, name, MAX_NAME_SIZE - 1);
            sub->name[MAX_NAME_SIZE - 1] = '\0';
            list_add_tail(&sub->link,&bus->subscriber);
    }
}

uint8_t message_dispatch(message_bus *bus)
{
    subscriber *sub;
    message *msg;
    message *msg_next;

    if(bus == NULL)
    {
        return -1;
    }
    list_for_each_entry_safe(msg,msg_next,&bus->message,link)
    {
        list_for_each_entry(sub,&bus->subscriber,link)
        {
            if(strcmp(sub->name,msg->name) == 0)
            {
                sub->msghandler(msg,sub->context);
            }
        }
        list_del(&msg->link);
    }
}

uint8_t message_bus_register(message_bus *bus)//先拿遥控器驱动顶顶，回头换成通用的驱动。
{
    if(bus == NULL)
    {
        return -1;
    }
    INIT_LIST_HEAD(&bus->message);
    INIT_LIST_HEAD(&bus->subscriber);
}

void notify_bus_register(void)
{
    message_bus_register(&telecontrol);
}