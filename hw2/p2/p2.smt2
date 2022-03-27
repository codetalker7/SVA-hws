; Declaring all the variables needed in the SSA
(declare-fun x0 () Int)
(declare-fun y0 () Int)
(declare-fun i0 () Int)
(declare-fun y1 () Int)
(declare-fun i1 () Int)
(declare-fun y2 () Int)
(declare-fun i2 () Int)

(assert
    ( not 
        (
            =>
            ( and
                (and (>= x0 (- y0 2)) (<= x0 (+ y0 2)))
                (= i0 0)
                (<= i0 10)
                (not (< x0 y0))
                (= y1 x0)
                (= i1 (+ i0 1))
                (<= i1 10)
                (not (< x0 y1))
                (= y2 x0)
                (= i2 (+ i1 1))
                (not (<= i2 10))
            ) 
            (= x0 y2)
        )
    )
)

; The above formula must be UNSAT to prove the property.

(check-sat)
