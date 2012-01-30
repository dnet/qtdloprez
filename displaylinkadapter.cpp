#include "displaylinkadapter.h"
#include <string.h>
#include <stdlib.h>

dlo_bmpflags_t DisplayLinkAdapter::flags = { 0 };

DisplayLinkAdapter::DisplayLinkAdapter() {
	dlo_init_t ini_flags = { 0 };
	dlo_claim_t cnf_flags = { 0 };

	if (dlo_init(ini_flags) != dlo_ok) return;
	uid = dlo_claim_first_device(cnf_flags, 0);
	if (!uid) return;

	/* Select the monitor's preferred mode, based on EDID */
	if (dlo_set_mode(uid, NULL) != dlo_ok) return;

	/* Read current mode information */
	mode_info = dlo_get_mode(uid);
	if (!mode_info) return;
}

uint16_t DisplayLinkAdapter::height() const {
	return mode_info->view.height;
}

uint16_t DisplayLinkAdapter::width() const {
	return mode_info->view.width;
}

DisplayLinkAdapter::~DisplayLinkAdapter() {
	dlo_final_t fin_flags = { 0 };

	if (uid) dlo_release_device(uid);
	dlo_final(fin_flags);
}

bool DisplayLinkAdapter::displayImage(const QImage &image) {
	const dlo_view_t *view = &(mode_info->view);
	dlo_dot_t dot;
	dlo_fbuf_t fbuf;

	if (!uid) return false;

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
		if (dlo_fill_rect(uid, view, &rec, DLO_RGB(0, 0, 0)) != dlo_ok) return false;

		rec.origin.y = fbuf.height + dot.y;
		rec.height = view->height - rec.origin.y;
		if (dlo_fill_rect(uid, view, &rec, DLO_RGB(0, 0, 0)) != dlo_ok) return false;
	} else {
		dot.y = 0;
	}

	fbuf.base = malloc(image.byteCount());
	if (!fbuf.base) return false;
	memcpy(fbuf.base, image.bits(), image.byteCount());
	if (dlo_copy_host_bmp(uid, flags, &fbuf, NULL, &dot) != dlo_ok) return false;
	free(fbuf.base);

	return true;
}
