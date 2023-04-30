/*
 Filename: bitstream.cpp
 Purpose:  Defines member functions of bitstream class. 
*/
#include "stdafx.h"
#include "bitstream.h"

// *******************************************************************************
// Function Name: Constructor for bitstream class
// Purpose:				Initialise all member data to 0.
// Explicit Return Data: None
// Implicit Return Data: None
// Arrays Affected:			 None
// Notes:		
// *******************************************************************************
bitstream::bitstream()
{
	bstream=write_byte=read_byte=NULL;
	read_bit=write_bit=0;
	bstream_length.byte=0;
	bstream_length.bit=0;
	reset_retrieved_long();
}

// *******************************************************************************
// Function Name: attach_char_array
// Purpose:				Attach a character array to be used to read/write bits
// Explicit Return Data: None
// Implicit Return Data: None
// Arrays Affected:			 bstream points to array
// Notes:								Array must be allocated to source_length length.
// *******************************************************************************
void bitstream::attach_char_array(unsigned char *array, bytebit source_length)
{
	bstream=read_byte=write_byte=array;
	bstream_length=source_length;
}

void bitstream::attach_char_array(unsigned char *array, unsigned long source_length)
{
	bstream=read_byte=write_byte=array;
	bstream_length.byte=source_length;
	bstream_length.bit=0;
}

// *******************************************************************************
// Function Name: reached_read_end
// Purpose:				Find out if read_byte/bit pointer has reached end of attached
//								char array
// Explicit Return Data: SUCCESS if read_byte/bit reached end of bitstream
//											 FAILURE otherwise
// Implicit Return Data: None
// Arrays Affected:			 None
// Notes:								 None
// *******************************************************************************
status bitstream::reached_read_end()
{
	if ((unsigned int)(read_byte-bstream)>=bstream_length.byte && 
		  read_bit>=bstream_length.bit)
		return SUCCESS;
	else
		return FAILURE;
}

// *******************************************************************************
// Function Name: reached_write_end
// Purpose:				Find out if write_byte/bit pointer has reached end of attached
//								char array
// Explicit Return Data: SUCCESS if write_byte/bit reached end of bitstream
//											 FAILURE otherwise
// Implicit Return Data: None
// Arrays Affected:			 None
// Notes:								 None
// *******************************************************************************
status bitstream::reached_write_end()
{
	if ((unsigned int)(write_byte-bstream)>=bstream_length.byte && 
		  write_bit>=bstream_length.bit)
		return SUCCESS;
	else
		return FAILURE;
}

// *******************************************************************************
// Function Name: reset_read_write
// Purpose:				Set read/write byte/bit pointers to beginning of char array.
// Explicit Return Data: None
// Implicit Return Data: None
// Arrays Affected:			 None
// Notes:								 None
// *******************************************************************************
void bitstream::reset_read_write()
{
	read_byte=write_byte=bstream;
	read_bit=write_bit=0;
}

// *******************************************************************************
// Function Name: wipe_clean
// Purpose:				Initialises attached char array to zero.
// Explicit Return Data: None
// Implicit Return Data: None
// Arrays Affected:			 bstream array.
// Notes:								 None
// *******************************************************************************
void bitstream::wipe_clean()
{
	unsigned long clear_length;
	if (bstream_length.bit==0)
		clear_length=bstream_length.byte;
	else
		clear_length=bstream_length.byte+1;
	for (unsigned int i=0; i<bstream_length.byte; i++)
		*(bstream+i)=0;
}

// *******************************************************************************
// Function Name: reset_retrieved_long
// Purpose:				Initialises retrieved_long to zero in preparation for reading
//								new bit pattern from stream.
// Explicit Return Data: None
// Implicit Return Data: None
// Arrays Affected:			 None
// Notes:								 None
// *******************************************************************************
void bitstream::reset_retrieved_long()
{ retrieved_long=0; }

// *******************************************************************************
// Function Name: get_read_length
// Purpose:				returns number of bytes read_byte has moved along bstream,
//								and next bit to be read from.
// Explicit Return Data: read_byte/read_bit in bytebit struct
// Implicit Return Data: None
// Arrays Affected:			 None
// Notes:								 None
// *******************************************************************************
bytebit bitstream::get_read_length()
{
	bytebit return_value;
	return_value.byte=read_byte-bstream;
	return_value.bit=read_bit;
	return return_value;
}

// *******************************************************************************
// Function Name: get_write_length
// Purpose:				returns number of bytes write_byte has moved along bstream,
//								and next bit to be written to.
// Explicit Return Data: write_byte/write_bit in bytebit struct
// Implicit Return Data: None
// Arrays Affected:			 None
// Notes:								 None
// *******************************************************************************
bytebit bitstream::get_write_length()
{
	bytebit return_value;
	return_value.byte=write_byte-bstream;
	return_value.bit=write_bit;
	return return_value;
}

