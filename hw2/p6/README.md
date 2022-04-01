# Problem 6

For this problem, the reference program is the file `p5/LC.c`. The predicate $\text{exactly1}$ on the set of bit vectors is defined as follows: $\text{exactly1}(bv)$ is true iff. exactly one bit of $bv$ is $1$.

We will also assume in this problem that all bit vectors have length $5$; if $x$ is a bit-vector, then the bits of $x$ (from left to right) will be represented by $x_1, x_2, x_3, x_4$ and $x_5$ respectively. 

# Problem 6, Part 1

In this problem, we will construct a transition system $TS = (\text{Init}, T)$ for the program over the domain $S = \text{BitVectors}\times\text{BitVectors}\times\mathbb{N}$, where $\text{BitVectors}$ is the set of bit vectors. A state will be interpreted as the tuple $\langle savex, x, cnt\rangle$.

First, for our convenience, we will define a predicate $>>$ which will denote the action of the left shift operator. If $x$ and $x'$ are two bit vectors, then the predicate is defined as follows.

$$
    \begin{aligned}
        >>(x, x') =\,&(x_1' = 0)\land (x_2' = x_1)\land (x_3' = x_2) \land (x_4' = x_3) \land (x_5' = x_4)
    \end{aligned}
$$

In other words, if $>>(x, x')$ is true, then it will be true that $x' = x >> 1$. Similarly, we can define predicates $>>^2$, $>>^3$, $>>^4$ and so on, which define shift operators which shift by more than $1$ step.

For convenience, we also define an equality predicate $\text{equal}$ for bit vectors. If $x$ and $x'$ are bit vectors, then this predicate is defined as follows.

$$\text{equal}(x, x') = (x_1 = x_1')\land (x_2 = x_2')\land (x_3 = x_3')\land (x_4 = x_4')\land (x_5 = x_5')$$

Now, let us define the predicate $\text{Init}$ which will represent the initial condition. **We will assume that the initial value of the bit vector $x$ is a power of $2$.**

$$
    \begin{aligned}
        \text{Init}(savex, x, cnt) = \,&(cnt = 0) &&\land\\
        & (\text{exactly1}(x))&&\land \\
        & \text{equal}(savex, x)
    \end{aligned}
$$

Let us now explain this predicate. The first conjunct is clear. The last conjunct just says that $savex = x$. The second conjunct specifies that $x$ must a power of $2$; note that this automatically implies that $x\le 16$, because the bit vector $x$ contains exactly $5$ bits.  

Next, we will define the predicate $T$ for the transition system.

$$
\begin{aligned}
    T(savex, &x, cnt, savex', x', cnt') =\\
    & (cnt' = \text{exactly1}(x\,\&\,1)\,?\,cnt+1\,:\,cnt)\,\, &&\land\\
    & (>>(x, x')) &&\land\\
    & (\text{equal}(savex, savex'))
\end{aligned}
$$

Above, in the term $x\,\&\,1$, $1$ is the bit vector whose integer value is $1$. Clearly, the above transition system models the body of the loop.

# Problem 6, Part 2.1

In this part, we construct a definition of $\text{Im}$ without the existential quantifier. To do this, we inspect the condition that the states in the image of $\text{Init}$ must satisfy. 

- Because $x\le 16$ initially and because $x$ is also a power of $2$ (as per the initial condition), after one iteration of the loop, the value $x' = x >> 1$ will remain a power of $2$ or it will be $0$.

- Since in the loop body, $x$ is updated to $x' = x >> 1$, we see that the inequality $x'\le 8$ must be true, since the initial value of $x$ was bounded by $16$. This point also implies that $>>(savex, x')$ must be true.

- Moreover, since $cnt$ is incremented *iff* $x$ is odd, we see that $cnt = 1\iff x = 0$ must be true. Also, this implies that $cnt\le 1$ has to be true for all states in the image of $\text{Init}$. 

The above three points describe *precisely* the image of $\text{Init}$ under the transition system. So, without using an existential quantifer, the predicate $\text{Im}$ can be described as follows.

$$
    \begin{aligned}
        \text{Im}(savex, x, cnt) = \,&(x_1 = 0) &&\land\\
        & (\text{exactly1}(x)\lor x = 0) &&\land\\
        & (>>(savex, x)) &&\land\\
        & (cnt \le 1) &&\land\\
        & (cnt = 1 \iff x = 0)
    \end{aligned}
$$

# Problem 6, Part 2.2
We will now construct predicates for $\text{IM}^i$ until $\text{IM}^i = \text{IM}^{i + 1}$.

First, note that $\text{IM}(\text{false})$ is just the predicate $\text{Init}$ just like in Problem 3. So,

$$\text{IM}^1 = \text{IM}(\text{false}) = \text{Init}$$

Again, just like in Problem 3, we have

$$\text{IM}^2 = \text{IM}(\text{Init}) = \text{Init}\lor\text{Im}$$

Now, let us calculate $\text{IM}^3$. We have

$$
    \begin{aligned}
        \text{IM}^3 &= \text{IM}(\text{IM}^2)\\
        &= \text{IM}(\text{Init}\lor \text{Im})\\
        &= \text{Init}\lor \text{ImP}(\text{Init}\lor \text{Im})
    \end{aligned}
$$

Now, note that $\text{ImP}(\text{Init}\lor \text{Im})$ is the set of all states reachable from $\text{Init}\lor \text{Im}$ in one step, and hence

$$\text{ImP}(\text{Init}\lor \text{Im}) = \text{Im}\lor \text{set of states reachable from Im in a step}$$

So, from the above, we see that $\text{IM}^3$ is the union of all states in $\text{Init}, \text{Im}$ and the set of states reachable from $\text{Im}$ in a step, which is just the set of states reachable from $\text{Init}$ in atmost $2$ steps.

In general, using the same reasoning, we can see that $\text{IM}^i$ is the set of all states reachable from $\text{Init}$ in atmost $i - 1$ steps. Using this knowledge, we can write out the following predicates. First,

$$
    \begin{aligned}
        \text{IM}^3(savex, x, cnt) = &\,\text{IM}^2\lor \\
        &((x_1 = 0) &&\land\\
        & (x_2 = 0) &&\land\\
        & (\text{exactly1}(x)\lor x = 0) &&\land\\
        & (>>^2(savex, x)) &&\land\\
        & (cnt \le 1) &&\land\\
        & (cnt = 1 \iff x = 0))
    \end{aligned}
$$

Then,

$$
    \begin{aligned}
        \text{IM}^4(savex, x, cnt) = &\,\text{IM}^3\lor \\
        &((x_1 = 0) &&\land\\
        & (x_2 = 0) &&\land\\
        & (x_3 = 0) &&\land\\
        & (\text{exactly1}(x)\lor x = 0) &&\land\\
        & (>>^3(savex, x)) &&\land\\
        & (cnt \le 1) &&\land\\
        & (cnt = 1 \iff x = 0))
    \end{aligned}
$$

Next, we have 

$$
    \begin{aligned}
        \text{IM}^5(savex, x, cnt) = &\,\text{IM}^4\lor \\
        &((x_1 = 0) &&\land\\
        & (x_2 = 0) &&\land\\
        & (x_3 = 0) &&\land\\
        & (x_4 = 0) &&\land\\
        & (\text{exactly1}(x)\lor x = 0) &&\land\\
        & (>>^4(savex, x)) &&\land\\
        & (cnt \le 1) &&\land\\
        & (cnt = 1 \iff x = 0))
    \end{aligned}
$$

And finally, we will see that

$$\text{IM}^6(savex, x, cnt) = \text{IM}^5\lor (x = 0\land cnt = 1)$$

Note that $\text{IM}^6$ does not include the variable $savex$. Now, note that by our transition system, any state of the form $\langle savex, 0, 1\rangle$ can only reach itself after a single step. So, it follwos that 

$$\text{IM}^7 = \text{IM}^6$$

Hence, $\text{IM}^6$ is a fixed point. 

# Problem 3

No, as far as the program in `p5/LI.c` us concerned, the fixed point obtained above is *not the strongest* inductive invariant for the program; the reason is that instead of starting with the original initial condition, we made an additional assumption that the initial value of $x$ is a power of $2$. 

Yes, our fixed point implies the post condition of the program. Note that cases where $savex$ is a power of $2$ are included in our transition system. Moreover, for every state in $\text{IM}^6$, it holds that $cnt = 1\iff x = 0$; so, indeed at the exit of the loop, we will have $x = 0$, and hence $cnt = 1$ will be true.