/*
 * Copyright (C) 2011-2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "MacroAssembler.h"
#include <wtf/PrintStream.h>

namespace JSC {

typedef MacroAssembler::FPRegisterID FPRReg;
static constexpr FPRReg InvalidFPRReg { FPRReg::InvalidFPRReg };

#if ENABLE(JIT)

#if CPU(X86) || CPU(X86_64)

class FPRInfo {
public:
    typedef FPRReg RegisterType;
    static const unsigned numberOfRegisters = 6;
    static const unsigned numberOfArgumentRegisters = is64Bit() ? 8 : 0;

    // Temporary registers.
    static const FPRReg fpRegT0 = X86Registers::xmm0;
    static const FPRReg fpRegT1 = X86Registers::xmm1;
    static const FPRReg fpRegT2 = X86Registers::xmm2;
    static const FPRReg fpRegT3 = X86Registers::xmm3;
    static const FPRReg fpRegT4 = X86Registers::xmm4;
    static const FPRReg fpRegT5 = X86Registers::xmm5;
#if CPU(X86_64)
    // Only X86_64 passes aguments in xmm registers
    static const FPRReg argumentFPR0 = X86Registers::xmm0; // fpRegT0
    static const FPRReg argumentFPR1 = X86Registers::xmm1; // fpRegT1
    static const FPRReg argumentFPR2 = X86Registers::xmm2; // fpRegT2
    static const FPRReg argumentFPR3 = X86Registers::xmm3; // fpRegT3
    static const FPRReg argumentFPR4 = X86Registers::xmm4; // fpRegT4
    static const FPRReg argumentFPR5 = X86Registers::xmm5; // fpRegT5
    static const FPRReg argumentFPR6 = X86Registers::xmm6;
    static const FPRReg argumentFPR7 = X86Registers::xmm7;
#endif
    // On X86 the return will actually be on the x87 stack,
    // so we'll copy to xmm0 for sanity!
    static const FPRReg returnValueFPR = X86Registers::xmm0; // fpRegT0

    // FPRReg mapping is direct, the machine regsiter numbers can
    // be used directly as indices into the FPR RegisterBank.
    COMPILE_ASSERT(X86Registers::xmm0 == 0, xmm0_is_0);
    COMPILE_ASSERT(X86Registers::xmm1 == 1, xmm1_is_1);
    COMPILE_ASSERT(X86Registers::xmm2 == 2, xmm2_is_2);
    COMPILE_ASSERT(X86Registers::xmm3 == 3, xmm3_is_3);
    COMPILE_ASSERT(X86Registers::xmm4 == 4, xmm4_is_4);
    COMPILE_ASSERT(X86Registers::xmm5 == 5, xmm5_is_5);
    static FPRReg toRegister(unsigned index)
    {
        return (FPRReg)index;
    }
    static unsigned toIndex(FPRReg reg)
    {
        unsigned result = (unsigned)reg;
        if (result >= numberOfRegisters)
            return InvalidIndex;
        return result;
    }

    static FPRReg toArgumentRegister(unsigned index)
    {
        return (FPRReg)index;
    }

    static const char* debugName(FPRReg reg)
    {
        ASSERT(reg != InvalidFPRReg);
        return MacroAssembler::fprName(reg);
    }

    static const unsigned InvalidIndex = 0xffffffff;
};

#endif // CPU(X86) || CPU(X86_64)

#if CPU(ARM)

class FPRInfo {
public:
    typedef FPRReg RegisterType;
    static const unsigned numberOfRegisters = 6;

#if CPU(ARM_HARDFP)
    static const unsigned numberOfArgumentRegisters = 8;
#else
    static const unsigned numberOfArgumentRegisters = 0;
#endif

    // Temporary registers.
    // d7 is use by the MacroAssembler as fpTempRegister.
    static const FPRReg fpRegT0 = ARMRegisters::d0;
    static const FPRReg fpRegT1 = ARMRegisters::d1;
    static const FPRReg fpRegT2 = ARMRegisters::d2;
    static const FPRReg fpRegT3 = ARMRegisters::d3;
    static const FPRReg fpRegT4 = ARMRegisters::d4;
    static const FPRReg fpRegT5 = ARMRegisters::d5;
    // ARMv7 doesn't pass arguments in fp registers. The return
    // value is also actually in integer registers, for now
    // we'll return in d0 for simplicity.
    static const FPRReg returnValueFPR = ARMRegisters::d0; // fpRegT0

#if CPU(ARM_HARDFP)
    static const FPRReg argumentFPR0 = ARMRegisters::d0; // fpRegT0
    static const FPRReg argumentFPR1 = ARMRegisters::d1; // fpRegT1
#endif

    // FPRReg mapping is direct, the machine regsiter numbers can
    // be used directly as indices into the FPR RegisterBank.
    COMPILE_ASSERT(ARMRegisters::d0 == 0, d0_is_0);
    COMPILE_ASSERT(ARMRegisters::d1 == 1, d1_is_1);
    COMPILE_ASSERT(ARMRegisters::d2 == 2, d2_is_2);
    COMPILE_ASSERT(ARMRegisters::d3 == 3, d3_is_3);
    COMPILE_ASSERT(ARMRegisters::d4 == 4, d4_is_4);
    COMPILE_ASSERT(ARMRegisters::d5 == 5, d5_is_5);
    static FPRReg toRegister(unsigned index)
    {
        return (FPRReg)index;
    }
    static unsigned toIndex(FPRReg reg)
    {
        return (unsigned)reg;
    }

#if CPU(ARM_HARDFP)
    static FPRReg toArgumentRegister(unsigned index)
    {
        ASSERT(index < numberOfArgumentRegisters);
        return static_cast<FPRReg>(index);
    }
#endif

    static const char* debugName(FPRReg reg)
    {
        ASSERT(reg != InvalidFPRReg);
        return MacroAssembler::fprName(reg);
    }

    static const unsigned InvalidIndex = 0xffffffff;
};

#endif // CPU(ARM)

#if CPU(ARM64)

class FPRInfo {
public:
    typedef FPRReg RegisterType;
    static const unsigned numberOfRegisters = 23;
    static const unsigned numberOfArgumentRegisters = 8;

    // Temporary registers.
    // q8-q15 are callee saved, q31 is use by the MacroAssembler as fpTempRegister.
    static const FPRReg fpRegT0 = ARM64Registers::q0;
    static const FPRReg fpRegT1 = ARM64Registers::q1;
    static const FPRReg fpRegT2 = ARM64Registers::q2;
    static const FPRReg fpRegT3 = ARM64Registers::q3;
    static const FPRReg fpRegT4 = ARM64Registers::q4;
    static const FPRReg fpRegT5 = ARM64Registers::q5;
    static const FPRReg fpRegT6 = ARM64Registers::q6;
    static const FPRReg fpRegT7 = ARM64Registers::q7;
    static const FPRReg fpRegT8 = ARM64Registers::q16;
    static const FPRReg fpRegT9 = ARM64Registers::q17;
    static const FPRReg fpRegT10 = ARM64Registers::q18;
    static const FPRReg fpRegT11 = ARM64Registers::q19;
    static const FPRReg fpRegT12 = ARM64Registers::q20;
    static const FPRReg fpRegT13 = ARM64Registers::q21;
    static const FPRReg fpRegT14 = ARM64Registers::q22;
    static const FPRReg fpRegT15 = ARM64Registers::q23;
    static const FPRReg fpRegT16 = ARM64Registers::q24;
    static const FPRReg fpRegT17 = ARM64Registers::q25;
    static const FPRReg fpRegT18 = ARM64Registers::q26;
    static const FPRReg fpRegT19 = ARM64Registers::q27;
    static const FPRReg fpRegT20 = ARM64Registers::q28;
    static const FPRReg fpRegT21 = ARM64Registers::q29;
    static const FPRReg fpRegT22 = ARM64Registers::q30;
    static const FPRReg fpRegCS0 = ARM64Registers::q8;
    static const FPRReg fpRegCS1 = ARM64Registers::q9;
    static const FPRReg fpRegCS2 = ARM64Registers::q10;
    static const FPRReg fpRegCS3 = ARM64Registers::q11;
    static const FPRReg fpRegCS4 = ARM64Registers::q12;
    static const FPRReg fpRegCS5 = ARM64Registers::q13;
    static const FPRReg fpRegCS6 = ARM64Registers::q14;
    static const FPRReg fpRegCS7 = ARM64Registers::q15;

    static const FPRReg argumentFPR0 = ARM64Registers::q0; // fpRegT0
    static const FPRReg argumentFPR1 = ARM64Registers::q1; // fpRegT1
    static const FPRReg argumentFPR2 = ARM64Registers::q2; // fpRegT2
    static const FPRReg argumentFPR3 = ARM64Registers::q3; // fpRegT3
    static const FPRReg argumentFPR4 = ARM64Registers::q4; // fpRegT4
    static const FPRReg argumentFPR5 = ARM64Registers::q5; // fpRegT5
    static const FPRReg argumentFPR6 = ARM64Registers::q6; // fpRegT6
    static const FPRReg argumentFPR7 = ARM64Registers::q7; // fpRegT7

    static const FPRReg returnValueFPR = ARM64Registers::q0; // fpRegT0

    static FPRReg toRegister(unsigned index)
    {
        ASSERT(index < numberOfRegisters);
        static const FPRReg registerForIndex[numberOfRegisters] = {
            fpRegT0, fpRegT1, fpRegT2, fpRegT3, fpRegT4, fpRegT5, fpRegT6, fpRegT7,
            fpRegT8, fpRegT9, fpRegT10, fpRegT11, fpRegT12, fpRegT13, fpRegT14, fpRegT15,
            fpRegT16, fpRegT17, fpRegT18, fpRegT19, fpRegT20, fpRegT21, fpRegT22
        };
        return registerForIndex[index];
    }

    static unsigned toIndex(FPRReg reg)
    {
        ASSERT(reg != InvalidFPRReg);
        ASSERT(static_cast<int>(reg) < 32);
        static const unsigned indexForRegister[32] = {
            0, 1, 2, 3, 4, 5, 6, 7,
            InvalidIndex, InvalidIndex, InvalidIndex, InvalidIndex, InvalidIndex, InvalidIndex, InvalidIndex, InvalidIndex,
            8, 9, 10, 11, 12, 13, 14, 15,
            16, 17, 18, 19, 20, 21, 22, InvalidIndex
        };
        unsigned result = indexForRegister[reg];
        return result;
    }

    static FPRReg toArgumentRegister(unsigned index)
    {
        ASSERT(index < 8);
        return static_cast<FPRReg>(index);
    }

    static const char* debugName(FPRReg reg)
    {
        ASSERT(reg != InvalidFPRReg);
        return MacroAssembler::fprName(reg);
    }

    static const unsigned InvalidIndex = 0xffffffff;
};

#endif // CPU(ARM64)

#if CPU(MIPS)

class FPRInfo {
public:
    typedef FPRReg RegisterType;
    static const unsigned numberOfRegisters = 7;
    static const unsigned numberOfArgumentRegisters = 2;

    // Temporary registers.
    static const FPRReg fpRegT0 = MIPSRegisters::f0;
    static const FPRReg fpRegT1 = MIPSRegisters::f2;
    static const FPRReg fpRegT2 = MIPSRegisters::f4;
    static const FPRReg fpRegT3 = MIPSRegisters::f6;
    static const FPRReg fpRegT4 = MIPSRegisters::f8;
    static const FPRReg fpRegT5 = MIPSRegisters::f10;
    static const FPRReg fpRegT6 = MIPSRegisters::f18;

    static const FPRReg returnValueFPR = MIPSRegisters::f0;

    static const FPRReg argumentFPR0 = MIPSRegisters::f12;
    static const FPRReg argumentFPR1 = MIPSRegisters::f14;

    static FPRReg toRegister(unsigned index)
    {
        static const FPRReg registerForIndex[numberOfRegisters] = {
            fpRegT0, fpRegT1, fpRegT2, fpRegT3, fpRegT4, fpRegT5, fpRegT6 };

        ASSERT(index < numberOfRegisters);
        return registerForIndex[index];
    }

    static FPRReg toArgumentRegister(unsigned index)
    {
        ASSERT(index < numberOfArgumentRegisters);
        static const FPRReg indexForRegister[2] = {
            argumentFPR0, argumentFPR1
        };
        return indexForRegister[index];
    }

    static unsigned toIndex(FPRReg reg)
    {
        ASSERT(reg != InvalidFPRReg);
        ASSERT(reg < 20);
        static const unsigned indexForRegister[20] = {
            0, InvalidIndex, 1, InvalidIndex,
            2, InvalidIndex, 3, InvalidIndex,
            4, InvalidIndex, 5, InvalidIndex,
            InvalidIndex, InvalidIndex, InvalidIndex, InvalidIndex,
            InvalidIndex, InvalidIndex, 6, InvalidIndex,
        };
        unsigned result = indexForRegister[reg];
        return result;
    }

    static const char* debugName(FPRReg reg)
    {
        ASSERT(reg != InvalidFPRReg);
        return MacroAssembler::fprName(reg);
    }

    static const unsigned InvalidIndex = 0xffffffff;
};

#endif // CPU(MIPS)

// We use this hack to get the FPRInfo from the FPRReg type in templates because our code is bad and we should feel bad..
constexpr FPRInfo toInfoFromReg(FPRReg) { return FPRInfo(); }

#endif // ENABLE(JIT)

} // namespace JSC

namespace WTF {

inline void printInternal(PrintStream& out, JSC::FPRReg reg)
{
#if ENABLE(JIT)
    out.print("%", JSC::FPRInfo::debugName(reg));
#else
    out.printf("%%fr%d", reg);
#endif
}

} // namespace WTF
