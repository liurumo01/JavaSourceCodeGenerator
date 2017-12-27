#include "common.h"

#include "string_utils.h"
#include "file_utils.h"

#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#define ERROR_GENERATE_BEAN_FAILED -11
#define ERROR_GENERATE_DAO_FAILED -12
#define ERROR_GENERATE_SERVICE_FAILED -13

int generate(struct project_config *obj);

#endif
