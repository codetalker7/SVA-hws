# Part a. 

Formulating the constraint that the array is non-decreasing is straightforward and we have done it using a `for` loop in lines 40-41.

# Part b. 

First, we have used a non-deterministic index `k` between `0` and `len - 1` (inclusive). Now, the constraint in part (i) can be formulated using the boolean condition `i == -1 && myarr[k] != x`; note that this condition is saying that when `i == -1` is true, then it must be true that `myarr[k] != x`, which essentially means that `x` must not be present in `myarr`. The constraint in part (ii) can be formulated by using the condition `0 <= i && i < len && myarr[i] == x`; this is simply saying that if and when `i` is in the range of the array, it *must* be the case that `myarr[i] == x`.

Running this in cbmc, the assert FAILED. The counterexample given was: `myarr = {1686442336, 1686548849, 1955381079, 1956978535}` and `x = 1956978535`. Clearly, running the original code on this example leads to an error. The fix for this was simple: just replace the statements in the `if` and `else if` conditions.

# Part c.
We then add the functionality where, if `x` is in the array, the *largest* index where `x` is stored is returned. For this, we have simply added some code in the `else` block of the code. The strategy is simple: if there is a match, i.e if `a[middle] == x`, then we try to increase the lower bound of the interval within which we are searching (the `low` variable) to `middle`. If the original interval has length 1, which happens iff `middle == low`, we simply return low.

To verify this, we add assumptions in lines 73, 74 and 75; namely that `myarr[l] == x` (that `x` occursin the array at some position `l`) and either `i == len - 1` (which by default will make `i` the highest index at which `x` is stored), or we enforce `k > i`. Then, we assert that either `i == len - 1`, or `myarr[k] != x`. Clearly, this checks that `i` is indeed the largest index at which `x` is stored. Running this leads to SUCCESS in cbmc.   
