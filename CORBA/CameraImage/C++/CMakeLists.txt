cmake_minimum_required(VERSION 2.8.12)

project(CORBATest)

find_package(OpenRTM REQUIRED)

if(${OPENRTM_VERSION_MAJOR} LESS 2)
  set(OPENRTM_CFLAGS ${OPENRTM_CFLAGS} ${OMNIORB_CFLAGS})
  set(OPENRTM_INCLUDE_DIRS ${OPENRTM_INCLUDE_DIRS} ${OMNIORB_INCLUDE_DIRS})
  set(OPENRTM_LIBRARY_DIRS ${OPENRTM_LIBRARY_DIRS} ${OMNIORB_LIBRARY_DIRS})
endif()

include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${PROJECT_BINARY_DIR})
link_directories(${OPENRTM_LIBRARY_DIRS})
add_definitions(${OPENRTM_CFLAGS})




set(idls ${CMAKE_CURRENT_SOURCE_DIR}/testService.idl)

macro(_IDL_OUTPUTS _idl _dir _result)
    set(${_result} ${_dir}/${_idl}Skel.cpp ${_dir}/${_idl}Skel.h)
endmacro(_IDL_OUTPUTS)

macro(_COMPILE_IDL _idl_file)
    if(NOT WIN32)
        execute_process(COMMAND rtm-config --prefix OUTPUT_VARIABLE OPENRTM_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(COMMAND rtm-config --idlflags OUTPUT_VARIABLE OPENRTM_IDLFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE)
        separate_arguments(OPENRTM_IDLFLAGS)
        execute_process(COMMAND rtm-config --idlc OUTPUT_VARIABLE OPENRTM_IDLC
        OUTPUT_STRIP_TRAILING_WHITESPACE)
        set(_rtm_skelwrapper_command "rtm-skelwrapper")
    else(NOT WIN32)
        set(_rtm_skelwrapper_command "rtm-skelwrapper.py")
    endif(NOT WIN32)
    get_filename_component(_idl ${_idl_file} NAME_WE)
    set(_idl_srcs_var ${_idl}_SRCS)
    _IDL_OUTPUTS(${_idl} ${CMAKE_CURRENT_BINARY_DIR} ${_idl_srcs_var})

    add_custom_command(OUTPUT ${${_idl_srcs_var}}
        COMMAND python ${OPENRTM_DIR}/bin/${_rtm_skelwrapper_command} --include-dir= --skel-suffix=Skel --stub-suffix=Stub --idl-file=${_idl}.idl
        COMMAND ${OPENRTM_IDLC} ${OPENRTM_IDLFLAGS} ${_idl_file}
        WORKING_DIRECTORY ${CURRENT_BINARY_DIR}
        DEPENDS ${_idl_file}
        COMMENT "Compiling ${_idl_file}" VERBATIM)
    add_custom_target(${_idl}_TGT DEPENDS ${${_idl_srcs_var}})
    set(ALL_IDL_SRCS ${ALL_IDL_SRCS} ${${_idl_srcs_var}})
    if(NOT TARGET ALL_IDL_TGT)
        add_custom_target(ALL_IDL_TGT)
    endif(NOT TARGET ALL_IDL_TGT)
    add_dependencies(ALL_IDL_TGT ${_idl}_TGT)
endmacro(_COMPILE_IDL)

macro(OPENRTM_COMPILE_IDL_FILES)
    foreach(idl ${ARGN})
        _COMPILE_IDL(${idl})
    endforeach(idl)
endmacro(OPENRTM_COMPILE_IDL_FILES)


OPENRTM_COMPILE_IDL_FILES(${idls})




set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
if(NOT TARGET ALL_IDL_TGT)
 add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)




add_executable(CORBATestIn CORBATestIn.cpp CORBASVC.cpp ${ALL_IDL_SRCS})
target_link_libraries(CORBATestIn ${OPENRTM_LIBRARIES})
add_executable(CORBATestOut CORBATestOut.cpp ${ALL_IDL_SRCS})
target_link_libraries(CORBATestOut ${OPENRTM_LIBRARIES})

add_dependencies(CORBATestIn ALL_IDL_TGT)
add_dependencies(CORBATestOut ALL_IDL_TGT)