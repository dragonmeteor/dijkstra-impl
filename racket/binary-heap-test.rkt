#lang racket

(require rackunit)
(require "binary-heap.rkt")

(provide binary-heap-tests)

(define binary-heap-tests
  (test-suite "binary-heap% tests"
    (test-case "creation should behave sensibly"
      (define heap (new binary-heap%))
      (check-eq? (send heap size) 0)
      (check-true (send heap empty?))
    )
  )
)

