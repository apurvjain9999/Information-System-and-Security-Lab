from PIL import Image
import stepic as sp

ans = "Y"
while ans != "N" or ans != 'n' :
    ed = input("\nPress: 1) E for Encryption 2) D for Decryption ")
    if (ed == "E" or ed == "e"):
        ip = input("\nEnter the image filename: ")
        i = ip.find('.')
        ext = ip[-(len(ip) - i - 1) :].upper()
        text = input("\nEnter the text to encode: ")
        im = Image.open(ip)
        tx = bytes(text, "utf-8")
        im1 = sp.encode(im, tx)
        im1.save(ip, 'PNG')

        im1 = Image.open(ip)
        im1.show()
        im.show()
    
    elif (ed == "D" or ed == "d"):
        ip = input("\nEnter the image filename: ")
        im = Image.open(ip)
        text = sp.decode(im)
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