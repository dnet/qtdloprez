#include "displaylinkadapter.h"
#include "displaylinkexception.h"
#include <string.h>
#include <stdlib.h>

dlo_bmpflags_t DisplayLinkAdapter::flags = { 0 };

DisplayLinkAdapter::DisplayLinkAdapter() {
	dlo_init_t ini_flags = { 0 };
	dlo_claim_t cnf_flags = { 0 };

	OO_ERR(dlo_init(ini_flags));
	uid = dlo_claim_first_device(cnf_flags, 0);
	if (!uid) throw NoDisplayLinkFound();

	setPreferredMode();
}

uint16_t DisplayLinkAdapter::height() const {
	return mode_info->view.height;
}

uint16_t DisplayLinkAdapter::width() const {
	return mode_info->view.width;
}

uint8_t DisplayLinkAdapter::bpp() const {
	return mode_info->view.bpp;
}

uint8_t DisplayLinkAdapter::refresh() const {
	return mode_info->refresh;
}

void DisplayLinkAdapter::setMode(uint16_t width, uint16_t height, uint8_t bpp, uint8_t refresh) {
	dlo_mode_t mode;

	mode.view.width = width;
	mode.view.height = height;
	mode.view.bpp = bpp;
	mode.view.base = 0;
	mode.refresh = refresh;

	setModePointer(&mode);
}

void DisplayLinkAdapter::setPreferredMode() {
	/* Select the monitor's preferred mode, based on EDID */
	setModePointer(NULL);
}

void DisplayLinkAdapter::setModePointer(const dlo_mode_t *mode) {
	OO_ERR(dlo_set_mode(uid, mode));

	/* Read current mode information */
	mode_info = dlo_get_mode(uid);
	OO_NERR(mode_info);
}

DisplayLinkAdapter::~DisplayLinkAdapter() {
	dlo_final_t fin_flags = { 0 };

	if (uid) dlo_release_device(uid);
	dlo_final(fin_flags);
}

void DisplayLinkAdapter::displayImage(const QImage &image) {
	const dlo_view_t *view = &(mode_info->view);
	dlo_dot_t dot;
	dlo_fbuf_t fbuf;

	OO_NERR(uid);

	fbuf.width  = image.width();
	fbuf.height = image.height();
	fbuf.stride = fbuf.width;
	fbuf.fmt = dlo_pixfmt_argb8888;

	dot.x = 0;

	if (view->height > fbuf.height) {
		dlo_rect_t rec;
		rec.origin.x = 0;
		rec.origin.y = 0;
		rec.width = view->width;

		dot.y = (view->height - fbuf.height) / 2;
		rec.height = dot.y;
		OO_ERR(dlo_fill_rect(uid, view, &rec, DLO_RGB(0, 0, 0)));

		rec.origin.y = fbuf.height + dot.y;
		rec.height = view->height - rec.origin.y;
		OO_ERR(dlo_fill_rect(uid, view, &rec, DLO_RGB(0, 0, 0)));
	} else {
		dot.y = 0;
	}

	fbuf.base = malloc(image.byteCount());
	OO_NERR(fbuf.base);
	memcpy(fbuf.base, image.bits(), image.byteCount());
	OO_ERR(dlo_copy_host_bmp(uid, flags, &fbuf, NULL, &dot));
	free(fbuf.base);
}
