/*
  In this file we do an unbounded analysis of the given loop 
  by breaking it into three checks, viz. the initial condition check,
  the loop body check and the exit condition check.

  The variables are cnt, x, i and savex. The LI and P, i.e the loop invariant
  and the property to verify are as follows. 

  LI : savex != (1 << i) || (cnt<=1 && ((cnt == 1) == (x == 0)))
  P : savex != (1 << i) || cnt == 1
*/

unsigned int nondet_uint();

int main(){
  unsigned int cnt, x, i, savex;  

  /*
    Doing the loop initial condition check
  */

  cnt = nondet_uint();
  x = nondet_uint();
  i = nondet_uint();
  savex = nondet_uint();
  
  __CPROVER_assume(x <= 16 && i <= 31 && savex == x && cnt == 0);
  
  //checking LI before the loop starts execution
  __CPROVER_assert(savex != (1 << i) || (cnt <= 1 && ((cnt == 1) == (x == 0))), "Base Case Check");
 
  /*
    Doing the loop exit check
  */
  
  //Reassinging x and cnt as only they are changed in the program
  cnt = nondet_uint();
  x = nondet_uint();
  i = nondet_uint();
  savex = nondet_uint();  

  //assume the LI
  __CPROVER_assume(savex != (1 << i) || (cnt <= 1) && ((cnt == 1) == (x == 0)));
  //assume the loop exit condition
  __CPROVER_assume(x == 0);
  //assert the property 
  __CPROVER_assert(savex != (1 << i) || cnt == 1, "Post Condition Check");    

  /*
    Doing the inductive check  
  */
  
  //Reassiging x and cnt as only they are changed in the program
  cnt = nondet_uint();
  x = nondet_uint();
  i = nondet_uint();
  savex = nondet_uint();  

  //Assuming LI and LC
  __CPROVER_assume(x != 0);   //LC
  __CPROVER_assume(savex != (1 << i) || (((savex % x == 0 && x <= savex) || x == 0) && (cnt <= 1 && ((cnt == 1) == (x == 0)))));  //Strengthened LI

  //Loop body
  if (x&1) cnt++;
  x >>= 1;

  //Asserting the strengthened LI again
  __CPROVER_assert(savex != (1 << i) || (((savex % x == 0 && x <= savex) || x == 0) && (cnt <= 1 && ((cnt == 1) == (x == 0)))), "Inductive Check");
 
}
