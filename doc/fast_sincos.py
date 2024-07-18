import curve_fit as curve_fit
import numpy as np
import sys
import sequences

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
    cols=evensfilt(curve_fit.polycols(x,2*K+1))
    c=list(cols)
    return curve_fit.lsq_fit(cols=c,y=y)

def fit_cosx(K=5):
    N=10000
    x=np.linspace(-1.0/8.0, 1.0/8.0, N)
    y=np.cos(x*np.pi*2.0)
    cols=evensfilt(curve_fit.polycols(x,2*K+1))
    c=list(cols)
    return curve_fit.lsq_fit(cols=c,y=y)



from scipy.special import erfinv
def fit_erfinv(K=5):
    N=1000
    x=np.linspace(0.0, 1.0, N)
    c=curve_fit.polycols(x,K)
    c=list(c)
    y=erfinv(x)
    return curve_fit.rational_fit(cols_numerator=c,cols_denominator=c,y=y)




def fit_erfinv_polyseq(K=5,N=1000,polyseq=None):
    x=curve_fit.closed_linspace(0.0, 1.0,N)
    bf=sequences.power_series_basis(polyseq)
    A=curve_fit.direct_zerofirst_fit(x=x,f=erfinv,zerofirst_basis_iterator=bf,M=K)
    print(A)


def square_fittable():
    return sequences.withzero(sequences.posneg(sequences.pot_rationals()))


fit_erfinv_polyseq(K=100,N=100,polyseq=square_fittable())