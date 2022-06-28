#lang racket

(require "binary-heap.rkt")
(require "graph.rkt")
(require math/flonum)
(require data/gvector)

(provide dijkstra-result%)
(provide run-dijkstra)

(define dijkstra-result%
  (class object%
    (init source)

    (define source- source)
    (define distance- (make-hash))
    (define pred- (make-hash))

    (super-new)

    (define/public (get-source) source-)
    
    (define/public (set-distance! vertex new-distance) (hash-set! distance- vertex new-distance))
    (define/public (has-distance? vertex) (hash-has-key? distance- vertex))
    (define/public (get-distance vertex) (hash-ref distance- vertex))
    
    (define/public (set-pred! vertex new-pred) (hash-set! pred- vertex new-pred))
    (define/public (has-pred? vertex) (hash-has-key? pred- vertex))
    (define/public (get-pred vertex) (hash-ref pred- vertex))
  )
)

(define (run-dijkstra graph source)
  (when (not (send graph has-vertex? source))
    (error (string-append "The given graph does not contain Vertex" (~a source))))
 
  (define heap (new binary-heap%))
  (define result (new dijkstra-result% [source source]))
  (send result set-distance! source 0.0)
  (send result set-pred! source source)
  (send heap add! source 0.0)  
  (define processed-vertices (make-hash))
  


  (define (dijkstra-loop)
    (when (not (send heap empty?))
      (define entry (send heap remove-min!))
      (define u (send entry get-object))
      (define u-distance (send entry get-value))

      (hash-set! processed-vertices u #t)

      (define u-adj-list (send graph get-adj-list u))      
      (for ([edge u-adj-list])        
        (define v (send edge get-dest))
        (define weight (send edge get-weight))
        (when (not (hash-has-key? processed-vertices v))
          (when (not (send result has-distance? v))
            (send result set-distance! v +max.0)
            (send result set-pred! v v)
            (send heap add! v +max.0)          
          )
          (define v-distance (send result get-distance v))
          (define new-v-distance (+ u-distance weight))
          (when (< new-v-distance v-distance)
            (send result set-distance! v new-v-distance)
            (send result set-pred! v u)
            (send heap change-value! v new-v-distance)
          )
        )
      )

      (dijkstra-loop)
    )
  ) 
  
  (dijkstra-loop)
  result
)