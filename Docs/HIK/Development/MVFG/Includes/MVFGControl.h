#ifndef _MV_FG_CTRL_H_
#define _MV_FG_CTRL_H_

#include "MVFGDefines.h"
#include "MVFGErrorDefine.h"

#ifndef MV_FGCTRL_API
    #if (defined (_WIN32) || defined(WIN64))
        #if defined(MV_FGCTRL_EXPORTS)
            #define MV_FGCTRL_API __declspec(dllexport)
        #else
            #define MV_FGCTRL_API __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif

        #ifndef MV_FGCTRL_API
            #define  MV_FGCTRL_API
        #endif
    #endif
#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/***********************************************************************/
/*                             版本信息                                 /
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  获取SDK版本信息
 *  @return 以字符串形式返回SDK版本信息
 *  @remarks 格式：“版本 + 类型 + 编译时间”
 ************************************************************************/
MV_FGCTRL_API unsigned char* __stdcall MV_FG_GetSDKVersion();


/***********************************************************************/
/*                             基本操作                                 /
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  更新采集卡列表
 *  @param  nTLayerType             [IN]           采集卡类型
 *  @param  pbChanged               [OUT]          采集卡列表是否改变
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 *  @remarks 进行采集卡操作之前必须调用该接口，只有在调用该接口时内部采集卡列表才会更新
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_UpdateInterfaceList(IN unsigned int nTLayerType, OUT bool8_t *pbChanged);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取采集卡数量
 *  @param  pnNumIfaces             [OUT]          采集卡数量
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNumInterfaces(OUT unsigned int *pnNumIfaces);

/********************************************************************//**
 *  @~chinese
 *  @brief  根据索引获取采集卡信息
 *  @param  nIndex                  [IN]           采集卡索引，从0开始
 *  @param  pstIfaceInfo            [OUT]          采集卡信息
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetInterfaceInfo(IN unsigned int nIndex, OUT MV_FG_INTERFACE_INFO *pstIfaceInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  打开采集卡
 *  @param  nIndex                  [IN]           采集卡索引，从0开始
 *  @param  phIface                 [OUT]          采集卡句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenInterface(IN unsigned int nIndex, OUT IFHANDLE* phIface);

/********************************************************************//**
 *  @~chinese
 *  @brief  关闭采集卡
 *  @param  hIface                  [IN]           采集卡句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_CloseInterface(IN IFHANDLE hIface);

/********************************************************************//**
 *  @~chinese
 *  @brief  更新指定采集卡下的设备列表
 *  @param  hIface                  [IN]           采集卡句柄
 *  @param  pbChanged               [OUT]          设备列表是否改变
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 *  @remarks 只有在调用该接口时内部设备列表才会更新
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_UpdateDeviceList(IN IFHANDLE hIface, OUT bool8_t *pbChanged);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取设备数量
 *  @param  hIface                  [IN]           采集卡句柄
 *  @param  pnNumDevices            [OUT]          设备数量
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNumDevices(IN IFHANDLE hIface, OUT unsigned int *pnNumDevices);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取设备信息
 *  @param  hIface                  [IN]           采集卡句柄
 *  @param  nIndex                  [IN]           设备索引，从0开始
 *  @param  pstDevInfo              [OUT]          设备信息
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetDeviceInfo(IN IFHANDLE hIface, IN unsigned int nIndex, OUT MV_FG_DEVICE_INFO *pstDevInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  打开设备
 *  @param  hIface                  [IN]           采集卡句柄
 *  @param  nIndex                  [IN]           设备索引，从0开始
 *  @param  phDevice                [OUT]          设备句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenDevice(IN IFHANDLE hIface, IN unsigned int nIndex, OUT DEVHANDLE* phDevice);

/********************************************************************//**
 *  @~chinese
 *  @brief  关闭设备
 *  @param  hDevice                  [IN]           设备句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_CloseDevice(IN DEVHANDLE hDevice);


/***********************************************************************/
/*                             图像采集                             /
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  获取流通道数量
 *  @param  hDevice                 [IN]           设备句柄
 *  @param  pnNumStreams            [OUT]          流通道数量
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNumStreams(IN DEVHANDLE hDevice, OUT unsigned int *pnNumStreams);

/********************************************************************//**
 *  @~chinese
 *  @brief  打开流通道
 *  @param  hDevice                 [IN]           设备句柄
 *  @param  nIndex                  [IN]           流通道索引
 *  @param  phStream                [OUT]          流通道句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenStream(IN DEVHANDLE hDevice, IN unsigned int nIndex, OUT STREAMHANDLE* phStream);

/********************************************************************//**
 *  @~chinese
 *  @brief  关闭流通道
 *  @param  hStream                 [IN]           流通道句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_CloseStream(IN STREAMHANDLE hStream);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取流通道的图像大小
 *  @param  hStream             [IN]           流通道句柄
 *  @param  pnPayloadSize       [OUT]          流通道的图像大小
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 *  @remarks 修改相机图像相关参数如宽高、像素格式等参数后需要重新获取流通道的图像大小
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetPayloadSize(IN STREAMHANDLE hStream, OUT unsigned int* pnPayloadSize);

/********************************************************************//**
 *  @~chinese
 *  @brief  向流通道中注册缓存
 *  @param  hStream             [IN]           流通道句柄
 *  @param  pBuffer             [IN]           图像缓存地址
 *  @param  nSize               [IN]           图像缓存大小
 *  @param  pPrivate            [IN]           私有信息地址
 *  @param  phBuffer            [OUT]          缓存句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 *  @remarks 图像缓存大小通过MV_FG_GetPayloadSize接口获取；私有信息由用户自定义；
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_AnnounceBuffer(IN STREAMHANDLE hStream, IN void *pBuffer, IN unsigned int nSize, IN void *pPrivate, OUT BUFFERHANDLE *phBuffer);

/********************************************************************//**
 *  @~chinese
 *  @brief  从流通道中撤销缓存
 *  @param  hStream             [IN]           流通道句柄
 *  @param  hBuffer             [IN]           缓存句柄
 *  @param  pBuffer             [OUT]          图像缓存地址
 *  @param  pPrivate            [OUT]          私有信息地址
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 *  @remarks 只能撤销未使用队列中的缓存，可通过MV_FG_FlushQueue接口将缓存放到未使用队列
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_RevokeBuffer(IN STREAMHANDLE hStream, IN BUFFERHANDLE hBuffer, OUT void **pBuffer, OUT void **pPrivate);

/********************************************************************//**
 *  @~chinese
 *  @brief  刷新缓存队列
 *  @param  hStream                     [IN]           流通道句柄
 *  @param  enQueueType                 [IN]           队列类型
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 *  @remarks 取流过程中不支持MV_FG_BUFFER_QUEUE_INPUT_TO_OUTPUT、MV_FG_BUFFER_QUEUE_ALL_TO_INPUT、MV_FG_BUFFER_QUEUE_ALL_DISCARD
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_FlushQueue(IN STREAMHANDLE hStream, IN MV_FG_BUFFER_QUEUE_TYPE enQueueType);

/********************************************************************//**
 *  @~chinese
 *  @brief  开始取流
 *  @param  hStream                     [IN]           流通道句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_StartAcquisition(IN STREAMHANDLE hStream);

/********************************************************************//**
 *  @~chinese
 *  @brief  停止取流
 *  @param  hStream                     [IN]           流通道句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_StopAcquisition(IN STREAMHANDLE hStream);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取一帧图像的缓存句柄
 *  @param  hStream                     [IN]           流通道句柄
 *  @param  phBuffer                    [OUT]          缓存句柄
 *  @param  nTimeout                    [IN]           超时时间，以毫秒为单位
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 *  @remarks 通过MV_FG_GetBufferInfo接口根据缓存句柄获取图像信息
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetImageBuffer(IN STREAMHANDLE hStream, OUT BUFFERHANDLE *phBuffer, IN unsigned int nTimeout);

/********************************************************************//**
 *  @~chinese
 *  @brief  通过缓存句柄获取缓存信息
 *  @param  hBuffer                     [IN]           缓存句柄
 *  @param  pstBufferInfo               [OUT]          缓存信息
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetBufferInfo(IN BUFFERHANDLE hBuffer, OUT MV_FG_BUFFER_INFO* pstBufferInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  将缓存句柄放回输入队列
 *  @param  hBuffer                     [IN]           缓存句柄
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_QueueBuffer(IN BUFFERHANDLE hBuffer);


/***********************************************************************/
/*                             参数操作                                 /
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  获取XML文件
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  pData                     [IN][OUT]      存放XML文件的缓存地址
 *  @param  nDataSize                 [IN]           存放XML文件的缓存大小
 *  @param  pnDataLen                 [OUT]          XML文件长度
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetXMLFile(IN PORTHANDLE hPort, IN OUT unsigned char* pData, IN unsigned int nDataSize, OUT unsigned int* pnDataLen);

/********************************************************************//**
 *  @~chinese
 *  @brief  获得节点的访问模式
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strName                   [IN]           节点名称
 *  @param  penAccessMode             [OUT]          节点访问模式
 *  @remarks 获取EnumEntry类型节点的访问模式，strName应传入EnumEntry_NodeName_EnumEntryName；如获取PixelFormat枚举类型下的EnumEntry节点Mono8，strName格式为“EnumEntry_PixelFormat_Mono8”
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNodeAccessMode(IN PORTHANDLE hPort, IN const char * strName, OUT MV_FG_NODE_ACCESS_MODE *penAccessMode);

/********************************************************************//**
 *  @~chinese
 *  @brief  获得节点的类型
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strName                   [IN]           节点名称
 *  @param  penInterfaceType          [OUT]          节点类型
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNodeInterfaceType(IN PORTHANDLE hPort, IN const char * strName, OUT MV_FG_NODE_INTERFACE_TYPE *penInterfaceType);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取整型节点信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  pstIntValue               [OUT]          整型节点信息
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetIntValue(IN PORTHANDLE hPort, IN const char* strKey, OUT MV_FG_INTVALUE *pstIntValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  设置整型节点信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  nValue                    [IN]           要设置的值
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetIntValue(IN PORTHANDLE hPort, IN const char* strKey, IN int64_t nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取枚举类型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  pstEnumValue              [OUT]          枚举类型节点信息
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetEnumValue(IN PORTHANDLE hPort, IN const char* strKey, OUT MV_FG_ENUMVALUE *pstEnumValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  设置枚举类型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  nValue                    [IN]           要设置的值
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetEnumValue(IN PORTHANDLE hPort, IN const char* strKey, IN unsigned int nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  通过字符串设置枚举类型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  strValue                  [IN]           要设置的值
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetEnumValueByString(IN PORTHANDLE hPort, IN const char* strKey, IN const char* strValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取单精度浮点型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  pstFloatValue             [OUT]          单精度浮点型节点信息
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetFloatValue(IN PORTHANDLE hPort, IN const char* strKey, OUT MV_FG_FLOATVALUE *pstFloatValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  设置单精度浮点型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  fValue                    [IN]           要设置的值
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetFloatValue(IN PORTHANDLE hPort, IN const char* strKey, IN float fValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取布尔型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  pbValue                   [OUT]          布尔型节点信息
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetBoolValue(IN PORTHANDLE hPort, IN const char* strKey, OUT bool8_t *pbValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  设置布尔类型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  bValue                    [IN]           要设置的值
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetBoolValue(IN PORTHANDLE hPort, IN const char* strKey, IN bool8_t bValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  获取字符串型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  pstStringValue            [OUT]          字符串型节点信息
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetStringValue(IN PORTHANDLE hPort, IN const char* strKey, OUT MV_FG_STRINGVALUE *pstStringValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  设置字符串型节点的信息
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @param  strValue                  [IN]           要设置的值
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetStringValue(IN PORTHANDLE hPort, IN const char* strKey, IN const char* strValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  执行命令型节点的命令
 *  @param  hPort                     [IN]           参数所属对象句柄
 *  @param  strKey                    [IN]           节点名称
 *  @return 成功，返回MV_FG_SUCCESS；失败返回错误码
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetCommandValue(IN PORTHANDLE hPort, IN const char* strKey);

/********************************************************************//**
 *  @~chinese
 *  @brief  保存设备属性
 *  @param  hPort                       [IN]            参数所属对象句柄
 *  @param  strFileName                 [IN]            属性文件名，不支持中文路径。
 *  @return 成功，返回MV_FG_SUCCESS；错误，返回错误码 
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_FeatureSave(IN PORTHANDLE hPort, IN const char* strFileName);

/********************************************************************//**
 *  @~chinese
 *  @brief  导入设备属性
 *  @param  hPort                       [IN]            参数所属对象句柄
 *  @param  strFileName                 [IN]            属性文件名，不支持中文路径。
 *  @return 成功，返回MV_FG_SUCCESS；错误，返回错误码 
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_FeatureLoad(IN PORTHANDLE hPort, IN const char* strFileName);

#ifdef __cplusplus
}
#endif 

#endif //_MV_FG_CTRL_H_
