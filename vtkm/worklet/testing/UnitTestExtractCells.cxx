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

#include <vtkm/worklet/ExtractGeometry.h>

#include <vtkm/cont/testing/MakeTestDataSet.h>
#include <vtkm/cont/testing/Testing.h>

#include <vtkm/cont/ArrayPortalToIterators.h>
#include <vtkm/cont/CellSet.h>

#include <algorithm>
#include <iostream>
#include <vector>

using vtkm::cont::testing::MakeTestDataSet;

template <typename DeviceAdapter>
class TestingExtractCells
{
public:
/*
  void TestExtractCellsStructuredWithSphere() const
  {
    std::cout << "Testing extract cells with implicit function (sphere):" << std::endl;

    typedef vtkm::cont::CellSetSingleType<> OutCellSetType;

    // Input data set created
    vtkm::cont::DataSet dataset = MakeTestDataSet().Make3DUniformDataSet1();
  
    // Implicit function
    vtkm::Vec<vtkm::FloatDefault, 3> center(2, 2, 2);
    vtkm::FloatDefault radius(1.8);
    vtkm::Sphere sphere(center, radius);
  
    // Output dataset contains input coordinate system
    vtkm::cont::DataSet outDataSet;
    outDataSet.AddCoordinateSystem(dataset.GetCoordinateSystem(0));
    for (vtkm::Id indx = 0; indx < dataset.GetNumberOfFields(); indx++)
    {
      vtkm::cont::Field field = dataset.GetField(indx);
      if (field.GetAssociation() == vtkm::cont::Field::ASSOC_POINTS)
      {
        outDataSet.AddField(field);
      }
    }

    // Output data set with cell set containing extracted cells
    vtkm::worklet::ExtractCells extractCells;
    OutCellSetType outCellSet;
    vtkm::cont::CellSetSingleType<> outputCellSet =
                outCellSet = extractCells.Run(
                                   dataset.GetCellSet(0),
                                   sphere,
                                   dataset.GetCoordinateSystem("coords"),
                                   DeviceAdapter());
    outDataSet.AddCellSet(outCellSet);

    VTKM_TEST_ASSERT(test_equal(outCellSet.GetNumberOfCells(), 27), "Wrong result for ExtractCells");
  }
*/

/*
  void TestExtractCellsStructuredWithBox() const
  {
    std::cout << "Testing extract cells with implicit function (box):" << std::endl;

    typedef vtkm::cont::CellSetSingleType<> OutCellSetType;

    // Input data set created
    vtkm::cont::DataSet dataset = MakeTestDataSet().Make3DUniformDataSet1();
  
    // Implicit function
    vtkm::Vec<vtkm::FloatDefault, 3> minPoint(1.0, 1.0, 1.0);
    vtkm::Vec<vtkm::FloatDefault, 3> maxPoint(3.0, 3.0, 3.0);
    vtkm::Box box(minPoint, maxPoint);
  
    // Output dataset contains input coordinate system
    vtkm::cont::DataSet outDataSet;
    outDataSet.AddCoordinateSystem(dataset.GetCoordinateSystem(0));
    for (vtkm::Id indx = 0; indx < dataset.GetNumberOfFields(); indx++)
    {
      vtkm::cont::Field field = dataset.GetField(indx);
      if (field.GetAssociation() == vtkm::cont::Field::ASSOC_POINTS)
      {
        outDataSet.AddField(field);
      }
    }

    // Output data set with cell set containing extracted points
    vtkm::worklet::ExtractPoints extractPoints;
    OutCellSetType outCellSet;
    vtkm::cont::CellSetSingleType<> outputCellSet =
    outCellSet = extractPoints.Run(dataset.GetCellSet(0),
                                   box,
                                   dataset.GetCoordinateSystem("coords"),
                                   DeviceAdapter());
    outDataSet.AddCellSet(outCellSet);

    VTKM_TEST_ASSERT(test_equal(outCellSet.GetNumberOfCells(), 27), "Wrong result for ExtractPoints");
  }
*/

/*
  void TestExtractCellsStructuredById() const
  {
    std::cout << "Testing extract cells structured by id:" << std::endl;

    typedef vtkm::cont::CellSetStructured<3> InCellSetType;
    typedef vtkm::cont::CellSetExplicit<> OutCellSetType;

    // Input data set created
    vtkm::cont::DataSet dataset = MakeTestDataSet().Make3DUniformDataSet1();
    InCellSetType cellSet;
    dataset.GetCellSet(0).CopyTo(cellSet);
  
    // Cells to extract
    const int nCells = 18;
    vtkm::Id cellids[nCells] = {0, 1, 2, 3, 4, 5, 10, 15, 20, 25, 50, 75, 100};
    vtkm::cont::ArrayHandle<vtkm::Id> cellIds =
                            vtkm::cont::make_ArrayHandle(cellids, nCells);

    // Output dataset contains input coordinate system
    vtkm::cont::DataSet outDataSet;
    outDataSet.AddCoordinateSystem(dataset.GetCoordinateSystem(0));

    // Output data set with cell set containing extracted cells and all points
    vtkm::worklet::ExtractCells extractCells;
    OutCellSetType outCellSet = extractCells.Run(cellSet,
                                                 cellIds,
                                                 DeviceAdapter());
    outDataSet.AddCellSet(outCellSet);

    VTKM_TEST_ASSERT(test_equal(outCellSet.GetNumberOfCells(), nCells), "Wrong result for ExtractCells");
  }
*/

