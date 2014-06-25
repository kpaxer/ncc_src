#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/types.h>

#include "tool_msg.h"

struct _MsgBuf                  // 消息结构体
{
    long mtype;                 // 消息类型
    time_t tTime;               // 消息时间戳
    char mtext[MSG_LEN];        // 消息内容
};
typedef struct _MsgBuf MsgBuf;

/****
* DESCRIBE      : 创建一个队列
* RELEASE       : v1.0
* PROGRAMMER    : 周彦川
* INPUT         : kKey          - 键值
*               : iFlg          - 指明msgget函数的行为
* OUTPUT        : 无
* RETURN        : >0            - 队列ID
*               : -1004         - 创建消息队列失败
* ERROR         : 返回调用函数
****/
int MsgGet(key_t kKey, int iFlg)
{
    int iMsgQueueID;
    
    iMsgQueueID = msgget(kKey, iFlg);
    if (iMsgQueueID < 0)
    {
        printf("创建消息队列失败！\n");
        return -1004;
    }
    
    return iMsgQueueID;
}

/****
* DESCRIBE      : 将一个新的消息写入队列
* RELEASE       : v1.0
* PROGRAMMER    : 周彦川
* INPUT         : iMsgQueueID   - 队列ID
*               : pstUsrMsgBuf  - 用户消息指针
*               : iLen          - 消息长度
*               : iFlg          - 指明msgsnd函数的行为
* OUTPUT        : 无
* RETURN        : 0             - 正常
*               : -1001         - 消息超长
*               : 其他          - 写消息失败
* ERROR         : 返回调用函数
****/
int MsgSnd(int iMsgQueueID, UsrMsgBuf* pstUsrMsgBuf, size_t sLen, int iFlg)
{
    int iRet;                   // 返回值

    MsgBuf stMsgBuf;            // 消息结构体

    iRet = 0;
    memset(&stMsgBuf, 0, sizeof(MsgBuf));

    if (sLen >= MSG_LEN)
    {
        printf("消息超长！\n");
        return -1001;
    }

    // 取得时间戳
    time(&stMsgBuf.tTime);

    snprintf(stMsgBuf.mtext, sizeof(stMsgBuf.mtext), "%s", pstUsrMsgBuf->mtext);
    stMsgBuf.mtype = pstUsrMsgBuf->mtype;
    sLen += sizeof(time_t);

    iRet = msgsnd(iMsgQueueID, &stMsgBuf, sLen, iFlg);
    if (0 != iRet)
    {
        printf("消息写入队列失败！\n");
        return iRet;
    }

    return iRet;
}

/****
* DESCRIBE      : 从消息队列中读消息
* RELEASE       : v1.0
* PROGRAMMER    : 周彦川
* INPUT         : iMsgQueueID   - 队列ID
*               : pstUsrMsgBuf  - 用户消息指针
*               : sMaxLen       - 消息最大长度
*               : lType         - 指定msgrcv函数读取消息的操作类型
*               : iFlg          - 指明msgsnd函数的行为
* OUTPUT        : pstUsrMsgBuf  - 用户消息指针
* RETURN        : 0             - 正常
*               : -1002         - 队列中没有符合条件的消息
*               : -1003         - 调用msgrcv函数出错
* ERROR         : 返回调用函数
****/
int MsgRcv(int iMsgQueueID, UsrMsgBuf* pstUsrMsgBuf, size_t sMaxLen, long lType, int iFlg)
{
    int iLen;                   // 消息长度

    MsgBuf stMsgBuf;            // 消息结构体

    iLen = 0;
    memset(&stMsgBuf, 0, sizeof(MsgBuf));

    if ((iLen = msgrcv(iMsgQueueID, (void*)&stMsgBuf, sMaxLen, lType, iFlg)) > 0)
    {
        pstUsrMsgBuf->mtype = stMsgBuf.mtype;
        snprintf(pstUsrMsgBuf->mtext, sizeof(pstUsrMsgBuf->mtext), "%s", stMsgBuf.mtext);
    }
    else if (0 == iLen)
    {
        printf("在队列中没有符合条件的消息。\n");
        return -1002;
    }
    else
    {
        printf("调用msgrcv函数出错！\n");
        return -1003;
    }

    return 0;
}
