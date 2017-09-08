cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(Hotline_Scunthorpe)
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
foreach (config ${CMAKE_CONFIGURATION_TYPES})
  string (TOUPPER ${config} config)
  set_target_properties(${_project} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}"
    ARCHIVE_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}"
    LIBRARY_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}"
    #PDB_OUTPUT_DIRECTORY_${config} ${sym_path}
    VS_INTERMEDIATE_DIRECTORY_${config} "temp"
  )
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( VS_INTERMEDIATE_DIRECTORY_${config} "temp/${config}")
  link_directories("${OUTPUT_DIRECTORY}/${config}")
endforeach ()

include(DownloadProject.cmake)

download_project(PROJ SFML
  GIT_REPOSITORY      https://github.com/SFML/SFML
  GIT_TAG             b7be4b2
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${SFML_SOURCE_DIR} ${SFML_BINARY_DIR})
include_directories("${SFML_SOURCE_DIR}/include")
link_directories(${SFML_BINARY_DIR}/lib)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
add_executable(Hotline_Scunthorpe_main ${SOURCE_FILES})

#copy General resources to build post build script
add_custom_command(TARGET Hotline_Scunthorpe_main POST_BUILD  
  COMMAND ${CMAKE_COMMAND} -E copy_directory  "${PROJECT_SOURCE_DIR}/res" $<TARGET_FILE_DIR:Hotline_Scunthorpe_main>/res)

if(${MSVC})
  #set outDir as debugging directory
  #This doesn't work yet?
  #set_target_properties(Hotline_Scunthorpe_main PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)")
  
  file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/Hotline_Scunthorpe_main.vcxproj.user" 
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>
    <Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">
      <LocalDebuggerWorkingDirectory>$(TargetDir)</LocalDebuggerWorkingDirectory>
      <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">
      <LocalDebuggerWorkingDirectory>$(TargetDir)</LocalDebuggerWorkingDirectory>
      <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
  </Project>")
		
  target_compile_options(Hotline_Scunthorpe_main PUBLIC /MP)

else()

endif()
target_link_libraries(Hotline_Scunthorpe_main 
  optimized sfml-graphics debug sfml-graphics-d 
  optimized sfml-audio debug sfml-audio-d 
  optimized sfml-window debug sfml-window-d 
  optimized sfml-system debug sfml-system-d 
  optimized sfml-graphics debug sfml-graphics-d
 )

add_dependencies(Hotline_Scunthorpe_main sfml-graphics)