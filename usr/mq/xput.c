#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <time.h>
#include <signal.h>
#include <sys/msg.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <math.h>
#include <sys/ipc.h>
#include "mbp_head.h"

/******************************* �궨��****************************/
#define SYSTEM_VER "V3.000"
#define __INIFILE     "key.ini"        /*���������ļ���*/
#define __YDZFSVRNAME  "queuesvr"             /*ͨѶ������*/
/****************************** ������ ****************************/

char *fpath = "/home/mbp/file/xmq/q.xml";
char *QMName = "QM_EFSSV2_EFSS";
char *QName = "LQ.MSG.BMI.BANK";

void main(int argc, char *argv[])
{

    key_t sndmsgkey = 4550;                                            /*������Ϣ���м�ֵ*/
    key_t rcvmsgkey = 4552;                                         /*����Ӧ������Ϣ���м�ֵ*/
    int  iYlkResptimeout = 60, iCtrlMsgkey = 0;
    char cfgbuf[256], sport[20];
    char buffer[65535];
    int port, ret2;
    int ret;
    /**********************************˽�в���****************************/
    /* ������Ϣ���м�ֵ */
    memset(cfgbuf, 0, sizeof(cfgbuf));
    if (ExGetCfgItem(__INIFILE, "MQCOMM", "SNDMSGKEY", cfgbuf, sizeof(cfgbuf)) >= 0)
    {
        trim(cfgbuf);
        sndmsgkey = atoi(cfgbuf);
    }
    else
    {
        printf( "MQCOMM�ڵ���û��[%s]", "SNDMSGKEY");
        exit(-2);
    }
    /* ����Ӧ������Ϣ���м�ֵ */
    memset(cfgbuf, 0, sizeof(cfgbuf));
    if (ExGetCfgItem(__INIFILE, "MQCOMM", "RCVMSGKEY", cfgbuf, sizeof(cfgbuf)) >= 0)
    {
        trim(cfgbuf);
        rcvmsgkey = atoi(cfgbuf);
    }
    else
    {
        printf( "MQCOMM�ڵ���û��[%s]", "RCVMSGKEY");
        exit(-3);
    }
    
    printf( "sndmsgkey[%d]rcvmsgkey[%d]\n", sndmsgkey, rcvmsgkey);
    HandleQue( sndmsgkey, rcvmsgkey);
}

int HandleQue( key_t sndmsgkey, key_t rcvmsgkey)
{
    FILE *fp;
    int len;
    char buffer[MAX_PKG]={0};
    if((fp=fopen(fpath,"r"))==NULL)
    {
        fclose(fp);
        printf("open err\n");
    }
    if (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        len = strlen(buffer);       /* length without null        */
        if (buffer[len - 1] == '\n') /* last char is a new-line    */
        {
            buffer[len - 1]  = '\0';  /* replace new-line with null */
            --len;                    /* reduce buffer length       */
        }
    }
    int  sndmsgfd, rcvmsgfd,  iRet = 0;
    struct
    {
        mtyp_t mtype;
        char mtext[MAX_PKG];
    } msg;
    /*��ʼ��������Ϣ����*/
    if ((sndmsgfd = msgget(sndmsgkey, 0666 | IPC_CREAT)) < 0)
    {
        printf( "sndmsgkey[%d]errno[%d]\n", sndmsgkey, errno);
        return -1;
    }
    /*���͵���Ӧ��,����ͷ���,���ٲ�ѯ���ն���*/
    if ((rcvmsgfd = msgget(rcvmsgkey, 0666 | IPC_CREAT)) < 0)
    {
        printf( "rcvmsgkey[%d]errno[%d]\n", sndmsgkey, errno);
        return -1;
    }
    msg.mtype = getmsgkey(buffer + 0);
    msg.mtype = 10;
    memset(msg.mtext, 0, MAX_PKG);
    memcpy(msg.mtext, buffer, strlen(buffer));
    printf( "msg.mtext[%s]\n", msg.mtext);
    printf( "msg.mtype[%d][%d]\n", msg.mtype,sizeof(mtyp_t));
    printf( "sndmsgkey[%d]\n", sndmsgkey);
    /*iRet = msgsnd(sndmsgfd, &msg, sizeof(msg)-sizeof(mtyp_t), IPC_NOWAIT);*/
    iRet = msgsnd(sndmsgfd, &msg, strlen(buffer), IPC_NOWAIT);
    if (iRet < 0)
    {
        printf( "������Ϣ����[%d]ʧ��[%d][%s]\n", sndmsgkey, errno,strerror(errno));
        return -1;
    }
    return 0;
}
/******************************************************
���ܣ���ȡ8583��ϵͳ���ٺ���Ϊ��Ϣ���еļ�ֵ���ú�����
      �����ڽ�8583
������ͨѶ����
���أ����ĸ��ٺ�
*******************************************************/
int getmsgkey(char *buffer)
{
    char gzh[7];
    unsigned char b[2];
    int fdlen[11] = {8, 0, 6, 12, 12, 12, 10, 8, 8, 8};
    int ilen = 0, j = 0, i;
    char tmp[3];

    memset(tmp, 0, sizeof(tmp));
    ilen += 4;
    memcpy(b, buffer + ilen, 2);
    ilen += 8;
    for (i = 1; i < 11; i++)
    {
        if ((b[j] & 0x80) > 0)
        {
            if (fdlen[i - 1] == 0)
            {
                /*LLVAR*/
                memcpy(tmp, buffer + ilen, 2);
                ilen += (2 + atoi(tmp));
            }
            else ilen += fdlen[i - 1];
        }
        b[j] = b[j] << 1;
        if (i % 8 == 0) j++;
    }
    memset(gzh, 0, sizeof(gzh));
    memcpy(gzh, buffer + ilen, 6);
    return atoi(gzh);
}
