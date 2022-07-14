;   adding element to a sorted list

(defun add_to_sorted (my_list element)
    (if my_list 
        (if (< element (first my_list)) 
            (push element my_list)
            (progn
                (setq a (add_to_sorted (cdr my_list) element ) )   
                (push (car my_list) a )
            )
        )

        (push element my_list)

    )
 )

 (setq mlist '(1 6 9))
 
 (write (add_to_sorted mlist 10))








; sorting
(defun mysort (mylist)
    (if mylist
        (progn
            (put_smallest_top mylist)
            (setf a (mysort (cdr mylist)))
            (push (car mylist) a)
        )

        mylist
    )
)

; function for sorting
(defun put_smallest_top(mylist)

    (setf smallest 0)

    (loop for a from 0 to (- (length mylist) 1)
        do (
            if (< (nth a mylist) (nth smallest mylist)) 
                (setf smallest a)
                (setf smallest smallest)
            
        )
    )
    (setf backup (first mylist))
    (setf (first mylist) (nth smallest mylist))
    (setf (nth smallest mylist) backup)
    mylist

)

(write
    (mysort '(2 7 3 1 8))
)






; (1 2 3 4 5) --> (2 1 4 3 5)
(defun swap2 (mylist)
    (if (< 1 (length mylist)) 
        (progn
            (setf backup (first mylist))
            (setf (first mylist) (second mylist))
            (setf (second mylist) backup)
            (setf a(swap2 (cddr mylist)))
            (push (second mylist) a)
            (push (first mylist) a)
        )
        mylist
    )    
)

(write
    (swap2 '(1 2 3 4 5))
)



; (1 2 3 4 5),(11 12 13 14 15 16) --> ( (1 11) (2 12) (3 13) (4 14) (5 15) (-1 16) )
(defun pairup (list1 list2 )
    (cond 
        (
            (and list1 list2)
            (setf (first list1) (list (first list1) (first list2)  ) )
        )
    
        (
            (and list1 list1)
                (setf (first list1) (list (first list1) -1  ) )
            
        )

        (
            (and list2 list2)
                (setf list1 (list (list -1 (first list2)) ) )
            
        )

        
    )

    (if (or list1 list2)
        
        (progn
            (setf a ( pairup (cdr list1) (cdr list2) ))
            (push (car list1) a)
        )
        list1
    )

)

(write 
    (pairup '(1 2 3 4 5 6 7) '(11 12 13 14 15 16) )
)


























