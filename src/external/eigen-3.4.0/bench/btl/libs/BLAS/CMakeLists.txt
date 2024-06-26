
find_package(ATLAS)
if (ATLAS_FOUND)
  btl_add_bench(btl_atlas main.cpp)
  if(BUILD_btl_atlas)
    target_link_libraries(btl_atlas ${ATLAS_LIBRARIES})
    set_target_properties(btl_atlas PROPERTIES COMPILE_FLAGS "-DCBLASNAME=ATLAS -DHAS_LAPACK=1")
  endif()
endif ()

find_package(MKL)
if (MKL_FOUND)
  btl_add_bench(btl_mkl main.cpp)
  if(BUILD_btl_mkl)
    target_link_libraries(btl_mkl ${MKL_LIBRARIES})
    set_target_properties(btl_mkl PROPERTIES COMPILE_FLAGS "-DCBLASNAME=INTEL_MKL -DHAS_LAPACK=1")
  endif()
endif ()


find_package(OPENBLAS)
if (OPENBLAS_FOUND)
  btl_add_bench(btl_openblas main.cpp)
  if(BUILD_btl_openblas)
    target_link_libraries(btl_openblas ${OPENBLAS_LIBRARIES} )
    set_target_properties(btl_openblas PROPERTIES COMPILE_FLAGS "-DCBLASNAME=OPENBLAS")
  endif()
endif ()

find_package(ACML)
if (ACML_FOUND)
  btl_add_bench(btl_acml main.cpp)
  if(BUILD_btl_acml)
    target_link_libraries(btl_acml ${ACML_LIBRARIES} )
    set_target_properties(btl_acml PROPERTIES COMPILE_FLAGS "-DCBLASNAME=ACML -DHAS_LAPACK=1")
  endif()
endif ()

if(Eigen_SOURCE_DIR AND CMAKE_Fortran_COMPILER_WORKS)
  # we are inside Eigen and blas/lapack interface is compilable
  include_directories(${Eigen_SOURCE_DIR})
  btl_add_bench(btl_eigenblas main.cpp)
  if(BUILD_btl_eigenblas)
    target_link_libraries(btl_eigenblas eigen_blas eigen_lapack )
    set_target_properties(btl_eigenblas PROPERTIES COMPILE_FLAGS "-DCBLASNAME=EigenBLAS")
  endif()
endif()


