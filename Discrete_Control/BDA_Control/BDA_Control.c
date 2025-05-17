/*
 * File: BDA_Control.c
 *
 * Code generated for Simulink model 'BDA_Control'.
 *
 * Model version                  : 1.33
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Tue Apr 22 12:47:17 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "BDA_Control.h"
#include "rtwtypes.h"
#include <math.h>

/* Exported block signals */
uint8_T Mode_Ch;                       /* '<Root>/Mode_Ch'
                                        * 模式选择，给1为离网模式，给2为并网模式，给3为停止输出
                                        */
real32_T O_Phase_add;                  /* '<Root>/O_Phase_add'
                                        * 并网电流相移值
                                        */
real32_T O_IL_ref;                     /* '<Root>/O_ILref'
                                        * 并网电流目标值，需要乘根号2
                                        */
real32_T IL_fb;                        /* '<Root>/IL_fb'
                                        * 电感电流反馈值，实际采到的电流
                                        */
real32_T Uo_fb;                        /* '<Root>/Uo_fb'
                                        * 逆变输出or电网电压值
                                        */
real32_T Udc_set;                      /* '<Root>/Udc_set'
                                        * 直流侧电压值
                                        */
real32_T F_U_ref;                      /* '<Root>/F_U_ref'
                                        * 离网模式输出电压目标值
                                        */
real32_T F_Freq_set;                   /* '<Root>/F_Freq_set'
                                        * 离网逆变输出电压频率
                                        */
real32_T Duty_L;                       /* '<S4>/Gain3'
                                        * 左桥臂PWM输出占空比
                                        */
real32_T Duty_R;                       /* '<S4>/Add5'
                                        * 右桥臂输出PWM占空比
                                        */
real32_T O_Iq;                         /* '<S239>/Gain2'
                                        * 并网模式电流Q轴分量，加负号
                                        */
real32_T O_Uq;                         /* '<S239>/Gain4'
                                        * 并网模式电压Q轴分量，加负号
                                        */
real32_T F_Id;                         /* '<S3>/Gain1'
                                        * 离网模式输出电流值
                                        */
real32_T F_Ud;                         /* '<S3>/Gain4'
                                        * 离网模式输出电压值
                                        */

/* Exported block parameters */
real32_T QPR_Kp = 10.0F;               /* Variable: QPR_Kp
                                        * Referenced by: '<S240>/Gain2'
                                        * QPR电流内环参数Kp
                                        */
real32_T QPR_Kr = 200.0F;              /* Variable: QPR_Kr
                                        * Referenced by: '<S240>/Gain3'
                                        * QPR电流内环参数Kr
                                        */
real32_T QPR_w0 = 314.159271F;         /* Variable: QPR_w0
                                        * Referenced by: '<S240>/Gain4'
                                        * QPR电流内环中心频率w0=2*pi*f
                                        */
real32_T QPR_wc = 3.14159274F;         /* Variable: QPR_wc = 3.14159274F; 
                                        * Referenced by:
                                        *   '<S240>/Gain3'
                                        *   '<S240>/Gain5'
                                        * QPR电流内环带宽频率w0=2*pi*delta_f
                                        */

/* Block signals and states (default storage) */
DW rtDW;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void IfActionSubsystem(real32_T rtu_In1, real32_T *rty_Out1);
static void IfActionSubsystem1(real32_T rtu_In1, real32_T *rty_Out1);
static void TwoinputsCRL(real32_T rtu_Alpha, real32_T rtu_Beta, real32_T
  rtu_sine, real32_T rtu_cos, real32_T *rty_Ds, real32_T *rty_Qs);

/*
 * Output and update for action system:
 *    '<S17>/If Action Subsystem'
 *    '<S26>/If Action Subsystem'
 *    '<S39>/If Action Subsystem'
 *    '<S301>/If Action Subsystem'
 *    '<S307>/If Action Subsystem'
 *    '<S319>/If Action Subsystem'
 *    '<S328>/If Action Subsystem'
 */
static void IfActionSubsystem(real32_T rtu_In1, real32_T *rty_Out1)
{
  /* Sum: '<S19>/Sum' incorporates:
   *  DataTypeConversion: '<S19>/Convert_back'
   *  DataTypeConversion: '<S19>/Convert_uint16'
   */
  *rty_Out1 = rtu_In1 - (real32_T)(int16_T)floorf(rtu_In1);
}

/*
 * Output and update for action system:
 *    '<S17>/If Action Subsystem1'
 *    '<S26>/If Action Subsystem1'
 *    '<S39>/If Action Subsystem1'
 *    '<S301>/If Action Subsystem1'
 *    '<S307>/If Action Subsystem1'
 *    '<S319>/If Action Subsystem1'
 *    '<S328>/If Action Subsystem1'
 */
static void IfActionSubsystem1(real32_T rtu_In1, real32_T *rty_Out1)
{
  /* Sum: '<S20>/Sum' incorporates:
   *  DataTypeConversion: '<S20>/Convert_back'
   *  DataTypeConversion: '<S20>/Convert_uint16'
   */
  *rty_Out1 = rtu_In1 - (real32_T)(int16_T)rtu_In1;
}

/*
 * Output and update for atomic system:
 *    '<S9>/Two inputs CRL'
 *    '<S10>/Two inputs CRL'
 *    '<S245>/Two inputs CRL'
 *    '<S311>/Two inputs CRL'
 *    '<S312>/Two inputs CRL'
 */
static void TwoinputsCRL(real32_T rtu_Alpha, real32_T rtu_Beta, real32_T
  rtu_sine, real32_T rtu_cos, real32_T *rty_Ds, real32_T *rty_Qs)
{
  /* AlgorithmDescriptorDelegate generated from: '<S14>/a16' incorporates:
   *  Product: '<S14>/acos'
   *  Product: '<S14>/asin'
   *  Product: '<S14>/bcos'
   *  Product: '<S14>/bsin'
   *  Sum: '<S14>/sum_Ds'
   *  Sum: '<S14>/sum_Qs'
   */
  *rty_Ds = rtu_Alpha * rtu_cos + rtu_Beta * rtu_sine;
  *rty_Qs = rtu_Beta * rtu_cos - rtu_Alpha * rtu_sine;
}

