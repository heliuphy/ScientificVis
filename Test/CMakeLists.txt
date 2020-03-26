INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Canny/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ImageFill/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Classes)

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/Canny)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/ImageFill)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/Classes)

SET(CLASSES_NEEDED_LIBS
        Canny
        ImageFill
        hlwAlgorithms
        hlwPlaneAlgorithms
        hlwVolumeAlgorithms
        PlaneNeighborGrowing
        CannyDetect
        hlwImageFill
        hlwImageMath
        hlwImageSlice
        CircleDelete)


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Classes)

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/Classes)

ADD_EXECUTABLE(PlaneNeighborGrowingTest PlaneNeighborGrowingTest.cpp)
TARGET_LINK_LIBRARIES(PlaneNeighborGrowingTest ${CLASSES_NEEDED_LIBS})

ADD_EXECUTABLE(CannyDetectTest CannyDetectTest.cpp)
TARGET_LINK_LIBRARIES(CannyDetectTest ${CLASSES_NEEDED_LIBS})

ADD_EXECUTABLE(hlwImageFillTest hlwImageFillTest.cpp)
TARGET_LINK_LIBRARIES(hlwImageFillTest ${CLASSES_NEEDED_LIBS})

ADD_EXECUTABLE(hlwImageMathTest hlwImageMathTest.cpp)
TARGET_LINK_LIBRARIES(hlwImageMathTest ${CLASSES_NEEDED_LIBS})

ADD_EXECUTABLE(hlwImageSliceTest hlwImageSliceTest.cpp)
TARGET_LINK_LIBRARIES(hlwImageSliceTest ${CLASSES_NEEDED_LIBS})

ADD_EXECUTABLE(BreakPointConnectedTest BreakPointConnectedTest.cpp)
TARGET_LINK_LIBRARIES(BreakPointConnectedTest ${CLASSES_NEEDED_LIBS})

ADD_EXECUTABLE(DeleteCircleTest DeleteCircleTest.cpp)
TARGET_LINK_LIBRARIES(DeleteCircleTest ${CLASSES_NEEDED_LIBS})
