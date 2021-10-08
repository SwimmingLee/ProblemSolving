#define MAX_LEN (20)
#define HASH_TABLE (6000000)
char table[HASH_TABLE][21];

/*
* #define MAX_LEN (20)
#define MAX_TABLE (300000)
unsigned long long dictionary[MAX_TABLE] = {0,};
 
char search(char word[MAX_LEN + 1])
{
    unsigned long long hash = 5381;
    while(*word != '\0'){
        hash = (((hash << 10) + hash) + *word -'a');
        word++;
    }
     
    int key = hash % MAX_TABLE;
     
    while(true){
        if(dictionary[key] == 0){
            dictionary[key] = hash;
            return '0';
        }else{
            if(dictionary[key] == hash){
                return '1';
            }else {
                key = (key + 1) % MAX_TABLE;
            }
        }
    }
        
*/

/*
* 
* struct Node {
    char str[MAX_LEN + 1];
    Node* next;
};
 
Node* hash_table[MAX_TABLE];

char search(char word[MAX_LEN + 1])
{
    unsigned long hash = hash_func(word);

    Node* now = hash_table[hash];

    while (now) {
        if (str_cmp(now->str, word) == 0) return '1';
        now = now->next;
    }

    now = new Node;
    str_cpy(now->str, word);
    now->next = hash_table[hash];
    hash_table[hash] = now;

    return '0';
}
*/
unsigned long hashing(char* word) {
    unsigned long hash = 5381;

    while (*word != '\0') {
        hash = (((hash << 5) + hash) + *word) % HASH_TABLE;
        word++;
    }
    return hash;
}

void _strcpy(char* des, char* src) {
    while (*src != '\0') {
        *(des++) = *(src++);
    }
    *des = '\0';
}

bool _strcmp(char* s1, char* s2) {
    while (*s1 != '\0') {
        if (*(s1++) != *(s2++)) return false;
    }
    if (*s1 != '\0') return false;
    return true;
}

char search(char word[MAX_LEN + 1])
{
    unsigned long hash = hashing(word);
    unsigned long phash = hash;
    
    while ((hash + 1) % HASH_TABLE != phash) {
        if (table[hash][0] == '\0') {
            _strcpy(table[hash], word);
            return '0';
        }
        else if (_strcmp(table[hash], word)) {
            return '1';
        }
        else {
            hash = (hash + 1) % HASH_TABLE;
        }
    }

    return '0';
}