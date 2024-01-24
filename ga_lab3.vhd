library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity ga_lab3 is
	port (
		clk           : in std_logic ;
		reset         : in std_logic ; -- reset_n
		sda           : inout std_logic;
		clk_adx       : inout std_logic;
		button 		  : in std_logic;
		seg1 		     : out std_logic_vector(6 downto 0);        --afficheur 7 segments
		seg2          : out std_logic_vector(6 downto 0);        
		seg3          : out std_logic_vector(6 downto 0);       
		seg4          : out std_logic_vector(6 downto 0);        
		seg5          : out std_logic_vector(6 downto 0);
		cs            : out std_logic;
		seg6          : out std_logic_vector(6 downto 0)   
	);
end entity ga_lab3;
	 
	 
architecture behav of ga_lab3 is 
	 
	 component lab3_qs is
        port (
            clk_clk                             : in    std_logic                    := 'X'; -- clk
            opencores_i2c_0_export_0_scl_pad_io : inout std_logic                    := 'X'; -- scl_pad_io
            opencores_i2c_0_export_0_sda_pad_io : inout std_logic                    := 'X'; -- sda_pad_io
            pio_0_external_connection_export    : in    std_logic                    := 'X'; -- export
            pio_1_external_connection_export    : out   std_logic_vector(3 downto 0);        -- export
            pio_2_external_connection_export    : out   std_logic_vector(3 downto 0);        -- export
            pio_3_external_connection_export    : out   std_logic_vector(3 downto 0);        -- export
            pio_4_external_connection_export    : out   std_logic_vector(3 downto 0);        -- export
            pio_5_external_connection_export    : out   std_logic_vector(3 downto 0);        -- export
            reset_reset_n                       : in    std_logic                    := 'X'; -- reset_n
            pio_6_external_connection_export    : out   std_logic_vector(3 downto 0)         -- export
        );
    end component lab3_qs;
	 
	 component segdecod is
		PORT (
				Entree:IN STD_LOGIC_VECTOR(3 DOWNTO 0);
				Sortie:OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
		);
	 end component segdecod;
	 
	signal seg1wire : std_logic_vector(3 downto 0);
	signal seg2wire : std_logic_vector(3 downto 0);
	signal seg3wire : std_logic_vector(3 downto 0);
	signal seg4wire : std_logic_vector(3 downto 0);
	signal seg5wire : std_logic_vector(3 downto 0);
	signal seg6wire : std_logic_vector(3 downto 0);
	
		begin
		
		cs <= '1';
		
	u0 : component lab3_qs
        port map (
            clk_clk                             => clk,                             --                       clk.clk
            opencores_i2c_0_export_0_scl_pad_io => clk_adx, --  opencores_i2c_0_export_0.scl_pad_io
            opencores_i2c_0_export_0_sda_pad_io => sda, --                          .sda_pad_io
            pio_0_external_connection_export    => button,    -- pio_0_external_connection.export
            pio_1_external_connection_export    => seg1wire,    -- pio_1_external_connection.export
            pio_2_external_connection_export    => seg2wire,    -- pio_2_external_connection.export
            pio_3_external_connection_export    => seg3wire,    -- pio_3_external_connection.export
            pio_4_external_connection_export    => seg4wire,    -- pio_4_external_connection.export
            pio_5_external_connection_export    => seg5wire,    -- pio_5_external_connection.export
            reset_reset_n                       => reset,                       --                     reset.reset_n
            pio_6_external_connection_export    => seg6wire     -- pio_6_external_connection.export
        );


	u1 : component segdecod
		  port map (
				Entree									=> seg1wire,
				Sortie									=> seg1
		  );
		  
	u2 : component segdecod
		  port map (
				Entree									=> seg2wire,
				Sortie									=> seg2
		  );
		
	u3 : component segdecod
		  port map (
				Entree									=> seg3wire,
				Sortie									=> seg3
		  );
		  
	u4 : component segdecod
		  port map (
				Entree									=> seg4wire,
				Sortie									=> seg4
		  );
		  
	u5 : component segdecod
		  port map (
				Entree									=> seg5wire,
				Sortie									=> seg5
		  );
		
	u6 : component segdecod
		  port map (
				Entree									=> seg6wire,
				Sortie									=> seg6
		  );

		  
end architecture behav;

    
    

    