--states/all states ordered (S8 also = 1000)/no CLK divider, trigger instead/elsif solved

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;


entity MATRIX_KEYPAD_B is
port(RST, CLK : in std_logic;
	  INPUT : in std_logic_vector (3 downto 0);
	  TRIGGER : in std_logic;
	  OUTPUT : out std_logic_vector (3 downto 0);
	  MOTOR_GHUMA : buffer std_logic;
	  BINARY_VECTOR_COUNT20 : out std_logic_vector (3 downto 0);
	  BINARY_VECTOR_COUNT10 : out std_logic_vector (3 downto 0)
	  );
end MATRIX_KEYPAD_B;

architecture BEHAVE of MATRIX_KEYPAD_B is

type STATE_TYPE is (S0,S1,S2,S3,S4,S5,S6,S7,S8);
signal Q,QPLUS,Q_CURR,Q_NEXT : STATE_TYPE;
signal DEN_INSERTED,DEN_CHOSEN,NUM,SUM,DEN_CHOSEN_FINAL,NUM_FINAL,COUNT20,COUNT10: integer range 0 to 500 :=0;
signal DEFICIT : integer range -510 to 510 :=0; 
signal COUNT : integer range 0 to 100000001 :=0;

begin
	
	process(CLK,RST)
	begin
		if RST = '1' then
			Q <= S0;
			MOTOR_GHUMA <= '0';
		   BINARY_VECTOR_COUNT10 <= "0000";
			BINARY_VECTOR_COUNT20 <= "0000";
			SUM <= 0;
			DEN_INSERTED <= 0;
			DEN_CHOSEN <= 0;
			NUM <= 0;
			DEFICIT <= 0;
			DEN_CHOSEN_FINAL <= 0;
			NUM_FINAL <= 0;
			COUNT <= 0;
			COUNT10 <= 0;
			COUNT20 <= 0;
		else
			if rising_edge(CLK) then
				Q <= QPLUS;
				if Q = S1 then
					DEN_INSERTED <= to_integer(unsigned(INPUT));
				end if;
				if (Q = S2 and (INPUT = "0010" or INPUT = "0011")) then
					DEN_INSERTED <= to_integer(unsigned(INPUT));
				end if;
				if (Q = S3 and (INPUT = "0010" or INPUT = "0001")) then
					DEN_CHOSEN <= to_integer(unsigned(INPUT));
				end if;
				if (Q = S4 and (INPUT = "0010" or INPUT = "0001")) then
					DEN_CHOSEN <= to_integer(unsigned(INPUT));
				end if;
				if (Q_CURR = S4 and Q_NEXT = S5) then
					if DEN_INSERTED = 2 then
						DEN_INSERTED <= 20;
					else	
						DEN_INSERTED <= 100;
					end if;
					if DEN_CHOSEN = 1 then
						DEN_CHOSEN_FINAL <= 10;
					end if;
					if DEN_CHOSEN = 2 then
						DEN_CHOSEN_FINAL <= 20;
					end if;
				end if;
				if (Q = S5 and (not(INPUT = "1010" or INPUT = "1011" or INPUT = "1100" or INPUT = "1101" or INPUT = "0000"))) then
					NUM <= to_integer(unsigned(INPUT));
				end if;
				if (Q = S6 and (INPUT = "1111" or INPUT = "0001" or INPUT = "0010" or INPUT = "0011" or INPUT = "0100" or INPUT = "0101" or INPUT = "0110" or INPUT = "0111" or INPUT = "1000" or INPUT = "1001")) then
					NUM <= to_integer(unsigned(INPUT));
				end if;
				if ((Q_CURR = S6 and Q_NEXT = S3) or (Q_CURR = S6 and Q_NEXT = S7)) then
					NUM_FINAL <= NUM;
					if(DEN_CHOSEN_FINAL = 10) then
						COUNT10 <= COUNT10 + NUM;	
					else
						COUNT20 <= COUNT20 + NUM;
					end if;
					SUM <= SUM + DEN_CHOSEN_FINAL*NUM;
				end if;
				if Q = S7 then
					if COUNT = 0 then
						DEFICIT <= DEN_INSERTED - SUM;
					end if;
					if COUNT = 4 then
						if SUM = DEN_INSERTED then
							MOTOR_GHUMA <= '1';
						end if;
						if SUM < DEN_INSERTED then
							if DEFICIT = 100 then
								COUNT20 <= COUNT20 + 5;
							end if;
							if DEFICIT = 90 then
								COUNT20 <= COUNT20 + 4;
								COUNT10 <= COUNT10 + 1;
							end if;
							if DEFICIT = 80 then
								COUNT20 <= COUNT20 + 4;
							end if;
							if DEFICIT = 70 then
								COUNT20 <= COUNT20 + 3;
								COUNT10 <= COUNT10 + 1;
							end if;
							if DEFICIT = 60 then
								COUNT20 <= COUNT20 + 3;
							end if;
							if DEFICIT = 50 then
								COUNT20 <= COUNT20 + 2;
								COUNT10 <= COUNT10 + 1;
							end if;
							if DEFICIT = 40 then
								COUNT20 <= COUNT20 + 2;
							end if;
							if DEFICIT = 30 then
								COUNT20 <= COUNT20 + 1;
								COUNT10 <= COUNT10 + 1;
							end if;
							if DEFICIT = 20 then
								COUNT20 <= COUNT20 + 1;
							end if;
							if DEFICIT = 10 then
								COUNT10 <= COUNT10 + 1;
							end if;
							MOTOR_GHUMA <= '1';
						else
							MOTOR_GHUMA <= '0';
						end if;
					end if;
					if COUNT = 8 then
						if(MOTOR_GHUMA = '1') then
							BINARY_VECTOR_COUNT10 <= std_logic_vector(to_unsigned(COUNT10, BINARY_VECTOR_COUNT10'length));
							BINARY_VECTOR_COUNT20 <= std_logic_vector(to_unsigned(COUNT20, BINARY_VECTOR_COUNT20'length));
						else
							BINARY_VECTOR_COUNT10 <= "0000";
							BINARY_VECTOR_COUNT20 <= "0000";
						end if;
					end if;
					if COUNT < 100000000 then
						COUNT <= COUNT + 1;
					else 
						COUNT <= 0;
					end if;
				end if;
				if Q = S0 then
					MOTOR_GHUMA <= '0';
					BINARY_VECTOR_COUNT10 <= "0000";
					BINARY_VECTOR_COUNT20 <= "0000";
					SUM <= 0;
					DEN_INSERTED <= 0;
					DEN_CHOSEN <= 0;
					NUM <= 0;
					DEFICIT <= 0;
					DEN_CHOSEN_FINAL <= 0;
					NUM_FINAL <= 0;
					COUNT <= 0;
					COUNT10 <= 0;
					COUNT20 <= 0;
				end if;	
			end if;
		end if;
	end process;

	process(TRIGGER,Q)
	begin
		Q_CURR <= Q;
		case Q is
			when S0 =>--RESET STATE/ENTER A
				OUTPUT <= "0000";
				if INPUT = "1010" then
					QPLUS <= S1;
					Q_NEXT <= S1;
				else
					QPLUS <= Q;
					Q_NEXT <= Q;
				end if;
			when S1 =>--INSERTED NOTE
				OUTPUT <= "0001";
				if (INPUT = "0010" or INPUT = "0011") then
					QPLUS <= S2;
					Q_NEXT <= S2;
				else
					QPLUS <= Q;
					Q_NEXT <= Q;
				end if;
			when S2 =>--ENTER B
				OUTPUT <= "0010";
				if INPUT = "1011" then
					QPLUS <= S3;
					Q_NEXT <= S3;
				else
					QPLUS <= Q;
					Q_NEXT <= Q;
				end if;
			when S3 =>--DENOMINATION NEEDED
				OUTPUT <= "0011";
				if (INPUT = "0001" or INPUT = "0010") then
					QPLUS <= S4;
					Q_NEXT <= S4;
				else	
					QPLUS <= Q;
					Q_NEXT <= Q;
				end if;
			when S4 =>--ENTER C
				OUTPUT <= "0100";
				if INPUT = "1100" then
					QPLUS <= S5;
					Q_NEXT <= S5;
				else
					QPLUS <= Q;
					Q_NEXT <= Q;
				end if;
			when S5 =>--NUMBER OF NOTES
				OUTPUT <= "0101";
				if (INPUT ="1010" or INPUT = "1011" or INPUT = "1100" or INPUT = "1101" or INPUT = "0000") then
					QPLUS <= Q;
					Q_NEXT <= Q;
				else
					QPLUS <= S6;
					Q_NEXT <= S6;
				end if;
			when S6 =>--NEXT DENOMINATION/FINAL ENTER
				OUTPUT <= "0110";
				if INPUT = "1101" then
					QPLUS <= S7;
					Q_NEXT <= S7;
				elsif INPUT = "1011" then
					QPLUS <= S3;
					Q_NEXT <= S3;
				else
					QPLUS <= Q;
					Q_NEXT <= Q;
				end if;
			when S7 =>--WE ARE IN THE GRAND MASTI NOW!
				OUTPUT <= "0111";
				if COUNT < 100000000 then
					QPLUS <= S8;
					Q_NEXT <= S8;
				else
					QPLUS <= S0;
					Q_NEXT <= S0;
				end if;
			when S8 =>
				OUTPUT <= "0111";
					QPLUS <= S7;
					Q_NEXT <= S7;
			when others =>
				OUTPUT <= "1000";
				QPLUS <= S0;
		end case;
	end process;
	
end BEHAVE;