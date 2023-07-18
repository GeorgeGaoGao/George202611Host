#ifndef _MV_FG_ERROR_DEFINE_H_
#define _MV_FG_ERROR_DEFINE_H_

typedef int MV_FG_ERROR;

//////////////////////////////////////////////////////////////////////////
#define    MV_FG_SUCCESS                  0          // 成功
//////////////////////////////////////////////////////////////////////////

///< SDK错误:范围0x80190001-0x801900FF
//////////////////////////////////////////////////////////////////////////
#define    MV_FG_ERR_ERROR                0x80190001 // 未知错误
#define    MV_FG_ERR_NOT_INITIALIZED      0x80190002 // 未初始化
#define    MV_FG_ERR_NOT_IMPLEMENTED      0x80190003 // 未实现
#define    MV_FG_ERR_RESOURCE_IN_USE      0x80190004 // 资源被占用
#define    MV_FG_ERR_ACCESS_DENIED        0x80190005 // 无权限
#define    MV_FG_ERR_INVALID_HANDLE       0x80190006 // 无效句柄
#define    MV_FG_ERR_INVALID_ID           0x80190007 // 无效ID
#define    MV_FG_ERR_NO_DATA              0x80190008 // 无数据
#define    MV_FG_ERR_INVALID_PARAMETER    0x80190009 // 无效参数
#define    MV_FG_ERR_IO                   0x80190010 // IO错误
#define    MV_FG_ERR_TIMEOUT              0x80190011 // 超时
#define    MV_FG_ERR_ABORT                0x80190012 // 操作被中断
#define    MV_FG_ERR_INVALID_BUFFER       0x80190013 // 无效缓存
#define    MV_FG_ERR_NOT_AVAILABLE        0x80190014 // 不可达
#define    MV_FG_ERR_INVALID_ADDRESS      0x80190015 // 无效地址
#define    MV_FG_ERR_BUFFER_TOO_SMALL     0x80190016 // 缓存太小
#define    MV_FG_ERR_INVALID_INDEX        0x80190017 // 无效索引
#define    MV_FG_ERR_PARSING_CHUNK_DATA   0x80190018 // 解析Chunk失败
#define    MV_FG_ERR_INVALID_VALUE        0x80190019 // 无效的值
#define    MV_FG_ERR_RESOURCE_EXHAUSTED   0x80190020 // 资源耗尽
#define    MV_FG_ERR_OUT_OF_MEMORY        0x80190021 // 内存申请失败
#define    MV_FG_ERR_BUSY                 0x80190022 // 忙碌
#define    MV_FG_ERR_LOADLIBRARY          0x80190023 // 动态库加载失败
//////////////////////////////////////////////////////////////////////////


///< GenICam错误:范围0x80190100-0x801901FF
//////////////////////////////////////////////////////////////////////////
#define    MV_FG_ERR_GC_GENERIC             0x80190100  // GenICam通用错误
#define    MV_FG_ERR_GC_ARGUMENT            0x80190101  // GenICam参数错误
#define    MV_FG_ERR_GC_RANGE               0x80190102  // GenICam参数范围错误
#define    MV_FG_ERR_GC_PROPERTY            0x80190103  // GenICam属性错误
#define    MV_FG_ERR_GC_RUNTIME             0x80190104  // GenICam运行环境错误
#define    MV_FG_ERR_GC_LOGICAL             0x80190105  // GenICam逻辑错误
#define    MV_FG_ERR_GC_ACCESS              0x80190106  // GenICam权限错误
#define    MV_FG_ERR_GC_TIMEOUT             0x80190107  // GenICam超时
#define    MV_FG_ERR_GC_DYNAMICCAST         0x80190108  // GenICam转换异常
#define    MV_FG_ERR_GC_UNKNOW              0x801901FF  // GenICam未知错误
//////////////////////////////////////////////////////////////////////////

#endif //_MV_FG_ERROR_DEFINE_H_
