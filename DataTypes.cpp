#include "pch.h"
#include "DataTypes.h"

CString DataTypes::Types[7] =
{
	DATATYPE_STRING,
	DATATYPE_DECIMAL,
	DATATYPE_INTEGER,
	DATATYPE_BOOLEAN,
	DATATYPE_DATE,
	DATATYPE_TIME,
	DATATYPE_NONE
};

int DataTypes::Length()
{
	return sizeof(Types) / sizeof(Types[0]);
}
