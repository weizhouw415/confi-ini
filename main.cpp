#include <iostream>
#include <cstring>
#include "cfg_op.h"

#define LCDP_CMD_KEY_LEN 32
#define LCDP_CMD_BUF_LEN 32
#define LCDP_CMD_LEN 1024

int main() 
{
    const char *cfg_file = "cmd_config.ini";
    const char *sect = "freerdp";
    char *key_buf[LCDP_CMD_KEY_LEN] = {0};
    char lcdp_cmd[LCDP_CMD_LEN] = {0};

    for (int i = 0; i < LCDP_CMD_KEY_LEN; ++i) {
        key_buf[i] = new char[LCDP_CMD_BUF_LEN];
    }

    int cmd_num = ConfigGetKeys((char *)cfg_file, (char *)sect, (char **)key_buf);
    if (cmd_num < 0) {
        std::cout << "Config Get Keys Error!" << std::endl;
        return -1;
    }

    snprintf(lcdp_cmd, LCDP_CMD_LEN, "./x%s", sect);

    for (int i = 0; i < cmd_num; ++i) {
        if (strlen(key_buf[i]) == 0)
            break;
        strcat(lcdp_cmd, " ");
        strcat(lcdp_cmd, key_buf[i]);
        char cmd_buf[LCDP_CMD_BUF_LEN] = {0};
        int res = ConfigGetKey((char *)cfg_file, (char *)sect, key_buf[i], (char *)cmd_buf);
        if (res < 0)
            return -1;
        if (strlen(cmd_buf) != 0) {
            strcat(lcdp_cmd, ":");
            strcat(lcdp_cmd, cmd_buf);
        }
    }

    for (int i = 0; i < LCDP_CMD_KEY_LEN; ++i)
        delete[] key_buf[i];
    
    std::cout << lcdp_cmd << std::endl;

    return 0;
}