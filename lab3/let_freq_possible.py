eng = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
ip_file = ""
#op_file = ""

ip_file = input("\nEnter input file name: ")
#op_file = input("\nEnter output file name: ")

plain_txt = []

freq_plain_txt = []

print("\nEnter top 10 most frequent possible plaintexts: ")

for i in range(10) :
    st = input("\nPlain Text " + str(i+1) + ": ")
    freq_plain_txt.insert(i, st.upper())

for pl in range(10) :
    count = [0 for i in range(26)]
    ip = open(ip_file, "r")
    #print(freq_plain_txt[pl])
    text_freq = {}
    st = "A"
    flag = 0
    while st:
        st = ip.readline().upper()
        st = st.split()
        #print(st)
        for i in st:
            if len(freq_plain_txt[pl]) == len(i) :
                flag = 1
                if i in text_freq :
                    text_freq[i] += 1
                else :
                    if i.isalpha() == True:
                        text_freq[i] = 1

    if flag == 0 :
        continue
    
    #print(str(text_freq))
    ip.close()
    
    s_text_freq = sorted(text_freq.items(), key=lambda x: x[1], reverse=True)
    #print(s_text_freq)
    ip.close()
    st = "A"

    res = [v for v in text_freq.values()]
    #print(res)
    max_i = []
    max_p = max(res)

    for i in range(len(res)):
        if max_p == res[i] :
            max_i.append(i)

    
    diff = 0
    fg = 0
    for i in max_i:
        st = s_text_freq[i][0]
        fg  = 0
        letter = [-1 for i in range(26)]
        for q in range(len(st)) :
            k = eng.index(st[q])
            
            #print(st)
            l = q
            #print(l)
            m = freq_plain_txt[pl][l]
            n = eng.index(m)
            #print(k)
            #print(n)
            #print(n - k)
            d = (n - k) % 26
            if (n-k) < 0 :
                d = d - 26
            if l != 0:
                if d != diff:
                    fg = 1
                else :
                    diff = d
            else :
                diff = d
            #print(diff)
            if fg == 1 :
                break
            letter[n] = k
        if fg == 1:
            continue
        for i in range(len(letter)):
            if letter[i] == -1 :
                letter[i] = (i-diff) % 26
                if (i-diff) < 0 :
                    letter[i] = letter[i] - 26
        #print(letter)
        ip = open(ip_file, "r")
        st = "A"
        while st:
            st = ip.readline().upper()
            #print(st)
            wr = ""
            for i in st:
                if i.isalpha() == True :
                    j = eng.index(i)
                    wr += eng[letter.index(j)]

                else:
                    wr += i

            wr = wr.lower()
            #print(wr)
            plain_txt.append(wr)
            #print(plain_txt)
                
        ip.close()

print("\nPossible Plain Texts: ")
l = 1
for i in range(len(plain_txt)) :
    j = 0
    f = 0
    while j<i :
        if plain_txt[j] == plain_txt[i] :
            f = 1
            break
        j += 1
    if f == 1:
        continue
    else :
        if plain_txt[i] != "":
            print("\nPlain Text ", l, ": ", plain_txt[i])
            l += 1
