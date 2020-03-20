#FILE(GLOB MAIN_SRC_FILE "*.cpp")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Canny_Z/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ImageFill/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Main/utils)

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/Canny)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/ImageFill)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/ImageFillOnlyOnePoint)

ADD_EXECUTABLE(print100Plane utils/HlwUtils.cpp print100plane.cpp)
TARGET_LINK_LIBRARIES(print100Plane myCanny imageFill imageFillOnlyOnePoint)

#ADD_EXECUTABLE(TestMatlabFillPointID TestMatlabFillPointID.cpp)
#TARGET_LINK_LIBRARIES(TestMatlabFillPointID imageFill)

ADD_EXECUTABLE(EdgeDetectionResultsNormalZ utils/HlwUtils.cpp EdgeDetectionResultsNormalZ.cpp)
TARGET_LINK_LIBRARIES(EdgeDetectionResultsNormalZ CannyZ imageFill imageFillOnlyOnePoint)

ADD_EXECUTABLE(EdgeDetectionResultsNormalX utils/HlwUtils.cpp EdgeDetectionResultsNormalX.cpp)
TARGET_LINK_LIBRARIES(EdgeDetectionResultsNormalX CannyX imageFill imageFillOnlyOnePoint)

ADD_EXECUTABLE(print100PlaneOOP utils/HlwUtils.cpp print100PlaneOOP.cpp)
TARGET_LINK_LIBRARIES(print100PlaneOOP myCanny imageFill imageFillOnlyOnePoint)

ADD_EXECUTABLE(Generate3DMaskDataOOP utils/HlwUtils.cpp Generate3DMaskDataOOP.cpp)
TARGET_LINK_LIBRARIES(Generate3DMaskDataOOP CannyZ imageFill imageFillOnlyOnePoint)
