
// unix_like_user_group_functions.cpp
// 2017 Dec 30

//#include "stdafx.h"
//#include "common_include_for_wlac_sources.h"
//#include "unix_like_user_group_header.h"
#include <unistd.h>
#include "usergroupdatabase.hpp"
#include <memory.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <pwd.h>

#ifndef LIKELY
#define LIKELY(_x) (_x)
#endif


static int
get_uid_gid_ggroup_witch_cashing(
	INPUT_PARAMETER accessType,
	struct SUserDetails* a_usr);

__BEGIN_C_DECLS

#define RESOURCE_BUF_LEN_MIN1	1023

void InitUserGroupDetails(struct SUserDetails* a_usr)
{
	memset(a_usr, 0, sizeof(struct SUserDetails));
}


USERGROUPID_EXPORT2 uid_t geteuid(void)
{
	struct SUserDetails aData;
	char vcUserName[RESOURCE_BUF_LEN_MIN1 + 1];
	DWORD	dwBufLen = RESOURCE_BUF_LEN_MIN1;
	int nReturn;

	vcUserName[RESOURCE_BUF_LEN_MIN1] = 0;
	if (LIKELY(GetUserNameA(vcUserName, &dwBufLen))) {
		InitUserGroupDetails(&aData);
		aData.un.userName = vcUserName;
		nReturn = get_uid_gid_ggroup_witch_cashing(UGID_USERNAME, &aData);
		if (nReturn) {
			//errno = nReturn; // This function is always successfull // https://linux.die.net/man/2/getuid 
			// should be returnd windows ssid (later)
			return 0;
		}
		return aData.m_UID;
	}

	return 0;
}


USERGROUPID_EXPORT2 uid_t getuid(void)
{
	return geteuid();
}


USERGROUPID_EXPORT2 gid_t getegid(void)
{
	struct SUserDetails aData;
	char vcUserName[RESOURCE_BUF_LEN_MIN1+1];
	DWORD	dwBufLen= RESOURCE_BUF_LEN_MIN1;
	int nReturn;

	vcUserName[RESOURCE_BUF_LEN_MIN1]=0;
	if( LIKELY(GetUserNameA(vcUserName,&dwBufLen))){
		InitUserGroupDetails(&aData);
		aData.un.userName = vcUserName;
		nReturn = get_uid_gid_ggroup_witch_cashing(UGID_USERNAME,&aData);
		if(nReturn){
			//errno = nReturn; // This function is always successfull // https://linux.die.net/man/2/getgid 
			// should be returnd windows ssid (later)
			return 0;
		}
		return aData.m_GID;
	}

	return 0;
}


USERGROUPID_EXPORT2 gid_t getgid(void)
{
	return getegid();
}

#define PW_AND_PASW_LEN		1023

static char s_vsPw_name  [PW_AND_PASW_LEN+1] = { 0 };
static char s_vsPw_passwd[PW_AND_PASW_LEN+1] = { 0 };
static char s_vsPw_gecos [PW_AND_PASW_LEN+1] = { 0 };
static char s_vsPw_dir   [PW_AND_PASW_LEN+1] = { 0 };
static char s_vsPw_shell [PW_AND_PASW_LEN+1] = { 0 };

static struct passwd	s_passwd = { s_vsPw_name,s_vsPw_passwd,0,0,s_vsPw_gecos,s_vsPw_dir,s_vsPw_shell };

USERGROUPID_EXPORT2 struct passwd *getpwuid(uid_t a_uid)
{
	DWORD dwBufLen = PW_AND_PASW_LEN;
	s_passwd.pw_uid = a_uid;
	GetUserNameA(s_passwd.pw_name, &dwBufLen);
	return &s_passwd;
}


//
// https://linux.die.net/man/3/getgrouplist 
//
USERGROUPID_EXPORT2 int getgrouplist(const char *a_user, gid_t a_group, gid_t *a_groups, int *a_ngroups)
{
	struct SUserDetails aData;
	int nReturn, i,nForLoop,nGroupIdIncluded;

	InitUserGroupDetails(&aData);

	aData.un.userName = a_user;
	nReturn = get_uid_gid_ggroup_witch_cashing(UGID_USERNAME,&aData);
	if (nReturn) {*a_ngroups = 0;return 0;}  // error 

	if (aData.m_nNgroups>(*a_ngroups)){nReturn = -1;nForLoop=(*a_ngroups);}
	else{nReturn=aData.m_nNgroups;nForLoop=aData.m_nNgroups;}

	nGroupIdIncluded = 0;
	for(i=0;i<nForLoop;++i){
		a_groups[i] = aData.m_vGroups[i];
		if(a_groups[i]== a_group){nGroupIdIncluded=1;}
	}

	if(nGroupIdIncluded==0){
		if((aData.m_nNgroups+1)>(*a_ngroups)){nReturn = -1;}
		else {a_groups[aData.m_nNgroups]=a_group;}
		++aData.m_nNgroups;
	}

	(*a_ngroups) = aData.m_nNgroups;

	return aData.m_nNgroups;
}


//
// https://linux.die.net/man/2/getgroups 
//
USERGROUPID_EXPORT2 int getgroups(int a_size, gid_t a_list[])
{
	struct SUserDetails aData;
	char vcUserName[RESOURCE_BUF_LEN_MIN1+1];
	DWORD	dwBufLen= RESOURCE_BUF_LEN_MIN1;

	vcUserName[RESOURCE_BUF_LEN_MIN1]=0;
	if( LIKELY(GetUserNameA(vcUserName,&dwBufLen))){
		InitUserGroupDetails(&aData);
		aData.un.userName = vcUserName;
		if (get_uid_gid_ggroup_witch_cashing(UGID_USERNAME,&aData)){errno=EFAULT;return -1;}  // error 
		//if (aData.m_nNgroups>a_size) { errno= EINVAL; return -1; } // error prone
		if(a_size>aData.m_nNgroups){a_size=aData.m_nNgroups;}
		if(a_size){memcpy(a_list,aData.m_vGroups,sizeof(gid_t)*a_size);}
		return aData.m_nNgroups;
	}

	return -1;
}


__END_C_DECLS

static UserGroupDatabase	s_dataBase;

static int 
get_uid_gid_ggroup_witch_cashing(
	INPUT_PARAMETER a_accessType,
	struct SUserDetails* a_usr)
{

	return s_dataBase.get_unix_user_group_idCls(a_accessType,a_usr);
}
