#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author: Xiaokang Yin
# @Date:   2017-06-01 19:47:41
# @Last Modified by:   Xiaokang Yin
# @Last Modified time: 2017-06-02 22:00:29

# complete the Needleman and Wunsch algorithm

def Needleman_Wunsch(str1, str2):
    '''Needleman_Wunsch.py'''
    if str1 == '' or str2 =='':
        return
    #保存最大值下标
    Max_index = [0,0]
    Max_value = 0
    #字符串长度
    len_str1 = len(str1)
    len_str2 = len(str2)

    #惩罚
    W1 = 2   #Wk = k*W1, W1=2
    penalty = 3      #a[i] == b[j] penalty = 3; else penalty = -3

    #构建分表
    lcs = [[0] for i in range(0, len_str1 + 1)]
    lcs[0] = [0 for j in range(0, len_str2 + 1)]

    for i in range(len_str1):
        for j in range(len_str2):
            #if ()
            lcs[i+1].append( max(lcs[i][j] + (1 if str1[i] == str2[j] else -1),
                lcs[i][j+1] + penalty,
                lcs[i+1][j] + penalty，
                0)
            )

    i = len_str1
    j = len_str2
    Alignment_str1 = u''
    Alignment_str2 = u''
    #Alignment_str1 = u"%s%s" % (str1[i], Alignment_str1)
    #Alignment_str2 = u"%s%s" % (str2[j], Alignment_str2)

    #traceback
    while i > 0 or j > 0:
        if (i > 0 and j > 0 and lcs[i][j] == lcs[i-1][j-1] + (1 if str1[i-1] == str2[j-1] else -1)):
            Alignment_str1 = u"%s%s" % (str1[i-1], Alignment_str1)
            Alignment_str2 = u"%s%s" % (str2[j-1], Alignment_str2)
            i = i - 1
            j = j - 1
        elif (i > 0 and lcs[i][j] == lcs[i-1][j] + penalty):
            Alignment_str1 = u"%s%s" % (str1[i-1], Alignment_str1)
            Alignment_str2 = u"%s%s" % ('-', Alignment_str2)
            i = i - 1
        else:
            Alignment_str1 = u"%s%s" % ('-', Alignment_str1)
            Alignment_str2 = u"%s%s" % (str2[j-1], Alignment_str2)
            j = j - 1

    print Alignment_str1
    print Alignment_str2
def main():
    str1 = raw_input("string1:")
    str2 = raw_input("string2:")
    Needleman_Wunsch(str1,str2)
    
if __name__ == '__main__':
    main()

