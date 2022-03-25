// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab1_mux21.h for the primary calling header

#include "Vlab1_mux21___024root.h"
#include "Vlab1_mux21__Syms.h"

//==========

VL_INLINE_OPT void Vlab1_mux21___024root___combo__TOP__1(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___combo__TOP__1\n"); );
    // Body
    vlSelf->y = (((~ (IData)(vlSelf->s)) & (IData)(vlSelf->a)) 
                 | ((IData)(vlSelf->s) & (IData)(vlSelf->b)));
}

void Vlab1_mux21___024root___eval(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___eval\n"); );
    // Body
    Vlab1_mux21___024root___combo__TOP__1(vlSelf);
}

QData Vlab1_mux21___024root___change_request_1(Vlab1_mux21___024root* vlSelf);

VL_INLINE_OPT QData Vlab1_mux21___024root___change_request(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___change_request\n"); );
    // Body
    return (Vlab1_mux21___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vlab1_mux21___024root___change_request_1(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vlab1_mux21___024root___eval_debug_assertions(Vlab1_mux21___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab1_mux21__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab1_mux21___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->a & 0xfeU))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->b & 0xfeU))) {
        Verilated::overWidthError("b");}
    if (VL_UNLIKELY((vlSelf->s & 0xfeU))) {
        Verilated::overWidthError("s");}
}
#endif  // VL_DEBUG
