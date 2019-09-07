freq_eng = {'E' : 12.0,'T' : 9.10,'A' : 8.12,'O' : 7.68,'I' : 7.31,'N' : 6.95,'S' : 6.28,'R' : 6.02,'H' : 5.92,'D' : 4.32,
            'L' : 3.98,'U' : 2.88,'C' : 2.71,'M' : 2.61,'F' : 2.30,'Y' : 2.11,'W' : 2.09,'G' : 2.03,'P' : 1.82,'B' : 1.49,
            'V' : 1.11,'K' : 0.69,'X' : 0.17,'Q' : 0.11,'J' : 0.10,'Z' : 0.07 }

ip_file = ""
op_file = ""

list_alp = ['A', 'B', 'C', 'D', 'E', "F"]

count = [0 for i in range(26)]
ip_file = input("\nEnter input file name: ")
op_file = input("\nEnter output file name: ")

ip = open(ip_file, "r")

text_freq = {}
st = "A"
while st:
    st = ip.readline().upper()
    for i in st:
        if i in text_freq:
            text_freq[i] += 1
        else :
            if (i.isalpha() == True):
                text_freq[i] = 1


#print(str(text_freq))

k = ["" for i in range(len(text_freq))]

s_text_freq = sorted(text_freq.items(), key=lambda x: x[1], reverse=True)
#print(s_text_freq)
freq_lett = [i for i in freq_eng.keys()]


for i in range(len(s_text_freq)) :
    k[i] = freq_lett[i]

#print(k)
op = open(op_file, "w")
ip.close()
st = "A"

res = [f[0] for f in s_text_freq]
ip = open(ip_file, "r")
while st:
    st = ip.readline().upper()
    #print(st)
    wr = ""
    for i in st:
        if i.isalpha() == True:
            j = res.index(i)
            #print(j)
            wr += k[j]
        
        else :
            wr += i
        
    wr = wr.lower()
    op.write(wr)
    
print("\nSuccessfully performed Letter Frequency Attack\n")
ip.close()
op.close()