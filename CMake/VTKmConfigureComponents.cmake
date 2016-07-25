##============================================================================
##  Copyright (c) Kitware, Inc.
##  All rights reserved.
##  See LICENSE.txt for details.
##  This software is distributed WITHOUT ANY WARRANTY; without even
##  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
##  PURPOSE.  See the above copyright notice for more information.
##
##  Copyright 2016 Sandia Corporation.
##  Copyright 2016 UT-Battelle, LLC.
##  Copyright 2016 Los Alamos National Security.
##
##  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
##  the U.S. Government retains certain rights in this software.
##
##  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
##  Laboratory (LANL), the U.S. Government retains certain rights in
##  this software.
##============================================================================

# This file provides all the component-specific configuration. To add a
# component to this list, first add the name of the component to
# VTKm_AVAILABLE_COMPONENTS. Then add a macro (or function) named
# vtkm_configure_component_<name> that configures the given component. At a
# minimum, this macro should set (or clear) the variable VTKm_<name>_FOUND. It
# should also modify other apropos variables such as VTKm_INCLUDE_DIRS and
# VTKm_LIBRARIES.
#
# Components generally rely on other components, and should call
# vtkm_configure_component_<name> for those components as necessary.
#
# Any component configuration added to VTKm_AVAILABLE_COMPONENTS will
# automatically be added to the components available to find_package(VTKm).
#

set(VTKm_AVAILABLE_COMPONENTS
  Base
  Serial
  OpenGL
  OSMesa
  EGL
  Interop
  TBB
  CUDA
  )

#-----------------------------------------------------------------------------
# Support function for making vtkm_configure_component<name> functions.
#-----------------------------------------------------------------------------
macro(vtkm_finish_configure_component component)
  if(NOT VTKm_${component}_FOUND)

    cmake_parse_arguments(VTKm_FCC
      ""
      ""
      "DEPENDENT_VARIABLES;ADD_INCLUDES;ADD_LIBRARIES"
      ${ARGN}
      )
    set(VTKm_${component}_FOUND TRUE)
    foreach(var ${VTKm_FCC_DEPENDENT_VARIABLES})
      if(NOT ${var})
        message(STATUS "Failed to configure VTK-m component ${component}: !${var}")
        set(VTKm_${component}_FOUND)
        break()
      endif()
    endforeach(var)

    if (VTKm_${component}_FOUND)
      set(VTKm_INCLUDE_DIRS ${VTKm_INCLUDE_DIRS} ${VTKm_FCC_ADD_INCLUDES})
      set(VTKm_LIBRARIES ${VTKm_LIBRARIES} ${VTKm_FCC_ADD_LIBRARIES})
    endif()
  endif()
endmacro()

#-----------------------------------------------------------------------------
# The configuration macros
#-----------------------------------------------------------------------------

macro(vtkm_configure_component_Base)
  # Find the Boost library.
  if(NOT Boost_FOUND)
    find_package(BoostHeaders ${VTKm_REQUIRED_BOOST_VERSION})
  endif()

  vtkm_finish_configure_component(Base
    DEPENDENT_VARIABLES Boost_FOUND
    ADD_INCLUDES ${Boost_INCLUDE_DIRS}
    )
endmacro()

macro(vtkm_configure_component_Serial)
  vtkm_configure_component_Base()

  vtkm_finish_configure_component(Serial
    DEPENDENT_VARIABLES VTKm_Base_FOUND
    )
endmacro(vtkm_configure_component_Serial)

macro(vtkm_configure_component_OpenGL)
  vtkm_configure_component_Base()

  find_package(OpenGL)

  vtkm_finish_configure_component(OpenGL
    DEPENDENT_VARIABLES VTKm_Base_FOUND OPENGL_FOUND
    ADD_INCLUDES ${OPENGL_INCLUDE_DIR}
    ADD_LIBRARIES ${OPENGL_LIBRARIES}
    )
endmacro(vtkm_configure_component_OpenGL)

macro(vtkm_configure_component_OSMesa)
  vtkm_configure_component_OpenGL()

  if (UNIX AND NOT APPLE)
    find_package(MESA)

    vtkm_finish_configure_component(OSMesa
      DEPENDENT_VARIABLES VTKm_OpenGL_FOUND OSMESA_FOUND
      ADD_INCLUDES ${OSMESA_INCLUDE_DIR}
      ADD_LIBRARIES ${OSMESA_LIBRARY}
      )
  else()
    message(STATUS "OSMesa not supported on this platform.")
  endif()
endmacro(vtkm_configure_component_OSMesa)

macro(vtkm_configure_component_EGL)
  vtkm_configure_component_OpenGL()

  find_package(EGL)

  vtkm_finish_configure_component(EGL
    DEPENDENT_VARIABLES VTKm_OpenGL_FOUND EGL_FOUND
    ADD_INCLUDES ${EGL_INCLUDE_DIR}
    ADD_LIBRARIES ${EGL_LIBRARY}
    )
endmacro(vtkm_configure_component_EGL)

macro(vtkm_configure_component_Interop)
  vtkm_configure_component_OpenGL()

  find_package(GLEW)

  set(vtkm_interop_dependent_vars
    VTKm_OpenGL_FOUND
    VTKm_ENABLE_OPENGL_INTEROP
    GLEW_FOUND
    )
  #on unix/linux Glew uses pthreads, so we need to find that, and link to it
  #explicitly or else in release mode we get sigsegv on launch
  if (VTKm_Interop_FOUND AND UNIX)
    find_package(Threads)
    set(vtkm_interop_dependent_vars ${vtkm_interop_dependent_vars} CMAKE_USE_PTHREADS_INIT)
  endif()

  vtkm_finish_configure_component(Interop
    DEPENDENT_VARIABLES ${vtkm_interop_dependent_vars}
    ADD_INCLUDES ${GLEW_INCLUDE_DIRS}
    ADD_LIBRARIES ${GLEW_LIBRARIES}
    )
