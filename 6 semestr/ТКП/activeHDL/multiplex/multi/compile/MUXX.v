//-----------------------------------------------------------------------------
//
// Title       : MUXX
// Design      : multi
// Author      : Unknown
// Company     : Unknown
//
//-----------------------------------------------------------------------------
//
// File        : d:\University\Katya\university\6 semestr\“ œ\activeHDL\multiplex\multi\compile\muxx.v
// Generated   : Wed Mar  1 10:44:27 2017
// From        : d:\University\Katya\university\6 semestr\“ œ\activeHDL\multiplex\multi\src\muxx.bde
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

module MUXX (A0,A1,D0,D1,D2,D3,notY) ;

// ------------ Port declarations --------- //
input A0;
wire A0;
input A1;
wire A1;
input D0;
wire D0;
input D1;
wire D1;
input D2;
wire D2;
input D3;
wire D3;
output notY;
wire notY;

// -------- Component instantiations -------//

MUX U1
(
	.A0(A0),
	.A1(A1),
	.D0(D0),
	.D1(D1),
	.D2(D2),
	.D3(D3),
	.notY(notY)
);



endmodule 
