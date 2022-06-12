#lang racket

(require data/gvector)

(provide (struct-out heap-entry))
(provide binary-heap%)

(struct heap-entry (object value) #:mutable)

(define binary-heap%
  (class object%
    (define entries- (make-gvector))
    (define object-positions- (make-hash))

    (super-new)

    (define/public (size) (gvector-count entries-))

    (define/public (empty?) (= (gvector-count entries-) 0))

    (define/public (check-rep)
      (for ([i (hash-count entries-)])
        (let* 
          [
            (entry (gvector-ref entries- i))
            (object (heap-entry-object entry))
          ]
          (when (not (hash-has-key? object-positions- object))
            (error (string-append "object-positions- does not contain object " (~a object))))
          (when (not (eq? (hash-ref object-positions- object) i))
            (error (string-append "position of the " (~a i) "th object is not " (~a i))))
        )
      )
    )

    (define/public (add-raw object value)
      (when (hash-has-key? object-positions- object)
        (error (string-append "Object " (~a object) " is already in the heap")))      
      (let [(entry (heap-entry object value))]
        (gvector-add! entries- entry)
        (hash-set! object-positions- object (- 1 (gvector-count entries-)))
      )
    )
  )
)