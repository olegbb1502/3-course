-------------------------------------------------------------------------------
--
-- Title       : mux1
-- Design      : mux
-- Author      : Machine
-- Company     : gypnor
--
-------------------------------------------------------------------------------
--
-- File        : mux1.vhd
-- Generated   : Wed Mar  1 10:46:29 2017
-- From        : interface description file
-- By          : Itf2Vhdl ver. 1.20
--
-------------------------------------------------------------------------------
--
-- Description : 
--
-------------------------------------------------------------------------------

--{{ Section below this comment is automatically maintained
--   and may be overwritten
--{entity {mux1} architecture {mux1}}

library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity mux is
	port (c, d, e, f: 	in std_logic;
	      s: 		in std_logic_vector(1 downto 0);
	      mux_out: 		out std_logic);
end mux;

architecture mux_impl of mux is
begin
	muxl: process (s, c, d, e, f)
	begin
	    case s is
	      	when "00" => mux_out <= not c;
	      	when "01" => mux_out <= not d;
      		when "10" => mux_out <= not e;
	      	when others => mux_out <= not f;
	    end case;
	end process muxl;
end mux_impl;