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
