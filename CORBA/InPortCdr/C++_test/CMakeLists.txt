cmake_minimum_required(VERSION 2.8.12)

project(InPortCdrTest)

find_package(OpenRTM REQUIRED)

if(${OPENRTM_VERSION_MAJOR} LESS 2)
  set(OPENRTM_CFLAGS ${OPENRTM_CFLAGS} ${OMNIORB_CFLAGS})
  set(OPENRTM_INCLUDE_DIRS ${OPENRTM_INCLUDE_DIRS} ${OMNIORB_INCLUDE_DIRS})
  set(OPENRTM_LIBRARY_DIRS ${OPENRTM_LIBRARY_DIRS} ${OMNIORB_LIBRARY_DIRS})

  if (DEFINED OPENRTM_INCLUDE_DIRS)
    string(REGEX REPLACE "-I" ";"
      OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
    string(REGEX REPLACE " ;" ";"
      OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
  endif (DEFINED OPENRTM_INCLUDE_DIRS)

  if (DEFINED OPENRTM_LIBRARY_DIRS)
    string(REGEX REPLACE "-L" ";"
      OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
    string(REGEX REPLACE " ;" ";"
      OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
  endif (DEFINED OPENRTM_LIBRARY_DIRS)

  if (DEFINED OPENRTM_LIBRARIES)
    string(REGEX REPLACE "-l" ";"
      OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
    string(REGEX REPLACE " ;" ";"
      OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
  endif (DEFINED OPENRTM_LIBRARIES)
endif()

include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${PROJECT_BINARY_DIR})
link_directories(${OPENRTM_LIBRARY_DIRS})
add_definitions(${OPENRTM_CFLAGS})



add_executable(InPortCdrTestIn CORBATestIn.cpp InPortCdr_impl.cpp testDataPortSkel.cpp testDataPortSkel.h)
target_link_libraries(InPortCdrTestIn ${OPENRTM_LIBRARIES})
add_executable(InPortCdrTestOut CORBATestOut.cpp testDataPortStub.cpp testDataPortStub.h)
target_link_libraries(InPortCdrTestOut ${OPENRTM_LIBRARIES})
