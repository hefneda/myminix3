#include <stdio.h>
#include <string.h>
//#include <mprofile.h>
//extern int load_profile(char *name);
//#include "kernel/kernel.h"
//#include "arch_proto.h"
//#include <signal.h>
//#include <string.h>
//#include <assert.h>
//#include "proc.h"
//#include "proto.h"
//#include <machine/vm.h>
#include "minix/ipc.h"


int main()
{
	message msg;
    int parent, child;
	
	parent=getpid();
	if((child=fork())==0){
        msg.m_type=1
		send(child, msg);
		printf("yes, send\n");
	} else {
		receive(parent, &msg, 0);
		printf("yes, receive %d\n ", msg.m_type);
	}

	return 0;
}

int test(int i){
//    struct message m_pagefault;
//    
//    mini_send(pr, VM_PROC_NR, &m_pagefault, FROM_KERNEL);
    return 0;
}