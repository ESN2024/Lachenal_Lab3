library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity ga_lab3 is
	port (
		clk           : in std_logic ;
		reset         : in std_logic ; -- reset_n
		data          : inout std_logic;
		address        : inout std_logic		
	);
end entity ga_lab3;
	 
	 
architecture behav of ga_lab3 is 
	 
	 component lab3_qs is
        port (
            clk_clk                             : in    std_logic := 'X'; -- clk
            reset_reset_n                       : in    std_logic := 'X'; -- reset_n
            opencores_i2c_0_export_0_scl_pad_io : inout std_logic := 'X'; -- scl_pad_io
            opencores_i2c_0_export_0_sda_pad_io : inout std_logic := 'X'  -- sda_pad_io
        );
    end component lab3_qs;
		begin
    u0 : component lab3_qs
        port map (
            clk_clk                             => clk,                             --                      clk.clk
            reset_reset_n                       => reset,                       --                    reset.reset_n
            opencores_i2c_0_export_0_scl_pad_io => data, -- opencores_i2c_0_export_0.scl_pad_io
            opencores_i2c_0_export_0_sda_pad_io => address  --                         .sda_pad_io
        );
		  
end architecture behav;
