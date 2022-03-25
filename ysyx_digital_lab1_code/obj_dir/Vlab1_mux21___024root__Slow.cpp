// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab1_mux21.h for the primary calling header

#include "Vlab1_mux21___024root.h"
#include "Vlab1_mux21__Syms.h"

//==========


void Vlab1_mux21___024root___ctor_var_reset(Vlab1_mux21___024root* vlSelf);

Vlab1_mux21___024root::Vlab1_mux21___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vlab1_mux21___024root___ctor_var_reset(this);
}

void Vlab1_mux21___024root::__Vconfigure(Vlab1_mux21__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vlab1_mux21___024root::~Vlab1_mux21___024root() {
}

void Vlab1_mux21___024root___eval_initial(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___eval_initial\n"); );
}

void Vlab1_mux21___024root___combo__TOP__1(Vlab1_mux21___024root* vlSelf);

void Vlab1_mux21___024root___eval_settle(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___eval_settle\n"); );
    // Body
    Vlab1_mux21___024root___combo__TOP__1(vlSelf);
}

void Vlab1_mux21___024root___final(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___final\n"); );
}

void Vlab1_mux21___024root___ctor_var_reset(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->a = VL_RAND_RESET_I(1);
    vlSelf->b = VL_RAND_RESET_I(1);
    vlSelf->s = VL_RAND_RESET_I(1);
    vlSelf->y = VL_RAND_RESET_I(1);
}
