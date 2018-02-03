library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity asavt_vozb is	
	generic (Lin: integer :=1); 
	 port(
	 x: in STD_LOGIC_vector (Lin downto 0);
	 z: out STD_LOGIC
	     );
end asavt_vozb;

architecture avt_vozb of asavt_vozb is
signal r1,s1,r0,s0:STD_LOGIC;                 -- вместо nexst
signal Q:STD_LOGIC_vector(1 downto 0):="00" ;	-- вместо st c установкой в начальное состояние
 	
-- после  кодирования в примере: 0-00, 1-11, 2-10, 3-01; z=Q1	 
 -- Задавать временные диаграммы нужно правильно.
begin
 process 
  begin	 --комбинацонная схема F1
wait on x,Q; 	   
r1<=(not Q(0)) and (not x(0)); --функции возбуждения
s1<=Q(0) and (not x(0)); 
r0<=(not x(1)) and x(0); 
s0<=x(1) and x(0); 
end process; 

  z<=Q(1);             -- z=Q1 	 комбинацонная схема F2

  process
begin  --регистр асинхронных RS- триггеров
wait on r0,s0,r1,s1;      
Q(0)<=s0 or (not(r0) and Q(0)); -- уравнение асинхронного RS-триггера
Q(1)<=s1 or (not(r1) and Q(1));	 
end process;   
end avt_vozb;  
