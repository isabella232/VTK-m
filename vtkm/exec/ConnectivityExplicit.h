//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2015 Sandia Corporation.
//  Copyright 2015 UT-Battelle, LLC.
//  Copyright 2015 Los Alamos National Security.
//
//  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
//  the U.S. Government retains certain rights in this software.
//
//  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
//  Laboratory (LANL), the U.S. Government retains certain rights in
//  this software.
//============================================================================
#ifndef vtk_m_exec_ConnectivityExplicit_h
#define vtk_m_exec_ConnectivityExplicit_h

#include <vtkm/CellShape.h>
#include <vtkm/Types.h>

#include <vtkm/VecFromPortal.h>

namespace vtkm {
namespace exec {

template<typename ShapePortalType,
         typename NumIndicesPortalType,
         typename ConnectivityPortalType,
         typename IndexOffsetPortalType
         >
class ConnectivityExplicit
{
public:
  typedef typename vtkm::Id SchedulingRangeType;

  ConnectivityExplicit() {}

  ConnectivityExplicit(const ShapePortalType& shapePortal,
                       const NumIndicesPortalType& numIndicesPortal,
                       const ConnectivityPortalType& connPortal,
                       const IndexOffsetPortalType& indexOffsetPortal
                       )
  : Shapes(shapePortal),
    NumIndices(numIndicesPortal),
    Connectivity(connPortal),
    IndexOffset(indexOffsetPortal)
  {

  }

  VTKM_EXEC
  SchedulingRangeType GetNumberOfElements() const
  {
    return this->Shapes.GetNumberOfValues();
  }

  typedef vtkm::CellShapeTagGeneric CellShapeTag;

  VTKM_EXEC
  CellShapeTag GetCellShape(vtkm::Id index) const
  {
    return CellShapeTag(this->Shapes.Get(index));
  }

  using IndicesType = vtkm::VecFromPortal<ConnectivityPortalType>;

  /// Returns a Vec-like object containing the indices for the given index.
  /// The object returned is not an actual array, but rather an object that
  /// loads the indices lazily out of the connectivity array. This prevents
  /// us from having to know the number of indices at compile time.
  ///
  VTKM_EXEC
  IndicesType GetIndices(vtkm::Id index) const
  {
    vtkm::Id offset = this->IndexOffset.Get(index);
    vtkm::IdComponent length = this->NumIndices.Get(index);
    return IndicesType(this->Connectivity, length, offset);
  }

private:
  ShapePortalType Shapes;
  NumIndicesPortalType NumIndices;
  ConnectivityPortalType Connectivity;
  IndexOffsetPortalType IndexOffset;
};

} // namespace exec
} // namespace vtkm

#endif //  vtk_m_exec_ConnectivityExplicit_h
