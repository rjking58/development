


void huge *_CType _FARFUNC memmoveHUGE( void huge *dst, const void huge *src, unsigned long n )
{
	long 	               x;
	unsigned char			huge *src_byte_p = (unsigned char huge *)src;
	unsigned char			huge *dst_byte_p = (unsigned char huge *)dst;

	// same space array copy.  If the source pointer is less than target pointer, assume that the
	// source and target spaces overlap and do a backward copy to prevent hosing the data during 
	// the move.  If the source pointer is greater than the target pointer, do a forward move for 
	// the same reason.  And finally, if both pointers are equal, return since there is nothing
	// to do!  rjk

	// if they are equal.. do nothing!
	if (src_byte_p != dst_byte_p)
	{
		
		// if src 
		if (src_byte_p < dst_byte_p)
		{
			// do a backward copy...

			// move pointers to end of memory space to be moved.
			src_byte_p += (n - 1);
			dst_byte_p += (n - 1);

			// move from high to low memory.
			for (x=n; x > 0; x--)
			{
				*dst_byte_p = *src_byte_p;
				dst_byte_p--;
				src_byte_p--;
			}
		}
		else
		{
			// do a forward copy
			// move from low to high memory.
			for (x=n; x > 0; x--)
			{
				*dst_byte_p = *src_byte_p;
				dst_byte_p++;
				src_byte_p++;
			}
		}               
	}
	return( dst );
}










//@DESC: memcpy function that uses huge pointers. This function uses the Borland memcpy function
//@DESC: as the initial pattern for creation.  Since the Borland memcpy does no overlap checking
//@DESC: this function does no overlap checking.  PROGRAMMERS TAKE NOTE: since this function uses 
//@DESC: 'huge' pointers, it cannot be optimized into assembler since the manipulation of huge
//@DESC: pointers depends on 'magic' that is done behind our back by the compiler and Windows. 
//@DESC: We could probably reverse engineer the way it is currently handled (up to a point), but any 
//@DESC: changes in the op. system/compiler would blow us out of the water.  
//@PGMR: RJK
//@CRDT: 961006

void huge * _FARFUNC memcpyHUGE(void huge *dst, const void huge *src, unsigned long n)
{

	// move in word fashion since we are OK with word alignment...
	unsigned int huge * 	mc_dst 		= (unsigned int huge *) dst ;
	unsigned int huge * 	mc_src		= (unsigned int huge *) src ;
	unsigned long			byte_move	= n & 1;
	unsigned long			mc_n			= n >> 1;

	while (mc_n>0)
	{
		*mc_dst = *mc_src;
		mc_dst++;
		mc_src++;
		mc_n--;
	}
	if (byte_move)
	{
		// cast back to byte and copy if this is the last one...
		* (unsigned char huge *) mc_dst = * (unsigned char huge *) mc_src;
	}
	return (dst);
}

						 

