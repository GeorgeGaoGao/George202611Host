#ifndef _MV_FG_DEFINES_H_
#define _MV_FG_DEFINES_H_

#  if defined(_WIN32)
#    if defined(_MSC_VER) && _MSC_VER >= 1600 /* VS2010 provides stdint.h */
#      include <stdint.h>
#    elif !defined _STDINT_H && !defined _STDINT
       /* stdint.h is usually not available under Windows */
       typedef unsigned char uint8_t;
       typedef __int32 int32_t;
       typedef __int64 int64_t;
       typedef unsigned __int32 uint32_t;
       typedef unsigned __int64 uint64_t;
#    endif
#  else
#    include <stdint.h>
#  endif

#ifdef __cplusplus
     typedef bool bool8_t;
#else
     typedef uint8_t bool8_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/// \~chinese 句柄类型定义
typedef void*  IFHANDLE;                                            ///< \~chinese 采集卡句柄
typedef void*  DEVHANDLE;                                           ///< \~chinese 设备句柄
typedef void*  STREAMHANDLE;                                        ///< \~chinese 取流句柄
typedef void*  BUFFERHANDLE;                                        ///< \~chinese 缓存句柄
typedef void*  PORTHANDLE;                                          ///< \~chinese 参数句柄，可以使用采集卡句柄或者设备句柄

///< \~chinese 采集卡类型
#define MV_FG_GEV_INTERFACE                     0x00000001          ///< \~chinese 网口采集卡
#define MV_FG_U3V_INTERFACE                     0x00000002          ///< \~chinese U3V采集卡
#define MV_FG_CAMERALINK_INTERFACE              0x00000004          ///< \~chinese CameraLink采集卡
#define MV_FG_CXP_INTERFACE                     0x00000008          ///< \~chinese CXP采集卡

///< \~chinese 卡信息的字符串最大长度
#define MV_FG_MAX_IF_INFO_SIZE 64

