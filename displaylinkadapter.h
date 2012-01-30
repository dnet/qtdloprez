#ifndef DISPLAYLINKADAPTER_H
#define DISPLAYLINKADAPTER_H

#include "libdlo.h"
#include "dlo_defs.h"
#include <QImage>

class DisplayLinkAdapter {

public:
	DisplayLinkAdapter();
	~DisplayLinkAdapter();
	bool displayImage(const QImage &image);
	uint16_t width() const;
	uint16_t height() const;

protected:
	dlo_dev_t uid;
	dlo_mode_t *mode_info;
	static dlo_bmpflags_t flags;
};

#endif // DISPLAYLINKADAPTER_H