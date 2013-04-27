/***************************************************************************************************
 
 C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	韩欣 (han.xin@datatom.com)
	
Creating Time:
	2012-8-10
***************************************************************************************************/

#ifndef __NETWORK_MESG_HEADER_H__
#define __NETWORK_MESG_HEADER_H__

///////////////////////////////////////////////////////////////////////////////////////////
// 网络通信协议
//
// 请不要随意修改
//
#define NETWORK_BASE_ID							0x00000000
//
// 无效消息包类型 == 0
//
#define NETWORK_INVALID_PACKET						(NETWORK_BASE_ID + 0)
//
// 交互通信，消息组
#define	IDML_COMMUNICAT_BASE						(NETWORK_BASE_ID + 0)	/* 1 ~ 1000*/
//
// 文件读写
#define	IDML_FILE_COMM_BASE							(NETWORK_BASE_ID + 1000) /* 1001 ~ 2000 */
//
// 用户、组 配额
#define	IDML_USER_COMM_BASE							(NETWORK_BASE_ID + 2000) /* 2001 ~ 3000 */
//
// 标签操作
#define	IDML_LABLE_COMM_BASE						(NETWORK_BASE_ID + 3000) /* 3001 ~ 4000 */
//
// 历史版本
#define	IDML_HISTORY_COMM_BASE						(NETWORK_BASE_ID + 4000) /* 4001 ~ 5000 */
//
// 共享
#define IDML_SHARE_COMM_BASE                        (NETWORK_BASE_ID + 5000) /*5001 ~ 6000 */
//
// 全文检索
#define IDML_FULLTEXT_COMM_BASE                     (NETWORK_BASE_ID + 6000) /*6001 ~ 7000 */
//
// Metadata
#define IDML_META_COMM_BASE                    		(NETWORK_BASE_ID + 7000) /*7001 ~ 8000 */




///////////////////////////////////////////////////////////////////////////////////////////
// 登录

enum IDML_MSG_NETWORK {

	//
	// 网络连接
	NETWORK_CONNECT_PACKET = IDML_COMMUNICAT_BASE + 1,		// 1
	
	// 客户端登录
	IDML_CLIENT_LOGIN,
	
	// 退出登录
	IDML_CLIENT_LOGOUT,
	
	// 查询在线服务器列表
	IDML_LIST_ONLINE_SERVERS,
	
	// 测试网络性能
	IDML_TEST_PERFORMANCE,
	
	// 添加监控事件
	IDML_ADD_TRACE_EVENT,
	
	// 查询文件监控 事件
	IDML_QUERY_FILE_TRACE,
	
	// 测试网络性能 （通过BSON打包）
	IDML_TEST_PERFORMANCE_BSON,
};


///////////////////////////////////////////////////////////////////////////////////////////
// 文件、文件夹操作
//

enum IDML_MSG_FILE {

	//
	// 打开文件
	NETWORK_BEGEIN_OBJECT = IDML_FILE_COMM_BASE + 1,
	
	// 写数据
	NETWORK_WRITE_FILE_BLOCK,
	
	// 读数据
	NETWORK_READ_FILE_BLOCK,
	
	// 关闭文件
	NETWORK_END_OBJECT,

	//移动文件
	IDML_MOVE_FILE,
	
	//创建文件
	IDML_CREATE_FILE,

	// 删除文件
	IDML_REMOVE_FILE,
	
	// 判断是否存在
	IDML_IF_EXISTS_FILE,

	// 截断文件
	IDML_TRUNCATE_FILE,
	
	// 刷新缓存
	IDML_FLUSH_FILE,

	// 获取文件大小
	IDML_GET_FILE_SIZE,

	// 查询文件信息
	IDML_QUERY_FILE_INFO,
	
	//更新文件信息
	IDML_UPDATE_FILE_INFO,
	
	// 从回收站彻底删除文件
	IDML_DELETE_FROM_RECYCLE,
	
	//清空回收站
	IDML_CLEAR_RECYCLE,
	
	//从回收站恢复某个文件或文件夹
	IDML_RECOVER_FROM_RECYCLE,
	
