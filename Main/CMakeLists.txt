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
        DrawCircles
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

ADD_EXECUTABLE(generate400SlicesBy2ndMethodPlus generate400SlicesBy2ndMethodPlus.cpp)
TARGET_LINK_LIBRARIES(generate400SlicesBy2ndMethodPlus ${LIBS_NEEDED})

ADD_EXECUTABLE(generate3dBy2ndMethodPlus generate3dBy2ndMethodPlus.cpp)
TARGET_LINK_LIBRARIES(generate3dBy2ndMethodPlus ${LIBS_NEEDED})

ADD_EXECUTABLE(SecondGenerate400Slices SecondGenerate400Slices.cpp)
TARGET_LINK_LIBRARIES(SecondGenerate400Slices ${LIBS_NEEDED})

ADD_EXECUTABLE(SecondGenerate3d SecondGenerate3d.cpp)
TARGET_LINK_LIBRARIES(SecondGenerate3d ${LIBS_NEEDED})

ADD_EXECUTABLE(SecondGenerate3d_Time_900 SecondGenerate3d_Time_900.cpp)
TARGET_LINK_LIBRARIES(SecondGenerate3d_Time_900 ${LIBS_NEEDED})

ADD_EXECUTABLE(generate400CannyOnlyReserveCircle generate400CannyOnlyReserveCircle.cpp)
TARGET_LINK_LIBRARIES(generate400CannyOnlyReserveCircle ${LIBS_NEEDED})
