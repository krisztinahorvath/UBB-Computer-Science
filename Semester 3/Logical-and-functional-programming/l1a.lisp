;; 12.
;; a) Write a function to return the dot product of two vectors. https://en.wikipedia.org/wiki/Dot_product
;; b) Write a function to return the maximum value of all the numerical atoms of a list, at any level.
;; c) All permutations to be replaced by: Write a function to compute the result of an arithmetic expression
;; memorised 
;;  in preorder on a stack. Examples:
;;  (+ 1 3) ==> 4 (1 + 3)
;;  (+ * 2 4 3) ==> 11 [((2 * 4) + 3)
;;  (+ * 2 4 - 5 * 2 2) ==> 9 ((2 * 4) + (5 - (2 * 2))
;; d) Write a function to return T if a list has an even number of elements on the first level, and NIL on the 
;; contrary case, without counting the elements of the list

; car - H
; cdr - T
; cddr - cdr twice, l3...ln
; cadr - second elem of H

;; a
;; dotProduct(l1...ln, k1...km) = 
;;      0, if n = 0
;;      l1*l2 + dotProduct(l2...ln, l2...km), otherwise

(defun dotProduct (l k)
    (cond 
        ( (null l) 0)
        ( T (+ (* (car l) (car k)) (dotProduct (cdr l) (cdr k))))
    )
)
;; l =  1 2 3  k = 4 5 6 
;; => 1*4 + 2*5 + 3*6 = 32

(defun test_dotProduct ()
    (assert (equal (dotProduct '(1 2 3) '(4 5 6)) 32))
    (assert (equal (dotProduct '(0 1) '(0 0)) 0))
    (assert (equal (dotProduct '(1 2 3 4) '(1 2 3 4)) 30))
)


;; b
;; lookForNumbers(l1...ln, c) =
;;      0, if n = 0 and c = 0
;;      1, if n = 0 and c > 0
;;      lookForNumbers(l2...ln, c + 1), if l1 - number
;;      lookForNumbers(l1, c) + lookForNumbers(l2...ln, c), if l1 - list
;;      lookForNumbers(l2...ln, c), otherwise

;; if we don't have any numbers then we can't look for the maximum 
(defun lookForNumbers (l c)
    (cond
        ( (and (null l) (= c 0)) 0)
        ( (and (null l) (> c 0)) 1)
        ( (numberp (car l)) (lookForNumbers (cdr l) (+ 1 c)))
        ( (listp (car l)) ( + (lookForNumbers (car l) c) (lookForNumbers (cdr l) c)))
        ( T (lookForNumbers (cdr l) c))
    )
)

;; myMax(a, b) = 
;;      (), if a not number and b not number
;;      b, if a not number
;;      a, if b not number
;;      a, if a > b
;;      b, otherwise

(defun myMax (a b)
    (cond 
        ( (and (not (numberp a)) (not (numberp b))) NIL)
        ( (not (numberp a)) b)
        ( (not (numberp b)) a)
        ( (> a b) a)
        (T b)
    )
)

;; (print(myMax 5 7) )

;; maxList(l1...ln) = 
;;      l1, if n = 1 and l1 is an atom
;;      myMax(maxList(l1), maxList(l2...ln)), if l1 is a list
;;      myMax(l1, maxList(l2...ln)), otherwise

(defun maxList (l)
    (cond
        ( (and (null (cdr l)) (atom (car l))) (car l))
        ( (listp (car l)) (myMax(maxList (car l)) (maxList (cdr l))))
        (T (myMax (car l) (maxList (cdr l))))
    )
)

;; (maxList '(1 2 3 0 10 9)) ; 10
;; (maxList '(18 90 17 90)) ; 90
;; (maxList '(10)) ; 10
;; (maxList '()) ; NIL


;; mainMaxList(l1..ln) =
;;      null,  if lookForNumbers = 0
;;      maxList(l1..ln), otherwise

(defun mainMaxList (l)
    (cond 
        ((= (lookForNumbers l 0) 0) NIL)
        (T (maxList l))
    )
)

(defun test_mainMaxList ()
    (assert (equal (mainMaxList '(1 A (B C) ((5) 8))) 8))
    (assert (equal (mainMaxList '(15 (19 (19)) A D * 18)) 19))
    (assert (equal (mainMaxList '()) NIL))
    (assert (equal (mainMaxList '(A B (B (C (9) 8) 7) 5)) 9))
)


;; c
;; myAppend(l1...ln, k1...km) =
;;      k1k2...km, if n = 0
;;      l1 U myAppend(l2...ln, k1k2...km), othewise

(defun myAppend (l1 l2)
    (cond 
        ( (null l1) l2)
        (T (cons (car l1) (myAppend (cdr l1) l2)))
    )
)


;; myReverse(l1...ln) = 
;;      (), if n = 0
;;      myAppend(myReverse(l2...ln), list(myReverse(l1))), if l1 is a list
;;      myAppend(myReverse(l2...ln), list(l1)), otherwise

(defun myReverse (l)
    (cond
        ((null l) NIL)
        ((listp (car l)) (myAppend (myReverse (cdr l)) (list (myReverse (car l)))))
        (T (myAppend (myReverse (cdr l)) (list (car l))))
    )
)

;; (myReverse '(+ * 2 4 - 5 * 2 2)) ; (2 2 * 5 - 4 2 * +)

;; evaluate(l1l2...ln, s1s2...sm) = 
;;      s1 , if n = 0
;;      evaluate(l2...ln, {l1} U s1s2...sm)  , if l1 is a number
;;      evaluate(l2...ln, {s1 * s2} U s3...sm) , if l1 = "*"
;;      evaluate(l2...ln, {s1 + s2} U s3...sm) , if l1 = "+"
;;      evaluate(l2...ln, {s1 / s2} U s3...sm) , if l1 = "/"
;;      evaluate(l2...ln, {s1 - s2} U s3...sm) , if l1 = "-"

(defun evaluate(l s)
  (cond
    ((null l) (car s))
    ((numberp (car l)) (evaluate (cdr l) (cons (car l) s)))
    ((string= "*" (car l)) (evaluate (cdr l) (cons (* (car s) (cadr s)) (cddr s))))
    ((string= "+" (car l)) (evaluate (cdr l) (cons (+ (car s) (cadr s)) (cddr s))))
    ((string= "/" (car l)) (evaluate (cdr l) (cons (floor (car s) (cadr s)) (cddr s))))
    (T (evaluate (cdr l) (cons (- (car s) (cadr s)) (cddr s))))
  )
)

;; (evaluate '(2 2 * 5 - 4 2 * +) ()) ; 9

;; mainEvaluate(l1l2...ln) 
;;       evaluate(myReverse(l1l2...ln) ()) 

(defun mainEvaluate(l)
  (cond
    (T (evaluate (myReverse l) ()))
  )
)


(defun test_mainEvaluate ()
    (assert (equal (mainEvaluate '(+ 1 3)) 4)) ; 4 (1 + 3)
    (assert (equal (mainEvaluate '(+ * 2 4 3)) 11)) ; 11 [((2 * 4) + 3)
    (assert (equal (mainEvaluate '(+ * 2 4 - 5 * 2 2)) 9)) ; 9 (2 * 4) + (5 - (2 * 2)) 
)


;; d
;; lengthEven(l1l2...ln) =
;;      true, if n = 0
;;      false, if n = 1
;;      lengthEven(l3..ln), otherwise

(defun lengthEven(l)
    (cond 
        ( (null l) T)
        ( (null (cdr l)) NIL)
        ( T (lengthEven (cddr l)))
    )
)


(defun test_lengthEven ()
    (assert (equal (lengthEven '(1 2 3)) NIL))
    (assert (equal (lengthEven '(1 2 3 4)) T))
    (assert (equal (lengthEven '()) T))
    (assert (equal (lengthEven '(1)) NIL))
)


(defun test_all ()
    (test_dotProduct)
    (test_mainMaxList)
    (test_mainEvaluate)
    (test_lengthEven)
)

(test_all)

;; https://www.tutorialspoint.com/execute_lisp_online.php
