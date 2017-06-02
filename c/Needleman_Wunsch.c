#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* strjoin(char *dst, char *src)
{
    char *buff;
    int dst_len, src_len;
    dst_len = strlen(dst);
    src_len = strlen(src);
    buff = malloc((dst_len+src_len)*sizeof(char));
    strcpy(buff,dst);
    strcat(buff,src);
    return buff;
}
int max3(int a, int b, int c)
{
    int tmp;
    tmp = a > b ? a:b;
    tmp = tmp > c ? tmp:c;
    return tmp;
}
void Needleman_Wunsch(char *str1, char *str2)
{
    int len_str1, len_str2;
    int i = 0, j = 0;
    int penalty = 0;
    char ch[]="-";
    int tmp;
    char ch_tmp[]="F";
    char *Alignment_str1="", *Alignment_str2="";
    int *lcs;

    len_str1 = strlen(str1);
    len_str2 = strlen(str2);

    if (len_str1 == 0 || len_str2 == 0)
        return;
    //构建分表
   
    lcs = malloc((len_str1+1) * (len_str2+1)*sizeof(int));
    memset(lcs,0,(len_str1+1) * (len_str2+1)*sizeof(int));
    for(i = 0; i < len_str2 + 1; ++i)
    {
        *(lcs+i) = i * penalty;
    }
    for(j = 0; j < len_str1 + 1; ++j)
    {
        *(lcs+(len_str2+1)*j) = j * penalty;
    }
    for(i = 0; i < len_str1; ++i)
    {
        for(j = 0; j < len_str2; ++j)
        {
            tmp = *(lcs + (i)*(len_str2+1) + j) + (str1[i] == str2[j] ? 1 :-1);
            *(lcs + (i+1)*(len_str2+1) + (j+1)) = max3(*(lcs + i*(len_str2+1) + j+1) + penalty,
                                                      *(lcs + (i+1)*(len_str2+1) + j) + penalty,
                                                      tmp
                                                      );
        }
    }

    for(i = 0; i < len_str1+1; ++i)
    {
         for(j = 0; j < len_str2+1;++j)
        {
            printf("%d\t",*(lcs + i*(len_str2+1) + j));
        }
        printf("\n");
    }

    

    i = len_str1;
    j = len_str2;
    while(i > 0 || j > 0)
    {
        tmp = *(lcs + (i-1)*(len_str2+1) + (j-1)) + (str1[i-1] == str2[j-1] ? 1:-1);
        if (i > 0 && j > 0 && *(lcs + i*(len_str2+1) + j) == tmp)
        {
            ch_tmp[0]= str1[i-1];
            Alignment_str1 = strjoin(ch_tmp,Alignment_str1);
            ch_tmp[0]= str2[j-1];
            Alignment_str2 = strjoin(ch_tmp,Alignment_str2);
            i = i - 1;
            j = j - 1;
        }
        else if(i > 0 && *(lcs + i*(len_str2+1) + j) == *(lcs + (i-1)*(len_str2+1) + j) + penalty)
        {
            ch_tmp[0]= str1[i-1];
            Alignment_str1 = strjoin(ch_tmp,Alignment_str1);
            Alignment_str2 = strjoin(ch,Alignment_str2);
            i = i - 1;
        }
        else
        {
            //Alignment_str1[i] = '-';
            //Alignment_str2[j] = str2[j-1];
            Alignment_str1 = strjoin(ch,Alignment_str1);
            ch_tmp[0]= str2[j-1];
            Alignment_str2 = strjoin(ch_tmp,Alignment_str2);
            j = j - 1;
        }
    }

    printf("%s\n",Alignment_str1);
    printf("%s\n",Alignment_str2);
    free(lcs);
    free(Alignment_str1);
    free(Alignment_str2);
}

int main(int argc, char **argv)
{
    //char *str1 = "GCCCTAGCGT";
    //char *str2 = "GCGCAATG";
    if(argc != 3)
        return -1;
    Needleman_Wunsch(argv[1], argv[2]);
    return 0;
}
