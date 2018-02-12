//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2015 National Technology & Engineering Solutions of Sandia, LLC (NTESS).
//  Copyright 2015 UT-Battelle, LLC.
//  Copyright 2015 Los Alamos National Security.
//
//  Under the terms of Contract DE-NA0003525 with NTESS,
//  the U.S. Government retains certain rights in this software.
//
//  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
//  Laboratory (LANL), the U.S. Government retains certain rights in
//  this software.
//============================================================================

#define vtkm_cont_ArrayHandle_cxx
#include <vtkm/cont/ArrayHandle.h>

#ifdef VTKM_MSVC
#define _VTKM_SHARED_PTR_INSTANTIATE(Type)                                                         \
  template class VTKM_CONT_EXPORT                                                                  \
    std::shared_ptr<vtkm::cont::ArrayHandle<Type, vtkm::cont::StorageTagBasic>::InternalStruct>;   \
  template class VTKM_CONT_EXPORT std::shared_ptr<                                                 \
    vtkm::cont::ArrayHandle<vtkm::Vec<Type, 2>, vtkm::cont::StorageTagBasic>::InternalStruct>;     \
  template class VTKM_CONT_EXPORT std::shared_ptr<                                                 \
    vtkm::cont::ArrayHandle<vtkm::Vec<Type, 3>, vtkm::cont::StorageTagBasic>::InternalStruct>;     \
  template class VTKM_CONT_EXPORT std::shared_ptr<                                                 \
    vtkm::cont::ArrayHandle<vtkm::Vec<Type, 4>, vtkm::cont::StorageTagBasic>::InternalStruct>;

_VTKM_SHARED_PTR_INSTANTIATE(char)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::Int8)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::UInt8)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::Int16)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::UInt16)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::Int32)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::UInt32)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::Int64)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::UInt64)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::Float32)
_VTKM_SHARED_PTR_INSTANTIATE(vtkm::Float64)

#undef _VTKM_SHARED_PTR_INSTANTIATE
#endif // VTKM_MSVC

namespace vtkm
{
namespace cont
{
namespace internal
{

TypelessExecutionArray::TypelessExecutionArray(void*& array,
                                               void*& arrayEnd,
                                               void*& arrayCapacity,
                                               const void* arrayControl,
                                               const void* arrayControlCapacity)
  : Array(array)
  , ArrayEnd(arrayEnd)
  , ArrayCapacity(arrayCapacity)
  , ArrayControl(arrayControl)
  , ArrayControlCapacity(arrayControlCapacity)
{
}

ExecutionArrayInterfaceBasicBase::ExecutionArrayInterfaceBasicBase(StorageBasicBase& storage)
  : ControlStorage(storage)
{
}

ExecutionArrayInterfaceBasicBase::~ExecutionArrayInterfaceBasicBase()
{
}

ArrayHandleImpl::~ArrayHandleImpl()
{
  if (this->ExecutionArrayValid && this->ExecutionInterface != nullptr &&
      this->ExecutionArray != nullptr)
  {
    TypelessExecutionArray execArray(this->ExecutionArray,
                                     this->ExecutionArrayEnd,
                                     this->ExecutionArrayCapacity,
                                     this->ControlArray->GetBasePointer(),
                                     this->ControlArray->GetCapacityPointer());
    this->ExecutionInterface->Free(execArray);
  }

  delete this->ControlArray;
  delete this->ExecutionInterface;
}

} // end namespace internal

#define _VTKM_ARRAYHANDLE_INSTANTIATE(Type)                                                        \
  template class VTKM_CONT_EXPORT ArrayHandle<Type, StorageTagBasic>;                              \
  template class VTKM_CONT_EXPORT ArrayHandle<vtkm::Vec<Type, 2>, StorageTagBasic>;                \
  template class VTKM_CONT_EXPORT ArrayHandle<vtkm::Vec<Type, 3>, StorageTagBasic>;                \
  template class VTKM_CONT_EXPORT ArrayHandle<vtkm::Vec<Type, 4>, StorageTagBasic>;

_VTKM_ARRAYHANDLE_INSTANTIATE(char)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::Int8)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::UInt8)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::Int16)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::UInt16)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::Int32)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::UInt32)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::Int64)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::UInt64)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::Float32)
_VTKM_ARRAYHANDLE_INSTANTIATE(vtkm::Float64)

#undef _VTKM_ARRAYHANDLE_INSTANTIATE
}
} // end vtkm::cont
