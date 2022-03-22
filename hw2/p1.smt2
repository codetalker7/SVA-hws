; Modelling the transition system of Problem 1. 

; Each state will be represented by a tuple <p, x, y, i>

; Defining the initial state.
; The initial state satisfies p = 0 and |x - y| <= 2
; The second is equivalent to y - 2 <= x <= y + 2
; The variable i is not a part of the initial state 

(define-fun init  ((p0 Int) (x0 Int) (y0 Int) (i0 Int)) Bool
    (and 
        (= p0 0)
        (and (<= x0 (+ y0 2)) (>= x0 (- y0 2)))    
    )
)

; Defining the transition relation. Here, we assume that 
; tran(p, x, y, i,  pn, xn, yn, in) is true iff. 
; <p, x, y, i> -> <pn, xn, yn, in> is a transition.

(define-fun tran ((p Int) (x Int) (y Int) (i Int)
            (pn Int) (xn Int) (yn Int) (in Int)) Bool
    (and 
        (=> (= p 0) (and (= in 0) (= xn x) (= pn 1)))    
        (=> (= p 1) (and 
                        (= in i) 
                        (= xn x)
                        (= pn (ite (> x 0) 5 2))
                    )
        ) 
        (=> (= p 2) (and
                        (= xn (ite (< x y) (+ x 1) x))
                        (= pn (ite (< x y) 4 3)) 
                    )
        ) 
        (=> (= p 3) (and (= yn x) (= pn 4))) 
        (=> (= p 4) (and (= in (+ i 1)) (= pn 1))) 
        (=> (= p 5) (and (= pn p) (= xn x) (= yn y) (= in i))) 
    )
)

; A 3-long race will have 4*3 = 12 variables.
; <p0, x0, y0, i0> -> <p1, x1, y1, i1> -> <p2, x2, y2, i2>

; Declaring all the 12 variables 
(declare-fun p0 () Int)
(declare-fun x0 () Int)
(declare-fun y0 () Int)
(declare-fun i0 () Int)
(declare-fun p1 () Int)
(declare-fun x1 () Int)
(declare-fun y1 () Int)
(declare-fun i1 () Int)
(declare-fun p2 () Int)
(declare-fun x2 () Int)
(declare-fun y2 () Int)
(declare-fun i2 () Int)

; Ensuring the initial condition 
(assert (init p0 x0 y0 i0))

; Ensuring that these variables form valid transitions 
(assert (and 
    (tran p0 x0 y0 i0 p1 x1 y1 i1)
    (tran p1 x1 y1 i1 p2 x2 y2 i2)
))

; Checking the property 
(assert (= x2 y2))

(check-sat)
(get-model)
