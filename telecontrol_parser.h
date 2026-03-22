#ifndef _TELECONTROL_PARSER_H
#define _TELECONTROL_PARSER_H

#include "oh-my-robot/lib/include/core/data_struct/corelist.h"
#include "telecontrol_types.h"


typedef struct telecontrolparser telecontrolparser;

typedef struct
{
    TelecontrolParseStatus (*parse_frame)(telecontrolparser *parser,
                                          void *data,
                                          size_t len
                                         ,telecontrol_map *out);//执行解包。
}telecontrolparseroperation;



typedef struct telecontrolparser
{
    const telecontrolparseroperation  *ops;//内挂解包使用的函数。
    ListHead link;
    char *name;
    telecontrol_map map;
}telecontrolparser;

void telecontrol_register(void);//注冊所有使用的驅動。

void telecontrol_parser_reset(telecontrolparser *parser);

telecontrolparser *telecontrol_parser_find(char *name);//尋找注冊表内的驅動，

int telecontrolparser_register(telecontrolparser *tcp);//注冊驅動，在init裏調用

TelecontrolParseStatus dji_parser_frame(telecontrolparser *parser,void *data,size_t len,telecontrol_map *out);//dji的特有解包

telecontrol_map dji_data_map(void *rawdata);//dji的映射。

#endif
