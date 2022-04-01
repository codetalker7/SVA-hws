# Problem 5

The reference program is contained in `LI.c`. 

# Exercise 0

The assertion in the lines 22-23 (the assertion outside the loop) is the check that `cnt = 1` must be true if `savex`, the original value of `x`, is a power of $2$. Since `i` can be an arbitrary natural number, the check will check all powers of $2$ against `savex`. 

# Exercise 1

The assertion outside the loop *fails* if we run it in CBMC with unwind depth $0$. The trace gives us the following values of the variables. 

1. `cnt = 0`.
2. `x = 0`.
3. `i = 50`.
4. `savex = 0`.

From this trace we can analyze why the given assertion fails. Note that $2^{50}$ is outside the range of `unsigned int`, and hence the condition `savex == (1 << i)` has undefined behavior (note that $0$ is not a power of $2$); in particular, this condition returns `true`, even though it isn't. So, even for an unwind depth of $0$, the given assertion will fail. 

# Exercise 2

The range of `unsigned int` in C is from $0$ to $4,294,967,295$; these are precisely those numbers represented by a $32$-bit vector (because $2^{32} = 4,294,967,295$). So, for the assertion to succeed, we must have `i <= 31`. So, we add the following statement to our assumptions
    
    __CPROVER_assume(i<=31);

This statement is in line 11 of `LI.c`. After this assumption, running CBMC with any unwind depth succeeds, because there won't be any overflows. 

# Exercise 3

In line 26 of `LI.c`, we have added the assertion outside the loop to verify that it is *not* inductive for the loop; indeed, running CBMC with any unwind depth fails the assertion. The error trace for unwind depth $1$ gives the following initial values of the variables. 

1. `cnt = 0`.
2. `x = 16`.
3. `savex = 16`.

Clearly, after one iteration, `x` will get the value `x = 8`, but `cnt` will still be 0, and hence the assertion will fail. 

In line 28 of `LI.c`, we have added the strengthened version of the post condition as an assert. Running CBMC with any unwind depth leads to success for this assertion, and hence it's indeed inductive.

# Exercise 4

In this we construct a proof check for the property to be proved using the inductive loop invariant. This is done in the `UnboundedAnalysis.c` file. The code is broken into three parts: 

- Doing the initial condition check for the loop, i.e the base case. 
- Doing the exit condition check of the loop. 
- Doing the inductiveness check of the loop invariant. 

The initial condition check is done in lines 18-30 and is pretty straightforward. We add assumptions about the initial values of the variable, and check whether the loop condition follows. Note that the loop invariant is the one inside the loop in `LI.c`; we have written it as a predicate. 

The ecxit condition check is done in lines 32-45. Note that here we only non-deterministially reassign new values to `x` and `cnt`, because the values `savex` and `i` are never changed within the loop body. 

Finally, we come to the interesting part, namely the inductiveness check, which is done in lines 47-67. Again, we non-deterministically reassign the values for `x` and `cnt`. Now, we add an additional assumption to the loop invariant in line 57, which is a strengthening of the proposed loop invariant to prove the given property. Namely, we claim that if `savex` is a power of $2$, then it must be the case that either `x` is a factor of `savex` or `x = 0` (this is clear from the behavior of the loop); this is needed because we have reassigned $x$ non-deterministically, and we need to make sure that if `savex` is a power of $2$, then `x` must be reachable from `savex` by repeatedly dividing by $2$. 

Then, we run the loop body, and assert the (strengthened) loop invariant again. Running this in CBMC gives success, and proves that the loop is indeed correct and proves the property. 
