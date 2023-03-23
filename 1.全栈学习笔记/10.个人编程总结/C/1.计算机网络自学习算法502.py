#数据与源主机相连
class datas:#从源主机发给目的主机的数据
        
    #要发送的目的主机的mac地址
    destinatinmac=""
    #发送的数据内容
    content=""
    #方法用来处理不同主机要发送的不同数据
    def __init__(self):
        self.destinatinmac=input("请输入数据的目标mac地址：")
        self.content=input("请输入要发送的内容：")
        print("数据类************执行成功！\n")
    
#主机与中心交换机相连,三个主机的目的接口分别为1 2 3
class hosts:#主机类
    data=""
    macip=None
    desinterface=None
    #主机通过线路两端的接口与交换机相连，主机端的默认接口为0
    def __init__(self,interface):#不同主机不同目的接口
        self.desinterface=interface
        self.macip=input("请输入主机的mac地址：")
        print("主机类************执行成功！\n")
    
    #方法函数用于向交换机的指定端口发送数据，并让交换机暂存
    def send_to_switch(self):
        self.data=datas()
        return self.data
		
#计算机网络自学习算法
#一个交换机，交换机中有交换表初始时是空的
#三个主机host1、host2、host3
#三个主机分别连接到该交换机switc上，其对应接口为1、2、3
#主机是一个对象一共三个主机
#交换机也是一个对象其中有一个属性为交换表一个方法进行转发和三个接口属性

