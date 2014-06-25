/********************************************************************/
/*                                                                  */
/*   AMQSPUT0 has the following parameters                          */
/*       required:                                                  */
/*                 (1) The name of the target queue                 */
/*       optional:                                                  */
/*                 (2) Queue manager name                           */
/*                 (3) The open options                             */
/*                 (4) The close options                            */
/*                 (5) The name of the target queue manager         */
/*                 (6) The name of the dynamic queue                */
/*                                                                  */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* includes for MQI */
#include <cmqc.h>
char *fpath = "/home/mbp/file/xmq/mq.xml";
char *QMName = "QM_EFSSV2_EFSS";
char *QName = "LQ.MSG.BMI.BANK";
int main(int argc, char **argv)
{
    /*  Declare file and character for sample input                   */
    FILE *fp;

    /*   Declare MQI structures needed                                */
    MQOD     od = {MQOD_DEFAULT};    /* Object Descriptor             */
    MQMD     md = {MQMD_DEFAULT};    /* Message Descriptor            */
    MQPMO   pmo = {MQPMO_DEFAULT};   /* put message options           */
    /** note, sample uses defaults where it can **/

    MQHCONN  Hcon;                   /* connection handle             */
    MQHOBJ   Hobj;                   /* object handle                 */
    MQLONG   O_options;              /* MQOPEN options                */
    MQLONG   C_options;              /* MQCLOSE options               */
    MQLONG   CompCode;               /* completion code               */
    MQLONG   OpenCode;               /* MQOPEN completion code        */
    MQLONG   Reason;                 /* reason code                   */
    MQLONG   CReason;                /* reason code for MQCONN        */
    MQLONG   messlen;                /* message length                */
    char     buffer[1024*10];            /* message buffer                */
    //char     QMName[50];             /* queue manager name            */

    printf("Sample AMQSPUT0 start\n");

    /******************************************************************/
    /*                                                                */
    /*   Connect to queue manager                                     */
    /*                                                                */
    /******************************************************************/
    //QMName[0] = 0;    /* default */
    //strcpy(QMName, argv[2]);
    MQCONN(QMName,                  /* queue manager                  */
           &Hcon,                   /* connection handle              */
           &CompCode,               /* completion code                */
           &CReason);               /* reason code                    */

    /* report reason and stop if it failed     */
    if (CompCode == MQCC_FAILED)
    {
        printf("MQCONN ended with reason code %d\n", CReason);
        exit( (int)CReason );
    }

    /******************************************************************/
    /*                                                                */
    /*   Use parameter as the name of the target queue                */
    /*                                                                */
    /******************************************************************/
    strncpy(od.ObjectName, QName, (size_t)MQ_Q_NAME_LENGTH);
    printf("target queue is %s\n", od.ObjectName);

    /******************************************************************/
    /*                                                                */
    /*   Open the target message queue for output                     */
    /*                                                                */
    /******************************************************************/
    if (argc > 3)
    {
        O_options = atoi( argv[3] );
        printf("open  options are %d\n", O_options);
    }
    else
    {
        O_options = MQOO_OUTPUT            /* open queue for output     */
                    | MQOO_FAIL_IF_QUIESCING /* but not if MQM stopping   */
                    ;                        /* = 0x2010 = 8208 decimal   */
    }

    MQOPEN(Hcon,                      /* connection handle            */
           &od,                       /* object descriptor for queue  */
           O_options,                 /* open options                 */
           &Hobj,                     /* object handle                */
           &OpenCode,                 /* MQOPEN completion code       */
           &Reason);                  /* reason code                  */

    /* report reason, if any; stop if failed      */
    if (Reason != MQRC_NONE)
    {
        printf("MQOPEN ended with reason code %d\n", Reason);
    }

    if (OpenCode == MQCC_FAILED)
    {
        printf("unable to open queue for output\n");
    }

    /******************************************************************/
    /*                                                                */
    /*   Read lines from the file and put them to the message queue   */
    /*   Loop until null line or end of file, or there is a failure   */
    /*                                                                */
    /******************************************************************/
    CompCode = OpenCode;        /* use MQOPEN result for initial test */
    //fp = stdin;
    if ((fp = fopen(fpath, "r")) == NULL)
    {
        fclose(fp);
        printf("open err\n");
    }

    memcpy(md.Format,           /* character string format            */
           MQFMT_STRING, (size_t)MQ_FORMAT_LENGTH);

    /******************************************************************/
    /* Use these options when connecting to Queue Managers that also  */
    /* support them, see the Application Programming Reference for    */
    /* details.                                                       */
    /* These options cause the MsgId and CorrelId to be replaced, so  */
    /* that there is no need to reset them before each MQPUT          */
    /******************************************************************/
    /* pmo.Options |= MQPMO_NEW_MSG_ID;                               */
    /* pmo.Options |= MQPMO_NEW_CORREL_ID;                            */

    while (CompCode != MQCC_FAILED)
    {
        if (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            messlen = (MQLONG)strlen(buffer);       /* length without null        */
            if (buffer[messlen - 1] == '\n') /* last char is a new-line    */
            {
                buffer[messlen - 1]  = '\0';  /* replace new-line with null */
                --messlen;                    /* reduce buffer length       */
            }
        }
        else messlen = 0;        /* treat EOF same as null line         */

        /****************************************************************/
        /*                                                              */
        /*   Put each buffer to the message queue                       */
        /*                                                              */
        /****************************************************************/
        printf("messlen[%d]\n",messlen);
        printf("buffer[%s]\n",buffer);
        if (messlen > 0)
        {
            /**************************************************************/
            /* The following two statements are not required if the       */
            /* MQPMO_NEW_MSG_ID and MQPMO_NEW _CORREL_ID options are used */
            /**************************************************************/
            memcpy(md.MsgId,           /* reset MsgId to get a new one    */
                   MQMI_NONE, sizeof(md.MsgId) );

            memcpy(md.CorrelId,        /* reset CorrelId to get a new one */
                   MQCI_NONE, sizeof(md.CorrelId) );

            MQPUT(Hcon,                /* connection handle               */
                  Hobj,                /* object handle                   */
                  &md,                 /* message descriptor              */
                  &pmo,                /* default options (datagram)      */
                  messlen,             /* message length                  */
                  buffer,              /* message buffer                  */
                  &CompCode,           /* completion code                 */
                  &Reason);            /* reason code                     */

            /* report reason, if any */
            if (Reason != MQRC_NONE)
            {
                printf("MQPUT ended with reason code %d\n", Reason);
            }
        }
        else   /* satisfy end condition when empty line is read */
            CompCode = MQCC_FAILED;
    }

    /******************************************************************/
    /*                                                                */
    /*   Close the target queue (if it was opened)                    */
    /*                                                                */
    /******************************************************************/
    if (OpenCode != MQCC_FAILED)
    {
        if (argc > 4)
        {
            C_options = atoi( argv[4] );
            printf("close options are %d\n", C_options);
        }
        else
        {
            C_options = MQCO_NONE;        /* no close options             */
        }

        MQCLOSE(Hcon,                   /* connection handle            */
                &Hobj,                  /* object handle                */
                C_options,
                &CompCode,              /* completion code              */
                &Reason);               /* reason code                  */

        /* report reason, if any     */
        if (Reason != MQRC_NONE)
        {
            printf("MQCLOSE ended with reason code %d\n", Reason);
        }
    }

    /******************************************************************/
    /*                                                                */
    /*   Disconnect from MQM if not already connected                 */
    /*                                                                */
    /******************************************************************/
    if (CReason != MQRC_ALREADY_CONNECTED)
    {
        MQDISC(&Hcon,                   /* connection handle            */
               &CompCode,               /* completion code              */
               &Reason);                /* reason code                  */

        /* report reason, if any     */
        if (Reason != MQRC_NONE)
        {
            printf("MQDISC ended with reason code %d\n", Reason);
        }
    }

    /******************************************************************/
    /*                                                                */
    /* END OF AMQSPUT0                                                */
    /*                                                                */
    /******************************************************************/
    printf("Sample AMQSPUT0 end\n");
    fclose(fp);
    return (0);
}
