#include <stdio.h>
#include <string.h>
#include <lib.h>    
#include "minix/ipc.h"

int main()
{
    message m, *msg;
    int status,i, pid[10], rv, parent=getpid();
    int gid = opengroup(0);
    addproc(gid, parent);
    msg = &m;
    
    for (i = 0; i < 4; i++){
        status = fork();
        if (status == 0 || status == -1) break;
        pid[i] = status;
        addproc(gid, pid[i]);
    }
    if (status == -1){
        //Fork error
    } else if (status == 0){
        //Circle send
        while(mreceive(gid, &m, parent)!=0);
        
        if(i==3){
            i -= 4;
        }
        printf("yes in send %d-%d-%d\n", getpid(), parent+i+2, i);
	    int rv = msend(gid, &m, parent+i+2);	
        printf("rv is %d-%d\n", rv, errno);
    } else {
        //Parent proc    
        printf("cur id:%d\n", parent);
        
        for(i=0; i<4; i++){
            rv = msend(gid, &m, SENDALL);
            printf("finish send %d-%d\n", rv, errno);
        }
    }
    return 0;
}