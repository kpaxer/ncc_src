start { 
    xnbk_P0013M_succ.log
    pfname[/home/mbp/simpre/msg/sim.cfg]
    port :[33001] len :[4] mbp_offset:[0]
    mbp_ip[192.168.3.115]
    connecting.......
    send data[P0013MINT*DMY   N                    01002013102903552947                        5                                  赖雅娟                                                                    5                                  赖雅娟                                                        1                                                                            0                0                00                1赖雅娟                             赖雅娟                             697245160442D7A96407675828AE*CLR                      ]
    headbuf[0541]
    recv data[022441001  N                        流水操作：更新核心流水表失败                                                                                                                                                                ]ret[220]
    nbk_P0013M
    xnbk_P0013M_succ.log
} end 

start { 
    xnbk_P0015M_succ.log
    pfname[/home/mbp/simpre/msg/sim.cfg]
    port :[33001] len :[4] mbp_offset:[0]
    mbp_ip[192.168.3.115]
    connecting.......
    send data[P0015MINT*DMY   N                    01002013052003247579                        5                                  赖雅娟                                                                    5                                  赖雅娟                                                        20                                                                           0                0                00                1赖雅娟                             赖雅娟                             9539683339460D66BC94192BAFF8*CLR            ]
    headbuf[0531]
    recv data[0224PAY2000N                        组件处理：组件[DATA_EnumConv]执行失败                                                                                                                                                       ]ret[220]
    nbk_P0015M
    xnbk_P0015M_succ.log
} end 

start { 
    xnbk_P0021M_succ.log
    pfname[/home/mbp/simpre/msg/sim.cfg]
    port :[33001] len :[4] mbp_offset:[0]
    mbp_ip[192.168.3.115]
    connecting.......
    send data[P0012MINT*DMY  N                     20140101201404016222750103029921                   13732918286    70          ]
    headbuf[0115]
    recv data[0032FIN0000YBOSS_20140611163106.]ret[28]
    nbk_P0021M
    xnbk_P0021M_succ.log
} end 

start { 
    xnbk_P0025M_succ.log
    pfname[/home/mbp/simpre/msg/sim.cfg]
    port :[33001] len :[4] mbp_offset:[0]
    mbp_ip[192.168.3.115]
    connecting.......
    send data[P0025MINT*DMY   N                             6222750103772348                   360103197504084120  ]               ]
    headbuf[0117]
    recv data[022499999  N                        与第三方通讯失败                                                                                                                                                                            ]ret[220]
    nbk_P0025M
    xnbk_P0025M_succ.log
} end 

start { 
    xnbk_P0060M_succ.log
    pfname[/home/mbp/simpre/msg/sim.cfg]
    port :[33001] len :[4] mbp_offset:[0]
    mbp_ip[192.168.3.115]
    connecting.......
    send data[P0060MINT*DMY   N                    10210003                  6222750103772348]
    headbuf[0079]
    recv data[0224PAY9998N                        煤气公司通讯出错                                                                                                                                                                            ]ret[220]
    nbk_P0060M
    xnbk_P0060M_succ.log
} end 

start { 
    xnbk_P0061M_succ.log
    pfname[/home/mbp/simpre/msg/sim.cfg]
    port :[33001] len :[4] mbp_offset:[0]
    mbp_ip[192.168.3.115]
    connecting.......
    send data[P0061MINT*DMY   N                    10210002                   6222750106091027]
    headbuf[0080]
    recv data[0224PAY9998N                        煤气公司通讯出错                                                                                                                                                                            ]ret[220]
    nbk_P0061M
    xnbk_P0061M_succ.log
} end 

start { 
    xnbk_P0063M_succ.log
    pfname[/home/mbp/simpre/msg/sim.cfg]
    port :[33001] len :[4] mbp_offset:[0]
    nbk_P0063M
    xnbk_P0063M_succ.log
} end 

