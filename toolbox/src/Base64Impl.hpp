#ifndef TOOLBOX_BASE64IMPL_H
#define TOOLBOX_BASE64IMPL_H

namespace Base64Impl
{
	// Converts binary data of length=len to base64 characters.
	// Length of the resultant string is stored in flen
	// (you must pass pointer flen).
	char* base64( const void* binaryData, int len, int *flen );

	unsigned char* unbase64( const char* ascii, int len, int *flen );
}

#endif
