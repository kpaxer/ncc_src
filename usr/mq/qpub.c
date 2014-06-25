#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/types.h>

#include "tool_msg.h"

struct _MsgBuf                  // ��Ϣ�ṹ��
{
    long mtype;                 // ��Ϣ����
    time_t tTime;               // ��Ϣʱ���
    char mtext[MSG_LEN];        // ��Ϣ����
};
typedef struct _MsgBuf MsgBuf;

/****
* DESCRIBE      : ����һ������
* RELEASE       : v1.0
* PROGRAMMER    : ���崨
* INPUT         : kKey          - ��ֵ
*               : iFlg          - ָ��msgget��������Ϊ
* OUTPUT        : ��
* RETURN        : >0            - ����ID
*               : -1004         - ������Ϣ����ʧ��
* ERROR         : ���ص��ú���
****/
int MsgGet(key_t kKey, int iFlg)
{
    int iMsgQueueID;
    
    iMsgQueueID = msgget(kKey, iFlg);
    if (iMsgQueueID < 0)
    {
        printf("������Ϣ����ʧ�ܣ�\n");
        return -1004;
    }
    
    return iMsgQueueID;
}

/****
* DESCRIBE      : ��һ���µ���Ϣд�����
* RELEASE       : v1.0
* PROGRAMMER    : ���崨
* INPUT         : iMsgQueueID   - ����ID
*               : pstUsrMsgBuf  - �û���Ϣָ��
*               : iLen          - ��Ϣ����
*               : iFlg          - ָ��msgsnd��������Ϊ
* OUTPUT        : ��
* RETURN        : 0             - ����
*               : -1001         - ��Ϣ����
*               : ����          - д��Ϣʧ��
* ERROR         : ���ص��ú���
****/
int MsgSnd(int iMsgQueueID, UsrMsgBuf* pstUsrMsgBuf, size_t sLen, int iFlg)
{
    int iRet;                   // ����ֵ

    MsgBuf stMsgBuf;            // ��Ϣ�ṹ��

    iRet = 0;
    memset(&stMsgBuf, 0, sizeof(MsgBuf));

    if (sLen >= MSG_LEN)
    {
        printf("��Ϣ������\n");
        return -1001;
    }

    // ȡ��ʱ���
    time(&stMsgBuf.tTime);

    snprintf(stMsgBuf.mtext, sizeof(stMsgBuf.mtext), "%s", pstUsrMsgBuf->mtext);
    stMsgBuf.mtype = pstUsrMsgBuf->mtype;
    sLen += sizeof(time_t);

    iRet = msgsnd(iMsgQueueID, &stMsgBuf, sLen, iFlg);
    if (0 != iRet)
    {
        printf("��Ϣд�����ʧ�ܣ�\n");
        return iRet;
    }

    return iRet;
}

/****
* DESCRIBE      : ����Ϣ�����ж���Ϣ
* RELEASE       : v1.0
* PROGRAMMER    : ���崨
* INPUT         : iMsgQueueID   - ����ID
*               : pstUsrMsgBuf  - �û���Ϣָ��
*               : sMaxLen       - ��Ϣ��󳤶�
*               : lType         - ָ��msgrcv������ȡ��Ϣ�Ĳ�������
*               : iFlg          - ָ��msgsnd��������Ϊ
* OUTPUT        : pstUsrMsgBuf  - �û���Ϣָ��
* RETURN        : 0             - ����
*               : -1002         - ������û�з�����������Ϣ
*               : -1003         - ����msgrcv��������
* ERROR         : ���ص��ú���
****/
int MsgRcv(int iMsgQueueID, UsrMsgBuf* pstUsrMsgBuf, size_t sMaxLen, long lType, int iFlg)
{
    int iLen;                   // ��Ϣ����

    MsgBuf stMsgBuf;            // ��Ϣ�ṹ��

    iLen = 0;
    memset(&stMsgBuf, 0, sizeof(MsgBuf));

    if ((iLen = msgrcv(iMsgQueueID, (void*)&stMsgBuf, sMaxLen, lType, iFlg)) > 0)
    {
        pstUsrMsgBuf->mtype = stMsgBuf.mtype;
        snprintf(pstUsrMsgBuf->mtext, sizeof(pstUsrMsgBuf->mtext), "%s", stMsgBuf.mtext);
    }
    else if (0 == iLen)
    {
        printf("�ڶ�����û�з�����������Ϣ��\n");
        return -1002;
    }
    else
    {
        printf("����msgrcv��������\n");
        return -1003;
    }

    return 0;
}
