/*
 * File: BDA_Control.h
 *
 * Code generated for Simulink model 'BDA_Control'.
 *
 * Model version                  : 1.25
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Thu Apr 17 22:02:43 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BDA_Control_h_
#define RTW_HEADER_BDA_Control_h_
#ifndef BDA_Control_COMMON_INCLUDES_
#define BDA_Control_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* BDA_Control_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTransferFcn_states[2];/* '<S313>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn1_states_c[2];/* '<S313>/Discrete Transfer Fcn1' */
  real32_T DiscreteTransferFcn_states_o[2];/* '<S312>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn1_states_l[2];/* '<S312>/Discrete Transfer Fcn1' */
  real32_T DiscreteTransferFcn_states_k[2];/* '<S245>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn1_states_lw[2];/* '<S245>/Discrete Transfer Fcn1' */
  real32_T DiscreteTransferFcn_states_a[2];/* '<S11>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn1_states_h[2];/* '<S11>/Discrete Transfer Fcn1' */
  real32_T DiscreteTransferFcn_states_p[2];/* '<S12>/Discrete Transfer Fcn' */
  real32_T DiscreteTransferFcn1_states_o[2];/* '<S12>/Discrete Transfer Fcn1' */
  real32_T Divide1;                    /* '<S238>/Divide1' */
  real32_T Add1;                       /* '<S236>/Add1' */
  real32_T Input;                      /* '<S237>/Input' */
  real32_T algDD_o1;
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S240>/Discrete-Time Integrator' */
  real32_T DiscreteTransferFcn1_states;/* '<S238>/Discrete Transfer Fcn1' */
  real32_T Integrator_DSTATE;          /* '<S279>/Integrator' */
  real32_T Integrator_DSTATE_p;        /* '<S75>/Integrator' */
  real32_T Integrator_DSTATE_f;        /* '<S219>/Integrator' */
  real32_T Integrator_DSTATE_l;        /* '<S123>/Integrator' */
  real32_T Integrator_DSTATE_h;        /* '<S171>/Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S240>/Discrete-Time Integrator' */
  uint8_T Delay1_DSTATE;               /* '<S240>/Delay1' */
  boolean_T Delay_DSTATE;              /* '<S236>/Delay' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S36>/sine_table_values'
   *   '<S15>/sine_table_values'
   *   '<S24>/sine_table_values'
   *   '<S298>/sine_table_values'
   *   '<S316>/sine_table_values'
   *   '<S325>/sine_table_values'
   */
  real32_T pooled2[1002];

  /* Computed Parameter: sine_table_values_Value
   * Referenced by: '<S241>/sine_table_values'
   */
  real32_T sine_table_values_Value[2002];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint8_T Mode_Ch;                /* '<Root>/Mode_Ch'
                                        * 模式选择，给1为离网模式，给2为并网模式，给3为停止输出
                                        */
extern real32_T O_Phase_add;           /* '<Root>/O_Phase_add'
                                        * 并网电流相移值
                                        */
extern real32_T O_IL_ref;              /* '<Root>/O_ILref'
                                        * 并网电流目标值，需要乘根号2
                                        */
extern real32_T IL_fb;                 /* '<Root>/IL_fb'
                                        * 电感电流反馈值，实际采到的电流
                                        */
extern real32_T Uo_fb;                 /* '<Root>/Uo_fb'
                                        * 逆变输出or电网电压值
                                        */
extern real32_T Udc_set;               /* '<Root>/Udc_set'
                                        * 直流侧电压值
                                        */
extern real32_T F_U_ref;               /* '<Root>/F_U_ref'
                                        * 离网模式输出电压目标值
                                        */
extern real32_T F_Freq_set;            /* '<Root>/F_Freq_set'
                                        * 离网逆变输出电压频率
                                        */
extern real32_T Duty_L;                /* '<S4>/Gain3'
                                        * 左桥臂PWM输出占空比
                                        */
extern real32_T Duty_R;                /* '<S4>/Add5'
                                        * 右桥臂输出PWM占空比
                                        */
