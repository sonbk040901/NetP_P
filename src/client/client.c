#include "index.h"
#include "login.h"
#include "login.ui.h"
int fa()
{
    printf("f1 called\n");
    return 0;
}
int fb()
{
    printf("f2 called\n");
    return 1;
}
int main(int argc, char const *argv[])
{
    f((void *)&fa, (void *)&fb);

    return 0;
}
