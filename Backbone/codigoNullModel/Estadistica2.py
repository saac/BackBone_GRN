
import sys

import numpy as np
import pandas as pd
from scipy import stats, integrate
import seaborn as sns
import matplotlib.pyplot as plt
#from pylab import *

#from scipy.stats import norm
import scipy.stats as stats

#np.random.seed(sum(map(ord, "distributions")))
#plt.show()

#x = np.random.normal(size=1000)
#print len(x)
#sns.distplot(x);
#plt.show()

#def GetData(data):
    #X=[]
    #lineas = open(data).readlines()
    #for i in lineas:
        #valores  = i.split('\t')
        #X.append(valores[2])
        
    #return X

def GetData(data):
    X=[]
    H=[]
    lineas = open(data).readlines()
    for i in lineas:
        valores  = i.split('\t')
        X.append(valores[2])
    for i in X:
        H.append(float(i.strip()))
        
    #return sorted(H,reverse=True)
    return H


dataSanos = sys.argv[1]
dataEnfermos = sys.argv[2]

S = GetData(dataSanos)
E = GetData(dataEnfermos)



#print len(S)
#print len(E)

#for i in S:
    #print i
#print E

#plt.hist(S)
#plt.hist(S,normed=True)  

#std = np.std(S) 
#mean = np.mean(S)    
#plt.plot(norm.pdf(S,mean,std))

#sns.distplot(S)
#plt.show()




tau, p_value = stats.kendalltau(S, E)
print tau

sns.distplot(S,kde=False)
sns.distplot(E,kde=False)
plt.savefig('prueba2.pdf')
#plt.show()


#A = [1,2,3,4,5,6,7,8,9,10,11,12]
#B = [2,1,4,3,6,5,8,7,10,9,12,11]
#B2  = [12,2,3,4,5,6,7,8,9,10,11,1]
#tau, p_value = stats.kendalltau(A, B)
#print tau
#print p_value

#print h
#plt.hist(h,normed=True)  

#sns.distplot(h);
#plt.show()




#x = np.random.normal(size=1000)
#print len(x)
#sns.distplot(x);
#plt.show()