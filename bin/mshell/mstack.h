#define MSTACKSIZE 50

typedef struct {
    int size;
    void **list;
} mstack;

void initstack(mstack **stk);
int push (void *item, mstack *stk);
int pop(void **item, mstack *stk);
void freestack(mstack *stk);