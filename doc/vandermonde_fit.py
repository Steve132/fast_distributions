import numpy as np

def lsq_fit(cols,y):
    At=np.array(cols)
    A=At.T
    
    x,res,_,_=np.linalg.lstsq(A,y)
    if(len(res)!=1):
        res=[0.0]
    return x,np.sqrt(res[0]/len(y))
    
def null_fit(cols):
    At=np.array(cols)
    A=At.T
    
    U,S,Vh=np.linalg.svd(A)
    sol=Vh[-1,:]
    return sol,S[-1]



def polycols(x,k):
    cx=np.ones_like(x)
    for j in range(k+1):
        yield np.array(cx)
        cx*=x
    
    
def rational_fit(cols_numerator,cols_denominator,y):
    cols_nf=np.array(cols_numerator).T
    cols_df=np.array(cols_denominator).T
    colsy=np.diag(y) @ cols_df
    A=np.hstack((cols_nf,colsy))
    
    # Remove rows with NaN values, inf values, or y is zero
    mask=np.isfinite(A).all(axis=1) & (y!=0.0)
    A=A[mask,:]
    
    coeffs,res=null_fit(A.T)
    
    p=len(cols_numerator)   
    cn,cd=coeffs[:p],coeffs[p:]
    
    yn=cols_nf[mask,:] @ cn
    yd=cols_df[mask,:] @ cd
    yf=yn/yd
    #mean error between y and yf
    res=np.mean(np.abs(y[mask]-yf))
    print(yn[::20])
    print(yd[::20])
    print(y[::20])
    return cn,cd,res
    
