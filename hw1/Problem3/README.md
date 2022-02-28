# Problem 3 part a. 

The given assertion *fails* if we run it in CBMC. The counterexample given by the trace is `i = 50`, `x = 0`, `savex = 0` and `cnt = 0`. Note that 2^50 is beyond the range which `unsigned int` allows; hence, the check `savex == (1 << i)` leads to undefined behavior. To fix this, we modify the assertion to be `__CPROVER_assert(savex == 0 || cnt == 1)`. Running this now in CBMC leads to success.

# Problem 3 part b.

We have already mentioned how to fix the assert in part a. above. And it is successfully verified by CBMC. Indeed, if `x` is a power of 2, then `cnt` will be only incremented by 1.

# Problem 3 part c. 

No, the fixed assertion is NOT a loop invariant; CBMC fails on running the assertion. The counterexample trace given by CBMC is `x = 1` and `savex = 1`. Clearly, even in the first iteration of teh loop, the given assert is not true, and hence this is NOT a loop invariant.        
