#include <stdio.h>
#include <assert.h>

void main(){
    int i, x, y;

    //assume that |x - y| <= 2
    __CPROVER_assume(x >= y - 2 && x <= y + 2);
    
    //unwinding for depth 2 using the first way
    if (i <= 10){
        if (x < y){
            x = x + 1;
        }
        else{ 
            y = x;  
        }

        i++;

        if (i <= 10){
            if (x < y){
                x = x + 1;  
            }
            else{
                y = x;
            }

            i++;
        }   
        else{
            __CPROVER_assert(x == y, "x == y");
        }
    }  
    else{
        __CPROVER_assert(x == y, "x == y");
    }
}
