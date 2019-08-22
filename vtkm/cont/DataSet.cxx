//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================

#include <vtkm/cont/DataSet.h>

namespace vtkm
{
namespace cont
{
void DataSet::Clear()
{
  this->CoordSystems.clear();
  this->Fields.clear();
  this->CellSets.clear();
}

void DataSet::CopyStructure(const vtkm::cont::DataSet& source)
{
  this->CoordSystems = source.CoordSystems;
  this->CellSets = source.CellSets;
}

const vtkm::cont::Field& DataSet::GetField(vtkm::Id index) const
{
  VTKM_ASSERT((index >= 0) && (index < this->GetNumberOfFields()));
  return this->Fields[static_cast<std::size_t>(index)];
}

vtkm::Id DataSet::GetFieldIndex(const std::string& name, vtkm::cont::Field::Association assoc) const
{
  bool found;
  vtkm::Id index = this->FindFieldIndex(name, assoc, found);
  if (found)
  {
    return index;
  }
  else
  {
    throw vtkm::cont::ErrorBadValue("No field with requested name: " + name);
  }
}

const vtkm::cont::CoordinateSystem& DataSet::GetCoordinateSystem(vtkm::Id index) const
{
  VTKM_ASSERT((index >= 0) && (index < this->GetNumberOfCoordinateSystems()));
  return this->CoordSystems[static_cast<std::size_t>(index)];
}

vtkm::cont::CoordinateSystem& DataSet::GetCoordinateSystem(vtkm::Id index)
{
  VTKM_ASSERT((index >= 0) && (index < this->GetNumberOfCoordinateSystems()));
  return this->CoordSystems[static_cast<std::size_t>(index)];
}

vtkm::Id DataSet::GetCoordinateSystemIndex(const std::string& name) const
{
  vtkm::Id index = -1;
  for (auto i = this->CoordSystems.begin(); i != this->CoordSystems.end(); ++i)
  {
    if (i->GetName() == name)
    {
      index = static_cast<vtkm::Id>(std::distance(this->CoordSystems.begin(), i));
      break;
    }
  }
  return index;
}

const vtkm::cont::CoordinateSystem& DataSet::GetCoordinateSystem(const std::string& name) const
{
  vtkm::Id index = this->GetCoordinateSystemIndex(name);
  if (index < 0)
  {
    std::string error_message("No coordinate system with the name " + name +
                              " valid names are: \n");
    for (const auto& cs : this->CoordSystems)
    {
      error_message += cs.GetName() + "\n";
    }
    throw vtkm::cont::ErrorBadValue(error_message);
  }
  return this->GetCoordinateSystem(index);
}

vtkm::cont::CoordinateSystem& DataSet::GetCoordinateSystem(const std::string& name)
{
  vtkm::Id index = this->GetCoordinateSystemIndex(name);
  if (index < 0)
  {
    std::string error_message("No coordinate system with the name " + name +
                              " valid names are: \n");
    for (const auto& cs : this->CoordSystems)
    {
      error_message += cs.GetName() + "\n";
    }
    throw vtkm::cont::ErrorBadValue(error_message);
  }
  return this->GetCoordinateSystem(index);
}

const vtkm::cont::DynamicCellSet& DataSet::GetCellSet(vtkm::Id index) const
{
  VTKM_ASSERT((index >= 0) && (index < this->GetNumberOfCellSets()));
  return this->CellSets[static_cast<std::size_t>(index)];
}

vtkm::Id DataSet::GetCellSetIndex(const std::string& name) const
{
  vtkm::Id index = -1;
  for (auto i = this->CellSets.begin(); i != this->CellSets.end(); ++i)
  {
    if (i->GetName() == name)
    {
      index = static_cast<vtkm::Id>(std::distance(this->CellSets.begin(), i));
      break;
    }
  }
  return index;
}

const vtkm::cont::DynamicCellSet& DataSet::GetCellSet(const std::string& name) const
{
  vtkm::Id index = this->GetCellSetIndex(name);
  if (index < 0)
  {
    std::string error_message("No cell set with the name " + name + " valid names are: \n");
    for (const auto& cs : this->CellSets)
    {
      error_message += cs.GetName() + "\n";
    }
    throw vtkm::cont::ErrorBadValue(error_message);
  }
  return this->GetCellSet(index);
}

void DataSet::PrintSummary(std::ostream& out) const
{
  out << "DataSet:\n";
  out << "  CoordSystems[" << this->CoordSystems.size() << "]\n";
  for (std::size_t index = 0; index < this->CoordSystems.size(); index++)
  {
    this->CoordSystems[index].PrintSummary(out);
  }

  out << "  CellSets[" << this->GetNumberOfCellSets() << "]\n";
  for (vtkm::Id index = 0; index < this->GetNumberOfCellSets(); index++)
  {
    this->GetCellSet(index).PrintSummary(out);
  }

  out << "  Fields[" << this->GetNumberOfFields() << "]\n";
  for (vtkm::Id index = 0; index < this->GetNumberOfFields(); index++)
  {
    this->GetField(index).PrintSummary(out);
  }
}

vtkm::Id DataSet::FindFieldIndex(const std::string& name,
                                 vtkm::cont::Field::Association association,
                                 bool& found) const
{
  for (std::size_t index = 0; index < this->Fields.size(); ++index)
  {
    if ((association == vtkm::cont::Field::Association::ANY ||
         association == this->Fields[index].GetAssociation()) &&
        this->Fields[index].GetName() == name)
    {
      found = true;
      return static_cast<vtkm::Id>(index);
    }
  }
  found = false;
  return -1;
}

} // namespace cont
} // namespace vtkm
