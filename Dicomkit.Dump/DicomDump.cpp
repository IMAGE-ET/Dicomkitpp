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

#include "DicomDump.h"
#include "..\Dicomkit.Sdk\DataSet.h"
#include "..\Dicomkit.Sdk\ValueRepresentation.h"

using namespace std;
using namespace Dicomkit::Dump;

DicomDump::DicomDump(string fileName)
{
	this->fileName = fileName;
	this->dicomReader = new DicomReader(fileName);
}


DicomDump::~DicomDump(void)
{
}

void DicomDump::Dump(ostream& out)
{
	out<<"Dumping dicom contents..."<<endl;
	//this->dicomReader->Dump();

	DataSet dataSet = this->dicomReader->ParseDicom();
	list<DataElement*> dataElements = dataSet.GetDataElement();

	DumpLog(dataElements, out);
}

void DicomDump::DumpLog(list<DataElement*> dataElements, ostream& out)
{
	for (list<DataElement*>::iterator dataElement1 = dataElements.begin();
		dataElement1 != dataElements.end();
		++dataElement1) {
			string message;

			DataElement* dataElement = *dataElement1;

			unsigned short valueType = dataElement->GetValueType();
			unsigned short groupId = dataElement->GetDicomTag().GroupId;
			unsigned short elementId = dataElement->GetDicomTag().ElementId;
			int valLen = dataElement->GetValueLength();

			//skip Item sequence.
			if (groupId == 0xfffe && elementId == 0xe000) {
				continue;
			}

			switch (valueType) {
			case FL:
				{
					unsigned char* data = dataElement->GetValueField();
					message = GetLog(groupId, elementId, "FL");
					out << message;

					for (int i = 0; i < dataElement->GetValueLength() / sizeof(float); i++) {
						float f;
						memcpy(&f, data + (i * 4), sizeof(float));
						out << f << "";
					}
					out << endl;

				}
				break;
			case SL:
				{
					unsigned char* data = dataElement->GetValueField();
					message = GetLog(groupId, elementId, "SL");
					out << message;

					for (int i = 0; i < dataElement->GetValueLength() / sizeof(long); i++) {
						int j = i * 4;
						long us = data[j] | data[j + 1] << 8 | data[j + 2] << 16 | data[j + 3] << 24;
						out << us << " ";
					}
					out << endl;
				}
				break;
			case SS:
				{
					unsigned char* data = dataElement->GetValueField();
					message = GetLog(groupId, elementId, "SS");
					out << message;

					for (int i = 0; i < dataElement->GetValueLength() / sizeof(short); i++) {
						short us = data[(i * 2) + 1] << 8 | data[i * 2];
						out << us << " ";
					}
					out << endl;
				}
				break;
			case UL:
				{
					unsigned char* data = dataElement->GetValueField();
					unsigned long ulong = data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24;
					message = GetLog(groupId, elementId, "UL");
					out << message << ulong << endl;
				}
				break;
			case OB:
				{
					message = GetLog(groupId, elementId, "OB");
					out << message;

					unsigned char* data = dataElement->GetValueField();
					for (int i = 0; i  < dataElement->GetValueLength(); i++) {
						out << hex << (unsigned short)*(data+i) << " ";
					}
					out<<endl;
				}
				break;
			case UI:
				{
					message = GetLog(groupId, elementId, "UI");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case SH:
				{
					message = GetLog(groupId, elementId, "SH");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case AE:
				{
					message = GetLog(groupId, elementId, "AE");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case CS:
				{
					message = GetLog(groupId, elementId, "CS");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case DA:
				{
					message = GetLog(groupId, elementId, "DA");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case TM:
				{
					message = GetLog(groupId, elementId, "TM");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case LO:
				{
					message = GetLog(groupId, elementId, "LO");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case PN:
				{
					message = GetLog(groupId, elementId, "PN");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case SQ:
				{
					message = GetLog(groupId, elementId, "SQ");
					out << message << endl;

					out << "-----------Start-----------" << endl;
					DumpLog(dataElement->GetDataElements(), out);
					out << "----------- End -----------" << endl;
				}
				break;
			case AS:
				{
					message = GetLog(groupId, elementId, "AS");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case DS:
				{
					message = GetLog(groupId, elementId, "DS");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case IS:
				{
					message = GetLog(groupId, elementId, "IS");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case US:
				{
					unsigned char* data = dataElement->GetValueField();
					message = GetLog(groupId, elementId, "US");
					out << message;

					for (int i = 0; i < dataElement->GetValueLength()/ sizeof(unsigned short); i++) {
						unsigned short us = data[(i * 2) + 1] << 8 | data[i * 2];
						out << us << " ";
					}
					out << endl;

				}
				break;
			case LT:
				{
					message = GetLog(groupId, elementId, "LT");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case ST:
				{
					message = GetLog(groupId, elementId, "ST");
					string uid((char*)dataElement->GetValueField(), valLen);
					out << message << uid.c_str() << endl;
				}
				break;
			case OW:
				{
					message = GetLog(groupId, elementId, "OW");
					out << message << endl;
					/*unsigned char* data = dataElement->GetValueField();
					  for (int i = 0; i  < dataElement->GetValueLength(); i++) {
						out << hex << (unsigned short)*(data+i) << " ";
					}*/
				}
				break;
			case AT:
				{
					message = GetLog(groupId, elementId, "AT");
					unsigned char* data = dataElement->GetValueField();

					int at1 = data[1] << 8 | data[0];
					int at2 = data[3] << 8 | data[2];

					char buf[20];
					sprintf_s(buf, sizeof(buf), "(%04x,%04x)", at1, at2);
					out << message << buf << endl;
				}
			default:
				message = GetLog(groupId, elementId, "--");
				out << message << endl;
				break;
			}
	}
}

string DicomDump::GetLog(short groupId, short elementId, char* valType)
{
	char message[40];
	sprintf_s(message,sizeof(message), "<%04x,%04x> \t %s \t",groupId, elementId, valType);
	return message;
}