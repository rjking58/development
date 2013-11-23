
#include "stdafx.h"
#include "SMTraceUtility.h"
#include "SMVariant.h"

void SMVariant::destroyValue()
{
	switch ( this->type )
	{
	case VT_UNDEF :
		{
			if ( NULL != this->object )
			{
				SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid value");
			}
			break;
		}
	case VT_LONG :
		{
			if ( NULL == this->object )
			{
				SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid value");
			}
			else 
			{
				delete static_cast<long*>(this->object);
				this->object = NULL;
				this->type = VT_UNDEF;
			}
			break;
		}
	case VT_ULONG :
		{
			if ( NULL == this->object )
			{
				SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid value");
			}
			else 
			{
				delete static_cast<unsigned long*>(this->object);
				this->object = NULL;
				this->type = VT_UNDEF;
			}
			break;
		}
	case VT_STRING :
		{
			if ( NULL == this->object )
			{
				SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid value");
			}
			else 
			{
				delete static_cast<SMString*>(this->object);
				this->object = NULL;
				this->type = VT_UNDEF;
			}
			break;
		}
	case VT_FLOAT :
		{
			if ( NULL == this->object )
			{
				SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid value");
			}
			else 
			{
				delete static_cast<double*>(this->object);
				this->object = NULL;
				this->type = VT_UNDEF;
			}
			break;
		}
	case VT_BOOL :
		{
			if ( NULL == this->object )
			{
				SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid value");
			}
			else 
			{
				delete static_cast<bool*>(this->object);
				this->object = NULL;
				this->type = VT_UNDEF;
			}
			break;
		}
	case VT_INT:
		{
			if ( NULL == this->object )
			{
				SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid value");
			}
			else 
			{
				delete static_cast<int*>(this->object);
				this->object = NULL;
				this->type = VT_UNDEF;
			}
			break;
		}
	case VT_INT64 :
		{
			if ( NULL == this->object )
			{
				SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid value");
			}
			else 
			{
				delete static_cast<__int64*>(this->object);
				this->object = NULL;
				this->type = VT_UNDEF;
			}
			break;
		}
	default :
		{
			SM_TRACE(SMTRACE, "ERROR : SMVariant::destroyValue - invalid type");
			break;
		}
	}
}

void SMVariant::setValue(const long & v)
{
	this->destroyValue();
	this->type = VT_LONG;
	this->object = new long(v);
}

void SMVariant::setValue(const unsigned long & v)
{
	this->destroyValue();
	this->type = VT_ULONG;
	this->object = new unsigned long(v);
}

void SMVariant::setValue(const char * const v)
{
	this->destroyValue();
	this->type = VT_STRING;
	this->object = new SMString(v);
}

void SMVariant::setValue(const double & v)
{
	this->destroyValue();
	this->type = VT_FLOAT;
	this->object = new double(v);
}

void SMVariant::setValue(const bool & v)
{
	this->destroyValue();
	this->type = VT_BOOL;
	this->object = new bool(v);
}

void SMVariant::setValue(const int & v)
{
	this->destroyValue();
	this->type = VT_INT;
	this->object = new long(v);
}

void SMVariant::setValue(const __int64 & v)
{
	this->destroyValue();
	this->type = VT_INT64;
	this->object = new __int64(v);
}

const long & SMVariant::getLong() const
{
	if ( VT_LONG == this->type )
	{
		return *static_cast<long*>(this->object);
	}
	else
	{
		throw std::domain_error("Type mismatch.");
	}
}

const unsigned long & SMVariant::getULong() const
{
	if ( VT_ULONG == this->type )
	{
		return *static_cast<unsigned long*>(this->object);
	}
	else
	{
		throw std::domain_error("Type mismatch.");
	}
}

const SMString & SMVariant::getString() const
{
	if ( VT_STRING == this->type )
	{
		return *static_cast<SMString*>(this->object);
	}
	else
	{
		throw std::domain_error("Type mismatch.");
	}
}

const double & SMVariant::getDouble() const
{
	if ( VT_FLOAT == this->type )
	{
		return *static_cast<double*>(this->object);
	}
	else
	{
		throw std::domain_error("Type mismatch.");
	}
}

const bool & SMVariant::getBool() const
{
	if ( VT_BOOL == this->type )
	{
		return *static_cast<bool*>(this->object);
	}
	else
	{
		throw std::domain_error("Type mismatch.");
	}
}

const int & SMVariant::getInt() const
{
	if ( VT_INT == this->type )
	{
		return *static_cast<int*>(this->object);
	}
	else
	{
		throw std::domain_error("Type mismatch.");
	}
}

const __int64 & SMVariant::getInt64() const
{
	if ( VT_INT64 == this->type )
	{
		return *static_cast<__int64*>(this->object);
	}
	else
	{
		throw std::domain_error("Type mismatch.");
	}
}





