#lang racket

(require "graph.rkt")
(require "dijkstra.rkt")

(define args (current-command-line-arguments))

(when #f
  (if (< (vector-length args) 2)
    (display "Usage: racket main.rkt <input-file-name> <output-file-name>\n")  
    (begin
      (display (string-append "input-file-name = " (vector-ref args 0) "\n"))
      (display (string-append "output-file-name = "(vector-ref args 1) "\n"))
    )
  )
)

;(define g (new graph%))
;(send g add-vertex! "A")
;(send g add-vertex! "B")
;(send g add-edge! "A" "B" 1.0)

;(define result (run-dijkstra g "A"))