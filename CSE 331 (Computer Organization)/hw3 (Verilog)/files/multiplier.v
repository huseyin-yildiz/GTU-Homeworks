module Full_Adder_Structural_Verilog( 
  input X1, X2, Cin, 
  output S, Cout
  );  
    wire a1, a2, a3;    
    xor u1(a1,X1,X2);
 and u2(a2,X1,X2);
 and u3(a3,a1,Cin);
 or u4(Cout,a2,a3);
    xor u5(S,a1,Cin); 
endmodule  





module rightShift64(
    input  [63:0] a,
    output [63:0] res 
);
wire w[63:0];


genvar i;
generate
for(i=0; i<63; i=i+1)
begin: shifting
    assign res[i] = a[i+1];
end
endgenerate

assign res[0] = 0;


endmodule



module tb_Shift();
 reg [63:0] A;
 wire [63:0] out;  
 
 rightShift64 rs1(
    .a(A),
    .res(out) 
   );
 initial begin
   A = 1265;
     #250

  
  
$monitor("RIGHTSHIFT64 time = %1d, a =%1b, out=%1b", $time, A,out);
  end
      
endmodule 









// equality comparator (32 bit)

module equal5(
    input [4:0] a,b,
    output res
);
wire [4:0] xored, noted;


genvar i;
generate
for(i=0; i<4; i=i+1)
begin: isEqual
    xor(xored[i], a[i], b[i]);
    not(noted[i],xored[i]);
end
endgenerate


and(res,  noted[0] , noted[1] , noted[2] , noted[3]);
endmodule




module tb_equality();
 reg [4:0] A,B;
 wire  out;  
 
 equal5 eq1(
    .a(A),
    .b(B),
    .res(out) 
   );
 initial begin
   A = 1265;
   B = 1265;
     #260

  
  
$monitor("EQUAL32 time = %1d, a =%1b, b =%1b,  out=%1b", $time, A,B,out);
  end
      
endmodule 







module mux3_8(
    input a0, a1,a2,a3,a4,a5,a6,a7,
    input [2:0] s,
    output  res
);

wire a[7:0];

assign a[0] = a7;
assign a[1] = a6;
assign a[2] = a5;
assign a[3] = a4;
assign a[4] = a3;
assign a[5] = a2;
assign a[6] = a1;
assign a[7] = a0;



wire w[7:0];
  
 
and(w[7], ~s[0], ~s[1], ~s[2], a[7] );
and(w[6], s[0], ~s[1], ~s[2], a[6] );
and(w[5], ~s[0], s[1], ~s[2], a[5] );
and(w[4], s[0], s[1], ~s[2], a[4] );
and(w[3], ~s[0], ~s[1], s[2], a[3] );
and(w[2], s[0], ~s[1], s[2], a[2] );
and(w[1], ~s[0], s[1], s[2], a[1] );
and(w[0], s[0], s[1], s[2], a[0] );

or(res,w[0], w[1], w[2], w[3], w[4], w[5], w[6], w[7]);

endmodule





module tb_mux3_8();
 reg [7:0] A;
 reg [2:0] S;
 wire  out;
 reg zero = 0;
 
 mux3_8 mux1(
    .a0(zero),.a1(zero),.a2(zero),.a3(zero),.a4(zero),.a5(zero),.a6(zero),.a7(~zero),
    .s(S),
    .res(out) 
   );
 initial begin
   A = 1;
   S = 7;
    #260

  
  
$monitor("MUX3_8 time = %1d, a =%1b, s=%1b, out=%1b", $time, A,S,out);
  end
      
endmodule 





module adder5(
    input  [4:0] a,b,
    output [4:0] res,
    input isSub
    
);

wire   [4:0] couts, xored;

xor(xored[0],b[0],isSub); 
Full_Adder_Structural_Verilog f1(a[0],xored[0],isSub,res[0],couts[0]);
genvar i;
generate
for(i=1; i<5; i=i+1)
begin: adding
    xor(xored[i],b[i],isSub);
    Full_Adder_Structural_Verilog f(a[i],xored[i],couts[i-1],res[i],couts[i]);
end
endgenerate



endmodule










module datapath(
    input ipp, prAssign, shiftOrProduct,init,
    output mult0, equal,
    output [4:0]i_val
    
);



wire [4:0] i_added, i_muxed;

reg [4:0] zero5 = 0;
reg [4:0] one5  = 0;
reg one = 1;
wire [2:0] sel;
assign sel[0] = init;
assign sel[1] = ipp;
assign sel[2] = zero;


adder5 adding1(i_muxed, one5, i_added, zero );


genvar in;
generate
for(in=0; in<4; in=in+1)
begin: muxing
    
    mux3_8 m(one , one, one,one,one,one,one,one,
    sel,
    i_muxed[in]);
end
endgenerate

assign i_val = i_muxed;



endmodule


module tb_dataPath();
 
 
 wire  mul0, equal;
 wire [4:0] i_val;
 reg zero = 0;
 
 
 datapath dp(
 .ipp(zero), 
 .prAssign(zero), 
 .shiftOrProduct(zero),
 .init(one),
 .mult0(mul0),
 .equal(equal),
 .i_val(i_val)
   );
 initial begin
   
#290
  
  
$monitor("MUX3_8 time = %1d,  out=%1d", $time, i_val);
  end
      
endmodule 







