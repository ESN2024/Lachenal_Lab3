	component lab3_qs is
		port (
			clk_clk                             : in    std_logic := 'X'; -- clk
			reset_reset_n                       : in    std_logic := 'X'; -- reset_n
			opencores_i2c_0_export_0_scl_pad_io : inout std_logic := 'X'; -- scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io : inout std_logic := 'X'  -- sda_pad_io
		);
	end component lab3_qs;

	u0 : component lab3_qs
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                      clk.clk
			reset_reset_n                       => CONNECTED_TO_reset_reset_n,                       --                    reset.reset_n
			opencores_i2c_0_export_0_scl_pad_io => CONNECTED_TO_opencores_i2c_0_export_0_scl_pad_io, -- opencores_i2c_0_export_0.scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io => CONNECTED_TO_opencores_i2c_0_export_0_sda_pad_io  --                         .sda_pad_io
		);

