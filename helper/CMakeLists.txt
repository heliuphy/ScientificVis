cmake_minimum_required(VERSION 3.3...3.12 FATAL_ERROR)

PROJECT(MainProject)
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

add_executable(ImageAccumulateGreyscale ImageAccumulateGreyscale)
target_link_libraries(ImageAccumulateGreyscale ${VTK_LIBRARIES})

add_executable(PseudoVolumeRendering PseudoVolumeRendering)
target_link_libraries(PseudoVolumeRendering ${VTK_LIBRARIES})

add_executable(BinaryByThreshold BinaryByThreshold)
target_link_libraries(BinaryByThreshold ${VTK_LIBRARIES})

add_executable(BinaryByEightNeighbor BinaryByEightNeighbor)
target_link_libraries(BinaryByEightNeighbor ${VTK_LIBRARIES})

add_executable(PrintLine PrintLine)
target_link_libraries(PrintLine ${VTK_LIBRARIES})

add_executable(FindBinaryInnerCircle FindBinaryInnerCircle)
target_link_libraries(FindBinaryInnerCircle ${VTK_LIBRARIES})

add_executable(MetaImageToPNG MetaImageToPNG)
target_link_libraries(MetaImageToPNG ${VTK_LIBRARIES})
