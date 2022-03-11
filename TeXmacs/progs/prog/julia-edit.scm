
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MODULE      : julia-edit.scm
;; DESCRIPTION : Editing julia programs
;; COPYRIGHT   : (C) 2022
;;
;; This software falls under the GNU general public license version 3 or later.
;; It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
;; in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(texmacs-module (prog julia-edit)
  (:use (prog prog-edit)))

(tm-define (get-tabstop)
    (:mode in-prog-julia?)
    2)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Automatic indentation
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tm-define (julia-unindent-end)
  (insert "end")
   (and-with doc (program-tree)
     (let* ((r (program-row-number)))
     (display* (tree->string (tree-ref doc r)) "\n")
     (if (== (string-trim-both (tree->string (tree-ref doc r))) "end")
        (program-indent #t))
   ))
  )
     
; FIXME: '#' in a string is interpreted as a comment
(define (strip-comment-buggy s)
  "Removes comment from julia line."
  (with i (string-index s #\#)
    (if i (string-take s i) s)))

(tm-define (program-compute-indentation doc row col)
  (:mode in-prog-julia?)
  (if (<= row 0) 0
      (let* ((r (program-row (- row 1)))
             (r (if r r ""))
             ;;(s (string-trim-right (strip-comment-buggy (if r r ""))))
             (i (string-get-indent r))
             (s (string-trim r)))
        (display* i "\n")
        (if (or (string-starts? s "if") (string-starts? s "else") 
                  (string-starts? s "elseif") (string-starts? s "function")
                  (string-starts? s "let") (string-starts? s "while")
                  (string-starts? s "for"))
               (+ i (get-tabstop)) i))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Automatic insertion, highlighting and selection of brackets and quotes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tm-define (julia-bracket-open lbr rbr)
  (bracket-open lbr rbr "\\"))

(tm-define (julia-bracket-close lbr rbr)
  (bracket-close lbr rbr "\\"))

; TODO: select strings first
;(tm-define (kbd-select-enlarge)
;  (:require prog-select-brackets?)
;  (:mode in-prog-julia?)
;  (program-select-enlarge "(" ")"))

(tm-define (notify-cursor-moved status)
  (:require prog-highlight-brackets?)
  (:mode in-prog-julia?)
  (select-brackets-after-movement "([{" ")]}" "\\"))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Copy and Paste
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tm-define (kbd-paste)
  (:mode in-prog-julia?)
  (clipboard-paste-import "julia" "primary"))
