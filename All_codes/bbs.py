#Cryptographically secure pseudorandom number generator algorithm
#Blum Blum Shub
#Made By: Apurv Jain

#importing required libraries
import sympy
import random
import re 

x = 3*10**10
y = 4*10**10

seed = random.randint(1,1e10) #Generating a seed 


def lcm(a, b): 
    """Compute the lowest common multiple of a and b"""
    return a * b / gcd(a, b)

def gcd(a,b):
    """Compute the greatest common divisor of a and b"""
    while b > 0:
        a = b
        b = a % b
    return a

#Getting prime number close to x such that x % 4 == 3
def n_prime(x):
        p = sympy.nextprime(x)
        while (p % 4 != 3):
            p = sympy.nextprime(p)
        return p

#Generating two large prime numbers
p = n_prime(x)
q = n_prime(y)

#Generating M
M = p*q

#For 10 digits
N = 10 

x = seed

bit_op = []
n = 2 ** 9
k = 0
#Generating random number in binary
for _ in range(N):
    x = x*x % M
    b = x % 2
    bit_op.append(b)
    #For binary to decimal conversion
    k = k + (b * n)
    n = n / 2

print("\nRandom Number: ",k)
#print(bit_op)
