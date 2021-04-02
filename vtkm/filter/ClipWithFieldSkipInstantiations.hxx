//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================
////////////////////////// **** DO NOT EDIT THIS FILE!!! ****
// This file is automatically generated by ClipWithFieldSkipInstantiations.hxx.in
// clang-format off

#ifndef vtk_m_filter_ClipWithFieldSkipInstantiations_hxx
#define vtk_m_filter_ClipWithFieldSkipInstantiations_hxx

#include <vtkm/filter/ClipWithField.h>
#include <vtkm/filter/ClipWithField.hxx>

#include <vtkm/cont/ArrayHandlePermutation.h>
#include <vtkm/cont/CellSetPermutation.h>
#include <vtkm/cont/CoordinateSystem.h>
#include <vtkm/cont/DynamicCellSet.h>
#include <vtkm/cont/ErrorFilterExecution.h>

namespace vtkm
{
namespace filter
{

#ifndef vtkm_filter_ClipWithFieldExecuteScalar_cxx

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Float32>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Float32, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Float64>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Float64, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

#endif // vtkm_filter_ClipWithFieldExecuteScalar_cxx

#ifndef vtkm_filter_ClipWithFieldExecuteSignedInteger_cxx

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Int8>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Int8, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Int16>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Int16, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Int32>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Int32, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Int64>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::Int64, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

#endif // vtkm_filter_ClipWithFieldExecuteSignedInteger_cxx

#ifndef vtkm_filter_ClipWithFieldExecuteUnsignedInteger_cxx

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::UInt8>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::UInt8, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::UInt16>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::UInt16, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::UInt32>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::UInt32, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::UInt64>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);

#ifndef VTKM_NO_DEPRECATED_VIRTUAL
VTKM_DEPRECATED_SUPPRESS_BEGIN
extern template VTKM_FILTER_EXTRA_EXPORT vtkm::cont::DataSet ClipWithField::DoExecute(
  const vtkm::cont::DataSet&,
  const vtkm::cont::ArrayHandle<vtkm::UInt64, vtkm::cont::StorageTagVirtual>&,
  const vtkm::filter::FieldMetadata&,
  vtkm::filter::PolicyBase<vtkm::filter::PolicyDefault>);
VTKM_DEPRECATED_SUPPRESS_END
#endif

#endif // vtkm_filter_ClipWithFieldExecuteUnsignedInteger_cxx


}
}

#endif
