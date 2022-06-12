#lang racket

(require data/gvector)

(provide edge%)
(provide graph%)

(define edge%
  (class object%
    (init source dest weight)

    (define source- source)
    (define dest- dest)
    (define weight- weight)

    (super-new)

    (define/public (get-source) source-)
    (define/public (get-dest) dest-)
    (define/public (get-weight) weight-)
  )
)

(define graph%
  (class object%
    (define adj-lists- (make-hash))

    (super-new)

    (define/public (get-vertex-count) (hash-count adj-lists-))
    
    (define/public (add-vertex vertex) 
      (begin 
        (when (not (string? vertex))
          (error (string-append "Input vertex " (~a vertex) " not a string!")))
        (when (hash-has-key? adj-lists- vertex)
          (error (string-append "Vertex '" vertex "' already exists")))
        (hash-set! adj-lists- vertex (make-gvector))
      )
    )

    (define/public (add-edge v0 v1 weight)
      (when (not (send this has-vertex? v0)) 
        (error (string-append "Vertex " (~a v0) " does not exists.")))
      (when (not (send this has-vertex? v1))
        (error (string-append "Vertex " (~a v1) " does not exists.")))
      (when (not (real? weight))
        (error (string-append "Weight " (~a weight) " is not a real number.")))
      (let [(v0-adj-list (hash-ref adj-lists- v0))] 
        (gvector-add! v0-adj-list (new edge% (source v0) (dest v1) (weight weight)))
      )      
    )

    (define/public (has-vertex? vertex) (hash-has-key? adj-lists- vertex))

    (define/public (get-adj-list vertex) 
      (when (not (send this has-vertex? vertex))
        (error (string-append "Vertex " (~a vertex) " does not exists.")))
      (hash-ref adj-lists- vertex)
    )
  )
)