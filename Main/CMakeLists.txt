INCLUDE_DIRECTORIES(./include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Classes)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Canny/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ImageFill/include)

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/Classes)

SET(LIBS_NEEDED
        hlwAlgorithms
        hlwPlaneAlgorithms
        hlwVolumeAlgorithms
        PlaneNeighborGrowing
        CannyDetect
        hlwImageFill
        hlwImageMath
        hlwImageSlice
        )

ADD_EXECUTABLE(generate3d generate3d.cpp)
TARGET_LINK_LIBRARIES(generate3d ${LIBS_NEEDED})
