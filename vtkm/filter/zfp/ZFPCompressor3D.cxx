//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================

#include <vtkm/filter/zfp/ZFPCompressor3D.h>
#include <vtkm/filter/zfp/worklet/ZFPCompressor.h>

namespace vtkm
{
namespace filter
{
namespace zfp
{
//-----------------------------------------------------------------------------
VTKM_CONT vtkm::cont::DataSet ZFPCompressor3D::DoExecute(const vtkm::cont::DataSet& input)
{
  vtkm::cont::CellSetStructured<3> cellSet;
  input.GetCellSet().AsCellSet(cellSet);
  vtkm::Id3 pointDimensions = cellSet.GetPointDimensions();

  vtkm::cont::ArrayHandle<vtkm::Int64> compressed;

  vtkm::worklet::ZFPCompressor compressor;
  using SupportedTypes = vtkm::List<vtkm::Int32, vtkm::Float32, vtkm::Float64>;
  this->GetFieldFromDataSet(input)
    .GetData()
    .CastAndCallForTypesWithFloatFallback<SupportedTypes, VTKM_DEFAULT_STORAGE_LIST>(
      [&](const auto& concrete) {
        compressed = compressor.Compress(concrete, rate, pointDimensions);
      });

  // TODO: is it really PointField or WHOLE_MESH, should we do it the same way as Histogram?
  return this->CreateResultFieldPoint(input, "compressed", compressed);
}
} // namespace zfp
} // namespace filter
} // namespace vtkm