///< \~chinese CXP采集卡信息
typedef struct _MV_CXP_INTERFACE_INFO_
{
    unsigned char       chInterfaceID[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese 采集卡ID
    unsigned char       chDisplayName[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese 显示名称
    unsigned char       chSerialNumber[MV_FG_MAX_IF_INFO_SIZE];     ///< \~chinese 序列号

    // 低16位有效: bits(0~2)代表功能, bits(3~7)代表设备, bits(8-15)代表总线
    // |15  14  13  12  11  10  9  8 | 7  6  5  4  3 | 2  1  0 |
    // +-----------------------------+---------------+---------+
    // |             bus             |    device     |  func   |
    unsigned int        nPCIEInfo;                                  ///< \~chinese 采集卡的PCIE插槽信息

    unsigned int        nReserved[64];                              ///< \~chinese 预留

}MV_CXP_INTERFACE_INFO;

///< \~chinese GEV采集卡信息
typedef struct _MV_GEV_INTERFACE_INFO_
{
    unsigned char       chInterfaceID[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese 采集卡ID
    unsigned char       chDisplayName[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese 显示名称
    unsigned char       chSerialNumber[MV_FG_MAX_IF_INFO_SIZE];     ///< \~chinese 序列号


    // 低16位有效: bits(0~2)代表功能, bits(3~7)代表设备, bits(8-15)代表总线
    // |15  14  13  12  11  10  9  8 | 7  6  5  4  3 | 2  1  0 |
    // +-----------------------------+---------------+---------+
    // |             bus             |    device     |  func   |
    unsigned int        nPCIEInfo;                                  ///< \~chinese 采集卡的PCIE插槽信息

    unsigned int        nReserved[64];                              ///< \~chinese 预留

}MV_GEV_INTERFACE_INFO;

///< \~chinese CML采集卡信息
typedef struct _MV_CML_INTERFACE_INFO_
{
    unsigned char       chInterfaceID[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese 采集卡ID
    unsigned char       chDisplayName[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese 显示名称
    unsigned char       chSerialNumber[MV_FG_MAX_IF_INFO_SIZE];     ///< \~chinese 序列号


    // 低16位有效: bits(0~2)代表功能, bits(3~7)代表设备, bits(8-15)代表总线
    // |15  14  13  12  11  10  9  8 | 7  6  5  4  3 | 2  1  0 |
    // +-----------------------------+---------------+---------+
    // |             bus             |    device     |  func   |
    unsigned int        nPCIEInfo;                                  ///< \~chinese 采集卡的PCIE插槽信息

    unsigned int        nReserved[64];                              ///< \~chinese 预留

}MV_CML_INTERFACE_INFO;

///< \~chinese 采集卡信息
typedef struct _MV_FG_INTERFACE_INFO_
{
    unsigned int        nTLayerType;                                ///< \~chinese 采集卡类型
    unsigned int        nReserved[4];                               ///< \~chinese 保留字段

    union
    {
        MV_CXP_INTERFACE_INFO   stCXPIfaceInfo;                     ///< \~chinese CXP采集卡信息
        MV_GEV_INTERFACE_INFO   stGEVIfaceInfo;                     ///< \~chinese GEV采集卡信息
        MV_CML_INTERFACE_INFO   stCMLIfaceInfo;                     ///< \~chinese CameraLink采集卡信息

        unsigned int            nReserved[256];                     ///< \~chinese 保留字段
        // more ...
    }IfaceInfo;

}MV_FG_INTERFACE_INFO;


///< \~chinese 设备信息的最大长度
#define MV_FG_MAX_DEV_INFO_SIZE 64

///< \~chinese CXP设备信息
typedef struct _MV_CXP_DEVICE_INFO_
{
    unsigned char       chVendorName[MV_FG_MAX_DEV_INFO_SIZE];      ///< \~chinese 供应商名字
    unsigned char       chModelName[MV_FG_MAX_DEV_INFO_SIZE];       ///< \~chinese 型号名字
    unsigned char       chManufacturerInfo[MV_FG_MAX_DEV_INFO_SIZE];///< \~chinese 厂商信息
    unsigned char       chDeviceVersion[MV_FG_MAX_DEV_INFO_SIZE];   ///< \~chinese 设备版本
    unsigned char       chSerialNumber[MV_FG_MAX_DEV_INFO_SIZE];    ///< \~chinese 序列号
    unsigned char       chUserDefinedName[MV_FG_MAX_DEV_INFO_SIZE]; ///< \~chinese 用户自定义名字

    unsigned int        nReserved[64];                              ///< \~chinese 保留字段

}MV_CXP_DEVICE_INFO;


#define MV_FG_GEV_IFCONFIG_LLA_BIT        0x00000004    ///< \~chinese GEV设备LLA使能标志位
#define MV_FG_GEV_IFCONFIG_DHCP_BIT       0x00000002    ///< \~chinese GEV设备DHCP使能标志位
#define MV_FG_GEV_IFCONFIG_PERSISTENT_BIT 0x00000001    ///< \~chinese GEV设备静态IP使能标志位
#define MV_FG_GEV_IFCONFIG_PR_BIT         0x80000000    ///< \~chinese GEV设备能否处理PAUSE帧标志位
#define MV_FG_GEV_IFCONFIG_PG_BIT         0x40000000    ///< \~chinese GEV设备能否生成PAUSE帧标志位
///< \~chinese GEV设备信息
typedef struct _MV_GEV_DEVICE_INFO_
{
    // 支持IP配置，1代表支持。bit0：静态IP, bit1：DHCP, bits2：LLA
    // |31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 | 15  14  13  12  11  10  9  8 7  6  5  4  3 |   2       1         0     |
    // |-----------------------------------------------------------------------------------------------------+-------+-----------|
    // |PR PG                                           |                                            |  LLA  +  DHCP + PERSISTENT|
    unsigned int        nIpCfgOption;                               ///< \~chinese 支持的IP配置
    unsigned int        nIpCfgCurrent;                              ///< \~chinese 当前IP配置，参考支持的IP配置说明

    unsigned int        nCurrentIp;                                 ///< \~chinese 当前IP地址
    unsigned int        nCurrentSubNetMask;                         ///< \~chinese 当前子网掩码
    unsigned int        nDefultGateWay;                             ///< \~chinese 当前网关
    unsigned int        nNetExport;                                 ///< \~chinese 网口IP地址
    uint64_t            nMacAddress;                                ///< \~chinese MAC地址

    unsigned char       chVendorName[MV_FG_MAX_DEV_INFO_SIZE];      ///< \~chinese 供应商名字
    unsigned char       chModelName[MV_FG_MAX_DEV_INFO_SIZE];       ///< \~chinese 型号名字
    unsigned char       chManufacturerInfo[MV_FG_MAX_DEV_INFO_SIZE];///< \~chinese 厂商信息
    unsigned char       chDeviceVersion[MV_FG_MAX_DEV_INFO_SIZE];   ///< \~chinese 设备版本
    unsigned char       chSerialNumber[MV_FG_MAX_DEV_INFO_SIZE];    ///< \~chinese 序列号
    unsigned char       chUserDefinedName[MV_FG_MAX_DEV_INFO_SIZE]; ///< \~chinese 用户自定义名字

    unsigned int        nReserved[64];                              ///< \~chinese 保留字段

}MV_GEV_DEVICE_INFO;

///< \~chinese CML设备信息
typedef struct _MV_CML_DEVICE_INFO_
{
    unsigned char       chVendorName[MV_FG_MAX_DEV_INFO_SIZE];      ///< \~chinese 供应商名字
    unsigned char       chModelName[MV_FG_MAX_DEV_INFO_SIZE];       ///< \~chinese 型号名字
    unsigned char       chManufacturerInfo[MV_FG_MAX_DEV_INFO_SIZE];///< \~chinese 厂商信息
    unsigned char       chDeviceVersion[MV_FG_MAX_DEV_INFO_SIZE];   ///< \~chinese 设备版本
    unsigned char       chSerialNumber[MV_FG_MAX_DEV_INFO_SIZE];    ///< \~chinese 序列号
    unsigned char       chUserDefinedName[MV_FG_MAX_DEV_INFO_SIZE]; ///< \~chinese 用户自定义名字

    unsigned int        nReserved[64];                              ///< \~chinese 保留字段

}MV_CML_DEVICE_INFO;

///< \~chinese 设备类型
#define MV_FG_GEV_DEVICE                     0x00000001          ///< \~chinese 网口设备
#define MV_FG_U3V_DEVICE                     0x00000002          ///< \~chinese U3V设备
#define MV_FG_CAMERALINK_DEVICE              0x00000003          ///< \~chinese CameraLink设备
#define MV_FG_CXP_DEVICE                     0x00000004          ///< \~chinese CXP设备

///< \~chinese 设备信息
typedef struct _MV_FG_DEVICE_INFO_
{
    unsigned int                nDevType;                           ///< \~chinese 设备类型
    unsigned int                nReserved[3];                       ///< \~chinese 保留字段

    union
    {
        MV_CXP_DEVICE_INFO      stCXPDevInfo;                       ///< \~chinese CXP设备信息
        MV_GEV_DEVICE_INFO      stGEVDevInfo;                       ///< \~chinese GEV设备信息
        MV_CML_DEVICE_INFO      stCMLDevInfo;                       ///< \~chinese CameraLink设备信息

        unsigned int            nReserved[256];                     ///< \~chinese 保留字段
        // more ...
    }DevInfo;

}MV_FG_DEVICE_INFO;


///< \~chinese 缓存队列类型
typedef enum _MV_FG_BUFFER_QUEUE_TYPE_
{
    MV_FG_BUFFER_QUEUE_INPUT_TO_OUTPUT          = 0,                ///< \~chinese 将输入队列的BUFFER放到输出队列
    MV_FG_BUFFER_QUEUE_OUTPUT_DISCARD           = 1,                ///< \~chinese 放弃输出队列的BUFFER
    MV_FG_BUFFER_QUEUE_ALL_TO_INPUT             = 2,                ///< \~chinese 将所有的BUFFER(包括输出队列)放到输入队列
    MV_FG_BUFFER_QUEUE_UNQUEUED_TO_INPUT        = 3,                ///< \~chinese 将未使用的BUFFER放到输入队列
    MV_FG_BUFFER_QUEUE_ALL_DISCARD              = 4                 ///< \~chinese 放弃输入和输出队列中的BUFFER

}MV_FG_BUFFER_QUEUE_TYPE;

///< \~chinese 像素格式定义
#define MV_FG_PIXEL_MONO                        0x01000000          ///< \~chinese Mono格式
#define MV_FG_PIXEL_COLOR                       0x02000000          ///< \~chinese 彩色格式
#define MV_FG_PIXEL_CUSTOM                      0x80000000          ///< \~chinese 自定义
#define MV_FG_PIXEL_BIT_COUNT(n)                ((n) << 16)         ///< \~chinese 位个数所在位置
typedef enum _MV_FG_PIXEL_TYPE_
{
    ///< \~chinese 未定义的格式
    MV_FG_PIXEL_TYPE_Undefined                  = 0xFFFFFFFF,   ///< \~chinese 未定义格式

    ///< \~chinese Mono格式
    MV_FG_PIXEL_TYPE_Mono8                      = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0001),   ///< \~chinese Mono8
    MV_FG_PIXEL_TYPE_Mono10                     = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0003),  ///< \~chinese Mono10
    MV_FG_PIXEL_TYPE_Mono10_Packed              = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0004),  ///< \~chinese Mono10_Packed
    MV_FG_PIXEL_TYPE_Mono12                     = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0005),  ///< \~chinese Mono12
    MV_FG_PIXEL_TYPE_Mono12_Packed              = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0006),  ///< \~chinese Mono12_Packed
    MV_FG_PIXEL_TYPE_Mono16                     = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0007),  ///< \~chinese Mono16

    ///< \~chinese Bayer格式 
    MV_FG_PIXEL_TYPE_BayerGR8                   = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0008),   ///< \~chinese BayerGR8
    MV_FG_PIXEL_TYPE_BayerRG8                   = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0009),   ///< \~chinese BayerRG8
    MV_FG_PIXEL_TYPE_BayerGB8                   = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x000A),   ///< \~chinese BayerGB8
    MV_FG_PIXEL_TYPE_BayerBG8                   = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x000B),   ///< \~chinese BayerBG8
    MV_FG_PIXEL_TYPE_BayerGR10                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000C),  ///< \~chinese BayerGR10
    MV_FG_PIXEL_TYPE_BayerRG10                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000D),  ///< \~chinese BayerRG10
    MV_FG_PIXEL_TYPE_BayerGB10                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000E),  ///< \~chinese BayerGB10
    MV_FG_PIXEL_TYPE_BayerBG10                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000F),  ///< \~chinese BayerBG10
    MV_FG_PIXEL_TYPE_BayerGR12                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0010),  ///< \~chinese BayerGR12
    MV_FG_PIXEL_TYPE_BayerRG12                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0011),  ///< \~chinese BayerRG12
    MV_FG_PIXEL_TYPE_BayerGB12                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0012),  ///< \~chinese BayerGB12
    MV_FG_PIXEL_TYPE_BayerBG12                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0013),  ///< \~chinese BayerBG12
    MV_FG_PIXEL_TYPE_BayerGR10_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0026),  ///< \~chinese BayerGR10_Packed
    MV_FG_PIXEL_TYPE_BayerRG10_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0027),  ///< \~chinese BayerRG10_Packed
    MV_FG_PIXEL_TYPE_BayerGB10_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0028),  ///< \~chinese BayerGB10_Packed
    MV_FG_PIXEL_TYPE_BayerBG10_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0029),  ///< \~chinese BayerBG10_Packed
    MV_FG_PIXEL_TYPE_BayerGR12_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002A),  ///< \~chinese BayerGR12_Packed
    MV_FG_PIXEL_TYPE_BayerRG12_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002B),  ///< \~chinese BayerRG12_Packed
    MV_FG_PIXEL_TYPE_BayerGB12_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002C),  ///< \~chinese BayerGB12_Packed
    MV_FG_PIXEL_TYPE_BayerBG12_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002D),  ///< \~chinese BayerBG12_Packed
    MV_FG_PIXEL_TYPE_BayerGR16                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x002E),  ///< \~chinese BayerGR16
    MV_FG_PIXEL_TYPE_BayerRG16                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x002F),  ///< \~chinese BayerRG16
    MV_FG_PIXEL_TYPE_BayerGB16                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0030),  ///< \~chinese BayerGB16
    MV_FG_PIXEL_TYPE_BayerBG16                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0031),  ///< \~chinese BayerBG16

    ///< \~chinese RGB格式 
    MV_FG_PIXEL_TYPE_RGB8_Packed                = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(24) | 0x0014),  ///< \~chinese RGB8_Packed
    MV_FG_PIXEL_TYPE_BGR8_Packed                = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(24) | 0x0015),  ///< \~chinese BGR8_Packed
    MV_FG_PIXEL_TYPE_RGBA8_Packed               = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(32) | 0x0016),  ///< \~chinese RGBA8_Packed
    MV_FG_PIXEL_TYPE_BGRA8_Packed               = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(32) | 0x0017),  ///< \~chinese BGRA8_Packed
    MV_FG_PIXEL_TYPE_RGB16_Packed               = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(48) | 0x0033),  ///< \~chinese RGB16_Packed

    ///< \~chinese YUV格式 
    MV_FG_PIXEL_TYPE_YUV422_Packed              = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(16) | 0x001F),  ///< \~chinese YUV422_Packed
    MV_FG_PIXEL_TYPE_YUV422_YUYV_Packed         = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(16) | 0x0032),  ///< \~chinese YUV422_YUYV_Packed

}MV_FG_PIXEL_TYPE;

