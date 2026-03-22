#include "telecontrol_parser.h"
#include "oh-my-robot/lib/include/core/data_struct/corelist.h"
#include "string.h"


static LIST_HEAD(telecontrolparser_list);


static telecontrolparseroperation dji_ = {
    .parse_frame = dji_parser_frame,
    //.reset = telecontrol_parser_reset,
};

static telecontrolparser djiparser = {
    .ops = &dji_,
    .map = {0,0,0,0,0},
    .name = "dji",
};

int telecontrolparser_register(telecontrolparser *tcp)
{
    if(tcp == NULL)
    {
        return -1;
    }
        list_add_tail(&tcp->link,&telecontrolparser_list);

        return 0;
}

telecontrolparser *parser_find(char *name)
{
    telecontrolparser *temp;
    list_for_each_entry(temp,&telecontrolparser_list,link)
    {
        if(strcmp(temp->name,name))
        {
            return temp;
        }
    }
    return NULL;
}

void telecontrol_register(void)
{
    telecontrolparser_register(&djiparser);
}




TelecontrolParseStatus dji_parser_frame(telecontrolparser *parser,void *data,size_t len,telecontrol_map *out)
{
        telecontroldji djidata = {.ch = {0,0,0,0},  
                               .keyboard = 0,
                               .mouse = {0,0,0,0,0},
                               .sw = {0,0},};

        static telecontroldji lastdata;
        uint8_t *temp = (uint8_t *)data;

        djidata.ch[0] = (temp[0] | temp[1] << 8) & 0x07ff - 1024;

        djidata.ch[1] = (temp[1] >> 3 | temp[2] << 5) & 0x7ff - 1024;

        djidata.ch[2] = (temp[2] >> 6 | temp[3] << 2 | temp[4] << 10) & 0x7ff - 1024;

        djidata.ch[3] = (temp[4] >> 1| temp[5] << 7) & 0x7ff - 1024;
        //此处放消除过小信号的处理。
        djidata.sw[0] = (temp[5] >> 4) & 0x0c;
        djidata.sw[1] = (temp[5] >> 6) & 0x0c;

        djidata.mouse.x = (temp[6] | temp[7] << 8);
        djidata.mouse.y = (temp[8] | temp[9] << 9);
        djidata.mouse.z = (temp[10] | temp[11] << 10);

        djidata.mouse.left = temp[12];

        djidata.mouse.right = temp[13];

        djidata.keyboard = (temp[14] | temp[15] <<8);

        if(memcmp(&djidata,&lastdata,sizeof(telecontroldji)) == 0)//儅數據完全沒有變化時不進行映射。
        {
            return 0;
        }
            *out = dji_data_map(&djidata);
}

telecontrol_map dji_data_map(void *rawdata)
{
    telecontrol_map temp;
    telecontroldji *djidata = (telecontroldji *)rawdata;
    if(djidata->ch[0])
    {
        temp.move_x = (float)djidata->ch[0]/660;
    }
    if(djidata->ch[1])
    {
        temp.move_y = (float)djidata->ch[1]/660;
    }
    if(djidata->ch[2])
    {
        temp.move_yam = (float)djidata->ch[2]/660;
    }
    if(djidata->ch[3])
    {
        temp.move_pit = (float)djidata->ch[3]/660;
    }
    static uint8_t lastsw[2] ={0,0};
    switch (djidata->sw[0])
    {
    case swup :
        break;
    case swmid :
        break;
    case swdown :
        break;
    }
}