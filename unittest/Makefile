# Copyright (c) 2014, Intel Corporation
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#     * Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of Intel Corporation nor the names of its contributors
#       may be used to endorse or promote products derived from this software
#       without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#CXX=icpc
#LD=icpc

#CXX=/opt/rh/devtoolset-2/root/usr/bin/g++
#LD=/opt/rh/devtoolset-2/root/usr/bin/g++
CXX=g++
LD=g++

RM=rm -rf
OUT_DIR=bin

#if we have built previously then we would have generated dependency for each .o file in a .d
AUTO_DEPS = $(shell find objs/ -type f -name '*.d')
AUTO_DEPS_CPPFLAGS = -MMD -MP

dir_guard= mkdir -p $(@D)

DEBUG_CPPFLAGS = -DDEBUG -O0 -inline-level=0
#VECREPORT_CPPFLAGS = -vec-report7
VECREPORT_CPPFLAGS = -vec-report6 -mP2OPT_hpo_emit_align_diagnostic_for_cpu 

#-opt-report-phase hpo

ICC_CPPFLAGS = $(AUTO_DEPS_CPPFLAGS) \
    -isystem./ \
    -I../include \
    -std=c++0x \
    -g \
    -O3 \
    -Iinclude \
    -debug inline-debug-info \
    -restrict \
    -Wno-deprecated -w2 -Wall -Wremarks -Wcheck -wd191 -wd304 -wd383 \
    -wd444 -wd981 -wd1418 -wd1875 -wd593 -wd177 -wd3218 -wd3346 -wd11074 -wd11076 \
    -Qoption,cpp,--print_include_stack 

GCC_CPPFLAGS = $(AUTO_DEPS_CPPFLAGS) \
    -isystem./ \
    -I../include \
    -std=c++0x \
    -g \
    -O3 \
    -Iinclude \
    -W \
    -Wall \
    -Wcast-align \
    -Wswitch \
    -Wno-unused-parameter \
    -Wreorder \
    -Wdisabled-optimization \
    -Wno-system-headers 

#CPPFLAGS = $(ICC_CPPFLAGS)
CPPFLAGS = $(GCC_CPPFLAGS)


LDFLAGS = -g -lrt



objs/%.o : %.cpp
	 $(dir_guard)
	 $(CXX) -c $(HOST_CPPFLAGS) $(CPPFLAGS) $< -o $@

OBJS = \
	objs/main.o \
        objs/AdaptersWork.o \
        objs/BasicTransformsMatch.o \
        objs/EliminateIdentityFromMultiplication.o \
        objs/InversesMatch.o \
        objs/InverseSxSH.o \
        objs/PartialPrecomputedSxSHxRxT.o \
        objs/PrecomputedSxSHxRxT.o \
        objs/StandardSxSHxRxT.o \
        objs/StandardSxSHxPSxPSHxRxIPSHxIPSxTxP.o \
        objs/TestValues.o \
        objs/TypeChecking.o \


% : $(OUT_DIR)/%

	
TEST_XBB_EXE = testXbb
$(OUT_DIR)/$(TEST_XBB_EXE) : $(OBJS)
	$(dir_guard)
	$(LD) -o $@ $(LDFLAGS) $^


all: $(TEST_XBB_EXE)


clean:
	$(RM) -r objs bin
	
	
-include $(AUTO_DEPS)


.DEFAULT_GOAL=all
