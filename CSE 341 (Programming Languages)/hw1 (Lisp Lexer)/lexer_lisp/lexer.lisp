(setq lex(list 1))
(setq lists(list 1) )		; all required global lists
(setq lximals(list 1))
(setq tkns(list 1))
(setq withvalues (list))

(defclass kw ()
  ((name :accessor kw-name
          :initarg :name
          :type str
          )
    
    (val :accessor kw-val
          :initarg :val
          :type integer
          )
          
    )
  )


(defun tknsize()
	(setq i 1)
	(setq len(length lximals))

	(loop		; finding pair of 
		(setq item(nth i lximals))
		(cond((equal item "and")
				(setq m "KW_AND")
				(push m(cdr (last tkns)))
			)
			((equal item "or")
				(setq m "KW_OR")
				(push m(cdr (last tkns)))
			)
			((equal item "not")	(setq m "KW_NOT") (push m(cdr (last tkns)))  )
			((equal item "equal")	(setq m "KW_EQUAL") (push m(cdr (last tkns))));equal item "equal"
			((equal item "less")	(setq m "KW_LESS") (push m(cdr (last tkns))));equal item "less"
			((equal item "nil")	(setq m "KW_NIL") (push m(cdr (last tkns))) )
			((equal item "list")	(setq m "KW_LIST") (push m(cdr (last tkns)))	)
			((equal item "append") (setq m "KW_APPEND")(push m(cdr (last tkns))))
			((equal item "concat") (setq m "KW_CONCAT") (push m(cdr (last tkns))))
			((equal item "set") (setq m "KW_SET")(push m(cdr (last tkns))))
			((equal item "deffun") (setq m "KW_DEFFUN") (push m(cdr (last tkns))))
			((equal item "for") (setq m "KW_FOR") (push m(cdr (last tkns))) )
			((equal item "if") (setq m "KW_IF") (push m(cdr (last tkns))) )
			((equal item "exit") (setq m "KW_EXIT")		(push m(cdr (last tkns))) )
			((equal item "load") (setq m "KW_LOAD") (push m(cdr (last tkns))))
			((equal item "disp") (setq m "KW_DISP") (push m(cdr (last tkns))))
			((equal item "true") (setq m "KW_TRUE") (push m(cdr (last tkns))))
			((equal item "false") (setq m "KW_FALSE") (push m(cdr (last tkns))))
			((equal item "+") (setq m "OP_PLUS") (push m(cdr (last tkns))))
			((equal item "-") (setq m "OP_MINUS") (push m(cdr (last tkns))))
			((equal item "/") (setq m "OP_DIV") (push m(cdr (last tkns))))
			((equal item "*")(setq m "OP_MULT") (push m(cdr (last tkns))))
			((equal item "(") (setq m "OP_OP") (push m(cdr (last tkns))))
			((equal item ")") (setq m "OP_CP") (push m(cdr (last tkns))))
			((equal item "**") (setq m "OP_DBL_MULT") (push m(cdr (last tkns))))
			((equal item "“") (setq m "OP_OC")(push m(cdr (last tkns))))
			((equal item "“") (setq m "OP_CC") (push m(cdr (last tkns))))
			((equal item ",")	(setq m "OP_COMMA") (push m(cdr (last tkns))) )
			((every #'digit-char-p item)	(setq x(subseq item 0 1))
				(setq lng(length item)) (cond((equal x "0") (cond((equal lng 1)
								(setq m "INTVALUE") (push m(cdr (last tkns))))(t (setq m "ERROR") (push m(cdr (last tkns))))))
			(t (setq m "INTVALUE") (push m(cdr (last tkns)))		)
			))
			
			(t
				(setq x(subseq item 0 1))
				(cond((equal x ";")	(setq m "COMMENT")	(push m(cdr (last tkns)))) (t	(cond((every #'digit-char-p x)	
				(setq m "ERROR") (push m(cdr (last tkns))) );
							(t (setq m "IDENTIFIER") (push m(cdr (last tkns)))))))	)
							
			)
			
	 										
	(setf withvalues (append withvalues (list (make-instance 'kw
                                            :name m
                                            :val item))
	 ))
	(setq i(+ i 1)) (when(>= i len)(return i))	)
)



; Output to the files
(defun allwrite(fname l)
	(setq aasd "file.out")
	(with-open-file (out fname :direction :output :if-exists :new-version :if-does-not-exist :create)
		(dolist (segment l)
			(format out "~{~a~^ ~%~}" segment)
		)
		(format out "~%")

	)
)
	
	



(defun betwened (str)		; single one keywords(operators, space etc.) spliting
	(setq i 0)	(setq j 1)
	(setq hold "")
	(setq len (length str))
	
	
	(loop (setq x(subseq str i j)) (cond((or (equal x " ")(equal x "	")) (push hold(cdr (last lex)))		(setq hold "")	)(t
				(cond((equal x ";") (push hold(cdr (last lex))) (setq adel x)
						(setq hold "") (push str(cdr (last lex)))
						(setq qwer i) (setq i len))(t
						(cond((equal x "(") (push hold(cdr (last lex))) (setq hold "") (push x(cdr (last lex)))) 	((equal x ")") (push hold(cdr (last lex)))
						 (setq hold "") (setq adel x) (setq acv(list 1)) (setq adel x)			(push x(cdr (last lex))))
							(t (setq u(concatenate 'string hold x)) (setq hold u) (cond((>= i (- len 1))
										(push hold(cdr (last lex))) (setq asdq x)
										(setq hold "") )
								)))))))(setq i(+ i 1)) (setq abff 3)(setq j(+ j 1))		(when(>= i len)(return i)))
)





(defun gppinterpreter()
	(setq fname(nth 0 *args*))
	(cond((equal fname nil)	; Extracts string from file
			(setq isIt 0)
			(setq incoming(read-line))
			(betwened incoming)
		)
		(t			(with-open-file (file fname)
				(loop for i from 0 for ln = (read-line file nil nil) while ln
					do(setq l ln) (betwened l)
				)))))

(defun set_structure()
	(setq len(length lex)) (setq i 1)	(setq alist(list 1))(loop	
	(setq item(nth i lex)) (cond((equal item "")	)	
		(t (push item(cdr (last lximals))) )) (setq i(+ i 1))(when(>= i len)(return i)))

)






(gppinterpreter)  ;; reading file and fetching string calling required funcs
(set_structure)  ;Splits codes and reset the structure
(tknsize) ; finds in terms of token pairs
(allwrite "result.txt" (list (cdr tkns)))		; writes the results to the file
(print tkns)
(print "values:")


           
(loop for a in withvalues                  
    do (print (kw-name a))
 )                 

(write-line "Results saved to the result.txt" )
