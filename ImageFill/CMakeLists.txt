INCLUDE_DIRECTORIES(./include)

FILE(GLOB IMAGE_FILL_SRC "./src/*.cpp")
ADD_LIBRARY(ImageFill STATIC ${IMAGE_FILL_SRC})
TARGET_LINK_LIBRARIES(ImageFill ${SYS_LIBS_MATLAB_NEEDED} ${MATLAB_LIBRARIES} ${VTK_LIBRARIES})


# test
INCLUDE_DIRECTORIES(./test)
ADD_EXECUTABLE(ImageFillTest ./test/main.cpp)
TARGET_LINK_LIBRARIES(ImageFillTest ImageFill)
