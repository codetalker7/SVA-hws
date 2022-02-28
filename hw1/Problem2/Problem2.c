//Problem 2: Review the following code and perform all experiments described below.
//the function binsearch take an element x and an array a, assuming the array a is sorted in increasing order
//with repeated elelments allowed.  It reruns -1, if x does not exist in the array a; if it does it returns an
// index of the array where x is stored.

#define len 4

_Bool nondet_bool();
unsigned int nondet_uint();

int binsearch(int x, int a[len]) {
   signed low=0, high=4;

   while(low<high) {
      signed middle=low+((high-low)>>1);

      if(a[middle]<x)
         low = middle + 1;
      else if(a[middle]>x)
         high = middle;
      else{
         if (middle == low)
            return low;
         else 
            low = middle; 
      }
   }

   return -1;
}

int main() {
   int i,j,k,x;

   int myarr[len];

   int * ptr;
   
   // Assume input array elements are ordered increasing order permittin repitions
   //a. Formulate the above constraint using _CPROVER_assume
   for (j = 0; j < len - 1; j++)
      __CPROVER_assume(myarr[j] <= myarr[j + 1]);
   
   // Invoke binsearch on myarr for an arbitrary x
   i = binsearch(x, myarr);
   
   //b. Specify the following properties described in English using nondeternistic index variables
   //    (as required) using assert without using any for loop.  Run CBMC to check them and submit the result
   //(i) "If i is -1, then x must not be anywhere in the array myarr."
   //(ii) "If i is within the array bound, then x must be in the array a i"
   __CPROVER_assume(0 <= k && k < len);
   __CPROVER_assert((i == -1 && myarr[k] != x) || (0 <= i && i < len && myarr[i] == x), "either i == -1 and x not in myarr, or myarr[i] == x");

   /*
    * The above assert fails; the counterexample given by cbmc is the following: 
    * k = 1
    * myarr = {1686442336, 1686548849, 1955381079, 1956978535}`
    * x = 1956978535
    * Clearly, running the current binary search on this data leads to an error. 
    * To fix this, the code of binary search above is fixed by replacing the statements of the if and else if blocks.
    * */


   //c. When x is stored at multiple locations in the array, the code as such may not return the largest
   //   or the smallest index at which there is a "hit". Adda piece of code in main to make i hold he largest
   //   index at which x is stored.  Formulate a property to check the correctness of the added functionality
   //   and submit outcome of successful verification effort.
   
   //To add the feature, we added a new else block which handles the case when myarr[middle] == x. This ensures
   //that the highest index at which x is stored is returned.
   //Below is the assert to check this claim.
   unsigned int l = nondet_uint();
   __CPROVER_assume(0 <= l && l < len); //assume that l is within the bound
   __CPROVER_assume(myarr[l] == x); //x occurs in the array
   __CPROVER_assume(i == len - 1 || k > i);  //k is anything greater than i
   __CPROVER_assert((i == len - 1) || (myarr[k] != x), "check that highest index at which x is stored is returned");

   return (0);
}

