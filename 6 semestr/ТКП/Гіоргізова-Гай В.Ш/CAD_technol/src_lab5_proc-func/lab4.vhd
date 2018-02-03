library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity lab4 is	
	generic (Lin: integer :=2; 
             Lout: integer :=2); 
	 port(
	 x: in STD_LOGIC_vector (Lin downto 0);
	 x1: in STD_LOGIC; 
	 C,R,S,J,K: in STD_LOGIC; 
	 Q,nQ: out STD_LOGIC; 
	 y: out STD_LOGIC_vector (Lout downto 0);
	 y1: out STD_LOGIC
	     );
end lab4;

architecture lab4 of lab4 is   

------------------процедуры и функции--------------------------
-- функция +1 (по алгоритму синхронного счетч. с последовательн. переносом)
function vecincr (vec: STD_LOGIC_vector)
return STD_LOGIC_vector is
variable k:STD_LOGIC:='1';
variable vec1:STD_LOGIC_vector (vec'length-1 downto 0);

variable retval:integer:=0;
begin  
	if vec'length-1 > 0 then  
	for i in 1 to vec'length-1 loop
		k:=k and vec(i-1);
		vec1(i):=(k and (not vec(i))) or((not k) and vec(i));
	end loop;
	else null;
		end if;
	 vec1(0):=not vec(0);
	return vec1;
	end vecincr; 
	
-- функция -1 (по алгоритму синхронного счетч. с последовательн. переносом)
	function vecdecr (vec: STD_LOGIC_vector)
return STD_LOGIC_vector is
variable k:STD_LOGIC:='1';
variable vec1:STD_LOGIC_vector (vec'length-1 downto 0);

variable retval:integer:=0;
begin  
	if vec'length-1 > 0 then  
	for i in 1 to vec'length-1 loop
		k:=k and (not(vec(i-1)));
		vec1(i):=(k and (not vec(i))) or((not k) and vec(i));
	end loop;
	else null;
		end if;
	 vec1(0):=not vec(0);
	return vec1;
 	end vecdecr;
	 
	-- функция суммирования (по алгоритму параллельного сумматора c послед. переносом) 
	 procedure addvec (ad1,ad2: in STD_LOGIC_vector; 
	 cin: in STD_LOGIC;
	 signal sum: out STD_LOGIC_vector;
	 signal	p:out STD_LOGIC) is	 
	 variable c:STD_LOGIC;
	 begin
		 c:=cin;
	if (ad1'length-1 > 0) and (ad2'length-1 > 0) and (ad1'length = ad2'length) then  
	for i in 0 to ad1'length-1 loop
		sum(i)<=c xor ad1(i) xor ad2(i);
		c:=(ad1(i) and ad2(i)) or (ad1(i)and c) or(ad2(i)and c);
	end loop;
	else null;	
	end if;	
	p<=c;
	end addvec;	
	
-- функция определения положительного фронта в многозначной логике
	function posedge (signal s: STD_LOGIC)
return STD_LOGIC is
begin  
	if s'event=FALSE then return '0'; 
	else if s'last_value ='0' and s ='1' then return '1';    
	    else if s='0' then return '0'; 
        	else return 'X'; 
        	end if;
	    end if;
	end if;
 	end posedge;
-------------------------------------------

	signal A,B:  STD_LOGIC_vector (Lin downto 0);
	signal Sum: STD_LOGIC_vector (Lout downto 0);
	signal Cou: STD_LOGIC;
signal sig_q,sig_nq: STD_LOGIC; --нужно вводить,если не работает корректно inout Q	и nQ

begin  
--y<=vecdecr(x);	
--addvec(A,B,'0',Sum,Cou); 
--y1<=posedge(x1);
process	
variable vq: STD_LOGIC; 
begin 
	wait on R,S,C;
if (R='1'and S='0') then vq:='0';
  elsif (R='0'and S='1') then vq:='1'; 
  elsif (R='0'and S='0') then  
    	if posedge(C)= '1' then	 vq:=(sig_nq and J)or(sig_q and not( K));	
		elsif posedge(C)= '0' then null;
	    else vq:='X';
	    end if;
 else vq:='X';		
end if;	
sig_q<=vq; --нужно вводить,если не работает корректно inout Q и nQ
sig_nq<=not(vq); --нужно вводить,если не работает корректно inout Q и nQ
end process; 

Q<=sig_q;  --если работает корректно inout Q и nQ, тогда Q<=vq; и  nQ<= not(vq) в конце процесса
nQ<= not(sig_q);  
end lab4;  
