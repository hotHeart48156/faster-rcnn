from typing import List
from matplotlib import pyplot as plt
import numpy as np
import math
import  random
def gen_data():
    
    duty_data=[(math.sin(i)+random.randint(-5,5)) for i,j in enumerate(range(0,200))]
    data=[(math.sin(i))for i,j in enumerate(range(0,200))]
    return duty_data,data

def show_data(x,y):
    pass
    # fig=plt.figure()
    # ax1=fig.add_subplot(111)
    # ax1.plot(x,y,color="red")
    # plt.show()
class Filter(object):
    def __init__(self, data:List):
        super(Filter, self)
        self.data=data;
    def process_data(self):
        self.sig=0
        for index,dot in enumerate(self.data):
            self.sig<<1
            if self.data[index+1]>dot:
                self.sig=self.sig|1;
            if self.sig&0x7==7 or self.sig&0x7==0:
                if self.daoshu(dot,self.data[index+1],self.data[index+2]):
                    self.average(3)
                
                    
                
    def daoshu(self,dot1,dot2,dot3):
            daoshu1=dot2-dot1
            daoshu2=dot3-dot2
            if np.abs(daoshu2-daoshu1)/daoshu1>0.2:
                return 1
            return 0
    def average(self,num):
        tmp=sorted(self.data)
        for i in range(0,num+1):
            tmp.remove(tmp[0+i])
            tmp.remove(tmp[0-i])
        return sum(tmp)/len(tmp)
    
if __name__ =="__main__":
    data=gen_data()
    # filter=Filter(data[0])
    # print(len(data[1]))
    len=len(data[1])
    # print(range(0,len))
    # show_data(range(0,len),data[1])
    plt.xlabel("time")
    plt.ylabel("data")
    plt.title("title")
    line,=plt.plot([1,2,3],[1,2,3],color="r")
    line.set_color("black")
    plt.show()
    