//
// file:			unistd.h
// created on:		2019 Aug 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2__unistd_h
#define WLAC2__unistd_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <.wlac_specific/redesigned/sys/types.h>

#ifndef MAX_USER_NAME_LEN_MIN1
#define	MAX_USER_NAME_LEN_MIN1		127
#endif

#ifndef MAX_NUMBER_OF_GROUPS
#define	MAX_NUMBER_OF_GROUPS		32
#endif

BEGIN_C_DECL2

enum INPUT_PARAMETER { UGID_USERNAME, UGID_USERID };

struct SUserDetails {

	union {
		const char* userName;
		char*		userNamePrivate;  // used by lib
	}un;
	union {
		const char* groupName;
		char*		groupNamePrivate;  // used by lib
	}gn;
	uid_t		m_UID;
	gid_t		m_GID;
	int			m_nNgroups;
	gid_t		m_vGroups[MAX_NUMBER_OF_GROUPS];
};

#if defined(getuid_needed)
USERGROUPID_EXPORT2 uid_t getuid(void);
#endif

//#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(getgid_needed)
#if defined(getgid_needed)
gid_t getgid(void);
#endif

#if defined(geteuid_needed)
USERGROUPID_EXPORT2 uid_t geteuid(void);
#endif

#if defined(getegid_needed)
USERGROUPID_EXPORT2 gid_t getegid(void);
#endif

#if defined(getgroups_needed)
USERGROUPID_EXPORT2 int getgroups(int gidsetsize, gid_t grouplist[]);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(WLAC2_SetLibraryCleaning_needed)
WLAC_EXPORT int WLAC2_SetLibraryCleaning(int isFreeLibraryCalled);
#endif

END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2__unistd_h
