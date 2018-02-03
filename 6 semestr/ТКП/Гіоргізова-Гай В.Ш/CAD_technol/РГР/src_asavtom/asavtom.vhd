library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity asavtom is	
	generic (Lin: integer :=1; 
	Lin2: integer :=0; 
	K: integer :=7; M: integer :=3;
	TZ: time :=2ns);
-- ������� ��� ����������� ������������������ ������������

	 port(
	 x: in bit_vector (Lin downto 0); 
-- � ������ ������� �(0)-�, � �(1)-D	 
	 z: out bit_vector(Lin2 downto 0)
	     );
end asavtom;

architecture asavtom of asavtom is
-- ������� �������������� bit_vector � integer
function vecint (vec1: bit_vector)
return integer is
variable retval:integer:=0;
begin
	for i in vec1'length-1 downto 1 loop
		if (vec1(i)='1') then retval:=(retval+1)*2;
		else  retval:= retval*2; end if;
	end loop;
	if vec1(0)='1' then retval:=retval+1;
	   else null; end if;
	return retval;
	end vecint;
	
type stab is array (0 to K, 0 to M) of integer;
type outtab is array (0 to K, 0 to M) of bit_vector(Lin2 downto 0);
 -- ��������� ������ �� 0 �� K (7 � �������), ����. ������ �� 0 �� M (3 � �������- D � C)
constant tab_st: stab :=((0,2,4,6),(1,3,5,7),
(0,2,16,6),(0,3,16,7),(0,2,4,6),(1,3,5,7),(16,2,5,6),(16,3,5,7));
constant tab_z : outtab :=(("0","0","0","0"), 
("1","1","1","1"),("0","0","0","0"),("0","1","0","1"),("0","0","0","0"),
("1","1","1","1"),("0","0","1","0"),("0","1","1","1"));	

signal st,nexst: integer:=0;

-- �������������� ������� ����� ��� ������� � ��������� 16,0.
-- �������� ��������� ��������� ����� ���������.
begin
 process 

 begin
wait on x, st;
if st=16 then null; 
	
else 
nexst<=tab_st(st,vecint(x));   --������������� ����� F1
z<=transport tab_z(st,vecint(x))after TZ;	  --������������� ����� F2
end if;
  end process;

st<= transport nexst after TZ;	 --������� ����������� ���������
end asavtom;  
