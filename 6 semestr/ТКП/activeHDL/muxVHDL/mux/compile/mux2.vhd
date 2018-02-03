-------------------------------------------------------------------------------
--
-- Title       : No Title
-- Design      : mux
-- Author      : Machine
-- Company     : gypnor
--
-------------------------------------------------------------------------------
--
-- File        : d:\University\Katya\university\6 semestr\ÒÊÏ\activeHDL\muxVHDL\mux\compile\mux2.vhd
-- Generated   : Wed Mar  1 11:03:33 2017
-- From        : d:\University\Katya\university\6 semestr\ÒÊÏ\activeHDL\muxVHDL\mux\src\mux2.bde
-- By          : Bde2Vhdl ver. 2.6
--
-------------------------------------------------------------------------------
--
-- Description : 
--
-------------------------------------------------------------------------------
-- Design unit header --
library IEEE;
use IEEE.std_logic_1164.all;


entity mux2 is
  port(
       C : in STD_LOGIC;
       D : in STD_LOGIC;
       E : in STD_LOGIC;
       F : in STD_LOGIC;
       S : in STD_LOGIC_VECTOR(1 downto 0);
       MUX_OUT : out STD_LOGIC
  );
end mux2;

architecture mux2 of mux2 is

---- Component declarations -----

component mux
  port (
       c : in STD_LOGIC;
       d : in STD_LOGIC;
       e : in STD_LOGIC;
       f : in STD_LOGIC;
       s : in STD_LOGIC_VECTOR(1 downto 0);
       mux_out : out STD_LOGIC
  );
end component;

begin

----  Component instantiations  ----

U1 : mux
  port map(
       c => C,
       d => D,
       e => E,
       f => F,
       mux_out => MUX_OUT,
       s => S
  );


end mux2;