  void TestExtractCellsExplicitById() const
  {
    std::cout << "Testing extract cell explicit by id:" << std::endl;

    typedef vtkm::cont::CellSetExplicit<> CellSetType;

    // Input data set created
    vtkm::cont::DataSet dataset = MakeTestDataSet().Make3DExplicitDataSet5();
    CellSetType cellSet;
    dataset.GetCellSet(0).CopyTo(cellSet);

    // Cells to extract
    const int nCells = 2;
    vtkm::Id cellids[nCells] = {1, 2};
    vtkm::cont::ArrayHandle<vtkm::Id> cellIds =
                            vtkm::cont::make_ArrayHandle(cellids, nCells);
  
    // Output dataset contains input coordinate system
    vtkm::cont::DataSet outDataSet;
    outDataSet.AddCoordinateSystem(dataset.GetCoordinateSystem(0));

    // Output data set with cell set containing extracted cells and all points
    vtkm::worklet::ExtractGeometry extractGeometry;
    CellSetType outCellSet = extractGeometry.RunExtractCellsExplicit(
                                              cellSet,
                                              cellIds,
                                              DeviceAdapter());
    outDataSet.AddCellSet(outCellSet);

    VTKM_TEST_ASSERT(test_equal(outCellSet.GetNumberOfCells(), nCells), "Wrong result for ExtractCells");
    VTKM_TEST_ASSERT(test_equal(outCellSet.GetConnectivityArray(vtkm::TopologyElementTagPoint(),
                                                                vtkm::TopologyElementTagCell()).
                     GetNumberOfValues(), 9), "Wrong result for ExtractCells");
  }

  void TestExtractCellsExplicitWithBox() const
  {
    std::cout << "Testing extract cells with implicit function (box) on explicit:" << std::endl;

    typedef vtkm::cont::CellSetExplicit<> CellSetType;

    // Input data set created
    vtkm::cont::DataSet dataset = MakeTestDataSet().Make3DExplicitDataSet5();
    CellSetType cellSet;
    dataset.GetCellSet(0).CopyTo(cellSet);

    // Implicit function
    vtkm::Vec<vtkm::FloatDefault, 3> minPoint(0.5, 0.0, 0.0);
    vtkm::Vec<vtkm::FloatDefault, 3> maxPoint(2.0, 2.0, 2.0);
    vtkm::Box box(minPoint, maxPoint);
  
    // Output dataset contains input coordinate system
    vtkm::cont::DataSet outDataSet;
    outDataSet.AddCoordinateSystem(dataset.GetCoordinateSystem(0));

    // Output data set with cell set containing extracted cells and all points
    vtkm::worklet::ExtractGeometry extractGeometry;
    CellSetType outCellSet = extractGeometry.RunExtractCellsExplicit(
                                              cellSet,
                                              box,
                                              dataset.GetCoordinateSystem("coordinates"),
                                              DeviceAdapter());
    outDataSet.AddCellSet(outCellSet);

    VTKM_TEST_ASSERT(test_equal(outCellSet.GetNumberOfCells(), 2), "Wrong result for ExtractCells");
    VTKM_TEST_ASSERT(test_equal(outCellSet.GetConnectivityArray(vtkm::TopologyElementTagPoint(),
                                                                vtkm::TopologyElementTagCell()).
                     GetNumberOfValues(), 9), "Wrong result for ExtractCells");
  }

  void operator()() const
  {
    //this->TestExtractCellsStructuredById();
    //this->TestExtractCellsStructuredWithSphere();
    //this->TestExtractCellsStructuredWithBox();
    this->TestExtractCellsExplicitById();
    this->TestExtractCellsExplicitWithBox();
  }
};

int UnitTestExtractCells(int, char *[])
{
  return vtkm::cont::testing::Testing::Run(
      TestingExtractCells<VTKM_DEFAULT_DEVICE_ADAPTER_TAG>());
}
