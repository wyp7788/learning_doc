module timertick_gen(
    clk_200,
    resetb,
    us_tick,
    ms_tick,
    sec_tick
);
//**************************
input clk_200;
input resetb;
output us_tick;
output ms_tick;
output sec_tick;

parameter US_COUNTER_MAX = 8'd199;

reg  [7:0]   us_counter;
wire [7:0]   us_counter_nxt;
reg          us_tick;
wire         us_tick_nxt;

reg  [9:0]   ms_counter;
reg  [9:0]   ms_counter_nxt;
reg          ms_tick;
wire         ms_tick_nxt;

reg  [9:0]   sec_counter;
wire [9:0]   sec_counter_nxt;
reg          sec_tick;
wire         sec_tick_nxt;
//******************************************
assign us_counter_nxt = (us_counter == US_COUNTER_MAX) ? 'd0 : (us_counter + 1'b1);
assign us_tick_nxt = (us_counter == US_COUNTER_MAX);
//*******************************************
// ms counter
always @(*) begin
    ms_counter_nxt = ms_counter;
    if(us_tick)begin
        if(ms_counter == 'd999)
            ms_counter_nxt = 0;
        else ms_counter_nxt = ms_counter + 1;
    end    
end

assign ms_tick_nxt = (ms_counter == 'd999);

assign sec_counter_nxt = ms_tick  ? ((sec_counter == 'd999) ? 'd0 : (sec_counter + 1'b1)) : sec_counter;

assign sec_tick_nxt = (sec_counter == 'd999);

always @(posedge clk_200 or negedge resetb) begin
    if(!resetb)begin
        us_counter  <= 'd0;
        ms_counter  <= 'd0;
        sec_counter <= 'd0;
        us_tick     <= 1'b0;
        ms_tick     <= 1'b0;
        sec_tick    <= 1'b0;
    end
    else begin
        us_counter <= us_counter_nxt;
        ms_counter <= ms_counter_nxt;
        sec_counter <= sec_counter_nxt;
        us_tick     <= us_tick_nxt;
        ms_tick     <= ms_tick_nxt;
        sec_tick    <= sec_tick_nxt; 
    end
end
endmodule