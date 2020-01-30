cmake_minimum_required(VERSION 2.8.12)

project(test_memcpy)



add_executable(test_memcpy test_memcpy.cpp test_func.cpp test_func.h)

	set(WARN_GCC
		-pedantic
		-Wall
		-Wextra
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Walloc-zero>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Walloca>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},4.9.9>: -Warray-bounds=2>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},7.9.9>: -Wcast-align=strict>
		-Wcast-qual
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},7.9.9>: -Wcatch-value=3>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},7.9.9>: -Wclass-memaccess>
		-Wcomments
		-Wconditionally-supported
		-Wconversion
		-Wctor-dtor-privacy
		-Wdate-time
		-Wdelete-non-virtual-dtor
		-Wdisabled-optimization
		-Wdouble-promotion
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wduplicated-branches>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},5.9.9>: -Wduplicated-cond>
		-Werror-implicit-function-declaration
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},7.9.9>: -Wextra-semi>
		-Wfloat-conversion
		-Wfloat-equal
		-Wformat
		-Wformat-nonliteral
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wformat-overflow=2>
		-Wformat-security
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},4.9.9>: -Wformat-signedness>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wformat-truncation=2>
		-Wformat-y2k
		-Wformat=2
		-Wframe-larger-than=9000		# size change 4000 to 9000 so RTPreemptEC.cpp larger than 4000 bytes.
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wimplicit-fallthrough=3>
		-Winit-self
		-Winline
		-Winvalid-pch
		-Wlogical-op
		-Wmissing-declarations
		-Wmissing-format-attribute
		-Wmissing-include-dirs
		-Wmultichar
		-Wnoexcept
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wnoexcept-type>
		-Wnon-virtual-dtor
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},5.9.9>: -Wnull-dereference>
		-Wold-style-cast
		-Woverlength-strings
		-Woverloaded-virtual
		-Wpacked
		-Wpedantic
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},5.9.9>: -Wplacement-new=1>
		-Wpointer-arith
		-Wredundant-decls
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wregister>
		-Wreorder
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},5.9.9>: -Wscalar-storage-order>
		-Wshadow
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wshadow-compatible-local>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wshadow-local>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wshadow=compatible-local>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wshadow=global>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wshadow=local>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},5.9.9>: -Wshift-overflow=1>
		-Wsign-conversion
		-Wsign-promo
		-Wstack-protector
		-Wstrict-null-sentinel
		-Wstrict-overflow=5
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},6.9.9>: -Wstringop-overflow=4>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},7.9.9>: -Wsuggest-attribute=cold>
		-Wsuggest-attribute=format
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},7.9.9>: -Wsuggest-attribute=malloc>
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},4.9.9>: -Wsuggest-override>
		-Wswitch-default
		-Wswitch-enum
		-Wsynth
		-Wtrampolines
		-Wundef
		-Wunreachable-code
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},5.9.9>: -Wunused-const-variable=2>
		-Wunused-macros
		-Wuseless-cast
		-Wvariadic-macros
		-Wvector-operation-performance
		-Wwrite-strings
		-Wzero-as-null-pointer-constant
		# exclude rule
		-Wno-padded)

set(WARN_GCC_RELEASE
		${WARN_GCC}
		-Wno-cast-qual
		-Wno-conditionally-supported
		-Wno-conversion
		-Wno-missing-declarations
		-Wno-old-style-cast
		-Wno-overloaded-virtual
		-Wno-shadow
		-Wno-sign-compare
		-Wno-sign-conversion
		-Wno-strict-overflow
		-Wno-suggest-attribute=format
		$<$<VERSION_GREATER:${CMAKE_CXX_COMPILER_VERSION},7.9.9>: -Wno-suggest-attribute=malloc>
		-Wno-unused-macros
		-Wno-unused-result
		-Wno-useless-cast
		)
target_compile_options(test_memcpy PRIVATE
		$<$<CXX_COMPILER_ID:GNU>:
			$<$<CONFIG:Debug>:-O2 ${WARN_GCC}> # Some options need O2.
			$<$<CONFIG:Release>:-Werror ${WARN_GCC_RELEASE}>
			$<$<CONFIG:RelWithDebInfo>: ${WARN_GCC_RELEASE}>
			$<$<CONFIG:MinSizeRel>: ${WARN_GCC_RELEASE}>
		>
	)