extern real32_T O_Iq;                  /* '<S239>/Gain2'
                                        * 并网模式电流Q轴分量，加负号
                                        */
extern real32_T O_Uq;                  /* '<S239>/Gain4'
                                        * 并网模式电压Q轴分量，加负号
                                        */
extern real32_T F_Id;                  /* '<S3>/Gain1'
                                        * 离网模式输出电流值
                                        */
extern real32_T F_Ud;                  /* '<S3>/Gain4'
                                        * 离网模式输出电压值
                                        */

/* Model entry point functions */
extern void BDA_Control_initialize(void);
extern void BDA_Control_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Propagation' : Unused code path elimination
 * Block '<S19>/Data Type Duplicate' : Unused code path elimination
 * Block '<S20>/Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S24>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Propagation' : Unused code path elimination
 * Block '<S28>/Data Type Duplicate' : Unused code path elimination
 * Block '<S29>/Data Type Duplicate' : Unused code path elimination
 * Block '<S23>/Data Type Duplicate' : Unused code path elimination
 * Block '<S23>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S7>/Display' : Unused code path elimination
 * Block '<S7>/Display1' : Unused code path elimination
 * Block '<S36>/Data Type Duplicate' : Unused code path elimination
 * Block '<S36>/Data Type Propagation' : Unused code path elimination
 * Block '<S41>/Data Type Duplicate' : Unused code path elimination
 * Block '<S42>/Data Type Duplicate' : Unused code path elimination
 * Block '<S37>/Data Type Duplicate' : Unused code path elimination
 * Block '<S37>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S8>/Data Type Duplicate2' : Unused code path elimination
 * Block '<S1>/Display' : Unused code path elimination
 * Block '<S4>/Scope4' : Unused code path elimination
 * Block '<S240>/Gain5' : Unused code path elimination
 * Block '<S298>/Data Type Duplicate' : Unused code path elimination
 * Block '<S298>/Data Type Propagation' : Unused code path elimination
 * Block '<S302>/Data Type Duplicate' : Unused code path elimination
 * Block '<S303>/Data Type Duplicate' : Unused code path elimination
 * Block '<S297>/Data Type Duplicate' : Unused code path elimination
 * Block '<S297>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S240>/Scope2' : Unused code path elimination
 * Block '<S240>/Sin' : Unused code path elimination
 * Block '<S241>/Data Type Duplicate' : Unused code path elimination
 * Block '<S241>/Data Type Propagation' : Unused code path elimination
 * Block '<S305>/Product1' : Unused code path elimination
 * Block '<S305>/Sum5' : Unused code path elimination
 * Block '<S305>/Sum6' : Unused code path elimination
 * Block '<S308>/Data Type Duplicate' : Unused code path elimination
 * Block '<S309>/Data Type Duplicate' : Unused code path elimination
 * Block '<S242>/Display3' : Unused code path elimination
 * Block '<S242>/Display4' : Unused code path elimination
 * Block '<S316>/Data Type Duplicate' : Unused code path elimination
 * Block '<S316>/Data Type Propagation' : Unused code path elimination
 * Block '<S320>/Data Type Duplicate' : Unused code path elimination
 * Block '<S321>/Data Type Duplicate' : Unused code path elimination
 * Block '<S315>/Data Type Duplicate' : Unused code path elimination
 * Block '<S315>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S325>/Data Type Duplicate' : Unused code path elimination
 * Block '<S325>/Data Type Propagation' : Unused code path elimination
 * Block '<S329>/Data Type Duplicate' : Unused code path elimination
 * Block '<S330>/Data Type Duplicate' : Unused code path elimination
 * Block '<S324>/Data Type Duplicate' : Unused code path elimination
 * Block '<S324>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S15>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<S24>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<S36>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<S7>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S7>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S238>/Gain' : Eliminated nontunable gain of 1
 * Block '<S5>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S284>/Proportional Gain' : Eliminated nontunable gain of 1
 * Block '<S298>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<S241>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<S316>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<S325>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<S1>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S21>/Offset' : Unused code path elimination
 * Block '<S21>/Unary_Minus' : Unused code path elimination
 * Block '<S30>/Offset' : Unused code path elimination
 * Block '<S30>/Unary_Minus' : Unused code path elimination
 * Block '<S43>/Offset' : Unused code path elimination
 * Block '<S43>/Unary_Minus' : Unused code path elimination
 * Block '<S304>/Offset' : Unused code path elimination
 * Block '<S304>/Unary_Minus' : Unused code path elimination
 * Block '<S322>/Offset' : Unused code path elimination
 * Block '<S322>/Unary_Minus' : Unused code path elimination
 * Block '<S331>/Offset' : Unused code path elimination
 * Block '<S331>/Unary_Minus' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('BDA_23A/BDA_Control')    - opens subsystem BDA_23A/BDA_Control
 * hilite_system('BDA_23A/BDA_Control/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'BDA_23A'
 * '<S1>'   : 'BDA_23A/BDA_Control'
 * '<S2>'   : 'BDA_23A/BDA_Control/Chart'
 * '<S3>'   : 'BDA_23A/BDA_Control/DQ_FGD'
 * '<S4>'   : 'BDA_23A/BDA_Control/Duty2SPWM'
 * '<S5>'   : 'BDA_23A/BDA_Control/PI_OGD'
 * '<S6>'   : 'BDA_23A/BDA_Control/DQ_FGD/DQ'
 * '<S7>'   : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control'
 * '<S8>'   : 'BDA_23A/BDA_Control/DQ_FGD/Position Generator1'
 * '<S9>'   : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform'
 * '<S10>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1'
 * '<S11>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/SOGI_II'
 * '<S12>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/SOGI_II1'
 * '<S13>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Sine Cosine'
 * '<S14>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Two inputs CRL'
 * '<S15>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Sine Cosine/Sine-Cosine Lookup'
 * '<S16>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Sine Cosine/Sine-Cosine Lookup/Interpolation'
 * '<S17>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp'
 * '<S18>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/Compare To Zero'
 * '<S19>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem'
 * '<S20>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem1'
 * '<S21>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S22>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Sine Cosine'
 * '<S23>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Two inputs CRL'
 * '<S24>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Sine Cosine/Sine-Cosine Lookup'
 * '<S25>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Sine Cosine/Sine-Cosine Lookup/Interpolation'
 * '<S26>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Sine Cosine/Sine-Cosine Lookup/WrapUp'
 * '<S27>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Sine Cosine/Sine-Cosine Lookup/WrapUp/Compare To Zero'
 * '<S28>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem'
 * '<S29>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem1'
 * '<S30>'  : 'BDA_23A/BDA_Control/DQ_FGD/DQ/Park Transform1/Two inputs CRL/Switch_Axis'
 * '<S31>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform'
 * '<S32>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller'
 * '<S33>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1'
 * '<S34>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2'
 * '<S35>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3'
 * '<S36>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform/Sine Cosine'
 * '<S37>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform/Two inputs CRL'
 * '<S38>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform/Sine Cosine/Interpolation'
 * '<S39>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform/Sine Cosine/WrapUp'
 * '<S40>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform/Sine Cosine/WrapUp/Compare To Zero'
 * '<S41>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform/Sine Cosine/WrapUp/If Action Subsystem'
 * '<S42>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform/Sine Cosine/WrapUp/If Action Subsystem1'
 * '<S43>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S44>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Anti-windup'
 * '<S45>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/D Gain'
 * '<S46>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Filter'
 * '<S47>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Filter ICs'
 * '<S48>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/I Gain'
 * '<S49>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Ideal P Gain'
 * '<S50>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Ideal P Gain Fdbk'
 * '<S51>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Integrator'
 * '<S52>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Integrator ICs'
 * '<S53>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/N Copy'
 * '<S54>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/N Gain'
 * '<S55>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/P Copy'
 * '<S56>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Parallel P Gain'
 * '<S57>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Reset Signal'
 * '<S58>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Saturation'
 * '<S59>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Saturation Fdbk'
 * '<S60>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Sum'
 * '<S61>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Sum Fdbk'
 * '<S62>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Tracking Mode'
 * '<S63>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Tracking Mode Sum'
 * '<S64>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Tsamp - Integral'
 * '<S65>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Tsamp - Ngain'
 * '<S66>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/postSat Signal'
 * '<S67>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/preSat Signal'
 * '<S68>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Anti-windup/Passthrough'
 * '<S69>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/D Gain/Disabled'
 * '<S70>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Filter/Disabled'
 * '<S71>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Filter ICs/Disabled'
 * '<S72>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/I Gain/Internal Parameters'
 * '<S73>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Ideal P Gain/Passthrough'
 * '<S74>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S75>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Integrator/Discrete'
 * '<S76>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Integrator ICs/Internal IC'
 * '<S77>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S78>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/N Gain/Disabled'
 * '<S79>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/P Copy/Disabled'
 * '<S80>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S81>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Reset Signal/Disabled'
 * '<S82>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Saturation/Passthrough'
 * '<S83>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Saturation Fdbk/Disabled'
 * '<S84>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Sum/Sum_PI'
 * '<S85>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Sum Fdbk/Disabled'
 * '<S86>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Tracking Mode/Disabled'
 * '<S87>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S88>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S89>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S90>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/postSat Signal/Forward_Path'
 * '<S91>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller/preSat Signal/Forward_Path'
 * '<S92>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Anti-windup'
 * '<S93>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/D Gain'
 * '<S94>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Filter'
 * '<S95>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Filter ICs'
 * '<S96>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/I Gain'
 * '<S97>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Ideal P Gain'
 * '<S98>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Ideal P Gain Fdbk'
 * '<S99>'  : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Integrator'
 * '<S100>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Integrator ICs'
 * '<S101>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/N Copy'
 * '<S102>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/N Gain'
 * '<S103>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/P Copy'
 * '<S104>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Parallel P Gain'
 * '<S105>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Reset Signal'
 * '<S106>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Saturation'
 * '<S107>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Saturation Fdbk'
 * '<S108>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Sum'
 * '<S109>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Sum Fdbk'
 * '<S110>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Tracking Mode'
 * '<S111>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Tracking Mode Sum'
 * '<S112>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Tsamp - Integral'
 * '<S113>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Tsamp - Ngain'
 * '<S114>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/postSat Signal'
 * '<S115>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/preSat Signal'
 * '<S116>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Anti-windup/Passthrough'
 * '<S117>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/D Gain/Disabled'
 * '<S118>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Filter/Disabled'
 * '<S119>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Filter ICs/Disabled'
 * '<S120>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/I Gain/Internal Parameters'
 * '<S121>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Ideal P Gain/Passthrough'
 * '<S122>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S123>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Integrator/Discrete'
 * '<S124>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Integrator ICs/Internal IC'
 * '<S125>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S126>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/N Gain/Disabled'
 * '<S127>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/P Copy/Disabled'
 * '<S128>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S129>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Reset Signal/Disabled'
 * '<S130>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Saturation/Passthrough'
 * '<S131>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Saturation Fdbk/Disabled'
 * '<S132>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Sum/Sum_PI'
 * '<S133>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Sum Fdbk/Disabled'
 * '<S134>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Tracking Mode/Disabled'
 * '<S135>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S136>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S137>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S138>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/postSat Signal/Forward_Path'
 * '<S139>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller1/preSat Signal/Forward_Path'
 * '<S140>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Anti-windup'
 * '<S141>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/D Gain'
 * '<S142>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Filter'
 * '<S143>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Filter ICs'
 * '<S144>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/I Gain'
 * '<S145>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Ideal P Gain'
 * '<S146>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Ideal P Gain Fdbk'
 * '<S147>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Integrator'
 * '<S148>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Integrator ICs'
 * '<S149>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/N Copy'
 * '<S150>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/N Gain'
 * '<S151>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/P Copy'
 * '<S152>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Parallel P Gain'
 * '<S153>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Reset Signal'
 * '<S154>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Saturation'
 * '<S155>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Saturation Fdbk'
 * '<S156>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Sum'
 * '<S157>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Sum Fdbk'
 * '<S158>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Tracking Mode'
 * '<S159>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Tracking Mode Sum'
 * '<S160>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Tsamp - Integral'
 * '<S161>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Tsamp - Ngain'
 * '<S162>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/postSat Signal'
 * '<S163>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/preSat Signal'
 * '<S164>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Anti-windup/Passthrough'
 * '<S165>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/D Gain/Disabled'
 * '<S166>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Filter/Disabled'
 * '<S167>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Filter ICs/Disabled'
 * '<S168>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/I Gain/Internal Parameters'
 * '<S169>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Ideal P Gain/Passthrough'
 * '<S170>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S171>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Integrator/Discrete'
 * '<S172>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Integrator ICs/Internal IC'
 * '<S173>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S174>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/N Gain/Disabled'
 * '<S175>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/P Copy/Disabled'
 * '<S176>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S177>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Reset Signal/Disabled'
 * '<S178>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Saturation/Passthrough'
 * '<S179>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Saturation Fdbk/Disabled'
 * '<S180>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Sum/Sum_PI'
 * '<S181>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Sum Fdbk/Disabled'
 * '<S182>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Tracking Mode/Disabled'
 * '<S183>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S184>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S185>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S186>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/postSat Signal/Forward_Path'
 * '<S187>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller2/preSat Signal/Forward_Path'
 * '<S188>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Anti-windup'
 * '<S189>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/D Gain'
 * '<S190>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Filter'
 * '<S191>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Filter ICs'
 * '<S192>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/I Gain'
 * '<S193>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Ideal P Gain'
 * '<S194>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Ideal P Gain Fdbk'
 * '<S195>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Integrator'
 * '<S196>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Integrator ICs'
 * '<S197>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/N Copy'
 * '<S198>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/N Gain'
 * '<S199>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/P Copy'
 * '<S200>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Parallel P Gain'
 * '<S201>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Reset Signal'
 * '<S202>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Saturation'
 * '<S203>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Saturation Fdbk'
 * '<S204>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Sum'
 * '<S205>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Sum Fdbk'
 * '<S206>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Tracking Mode'
 * '<S207>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Tracking Mode Sum'
 * '<S208>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Tsamp - Integral'
 * '<S209>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Tsamp - Ngain'
 * '<S210>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/postSat Signal'
 * '<S211>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/preSat Signal'
 * '<S212>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Anti-windup/Passthrough'
 * '<S213>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/D Gain/Disabled'
 * '<S214>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Filter/Disabled'
 * '<S215>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Filter ICs/Disabled'
 * '<S216>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/I Gain/Internal Parameters'
 * '<S217>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Ideal P Gain/Passthrough'
 * '<S218>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S219>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Integrator/Discrete'
 * '<S220>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Integrator ICs/Internal IC'
 * '<S221>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S222>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/N Gain/Disabled'
 * '<S223>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/P Copy/Disabled'
 * '<S224>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S225>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Reset Signal/Disabled'
 * '<S226>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Saturation/Passthrough'
 * '<S227>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Saturation Fdbk/Disabled'
 * '<S228>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Sum/Sum_PI'
 * '<S229>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Sum Fdbk/Disabled'
 * '<S230>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Tracking Mode/Disabled'
 * '<S231>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S232>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Tsamp - Integral/TsSignalSpecification'
 * '<S233>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S234>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/postSat Signal/Forward_Path'
 * '<S235>' : 'BDA_23A/BDA_Control/DQ_FGD/FGD_Control/PID Controller3/preSat Signal/Forward_Path'
 * '<S236>' : 'BDA_23A/BDA_Control/DQ_FGD/Position Generator1/Accumulate'
 * '<S237>' : 'BDA_23A/BDA_Control/DQ_FGD/Position Generator1/Accumulate/Subsystem'
 * '<S238>' : 'BDA_23A/BDA_Control/PI_OGD/Current_loop'
 * '<S239>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K'
 * '<S240>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL'
 * '<S241>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Sine-Cosine Lookup1'
 * '<S242>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem'
 * '<S243>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller'
 * '<S244>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform'
 * '<S245>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/SOGI_II'
 * '<S246>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Anti-windup'
 * '<S247>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/D Gain'
 * '<S248>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Filter'
 * '<S249>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Filter ICs'
 * '<S250>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/I Gain'
 * '<S251>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Ideal P Gain'
 * '<S252>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S253>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Integrator'
 * '<S254>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Integrator ICs'
 * '<S255>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/N Copy'
 * '<S256>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/N Gain'
 * '<S257>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/P Copy'
 * '<S258>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Parallel P Gain'
 * '<S259>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Reset Signal'
 * '<S260>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Saturation'
 * '<S261>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Saturation Fdbk'
 * '<S262>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Sum'
 * '<S263>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Sum Fdbk'
 * '<S264>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Tracking Mode'
 * '<S265>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Tracking Mode Sum'
 * '<S266>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Tsamp - Integral'
 * '<S267>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Tsamp - Ngain'
 * '<S268>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/postSat Signal'
 * '<S269>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/preSat Signal'
 * '<S270>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S271>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S272>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S273>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/D Gain/Disabled'
 * '<S274>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Filter/Disabled'
 * '<S275>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Filter ICs/Disabled'
 * '<S276>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S277>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S278>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S279>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Integrator/Discrete'
 * '<S280>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S281>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/N Copy/Disabled wSignal Specification'
 * '<S282>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/N Gain/Disabled'
 * '<S283>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/P Copy/Disabled'
 * '<S284>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S285>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Reset Signal/Disabled'
 * '<S286>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Saturation/Enabled'
 * '<S287>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S288>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Sum/Sum_PI'
 * '<S289>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S290>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S291>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S292>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Tsamp - Integral/Passthrough'
 * '<S293>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S294>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S295>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S296>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Sine Cosine'
 * '<S297>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Two inputs CRL'
 * '<S298>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Sine Cosine/Sine-Cosine Lookup'
 * '<S299>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Sine Cosine/Sine-Cosine Lookup/Interpolation'
 * '<S300>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp'
 * '<S301>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/Compare To Zero'
 * '<S302>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem'
 * '<S303>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem1'
 * '<S304>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/SOGI_PLL/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S305>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Sine-Cosine Lookup1/Interpolation'
 * '<S306>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Sine-Cosine Lookup1/WrapUp'
 * '<S307>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Sine-Cosine Lookup1/WrapUp/Compare To Zero'
 * '<S308>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Sine-Cosine Lookup1/WrapUp/If Action Subsystem'
 * '<S309>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Sine-Cosine Lookup1/WrapUp/If Action Subsystem1'
 * '<S310>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform'
 * '<S311>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1'
 * '<S312>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/SOGI_II'
 * '<S313>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/SOGI_II1'
 * '<S314>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Sine Cosine'
 * '<S315>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Two inputs CRL'
 * '<S316>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Sine Cosine/Sine-Cosine Lookup'
 * '<S317>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Sine Cosine/Sine-Cosine Lookup/Interpolation'
 * '<S318>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp'
 * '<S319>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/Compare To Zero'
 * '<S320>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem'
 * '<S321>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem1'
 * '<S322>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S323>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Sine Cosine'
 * '<S324>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Two inputs CRL'
 * '<S325>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Sine Cosine/Sine-Cosine Lookup'
 * '<S326>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Sine Cosine/Sine-Cosine Lookup/Interpolation'
 * '<S327>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Sine Cosine/Sine-Cosine Lookup/WrapUp'
 * '<S328>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Sine Cosine/Sine-Cosine Lookup/WrapUp/Compare To Zero'
 * '<S329>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem'
 * '<S330>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Sine Cosine/Sine-Cosine Lookup/WrapUp/If Action Subsystem1'
 * '<S331>' : 'BDA_23A/BDA_Control/PI_OGD/SOGI_PLL_10K/Subsystem/Park Transform1/Two inputs CRL/Switch_Axis'
 */
#endif                                 /* RTW_HEADER_BDA_Control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
