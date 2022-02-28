# Problem 1, Part a. 

To check whether there is some `l` with `0 <= l < len` and `myarr[l]== x`, we can simply check whether one of `myarr[0]`, `myarr[1]`, `myarr[2]` or `myarr[3]` is equal to `x`. Note that here we are only using `myarr`, and also the fact that the length of `myarr` is 4. We are not using any non-deterministic variables here. This is what we have done in line 32 of the solution. 

# Problem 1, Part b. 

This is straightforward; we just check the assertion `myarr[l] != x`. Since `l` is non-deterministic, the failure of this assertion will imply that `x` indeed occurs in `myarr`. This is what we are doing in line 39 of the solution. 

# Problem 1, Part c. (i)

This is straightforward. We have done this in lines 46-47 of the solution. 

# Problem 1, Part c. (ii)

Here, again we use the fact that `myarr` has length 4, and we just explicity write down the conditions separated by the Boolean AND operator. This is straightforward and we are not using any for loop. 