///< \~chinese 输出的图像信息
typedef struct _MV_FG_BUFFER_INFO_
{
    void*               pBuffer;                                    ///< [OUT] \~chinese 图像缓存地址
    unsigned int        nSize;                                      ///< [OUT] \~chinese 地址大小
    unsigned int        nFilledSize;                                ///< [OUT] \~chinese 图像长度
    void*               pPrivate;                                   ///< [OUT] \~chinese 私有数据

    unsigned int        nWidth;                                     ///< [OUT] \~chinese 宽度
    unsigned int        nHeight;                                    ///< [OUT] \~chinese 高度
    MV_FG_PIXEL_TYPE    enPixelType;                                ///< [OUT] \~chinese 像素格式

    bool                bNewData;                                   ///< [OUT] \~chinese 是否是新图像到来
    bool                bQueued;                                    ///< [OUT] \~chinese 是否在取图队列中
    bool                bAcquiring;                                 ///< [OUT] \~chinese 是否在取图
    bool                bIncomplete;                                ///< [OUT] \~chinese 是否未完成

    int64_t             nFrameID;                                   ///< [OUT] \~chinese 帧号
    int64_t             nDevTimeStamp;                              ///< [OUT] \~chinese 设备时间戳
    int64_t             nHostTimeStamp;                             ///< [OUT] \~chinese 主机时间戳

    unsigned int        nReserved[64];                              ///<       \~chinese 保留字段

}MV_FG_BUFFER_INFO;


