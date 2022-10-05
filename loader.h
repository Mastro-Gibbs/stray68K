#ifndef __LOADER_H__68000
#define __LOADER_H__68000

#include "motorolatypes.h"
#include "utils.h"


/**
 * @brief load_bytecode
 * @param filename, file to load
 * @return last write ram address
 */
generic_u32_t load_executable(char *filename);



#endif // __LOADER_H__68000
