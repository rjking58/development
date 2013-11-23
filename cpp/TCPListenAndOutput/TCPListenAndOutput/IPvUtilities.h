#pragma once

// these two helper functions are used to set the correct IPv4/IPv6 values 
const SMString getValidIPValue(const SMString &IPv4Value, const SMString &IPv6Value)
{
	if (!IPv4Value.IsEmpty())
		return (IPv4Value);
	else if (!IPv6Value.IsEmpty())
		return (IPv6Value);

	return ("");
}

const ULONG getValidIPValue(ULONG IPv4Value, ULONG IPv6Value)
{
	if (0 != IPv4Value)
		return (IPv4Value);
	else if (0 != IPv6Value)
		return (IPv6Value);

	return (0);
}
