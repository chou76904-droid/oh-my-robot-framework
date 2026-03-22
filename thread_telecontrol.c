#include "eventnotify.h"
#include "core/om_cpu.h"
#include "drivers/peripheral/serial/pal_serial_dev.h"
#include "oh-my-robot/lib/include/core/data_struct/corelist.h"
#include "osal/osal.h"
#include "osal/osal_time.h"
#include <string.h>

uint8_t test[5] = {1,2,3,4,5};
void msghanler(message *msg,void *context)
{
    context = msg->priv;
}

static subscriber test_sub = {
    .context = NULL,
    .link.next = NULL,
    .link.prev = NULL,
    .msghandler = msghanler, 
};

static message test_msg = 
{
    .data_len = 2,
    .link.next = NULL,
    .link.prev = NULL,
    .priv = test,
};

int main()
{

    notify_bus_register();
    message_publish(&telecontrol,&test_msg,"test");

    message_subscribe(&telecontrol,&test_sub,"test",msghanler,NULL);

    message_dispatch(&telecontrol);
}