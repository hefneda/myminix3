#define MQUEUESIZE 200

typedef struct 
{  
    void ** list;      
    int head;   
    int tail;     
} mqueue;  

void initQueue(mqueue ** que);                
int isEmpty(mqueue * que);                   
int isFull(mqueue * que);                  
int enqueue(void *item, mqueue * que);        
int dequeue(void **item, mqueue * que);   
void closeQueue(mqueue * que);   