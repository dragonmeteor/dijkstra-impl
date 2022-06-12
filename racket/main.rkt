#lang racket

(require "graph.rkt")

(define args (current-command-line-arguments))

(if (< (vector-length args) 2)
  (display "Usage: racket main.rkt <input-file-name> <output-file-name>\n")  
  (begin
    (display (string-append "input-file-name = " (vector-ref args 0) "\n"))
    (display (string-append "output-file-name = "(vector-ref args 1) "\n"))
  )
)