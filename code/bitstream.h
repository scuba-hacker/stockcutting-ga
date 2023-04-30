/*
	Filename:	bistream.h
	Purpose:	Declares bitstream class used to read and write streams of bit patterns (max
						length 31 bits) stored in a character array. Also declares status_type, status,
						bytebit_struct and bytebit data types - required for implementing bitstream.
*/
#include <iostream.h>
#include "define_vars.h"

#ifndef _bitstream_h
#define _bitstream_h
struct bytebit_struct
{
	unsigned long byte;
	unsigned int bit;
};	typedef struct bytebit_struct bytebit;

class bitstream
{
	public:
		unsigned char *bstream;						// Pointer to externally allocated memory
		bytebit bstream_length;						// Length of allocated memory
		unsigned char *write_byte;				// Points to next byte to write to
		unsigned char write_bit;					// Points to next bit to write to
		unsigned char *read_byte;					// Points to next byte to read from
		unsigned char read_bit;						// Points to next bit to read from

		unsigned long retrieved_long;			// Stores last read bit pattern

	// Default Constructor - initialise all member data to 0
	bitstream();
	
	// This function attaches some allocated memory to use for reading/writing bit patterns
	void attach_char_array(unsigned char *array, bytebit source_length);
	void attach_char_array(unsigned char *array, unsigned long source_length);
	
	// This function sets the read/write byte/bit pointers to the start of the character array
	void reset_read_write();
	
	// This function initialises the attached character array to zero.
	void wipe_clean();

	// This function appends the 'no_of_bits' Least Significant Bits of 'source' to the
	// attached character array.
	status append_bits(unsigned long source, unsigned char no_of_bits);

	status append_word(unsigned int source);

	unsigned int high_bit(unsigned long bit_number);
	void set_bit_1(unsigned long bit_number);
	void set_bit_0(unsigned long bit_number);

	// This function gets the next read bit from the attached character array, and appends it
	// to the 'retrieved_long' data member which is returned through 'target'.
	status retrieve_bit(unsigned long &target);
	status retrieve_bool(bool &result);

	// This function sets retrieved_long to zero in preparation for reading a new bit pattern
	// from the attached character array.
	void reset_retrieved_long();
	
	// This function gets the current offset of the write byte and write bit pointers from 
	// the start of the attached character array.
	bytebit get_write_length();
	
	// This function gets the current offset of the read byte and read bit pointers from 
	// the start of the attached character array.
	bytebit get_read_length();
	
	// These functions return ERROR if the appropriate byte pointer has reached the end of
	// the attached character array, otherwise SUCCESS is returned.
	status reached_read_end();
	status reached_write_end();
};
#endif