class switches:#交换机类
    #switch_list={"源主机mac地址":['host1','host2','host3'],"接口":[1,2,3]}  #交换表属性，其类型属于字典
    switch_list={"mac地址":[],"接口":[]}#初始时为空
    
    def newhosts(self):
        print("创建与交换机相连的三台主机：")
        self.host1=hosts(1)
        self.host2=hosts(2)
        self.host3=hosts(3)
        return [self.host1,self.host2,self.host3]#返回三台主机地址
    
    #交换机类的方法函数，用于将数据帧、数据报或分租转发给指定主机处理
    def send_destinatin_hosts(self,d,sourecehost):#host为当前发送数据给交换机的主机
        #先判断交换表是否为空
        if len(self.switch_list["mac地址"])==0 and len(self.switch_list["接口"])==0:#交换表为空时全站广播
        #任选其二皆可
        #传送数据的目标mac地址若与某一主机的mac地址相等则发送并接收，host主机为发送数据所在的主机接口其不能与要广播或转发的接口对应的主机一致
            #匹配host1
            if self.host1.macip==d.destinatinmac and self.host1.macip!=sourecehost.macip:
                self.host1.data=d.content
                self.switch_list["mac地址"].append(sourecehost.macip)
                self.switch_list["接口"].append(sourecehost.desinterface)
                print("交换表为：{}".format(self.switch_list))
                print("主机host1接收成功！\n")
            else:
                #           当前主机不是源主机          且       当前主机不是目的主机
                if self.host1.macip!=sourecehost.macip:
                    print("广播后主机host1拒收！\n")
                             
            #匹配host2    
            if self.host2.macip==d.destinatinmac and self.host2.macip!=sourecehost.macip:
                self.host2.data=d.content
                self.switch_list["mac地址"].append(sourecehost.macip)
                self.switch_list["接口"].append(sourecehost.desinterface)
                print("交换表为：{}".format(self.switch_list))
                print("主机host2接收成功！\n")
            else:
                if self.host2.macip!=sourecehost.macip:
                    print("广播后主机host2拒收！\n")
                              
            #匹配host3
            if self.host3.macip==d.destinatinmac and self.host3.macip!=sourecehost.macip:
                self.host3.data=d.content
                self.switch_list["mac地址"].append(sourecehost.macip)
                self.switch_list["接口"].append(sourecehost.desinterface)
                print("交换表为：{}".format(self.switch_list))
                print("主机host3接收成功！\n")
            else:
                if self.host3.macip!=sourecehost.macip:
                    print("广播后主机host3拒收！\n")
                    
        #若交换表不为空则遍历交换表对比是否有与所发数据目的地址一致的mac地址
        else:
            flag=0#初始时假设交换表没有目的mac
            
            for i in range(0,len(self.switch_list["mac地址"])):
                if self.switch_list["mac地址"][i]==d.destinatinmac:#数据的目的地址若与交换表某行的mac地址匹配时跳转至该行mac地址对应的接口发送给该接口对应的主机
                    flag=1#交换表存在目的mac时标志量为1
                    
                    print("交换表中存在目的mac，故通过交换表中的接口{}转发".format(self.switch_list["接口"][i]))
                    #若交换表中存在目标mac时，则直接转发，并将源mac加入交换表（但是必须得事前判断源mac在不在mac表中）
                    
                    #然后将data发送给目的主机
                    if self.switch_list["接口"][i]==self.host1.desinterface:
                        self.host1.data=sourecehost.data
                        print("数据成功传输至：{}主机".format(self.host1.macip))
                    elif self.switch_list["接口"][i]==self.host2.desinterface:
                        self.host2.data=sourecehost.data
                        print("数据成功传输至：{}主机".format(self.host2.macip))
                    elif self.switch_list["接口"][i]==self.host3.desinterface:
                        self.host3.data=sourecehost.data
                        print("数据成功传输至：{}主机".format(self.host3.macip))
                    
                    if sourecehost.macip not in self.switch_list["mac地址"]:#前者的值不在后者里面，就将前者加入后者
                        self.switch_list["mac地址"].append(sourecehost.macip)
                        self.switch_list["接口"].append(sourecehost.desinterface)
                        #然后将data发送给目的主机
                        
                        print("交换表为：{}".format(self.switch_list))
                        print("已经将源mac：{}加入交换表".format(sourecehost.macip))
                    #通过接口获取主机并发送消息
                    break
            if flag==0:#标志量为0时表示mac表中不存在数据的目的mac地址，要向其它主机广播
                
                #准备广播
                #          当前主机==目的主机         且         目的主机！=源主机   
                if self.host1.macip==d.destinatinmac and self.host1.macip!=sourecehost.macip:
                    print("给主机host1进行广播")
                    if sourecehost.macip not in self.switch_list["mac地址"]:
                        self.switch_list["mac地址"].append(sourecehost.macip)
                        self.switch_list["接口"].append(sourecehost.desinterface)
                        #然后将data发送给目的主机
                        self.host1.data=d.content
                        print("交换表为：{}".format(self.switch_list))
                        print("host1接收成功，并将源mac写入交换表！\n")
                    else:#源mac存在于交换表中
                        print("源mac：{}已存在，无需加入".format(sourecehost.macip))#已经建立自学习算法
                        print("通过接口：{}转发给mac为：{}的主机".format(self.host1.desinterface,self.host1.macip))
                        #然后将data发送给目的主机
                        self.host1.data=d.content
                        print("数据成功传输至：{}主机\n".format(self.host1.macip))
                #          当前主机不是目的主机          且       当前主机不是源主机
                elif self.host1.macip not in self.switch_list["mac地址"]:
                    if self.host1.macip!=d.destinatinmac and self.host1.macip!=sourecehost.macip:
                        print("mac地址不匹配,广播后主机host1拒收！\n")
                            
                    
                if self.host2.macip==d.destinatinmac and self.host2.macip!=sourecehost.macip:
                    #print("给主机host2进行广播")
                    if sourecehost.macip not in self.switch_list["mac地址"]:
                        self.switch_list["mac地址"].append(sourecehost.macip)
                        self.switch_list["接口"].append(sourecehost.desinterface)
                        #然后将data发送给目的主机
                        self.host2.data=d.content
                        print("交换表为：{}".format(self.switch_list))
                        print("host2接收成功，并将源mac写入交换表！\n")
                    else:#源mac存在于交换表中
                        print("源mac：{}已存在，无需加入".format(sourecehost.macip))#已经建立自学习算法
                        print("通过接口：{}转发给mac为：{}的主机".format(self.host2.desinterface,self.host2.macip))
                        #然后将data发送给目的主机
                        self.host2.data=d.content
                        print("数据成功传输至：{}主机\n".format(self.host2.macip))
                elif self.host2.macip not in self.switch_list["mac地址"]:
                    if self.host2.macip!=d.destinatinmac and self.host2.macip!=sourecehost.macip:
                        print("mac地址不匹配,广播后主机host2拒收！\n")
                        
                        
                if self.host3.macip==d.destinatinmac and self.host3.macip!=sourecehost.macip:
                    #一定得判断源主机是否存在于交换表中不存在就加入
                    #print("给主机host3进行广播")
                    if sourecehost.macip not in self.switch_list["mac地址"]: 
                        self.switch_list["mac地址"].append(sourecehost.macip)
                        self.switch_list["接口"].append(sourecehost.desinterface)
                        #然后将data发送给目的主机
                        self.host3.data=d.content
                        print("交换表为：{}".format(self.switch_list))
                        print("host3接收成功，并将源mac写入交换表！\n")
                    else:#源mac存在于交换表中
                        print("源mac：{}已存在，无需加入".format(sourecehost.macip))#已经建立自学习算法
                        print("通过接口：{}转发给mac为：{}的主机".format(self.host3.desinterface,self.host3.macip))
                        #然后将data发送给目的主机
                        self.host3.data=d.content
                        print("数据成功传输至：{}主机\n".format(self.host3.macip))
                elif self.host3.macip not in self.switch_list["mac地址"]:
                    if self.host3.macip!=d.destinatinmac and self.host3.macip!=sourecehost.macip:
                        print("mac地址不匹配,广播后主机host3拒收！\n")
                    
                    
                              
        
    
    #查看每一次转发的交换表中的数据变化
    def show_switch_list(self):
        print(self.switch_list)

#以上是主体程序
#####################jupyter中运行##################################################################################################################################################
#以下是测试语句

switch1=switches()#构建交换机
    
host123=switch1.newhosts()#构建主机并链接交换机

#host1---->0
#host2---->1
#host3---->2
hostname=input("请输入源mac地址：")
if hostname.lower()=='host1':
    i=0
elif hostname.lower()=='host2':
    i=1
elif hostname.lower()=='host3':
    i=2
#要发送数据的源主机，进行数据发送
data1=host123[i].send_to_switch()#数据由host123[0]（host1发送数据）----->host2


#########################

#路由表非空时前面的if语句不会执行
switch1.send_destinatin_hosts(data1,host123[i])#第二个参数是要发送数据的已经存在的主机


#每次调用这个语句防止路由表被替换

host123

switch1.show_switch_list()#输出路由表