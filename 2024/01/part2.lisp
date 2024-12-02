#!/usr/bin/sbcl --script

(defun split-input (s)
  "We iter from start, and each time we see a space we go to 3 char after
  (the column are separated in the input by 3 space chars)"
  (loop for i = 0 then (+ j 3)
    as j = (position #\Space s :start i)
    collect (parse-integer (subseq s i j))
    while j))

(defun list-of-couple-to-couple-of-list (l)
  (list
    (mapcar #'car l)
    (mapcar #'cadr l)
  )
)

(defun parse-file (filename)
  (with-open-file (stream filename)
    (loop for line = (read-line stream nil)
          while line
          collect (split-input line))))

(defun calculate-similarity (lists)
  (apply '+ 
    (loop for i in (car lists)
        collect (* i
          (count i (cadr lists))
        )
    )
  )
)

(defun get-input (filename)
  (list-of-couple-to-couple-of-list (parse-file filename))
)

(write (calculate-similarity (get-input "input.txt")))
