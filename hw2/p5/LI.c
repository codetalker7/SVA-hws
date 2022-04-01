unsigned int nondet_uint(); // Returns a nondeterministic unsigned int

int main() {
  unsigned int cnt;
  unsigned int x;
  unsigned int i;
  __CPROVER_assume(x<=16);
  
  //Answer of Exercise2
  //The following assumption prevents overflows
  __CPROVER_assume(i<=31);

  unsigned int savex = x; //save initial value of x for later use in assertion

  cnt = 0;
  while(x != 0) {
    if(x&1) cnt++;
    x >>= 1;
    if (savex == (1<<i))
      __CPROVER_assert( cnt<=1 && ((cnt == 1) == (x==0)), "check_LI");

    //Exercise3
    //If we try to replace the above assertion with the one outside the loop,
    //CBMC should fail because the assertion outside the loop is not inductive
    //for this loop.
    //__CPROVER_assert(cnt == 1, "checking whether this is inductive. CBMC should fail for unwind depths");

    //__CPROVER_assert(savex != (1 << i) || (cnt<=1 && ((cnt == 1) == (x == 0))), "strengthened LI"); 
  }
  
  if (savex == (1<<i)) // N << i shifts bv rep of N by i places to the left
  __CPROVER_assert(cnt == 1, "check for various unwind depth");
  
  //Exercise0: Explain in in English what the conditional assertion check on lines22-23 means?  Note: i can be an arbitrary nat!!
  //Exercise1: Check if the above assertion succeeds for unwind = 0?  If it fails,  analyze the trace and explain why it fails.
  //Exercise2: Fix the assumption to make the assertion succeed for any unwind depth.  Explain why it succeeds after your fix.
  //Exercise3: Note that the assertion on line 21-22 is NOT inductive for this loop.  One way to check this is to include it inside
  //the loop at lines 17-18 (instead of existing assertion) and checking if it succeeds for all unwinding depths for the
  //loop till termination or more.  Perform this exercise and learn what's going wrong from the error trace.
  //One way to make the post condition  inductive is to strengthen the conclusion as shown in lines 19-20; Check that this indeed holds
  // for all unwindings.
  
  //Exercise4: Use the assertion shown on lines 19-20 as an inductive loop invariant to construct a decomposed CBMC proof check of the
  //program for unbounded anlaysis  as discussed in the Lecture on March 11.  This will require you to do the following.
  //a. Construct an abstract program that replaces the loop with using the stated LI as a nondeterministic assignment
  //b. Perform Initiation and Exit checks using the absract program with CBMC
  //c. Verify in CBMC using the body code and appropriate assume and assert statements that the LI is inductive.
}