///< \~chinese 节点权限
typedef enum _MV_FG_NODE_ACCESS_MODE_
{
    ACCESS_MODE_NI                              = 0,                ///< \~chinese Value不可实现
    ACCESS_MODE_NA                              = 1,                ///< \~chinese Value不可用
    ACCESS_MODE_WO                              = 2,                ///< \~chinese Value只写
    ACCESS_MODE_RO                              = 3,                ///< \~chinese Value只读
    ACCESS_MODE_RW                              = 4,                ///< \~chinese Value读写
    ACCESS_MODE_UNDEFINED                       = 5,                ///< \~chinese Value未定义

}MV_FG_NODE_ACCESS_MODE;

///< \~chinese 节点类型
typedef enum _MV_FG_NODE_INTERFACE_TYPE_
{
    INTERFACE_TYPE_Value                        = 0,                ///< \~chinese Value
    INTERFACE_TYPE_Base                         = 1,                ///< \~chinese Base
    INTERFACE_TYPE_Integer                      = 2,                ///< \~chinese Integer
    INTERFACE_TYPE_Boolean                      = 3,                ///< \~chinese Boolean
    INTERFACE_TYPE_Command                      = 4,                ///< \~chinese Command
    INTERFACE_TYPE_Float                        = 5,                ///< \~chinese Float
    INTERFACE_TYPE_String                       = 6,                ///< \~chinese String
    INTERFACE_TYPE_Register                     = 7,                ///< \~chinese Register
    INTERFACE_TYPE_Category                     = 8,                ///< \~chinese Category
    INTERFACE_TYPE_Enumeration                  = 9,                ///< \~chinese Enumeration
    INTERFACE_TYPE_EnumEntry                    = 10,               ///< \~chinese EnumEntry
    INTERFACE_TYPE_Port                         = 11,               ///< \~chinese Port

}MV_FG_NODE_INTERFACE_TYPE;

