#FILE(GLOB MAIN_SRC_FILE "*.cpp")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Canny/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ImageFill/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/CannyAndFill/utils)

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/Canny)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/ImageFill)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/ImageFillOnlyOnePoint)

ADD_EXECUTABLE(print100Plane utils/HlwUtils.cpp print100plane.cpp)
TARGET_LINK_LIBRARIES(print100Plane myCanny imageFill imageFillOnlyOnePoint)

#ADD_EXECUTABLE(TestMatlabFillPointID TestMatlabFillPointID.cpp)
#TARGET_LINK_LIBRARIES(TestMatlabFillPointID imageFill)

ADD_EXECUTABLE(creat3dcanny utils/HlwUtils.cpp creat3dcanny.cpp)
TARGET_LINK_LIBRARIES(creat3dcanny myCanny imageFill imageFillOnlyOnePoint)
