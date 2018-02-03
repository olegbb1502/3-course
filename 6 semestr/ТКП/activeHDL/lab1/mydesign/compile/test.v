//-----------------------------------------------------------------------------
//
// Title       : test
// Design      : mydesign
// Author      : Unknown
// Company     : Unknown
//
//-----------------------------------------------------------------------------
//
// File        : d:\University\Katya\university\6 semestr\“ œ\activeHDL\lab1\mydesign\compile\test.v
// Generated   : Wed Feb 22 11:19:47 2017
// From        : d:\University\Katya\university\6 semestr\“ œ\activeHDL\lab1\mydesign\src\test.bde
// By          : Bde2Verilog ver. 2.01
//
//-----------------------------------------------------------------------------
//
// Description : 
//
//-----------------------------------------------------------------------------

`ifdef _VCP
`else
`define library(a,b)
`endif


// ---------- Design Unit Header ---------- //
`timescale 1ps / 1ps

module test (a,b,c,f1,f2) ;

// ------------ Port declarations --------- //
input a;
wire a;
input b;
wire b;
input c;
wire c;
output f1;
wire f1;
output f2;
wire f2;

// -------- Component instantiations -------//

func12 U2
(
	.a(a),
	.b(b),
	.c(c),
	.f1(f1),
	.f2(f2)
);



endmodule 
