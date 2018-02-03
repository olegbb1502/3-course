//-----------------------------------------------------------------------------
//
// Title       : function1
// Design      : mydesign
// Author      : Machine
// Company     : gypnor
//
//-----------------------------------------------------------------------------
//
// File        : function1.v
// Generated   : Thu Feb 16 18:22:26 2017
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
//{module {function1}}
module function1 ( a ,b ,c ,F1 );

input a ;
wire a ;
input b ;
wire b ;
input c ;
wire c ;

inout F1 ;
wire F1 ;

//}} End of automatically maintained section

assign #1 F1=!(a|b|c);

endmodule
