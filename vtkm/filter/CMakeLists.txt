##============================================================================
##  Copyright (c) Kitware, Inc.
##  All rights reserved.
##  See LICENSE.txt for details.
##
##  This software is distributed WITHOUT ANY WARRANTY; without even
##  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
##  PURPOSE.  See the above copyright notice for more information.
##============================================================================

set(deprecated_headers
  AmrArrays.h
  CellAverage.h
  CellMeasures.h
  CellSetConnectivity.h
  CleanGrid.h
  ClipWithField.h
  ClipWithImplicitFunction.h
  ComputeMoments.h
  Contour.h
  ContourTreeUniform.h
  ContourTreeUniformAugmented.h
  ContourTreeUniformDistributed.h
  CoordinateSystemTransform.h
  CrossProduct.h
  DotProduct.h
  Entropy.h
  ExternalFaces.h
  ExtractGeometry.h
  ExtractPoints.h
  ExtractStructured.h
  FieldToColors.h
  GenerateIds.h
  GhostCellClassify.h
  GhostCellRemove.h
  Gradient.h
  Histogram.h
  ImageConnectivity.h
  ImageDifference.h
  ImageMedian.h
  Instantiations.h
  Mask.h
  MaskPoints.h
  MeshQuality.h
  MIRFilter.h
  NDEntropy.h
  NDHistogram.h
  ParticleDensityCloudInCell.h
  ParticleDensityNearestGridPoint.h
  PointAverage.h
  PointElevation.h
  PointTransform.h
  Probe.h
  Slice.h
  SplitSharpEdges.h
  SurfaceNormals.h
  Tetrahedralize.h
  Threshold.h
  ThresholdPoints.h
  Triangulate.h
  Tube.h
  VertexClustering.h
  VectorMagnitude.h
  WarpScalar.h
  WarpVector.h
  ZFPCompressor1D.h
  ZFPCompressor2D.h
  ZFPCompressor3D.h
  ZFPDecompressor1D.h
  ZFPDecompressor2D.h
  ZFPDecompressor3D.h
  )

vtkm_declare_headers(${deprecated_headers})

set(common_headers
  CreateResult.h
  FieldMetadata.h
  FilterCell.h
  FilterDataSet.h
  FilterDataSetWithField.h
  FilterField.h
  Filter.h
  FilterTraits.h
  PolicyBase.h
  PolicyDefault.h
  Lagrangian.h
  LagrangianStructures.h
  )

vtkm_declare_headers(${common_headers})

set(common_header_template_sources
  FilterDataSet.hxx
  FilterDataSetWithField.hxx
  FilterField.hxx
  Filter.hxx
  Lagrangian.hxx
  LagrangianStructures.hxx
  )

vtkm_declare_headers(${common_header_template_sources})

set(core_headers
  FieldSelection.h
  NewFilter.h
  NewFilterField.h
  MapFieldMergeAverage.h
  MapFieldPermutation.h
  TaskQueue.h
  )
set(core_sources
  NewFilterField.cxx
  )
set(core_sources_device
  MapFieldMergeAverage.cxx
  MapFieldPermutation.cxx
  NewFilter.cxx
  )

vtkm_library(
  NAME vtkm_filter_core
  HEADERS ${core_headers}
  SOURCES ${core_sources}
  DEVICE_SOURCES ${core_sources_device}
  USE_VTKM_JOB_POOL
)

add_library(vtkm_filter INTERFACE)

set_target_properties(
  vtkm_filter_core
  PROPERTIES
  UNITY_BUILD ON
  UNITY_BUILD_MODE BATCH
)

target_link_libraries(vtkm_filter_core PUBLIC vtkm_cont vtkm_worklet)

target_link_libraries(vtkm_filter PUBLIC INTERFACE
  vtkm_filter_core
  )

install(TARGETS vtkm_filter EXPORT ${VTKm_EXPORT_NAME})

add_subdirectory(clean_grid)
add_subdirectory(connected_components)
add_subdirectory(contour)
add_subdirectory(density_estimate)
add_subdirectory(entity_extraction)
add_subdirectory(flow)
add_subdirectory(image_processing)
add_subdirectory(internal)
add_subdirectory(field_conversion)
add_subdirectory(field_transform)
add_subdirectory(geometry_refinement)
add_subdirectory(mesh_info)
add_subdirectory(multi_block)
add_subdirectory(resampling)
add_subdirectory(scalar_topology)
add_subdirectory(vector_analysis)
add_subdirectory(zfp)

#-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -
if (VTKm_ENABLE_TESTING)
  add_subdirectory(testing)
endif ()
