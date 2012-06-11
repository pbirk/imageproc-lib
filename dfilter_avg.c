/*
 * Copyright (c) 2012, Regents of the University of California
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the University of California, Berkeley nor the names
 *   of its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Averaging filter using a circular buffer
 *
 * by Andrew Pullin
 *
 * v.0.1
 *
 * Revisions:
 *  Andrew Pullin   2012-5-28   Initial release.
 */

#include "dfilter_avg.h"
#include<stdlib.h>

//Creates a filter and returns a point.
//Caller should check for NULL returns.
void filterAvgCreate(filterAvgInt_t* filt, unsigned int length){
	filt->data = calloc(length, sizeof(int)); //Initialize data to 0
	filt->windowLen = length;
	filt->index = 0;
}

//Add a value to the circular buffer, incrementing index
void filterAvgUpdate(filterAvgInt_t* filt, int newval){
	filt->data[filt->index] = newval;
	filt->index = (filt->index + 1) % filt->windowLen;
}

//Calculate and return average value;
//TODO: more efficient calculation? DSP? delta?
int filterAvgCalc(filterAvgInt_t* filt){
	int i;
	long acc = 0;
	for(i = 0; i < filt->windowLen; i++){
		acc += filt->data[i];
	}
	return acc/(filt->windowLen); //Integer division
}
