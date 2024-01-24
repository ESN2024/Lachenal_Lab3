
module lab3_qs (
	clk_clk,
	opencores_i2c_0_export_0_scl_pad_io,
	opencores_i2c_0_export_0_sda_pad_io,
	pio_0_external_connection_export,
	pio_1_external_connection_export,
	pio_2_external_connection_export,
	pio_3_external_connection_export,
	pio_4_external_connection_export,
	pio_5_external_connection_export,
	pio_6_external_connection_export,
	reset_reset_n);	

	input		clk_clk;
	inout		opencores_i2c_0_export_0_scl_pad_io;
	inout		opencores_i2c_0_export_0_sda_pad_io;
	input		pio_0_external_connection_export;
	output	[3:0]	pio_1_external_connection_export;
	output	[3:0]	pio_2_external_connection_export;
	output	[3:0]	pio_3_external_connection_export;
	output	[3:0]	pio_4_external_connection_export;
	output	[3:0]	pio_5_external_connection_export;
	output	[3:0]	pio_6_external_connection_export;
	input		reset_reset_n;
endmodule
