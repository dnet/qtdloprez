#include "displaylinkexception.h"

DisplayLinkException::DisplayLinkException(const dlo_retcode_t err) : retcode(err) {}

const char* DisplayLinkException::message() const {
	return dlo_strerror(retcode);
}
