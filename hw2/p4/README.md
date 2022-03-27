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
**Here $LI$ is the proposed loop invariant, and $P$ is the propetry that we wish to prove. Answer the following questions.** 

1. **Is $LI(x, z)$ an inductive invariant for the loop at the point of placement of $LI$?**

2. **Formulate a way to strengthen $LI$ into an inductive invariant that can prove the post condition $P$ on existing the loop.**

3. **What is the strongest inductive invariant predicate that holds at $LI$? Hint: You need to formulate a predicate $P_y(y, z)$ that relates values of $y$ and $z$ invariantly.**

4. **Can you construct a predicate $Q(x, y, z)$ that is inductive but NOT an invariant for the loop at location $LI$?**
