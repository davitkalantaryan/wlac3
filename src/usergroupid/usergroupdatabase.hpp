
// usergroupdatabase.hpp
// 2018 Jan 02

#ifndef __usergroupdatabase_hpp__
#define __usergroupdatabase_hpp__

//#include "unix_like_user_group_header.h"
#include "util/common_hashtbl.hpp"
//#include "util/common_list.hpp"



class UserGroupDatabase
{
public:
	UserGroupDatabase();
	~UserGroupDatabase();

	int get_unix_user_group_idCls(enum INPUT_PARAMETER accessType,struct SUserDetails* a_usr);


private:
	//common::List<struct SUserDetails*>		m_list;
	common::HashTbl<struct SUserDetails*>	m_hashByUserName;
	//common::HashTbl<struct SUserDetails*>	m_hashByGroupName;
	common::HashTbl<struct SUserDetails*>	m_hashByUserId;
	//common::HashTbl<struct SUserDetails*>	m_hashByGroupId;
	//static DAVIT_CLASSES::ReadWriteLock	s_Lock;
};


#endif  // #ifndef __usergroupdatabase_hpp__
