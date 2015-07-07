#include "header.h"
static unsigned char basis_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64encode(const unsigned char *input, int input_length, unsigned char *output, int output_length)
{
	int	i = 0, j = 0;
	int	pad;

	assert(output_length >= (input_length * 4 / 3));

	while (i < input_length) {
        	pad = 3 - (input_length - i);
		if (pad == 2) {
           		output[j  ] = basis_64[input[i]>>2];
			output[j+1] = basis_64[(input[i] & 0x03) << 4];
		      	output[j+2] = '=';
			output[j+3] = '=';	
		} else if (pad == 1) {
			output[j  ] = basis_64[input[i]>>2];
            output[j+1] = basis_64[((input[i] & 0x03) << 4) | ((input[i+1] & 0xf0) >> 4)];
			output[j+2] = basis_64[(input[i+1] & 0x0f) << 2];
            output[j+3] = '=';
		} else{
			output[j  ] = basis_64[input[i]>>2];
			output[j+1] = basis_64[((input[i] & 0x03) << 4) | ((input[i+1] & 0xf0) >> 4)];
			output[j+2] = basis_64[((input[i+1] & 0x0f) << 2) | ((input[i+2] & 0xc0) >> 6)];
			output[j+3] = basis_64[input[i+2] & 0x3f];}					
            i += 3;															
            j += 4;																									      
      }
    output[j]=0;  
         return j;																								
}
