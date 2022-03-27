#include <stdio.h>
#include <assert.h>

void main(){
    int i, x, y;

    //assume that |x - y| <= 2
    __CPROVER_assume(x >= y - 2 && x <= y + 2);
    
    while(i <= 10){
        if (x < y)
            x = x + 1;
        else
            y = x;
        i++;
    } 
    
   __CPROVER_assert(x == y, "x == y");
}
