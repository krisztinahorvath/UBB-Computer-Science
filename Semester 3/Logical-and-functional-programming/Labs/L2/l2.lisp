;; 7.Write a function that substitutes an element E with 
;; all elements of a list L1 at all levels of a given list L.


;; mySubstitute(l, elem, p) =
;; = l , if l != elem and l - atom
;; = p , if l = elem and l - atom
;; = mySubstitute(l1, elem, p) U mySubstitute(l2, elem, p) U ... U mySubstitute(ln, elem, p), if l - list

(defun mySubstitute(l elem p)
  (cond
    ((and (not (equal l elem)) (atom l))  l)
    ((and (equal l elem) (atom l)) p)
    (t (mapcar #' (lambda (l) (mySubstitute l elem p)) l))
  )
)

(defun test_mySubsitute ()
    (assert (equal (mySubstitute '(1 2 3 4 1 (1)) 1 '(5 5)) '((5 5) 2 3 4 (5 5) ((5 5)))))
    (assert (equal (mySubstitute '(1 2 3 4 5) 6 '(9 9)) '(1 2 3 4 5)))
    (assert (equal (mySubstitute '() 4 '(2 3)) '()))
    (assert (equal (mySubstitute '(1 2 3 4 5 (3 (2 3))) 3 '(9 9 9 9)) '(1 2 (9 9 9 9) 4 5 ((9 9 9 9) (2 (9 9 9 9))))))
    (assert (equal (mySubstitute '(1 2 3 ()) 1 '(5 6)) '((5 6) 2 3 ())))
    (assert (equal (mySubstitute '(1 2 3 () 1 3 (1)) 1 '()) '(() 2 3 () () 3 (()))))
    (assert (equal (mySubstitute '(1) 1 '()) '(())))
)

(test_mySubsitute)
