# Problem 3

The set of states $S$ is 
$$S = \{\langle 0, 0\rangle, \langle 0, 1\rangle, \langle 1, 0\rangle, \langle 1, 1\rangle\}$$

The initial state predicate formula is the following. 
$$\text{Init}(\langle x_1, x_0\rangle) = x_0\lor x_1$$
The transition system is given by the following predicate formula. 
$$\text{TS}(\langle x_1, x_0\rangle, \langle x_1', x_0'\rangle) = (x_1' = x_0) \land (x_0' = x_1)$$
With these definitions, we will now answer the following questions. 

1. **What sets of states do the following predicates denote?**
    $$\text{Im}(\langle y_1, y_0\rangle) = (\exists \langle x_1, x_0\rangle)\,\,.\,\,\text{Init}(\langle x_1, x_0\rangle \land T(\langle x_1, x_0\rangle, \langle y_1, y_0\rangle))$$
    *Answer:* Note that $\text{Im}(\langle y_1, y_0\rangle)$ will be true if and only if the state $\langle y_1, y_0\rangle$ is reachable from an initial state in exactly one step. So, the predicate $\text{Im}$ will be satisfied by precisely those states which are reachable from some initial state in exactly one step. Now because the only possible initial states are $\langle 1, 0\rangle$, $\langle 0, 1\rangle$ and $\langle 1, 1\rangle$, it follows that the set represented by $\text{Im}$ is the following. 
    $$\{\langle 1,0\rangle\}, \langle 0, 1\rangle, \langle 1, 1\rangle\}$$

2. **Consider the following higher-order function on state predicates:**
    $$\text{ImP}(P)(\langle y_1, y_0\rangle) = (\exists \langle x_1, x_0\rangle)\,\,.\,\,P(\langle x_1, x_0\rangle)\land T(\langle x_1, x_0\rangle, \langle y_1, y_0\rangle))$$
    **What does $\text{ImP}(\text{Init})$ denote?**

    *Answer:* $\text{ImP}(\text{Init})$ denotes the $\text{Im}$ predicate from problem 1. We just substitute $\text{Init}$ for $P$.  

3. **Now let's define another higher-order "predicate generator" function $\text{IM}: \text{Pred}[S]\to \text{Pred}[S]$ as follows.** 
    $$\text{IM}(X)(\langle x_1, x_0\rangle) = \text{Init}(\langle x_1, x_0\rangle)\lor \text{ImP}(X)(\langle x_1, x_0\rangle)$$
    **Answer the following questions.** 

    **(i)** What does the predicate returned by $\text{IM}^1 = \text{IM}(\text{false})$ denote?

    **(ii)** What does $\text{IM}^2 = \text{IM}(\text{IM}(\text{false}))$

    *Answer:* Note that 
    $$\text{IM}(\text{false})(\langle x_1, x_0\rangle) = \text{Init}(\langle x_1, x_0\rangle)\lor \text{ImP}(\text{false})(\langle x_1, x_0\rangle)=\text{Init}(\langle x_1, x_0\rangle)$$
    because $\text{ImP}(\text{false})$ can never be satisfied by any state, i.e it is the false predicate. So, it follows that 
    $$\text{IM}^1 = \text{Init}$$
    
    Next, we see what $\text{IM}^1$ denotes. Note that 
    $$\text{IM}^2 = \text{IM}(\text{IM}(\text{false})) = \text{IM}(\text{Init})$$
    Moreover, 
    $$\text{IM}(\text{Init})(\langle x_1, x_0\rangle) = \text{Init}(\langle x_1, x_0\rangle)\lor \text{ImP}(\text{Init})(\langle x_1, x_0\rangle)$$
    But, from problem 2, we know that $\text{ImP}(\text{Init})$ is just the $\text{Im}$ predicate from problem 1, which is the set of all states reachable from an initial state in one step. So, we see that 
    $$\text{IM}^2 = \text{Init}\lor \text{Im}$$
    Said in words, this means that $\text{IM}^2$ is the set of all states reachable from an initial state in atmost $1$ step.