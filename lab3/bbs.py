#Cryptographically secure pseudorandom number generator algorithm
#Blum Blum Shub
import sympy
import random
import re 
import sys

x = 3*10**10
y = 4*10**10
seed = random.randint(1,1e10)


def lcm(a, b):
    """Compute the lowest common multiple of a and b"""
    return a * b / gcd(a, b)

def gcd(a,b):
    """Compute the greatest common divisor of a and b"""
    while b > 0:
        a = b
        b = a % b
    return a

def n_prime(x):
        p = sympy.nextprime(x)
        while (p % 4 != 3):
            p = sympy.nextprime(p)
        return p

p = n_prime(x)
q = n_prime(y)

M = p*q

N = 10 

x = seed

bit_op = []
n = 2 ** 9
k = 0
for _ in range(N):
    x = x*x % M
    b = x % 2
    bit_op.append(b)
    k = k + (b * n)
    n = n / 2

print("\nRandom Number: ",k)
#print(bit_op)
