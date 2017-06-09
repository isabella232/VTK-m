//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2017 Sandia Corporation.
//  Copyright 2017 UT-Battelle, LLC.
//  Copyright 2017 Los Alamos National Security.
//
//  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
//  the U.S. Government retains certain rights in this software.
//
//  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
//  Laboratory (LANL), the U.S. Government retains certain rights in
//  this software.
//============================================================================
#ifndef vtk_m_filter_SurfaceNormals_h
#define vtk_m_filter_SurfaceNormals_h

#include <vtkm/filter/FilterCell.h>

namespace vtkm
{
namespace filter
{

/// Compute surface normals on points and/or cells of a polygonal dataset.
/// The cell normals are faceted and are computed based on the plane where a
/// face lies. The point normals are smooth normals, computed by averaging
/// the face normals of incident cells.
class SurfaceNormals : public vtkm::filter::FilterCell<SurfaceNormals>
{
public:
  SurfaceNormals();

  /// Set/Get if cell normals should be generated. Default is off.
  void SetGenerateCellNormals(bool value) { this->GenerateCellNormals = value; }
  bool GetGenerateCellNormals() const { return this->GenerateCellNormals; }

  /// Set/Get if the point normals should be generated. Default is on.
  void SetGeneratePointNormals(bool value) { this->GeneratePointNormals = value; }
  bool GetGeneratePointNormals() const { return this->GeneratePointNormals; }

  /// Set/Get the name of the cell normals field. Defaul is "Normals".
  void SetCellNormalsName(const std::string& name) { this->CellNormalsName = name; }
  const std::string& GetCellNormalsName() const { return this->CellNormalsName; }

  /// Set/Get the name of the point normals field. Defaul is "Normals".
  void SetPointNormalsName(const std::string& name) { this->PointNormalsName = name; }
  const std::string& GetPointNormalsName() const { return this->PointNormalsName; }

  using vtkm::filter::FilterCell<SurfaceNormals>::Execute;

  /// Execute the filter using the active coordinate system.
  VTKM_CONT
  vtkm::filter::ResultField Execute(const vtkm::cont::DataSet& input);

  /// Execute the filter using the active coordinate system.
  template <typename DerivedPolicy>
  VTKM_CONT ResultField Execute(const vtkm::cont::DataSet& input,
                                const vtkm::filter::PolicyBase<DerivedPolicy>& policy);

  template <typename T, typename StorageType, typename DerivedPolicy, typename DeviceAdapter>
  vtkm::filter::ResultField DoExecute(
    const vtkm::cont::DataSet& input,
    const vtkm::cont::ArrayHandle<vtkm::Vec<T, 3>, StorageType>& points,
    const vtkm::filter::FieldMetadata& fieldMeta,
    const vtkm::filter::PolicyBase<DerivedPolicy>& policy,
    const DeviceAdapter& device);

private:
  bool GenerateCellNormals;
  bool GeneratePointNormals;

  std::string CellNormalsName;
  std::string PointNormalsName;
};

template <>
class FilterTraits<SurfaceNormals>
{
public:
  using InputFieldTypeList =
    vtkm::ListTagBase<vtkm::Vec<vtkm::Float32, 3>, vtkm::Vec<vtkm::Float64, 3>>;
};
}
} // vtkm::filter

#include <vtkm/filter/SurfaceNormals.hxx>

#endif // vtk_m_filter_SurfaceNormals_h
