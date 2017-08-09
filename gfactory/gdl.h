#ifndef  GDL_H
#define  GDL_H 1

// this code is based on this tutorial:
// https://0x00sec.org/t/c-dynamic-loading-of-shared-objects-at-runtime/1498

// c++ plugin loading functions
#include <dlfcn.h>

typedef void* dlhandle;

static dlhandle load_lib(const string& path);
static void close_lib(dlhandle handle);

/**
 * @struct DynamicLib
 * @brief  Structure to load dynamically symbols from a shared library
 */
// PRAGMA TODO: add verbosity option?
// add error if DL is not found, with msg
struct DynamicLib {
	
	// default constructor
	DynamicLib() = default;
	
	string   path;    ///< filename base of the dynamic library
	dlhandle handle;  ///< posix handle of the dynamic library

	/**
	 * @param p name of the dynamic library
	 */
	DynamicLib(string p) : path(p), handle(nullptr) {
	//	cout << " Loading DL " << p << endl;
		handle = load_lib(p);
	}
	
	~DynamicLib() {
		if (handle != nullptr)
			close_lib(handle);
//		cout << " Closing DL " << path << endl;
	}
};


static dlhandle load_lib(const string& path) {

	return dlopen(path.data() , RTLD_NOW);
	// get a handle to the lib, may be nullptr.
	// RTLD_NOW ensures that all the symbols are resolved immediately. This means that
	// if a symbol cannot be found, the program will crash now instead of later.
}

static void close_lib(dlhandle handle) {
	dlclose(handle);
}

#endif
