library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity avt_code is	
	generic (Lin: integer :=1; 
	K: integer :=3; M: integer :=3;	
	Lst: integer :=2;
	TZ: time :=2ns);
	-- ������� ��� ����������� ������������������ ������������
	 port(
	 x: in bit_vector (Lin downto 0);
	 z: out bit
	     );
end avt_code;

architecture avt_code of avt_code is

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
	
type stab is array (0 to K, 0 to M) of bit_vector(Lst downto 0);
--������� ������� ��� �� ������ ����� ������ ����������� - �����!
type outtab is array (0 to K, 0 to M) of bit;
-- ����� ����������� ��������� � ������� ����������: 0-00, 1-11, 2-10, 3-01; z=Q1
-- ������ ������� ��������� �������� � ������� 00,01,10,11 !!!!	

constant Ust: bit_vector(Lst downto 0):=(others =>'1');--����������� �������  
-- ����������!	

constant tab_st: stab :=(("000","000","000","001"),("111","000","011","001"),
("000","010","111","011"),("011","010","011","011"));
constant tab_z : outtab :=(('0','0','0','0'), 
('1','0','1','0'),('0','1','1','1'),('1','1','1','1'));	

signal st,nexst: bit_vector(Lst downto 0):=(others =>'0');
-- ����������!

-- �������������� ������� ����� ��� ������� � ��������� 111,1.
-- �������� ��������� ��������� ����� ���������.
begin
 process 

 begin
wait on x, st;
if st=Ust then null; 
else 
nexst<=tab_st(vecint(st),vecint(x));   --���������� ����� F1
z<=transport tab_z(vecint(st),vecint(x))after TZ;	  --���������� ����� F2 (����� � ������� <= st(1) 
-- ����������!
end if;
  end process;

st<= transport nexst after TZ;	 --������� ����������� ���������
end avt_code;  
