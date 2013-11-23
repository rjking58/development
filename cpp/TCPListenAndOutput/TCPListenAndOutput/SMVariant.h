#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"

//! Contains value of arbitrary type
class SMUTILITIES_API SMVariant 
{
public:
	enum VariantType { VT_UNDEF, VT_LONG, VT_ULONG, VT_STRING, VT_FLOAT, VT_BOOL, VT_INT, VT_INT64 };

	SMVariant()		: type(VT_UNDEF), object(NULL)	{};
	SMVariant(const long & v) : type(VT_UNDEF), object(NULL) { this->setValue(v); };
	SMVariant(const unsigned long & v) : type(VT_UNDEF), object(NULL) { this->setValue(v); };
	SMVariant(const char * const v) : type(VT_UNDEF), object(NULL) { this->setValue(v); };
	SMVariant(const double & v) : type(VT_UNDEF), object(NULL) { this->setValue(v); };
	SMVariant(const bool & v) : type(VT_UNDEF), object(NULL) { this->setValue(v); };
	SMVariant(const int & v) : type(VT_UNDEF), object(NULL) { this->setValue(v); };
	SMVariant(const __int64 & v) : type(VT_UNDEF), object(NULL) { this->setValue(v); };

	~SMVariant()	{ this->destroyValue();};
	bool IsEmpty() const { return this->type == VT_UNDEF; };
	void Clear() { this->destroyValue(); };
	VariantType getType() const { return this->type; };

	const long & getLong() const;
	const unsigned long & getULong() const;
	const SMString & getString() const;
	const double & getDouble() const;
	const bool & getBool() const;
	const int & getInt() const;
	const __int64 & getInt64() const;

	const SMVariant & operator=(const long & v) { this->setValue(v); return *this; };
	const SMVariant & operator=(const unsigned long & v) { this->setValue(v); return *this; };
	const SMVariant & operator=(const char * const v) { this->setValue(v); return *this; };
	const SMVariant & operator=(const double & v) { this->setValue(v); return *this; };
	const SMVariant & operator=(const bool & v) { this->setValue(v); return *this; };
	const SMVariant & operator=(const int & v) { this->setValue(v); return *this; };
	const SMVariant & operator=(const __int64 & v) { this->setValue(v); return *this; };

private:
	VariantType type;
	void* object;

	void destroyValue();
	void setValue(const long & v);
	void setValue(const unsigned long & v);
	void setValue(const char * const v);
	void setValue(const double & v);
	void setValue(const bool & v);
	void setValue(const int & v);
	void setValue(const __int64 & v);

	
};

