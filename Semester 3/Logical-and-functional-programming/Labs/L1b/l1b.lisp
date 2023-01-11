;; 2. Return the list of nodes on the k-th level of a tree of type (1)

;    A
;   B  C
;     D  E

; left_traversal(l1l2...ln, nrNodes, nrVertices) = 
;  nil, if n = 0
;  nil, if nrNodes = 1 + nrVertices
;  {l1} U {l2} U left_traversal(l3...ln, nrNodes + 1, l2 + nrVertices), otherwise

(defun left_traversal (l nrNodes nrVertices)
  (cond
    ((null l) nil)
    ((= nrNodes ( + 1 nrVertices)) nil)
    (t (cons (car l) (cons (cadr l) (left_traversal (cddr l) (+ 1 nrNodes) (+ (cadr l) nrVertices)))))
  )
)


; right_traversal(l1l2...ln, nrNodes, nrVertices) =
;  nil, if n = 0
;  l1l2...ln, if nrNodes = 1 + nrVertices
;  right_traversal(l3...ln, nrNodes + 1, nrVertices + l2), otherwise

(defun right_traversal (l nrNodes nrVertices)
  (cond
    ((null l) nil)
    ((= nrNodes (+ 1 nrVertices)) l)
    (t (right_traversal (cddr l) (+ 1 nrNodes) (+ (cadr l) nrVertices)))
  )
)


;left_subtree(l1l2...ln) = 
;  left_traversal(l3...ln, 0,0)

(defun left_subtree(l)
  (left_traversal (cddr l) 0 0)
)


;right_subtree(l1l2...ln) =
;  right_traversal(l3...ln, 0, 0)

(defun right_subtree(l)
  (right_traversal (cddr l) 0 0)
)


; myAppend(l1l2...ln, p1p2...pm) = 
;  p1p2...pm, if n = 0
;  {l1} U myAppend(l2...ln, p1p2...pm), otherwise

(defun myAppend(l p)
  (cond
    ((null l) p)
    (t (cons (car l) (myAppend (cdr l) p)))
  )
)


; nodes(l1l2...ln, counter, level) = 
; = nil, if n = 0 
; = l1 , if counter = level
; = myAppend(nodes(left_subtree(l1l2...ln), (c + 1), level), 
;   nodes(right_subtree(l1l2...ln), (c + 1), level)), otherwise

(defun nodes(l counter level)
  (cond
    ((null l) nil)
    ((equal counter level) (list (car l)))
    (t (myAppend (nodes (left_subtree l) (+ 1 counter) level) (nodes (right_subtree l) (+ 1 counter) level)))
  )
)

;; main(l1l2...ln, level) = 
;;   nodes(l112...ln, 0, level)

(defun main(l level)
  (nodes l 0 level)
)

    ;;    A   
    ;;    B 
    ;; C    D 
    ;; E    F
    ;;    G   H
    

(defun test_main ()
  (assert (equal (main '(A 2 B 0 C 2 D 0 E 0) 2) '(D E)))
  (assert (equal (main '(A 1 B 2 C 1 E 0 D 1 F 2 G 0 H 0) 0) '(A)))
  (assert (equal (main '(A 1 B 2 C 1 E 0 D 1 F 2 G 0 H 0) 1) '(B)))
  (assert (equal (main '(A 1 B 2 C 1 E 0 D 1 F 2 G 0 H 0) 2) '(C D)))
  (assert (equal (main '(A 1 B 2 C 1 E 0 D 1 F 2 G 0 H 0) 3) '(E F)))
  (assert (equal (main '(A 1 B 2 C 1 E 0 D 1 F 2 G 0 H 0) 4) '(G H)))
)

(test_main)
