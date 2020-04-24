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
        CircleDelete
        AreaDelete
        SliceTypeDetector
        )

ADD_EXECUTABLE(generate3d generate3dByFIrstMethod.cpp)
TARGET_LINK_LIBRARIES(generate3d ${LIBS_NEEDED})

ADD_EXECUTABLE(generateSlices generate400SlicesByFIrstMethod.cpp)
TARGET_LINK_LIBRARIES(generateSlices ${LIBS_NEEDED})

ADD_EXECUTABLE(generateSlices2nd generate400SlicesBy2ndMethod.cpp)
TARGET_LINK_LIBRARIES(generateSlices2nd ${LIBS_NEEDED})

ADD_EXECUTABLE(generate400Canny generate400Canny.cpp)
TARGET_LINK_LIBRARIES(generate400Canny ${LIBS_NEEDED})

ADD_EXECUTABLE(generate400ImageFill generate400ImageFill.cpp)
TARGET_LINK_LIBRARIES(generate400ImageFill ${LIBS_NEEDED})

ADD_EXECUTABLE(generate3dBy2ndMethod generate3dBy2ndMethod.cpp)
TARGET_LINK_LIBRARIES(generate3dBy2ndMethod ${LIBS_NEEDED})

ADD_EXECUTABLE(testFourSpecialZIndexes testFourSpecialZIndexes.cpp)
TARGET_LINK_LIBRARIES(testFourSpecialZIndexes ${LIBS_NEEDED})
