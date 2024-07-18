
import fractions

#https://numbersandshapes.net/posts/enumerating_the_rationals
def root_fractions():
    x=fractions.Fraction(1,1)

    while True:
        yield x
        x=2 * (x.numerator//x.denominator) - x + 1
        x=fractions.Fraction(1,x)
            
def posneg(g):
    for v in g:
        yield v
        yield -v
        
def withzero(g):
    didz=False
    for v in g:
        if(not didz):
            didz=True
            yield v-v
        yield v
        
        

def power_series_basis(sequence):
    def p_eval(v,s):
        if(s < 0):
            import numpy as np
            v=np.reciprocal(v)
            v=np.nan_to_num(v, copy=False, nan=0.0, posinf=0.0, neginf=0.0)
            s=-s
        return v**s
    for s in sequence:
        yield lambda v : p_eval(v,s)
        
def pot_rationals():
    for r in root_fractions():
        if(r.denominator.bit_count() == 1):
            yield r

if __name__=='__main__':
    for i,x in zip(range(10),enumerate_pot_rationals()):
        print(i,x)