_Bool nondet_bool();
unsigned int nondet_uint(); // Returns a nondeterministic unsigned int

//Returns a non-determnistic int between 0 and n
unsigned int  zero_to_n(unsigned int n){
  unsigned int result=nondet_uint();
  __CPROVER_assume(result>=0 && result<=n);
  return result; 
}


int main() {
  int cnt;
  unsigned int x;
  __CPROVER_assume(x<=16);
  //assert(0);
  unsigned int savex = x; //save for later use in assertion

  cnt = 0;
  while(x != 0) {
    //__CPROVER_assert(savex == 0 || cnt == 1, "Loop invariant");
    if(x&1) cnt++; 
    x >>= 1; //integer division by 2
  } 
   
  unsigned int i;
  if (savex == (1<<i)) // if x is a nonzero power of 2)
     __CPROVER_assert(savex == 0 || cnt == 1, "out assertion");

  //Problem 3
  //a: Check if the above assertion succeeds?  If it fails, analyse the error trace to determine why it fails.
  /*
   * The above assertion DOES NOT succeed. The error trace gives x = 0, savex = 0, cnt = 0 and i = 50. Note 
   * that 2^50 is not within the range of unsigned int; hence, the condition savex == (1 << i) is not enough;
   * we must add savex != 0 to the condition to ensure that savex is non-zero (indeed, no power of 2 can be zero). 
   * */

  //b: Fix the assertion to make it succeed and show that it indeed succeeds.
  /*
   * As mentioned above, we add the condition savex == 0 to the assert; after adding the condition, 
   * the assertion indeed succeeds. 
   * */
  //c: Check if the fixed assertion is also true inside the loop immedately after the "while" line
  //   That is, it is a "loop invariant"
  /*
   * No, the fixed assertion is not a loop invariant. The counterexample given by teh trace is simple, 
     x = 1 and savex = 1.
  */
}

/*
commands you can try to prove assertions or explore other things:
cbmc (or hw-cbmc) while_loop.c --help  (This lists all available options)
cbmc while_loop.c --show-goto-functions (This outputs the program graph)
cbmc while_loop.c --show-claims (This lists all the assertions defined)
cbmc while_loop.c --unwind 33 (This cheks all the claims/assertions)
*/
