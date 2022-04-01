# Problem 1

In the file `p1_length3.smt2`, we have encoded the verification condition formula required to prove the given property. Note that a state in our program is a tuple $\langle p, x, y, i\rangle$, where $p$ denotes the value of the program counter (i.e $p = PC$), and $x$, $y$ and $i$ denote the values of the respective variables. Any $3$-long race is of the form

$$\langle p_0, x_0, y_0, i_0\rangle\to \langle p_1, x_1, y_1, i_1\rangle\to \langle p_2, x_2, y_2, i_2\rangle$$

and these are precisely the variables we have maintained in the file. 

The formula is composed of three parts: `init`, a predicate for the initial condition, `tran`, a predicate used to define the transition system, and `P`, which is just a predicate for the property. To check the property, we check whether the formula is UNSAT. Indeed, running the file in Z3 says so. 

Similarly, we check the verification condition formula for $1$-long and $2$-long races in the other files. 

Running times: 
- `p1_length1.smt2`: 0.034s
- `p1_length2.smt2`: 0.034s
- `p1_length3.smt2`: 0.035s

**Important Note:** Note that there is *no* transition starting from a state where $PC = 5$; hence, it must be ensured that in any such formula for checking $k$-races, there is no transition starting from the state with $PC = 5$ (otherwise, the formula will *always* be UNSAT, and could give erroneous results). 
