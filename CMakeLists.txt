cmake_minimum_required(VERSION 3.3...3.12 FATAL_ERROR)

PROJECT (MainProject)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(CannyEdgeDetector CannyEdgeDetector)
target_link_libraries(CannyEdgeDetector ${VTK_LIBRARIES})

add_executable(LaplacianExample LaplacianExample)
target_link_libraries(LaplacianExample ${VTK_LIBRARIES})

add_executable(ImageGradientExample ImageGradientExample)
target_link_libraries(ImageGradientExample ${VTK_LIBRARIES})

add_executable(ResliceAndExportFile ResliceAndExportFile)
target_link_libraries(ResliceAndExportFile ${VTK_LIBRARIES})

add_executable(ImageGradientMagnitude ImageGradientMagnitude)
target_link_libraries(ImageGradientMagnitude ${VTK_LIBRARIES})
