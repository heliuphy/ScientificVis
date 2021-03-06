CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
PROJECT(myProj)

# 搜索 matlab vtk 库
FIND_PACKAGE(Matlab REQUIRED)
FIND_PACKAGE(VTK REQUIRED)

# 检查 matlab vtk 库
IF (MATLAB_FOUND)
    message(STATUS "MATLAB Found, MATLAB Project will be compiled.")
ELSE (MATLAB_FOUND)
    MESSAGE("MATLAB not found...nothing will be built.")
ENDIF (MATLAB_FOUND)

IF (VTK_FOUND)
    message(STATUS "VTK Found, VTK Project will be compiled.")
ELSE (VTK_FOUND)
    MESSAGE("VTK not found...nothing will be built.")
ENDIF (VTK_FOUND)


# 设置 vtk matlab 头文件
INCLUDE(${VTK_USE_FILE})
INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Matlab_ROOT_DIR}/extern/include ${Matlab_ROOT_DIR}/simulink/include ${Matlab_ROOT_DIR}/rtw/c/src ${Matlab_ROOT_DIR}/rtw/c/src/ext_mode/common ${Matlab_ROOT_DIR}/rtw/c/ert)


# 设置 matlab 库文件
SET(SYS_LIBS_MATLAB_NEEDED -lm -lstdc++ -lmwippfilter -lmwipp -lmwimfilter -lmwnhood -lmwgetnumcores -lmwtbbhist -lmwcannythresholding_tbb -lmwippreconstruct)
LINK_DIRECTORIES(${Matlab_ROOT_DIR}/bin/maci64)

# 输出相关信息
MESSAGE("project dir is: " ${PROJECT_SOURCE_DIR})
MESSAGE("binary dir is: " ${PROJECT_BINARY_DIR})
MESSAGE("matlab include dir is " ${MATLAB_INCLUDE_DIRS})

# 增加子目录
# 用来编译库

ADD_SUBDIRECTORY(Canny)
ADD_SUBDIRECTORY(ImageFill)

ADD_SUBDIRECTORY(Classes)
ADD_SUBDIRECTORY(Test)
ADD_SUBDIRECTORY(Main)

