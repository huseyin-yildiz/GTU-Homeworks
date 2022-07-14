% Rooms

room(z06,30).
room(z23,80).

capacity(30,z06).
capacity(80,z06).



special_equipment(projector,z06).
special_equipment(projector,z23).
special_equipment(smart_board,z23).


% Courses
course(cse341, yakup_genc, 25).
course_student(huseyin_yildiz,cse341).
course_student(osman_aydin,cse341).
course_need(projector,cse341).
course_hour(14,cse341,z06).
course_hour(15,cse341,z06).
course_hour(8,cse341,z23).
course_hour(9,cse341,z23).
course_hour(9,cse351,z23).     % conflict




%instructor
course_instructor(101,yakup_genc).
preference(projector,yakup_genc).


% student
student(201,huseyin_yildiz).
student(202,osman_aydin).
student(203,veli_yilmaz).
handicapped(veli_yilmaz).

hours(X) :- between(0, 23, X).


% predicates
bussy_at(Room,Hour) :-  course_hour(Hour,_,Room).

free_hour(Room,X) :- between(0,23,X), not(bussy_at(Room,X)).


schedule_conflict() :- course_hour(A,B,C), course_hour(A,Z,C), B \= Z, write('There is conflict').


%course_size(Course,Size,0) :- course_student(_,Course), Size is 1.
%course_size(Course,Size) :- course_student(_,Course); Size is 0.
%course_size(Course,Size,0) :- course_student(_,Course) Size1 is Size + 1, course_size(Course,Size1).



%appropriate_rooms(Course) :- course_hour(Hour,Course,_), room(Room,_),course_hour(Hour2,) 