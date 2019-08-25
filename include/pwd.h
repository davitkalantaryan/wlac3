//
// file:			pwd.h
// created on:		2019 Aug 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2__pwd_h
#define WLAC2__pwd_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <.wlac_specific/redesigned/sys/types.h>

BEGIN_C_DECL2

struct passwd{
	char *pw_name;		/* Username.  */
	char *pw_passwd;		/* Password.  */
	uid_t pw_uid;		/* User ID.  */
	gid_t pw_gid;		/* Group ID.  */
	char *pw_gecos;		/* Real name.  */
	char *pw_dir;			/* Home directory.  */
	char *pw_shell;		/* Shell program.  */
};

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(getpwuid_needed)
WLAC_EXPORT struct passwd *getpwuid(uid_t uid);
#endif


END_C_DECL2

#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2__pwd_h
