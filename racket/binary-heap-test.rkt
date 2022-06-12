#lang racket

(require rackunit)
(require "binary-heap.rkt")

(provide binary-heap-tests)

(define binary-heap-tests
  (test-suite "binary-heap% tests"
    (test-case "creation should behave sensibly"
      (define heap (new binary-heap%))
      (check-eq? (send heap count) 0)
      (check-true (send heap empty?))
      (send heap check-rep)
    )

    (test-case "add-raw! should behave sensibly"
      (define heap (new binary-heap%))
      (send heap add-raw! "A" 10)
      (send heap add-raw! "B" 20)
      (send heap add-raw! "C" 30)
      (check-eq? (send heap count) 3)
      (check-false (send heap empty?))
      (send heap check-rep)
    )

    (test-case "is-heap-order? (true case)"
      (define heap (new binary-heap%))
      (send heap add-raw! "A" 10)
      (send heap add-raw! "B" 20)
      (send heap add-raw! "C" 30)
      (check-true (send heap is-heap-order?))
    )

    (test-case "is-heap-order? (false case)"
      (define heap (new binary-heap%))
      (send heap add-raw! "A" 30)
      (send heap add-raw! "B" 20)
      (send heap add-raw! "C" 10)      
      (check-false (send heap is-heap-order?))
    )

    (test-case "build"
      (define heap (new binary-heap%))
      (send heap add-raw! "A" 30)
      (send heap add-raw! "B" 20)
      (send heap add-raw! "C" 10)
      (send heap build)
      (send heap check-rep)
      (check-true (send heap is-heap-order?))      
    )

    (test-case "add!"
      (define heap (new binary-heap%))
      (send heap add! "A" 30)
      (send heap add! "B" 20)
      (send heap add! "C" 10)
      (send heap check-rep)
      (check-true (send heap is-heap-order?))
    )

    (test-case "has-object?"
      (define heap (new binary-heap%))
      (send heap add! "A" 30)
      (send heap add! "B" 20)
      (send heap add! "C" 10)
      (check-true (send heap has-object? "A"))
      (check-true (send heap has-object? "B"))
      (check-true (send heap has-object? "C"))
      (check-false (send heap has-object? "D"))
      (check-false (send heap has-object? "E"))
      (check-false (send heap has-object? "F"))
    )

    (test-case "get-value"
      (define heap (new binary-heap%))
      (send heap add! "A" 30)
      (send heap add! "B" 20)
      (send heap add! "C" 10)
      (check-eq? (send heap get-value "A") 30)
      (check-eq? (send heap get-value "B") 20)
      (check-eq? (send heap get-value "C") 10)
      (check-exn exn:fail? (lambda () (send heap get-value "D")))
      (check-exn exn:fail? (lambda () (send heap get-value "E")))
      (check-exn exn:fail? (lambda () (send heap get-value "F")))
    )

    (test-case "change-value!"
      (define heap (new binary-heap%))
      (send heap add! "A" 30)
      (send heap add! "B" 20)
      (send heap add! "C" 10)
      (send heap change-value! "A" 0)
      (send heap check-rep)      
      (check-eq? (send heap get-value "A") 0)      
      (check-true (send heap is-heap-order?))
    )
  )
)

