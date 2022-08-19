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





(setq reserved_words (make-hash-table :test 'equal)) ; reserved words

        ; Production Rules

;   Start
    (setq startInput '( "START" "INPUT" )) ;                           {printf("\n>>");}       
     

;   INPUT:
    
    (setq expi '("EXPI"))   ;                    { if(!isList) printf("Syntax OK.\nResult: %d",$1); else {isList=false; printf("Syntax OK.\nResult:("); for(int i=0; i<list.len-1; i++)printf("%d ",list.list[i]); printf("%d)",list.list[list.len-1]);} }
    (setq explisti '( "EXPLISTI"))    ;              { printf("Syntax OK.\nResult:("); for(int i=0; i<$1.len-1; i++)printf("%d ",$1.list[i]); printf("%d)",$1.list[$1.len-1]);  }
    (setq expb '( "EXPB" ))   ;                  { char *str="false"; if($1)str="true"; printf("Syntax OK.\nResult: %s",str); }

  


;   EXPB : 
   (setq expand '( "OP_OP" "KW_AND" "EXPB" "EXPB" "OP_CP"  ))    ;      {$$ = $3 & $4;}
    (setq expor '( "OP_OP" "KW_OR" "EXPB" "EXPB" "OP_CP"   ))     ;   {$$ = $3 | $4;}
    (setq expnot '("OP_OP" "KW_NOT" "EXPB" "OP_CP"         ))     ; {$$ = !($3); }
    (setq expequal1 '("OP_OP" "KW_EQUAL" "EXPI" "EXPI" "OP_CP" ))  ;     {$$ = $3 == $4;}
    (setq expequal2 '("OP_OP" "KW_EQUAL" "EXPB" "EXPB" "OP_CP"  ))  ;    {$$ = $3 == $4;}
    
    ;//| BinaryValue
    (setq exptrue '( "KW_TRUE" ));                               {$$ = 1;}
    (setq expfalse'( "KW_FALSE"));                           {$$ = 0;}
    






 
;   EXPI :                                      


    (setq eplus '( "OP_OP" "OP_PLUS" "EXPI" "EXPI" "OP_CP"  ) )        ;{$$ = $3 + $4;}
    (setq eminus '( "OP_OP" "OP_MINUS" "EXPI" "EXPI" "OP_CP" ) )     ;{$$ = $3 - $4;}
    (setq emult '( "OP_OP" "OP_MULT" "EXPI" "EXPI" "OP_CP"  ) )      ;{$$ = $3 * $4;}
    (setq ediv '( "OP_OP" "OP_DIV" "EXPI" "EXPI" "OP_CP"   ) )     ;{$$ = $3 / $4;}
    (setq eid '( "IDENTIFIER"                             ) )   ;{ int index = lookup(&ids,$1); if(index==-1) printf("%s is not ;declared",$1 ); else  $$=ids.valueTable[index]; }
    
    
    (setq eint '( "INTVALUE" ) )                                  ; /* IntegerValue  */          ;{$$ = $1; printf("expi");}
    ; //| "EXPI" EXPI;

    ; ASSIGNMENT;
    (setq eassign '( "OP_OP" "KW_SET" "IDENTIFIER" "EXPI" "OP_CP" ))    ;{ setId(&ids,$3,$4); $$=$4; }


    ;//    OP_OP defvar Id EXPI OP_CP     ;           // defining a variable
    (setq edefvar '( "OP_OP" "KW_DEFVAR" "IDENTIFIER" "EXPI" "OP_CP" ))    ;     { setId(&ids,$3,$4); $$=$4; }                  // setting a variable
        ;



    ; FUNCTIONS
    
    (setq edefun '( "OP_OP" "KW_DEFFUN" "IDENTIFIER" "IDLIST" "EXPLISTI" "OP_CP" ))   ;     {  } // DEFINITION
    (setq ecall '( "OP_OP" "IDENTIFIER" "EXPLISTI" "OP_CP"  ))                ;     {  } // CALL. PREDEFINEDS MUST BE ADDED
    
    
    ;//    OP_OP IDENTIFIER EXPI EXPI OP_CP                 ;  // CALL                   PREDEFINEDS MUST BE ADDED
    




;// CONTROL STATEMENTS                   ;
    (setq eifelse '( "OP_OP" "KW_IF" "EXPB" "EXPLISTI" "OP_CP" ))      ;         {if($3) $$=$4; }
    (setq eif '( "OP_OP" "KW_IF" "EXPB" "EXPLISTI" "EXPLISTI" "OP_CP" )) ;      {if($3) $$=$4; else  $$=$5;}
    (setq ewhile '( "OP_OP" "KW_WHILE" "OP_OP" "EXPB" "OP_CP" "EXPLISTI" "OP_CP" ))  ;
    (setq efor '( "OP_OP" "KW_FOR" "OP_OP" "IDENTIFIER" "EXPI" "EXPI" "OP_CP" "EXPLISTI" "OP_CP" )) ;



   ;EXPLISTI :
    (setq econcat'( "OP_OP" "KW_CONCAT" "EXPLISTI" "EXPLISTI" "OP_CP" ))  ; { for(int i=0; i<$4.len; i++) addItem(&$3,$4.list[i]); $$=$3;  }
    (setq eappend'( "OP_OP" "KW_APPEND" "EXPI" "EXPLISTI" "OP_CP"     ))  ; { addItem(&$4,$3); $$=$4; }
    (setq elistval'( "LISTVALUE"                                       ))  ; { $$=$1; }
    (setq enil'( "KW_NIL"))
    ;






(defun get_id_value (identifier)
    (gethash identifier reserved_words)
)

(defun set_id_value (identifier val)
    (setf (gethash identifier reserved_words) val )
)

(defun nth_val_in_match (n match_result)
    (kw-val (nth (+ n (first match_result)) stack))
)



(setq withvalues (list ))
(setq stack (list ))



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
  (:documentation "A bicycle.")
  )

(defun add (kw val) 
  	(setf withvalues (append withvalues (list (make-instance 'kw
                                            :name kw
                                            :val val))
	 ))
)       
      

       
 (defun print_withvalues ()          
    (print "withvalues:")
    (loop for a in withvalues                  
        do (write (kw-name a))
    )                 
 
 )
 
  
(defun print_stack ()
    (print "stack:")
    (loop for a in stack                  
        do (write (kw-name a))
    )
    (print "stack-vals:")
    (loop for a in stack                  
        do (write (kw-val a))
    )
    
)

 (defun shift ()        
        (setf stack (append stack (list (first withvalues) )))
        (setf withvalues (cdr withvalues)) 
        (reduce_expr)
 )
 
 

(defun is_match_from_start(stck mylist)
    (defvar res)
  
    (if (equal mylist nil) 
        (setq res T) 
        (if  stck 
            (if (equal (first mylist)  (kw-name (first stck)) )
                (is_match_from_start(cdr stck) (cdr mylist) )
               (setq res NIL) 
            )
            (setq res NIL)
        )
    )

    
    
    
)




(defun match(stck mylist count)
    (if (equal 0 (length stck) )
        NIL
        (if (is_match_from_start stck mylist)
            (values count (+ count (length mylist) -1) )       ;then
            (match (cdr stck) mylist (+ count 1))   ;else
        )
    )
)

(defun remove-nth-element (nth list)
(setq stack (cond
   ((equal nil list) list)
   ((zerop nth) (cdr list))
   (t (cons (car list)
            (remove-nth-element (- nth 1)
                                (cdr list))))))
                                )




(defun change (startIndex endIndex kw)      ; Removes the indexes between startIndex-endIndex. Puts kw between them in stack.
    (setf (nth startIndex stack) kw)
    (if (< startIndex endIndex )
        ( dotimes (n (- endIndex startIndex))
            ( remove-nth-element (+ 1 startIndex) stack)
        )
    )
)



;(is_match_from_start '("1") '( "1" "3" ))


(defun downgrade (from_list to_str)         
    
               ; (print "to ")
            ;    (write to_str)
                (setq new_kw to_str)
                (setq match_result (multiple-value-list (match stack from_list 0)))     ; matchresult- >(start end)
                
            ; val (setq new_val (get_id_value (nth_val_in_match 1 match_result ) ))
        
)

(defvar match_result)
    (defvar new_val 0)
    (defvar new_kw nil)


(defun reduce_expr ()
    
    

    (cond
             


        ; EXPLISTI

        (
            (match stack econcat 0)        ; identifier -> expi
            (downgrade econcat "EXPLISTI")
            ;val
        )
        
        (
            (match stack eappend 0)        ; identifier -> expi
            (downgrade eappend "EXPLISTI")
            ;val
        )
        
        (
            (match stack elistval 0)        ; identifier -> expi
            (downgrade elistval "EXPLISTI")
            ;val
        )
        
        (
            (match stack enil 0)        ; identifier -> expi
            (downgrade enil "EXPLISTI")
            ;val
        )




        ;; EXPB

         (
            (match stack expand 0)        ; identifier -> expi
            (downgrade expand "EXPB")
            ;val
        )


        (
            (match stack expor 0)        ; identifier -> expi
            (downgrade expor "EXPB")
            ;val
        )

        (
            (match stack expnot 0)        ; identifier -> expi
            (downgrade expnot "EXPB")
            ;val
        )


        (
            (match stack expequal1 0)        ; identifier -> expi
            (downgrade expequal1 "EXPB")
            ;val
        )

        (
            (match stack expequal2 0)        ; identifier -> expi
            (downgrade expequal2 "EXPB")
            ;val
        )

        (
            (match stack exptrue 0)        ; identifier -> expi
            (downgrade exptrue "EXPB")
            ;val
        )

        (
            (match stack expfalse 0)        ; identifier -> expi
            (downgrade expfalse "EXPB")
            ;val
        )



        

        

        ; EXPI   

            ;ASSIGNMENT

        (
            (match stack eassign 0)        ; identifier -> expi
            (downgrade eassign "EXPI")
            ;val
        )


        ;     
        (
            (match stack eint 0)        
            (progn
           ;     (print "eint")
                (setq match_result (multiple-value-list (match stack eint 0)))        
                (setq new_val (kw-val (nth (first match_result) stack))))
                (setq new_kw "EXPI")
            )
    
        (
            (match stack edefvar 0)
            (progn
          ;  (print "edefvar")
                (setq match_result (multiple-value-list (match stack edefvar 0)))        
                (setq iden (nth (+ 2 (first match_result)) stack))
                (setq id_val (nth (+ 3 (first match_result)) stack))
                
                (if(not (gethash iden reserved_words))
                    (setf (gethash iden reserved_words) id_val )
                    
                )
                    (setq new_val (gethash iden reserved_words))
                    (setq new_kw "EXPI")
                )
            )

        (
            (match stack eid 0)        ; identifier -> expi
            (progn
             ;   (print "eid")
                (setq match_result (multiple-value-list (match stack eid 0)))     ; matchresult- >(start end)
                (setq new_val (get_id_value (nth_val_in_match 1 match_result ) ))
                (setq new_kw "EXPI")
            )
        )



        (
            (match stack eplus 0)        ; identifier -> expi
            (progn
            ;    (print "eplus")
                (setq match_result (multiple-value-list (match stack eplus 0)))     ; matchresult- >(start end)
                ; val (setq new_val (get_id_value (nth_val_in_match 1 match_result ) ))
                (setq new_kw "EXPI")
                (setq new_val (+ (parse-integer (nth_val_in_match 2 match_result))    (parse-integer(nth_val_in_match 3 match_result)) ))   
            )
        )


        (
            (match stack emult 0)        ; identifier -> expi
            (progn
              ;  (print "emult")
                (setq match_result (multiple-value-list (match stack emult 0)))     ; matchresult- >(start end)
                ; val (setq new_val (get_id_value (nth_val_in_match 1 match_result ) ))
                (setq new_kw "EXPI")
                (setq new_val (* (parse-integer (nth_val_in_match 2 match_result))    (parse-integer(nth_val_in_match 3 match_result)) ))   
            )
        )



        (
            (match stack ediv 0)        ; identifier -> expi
            (progn
              ;  (print "ediv")
                (setq match_result (multiple-value-list (match stack ediv 0)))     ; matchresult- >(start end)
                ; val (setq new_val (get_id_value (nth_val_in_match 1 match_result ) ))
                (setq new_kw "EXPI")
                (setq new_val (/ (parse-integer (nth_val_in_match 2 match_result))    (parse-integer(nth_val_in_match 3 match_result)) ))   

            )
        )

        (
            (match stack eminus 0)        ; identifier -> expi
            (progn
              ;  (print "eminus")
                (setq match_result (multiple-value-list (match stack eminus 0)))     ; matchresult- >(start end)
                ; val (setq new_val (get_id_value (nth_val_in_match 1 match_result ) ))
                (setq new_kw "EXPI")

                (setq new_val (- (parse-integer (nth_val_in_match 2 match_result))    (parse-integer(nth_val_in_match 3 match_result)) ))   
            
            )
        )


        (
            (match stack expb 0)        ; identifier -> expi
            (progn
                (downgrade expb "INPUT")
                (print "Syntax OK.")
                (print "Result:")
                (write (nth_val_in_match 0 match_result ) )
                
            )
            ;val
        )



        (
            (match stack explisti 0)        ; identifier -> expi
            (progn
              ;  (print "explisti")
                (setq match_result (multiple-value-list (match stack explisti 0)))     ; matchresult- >(start end)
                ; val (setq new_val (get_id_value (nth_val_in_match 1 match_result ) ))
                (setq new_kw "INPUT")
            )
        )

        
        
        (
            (match stack expi 0)        ; identifier -> expi
            (progn
               ; (print "expi")
                (setq match_result (multiple-value-list (match stack expi 0)))     ; matchresult- >(start end)
                ; val (setq new_val (get_id_value (nth_val_in_match 1 match_result ) ))
                (setq new_kw "INPUT")

                (print "Syntax OK.")
                (print "Result:")
                (write (nth_val_in_match 0 match_result ) )
            )
        )

        
    
    )
 (if new_kw 
    (progn 
        (setq new_kw (make-instance 'kw
                                :name new_kw
                                :val new_val)
        )
        (change (first match_result) (second match_result) new_kw)
    )
 )
    
    
    (if (equal withvalues '()) (if (<= 1 (length stack)) 1 reduce) (shift) )
    
)


;;; main


(gppinterpreter)  ;; reading line
(set_structure)  ;Splits codes and reset the structure
(tknsize) ; finds in terms of token pairs


 
(shift)
(reduce_expr)
