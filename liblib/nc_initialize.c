/*********************************************************************
 *   Copyright 2010, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "config.h"

#ifdef USE_PARALLEL
#include <mpi.h>
#endif

#include "ncdispatch.h"

extern void nc_finalize(void);

extern int NC3_initialize(void);
extern int NC3_finalize(void);

#ifdef USE_NETCDF4
#include "nc4internal.h"
extern int NC4_initialize(void);
extern int NC4_finalize(void);
#endif

#ifdef ENABLE_DAP2
extern int NCD2_initialize(void);
extern int NCD2_finalize(void);
#endif

#ifdef ENABLE_DAP4
extern int NCD4_initialize(void);
extern int NCD4_finalize(void);
#endif

#ifdef USE_PNETCDF
extern int NCP_initialize(void);
extern int NCP_finalize(void);
#endif

#ifdef USE_HDF4
extern int HDF4_initialize(void);
extern int HDF4_finalize(void);
#endif

#ifdef _MSC_VER
#include <io.h>
#include <fcntl.h>
#endif

int NC_argc = 1;
char* NC_argv[] = {"nc_initialize",NULL};

int NC_initialized = 0;
int NC_finalized = 1;

/**
This procedure invokes all defined
initializers, and there is an initializer
for every known dispatch table.
So if you modify the format of NC_Dispatch,
then you need to fix it everywhere.
It also initializes appropriate external libraries.
*/

int
nc_initialize()
{
    int stat = NC_NOERR;

    if(NC_initialized) return NC_NOERR;
    NC_initialized = 1;
    NC_finalized = 0;

#ifdef _MSC_VER
    /* Force binary mode */
    _set_fmode(_O_BINARY);
#endif

    /* Do general initialization */
    if((stat = NCDISPATCH_initialize())) goto done;

    /* Initialize each active protocol */
    if((stat = NC3_initialize())) goto done;
#ifdef ENABLE_DAP
    if((stat = NCD2_initialize())) goto done;
#endif
#ifdef ENABLE_DAP4
    if((stat = NCD4_initialize())) goto done;
#endif
#ifdef USE_PNETCDF
    if((stat = NCP_initialize())) goto done;
#endif
#ifdef USE_HDF4
    if((stat = HDF4_initialize())) goto done;
#endif
#ifdef USE_NETCDF4
    if((stat = NC4_initialize())) goto done;
    stat = NC4_fileinfo_init();
#endif /* USE_NETCDF4 */

#ifdef HAVE_ATEXIT
    /* If we have atexit(), then use it to invoke nc_finalize */
    if(atexit(nc_finalize))
	fprintf(stderr,"atexit failed\n");
#endif

done:
    return stat;
}

/**
This procedure invokes all defined
finalizers, and there should be one
for every known dispatch table.
So if you modify the format of NC_Dispatch,
then you need to fix it everywhere.
It also finalizes appropriate external libraries.
*/

void
nc_finalize(void)
{
    int stat = NC_NOERR;

    if(NC_finalized) goto done;
    NC_initialized = 0;
    NC_finalized = 1;

    /* Finalize each active protocol */

#ifdef ENABLE_DAP2
    if((stat = NCD2_finalize())) goto done;
#endif
#ifdef ENABLE_DAP4
    if((stat = NCD4_finalize())) goto done;
#endif

#ifdef USE_PNETCDF
    if((stat = NCP_finalize())) goto done;
#endif

#ifdef USE_NETCDF4
    if((stat = NC4_finalize())) goto done;
#endif /* USE_NETCDF4 */

    if((stat = NC3_finalize())) goto done;

    /* Do general finalization */
    if((stat = NCDISPATCH_finalize())) goto done;

done:
    if(stat) fprintf(stderr,"nc_finalize failed\n");
    return;
}
