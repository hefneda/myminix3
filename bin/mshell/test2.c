#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

int main(int argc, char **argv)
{
    printf("Executing...\n");
    printf("value=%d", chdir(""));
}