/// \~chinese Int类型信息
typedef struct _MV_FG_INTVALUE_
{
    int64_t             nCurValue;                                  ///< [OUT] \~chinese 当前值
    int64_t             nMax;                                       ///< [OUT] \~chinese 最大值
    int64_t             nMin;                                       ///< [OUT] \~chinese 最小值
    int64_t             nInc;                                       ///< [OUT] \~chinese 步长

    unsigned int        nReserved[16];                              ///<       \~chinese 保留字段

}MV_FG_INTVALUE;

/// \~chinese XML描述文件中的最大符号数
#define MV_FG_MAX_SYMBOLIC_NUM      64

/// \~chinese XML描述文件的符号最大长度
#define MV_FG_MAX_SYMBOLIC_STRLEN   64

/// \~chinese 枚举类型信息
typedef struct _MV_FG_ENUMVALUE_
{
    unsigned int        nCurValue;                                  ///< [OUT] \~chinese 当前值
    char                strCurSymbolic[MV_FG_MAX_SYMBOLIC_STRLEN];  ///< [OUT] \~chinese 当前值的符号名称

    unsigned int        nSupportedNum;                              ///< [OUT] \~chinese 支持的枚举类型个数
    unsigned int        nSupportValue[MV_FG_MAX_SYMBOLIC_NUM];      ///< [OUT] \~chinese 支持的枚举类型的值
    char                strSymbolic[MV_FG_MAX_SYMBOLIC_NUM][MV_FG_MAX_SYMBOLIC_STRLEN];///< [OUT] \~chinese 支持的枚举类型的符号名称

    unsigned int        nReserved[4];                               ///<       \~chinese 保留字段

}MV_FG_ENUMVALUE;

/// \~chinese Float类型信息
typedef struct _MV_FG_FLOATVALUE_
{
    float               fCurValue;                                  ///< [OUT] \~chinese 当前值
    float               fMax;                                       ///< [OUT] \~chinese 最大值
    float               fMin;                                       ///< [OUT] \~chinese 最小值

    unsigned int        nReserved[4];                               ///<       \~chinese 保留字段

}MV_FG_FLOATVALUE;

/// \~chinese String类型信息
typedef struct _MV_FG_STRINGVALUE_
{
    char                strCurValue[256];                           ///< [OUT] \~chinese 当前值
    int64_t             nMaxLength;                                 ///< [OUT] \~chinese 最大长度

    unsigned int        nReserved[4];                               ///<       \~chinese 保留字段

}MV_FG_STRINGVALUE;

#ifdef __cplusplus
}
#endif 

#endif //_MV_FG_DEFINES_H_
