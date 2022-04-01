# Problem 4

**The reference program for the problem is given below.**

    {true}
    int x, y, z;
    x = 1; y = 1; z = 0;

    while {LI: x = (z + 1)^2} (z < 10){
        x = x + y + 2;
        y = y + 2;
        z = z + 1;
    }
    {P: x = 121}
**Here $LI$ is the proposed loop invariant, and $P$ is the property that we wish to prove.** 

# An inductive invariant for the loop

Before solving the problems, we will construct an inductive loop invariant for the given program, and we will show that it indeed is an inductive loop invariant. The inductive loop invariant that we propose is the following. 

$$LI_y(y, z) = (y = 2z + 1)$$

Let us show that this is an inductive invariant for the program.

1. The initial values of $y$ and $z$ are $1$ and $0$ respectively. Also, $1 = 2\cdot0 + 1$. So, $LI_y(y, z)$ holds before the start of the loop.

2. Now, suppose $LI_y(y, z)$ holds before some loop iteration. Now, within the loop body, the value of $y$ is updated to $y' = y + 2$ and the value of $z$ is updated to $z' = z + 1$. We want to check that $y' = 2z' + 1$, which is the same as checking whether $y + 2 = 2(z + 1) + 1$ holds. But note that $2(z + 1) + 1 = 2z + 2 + 1 = y + 2$ and hence the equality holds indeed.

So, it follows that $LI_y(y, z)$ is an inductive loop invariant for the given loop.   

# Questions

**Is $LI(x, z)$ an inductive invariant for the loop at the point of placement of $LI$?**

*Answer:* To check whether $LI(x, z)$ is an inductive loop invariant, we need to check two things, namely that $LI$ holds before the loop execution, and that the LI holds after every iteration of the loop.

So first, let us check whether $LI(x, z)$ holds before the loop execution. Note that the initial values of $x$ and $z$ are $1$ and $0$ respectively, and clearly it holds that $x = (z + 1)^2$. Hence, $LI(x, z)$ indeed holds before the loop execution.

Let, let's check whether $LI(x, z)$ holds after every iteration of the loop. So, suppose $LI(x, z)$ holds before a loop iteration, i.e $x = (z + 1)^2$ before the start of the loop iteration. Note that within the loop $x$ is updated to the value $x' = x + y + 2$, $y$ is updated to the value $y' = y + 2$ and $z$ is updated to the value $z' = z + 1$. So, we need to check whether $x' = (z' + 1)^2$ holds, which is equivalent to checking whether

$$x + y + 2 = (z' + 1)^2$$

holds. Now, we know that $x = (z + 1)^2 = z'^2$. Also, by the inductive invariant $LI_y(y, z)$ that we've shown above, it holds that $y' = 2z' + 1$. Using this, we can see that 

$$(z' + 1)^2 = (z')^2 + 1 + 2z' = x + y' = x + y + 2 = x'$$

and hence $LI(x', z')$ indeed holds. So, $LI(x, z)$ is a loop invariant. 

**Formulate a way to strengthen $LI$ into an inductive invariant that can prove the post condition $P$ on exiting the loop.**

*Answer:* For the loop invariant $LI$ to be strong enough to prove $P$, it must be the case that the formula $LI\land \neg LC\implies P$ is valid, where $LC$ is the loop condition. If we substitute $LI$, $LC$ and $P$ in this formula, clearly we see that the formula $(x = (z + 1)^2)\land \neg(z < 10)\implies (x = 121)$ is not valid (because $z$ could be anything $\ge 10$). So, to strengthen $LI$, we add an upper bound on $z$, namely $z\le 10$; i.e, we let $LI = (x = (z + 1)^2)\land z\le 10$. Note that the formula

$$(x = (z + 1)^2)\land z\le 10\land \neg(z < 10)\implies x = 121$$

is valid, and hence this new LI is strong enough to prove $P$ on exiting the loop.

**What is the strongest inductive invariant predicate that holds at $LI$? Hint: You need to formulate a predicate $P_y(y, z)$ that relates values of $y$ and $z$ invariantly.**

*Answer:* The strongest inductive invariant that holds at $LI$ is the following.

$$LI_{\text{strongest}} = LI(x, y)\land LI_y(y, z)\land z
\le 10$$

More explicitly,

$$LI_{\text{strongest}} = (x = (z + 1)^2)\land (y = 2z + 1)\land 0\le z\le 10$$

Note that this captures precisely those values of $x, y$ and $z$ which are possible in the loop; this is because $z$ can only take values in the range $[0, 10]$ before and after the loop execution, and we've already shown that $LI$ and $LI_y$ are inductive loop invariants.

**Can you construct a predicate $Q(x, y, z)$ that is inductive but NOT an invariant for the loop at location $LI$?**

*Answer:* Consider the predicate $LI_{even}(y) = \text{even}(y)$, i.e the predicate $LI_{even}$ checks whether $y$ is even. Clearly, this predicate is inductive for the given loop; if $y$ is even at the beginning of some iteration, then certainly $y' = y + 2$ is also even at the end of the iteration. However, this predicate is not an inductive loop invariant, simply because it doesn't hold before the execution of the loop (as $y = 1$ is the initial value). 
