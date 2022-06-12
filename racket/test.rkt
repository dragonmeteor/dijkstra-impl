#lang racket

(require "graph-test.rkt")
(require "binary-heap-test.rkt")
(require rackunit/text-ui)

(run-tests graph-tests)
(run-tests binary-heap-tests)