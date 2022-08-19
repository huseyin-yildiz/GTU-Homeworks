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


// fpga4student.com 
// FPGA projects, VHDL projects, Verilog projects 
// Verilog code for full adder 
// Testbench code of the structural code for full adder 
//`timescale 10ns/ 10ps;
module Testbench_structural_adder();
 reg A,B,Cin;
 wire S,Cout;  
 //Verilog code for the structural full adder 
 Full_Adder_Structural_Verilog structural_adder(
    .X1(A),
    .X2(B),
    .Cin(Cin),
    .S(S),
    .Cout(Cout) 
   );
 initial begin
   A = 0;
   B = 0;
   Cin = 0;
   #10;
   A = 0;
   B = 0;
   Cin = 1;
   #10;  
   A = 0;
   B = 1;
   Cin = 0;
   #10;
   A = 0;
   B = 1;
   Cin = 1;
   #10;
   A = 1;
   B = 0;
   Cin = 0;
   #10;
   A = 1;
   B = 0;
   Cin = 1;
   #10;
   A = 1;
   B = 1;
   Cin = 0;
   #10;  
   A = 1;
   B = 1;
   Cin = 1;
   #10;  
  end
  
  initial
begin
$monitor("time = %2d, a =%1b, b=%1b, carry_in=%1b, sum=%1b, carry_out=%1b", $time, A, B, Cin, S, Cout);
end
      
endmodule 






// 
module adder(
    input  [31:0] a,b,
    output [31:0] res,
    input isSub,
    output overflow
);

wire   [31:0] couts, xored;

xor(xored[0],b[0],isSub); 
Full_Adder_Structural_Verilog f1(a[0],xored[0],isSub,res[0],couts[0]);
genvar i;
generate
for(i=1; i<32; i=i+1)
begin: adding
    xor(xored[i],b[i],isSub);
    Full_Adder_Structural_Verilog f(a[i],xored[i],couts[i-1],res[i],couts[i]);
end
endgenerate

xor(overflow,couts[31],couts[30]);

endmodule






module tb_N_bit_adder;
 // Inputs
 reg [31:0] input1;
 reg [31:0] input2;
 reg isSub;
 wire overflow;
 // Outputs
 wire [31:0] answer, test;

 // Instantiate the Unit Under Test (UUT)
 adder uut (
  .a(input1), 
  .b(input2), 
  .res(answer),
  .isSub(isSub),
  .overflow(overflow)
 );

 initial begin
  // Initialize Inputs
  input1 = 54565;
  input2 = 4565;
  isSub = 1;
  
  
  
  #100;
  
  

  // Add stimulus here
  $monitor("time = %2d, a =%1d, b=%1d, sum=%1d  overflow:%1b ", $time, input1, input2, answer,overflow );


      end
  
endmodule



module xor32(
    input  [31:0] a,b,
    output [31:0] res
);


genvar i;
generate
for(i=0; i<32; i=i+1)
begin: xoring
    xor x(res[i],a[i],b[i]);
end
endgenerate
endmodule



module tb_xor();
 reg [31:0] A,B;
 wire [31:0] out;  
 //Verilog code for the structural full adder 
 xor32 xor1(
    .a(A),
    .b(B),
    .res(out) 
   );
 initial begin
   A = 1265;
   B = 598;
   #10;  
   A = 0;
   B = 1;
   #10;
   A = 1;
   B = 0;
   #10;
   A = 1;
   B = 1;
   #10;  
  end
  
  initial
begin
$monitor("time = %2d, a =%1b, b=%1b out=%1b", $time, A, B,out);
end
      
endmodule 









module slt32(
input [31:0] a,b,
output [31:0] out
);

wire[31:0] sub;
wire overflow;
reg isSub = 1, zero = 0;

adder f(a,b,sub,isSub,overflow);
xor(out[0],sub[31],zero);

endmodule



module tb_slt();
 reg [31:0] A,B;
 wire [31:0] out;  
 //Verilog code for the structural full adder 
 slt32 slt(
    .a(A),
    .b(B),
    .out(out) 
   );
 initial begin
   A = 1265;
   B = 598;
   #50;  
   A = 666;
   B = 7777;
   #50;
   A = 55;
   B = 55;
   #50;
   A = 61;
   B = 61;
   #50;  

$monitor("time = %2d, a =%1d, b=%1d out=%1b ", $time, A, B,out);
  end

  
  initial
begin
$monitor("time = %2d, a =%1d, b=%1d out=%1b", $time, A, B,out);
end
      
endmodule 






module nor32(
    input  [31:0] a,b,
    output [31:0] res
);


genvar i;
generate
for(i=0; i<32; i=i+1)
begin: noring
    nor n(res[i],a[i],b[i]);
end
endgenerate
endmodule



module tb_nor();
 reg [31:0] A,B;
 wire [31:0] out;  
 //Verilog code for the structural full adder 
 nor32 nor1(
    .a(A),
    .b(B),
    .res(out) 
   );
 initial begin
   A = 1265;
   B = 598;
     #220

  
  
$monitor("time = %1d, a =%1b, b=%1b out=%1b", $time, A, B,out);
  end
      
endmodule 








module and32(
    input  [31:0] a,b,
    output [31:0] res
);


genvar i;
generate
for(i=0; i<32; i=i+1)
begin: anding
    and a(res[i],a[i],b[i]);
end
endgenerate
endmodule



module tb_and();
 reg [31:0] A,B;
 wire [31:0] out;  
 //Verilog code for the structural full adder 
 and32 and1(
    .a(A),
    .b(B),
    .res(out) 
   );
 initial begin
   A = 1265;
   B = 598;
     #230

  
  
$monitor("time = %1d, a =%1b, b=%1b out=%1b", $time, A, B,out);
  end
      
endmodule 











module or32(
    input  [31:0] a,b,
    output [31:0] res
);


genvar i;
generate
for(i=0; i<32; i=i+1)
begin: oring
    or o(res[i],a[i],b[i]);
end
endgenerate
endmodule



module tb_or();
 reg [31:0] A,B;
 wire [31:0] out;  
 //Verilog code for the structural full adder 
 or32 or1(
    .a(A),
    .b(B),
    .res(out) 
   );
 initial begin
   A = 1265;
   B = 598;
     #240

  
  
$monitor("OR32 time = %1d, a =%1b, b=%1b out=%1b", $time, A, B,out);
  end
      
endmodule   