endmacro(vtkm_configure_component_Interop)

macro(vtkm_configure_component_TBB)
  if(VTKm_ENABLE_TBB)
    vtkm_configure_component_Base()

    find_package(TBB)
  endif()

  vtkm_finish_configure_component(TBB
    DEPENDENT_VARIABLES VTKm_ENABLE_TBB VTKm_Base_FOUND TBB_FOUND
    ADD_INCLUDES ${TBB_INCLUDE_DIRS}
    ADD_LIBRARIES ${TBB_LIBRARIES}
    )
endmacro(vtkm_configure_component_TBB)

macro(vtkm_configure_component_CUDA)
  if(VTKm_ENABLE_CUDA)
    vtkm_configure_component_Base()

    find_package(CUDA)
    mark_as_advanced(
      CUDA_BUILD_CUBIN
      CUDA_BUILD_EMULATION
      CUDA_HOST_COMPILER
      CUDA_SDK_ROOT_DIR
      CUDA_SEPARABLE_COMPILATION
      CUDA_TOOLKIT_ROOT_DIR
      CUDA_VERBOSE_BUILD
      )

    find_package(Thrust)
  endif()

  vtkm_finish_configure_component(CUDA
    DEPENDENT_VARIABLES
      VTKm_ENABLE_CUDA
      VTKm_Base_FOUND
      CUDA_FOUND
      THRUST_FOUND
    ADD_INCLUDES ${THRUST_INCLUDE_DIRS}
    )

  if(VTKm_CUDA_FOUND)
    #---------------------------------------------------------------------------
    # Setup build flags for CUDA
    #---------------------------------------------------------------------------
    # Populates CUDA_NVCC_FLAGS with the best set of flags to compile for a
    # given GPU architecture. The majority of developers should leave the
    # option at the default of 'native' which uses system introspection to
    # determine the smallest numerous of virtual and real architectures it
    # should target.
    #
    # The option of 'all' is provided for people generating libraries that
    # will deployed to any number of machines, it will compile all CUDA code
    # for all major virtual architectures, guaranteeing that the code will run
    # anywhere.
    #
    #
    # 1 - native
    #   - Uses system introspection to determine compile flags
    # 2 - fermi
    #   - Uses: --generate-code arch=compute_20,code=compute_20
    # 3 - kepler
    #   - Uses: --generate-code arch=compute_30,code=compute_30
    #   - Uses: --generate-code arch=compute_35,code=compute_35
    # 4 - maxwell
    #   - Uses: --generate-code arch=compute_50,code=compute_50
    #   - Uses: --generate-code arch=compute_52,code=compute_52
    # 5 - all
    #   - Uses: --generate-code arch=compute_20,code=compute_20
    #   - Uses: --generate-code arch=compute_30,code=compute_30
    #   - Uses: --generate-code arch=compute_35,code=compute_35
    #   - Uses: --generate-code arch=compute_50,code=compute_50
    #

    #specify the property
    set(VTKm_CUDA_Architecture "native" CACHE STRING "Which GPU Architecture(s) to compile for")
    set_property(CACHE VTKm_CUDA_Architecture PROPERTY STRINGS native fermi kepler maxwell all)

    #detect what the propery is set too
    if(VTKm_CUDA_Architecture STREQUAL "native")
      #run execute_process to do auto_detection
      set(command ${CUDA_NVCC_EXECUTABLE})
      set(args "-ccbin" "${CMAKE_CXX_COMPILER}" "--run" "${VTKm_CMAKE_MODULE_PATH}/VTKmDetectCUDAVersion.cxx")
      execute_process(
        COMMAND ${command} ${args}
        RESULT_VARIABLE ran_properly
        OUTPUT_VARIABLE run_output
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

      if(ran_properly EQUAL 0)
        #find the position of the "--generate-code" output. With some compilers such as
        #msvc we get compile output plus run output. So we need to strip out just the
        #run output
        string(FIND "${run_output}" "--generate-code" position)
        string(SUBSTRING "${run_output}" ${position} -1 run_output)
        set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} ${run_output}")
      else()
        message(STATUS "Unable to run \"${CUDA_NVCC_EXECUTABLE}\" to autodetect GPU architecture."
          "Falling back to fermi, please manually specify if you want something else.")
        set(VTKm_CUDA_Architecture "fermi")
      endif()
    endif()

    #since when we are native we can fail, and fall back to "fermi" these have
    #to happen after, and separately of the native check
    if(VTKm_CUDA_Architecture STREQUAL "fermi")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_20,code=compute_20")
    elseif(VTKm_CUDA_Architecture STREQUAL "kepler")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_30,code=compute_30")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_35,code=compute_35")
    elseif(VTKm_CUDA_Architecture STREQUAL "maxwell")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_50,code=compute_50")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_52,code=compute_52")
    elseif(VTKm_CUDA_Architecture STREQUAL "all")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_20,code=compute_20")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_30,code=compute_30")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_35,code=compute_35")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_50,code=compute_50")
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --generate-code arch=compute_52,code=compute_52")
    endif()

    if(WIN32)
      # On Windows, there is an issue with performing parallel builds with
      # nvcc. Multiple compiles can attempt to write the same .pdb file. Add
      # this argument to avoid this problem.
      set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --compiler-options /FS")
    endif()
  endif()
endmacro(vtkm_configure_component_CUDA)