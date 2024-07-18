import numpy as np
from scipy.optimize import linprog

def max_sparsity_vector(orthonormal_vectors):
    # Number of orthonormal vectors (columns) and their dimension (rows)
    
    m, n = orthonormal_vectors.shape
    
    A=orthonormal_vectors.T
    #A=np.vstack((A,np.ones((1,A.shape[1]))))
    
    M=A @ A.T
    print(M) 

    # Convert the orthonormal vectors into an optimization problem
    # Minimize the L1 norm (which promotes sparsity)
    c = np.ones(m)

    # Constraints are that the vector is in the span of the orthonormal vectors
    # A_eq * x = b
    A_eq = orthonormal_vectors.T
    b_eq = np.zeros(n)
    #add the constraint that the vector has a sum greater than 0.0
    
    Ap_eq = np.vstack((A_eq,np.ones((1,m))))
    bp_eq = np.hstack((b_eq,0.0))
    
    # Use linprog to minimize the L1 norm
    result = linprog(c, A_eq=A_eq, b_eq=b_eq, method='highs')

    if result.success:
        return result.x
    else:
        raise ValueError("Optimization did not converge.")

def lsq_fit(cols,y):
    At=np.array(cols)
    A=At.T
    
    x,res,_,_=np.linalg.lstsq(A,y)
    if(len(res)!=1):
        res=[0.0]
    return x,np.sqrt(res[0]/len(y))
    
    
def right_null_solve(Ap,prenormalize=True,rcond=None):
    if(prenormalize):
        Wequal=np.linalg.norm(Ap,axis=1)
        pW=np.reciprocal(Wequal)
        pw=np.nan_to_num(pW, copy=False, nan=0.0, posinf=0.0, neginf=0.0)
        Ap=np.diag(pW) @ Ap
        
    rcond=rcond or max(Ap.shape)*np.finfo(Ap.dtype).eps
    U,S,Vh=np.linalg.svd(Ap,full_matrices=False)
        
    tol=rcond*np.max(S)
    rank=np.sum(S>tol)
    null_size=len(S)-rank
    
    
    if(null_size==0):
        return Vh[-1,:]
    else:
        return max_sparsity_vector(Vh[-null_size:,:].T).T
    
    #    print(null_size)
    #    return max_sparsity_vector(Vh[-null_size:,:].T).T

def polycols(x,k):
    cx=np.ones_like(x)
    for j in range(k+1):
        yield np.array(cx)
        cx*=x
    
def closed_linspace(a,b,n):
    return np.linspace(a,b,n+1,endpoint=False)[1:]
    
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



def basis_iterator(basis_f):
    k=0
    while True:
        f=lambda v: basis_f(v,k)
        yield f
        k+=1
    
#solve for f(v)=0 for all v0
#todo: weights.
def implicit_fit(v,basis_f,M=0,rcond=None): 
    N=len(v)
    if(M==0):
        M=N
    
    # M > N means use larger null space to search for l1 solution.
    basis_results=[]
    for f,k in zip(basis_f,range(M)):
        basis_results.append(f(v))
    A=np.array(basis_results,dtype=np.float64).T
    return right_null_solve(A,rcond=rcond)
        
    
def direct_zerofirst_fit(x,f,zerofirst_basis_iterator,M=0,rcond=None):
    def basis_it():
        didz=False
        for bf in zerofirst_basis_iterator:
            if(not didz):
                didz=True
                yield lambda xp: bf(xp)-f(xp)
                continue
            yield bf
    return implicit_fit(x,basis_it(),M=M,rcond=rcond)

def reconstruct(basis_f,coeffs):
    slist=[(c,bf) for c,bf in zip(coeffs,basis_f)]
    def mfunc(x):
        return sum(c*bf(x) for c,bf in slist)
    
    return mfunc