/* 
* @Author: Xiaokang Yin
* @Date:   2017-06-05 09:23:31
* @Last Modified by:   Xiaokang Yin
* @Last Modified time: 2017-06-06 10:05:23
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


/** CMP String  equal return 1, not equal return 0*/
int str_equal(void *str1, void *str2)
{
    return(strcmp((char*)str1, (char*)str2) == 0);
}

/** String hash Function, ELF hash */
u_int str_ELF_hash(void *str)
{
    char *buff = (char *)str;
    char *p;
    u_int h = 0, g = 0;

    for (p = buff; *p != '\0'; p += 1) {
          //put the low four bits into h
        h = (h << 4) + *p;
        if ((g = h & 0xf0000000)) {
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }

    return(h);
} //end ELF hash

/** RS hash */
u_int str_RS_hash(void *str)
{
    u_int b = 378551;
    u_int a = 63689;
    u_int h = 0;
    char *buff = (char *)str;
    char *p;

    for (p = buff; *p != '\0'; p += 1) {
        h = h * a + *p;
        a = a * b;
    }

    return h;
} // end RS hash

/** JS hash */
u_int str_JS_hash(void *str)
{
    char *buff = (char *)str;
    char *p;
    u_int h = 1315423911;

    for (p = buff; *p != '\0'; p += 1) {
        hash ^= ((hash << 5) + *p + (hash >> 2));
    }

    return h;
} //end JS hash

/** PJW hash */
u_int str_PJW_hash(void *str)
{
    char *buff = (char *)str;
    char *p;
    u_int BitsIntUnsignedInt = u_int (sizeof(u_int) * 8);
    u_int ThreeQuarters = u_int ((BitsIntUnsignedInt * 3) / 4);
    u_int OneEigth = u_int (BitsIntUnsignedInt / 8);
    u_int HightBits = u_int (0xFFFFFFFF) << (BitsIntUnsignedInt - OneEigth);
    u_int h = 0;
    u_int tmp = 0;

    for (p = buff; *p != '\0'; p += 1) {
        h = (h << OneEigth) + *p;

        if ((tmp = h & HightBits) != 0) {
            h = ((h ^ (tmp >> ThreeQuarters)) & (~HightBits));
        }
    }

    return h;
} //end PJW hash

/** BKDR hash */
u_int str_BKDR_hash(void *str)
{
    char *buff = (char *)str;
    char *p;
    u_int seed = 131; //31 131 1313 13131 131313 etc.
    u_int h = 0;

    for (p = buff; *p != '\0'; p += 1) {
        h = (h * seed) + *p;
    }

    return h;
} //end BKDR hash

/** SDBM hash */
u_int str_SDBM_hash(void *str)
{
    char *buff = (char *)str;
    char *p;
    u_int h = 0;

    for (p = buff; *p != '\0'; p += 1) {
        h = (h << 6) + (h << 16) + *p - h;
    }

    return h;
} //end SDBM hash

/** DJB hash */
u_int str_DJB_hash(void *str)
{
    char *buff = (char *)str;
    char *p;
    u_int h = 5381;

    for (p = buff; *p != '\0'; p += 1) {
        h = (h << 5) + h + *p;
    }

    return h;
} //end DJB hash

/** DEK hash */
u_int str_DEK_hash(void *str)
{
    char *buff = (char *)str;
    char *p;
    u_int h = strlen(buff);

    for (p = buff; *p != '\0'; p += 1) {
        h = ((h << 5) ^ (hash >> 27)) ^ *p;
    }

    return h;
} //DEK hash

/** AP hash */
u_int str_AP_hash(void *str)
{
    char *buff = (char *)str;
    char *p;
    u_int h = 0xAAAAAAAA;
    u_int i = 0;

    for (p = buff; *p != '\0'; p += 1) {
        h = ((i & 1) == 0) ? ((h << 7) ^ *p * (h >> 3)):
                            (~((h << 11) + (*p ^ (h >> 5))));
    }

    return h;
} //end AP hash