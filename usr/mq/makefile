##########################################################################
# 项目名称:综合应用前置（MBP）项目
# 版    本:V1.0
# 操作系统:AIX4.3
# 文件描述:函数组件动态连接库通用MAKEFILE
# 数 据 库:
##########################################################################
include $(MBPSRCHOME)/etc/makefile.all
##########################################################################
MAKEUSAGE=makelist :\n\tsendbplat
CCFLAG=-I/usr/mqm/inc -G -qmkshrobj -q32
all:xqput  xmqput xput qsget
xput:xput.o
	${BACKUP_COMP}
	$(EC_LINK_COMMON)
xqput:xqput.o
	${BACKUP_COMP}
	$(EC_LINK_COMMON)
qsget:qsget.o
	${BACKUP_COMP}
	$(EC_LINK_COMMON)
xmqput:xmqput.o
	${BACKUP_COMP}
	$(LINK_TUXLCLI) ${LIB_CHANNEL} ${LIB_MBPBASE} ${LIB_TUXLCLI} $(MQINCDIR) $(SYSLIBFLAGS64) -lmqm -lmqmcs -lmqmzse -lmqz -L/usr/mqm/lib64 

clean:
	rm -rf *.o
	
