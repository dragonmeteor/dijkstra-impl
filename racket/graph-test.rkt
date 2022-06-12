#lang racket

(require rackunit)
(require "graph.rkt")
(require data/gvector)

(provide graph-tests)

(define graph-tests 
  (test-suite "graph% tests"
    (test-case "New graph% should have zero vertices"
      (define g (new graph%))
      (check-equal? (send g get-num-vertices) 0)
    )
    
    (test-case "add-vertex of non-string argument should fail"
      (define g  (new graph%))
      (check-exn exn:fail? (lambda () (send g add-vertex 0)))
    )

    (test-case "add-vertex should behave sensibly"
      (define g  (new graph%))
      
      (send g add-vertex "A")
      (send g add-vertex "B")
      (send g add-vertex "C")

      (check-equal? (send g get-num-vertices) 3)
      
      (check-true (send g has-vertex? "A"))
      (check-true (send g has-vertex? "B"))
      (check-true (send g has-vertex? "C"))
      
      (check-false (send g has-vertex? "D"))
      (check-false (send g has-vertex? "E"))      
    )

    (test-case "get-adj-list should behave sensibly"
      (define g  (new graph%))
      
      (send g add-vertex "A")
      (send g add-vertex "B")
      (send g add-vertex "C")
      
      (check-eq? (gvector-count (send g get-adj-list "A")) 0)
      (check-eq? (gvector-count (send g get-adj-list "B")) 0)
      (check-eq? (gvector-count (send g get-adj-list "C")) 0)

      (check-exn exn:fail? (lambda () (send g get-adj-list "D")))
      (check-exn exn:fail? (lambda () (send g get-adj-list "E")))
      (check-exn exn:fail? (lambda () (send g get-adj-list "F")))
    )  

    (test-case "adding duplicated vertices should throw excpetion"
      (define g (new graph%))

      (send g add-vertex "A")
      (check-exn exn:fail? (lambda () (send g add-vertex "A")))
    )

    (test-case "adding an edge should behave sensibly"
      (define g (new graph%))
      
      (send g add-vertex "A")
      (send g add-vertex "B")
      (send g add-edge "A" "B" 10)

      (define A-adj-list (send g get-adj-list "A"))
      (check-equal? (gvector-count A-adj-list) 1)
      (define edge (gvector-ref A-adj-list 0))
      (check-equal? (send edge get-source) "A")
      (check-equal? (send edge get-dest) "B")
      (check-equal? (send edge get-weight) 10)
    )

    (test-case "adding multiple edges should behave sensibly"
      (define g (new graph%))
      
      (send g add-vertex "A")
      (send g add-vertex "B")
      (send g add-vertex "C")
      (send g add-edge "A" "B" 10)
      (send g add-edge "A" "C" 20)

      (define A-adj-list (send g get-adj-list "A"))
      (check-equal? (gvector-count A-adj-list) 2)
      (define edge-0 (gvector-ref A-adj-list 0))
      (define edge-1 (gvector-ref A-adj-list 1))
      (check-equal? (send edge-0 get-source) "A")
      (check-equal? (send edge-0 get-dest) "B")
      (check-equal? (send edge-0 get-weight) 10)
      (check-equal? (send edge-1 get-source) "A")
      (check-equal? (send edge-1 get-dest) "C")
      (check-equal? (send edge-1 get-weight) 20)
    )
  )
)