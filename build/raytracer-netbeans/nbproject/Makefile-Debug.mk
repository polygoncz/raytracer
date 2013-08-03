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
	${OBJECTDIR}/_ext/1640006723/lambert.o \
	${OBJECTDIR}/_ext/1640006723/specular.o \
	${OBJECTDIR}/_ext/1778090205/perspective.o \
	${OBJECTDIR}/_ext/1639979382/camera.o \
	${OBJECTDIR}/_ext/1639979382/film.o \
	${OBJECTDIR}/_ext/1639979382/geometry.o \
	${OBJECTDIR}/_ext/1639979382/integrator.o \
	${OBJECTDIR}/_ext/1639979382/primitive.o \
	${OBJECTDIR}/_ext/1639979382/renderer.o \
	${OBJECTDIR}/_ext/1639979382/scene.o \
	${OBJECTDIR}/_ext/402693072/objimporter.o \
	${OBJECTDIR}/_ext/1125726351/whitted.o \
	${OBJECTDIR}/_ext/484622816/ambient.o \
	${OBJECTDIR}/_ext/484622816/point.o \
	${OBJECTDIR}/_ext/1675404321/matte.o \
	${OBJECTDIR}/_ext/1675404321/phong.o \
	${OBJECTDIR}/_ext/1461044219/raytracer.o \
	${OBJECTDIR}/_ext/683920669/plane.o \
	${OBJECTDIR}/_ext/683920669/sphere.o \
	${OBJECTDIR}/_ext/683920669/trianglemesh.o \
	${OBJECTDIR}/_ext/718975279/imagebuffer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`wx-config --cxxflags` 
CXXFLAGS=`wx-config --cxxflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raytracer-netbeans

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raytracer-netbeans: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raytracer-netbeans ${OBJECTFILES} ${LDLIBSOPTIONS} `wx-config --libs`

${OBJECTDIR}/_ext/1640006723/lambert.o: ../../src/brdf/lambert.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1640006723
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1640006723/lambert.o ../../src/brdf/lambert.cpp

${OBJECTDIR}/_ext/1640006723/specular.o: ../../src/brdf/specular.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1640006723
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1640006723/specular.o ../../src/brdf/specular.cpp

${OBJECTDIR}/_ext/1778090205/perspective.o: ../../src/cameras/perspective.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778090205
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1778090205/perspective.o ../../src/cameras/perspective.cpp

${OBJECTDIR}/_ext/1639979382/camera.o: ../../src/core/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1639979382
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1639979382/camera.o ../../src/core/camera.cpp

${OBJECTDIR}/_ext/1639979382/film.o: ../../src/core/film.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1639979382
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1639979382/film.o ../../src/core/film.cpp

${OBJECTDIR}/_ext/1639979382/geometry.o: ../../src/core/geometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1639979382
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1639979382/geometry.o ../../src/core/geometry.cpp

${OBJECTDIR}/_ext/1639979382/integrator.o: ../../src/core/integrator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1639979382
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1639979382/integrator.o ../../src/core/integrator.cpp

${OBJECTDIR}/_ext/1639979382/primitive.o: ../../src/core/primitive.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1639979382
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1639979382/primitive.o ../../src/core/primitive.cpp

${OBJECTDIR}/_ext/1639979382/renderer.o: ../../src/core/renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1639979382
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1639979382/renderer.o ../../src/core/renderer.cpp

${OBJECTDIR}/_ext/1639979382/scene.o: ../../src/core/scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1639979382
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1639979382/scene.o ../../src/core/scene.cpp

${OBJECTDIR}/_ext/402693072/objimporter.o: ../../src/import/objimporter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/402693072
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/402693072/objimporter.o ../../src/import/objimporter.cpp

${OBJECTDIR}/_ext/1125726351/whitted.o: ../../src/integrators/whitted.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1125726351
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1125726351/whitted.o ../../src/integrators/whitted.cpp

${OBJECTDIR}/_ext/484622816/ambient.o: ../../src/ligths/ambient.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484622816
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/484622816/ambient.o ../../src/ligths/ambient.cpp

${OBJECTDIR}/_ext/484622816/point.o: ../../src/ligths/point.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484622816
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/484622816/point.o ../../src/ligths/point.cpp

${OBJECTDIR}/_ext/1675404321/matte.o: ../../src/materials/matte.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1675404321
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1675404321/matte.o ../../src/materials/matte.cpp

${OBJECTDIR}/_ext/1675404321/phong.o: ../../src/materials/phong.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1675404321
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1675404321/phong.o ../../src/materials/phong.cpp

${OBJECTDIR}/_ext/1461044219/raytracer.o: ../../src/renderers/raytracer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1461044219
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1461044219/raytracer.o ../../src/renderers/raytracer.cpp

${OBJECTDIR}/_ext/683920669/plane.o: ../../src/shapes/plane.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/683920669
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/683920669/plane.o ../../src/shapes/plane.cpp

${OBJECTDIR}/_ext/683920669/sphere.o: ../../src/shapes/sphere.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/683920669
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/683920669/sphere.o ../../src/shapes/sphere.cpp

${OBJECTDIR}/_ext/683920669/trianglemesh.o: ../../src/shapes/trianglemesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/683920669
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/683920669/trianglemesh.o ../../src/shapes/trianglemesh.cpp

${OBJECTDIR}/_ext/718975279/imagebuffer.o: ../../src/wxgui/imagebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/718975279
	${RM} $@.d
	$(COMPILE.cc) -g -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I../../src -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/718975279/imagebuffer.o ../../src/wxgui/imagebuffer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raytracer-netbeans

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
