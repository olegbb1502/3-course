//-----------------------------------------------------------------------------
//
// Title       : func12
// Design      : mydesign
// Author      : Machine
// Company     : gypnor
//
//-----------------------------------------------------------------------------
//
// File        : func12.v
// Generated   : Fri Feb 17 13:19:33 2017
// From        : interface description file
// By          : Itf2Vhdl ver. 1.21
//
//-----------------------------------------------------------------------------
//
// Description : 
//
//-----------------------------------------------------------------------------
`timescale 1 ns / 1 ps

//{{ Section below this comment is automatically maintained
//   and may be overwritten
//{module {func12}}
module func12 ( a ,b ,c ,f1 ,f2 );

output f1 ;
wire f1 ;
output f2 ;
wire f2 ;

input a ;
wire a ;
input b ;
wire b ;
input c ;
wire c ;

//}} End of automatically maintained section

assign #1 f1=!(a|b|c);
assign #1 f2=!(a)&!(b)|c;

endmodule
