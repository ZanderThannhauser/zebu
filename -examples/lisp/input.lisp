
(* (+ 1 2) (- 5 3))

(/ (+ 1 2 3 4 5) 5)

(* (+ 3 5 7 11) (- 23 5 7))

(concat `(+) (prepend 1 `(2 3)) (append `(4 5) 6))

(strconcat "abc" "def")

(map ^ `(1 2 3) `(4 5 6))

(list (& #t #t) (& #t #f) (& #f #t) (& #f #f))
(list (| #t #t) (| #t #f) (| #f #t) (| #f #f))

(map (lambda `(x y) `(+ (* x y) y)) `(2 3 4) `(5 6 7))

"fibonacci numbers:"

(define `fib
	(lambda `(x) `(if (< x 2) `x `(+ (fib (- x 1)) (fib (- x 2)))))
	`(map fib (range 10)))

"prime numbers (after 1):"

(filter
	(lambda `(x) `(reduce & (map (lambda `(y) `(bool (% x y))) (range 2 x)) #t))
	(range 2 100))

"q-sorted numbers:"

(define `qsort
	(lambda `(x)
		`(if (> (len x) 1)
			`(define `f (first x) `(concat
				(qsort (filter (lambda `(e) `(< e f)) x))
				(filter (lambda `(e) `(= e f)) x)
				(qsort (filter (lambda `(e) `(> e f)) x))))
			`x))
	`(qsort `(1 5 2 3 8 7 9 0 6 4)))























