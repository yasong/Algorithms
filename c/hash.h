#ifndef __HASH_H__
#define __HASH_H__  1
#include <stdlib.h>


#define SHORT_SEED      40503;
#define INT_SEED        2654435769
#define LONG_SEED       11400714819323198485

typedef unsigned int    u_int;
typedef unsigned short  u_short;
typedef unsigned char   u_char;
typedef unsigned long   u_long;


typedef hash_node hash_node_t;
struct hash_node{
    void *key;
    void *value;
    hash_node *next;
};
/* Key computation function */
typedef u_int (*hash_fcompute)(void *key);

/* Comparison function for 2 keys */
typedef int (*hash_fcompare)(void *key1,void *key2);

typedef struct hash_table hash_table_t;
struct hash_table{
    int size, num_node;
    hash_node_t **nodes;
    hash_fcompute hash_func;
    hash_fcompare key_cmp;
};

/** Create node */
hash_node_t *hash_node_alloc(void *key, void *value);

/** Delete node */
void hash_node_delete(hash_node_t *node);

/** Create hash table */
hash_table_t *hash_table_create(hash_fcompute hash_func, hash_fcompare key_cmp, 
                                int hash_size);
/** Delete an existing hash table */
void hash_table_delete(hash_table_t *ht);

/** Insert a new pair(key, value) if sucess return 0*/
int hash_table_insert(hash_table_t *ht, void *key, void *value);

/** Remove a pair（key, value) from a hash table */
void *hash_table_remove(hash_table_t *ht, void *key);

/** String hash functions
*function algorithm: ELF, RS, JS, PJW, BKDR, SDBM, DJB, DEK, AP
**/
int str_equal(void *str1, void *str2);
u_int str_ELF_hash(void *str);
u_int str_RS_hash(void *str);
u_int str_JS_hash(void *str);
u_int str_PJW_hash(void *str);
u_int str_BKDR_hash(void *str);
u_int str_SDBM_hash(void *str);
u_int str_DJB_hash(void *str);
u_int str_DEK_hash(void *str);
u_int str_AP_hash(void *str);

/** Int */
int int_equal(void *int1, void *int2);
u_int int_hash(void *it);

#endif