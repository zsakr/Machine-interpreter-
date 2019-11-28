The SM-275 is a new machine that is in the design phase right now. This project is a simulator for the machine, which will interpret instructions to test its design. The simulator will be written in C, and it should accept instructions in the assembly language of the SM-275, SMA.

# Instruction Set Architecture
  All general-purpose registers and memory locations can store 1 byte.
  All data is of type integer, implemented in two’s complement.
  There are four general-purpose registers R0…R3. Register R0 is also the designated destination of any arithmetic operation.
  There are eight memory locations, M0…M7.
  There are three one-bit flag registers: ZF (zero flag), SF (sign flag), OF (overflow flag). They are set/cleared by all the arithmetic instructions below, as well as the COMP instruction. Note: given that R0 always contains the result of an arithmetic operation, in this case ZF and SF are set solely based on that value.
# The instruction set is as follows:
    READ data, Mk. Input data is stored at Mk. OF set if out of range.
    WRITE Rk|Mk. Value stored at register or memory location is output.
    PRINTS. Print the current state of the machine (see sample output below).
    MOVE Rj|Mj, Rk|Mk. Value stored at first operand copied to second, except both cannot be memory locations. Example: MOVE M2, R1
   ADD, SUB, MULT, DIV, MOD. These are all two-operand instructions. Each operand can be either a register or a memory location, except both cannot be memory locations. The result is always stored in R0. The order of operands for subtraction is “subtract arg1 from arg2” The order of both division operations is “arg1 div/mod arg2”. Examples:

    ADD R2, M1
    MOD M3, R1
    COMP Rj,Rk. sets flags according the table below.
    QUIT. Quit the interpreter.
# Condition
    Zero Flag
    Sign Flag
    Rj. > Rk
    0
    1
    Rj. < Rk
    0
    0
    Rj. == Rk
    1
    0
All instructions and operands are to be case-insensitive. The first operand of all two-operand instructions must be followed by a comma. Rather than detailed messages, the interpreter can just complain of bad input with “???”.


The simulator will be an interpreted (rather than compiled) system, and it should be set up for keyboard rather than file input. At the prompt, the user will enter an instruction in SM-275 Assembly Language (hereafter SMA). The machine will immediately update its state or perform any indicated output. The output of a WRITE instruction will simply be an integer value in decimal and a newline character. The output of a PRINTS statement should look like this:

      33 12 ? 0 ? ? … 43 0 1 0
      -- -- -- -- -- -- -- -- -- --
      R0 R1 R2 R3 M0 M1 M7 ZF SF OF
The ‘?’ character is for display purposes and represents uninitialized registers or memory locations. Note: since registers and memory locations generally will be storing small integers, you won’t store ‘?’ in them. Instead, choose a value outside the range of what the simulated machine can understand (such as 128), and use it to represent ‘?’. Then when displaying, your code will read 128 and print ‘?’. The flag registers are assumed to be initialized to 0.

The interpreter should detect input errors such invalid instructions or instructions with the wrong number of arguments, or unacceptable arguments such as two memory locations where prohibited. However, the only error message is the ever-helpful “???”. It should accept references to registers and memory locations with either upper- or lower-case font, e.g. M2 or m2, and instructions should be case-insensitive as well. It should detect overflow either on input or as the result of calculation and set the overflow flag accordingly. After an overflow caused by calculation, the value of the result register R0 should be set to ‘?’. If an instruction is invoked and one of the arguments is undefined, then the result should be undefined. If there is an error in an instruction, the program should continue allowing the user to try again after seeing the ‘???’ output. 

# Example run of the interepter 

    SM$ prints
    ?   ?  ?  ?  ? ? … ? 0   0  0
    -- -- -- -- -- -- -- -- -- --
    R0 R1 R2 R3 M0 M1 M7 ZF SF OF
    
    SM$ read 11, m0
    SM$ read 17, m1
    SM$ write m0
    11
    SM$ move m1, r1
    SM$ sub r1, m0
    
    SM$ prints
    -6 17 ? ? 11 17 … ?  0  1  0
    -- -- -- -- -- -- -- -- -- --
    R0 R1 R2 R3 M0 M1 M7 ZF SF OF
