#lang racket

(require rackunit)
(require "graph.rkt")
(require "dijkstra.rkt")
(require data/gvector)

(provide dijkstra-tests)

(define dijkstra-tests 
  (test-suite "run-dijkstra tests"
    (test-case "Single vertex graph"
      (define g (new graph%))
      (send g add-vertex! "A")
      
      (define result (run-dijkstra g "A"))

      (check-eq? (send result get-source) "A")
      (check-eq? (send result get-distance "A") 0.0)
      (check-eq? (send result get-pred "A") "A")
    )

    (test-case "Source not in the graph"
      (define g (new graph%))
      (send g add-vertex! "A")
      
      (check-exn exn:fail? (lambda () (run-dijkstra g "B")))
    )

    (test-case "Two vertices graph"
      (define g (new graph%))
      (send g add-vertex! "A")
      (send g add-vertex! "B")
      (send g add-edge! "A" "B" 1.0)
      
      (define result (run-dijkstra g "A"))

      (check-eq? (send result get-source) "A")

      (check-within (send result get-distance "A") 0.0 1e-4)
      (check-eq? (send result get-pred "A") "A")

      (check-within (send result get-distance "B") 1.0 1e-4)
      (check-eq? (send result get-pred "B") "A")
    )

    (test-case "Three vertices graph"
      (define g (new graph%))
      (send g add-vertex! "A")
      (send g add-vertex! "B")
      (send g add-vertex! "C")
      (send g add-edge! "A" "B" 10.0)
      (send g add-edge! "B" "C" 10.0)
      (send g add-edge! "A" "C" 30.0)

      (define result (run-dijkstra g "A"))

      (check-within (send result get-distance "A") 0.0 1e-4)
      (check-within (send result get-distance "B") 10.0 1e-4)
      (check-within (send result get-distance "C") 20.0 1e-4)
    )

    (test-case "Unreachable vertices"
      (define g (new graph%))
      (send g add-vertex! "A")
      (send g add-vertex! "B")
      (send g add-vertex! "C")
      (send g add-vertex! "D")
      (send g add-edge! "A" "B" 10.0)
      (send g add-edge! "C" "D" 10.0)

      (define result (run-dijkstra g "A"))

      (check-within (send result get-distance "A") 0.0 1e-4)
      (check-within (send result get-distance "B") 10.0 1e-4)
      (check-false (send result has-distance? "C"))
      (check-false (send result has-distance? "D"))
    )
  )
)