/*
 * displaylinkadapter.h - wraps libdlo functionality into an object
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

#ifndef DISPLAYLINKADAPTER_H
#define DISPLAYLINKADAPTER_H

#include "libdlo.h"
#include "dlo_defs.h"
#include <QImage>

class DisplayLinkAdapter {

public:
	DisplayLinkAdapter();
	~DisplayLinkAdapter();
	void displayImage(const QImage &image);
	void setMode(uint16_t width, uint16_t height, uint8_t bpp, uint8_t refresh);
	void setPreferredMode();
	uint16_t width() const;
	uint16_t height() const;
	uint8_t bpp() const;
	uint8_t refresh() const;

protected:
	dlo_dev_t uid;
	dlo_mode_t *mode_info;
	static dlo_bmpflags_t flags;
	void setModePointer(const dlo_mode_t *mode);
};

#endif // DISPLAYLINKADAPTER_H
