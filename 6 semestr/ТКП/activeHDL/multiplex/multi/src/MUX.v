//-----------------------------------------------------------------------------
//
// Title       : MUX
// Design      : multi
// Author      : Machine
// Company     : gypnor
//
//-----------------------------------------------------------------------------
//
// File        : MUX.v
// Generated   : Sat Feb 25 23:47:43 2017
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
//{module {MUX}}
module MUX ( D0 ,D1 ,D2 ,D3 ,A0 ,A1 ,notY );

output notY ;
wire notY ;

input D0 ;
wire D0 ;
input D1 ;
wire D1 ;
input D2 ;
wire D2 ;
input D3 ;
wire D3 ;
input A0 ;
wire A0 ;
input A1 ;
wire A1 ;

//}} End of automatically maintained section

// -- Enter your statements here -- //
assign #1 notY=!((D0&!A1&!A0)|(D1&A1&!A0)|(D2&!A1&A0)|(D3&A1&A0));
endmodule
