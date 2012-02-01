/*
 * displaylinkexception.h - wraps libdlo errors into exceptions
 *
 * Copyright (c) 2012 András Veres-Szentkirályi
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef DISPLAYLINKEXCEPTION_H
#define DISPLAYLINKEXCEPTION_H

#include "libdlo.h"
#include "dlo_defs.h"

#define OO_ERR(cmd) do { dlo_retcode_t __err = (cmd); if (__err != dlo_ok) throw DisplayLinkException(__err); } while(0)
#define OO_NERR(ptr) do { if (!(ptr)) throw DisplayLinkException(dlo_err_memory); } while (0)

class DisplayLinkException {

public:
	DisplayLinkException(const dlo_retcode_t retcode);
	const char* message() const;
protected:
	const dlo_retcode_t retcode;
};

class NoDisplayLinkFound {};

#endif // DISPLAYLINKEXCEPTION_H
