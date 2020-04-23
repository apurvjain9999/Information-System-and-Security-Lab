#Image Steganography in Python
#Made By: Apurv Jain

#import required packages and functions
from PIL import Image
import stepic as sp

ans = "Y"
#Asking user for input
while ans != "N" or ans != 'n' :
    ed = input("\nPress: 1) E for Encryption 2) D for Decryption ")
    if (ed == "E" or ed == "e"):
        ip = input("\nEnter the image filename: ") #Image filename
        i = ip.find('.')
        ext = ip[-(len(ip) - i - 1) :].upper() #Getting extension 
        text = input("\nEnter the text to encode: ") #Getting text to encode
        im = Image.open(ip)
        tx = bytes(text, "utf-8")
        im1 = sp.encode(im, tx) #Encoding text into image
        im1.save(ip, 'PNG') #Saving image with the same name

        #im1 = Image.open(ip)
        #im1.show()
        #im.show()
    
    elif (ed == "D" or ed == "d"): #Decoding
        ip = input("\nEnter the image filename: ") #Iamge file
        im = Image.open(ip) 
        text = sp.decode(im) #Decoding text
        print("\nDecoded Text: ", text)
    
    else :
        print("\nPress valid key\n")
        ans = "Y"
        continue

    ans = input("\nWant to continue ? (Y/N): ")
    if ans == "Y" :
        continue
    else :
        break