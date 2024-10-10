#include <stdio.h>
#include <stdlib.h>
#include <linux/ipc.h>
#include <linux/msg.h>

int main(int argv, char argc[])
{

printf("Начало программы\n");

int id;
key_t key;
int res, lenght;

/*структура сообщения*/
struct my_buf
{
long mtype;
/*произволльные поля очереди*/
int op_type;
int l_op;
int r_op;
} msg;

/*создаем IFC-ключ*/
key = ftok(".",'a');

/*создаем очередь или присоединяемся к уже существующей*/
if((id = msgget(key,IPC_CREAT | 0660)) == -1)
{
printf("ошибка при создании очереди\n");
exit(1);
}

/*формируем сообщение*/
msg.mtype = 1;
msg.op_type = 0;
msg.l_op = 5;
msg.r_op = 4;

/*отправить сообщение в очередь*/
lenght = sizeof(struct my_buf);

if((res = msgsnd(id,&msg,lenght,0)) == -1)
{
printf("ошибка при постановке сообщения в очередь\n");
exit(1);
}


return 0;
}


