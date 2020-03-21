#FILE(GLOB MAIN_SRC_FILE "*.cpp")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Canny/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ImageFill/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Main/utils)

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/Canny)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/ImageFill)

ADD_EXECUTABLE(print100Plane utils/HlwUtils.cpp print100plane.cpp)
TARGET_LINK_LIBRARIES(print100Plane hlwCanny hlwImageFill)


ADD_EXECUTABLE(print100PlaneOOP utils/HlwUtils.cpp print100PlaneOOP.cpp)
TARGET_LINK_LIBRARIES(print100PlaneOOP hlwCanny hlwImageFill)


ADD_EXECUTABLE(Generate3DMaskDataOOP utils/HlwUtils.cpp Generate3DMaskDataOOP.cpp)
TARGET_LINK_LIBRARIES(Generate3DMaskDataOOP hlwCanny hlwImageFill)

ADD_EXECUTABLE(InfArrayEg utils/HlwUtils.cpp InfArrayEg.cpp)
TARGET_LINK_LIBRARIES(InfArrayEg hlwCanny hlwImageFill)