// *******************************************************************************
// Function Name: append_bits
// Purpose:				Appends a number of bits from source to the bitstream starting at
//								the byte/bit pointed to by read_byte/read_bit.
// Explicit Return Data: FAILURE if overwritten end of attached char array
//											 FAILURE if no_of_bits>32.
//											 SUCCESS otherwise.
// Implicit Return Data: None
// Arrays Affected:			 bstream array.
// Notes:								 None
// *******************************************************************************
status bitstream::append_bits(unsigned long source, unsigned char no_of_bits)
{
	// Check for end of attached char array and that no_of_bits not out of range
	if (write_byte>=bstream+bstream_length.byte && write_bit>=bstream_length.bit
			|| no_of_bits>32)
		return FAILURE;

	// one_bit_mask: Masks out a single bit in source, starting with msb.
	unsigned long one_bit_mask=(1<<no_of_bits-1);
	// Write all no_of_bits lsb in source to bitstream
	do
	{
		if (source & one_bit_mask)							// If the current bit is 1
			*write_byte|=1 << write_bit;					// write a 1 into write_byte
		else																		// Else
			*write_byte&=~(1 << write_bit);				// write a 0 into write_byte

		// Move write_byte/write_bit pointers to next bit in char array
		if (++write_bit == 8)										// Increment write_bit, reset to 0 if 8
		{
			write_bit=0;
			write_byte++;													// And increment write_byte
			// Check for exceeding the char array bounds.
			if (write_byte>=bstream+bstream_length.byte && write_bit>=bstream_length.bit)
				return FAILURE;
		}
	}
	while (one_bit_mask>>=1);				// Stop when shifted reaches 0 and done all bits
	return SUCCESS;
}

status bitstream::append_word(unsigned int source)
{
	if (write_bit!=0)			// append only on byte boundary
		return FAILURE;

	*(write_byte++)=source;
	*(write_byte++)=source >> 8;

	return SUCCESS;
}

unsigned int bitstream::high_bit(unsigned long bit_number)
{
/*
	unsigned long byte_count=bit_number >> 3;			// same as divide by 8
	unsigned long bit_count=bit_number % 8;
	unsigned char mask=1 << bit_count;
	return (*(bstream+byte_count) & mask)>0;
*/
	return ((*(bstream + (bit_number>>3))) & (1<<(bit_number%8)))  >0;

}

void bitstream::set_bit_1(unsigned long bit_number)
{
/*
	unsigned long byte_count=bit_number >> 3;			// same as divide by 8
	unsigned long bit_count=bit_number % 8;
	unsigned char mask=1 << bit_count;
	*(bstream+byte_count)|=mask;
*/
	(*(bstream+(bit_number>>3))) |= (1<<(bit_number%8));
}

void bitstream::set_bit_0(unsigned long bit_number)
{
/*
	unsigned long byte_count=bit_number >> 3;			// same as divide by 8
	unsigned long bit_count=bit_number % 8;
	unsigned char mask=1 << bit_count;
	*(bstream+byte_count)&=~mask;
*/
	(*(bstream+(bit_number>>3))) &= (~(1<<(bit_number%8)));
}


// *******************************************************************************
// Function Name: retrieve_bit
// Purpose:				Shift retrieved_long one bit to left, store in lsb next bit
//								in bitstream, and retrieved_long.
// Explicit Return Data: FAILURE if reading beyond end of attached char array
//											 SUCCESS otherwise.
// Implicit Return Data: retrieved_long value after appending next bit.
// Arrays Affected:			 None
// Notes:					Before reading a new bit pattern, reset_retrieved_long must be
//								called to set retrieved_long to zero.
// *******************************************************************************
status bitstream::retrieve_bit(unsigned long &target)
{
	// Check for end of char array
	if (read_byte>=bstream+bstream_length.byte && read_bit>=bstream_length.bit)
	{
		target=0;
		return FAILURE;	
	}
	retrieved_long<<=1;												// Shift Retrieved Long by 1 bit to left
	// If the currently examined bit is one, append one to retrieved_long
	if (*read_byte & (1 << read_bit))
		retrieved_long|=1;

	if (++read_bit == 8)									// increment read_bit, reset to 0 if 8
	{
		read_bit=0;
		read_byte++;													// and increment read_byte
	}
	target=retrieved_long;
	return SUCCESS;
}

status bitstream::retrieve_bool(bool &result)
{
	if (read_byte>=bstream+bstream_length.byte && read_bit>=bstream_length.bit)
		return FAILURE;	

	if (*read_byte & (1 << read_bit))
		result=true;
	else
		result=false;

	if (++read_bit == 8)									// increment read_bit, reset to 0 if 8
	{
		read_bit=0;
		read_byte++;													// and increment read_byte
	}
	return SUCCESS;
}


