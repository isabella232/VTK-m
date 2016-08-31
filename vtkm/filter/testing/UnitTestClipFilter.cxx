//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2014 Sandia Corporation.
//  Copyright 2014 UT-Battelle, LLC.
//  Copyright 2014 Los Alamos National Security.
//
//  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
//  the U.S. Government retains certain rights in this software.
//
//  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
//  Laboratory (LANL), the U.S. Government retains certain rights in
//  this software.
//============================================================================

#include <vtkm/filter/Clip.h>

#include <vtkm/cont/DynamicArrayHandle.h>
#include <vtkm/cont/testing/Testing.h>
#include <vtkm/cont/testing/MakeTestDataSet.h>

namespace {

typedef vtkm::Vec<vtkm::FloatDefault, 3> Coord3D;


vtkm::cont::DataSet MakeTestDatasetExplicit()
{
  std::vector<Coord3D> coords;
  coords.push_back( Coord3D(0.0f, 0.0f, 0.0f) );
  coords.push_back( Coord3D(1.0f, 0.0f, 0.0f) );
  coords.push_back( Coord3D(1.0f, 1.0f, 0.0f) );
  coords.push_back( Coord3D(0.0f, 1.0f, 0.0f) );

  std::vector<vtkm::Id> connectivity;
  connectivity.push_back(0);
  connectivity.push_back(1);
  connectivity.push_back(3);
  connectivity.push_back(3);
  connectivity.push_back(1);
  connectivity.push_back(2);

  vtkm::cont::DataSet ds;
  vtkm::cont::DataSetBuilderExplicit builder;
  ds = builder.Create(coords, vtkm::CellShapeTagTriangle(), connectivity, "coords");

  std::vector<vtkm::Float32> values;
  values.push_back(1.0);
  values.push_back(2.0);
  values.push_back(1.0);
  values.push_back(0.0);
  vtkm::cont::DataSetFieldAdd fieldAdder;
  fieldAdder.AddPointField(ds, "scalars", values);

  return ds;
}

void TestClipExplicit()
{
  std::cout << "Testing Clip Filter on Explicit data" << std::endl;

  vtkm::cont::DataSet ds = MakeTestDatasetExplicit();

  vtkm::filter::ResultDataSet result;
  vtkm::filter::Clip clip;
  clip.SetClipValue(0.5);

  result = clip.Execute( ds, std::string("scalars"));


  const vtkm::cont::DataSet& outputData = result.GetDataSet();
  VTKM_TEST_ASSERT(outputData.GetNumberOfCellSets() == 1,
                   "Wrong number of cellsets in the output dataset");
  VTKM_TEST_ASSERT(outputData.GetNumberOfCoordinateSystems() == 1,
                   "Wrong number of coordinate systems in the output dataset");

  VTKM_TEST_ASSERT(outputData.GetNumberOfFields() == 1,
                   "Wrong number of fields in the output dataset");

  vtkm::cont::DynamicArrayHandle temp = outputData.GetField("scalars").GetData();
  vtkm::cont::ArrayHandle<vtkm::Float32> resultArrayHandle;
  temp.CopyTo(resultArrayHandle);

  vtkm::Float32 expected[7] = { 1, 2, 1, 0, 0.5, 0.5, 0.5 };
  for (int i = 0; i < 7; ++i)
  {
    VTKM_TEST_ASSERT(test_equal(resultArrayHandle.GetPortalConstControl().Get(i),
        expected[i]), "Wrong result for Clip fliter on triangle explicit data");
  }

}


void TestClip()
{
  //todo: add more clip tests
  TestClipExplicit();
}

}

int UnitTestClipFilter(int, char *[])
{
  return vtkm::cont::testing::Testing::Run(TestClip);
}