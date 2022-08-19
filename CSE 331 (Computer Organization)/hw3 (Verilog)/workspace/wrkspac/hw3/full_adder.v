module full_adder(   
  
  output result, Cout,
  input a, b, cin 
  
  );  
    wire w1, w2, w3;    
    xor u1(w1,a,b);
 and u2(w2,a,b);
 and u3(w3,w1,cin);
 or u4(Cout,w2,w3);
    xor u5(result,w1,cin); 

endmodule




