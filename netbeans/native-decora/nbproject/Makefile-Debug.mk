#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1896763939/SSEBoxBlurPeer.o \
	${OBJECTDIR}/_ext/1896763939/SSEBoxShadowPeer.o \
	${OBJECTDIR}/_ext/1896763939/SSELinearConvolvePeer.o \
	${OBJECTDIR}/_ext/1896763939/SSELinearConvolveShadowPeer.o \
	${OBJECTDIR}/_ext/1896763939/SSEUtils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-decora.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-decora.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-decora.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/1896763939/SSEBoxBlurPeer.o: ../../modules/javafx.graphics/src/main/native-decora/SSEBoxBlurPeer.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/1896763939
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1896763939/SSEBoxBlurPeer.o ../../modules/javafx.graphics/src/main/native-decora/SSEBoxBlurPeer.cc

${OBJECTDIR}/_ext/1896763939/SSEBoxShadowPeer.o: ../../modules/javafx.graphics/src/main/native-decora/SSEBoxShadowPeer.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/1896763939
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1896763939/SSEBoxShadowPeer.o ../../modules/javafx.graphics/src/main/native-decora/SSEBoxShadowPeer.cc

${OBJECTDIR}/_ext/1896763939/SSELinearConvolvePeer.o: ../../modules/javafx.graphics/src/main/native-decora/SSELinearConvolvePeer.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/1896763939
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1896763939/SSELinearConvolvePeer.o ../../modules/javafx.graphics/src/main/native-decora/SSELinearConvolvePeer.cc

${OBJECTDIR}/_ext/1896763939/SSELinearConvolveShadowPeer.o: ../../modules/javafx.graphics/src/main/native-decora/SSELinearConvolveShadowPeer.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/1896763939
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1896763939/SSELinearConvolveShadowPeer.o ../../modules/javafx.graphics/src/main/native-decora/SSELinearConvolveShadowPeer.cc

${OBJECTDIR}/_ext/1896763939/SSEUtils.o: ../../modules/javafx.graphics/src/main/native-decora/SSEUtils.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/1896763939
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1896763939/SSEUtils.o ../../modules/javafx.graphics/src/main/native-decora/SSEUtils.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnative-decora.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
