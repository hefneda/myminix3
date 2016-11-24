#include <stdio.h>
#include <string.h>
#include <lib.h>    
#include "minix/ipc.h"
#include "testhelper.h"


/**************************************************************
 *       test SENDALL to send all process in the group
 *************************************************************/
int main()
{
    message m1, m;
    int status,i, pid[10], rv, parent=getpid(), value[3];
    int gid = opengroup(0);
    ASSERT_GREATER(gid, 0);
    
    rv = addproc(gid, parent);
    ASSERT_EQUAL(rv, 0);

    for (i = 0; i < 3; i++){
        status = fork();
        if (status == 0 || status == -1) break;
        pid[i] = status;
        rv = addproc(gid, pid[i]);
	ASSERT_EQUAL(rv, 0);
    }
    if (status == -1){
        //Fork error
    } else if (status == 0){
        //Child proc
        message m;
        rv = mreceive(gid, &m, parent);    	
        ASSERT_EQUAL(rv, 0);
        TEST_EQUAL(m.m1_i1, 10, "message should be 10.");
        rv = mreceive(gid, &m, parent);    	
        ASSERT_EQUAL(rv, 0);
        TEST_EQUAL(m.m1_i1, 20, "message should be 20.");
	rv = mreceive(gid, &m, parent);    	
        ASSERT_EQUAL(rv, 0);
        TEST_EQUAL(m.m1_i1, 30, "message should be 30.");
    } else {
        //Parent proc   
        m1.m1_i1 = 10;
        rv = msend(gid, &m1, SENDALL);
        ASSERT_EQUAL(rv, 0);
        TEST_EQUAL(rv, 0, "msend finish should return 0");
        m1.m1_i1 = 20;
        rv = msend(gid, &m1, SENDALL);
        ASSERT_EQUAL(rv, 0);
        TEST_EQUAL(rv, 0, "msend finish should return 0");
	m1.m1_i1 = 30;
	rv = msend(gid, &m1, SENDALL);
        ASSERT_EQUAL(rv, 0);
        TEST_EQUAL(rv, 0, "msend finish should return 0");
        closegroup(gid);
    }
    return 0;
}