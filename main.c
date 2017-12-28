#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void rele_on(char *data, int fd)
{
    data[0] = 0xA0;
    data[1] = 0x01;
    data[2] = 0x01;
    data[3] = 0xA2;

    write(fd, data, 4);
}

void rele_off(char *data, int fd)
{
    data[0] = 0xA0;
    data[1] = 0x01;
    data[2] = 0x00;
    data[3] = 0xA1;

    write(fd, data, 4);
}

int main(int argc, char *argv[])
{
    int fd;
    char data[4];
//проверка количества аргументов
    if( argc < 3 ){
        printf("Usage:\nrele_switch file_name on | off \n");
        exit(1);
    }
//проверка на существование файла
    if( (fd = open(argv[1], O_WRONLY, 0)) == -1){
        printf("error: can't open file %s\n", argv[1]);
        exit(1);
    }

    if( strcmp(argv[2],"on") == 0)
        rele_on(data, fd);
    else if(strcmp(argv[2],"off") == 0)
        rele_off(data, fd);
    else{
        printf("Usage:\nrele_switch file_name on | off \n");
        exit(1);
    }
    return 0;
}
