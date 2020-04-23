//Apurv Jain
//2017KUCP1016
//Image Steganography in C (for only BMP images)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get_img_header(FILE *img)
{
    fseek(img, 10, 0);
    int header;
    header = (int)fgetc(img);
    return header;
}

int get_msg_size(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return(size);
}

int get_bit(char num, int n_bit)
{
    return((num>>8-n_bit)&1);
}

void encode()
{
    FILE *img;
    FILE *msg;
    FILE *steg;
    char *im;
    char *ms;
    char *stg;
    im = malloc(256);
    ms = malloc(256);
    stg = malloc(256);
    printf("\nEnter name of image file: ");
    scanf("%s", im);
    printf("\nEnter name of message file: ");
    scanf("%s", ms);
    printf("\nEnter name of destination image file: ");
    scanf("%s", stg);

    img = fopen(im, "r");
    if (img == NULL)
    {
        printf("\nCannot open image file\n");
        return;
    }

    steg = fopen(stg, "w");
    if (stg == NULL)
    {
        printf("\nCannot create destination file\n");
        return;
    }

    int c = 0;
    //Generating file with the same header (copying first 128 bytes)
    //Creating a BMP File
    char temp;
    int header;
    header = get_img_header(img);
    rewind(img);

    int i;
    for(i=0; i<header; i++)
    {
        temp = fgetc(img);
        fputc(temp, steg);
        c++;
    }

    char f_buff;    //temp var for one byte from img file
    char m_buff;    //temp var for one byte from msg file

    msg = fopen(ms, "r");
    if (msg == NULL)
    {
        printf("\nCannot open message file\n");
        return;
    }
    int msg_size;
    msg_size = get_msg_size(msg);
    //Writing size of message (for using it in decrypting)
    fputc(msg_size, steg);
    c++;
    do
    {
        int bit_msg;
        if (!feof(msg))
        {
            m_buff = fgetc(msg);
            for(i=1; i<=8; i++) //For each bit in every byte of original image
            {
                f_buff = fgetc(img);
                c++;
                int f_lsb = f_buff & 1; //To get LSB 
                bit_msg = get_bit(m_buff, i);

                if (f_lsb == bit_msg)
                {
                    fputc(f_buff, steg);
                }
                else
                {
                    if (f_lsb == 0)
                    {
                        f_buff = (f_buff | 1);
                    }
                    else
                    {
                        f_buff = (f_buff & ~1);
                    }
                    //flip the lsb 
                    fputc(f_buff, steg);   
                }
            }
        }
        else
        {
            temp = fgetc(img);
            fputc(temp, steg);
            c++;
        }
    } while (!feof(img));
    
    fclose(img);
    fclose(steg);
    fclose(msg);
}

void decode()
{
    FILE *img;
    FILE *msg;
    char *im;
    char *ms;
    im = malloc(256);
    ms = malloc(256);
    printf("\nEnter name of image file: ");
    scanf("%s", im);
    printf("\nEnter name of output message file: ");
    scanf("%s", ms);
    img = fopen(im, "r");
    if (img == NULL)
    {
        printf("\nCannot open image file\n");
        return;
    }
    msg = fopen(ms, "w");
    if (msg == NULL)
    {
        printf("\nCannot create destination file\n");
        return;
    }
    //Eliminating header data
    int header = get_img_header(img);
    rewind(img);
    int i;
    char temp;
    for(i=0; i<header; i++)
    {
        temp = fgetc(img);
    }
    //Getting msg size
    int msg_size;
    msg_size = fgetc(img);
    int j;
    char f_buff;
    for(i=0; i<msg_size; i++)
    {
        temp = '\0';
        for(j=0; j<8; j++)
        {
            temp = temp << 1;
            f_buff = fgetc(img);
            int f_lsb = f_buff & 1;
            temp |= f_lsb;
            
        }
        //printf("\n %c", temp);
        fputc(temp, msg);
    }
    fclose(img);
    fclose(msg);
}

int main()
{
    printf("\n---- Image Steganography in C ----\n");
    int ans = 0;
    do
    {
        printf("\nSelect option: 1) Encrypt 2) Decrypt 3) Exit \n");
        scanf("%d", &ans);
        switch(ans)
        {
            case 1 : encode();
            break;
            case 2 : decode();
            break;
            case 3 : break;
            default : printf("\nSelect correct option\n");
        }
    }while(ans != 3);
    return 0;
}
