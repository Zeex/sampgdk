#include "filterscript.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

// Copied from amxaux.c
static int AMXAPI aux_LoadProgram(AMX *amx, const char *filename, void *memblock)
{
	FILE *fp;
	AMX_HEADER hdr;
	int result, didalloc;

	/* open the file, read and check the header */
	if ((fp = fopen(filename, "rb")) == NULL)
		return AMX_ERR_NOTFOUND;
	fread(&hdr, sizeof hdr, 1, fp);
	amx_Align16(&hdr.magic);
	amx_Align32((uint32_t *)&hdr.size);
	amx_Align32((uint32_t *)&hdr.stp);
	if (hdr.magic != AMX_MAGIC) {
		fclose(fp);
		return AMX_ERR_FORMAT;
	} /* if */

	/* allocate the memblock if it is NULL */
	didalloc = 0;
	if (memblock == NULL) {
		if ((memblock = malloc(hdr.stp)) == NULL) {
			fclose(fp);
			return AMX_ERR_MEMORY;
		} /* if */
		didalloc = 1;
		/* after amx_Init(), amx->base points to the memory block */
	} /* if */

	/* read in the file */
	rewind(fp);
	fread(memblock, 1, (size_t)hdr.size, fp);
	fclose(fp);

	/* initialize the abstract machine */
	memset(amx, 0, sizeof *amx);
	result = amx_Init(amx, memblock);

	/* free the memory block on error, if it was allocated here */
	if (result != AMX_ERR_NONE && didalloc) {
		free(memblock);
		amx->base = NULL;									 /* avoid a double free */
	} /* if */

	return result;
}

// Copied from amxaux.c
static int AMXAPI aux_FreeProgram(AMX *amx)
{
	if (amx->base!=NULL) {
		amx_Cleanup(amx);
		free(amx->base);
		memset(amx,0,sizeof(AMX));
	} /* if */
	return AMX_ERR_NONE;
}

namespace unlimitedfs {

FilterScript::FilterScript()
	: loaded_(false)
{
}

FilterScript::FilterScript(const std::string &filename)
	: loaded_(false)
{
	Load(filename);
}

FilterScript::~FilterScript() {
	Unload();
}

bool FilterScript::Load(const std::string &filename) {
	if (!loaded_) {
		int err = aux_LoadProgram(&amx_, filename.c_str(), NULL);
		if (err == AMX_ERR_NONE) {
			loaded_ = true;
			return true;
		}
	}
	return false;
}

int FilterScript::Init(cell *retval) {
	int error, index;
	error = amx_FindPublic(&amx_, "OnFilterScriptInit", &index) == AMX_ERR_NONE;
	if (error != AMX_ERR_NONE) {
		error = amx_Exec(&amx_, retval, index) == AMX_ERR_NONE;
	}
	return error;
}

int FilterScript::Exit(cell *retval) {
	int error, index;
	error = amx_FindPublic(&amx_, "OnFilterScriptExit", &index) == AMX_ERR_NONE;
	if (error != AMX_ERR_NONE) {
		error = amx_Exec(&amx_, retval, index) == AMX_ERR_NONE;
	}
	return error;
}

bool FilterScript::Unload() {
	if (loaded_) {
		return aux_FreeProgram(&amx_) == AMX_ERR_NONE;
	}
	return false;
}

bool FilterScript::Exec(const char *name, bool default_retval) {
	int index = 0;
	if (amx_FindPublic(&amx_, name, &index) == AMX_ERR_NONE) {
		cell retval;
		if (amx_Exec(&amx_, &retval, index) == AMX_ERR_NONE) {
			return retval != 0;
		}
	}
	return default_retval;
}

} // namespace samp
