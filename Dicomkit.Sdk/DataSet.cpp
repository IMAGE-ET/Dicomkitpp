// This file is part of Dicomkit.
//  
// DicomKit  is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// DicomKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with DicomKit.  If not, see <http://www.gnu.org/licenses/>.

#include <string>

#include "DataSet.h"

using namespace std;
using namespace Dicomkit::Sdk;

DataSet::DataSet(void)
{
}


DataSet::~DataSet(void)
{
}

void DataSet::SetPreamble(char* preamble)
{
	memcpy(this->preamble,preamble,128);
}

void DataSet::SetPrefix(char* prefix)
{
	memcpy(this->prefix, prefix,4);
}

void DataSet::AddDataElement(DataElement dataElement)
{
	this->dataElement.push_back(new DataElement(dataElement));
}

void DataSet::AddDataElement(DataElement* dataElement)
{
	this->dataElement.push_back(dataElement);
}

void DataSet::RemoveDataElement(DataElement* dataElement)
{
	this->dataElement.remove(dataElement);	
}

list<DataElement*> DataSet::GetDataElement()
{
	return this->dataElement;
}

char* DataSet::GetPreamble()
{
	return this->preamble;
}

char* DataSet::GetPrefix()
{
	return this->prefix;
}