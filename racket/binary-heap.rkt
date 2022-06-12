#lang racket

(require data/gvector)

(provide heap-entry%)
(provide binary-heap%)

(define heap-entry%
  (class object%
    (init object value)

    (define object- object)
    (define value- value)

    (super-new)

    (define/public (get-object) object-)
    (define/public (get-value) value-)
    (define/public (set-value! new-value) (set! value- new-value))
  )
)

(define binary-heap%
  (class object%
    (define entries- (make-gvector))
    (define object-positions- (make-hash))

    (super-new)

    (define/public (count) (gvector-count entries-))

    (define/public (empty?) (= (gvector-count entries-) 0))

    (define/public (check-rep)
      (for ([i (gvector-count entries-)])
        (let* 
          [
            (entry (gvector-ref entries- i))
            (object (send entry get-object))
          ]
          (when (not (hash-has-key? object-positions- object))
            (error (string-append "object-positions- does not contain object " (~a object))))
          (when (not (eq? (hash-ref object-positions- object) i))
            (error (string-append "position of the " (~a i) "(th) object is not " (~a i))))
        )
      )
    )

    (define/public (add-raw! object value)
      (when (hash-has-key? object-positions- object)
        (error (string-append "Object " (~a object) " is already in the heap")))      
      (let [(entry (new heap-entry% (object object) (value value)))]
        (gvector-add! entries- entry)
        (hash-set! object-positions- object (- (gvector-count entries-) 1))
      )
    )

    (define (get-value-at index) (send (gvector-ref entries- index) get-value))

    (define (is-heap-order-at-indices? i0 i1) 
      (if (>= i1 (count))
        #t
        (let 
          [
            (v0 (get-value-at i0))
            (v1 (get-value-at i1))
          ]
          (<= v0 v1)
        )
      )
    )

    (define (is-heap-order-helper? i) 
      (cond 
        [(>= i (count)) #t]
        [(not (is-heap-order-at-indices? i (* 2 i))) #f]
        [(not (is-heap-order-at-indices? i (+ (* 2 i) 1))) #f]
        [else (is-heap-order-helper? (+ i 1))]
      )
    )

    (define/public (is-heap-order?) (is-heap-order-helper? 0))

    (define (swap a b)
      (when (not (= a b))
        (define a-entry (gvector-ref entries- a))
        (define b-entry (gvector-ref entries- b))
        (hash-set! object-positions- (send a-entry get-object) b)
        (hash-set! object-positions- (send b-entry get-object) a)
        (gvector-set! entries- a b-entry)
        (gvector-set! entries- b a-entry)
      )
    )

    (define (percolate-down i)
      (define n (count))
      (when (< i n)
        (define min-index i)
        (let ((j (* 2 i)))
          (when (and (< j n) (> (get-value-at min-index) (get-value-at j)))
            (set! min-index j)
          )
        )
        (let ((j (+ 1 (* 2 i))))
          (when (and (< j n) (> (get-value-at min-index) (get-value-at j)))
            (set! min-index j)
          )
        )
        (when (not (= i min-index)) 
          (swap i min-index)
          (percolate-down min-index)
        )
      )
    )

    (define/public (build)
      (for ([i (in-range (quotient (count) 2) -1 -1)])
        (percolate-down i)
      )
    )

    (define (percolate-up i)
      (let [(j (quotient i 2))]
        (when (and (> i 0) (< (get-value-at i) (get-value-at j)))
          (swap i j)
          (percolate-up j)
        )
      )      
    )

    (define/public (add! object value)
      (add-raw! object value)
      (percolate-up (- (count) 1))
    )

    (define/public (change-value! object value)
      (when (not (hash-has-key? object-positions- object))
        (error (string-append "Object " (~a object) " is not in the heap")))
      (define i (hash-ref object-positions- object))
      (define entry (gvector-ref entries- i))
      (define old-value (send entry get-value))
      (when (not (= old-value value))
        (send entry set-value! value)
        (if (< value old-value) 
          (percolate-up i)
          (percolate-down i)
        )
      )
    )

    (define/public (get-value object)
      (when (not (hash-has-key? object-positions- object))
        (error (string-append "Object " (~a object) " is not in the heap")))
      (get-value-at (hash-ref object-positions- object))
    )

    (define/public (has-object? object) (hash-has-key? object-positions- object))

    (define/public (remove-min!)
      (when (empty?)
        (error "Heap is empty!"))
      (define n (count))
      (define output (gvector-ref entries- 0))
      (swap 0 (- n 1))
      (gvector-remove! entries- (- n 1))
      (hash-remove! object-positions- (send output get-object))
      output
    )
  )
)