/* Model step function */
void BDA_Control_step(void)
{
  real_T rtb_Add1;
  real32_T DiscreteTransferFcn1_tmp_n;
  real32_T DiscreteTransferFcn_tmp_f;
  real32_T algDD_o1_tmp;
  real32_T rtb_DiscreteTimeIntegrator1;
  real32_T rtb_DiscreteTransferFcn1_e;
  real32_T rtb_DiscreteTransferFcn_b;
  real32_T rtb_DiscreteTransferFcn_iy;
  real32_T rtb_Sum2_p;
  real32_T rtb_algDD_o1_h;
  real32_T rtb_algDD_o1_j;
  real32_T rtb_algDD_o2_g;
  real32_T rtb_algDD_o2_m;
  real32_T rtb_convert_pu_mc;
  real32_T rtb_indexing_p;
  real32_T rtb_sum_beta;
  uint16_T rtb_Get_Integer_c0;
  int8_T tmp;
  int8_T tmp_0;
  uint8_T rtb_State_A;
  uint8_T rtb_State_B;

  /* Outputs for Atomic SubSystem: '<Root>/BDA_Control' */
  /* Chart: '<S1>/Chart' incorporates:
   *  Inport: '<Root>/Mode_Ch'
   */
  rtb_State_A = 0U;
  rtb_State_B = 0U;
  switch (Mode_Ch) {
   case 1:
    rtb_State_A = 1U;
    break;

   case 2:
    rtb_State_B = 1U;
    break;
  }

  /* End of Chart: '<S1>/Chart' */

  /* Outputs for Enabled SubSystem: '<S1>/DQ_FGD' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (rtb_State_A > 0) {
    /* Outputs for Enabled SubSystem: '<S8>/Accumulate' incorporates:
     *  EnablePort: '<S236>/Enable'
     */
    /* Outputs for Enabled SubSystem: '<S236>/Subsystem' incorporates:
     *  EnablePort: '<S237>/Enable'
     */
    /* Delay: '<S236>/Delay' */
    if (rtDW.Delay_DSTATE) {
      /* SignalConversion generated from: '<S237>/Input' incorporates:
       *  Gain: '<S3>/Gain3'
       *  Gain: '<S8>/scaleIn'
       *  Inport: '<Root>/F_Freq_set'
       */
      rtDW.Input = 0.000628318521F * F_Freq_set * 0.159154937F;
    }

    /* End of Delay: '<S236>/Delay' */
    /* End of Outputs for SubSystem: '<S236>/Subsystem' */

    /* Sum: '<S236>/Add' incorporates:
     *  UnitDelay: '<S8>/Unit Delay'
     */
    rtb_sum_beta = rtDW.Input + rtDW.Add1;

    /* Sum: '<S236>/Add1' incorporates:
     *  DataTypeConversion: '<S236>/Data Type Conversion'
     *  DataTypeConversion: '<S236>/Data Type Conversion1'
     */
    rtDW.Add1 = rtb_sum_beta - (real32_T)(int16_T)floorf(rtb_sum_beta);

    /* Update for Delay: '<S236>/Delay' incorporates:
     *  Constant: '<S236>/Constant'
     */
    rtDW.Delay_DSTATE = true;

    /* End of Outputs for SubSystem: '<S8>/Accumulate' */

    /* Gain: '<S8>/scaleOut' */
    rtb_DiscreteTimeIntegrator1 = 6.28318548F * rtDW.Add1;

    /* Gain: '<S39>/convert_pu' incorporates:
     *  Gain: '<S17>/convert_pu'
     *  Gain: '<S26>/convert_pu'
     */
    rtb_convert_pu_mc = 0.159154937F * rtb_DiscreteTimeIntegrator1;

    /* If: '<S39>/If' incorporates:
     *  Constant: '<S40>/Constant'
     *  Gain: '<S39>/convert_pu'
     *  RelationalOperator: '<S40>/Compare'
     */
    if (rtb_convert_pu_mc < 0.0F) {
      /* Outputs for IfAction SubSystem: '<S39>/If Action Subsystem' incorporates:
       *  ActionPort: '<S41>/Action Port'
       */
      IfActionSubsystem(rtb_convert_pu_mc, &rtb_indexing_p);

      /* End of Outputs for SubSystem: '<S39>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S39>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S42>/Action Port'
       */
      IfActionSubsystem1(rtb_convert_pu_mc, &rtb_indexing_p);

      /* End of Outputs for SubSystem: '<S39>/If Action Subsystem1' */
    }

    /* End of If: '<S39>/If' */

    /* Gain: '<S36>/indexing' */
    rtb_indexing_p *= 800.0F;

    /* If: '<S26>/If' incorporates:
     *  Constant: '<S27>/Constant'
     *  RelationalOperator: '<S27>/Compare'
     */
    if (rtb_convert_pu_mc < 0.0F) {
      /* Outputs for IfAction SubSystem: '<S26>/If Action Subsystem' incorporates:
       *  ActionPort: '<S28>/Action Port'
       */
      IfActionSubsystem(rtb_convert_pu_mc, &rtb_Sum2_p);

      /* End of Outputs for SubSystem: '<S26>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S26>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S29>/Action Port'
       */
      IfActionSubsystem1(rtb_convert_pu_mc, &rtb_Sum2_p);

      /* End of Outputs for SubSystem: '<S26>/If Action Subsystem1' */
    }

    /* End of If: '<S26>/If' */

    /* Gain: '<S24>/indexing' */
    rtb_Sum2_p *= 800.0F;

    /* If: '<S17>/If' incorporates:
     *  Constant: '<S18>/Constant'
     *  RelationalOperator: '<S18>/Compare'
     */
    if (rtb_convert_pu_mc < 0.0F) {
      /* Outputs for IfAction SubSystem: '<S17>/If Action Subsystem' incorporates:
       *  ActionPort: '<S19>/Action Port'
       */
      IfActionSubsystem(rtb_convert_pu_mc, &rtb_DiscreteTimeIntegrator1);

      /* End of Outputs for SubSystem: '<S17>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S17>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S20>/Action Port'
       */
      IfActionSubsystem1(rtb_convert_pu_mc, &rtb_DiscreteTimeIntegrator1);

      /* End of Outputs for SubSystem: '<S17>/If Action Subsystem1' */
    }

    /* End of If: '<S17>/If' */

    /* Gain: '<S15>/indexing' */
    rtb_DiscreteTimeIntegrator1 *= 800.0F;

    /* Sum: '<S15>/Sum2' incorporates:
     *  DataTypeConversion: '<S15>/Data Type Conversion1'
     *  DataTypeConversion: '<S15>/Get_Integer'
     */
    rtb_convert_pu_mc = rtb_DiscreteTimeIntegrator1 - (real32_T)(uint16_T)
      rtb_DiscreteTimeIntegrator1;

    /* DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn' incorporates:
     *  Inport: '<Root>/Uo_fb'
     */
    rtb_sum_beta = (Uo_fb - -1.98343372F * rtDW.DiscreteTransferFcn_states_a[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn_states_a[1];
    DiscreteTransferFcn_tmp_f = rtb_sum_beta;
    rtb_DiscreteTransferFcn_b = 0.00779332919F * rtb_sum_beta + 0.0F *
      rtDW.DiscreteTransferFcn_states_a[0];

    /* DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn1' incorporates:
     *  Inport: '<Root>/Uo_fb'
     */
    rtb_sum_beta = (Uo_fb - -1.98343372F * rtDW.DiscreteTransferFcn1_states_h[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn1_states_h[1];
    DiscreteTransferFcn1_tmp_n = rtb_sum_beta;

    /* Outputs for Atomic SubSystem: '<S9>/Two inputs CRL' */
    /* DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn' incorporates:
     *  Constant: '<S15>/offset'
     *  Constant: '<S15>/sine_table_values'
     *  DataTypeConversion: '<S15>/Get_Integer'
     *  DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn1'
     *  Product: '<S16>/Product'
     *  Product: '<S16>/Product1'
     *  Selector: '<S15>/Lookup'
     *  Sum: '<S15>/Sum'
     *  Sum: '<S16>/Sum3'
     *  Sum: '<S16>/Sum4'
     *  Sum: '<S16>/Sum5'
     *  Sum: '<S16>/Sum6'
     */
    TwoinputsCRL(rtb_DiscreteTransferFcn_b + -0.00779332919F *
                 rtDW.DiscreteTransferFcn_states_a[1], (0.000122456287F *
      rtb_sum_beta + 0.000244912575F * rtDW.DiscreteTransferFcn1_states_h[0]) +
                 0.000122456287F * rtDW.DiscreteTransferFcn1_states_h[1],
                 (rtConstP.pooled2[(int32_T)((uint16_T)
      rtb_DiscreteTimeIntegrator1 + 1U)] - rtConstP.pooled2[(uint16_T)
                  rtb_DiscreteTimeIntegrator1]) * rtb_convert_pu_mc +
                 rtConstP.pooled2[(uint16_T)rtb_DiscreteTimeIntegrator1],
                 (rtConstP.pooled2[(int32_T)((uint16_T)
      rtb_DiscreteTimeIntegrator1 + 201U)] - rtConstP.pooled2[(int32_T)
                  ((uint16_T)rtb_DiscreteTimeIntegrator1 + 200U)]) *
                 rtb_convert_pu_mc + rtConstP.pooled2[(int32_T)((uint16_T)
      rtb_DiscreteTimeIntegrator1 + 200U)], &rtb_algDD_o1_h, &rtb_algDD_o2_g);

    /* End of Outputs for SubSystem: '<S9>/Two inputs CRL' */

    /* Sum: '<S7>/Sum' incorporates:
     *  Gain: '<S7>/Gain7'
     *  Inport: '<Root>/F_U_ref'
     */
    rtb_DiscreteTimeIntegrator1 = 1.41421354F * F_U_ref - rtb_algDD_o1_h;

    /* Sum: '<S24>/Sum2' incorporates:
     *  DataTypeConversion: '<S24>/Data Type Conversion1'
     *  DataTypeConversion: '<S24>/Get_Integer'
     */
    rtb_convert_pu_mc = rtb_Sum2_p - (real32_T)(uint16_T)rtb_Sum2_p;

    /* DiscreteTransferFcn: '<S12>/Discrete Transfer Fcn' incorporates:
     *  Inport: '<Root>/IL_fb'
     */
    rtb_sum_beta = (IL_fb - -1.98343372F * rtDW.DiscreteTransferFcn_states_p[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn_states_p[1];
    rtb_DiscreteTransferFcn_b = rtb_sum_beta;
    rtb_DiscreteTransferFcn_iy = 0.00779332919F * rtb_sum_beta + 0.0F *
      rtDW.DiscreteTransferFcn_states_p[0];

    /* DiscreteTransferFcn: '<S12>/Discrete Transfer Fcn1' incorporates:
     *  Inport: '<Root>/IL_fb'
     */
    rtb_sum_beta = (IL_fb - -1.98343372F * rtDW.DiscreteTransferFcn1_states_o[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn1_states_o[1];
    rtb_DiscreteTransferFcn1_e = rtb_sum_beta;

    /* Outputs for Atomic SubSystem: '<S10>/Two inputs CRL' */
    /* DiscreteTransferFcn: '<S12>/Discrete Transfer Fcn' incorporates:
     *  Constant: '<S24>/offset'
     *  Constant: '<S24>/sine_table_values'
     *  DataTypeConversion: '<S24>/Get_Integer'
     *  DiscreteTransferFcn: '<S12>/Discrete Transfer Fcn1'
     *  Product: '<S25>/Product'
     *  Product: '<S25>/Product1'
     *  Selector: '<S24>/Lookup'
     *  Sum: '<S24>/Sum'
     *  Sum: '<S25>/Sum3'
     *  Sum: '<S25>/Sum4'
     *  Sum: '<S25>/Sum5'
     *  Sum: '<S25>/Sum6'
     */
    TwoinputsCRL(rtb_DiscreteTransferFcn_iy + -0.00779332919F *
                 rtDW.DiscreteTransferFcn_states_p[1], (0.000122456287F *
      rtb_sum_beta + 0.000244912575F * rtDW.DiscreteTransferFcn1_states_o[0]) +
                 0.000122456287F * rtDW.DiscreteTransferFcn1_states_o[1],
                 (rtConstP.pooled2[(int32_T)((uint16_T)rtb_Sum2_p + 1U)] -
                  rtConstP.pooled2[(uint16_T)rtb_Sum2_p]) * rtb_convert_pu_mc +
                 rtConstP.pooled2[(uint16_T)rtb_Sum2_p], (rtConstP.pooled2
      [(int32_T)((uint16_T)rtb_Sum2_p + 201U)] - rtConstP.pooled2[(int32_T)
      ((uint16_T)rtb_Sum2_p + 200U)]) * rtb_convert_pu_mc + rtConstP.pooled2
                 [(int32_T)((uint16_T)rtb_Sum2_p + 200U)], &rtb_algDD_o1_j,
                 &rtb_algDD_o2_m);

    /* End of Outputs for SubSystem: '<S10>/Two inputs CRL' */

    /* Sum: '<S7>/Sum4' incorporates:
     *  DiscreteIntegrator: '<S75>/Integrator'
     *  Gain: '<S7>/Gain2'
     *  Gain: '<S80>/Proportional Gain'
     *  Sum: '<S84>/Sum'
     */
    rtb_Sum2_p = (0.065F * rtb_DiscreteTimeIntegrator1 +
                  rtDW.Integrator_DSTATE_p) - 2.51327419E-5F * rtb_algDD_o2_g;

    /* Saturate: '<S7>/Saturation' */
    if (rtb_Sum2_p > 7.0F) {
      rtb_Sum2_p = 7.0F;
    } else if (rtb_Sum2_p < -7.0F) {
      rtb_Sum2_p = -7.0F;
    }

    /* Sum: '<S7>/Sum1' incorporates:
     *  Saturate: '<S7>/Saturation'
     */
    rtb_convert_pu_mc = rtb_Sum2_p - rtb_algDD_o1_j;

    /* Sum: '<S7>/Sum5' incorporates:
     *  Constant: '<S7>/Constant9'
     *  DiscreteIntegrator: '<S123>/Integrator'
     *  Gain: '<S128>/Proportional Gain'
     *  Gain: '<S7>/Gain1'
     *  Sum: '<S132>/Sum'
     *  Sum: '<S7>/Sum2'
     */
    rtb_Sum2_p = ((0.0F - rtb_algDD_o2_g) * 0.065F + rtDW.Integrator_DSTATE_l) +
      2.51327419E-5F * rtb_algDD_o1_h;

    /* Saturate: '<S7>/Saturation1' */
    if (rtb_Sum2_p > 5.0F) {
      rtb_Sum2_p = 5.0F;
    } else if (rtb_Sum2_p < -5.0F) {
      rtb_Sum2_p = -5.0F;
    }

    /* Sum: '<S7>/Sum3' incorporates:
     *  Saturate: '<S7>/Saturation1'
     */
    rtb_DiscreteTransferFcn_iy = rtb_Sum2_p - rtb_algDD_o2_m;

    /* Sum: '<S36>/Sum2' incorporates:
     *  DataTypeConversion: '<S36>/Data Type Conversion1'
     *  DataTypeConversion: '<S36>/Get_Integer'
     */
    rtb_sum_beta = rtb_indexing_p - (real32_T)(uint16_T)rtb_indexing_p;

    /* Selector: '<S36>/Lookup' incorporates:
     *  Constant: '<S36>/offset'
     *  Constant: '<S36>/sine_table_values'
     *  DataTypeConversion: '<S36>/Get_Integer'
     *  Sum: '<S36>/Sum'
     *  Sum: '<S38>/Sum5'
     */
    rtb_Sum2_p = rtConstP.pooled2[(int32_T)((uint16_T)rtb_indexing_p + 200U)];
    algDD_o1_tmp = rtConstP.pooled2[(uint16_T)rtb_indexing_p];

    /* Outputs for Atomic SubSystem: '<S31>/Two inputs CRL' */
    /* AlgorithmDescriptorDelegate generated from: '<S37>/a16' incorporates:
     *  Constant: '<S36>/offset'
     *  Constant: '<S36>/sine_table_values'
     *  Constant: '<S7>/Constant10'
     *  DataTypeConversion: '<S36>/Get_Integer'
     *  DiscreteIntegrator: '<S171>/Integrator'
     *  DiscreteIntegrator: '<S219>/Integrator'
     *  Gain: '<S176>/Proportional Gain'
     *  Gain: '<S224>/Proportional Gain'
     *  Gain: '<S7>/Gain4'
     *  Gain: '<S7>/Gain5'
     *  Product: '<S37>/dcos'
     *  Product: '<S37>/qsin'
     *  Product: '<S38>/Product'
     *  Product: '<S38>/Product1'
     *  Product: '<S7>/Divide'
     *  Product: '<S7>/Divide1'
     *  Selector: '<S36>/Lookup'
     *  Sum: '<S180>/Sum'
     *  Sum: '<S228>/Sum'
     *  Sum: '<S36>/Sum'
     *  Sum: '<S37>/sum_alpha'
     *  Sum: '<S38>/Sum3'
     *  Sum: '<S38>/Sum4'
     *  Sum: '<S38>/Sum5'
     *  Sum: '<S38>/Sum6'
     *  Sum: '<S7>/Sum8'
     *  Sum: '<S7>/Sum9'
     */
    rtDW.algDD_o1 = (((15.712F * rtb_convert_pu_mc + rtDW.Integrator_DSTATE_f) +
                      rtb_algDD_o1_h) - 0.00628318544F * rtb_algDD_o2_m) / 50.0F
      * ((rtConstP.pooled2[(int32_T)((uint16_T)rtb_indexing_p + 201U)] -
          rtb_Sum2_p) * rtb_sum_beta + rtb_Sum2_p) - (((15.712F *
      rtb_DiscreteTransferFcn_iy + rtDW.Integrator_DSTATE_h) + 0.00628318544F *
      rtb_algDD_o1_j) + rtb_algDD_o2_g) / 50.0F * ((rtConstP.pooled2[(int32_T)
      ((uint16_T)rtb_indexing_p + 1U)] - algDD_o1_tmp) * rtb_sum_beta +
      algDD_o1_tmp);

    /* End of Outputs for SubSystem: '<S31>/Two inputs CRL' */

    /* Gain: '<S3>/Gain1' */
    F_Id = 0.707106769F * rtb_algDD_o1_j;

    /* Gain: '<S3>/Gain4' */
    F_Ud = 0.707106769F * rtb_algDD_o1_h;

    /* Update for DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states_a[1] = rtDW.DiscreteTransferFcn_states_a[0];
    rtDW.DiscreteTransferFcn_states_a[0] = DiscreteTransferFcn_tmp_f;

    /* Update for DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn1' */
    rtDW.DiscreteTransferFcn1_states_h[1] = rtDW.DiscreteTransferFcn1_states_h[0];
    rtDW.DiscreteTransferFcn1_states_h[0] = DiscreteTransferFcn1_tmp_n;

    /* Update for DiscreteIntegrator: '<S75>/Integrator' incorporates:
     *  Gain: '<S72>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_p += 0.001F * rtb_DiscreteTimeIntegrator1;

    /* Update for DiscreteTransferFcn: '<S12>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states_p[1] = rtDW.DiscreteTransferFcn_states_p[0];
    rtDW.DiscreteTransferFcn_states_p[0] = rtb_DiscreteTransferFcn_b;

    /* Update for DiscreteTransferFcn: '<S12>/Discrete Transfer Fcn1' */
    rtDW.DiscreteTransferFcn1_states_o[1] = rtDW.DiscreteTransferFcn1_states_o[0];
    rtDW.DiscreteTransferFcn1_states_o[0] = rtb_DiscreteTransferFcn1_e;

    /* Update for DiscreteIntegrator: '<S219>/Integrator' incorporates:
     *  Gain: '<S216>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_f += 0.0F * rtb_convert_pu_mc;

    /* Update for DiscreteIntegrator: '<S123>/Integrator' incorporates:
     *  Constant: '<S7>/Constant9'
     *  Gain: '<S120>/Integral Gain'
     *  Sum: '<S7>/Sum2'
     */
    rtDW.Integrator_DSTATE_l += (0.0F - rtb_algDD_o2_g) * 0.0015F;

    /* Update for DiscreteIntegrator: '<S171>/Integrator' incorporates:
     *  Gain: '<S168>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_h += 0.0F * rtb_DiscreteTransferFcn_iy;
  }

  /* End of Outputs for SubSystem: '<S1>/DQ_FGD' */

  /* Outputs for Enabled SubSystem: '<S1>/QPR_OGD' incorporates:
   *  EnablePort: '<S5>/Enable'
   */
  if (rtb_State_B > 0) {
    /* Delay: '<S241>/Delay1' */
    rtb_State_A = rtDW.Delay1_DSTATE;

    /* DiscreteIntegrator: '<S241>/Discrete-Time Integrator' incorporates:
     *  Delay: '<S241>/Delay1'
     */
    if ((rtDW.Delay1_DSTATE > 0) && (rtDW.DiscreteTimeIntegrator_PrevRese <= 0))
    {
      rtDW.DiscreteTimeIntegrator_DSTATE = 0.0156F;
    }

    /* Gain: '<S301>/convert_pu' incorporates:
     *  DiscreteIntegrator: '<S241>/Discrete-Time Integrator'
     *  Gain: '<S319>/convert_pu'
     *  Gain: '<S328>/convert_pu'
     */
    rtb_convert_pu_mc = 0.159154937F * rtDW.DiscreteTimeIntegrator_DSTATE;

    /* If: '<S301>/If' incorporates:
     *  Constant: '<S302>/Constant'
     *  Gain: '<S301>/convert_pu'
     *  RelationalOperator: '<S302>/Compare'
     */
    if (rtb_convert_pu_mc < 0.0F) {
      /* Outputs for IfAction SubSystem: '<S301>/If Action Subsystem' incorporates:
       *  ActionPort: '<S303>/Action Port'
       */
      IfActionSubsystem(rtb_convert_pu_mc, &rtb_Sum2_p);

      /* End of Outputs for SubSystem: '<S301>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S301>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S304>/Action Port'
       */
      IfActionSubsystem1(rtb_convert_pu_mc, &rtb_Sum2_p);

      /* End of Outputs for SubSystem: '<S301>/If Action Subsystem1' */
    }

    /* End of If: '<S301>/If' */

    /* Gain: '<S299>/indexing' */
    rtb_Sum2_p *= 800.0F;

    /* If: '<S319>/If' incorporates:
     *  Constant: '<S320>/Constant'
     *  RelationalOperator: '<S320>/Compare'
     */
    if (rtb_convert_pu_mc < 0.0F) {
      /* Outputs for IfAction SubSystem: '<S319>/If Action Subsystem' incorporates:
       *  ActionPort: '<S321>/Action Port'
       */
      IfActionSubsystem(rtb_convert_pu_mc, &DiscreteTransferFcn_tmp_f);

      /* End of Outputs for SubSystem: '<S319>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S319>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S322>/Action Port'
       */
      IfActionSubsystem1(rtb_convert_pu_mc, &DiscreteTransferFcn_tmp_f);

      /* End of Outputs for SubSystem: '<S319>/If Action Subsystem1' */
    }

    /* End of If: '<S319>/If' */

    /* Gain: '<S317>/indexing' */
    DiscreteTransferFcn_tmp_f *= 800.0F;

    /* If: '<S328>/If' incorporates:
     *  Constant: '<S329>/Constant'
     *  RelationalOperator: '<S329>/Compare'
     */
    if (rtb_convert_pu_mc < 0.0F) {
      /* Outputs for IfAction SubSystem: '<S328>/If Action Subsystem' incorporates:
       *  ActionPort: '<S330>/Action Port'
       */
      IfActionSubsystem(rtb_convert_pu_mc, &rtb_sum_beta);

      /* End of Outputs for SubSystem: '<S328>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S328>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S331>/Action Port'
       */
      IfActionSubsystem1(rtb_convert_pu_mc, &rtb_sum_beta);

      /* End of Outputs for SubSystem: '<S328>/If Action Subsystem1' */
    }

    /* End of If: '<S328>/If' */

    /* Gain: '<S326>/indexing' */
    rtb_sum_beta *= 800.0F;

    /* DataTypeConversion: '<S326>/Get_Integer' */
    rtb_Get_Integer_c0 = (uint16_T)rtb_sum_beta;

    /* Gain: '<S307>/convert_pu' incorporates:
     *  DiscreteIntegrator: '<S241>/Discrete-Time Integrator'
     *  Inport: '<Root>/O_Phase_add'
     *  Sum: '<S239>/Add4'
     */
    rtb_DiscreteTimeIntegrator1 = (rtDW.DiscreteTimeIntegrator_DSTATE +
      O_Phase_add) * 0.159154937F;

    /* If: '<S307>/If' incorporates:
     *  Constant: '<S308>/Constant'
     *  RelationalOperator: '<S308>/Compare'
     */
    if (rtb_DiscreteTimeIntegrator1 < 0.0F) {
      /* Outputs for IfAction SubSystem: '<S307>/If Action Subsystem' incorporates:
       *  ActionPort: '<S309>/Action Port'
       */
      IfActionSubsystem(rtb_DiscreteTimeIntegrator1, &rtb_convert_pu_mc);

      /* End of Outputs for SubSystem: '<S307>/If Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S307>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S310>/Action Port'
       */
      IfActionSubsystem1(rtb_DiscreteTimeIntegrator1, &rtb_convert_pu_mc);

      /* End of Outputs for SubSystem: '<S307>/If Action Subsystem1' */
    }

    /* End of If: '<S307>/If' */

    /* Gain: '<S242>/indexing' */
    rtb_convert_pu_mc *= 1600.0F;

    /* Selector: '<S242>/Lookup' incorporates:
     *  Constant: '<S242>/sine_table_values'
     *  DataTypeConversion: '<S242>/Get_Integer'
     */
    rtb_DiscreteTimeIntegrator1 = rtConstP.sine_table_values_Value[(uint16_T)
      rtb_convert_pu_mc];

    /* Sum: '<S238>/Add2' incorporates:
     *  Constant: '<S242>/offset'
     *  Constant: '<S242>/sine_table_values'
     *  DataTypeConversion: '<S242>/Data Type Conversion1'
     *  DataTypeConversion: '<S242>/Get_Integer'
     *  Inport: '<Root>/IL_fb'
     *  Inport: '<Root>/O_ILref'
     *  Product: '<S238>/Product'
     *  Product: '<S306>/Product'
     *  Selector: '<S242>/Lookup'
     *  Sum: '<S242>/Sum'
     *  Sum: '<S242>/Sum2'
     *  Sum: '<S306>/Sum3'
     *  Sum: '<S306>/Sum4'
     */
    rtb_DiscreteTimeIntegrator1 = ((rtConstP.sine_table_values_Value[(int32_T)
      ((uint16_T)rtb_convert_pu_mc + 1U)] - rtb_DiscreteTimeIntegrator1) *
      (rtb_convert_pu_mc - (real32_T)(uint16_T)rtb_convert_pu_mc) +
      rtb_DiscreteTimeIntegrator1) * O_IL_ref - IL_fb;

    /* DiscreteIntegrator: '<S240>/Discrete-Time Integrator' */
    rtb_indexing_p = rtDW.DiscreteTimeIntegrator_DSTATE_k;

    /* Product: '<S238>/Divide1' incorporates:
     *  DiscreteIntegrator: '<S240>/Discrete-Time Integrator'
     *  Gain: '<S240>/Gain2'
     *  Inport: '<Root>/Udc_set'
     *  Inport: '<Root>/Uo_fb'
     *  Sum: '<S238>/Add3'
     *  Sum: '<S240>/Add'
     */
    rtDW.Divide1 = ((QPR_Kp * rtb_DiscreteTimeIntegrator1 +
                     rtDW.DiscreteTimeIntegrator_DSTATE_k) + Uo_fb) / Udc_set;

    /* Sum: '<S326>/Sum2' incorporates:
     *  DataTypeConversion: '<S326>/Data Type Conversion1'
     *  DataTypeConversion: '<S326>/Get_Integer'
     */
    rtb_convert_pu_mc = rtb_sum_beta - (real32_T)(uint16_T)rtb_sum_beta;

    /* DiscreteTransferFcn: '<S314>/Discrete Transfer Fcn' incorporates:
     *  Inport: '<Root>/IL_fb'
     */
    rtb_sum_beta = (IL_fb - -1.98343372F * rtDW.DiscreteTransferFcn_states[0]) -
      0.984413326F * rtDW.DiscreteTransferFcn_states[1];
    rtb_DiscreteTransferFcn_iy = rtb_sum_beta;
    rtb_DiscreteTransferFcn_b = 0.00779332919F * rtb_sum_beta + 0.0F *
      rtDW.DiscreteTransferFcn_states[0];

    /* DiscreteTransferFcn: '<S314>/Discrete Transfer Fcn1' incorporates:
     *  Inport: '<Root>/IL_fb'
     */
    rtb_sum_beta = (IL_fb - -1.98343372F * rtDW.DiscreteTransferFcn1_states[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn1_states[1];
    rtb_algDD_o1_h = rtb_sum_beta;

    /* Outputs for Atomic SubSystem: '<S312>/Two inputs CRL' */
    /* DiscreteTransferFcn: '<S314>/Discrete Transfer Fcn' incorporates:
     *  Constant: '<S326>/offset'
     *  Constant: '<S326>/sine_table_values'
     *  DiscreteTransferFcn: '<S314>/Discrete Transfer Fcn1'
     *  Product: '<S327>/Product'
     *  Product: '<S327>/Product1'
     *  Selector: '<S326>/Lookup'
     *  Sum: '<S326>/Sum'
     *  Sum: '<S327>/Sum3'
     *  Sum: '<S327>/Sum4'
     *  Sum: '<S327>/Sum5'
     *  Sum: '<S327>/Sum6'
     */
    TwoinputsCRL(rtb_DiscreteTransferFcn_b + -0.00779332919F *
                 rtDW.DiscreteTransferFcn_states[1], (0.000122456287F *
      rtb_sum_beta + 0.000244912575F * rtDW.DiscreteTransferFcn1_states[0]) +
                 0.000122456287F * rtDW.DiscreteTransferFcn1_states[1],
                 (rtConstP.pooled2[(int32_T)(rtb_Get_Integer_c0 + 1U)] -
                  rtConstP.pooled2[rtb_Get_Integer_c0]) * rtb_convert_pu_mc +
                 rtConstP.pooled2[rtb_Get_Integer_c0], (rtConstP.pooled2
      [(int32_T)(rtb_Get_Integer_c0 + 201U)] - rtConstP.pooled2[(int32_T)
      (rtb_Get_Integer_c0 + 200U)]) * rtb_convert_pu_mc + rtConstP.pooled2
                 [(int32_T)(rtb_Get_Integer_c0 + 200U)], &rtb_sum_beta,
                 &DiscreteTransferFcn1_tmp_n);

    /* End of Outputs for SubSystem: '<S312>/Two inputs CRL' */

    /* Gain: '<S239>/Gain2' */
    O_Iq = 0.707106769F * DiscreteTransferFcn1_tmp_n;

    /* Sum: '<S317>/Sum2' incorporates:
     *  DataTypeConversion: '<S317>/Data Type Conversion1'
     *  DataTypeConversion: '<S317>/Get_Integer'
     */
    rtb_convert_pu_mc = DiscreteTransferFcn_tmp_f - (real32_T)(uint16_T)
      DiscreteTransferFcn_tmp_f;

    /* DiscreteTransferFcn: '<S313>/Discrete Transfer Fcn' incorporates:
     *  Inport: '<Root>/Uo_fb'
     */
    rtb_sum_beta = (Uo_fb - -1.98343372F * rtDW.DiscreteTransferFcn_states_o[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn_states_o[1];
    rtb_DiscreteTransferFcn_b = rtb_sum_beta;
    DiscreteTransferFcn1_tmp_n = 0.00779332919F * rtb_sum_beta + 0.0F *
      rtDW.DiscreteTransferFcn_states_o[0];

    /* DiscreteTransferFcn: '<S313>/Discrete Transfer Fcn1' incorporates:
     *  Inport: '<Root>/Uo_fb'
     */
    rtb_sum_beta = (Uo_fb - -1.98343372F * rtDW.DiscreteTransferFcn1_states_l[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn1_states_l[1];
    rtb_algDD_o2_g = rtb_sum_beta;

    /* Outputs for Atomic SubSystem: '<S311>/Two inputs CRL' */
    /* DiscreteTransferFcn: '<S313>/Discrete Transfer Fcn' incorporates:
     *  Constant: '<S317>/offset'
     *  Constant: '<S317>/sine_table_values'
     *  DataTypeConversion: '<S317>/Get_Integer'
     *  DiscreteTransferFcn: '<S313>/Discrete Transfer Fcn1'
     *  Product: '<S318>/Product'
     *  Product: '<S318>/Product1'
     *  Selector: '<S317>/Lookup'
     *  Sum: '<S317>/Sum'
     *  Sum: '<S318>/Sum3'
     *  Sum: '<S318>/Sum4'
     *  Sum: '<S318>/Sum5'
     *  Sum: '<S318>/Sum6'
     */
    TwoinputsCRL(DiscreteTransferFcn1_tmp_n + -0.00779332919F *
                 rtDW.DiscreteTransferFcn_states_o[1], (0.000122456287F *
      rtb_sum_beta + 0.000244912575F * rtDW.DiscreteTransferFcn1_states_l[0]) +
                 0.000122456287F * rtDW.DiscreteTransferFcn1_states_l[1],
                 (rtConstP.pooled2[(int32_T)((uint16_T)DiscreteTransferFcn_tmp_f
      + 1U)] - rtConstP.pooled2[(uint16_T)DiscreteTransferFcn_tmp_f]) *
                 rtb_convert_pu_mc + rtConstP.pooled2[(uint16_T)
                 DiscreteTransferFcn_tmp_f], (rtConstP.pooled2[(int32_T)
      ((uint16_T)DiscreteTransferFcn_tmp_f + 201U)] - rtConstP.pooled2[(int32_T)
      ((uint16_T)DiscreteTransferFcn_tmp_f + 200U)]) * rtb_convert_pu_mc +
                 rtConstP.pooled2[(int32_T)((uint16_T)DiscreteTransferFcn_tmp_f
      + 200U)], &rtb_sum_beta, &DiscreteTransferFcn_tmp_f);

    /* End of Outputs for SubSystem: '<S311>/Two inputs CRL' */

    /* Gain: '<S239>/Gain4' */
    O_Uq = 0.707106769F * DiscreteTransferFcn_tmp_f;

    /* Sum: '<S299>/Sum2' incorporates:
     *  DataTypeConversion: '<S299>/Data Type Conversion1'
     *  DataTypeConversion: '<S299>/Get_Integer'
     */
    rtb_convert_pu_mc = rtb_Sum2_p - (real32_T)(uint16_T)rtb_Sum2_p;

    /* DiscreteTransferFcn: '<S246>/Discrete Transfer Fcn' incorporates:
     *  Inport: '<Root>/Uo_fb'
     */
    rtb_sum_beta = (Uo_fb - -1.98343372F * rtDW.DiscreteTransferFcn_states_k[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn_states_k[1];
    DiscreteTransferFcn1_tmp_n = rtb_sum_beta;
    DiscreteTransferFcn_tmp_f = 0.00779332919F * rtb_sum_beta + 0.0F *
      rtDW.DiscreteTransferFcn_states_k[0];

    /* DiscreteTransferFcn: '<S246>/Discrete Transfer Fcn1' incorporates:
     *  Inport: '<Root>/Uo_fb'
     */
    rtb_sum_beta = (Uo_fb - -1.98343372F * rtDW.DiscreteTransferFcn1_states_lw[0])
      - 0.984413326F * rtDW.DiscreteTransferFcn1_states_lw[1];
    rtb_DiscreteTransferFcn1_e = rtb_sum_beta;

    /* Outputs for Atomic SubSystem: '<S245>/Two inputs CRL' */
    /* DiscreteTransferFcn: '<S246>/Discrete Transfer Fcn' incorporates:
     *  Constant: '<S299>/offset'
     *  Constant: '<S299>/sine_table_values'
     *  DataTypeConversion: '<S299>/Get_Integer'
     *  DiscreteTransferFcn: '<S246>/Discrete Transfer Fcn1'
     *  Product: '<S300>/Product'
     *  Product: '<S300>/Product1'
     *  Selector: '<S299>/Lookup'
     *  Sum: '<S299>/Sum'
     *  Sum: '<S300>/Sum3'
     *  Sum: '<S300>/Sum4'
     *  Sum: '<S300>/Sum5'
     *  Sum: '<S300>/Sum6'
     */
    TwoinputsCRL(DiscreteTransferFcn_tmp_f + -0.00779332919F *
                 rtDW.DiscreteTransferFcn_states_k[1], (0.000122456287F *
      rtb_sum_beta + 0.000244912575F * rtDW.DiscreteTransferFcn1_states_lw[0]) +
                 0.000122456287F * rtDW.DiscreteTransferFcn1_states_lw[1],
                 (rtConstP.pooled2[(int32_T)((uint16_T)rtb_Sum2_p + 1U)] -
                  rtConstP.pooled2[(uint16_T)rtb_Sum2_p]) * rtb_convert_pu_mc +
                 rtConstP.pooled2[(uint16_T)rtb_Sum2_p], (rtConstP.pooled2
      [(int32_T)((uint16_T)rtb_Sum2_p + 201U)] - rtConstP.pooled2[(int32_T)
      ((uint16_T)rtb_Sum2_p + 200U)]) * rtb_convert_pu_mc + rtConstP.pooled2
                 [(int32_T)((uint16_T)rtb_Sum2_p + 200U)], &rtb_sum_beta,
                 &rtb_Sum2_p);

    /* End of Outputs for SubSystem: '<S245>/Two inputs CRL' */

    /* Sum: '<S241>/Add2' */
    rtb_convert_pu_mc = rtb_sum_beta;

    /* Sum: '<S289>/Sum' incorporates:
     *  DiscreteIntegrator: '<S280>/Integrator'
     *  Sum: '<S241>/Add2'
     */
    rtb_sum_beta += rtDW.Integrator_DSTATE;

    /* Saturate: '<S287>/Saturation' incorporates:
     *  DeadZone: '<S273>/DeadZone'
     */
    if (rtb_sum_beta > 500.0F) {
      DiscreteTransferFcn_tmp_f = 500.0F;
      rtb_sum_beta -= 500.0F;
    } else {
      if (rtb_sum_beta < -700.0F) {
        DiscreteTransferFcn_tmp_f = -700.0F;
      } else {
        DiscreteTransferFcn_tmp_f = rtb_sum_beta;
      }

      if (rtb_sum_beta >= -700.0F) {
        rtb_sum_beta = 0.0F;
      } else {
        rtb_sum_beta -= -700.0F;
      }
    }

    /* End of Saturate: '<S287>/Saturation' */

    /* Gain: '<S277>/Integral Gain' */
    rtb_convert_pu_mc *= 0.001F;

    /* Update for Delay: '<S241>/Delay1' incorporates:
     *  Constant: '<S241>/Constant8'
     *  DataTypeConversion: '<S241>/Data Type Conversion1'
     *  DiscreteIntegrator: '<S241>/Discrete-Time Integrator'
     *  RelationalOperator: '<S241>/Relational Operator'
     */
    rtDW.Delay1_DSTATE = (uint8_T)(rtDW.DiscreteTimeIntegrator_DSTATE >=
      6.25176954F);

    /* Update for DiscreteIntegrator: '<S241>/Discrete-Time Integrator' incorporates:
     *  Constant: '<S241>/Constant7'
     *  Sum: '<S241>/Sum'
     */
    rtDW.DiscreteTimeIntegrator_DSTATE += (DiscreteTransferFcn_tmp_f +
      314.159271F) * 0.0001F;
    if (rtDW.DiscreteTimeIntegrator_DSTATE < 0.0156F) {
      rtDW.DiscreteTimeIntegrator_DSTATE = 0.0156F;
    }

    rtDW.DiscreteTimeIntegrator_PrevRese = (int8_T)(rtb_State_A > 0);

    /* End of Update for DiscreteIntegrator: '<S241>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S240>/Discrete-Time Integrator' incorporates:
     *  DiscreteIntegrator: '<S240>/Discrete-Time Integrator1'
     *  Gain: '<S240>/Gain3'
     *  Gain: '<S240>/Gain4'
     *  Gain: '<S240>/Gain5'
     *  Sum: '<S240>/Sum'
     */
    rtDW.DiscreteTimeIntegrator_DSTATE_k += ((2.0F * QPR_Kr * QPR_wc *
      rtb_DiscreteTimeIntegrator1 - 2.0F * QPR_wc *
      rtDW.DiscreteTimeIntegrator_DSTATE_k) - QPR_w0 * QPR_w0 *
      rtDW.DiscreteTimeIntegrator1_DSTATE) * 0.0001F;

    /* Update for DiscreteIntegrator: '<S240>/Discrete-Time Integrator1' */
    rtDW.DiscreteTimeIntegrator1_DSTATE += 0.0001F * rtb_indexing_p;

    /* Update for DiscreteTransferFcn: '<S314>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states[1] = rtDW.DiscreteTransferFcn_states[0];
    rtDW.DiscreteTransferFcn_states[0] = rtb_DiscreteTransferFcn_iy;

    /* Update for DiscreteTransferFcn: '<S314>/Discrete Transfer Fcn1' */
    rtDW.DiscreteTransferFcn1_states[1] = rtDW.DiscreteTransferFcn1_states[0];
    rtDW.DiscreteTransferFcn1_states[0] = rtb_algDD_o1_h;

    /* Update for DiscreteTransferFcn: '<S313>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states_o[1] = rtDW.DiscreteTransferFcn_states_o[0];
    rtDW.DiscreteTransferFcn_states_o[0] = rtb_DiscreteTransferFcn_b;

    /* Update for DiscreteTransferFcn: '<S313>/Discrete Transfer Fcn1' */
    rtDW.DiscreteTransferFcn1_states_l[1] = rtDW.DiscreteTransferFcn1_states_l[0];
    rtDW.DiscreteTransferFcn1_states_l[0] = rtb_algDD_o2_g;

    /* Update for DiscreteTransferFcn: '<S246>/Discrete Transfer Fcn' */
    rtDW.DiscreteTransferFcn_states_k[1] = rtDW.DiscreteTransferFcn_states_k[0];
    rtDW.DiscreteTransferFcn_states_k[0] = DiscreteTransferFcn1_tmp_n;

    /* Update for DiscreteTransferFcn: '<S246>/Discrete Transfer Fcn1' */
    rtDW.DiscreteTransferFcn1_states_lw[1] =
      rtDW.DiscreteTransferFcn1_states_lw[0];
    rtDW.DiscreteTransferFcn1_states_lw[0] = rtb_DiscreteTransferFcn1_e;

    /* Switch: '<S271>/Switch1' incorporates:
     *  Constant: '<S271>/Clamping_zero'
     *  Constant: '<S271>/Constant'
     *  Constant: '<S271>/Constant2'
     *  RelationalOperator: '<S271>/fix for DT propagation issue'
     */
    if (rtb_sum_beta > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S271>/Switch2' incorporates:
     *  Constant: '<S271>/Clamping_zero'
     *  Constant: '<S271>/Constant3'
     *  Constant: '<S271>/Constant4'
     *  RelationalOperator: '<S271>/fix for DT propagation issue1'
     */
    if (rtb_convert_pu_mc > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S271>/Switch' incorporates:
     *  Constant: '<S271>/Clamping_zero'
     *  Constant: '<S271>/Constant1'
     *  Logic: '<S271>/AND3'
     *  RelationalOperator: '<S271>/Equal1'
     *  RelationalOperator: '<S271>/Relational Operator'
     *  Switch: '<S271>/Switch1'
     *  Switch: '<S271>/Switch2'
     */
    if ((rtb_sum_beta != 0.0F) && (tmp == tmp_0)) {
      rtb_convert_pu_mc = 0.0F;
    }

    /* Update for DiscreteIntegrator: '<S280>/Integrator' incorporates:
     *  Switch: '<S271>/Switch'
     */
    rtDW.Integrator_DSTATE += rtb_convert_pu_mc;
    if (rtDW.Integrator_DSTATE > 400.0F) {
      rtDW.Integrator_DSTATE = 400.0F;
    } else if (rtDW.Integrator_DSTATE < -400.0F) {
      rtDW.Integrator_DSTATE = -400.0F;
    }

    /* End of Update for DiscreteIntegrator: '<S280>/Integrator' */
  }

  /* End of Outputs for SubSystem: '<S1>/QPR_OGD' */

  /* MultiPortSwitch: '<S1>/Multiport Switch' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Mode_Ch'
   */
  switch (Mode_Ch) {
   case 1:
    rtb_Add1 = rtDW.algDD_o1;
    break;

   case 2:
    rtb_Add1 = rtDW.Divide1;
    break;

   default:
    rtb_Add1 = 0.0;
    break;
  }

  /* End of MultiPortSwitch: '<S1>/Multiport Switch' */

  /* Gain: '<S4>/Gain3' incorporates:
   *  Constant: '<S4>/Constant2'
   *  Product: '<S4>/Product3'
   *  Sum: '<S4>/Add1'
   */
  Duty_L = (real32_T)((0.85000002384185791 * rtb_Add1 + 1.0) * 0.5);

  /* Sum: '<S4>/Add5' incorporates:
   *  Constant: '<S4>/Constant11'
   */
  Duty_R = 1.0F - Duty_L;

  /* End of Outputs for SubSystem: '<Root>/BDA_Control' */
}

/* Model initialize function */
void BDA_Control_initialize(void)
{
  /* Registration code */

  /* external inputs */
  Mode_Ch = 3U;
  O_Phase_add=0.0645771F;
  O_IL_ref = 1.41421366F;
  Udc_set = 50.0F;
  F_U_ref = 24.0F;
  F_Freq_set = 50.0F;

  /* SystemInitialize for Atomic SubSystem: '<Root>/BDA_Control' */
  /* SystemInitialize for Enabled SubSystem: '<S1>/QPR_OGD' */
  /* InitializeConditions for DiscreteIntegrator: '<S241>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE = 0.0156F;
  rtDW.DiscreteTimeIntegrator_PrevRese = 2;

  /* End of SystemInitialize for SubSystem: '<S1>/QPR_OGD' */
  /* End of SystemInitialize for SubSystem: '<Root>/BDA_Control' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
