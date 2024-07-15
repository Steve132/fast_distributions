import vandermonde_fit
import numpy as np
import numpy as np
import sys

# Set numpy print options
np.set_printoptions(threshold=sys.maxsize,linewidth=1000)

def evensfilt(it):
    for i,v in enumerate(it):
        if(i % 2 == 0):
            yield v

def fit_sinxoverx(K=5):
    N=1000
    x=np.linspace(-1.0/8.0, 1.0/8.0, N)
    y=np.sin(x*np.pi*2.0)/x
    cols=evensfilt(vandermonde_fit.polycols(x,2*K+1))
    c=list(cols)
    return vandermonde_fit.lsq_fit(cols=c,y=y)

def fit_cosx(K=5):
    N=10000
    x=np.linspace(-1.0/8.0, 1.0/8.0, N)
    y=np.cos(x*np.pi*2.0)
    cols=evensfilt(vandermonde_fit.polycols(x,2*K+1))
    c=list(cols)
    return vandermonde_fit.lsq_fit(cols=c,y=y)

from scipy.special import erfinv
def fit_erfinv(K=5):
    N=1000
    x=np.linspace(0.0, 1.0, N)
    c=vandermonde_fit.polycols(x,K)
    c=list(c)
    y=erfinv(x)
    return vandermonde_fit.rational_fit(cols_numerator=c,cols_denominator=c,y=y)

for k in range(1,9):
#    print(('sin(x)/x',k,fit_sinxoverx(k)))
    print(('cos(x)',k,fit_cosx(k)))

#print(('erfinv(x)',5,fit_erfinv(5)))
 
   


#this is a "reduce" instruction.
#