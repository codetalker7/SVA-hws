#include <assert.h>
#define len 4

int main(){
   unsigned int i, j, k, x;
   
   // Nondeterministic functions
   _Bool nondet_bool();
   unsigned int nondet_uint();

   i = nondet_uint(); j = nondet_uint();

   //Assume annotations
   __CPROVER_assume(0 <= i && i < len);

   unsigned int l = nondet_uint();
   __CPROVER_assume(0<= l && l < len);

   int myarr[len];
  
   //replaced myarr[i] = x with the following  
   __CPROVER_assume(myarr[i] == x);
   __CPROVER_assume(0 <= k && k < len);
   
   /*
      Problem 1, a.
      The success of the below assertion proves the claim
      given in the problem statement. Here, note that we are not 
      using any non-det variables; only compile time constants 
      and myarr. We are using the fact that len = 4.
      */
   __CPROVER_assert(myarr[0] == x || myarr[1] == x || myarr[2] == x || myarr[3] == x, "myarr contains value x");

   /*
      Problem 1, b.
      The failure of the below assertion proves the claim
      given in the problem statement.
   */
   //__CPROVER_assert(myarr[l] != x, "myarr[l] != x. Failure of this assertion proves that myarr contains x.");

   /*
      Problem 1, c. (i).
      assume inside a for loop to enforce the forall 
      assumption.
   */   
   for (j = 0; j < len; j++)
     __CPROVER_assume(myarr[j] == j);

   /*
      Problem 1, c. (ii)
      enforcing the forall assumption without a 
      for loop. 
   */
   //This assumption does the job. 
   //__CPROVER_assume(myarr[0] == 0 && myarr[1] == 1 && myarr[2] == 2 && myarr[3] == 3); 
}
