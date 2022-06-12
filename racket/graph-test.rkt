#lang racket

(require rackunit)
(require rackunit/text-ui)
(require "graph.rkt")

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
      
      (check-true (null? (send g get-adj-list "A")))
      (check-true (null? (send g get-adj-list "B")))
      (check-true (null? (send g get-adj-list "C")))

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
      
    )
  )
)

(run-tests graph-tests)