	//查找文件
	IDML_SEARCH_FILE,
	
	//列举回收站所有删除的文件文件夹
	IDML_LIST_RECYCLE,
};


///////////////////////////////////////////////////////////////////////////////////////////
// 历史版本
//

enum IDML_MSG_HISTORY {

	//
	// 创建历史镜像
	IDML_NEW_VERSION = IDML_HISTORY_COMM_BASE + 1,
	
	// 删除历史镜像
	IDML_DEL_VERSION,
	
	// 列举历史镜像
	IDML_LIST_VERSION,
	
	// 应用某个历史版本
	IDML_APPLY_VERSION,
	
	//清除某个文件的所有历史版本
	IDML_CLEAR_VERSION,
};



///////////////////////////////////////////////////////////////////////////////////////////
// 用户，组操作
//

enum IDML_MSG_USER {

	//
	//列举用户
	IDML_LIST_USER = IDML_USER_COMM_BASE + 1,
	
	//列举组
	IDML_LIST_GROUP,
	
	//列举配额信息
	IDML_QUERY_GUOTA,
	
	//注册用户
	IDML_CREATE_USER,
		
	//修改用户信息
	IDML_UPDATE_USER,
	
	//获取某个用户信息
	IDML_GET_USER_INFO,
	
	//删除用户
	IDML_REMOVE_USER,
	
	//新建组
	IDML_CREATE_GROUP,
	
	//修改组信息
	IDML_UPDATE_GROUP,
	
	//获取某个组信息
	IDML_GET_GROUP_INFO,
	
	//删除组
	IDML_REMOVE_GROUP,
	

	
};
	

///////////////////////////////////////////////////////////////////////////////////////////
// 标签   
//

enum IDML_MSG_LABLE {

	//添加标签
	IDML_ADD_FILE_LABLE	= IDML_LABLE_COMM_BASE + 1,
	
	//删除标签
	IDML_DELETE_FILE_LABLE,
	
	//clear 标签
	IDML_CLEAR_FILE_LABLE,
	
	//delete 标签
	IDML_REMOVE_LABLE,
	
	// 获取标签 by file
	IDML_GET_FILE_LABLE,
	
	// list file by lable
	IDML_LIST_FILE_BY_LABLE,
	
	// 列举我的标签
	IDML_LIST_MY_LABLE,
};


///////////////////////////////////////////////////////////////////////////////////////////
// 共享   
//

enum IDML_MSG_SHARE {

	// 添加共享
	IDML_SHARE_SET = IDML_SHARE_COMM_BASE + 1, 
	
	// 删除共享
	IDML_SHARE_REMOVE,
	
	// 删除所有
	IDML_SHARE_REMOVE_ALL,
	
	// 列举我的共享		 
	IDML_SHARE_LIST_MY,
	
	// 列举共享给我的			   
	IDML_SHARE_LIST_TO_ME,
};



enum IDML_MSG_FULLTEXT{

	// 通知索引
	IDML_NOTIFY_INDEX= IDML_FULLTEXT_COMM_BASE + 1,
	
	// 查询
	IDML_FULL_SEARCH,
	
};



enum IDML_MSG_METADATA{

	// 设置元数据
	IDML_SET_METADATA = IDML_META_COMM_BASE + 1,

	//查询某个元数据
	IDML_QUERY_METADATA,
	
	// 查询所有元数据列表
	IDML_QUERY_METADATA_LIST,
	
	// 删除某个属性
	IDML_DELETE_METADATA,
	
	// 清空属性
	IDML_CLEAR_METADATA,	

};



// 属性
///////////////////////////////////////////////////////////////////////////////////////////
//
// The gns object is a directory，defualt is file
//
#define OBJ_ATTR_IS_DIRECTORY				0x00000001

//
// The object will replace the existing object 
//
#define OBJ_ATTR_REPLACE_EXIST				0x00000002

//
// The object is the last block
//
#define OBJ_ATTR_IS_LAST_BLOCK				0x00000004



#endif	//__NETWORK_MESG_HEADER_H__
