/***************************************************************************************************
 *  @file   MultipleCamera.cpp
 *  @ver    v1.0.0  创建文件.
 *          v1.0.1  移除了缓存对齐的要求。
****************************************************************************************************/

#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include "MVFGControl.h"

#define BUFFER_NUMBER           3       // 申请的缓存个数

typedef struct _FG_DEVICE_CONTEXT_
{
    unsigned int        nDeviceIndex;
    DEVHANDLE           hDevice;
    STREAMHANDLE        hStream;
    BUFFERHANDLE        hBuffer[BUFFER_NUMBER];
    PVOID               pBuffer[BUFFER_NUMBER];

    bool                bThreadState;
    void*               hThreadHandle;

} FG_DEVICE_CONTEXT;

// 等待按键输入
void WaitForKeyPress(void)
{
    while(!_kbhit())
    {
        Sleep(10);
    }
    _getch();
}

// 清空标准输入中的残留数据
void ClearStdin(void)
{
    char c = '0';
    
    do
    {
        c = getchar();
        if (c == '\n' ||c == EOF)
        {
            break;
        }
    }
    while(TRUE);
}

// 保存图像原始数据
void SaveRawImage(unsigned int nDeviceIndex, int nImageNo, MV_FG_BUFFER_INFO* pstImageInfo)
{
    if (pstImageInfo)
    {
        char szFileName[256] = {0};

        sprintf_s(szFileName, 256, "Image_Dev%d_w%d_h%d_n%d.raw", nDeviceIndex, pstImageInfo->nWidth, pstImageInfo->nHeight, nImageNo);
        FILE* pImageFile = NULL;
        if ((0 != fopen_s(&pImageFile, szFileName, "wb")) || (NULL == pImageFile))
        {
            return;
        }

        fwrite(pstImageInfo->pBuffer, 1, pstImageInfo->nFilledSize, pImageFile);
        fclose(pImageFile);
    }
}

// 取流线程例程
unsigned int __stdcall GrabbingThread(void* pUser)
{
    if (pUser)
    {
        FG_DEVICE_CONTEXT*  pstDeviceContext = (FG_DEVICE_CONTEXT*)pUser;
        BUFFERHANDLE        hBuffer = NULL;
        MV_FG_BUFFER_INFO   stFrameInfo = {0};
        int                 nSaveImage = 10;

        // 开启取流
        int nRet = MV_FG_StartAcquisition(pstDeviceContext->hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Start Acquisition failed, %#x\n", nRet);
            return nRet;
        }

        while(pstDeviceContext->bThreadState)
        {
            // 获取图片缓存
            nRet = MV_FG_GetImageBuffer(pstDeviceContext->hStream, &hBuffer, 1000);
            if (MV_FG_SUCCESS == nRet)
            {
                // 获取并打印图像信息
                nRet = MV_FG_GetBufferInfo(hBuffer, &stFrameInfo);
                if (MV_FG_SUCCESS == nRet)
                {
                    printf("[%d] FrameNumber:%-8I64d\tWidth: %d\tHeight: %d\n", pstDeviceContext->nDeviceIndex, stFrameInfo.nFrameID, stFrameInfo.nWidth, stFrameInfo.nHeight);
                    if (nSaveImage > 0)
                    {
                        SaveRawImage(pstDeviceContext->nDeviceIndex, --nSaveImage, &stFrameInfo);
                    }
                }

                // 将图像缓存放回SDK内部队列
                nRet = MV_FG_QueueBuffer(hBuffer);
                if (MV_FG_SUCCESS != nRet)
                {
                    printf("Queue Buffer error, %#x\n", nRet);
                    break;
                }
            }
            else
            {
                printf("Get Image Buffer error, %#x\n", nRet);
            }
        }

        // 停止取流
        nRet = MV_FG_StopAcquisition(pstDeviceContext->hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Stop Acquisition failed, %#x\n", nRet);
            return nRet;
        }
    }

    return MV_FG_SUCCESS;
}

// 停止相机取流
void StopDeviceStream(FG_DEVICE_CONTEXT* pstDeviceContext)
{
    int     nRet = MV_FG_SUCCESS;

    if (NULL == pstDeviceContext)
    {
        return;
    }

    // 终止线程，并释放句柄
    if (NULL != pstDeviceContext->hThreadHandle)
    {
        pstDeviceContext->bThreadState = FALSE;
        WaitForSingleObject(pstDeviceContext->hThreadHandle, INFINITE);
        CloseHandle(pstDeviceContext->hThreadHandle);
        pstDeviceContext->hThreadHandle = NULL;
    }

    if (NULL != pstDeviceContext->hStream)
    {
        // 清空缓存队列
        nRet = MV_FG_FlushQueue(pstDeviceContext->hStream, MV_FG_BUFFER_QUEUE_ALL_DISCARD);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Flush Buffer Queue error, %#x\n", nRet);
        }

        // 回收并释放注册的缓存
        for (int nBufferIndex = 0; nBufferIndex < BUFFER_NUMBER; nBufferIndex++)
        {
            if (NULL != pstDeviceContext->hBuffer[nBufferIndex])
            {
                MV_FG_RevokeBuffer(pstDeviceContext->hStream, pstDeviceContext->hBuffer[nBufferIndex], NULL, NULL);
                pstDeviceContext->hBuffer[nBufferIndex] = NULL;
            }

            if (NULL != pstDeviceContext->pBuffer[nBufferIndex])
            {
                free(pstDeviceContext->pBuffer[nBufferIndex]);
                pstDeviceContext->pBuffer[nBufferIndex] = NULL;
            }
        }

        // 关闭流通道
        MV_FG_CloseStream(pstDeviceContext->hStream);
        pstDeviceContext->hStream = NULL;
    }

    // 关闭设备
    if (NULL != pstDeviceContext->hDevice)
    {
        MV_FG_CloseDevice(pstDeviceContext->hDevice);
        pstDeviceContext->hDevice = NULL;
    }
}


// 开启相机取流
int StartDeviceStream(IFHANDLE hInterface, unsigned int nDeviceIndex, FG_DEVICE_CONTEXT* pstDeviceContext)
{
    int nRet = MV_FG_SUCCESS;

    do
    {
        if (NULL == hInterface || nDeviceIndex < 0 || NULL == pstDeviceContext)
        {
            printf("Invalid parameter\n");
            nRet = MV_FG_ERR_INVALID_PARAMETER;
            break;
        }

        pstDeviceContext->nDeviceIndex = nDeviceIndex;

        // 打开设备，获取设备句柄
        nRet = MV_FG_OpenDevice(hInterface, nDeviceIndex, &(pstDeviceContext->hDevice));
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open device error, %#x\n", nRet);
            break;
        }

        // 关闭触发模式
        nRet = MV_FG_SetEnumValueByString(pstDeviceContext->hDevice, "TriggerMode", "Off");
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Turn off TriggerMode failed, %#x\n", nRet);
            break;
        }

        // 获取流个数
        unsigned int nStreamNumber = 0;
        nRet = MV_FG_GetNumStreams(pstDeviceContext->hDevice, &nStreamNumber);
        if (MV_FG_SUCCESS != nRet || 0 == nStreamNumber)
        {
            printf("No Stream available\n");
            break;
        }

        // 打开流通道(目前只支持单个流)
        nRet = MV_FG_OpenStream(pstDeviceContext->hDevice, 0, &(pstDeviceContext->hStream));
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open Stream error, %#x\n", nRet);
            break;
        }

        // 获取图像大小
        unsigned int nImagePayloadSize = 0;
        nRet = MV_FG_GetPayloadSize(pstDeviceContext->hStream, &nImagePayloadSize);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Get payload size error, %#x\n", nRet);
            break;
        }

        // 分配并注册用于保存图片的缓存
        for (unsigned int i = 0; i < BUFFER_NUMBER; i++)
        {
            // 分配图像缓存
            pstDeviceContext->pBuffer[i] = malloc(nImagePayloadSize);
            if (NULL == pstDeviceContext->pBuffer[i])
            {
                printf("Allocate Buffer error\n");
                nRet = MV_FG_ERR_OUT_OF_MEMORY;
                break;
            }

            // 注册缓存供SDK使用
            nRet = MV_FG_AnnounceBuffer(pstDeviceContext->hStream, pstDeviceContext->pBuffer[i],
                nImagePayloadSize, NULL, &(pstDeviceContext->hBuffer[i]));
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Announce Buffer error, %#x\n", nRet);
                break;
            }
        }

        if (MV_FG_SUCCESS != nRet)
        {
            break;
        }

        // 将所有缓存放入输入队列，以备取流使用
        nRet = MV_FG_FlushQueue(pstDeviceContext->hStream, MV_FG_BUFFER_QUEUE_ALL_TO_INPUT);
        if (MV_FG_SUCCESS != nRet)
        {
            break;
        }

        // 创建线程进行取流
        pstDeviceContext->bThreadState = TRUE;
        pstDeviceContext->hThreadHandle = (void*) _beginthreadex(NULL , 0, GrabbingThread, pstDeviceContext, 0, NULL);
        if (NULL == pstDeviceContext->hThreadHandle)
        {
            printf("Create Thread Error\n");
            nRet = MV_FG_ERR_ERROR;
            break;
        }
    } while(FALSE);

    // 若发生错误，则停止取流
    if (MV_FG_SUCCESS != nRet)
    {
        StopDeviceStream(pstDeviceContext);
    }

    return nRet;
}


int main(int argc, char** argv)
{
    int                 nRet = MV_FG_SUCCESS;
    IFHANDLE            hInterface = NULL;
    FG_DEVICE_CONTEXT*  pstDeviceContext = NULL;

    do 
    {
        // 枚举采集卡
        bool bChanged = false;
        nRet = MV_FG_UpdateInterfaceList(MV_FG_CXP_INTERFACE | MV_FG_GEV_INTERFACE | MV_FG_CAMERALINK_INTERFACE, &bChanged);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Update Interface List error, %#x\n", nRet);
            break;
        }

        // 获取采集卡个数
        unsigned int nInterfaceNumber = 0;
        nRet = MV_FG_GetNumInterfaces(&nInterfaceNumber);
        if (MV_FG_SUCCESS != nRet || 0 == nInterfaceNumber)
        {
            printf("No Interface found\n");
            break;
        }

        // 打印采集卡信息
        for (unsigned int i = 0; i < nInterfaceNumber; i++)
        {
            MV_FG_INTERFACE_INFO stInterfaceInfo = {0};

            nRet = MV_FG_GetInterfaceInfo(i, &stInterfaceInfo);
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Get info of No.%d Interface error, %#x\n", i, nRet);
                break;
            }

            if (stInterfaceInfo.nTLayerType == MV_FG_CXP_INTERFACE)
            {
                printf("[CXP]No.%d Interface: \n\tDisplayName: %s\n\tInterfaceID: %s\n\tSerialNumber:%s\n", i, 
                    stInterfaceInfo.IfaceInfo.stCXPIfaceInfo.chDisplayName, 
                    stInterfaceInfo.IfaceInfo.stCXPIfaceInfo.chInterfaceID, 
                    stInterfaceInfo.IfaceInfo.stCXPIfaceInfo.chSerialNumber);
            }
            else if (stInterfaceInfo.nTLayerType == MV_FG_GEV_INTERFACE)
            {
                printf("[GEV]No.%d Interface: \n\tDisplayName: %s\n\tInterfaceID: %s\n\tSerialNumber:%s\n", i, 
                    stInterfaceInfo.IfaceInfo.stGEVIfaceInfo.chDisplayName, 
                    stInterfaceInfo.IfaceInfo.stGEVIfaceInfo.chInterfaceID, 
                    stInterfaceInfo.IfaceInfo.stGEVIfaceInfo.chSerialNumber);
            }
            else if (stInterfaceInfo.nTLayerType == MV_FG_CAMERALINK_INTERFACE)
            {
                printf("[CML]No.%d Interface: \n\tDisplayName: %s\n\tInterfaceID: %s\n\tSerialNumber:%s\n", i, 
                    stInterfaceInfo.IfaceInfo.stCMLIfaceInfo.chDisplayName, 
                    stInterfaceInfo.IfaceInfo.stCMLIfaceInfo.chInterfaceID, 
                    stInterfaceInfo.IfaceInfo.stCMLIfaceInfo.chSerialNumber);
            }
        }
        if (MV_FG_SUCCESS != nRet)
        {
            break;
        }

        // 让用户选择采集卡，获取采集卡下标
        int nSelectedInterfaceIndex = -1;
        printf("Select an interface: ");
        scanf_s("%d", &nSelectedInterfaceIndex);
        ClearStdin();

        if ((nSelectedInterfaceIndex < 0) || (nSelectedInterfaceIndex >= (int)nInterfaceNumber))
        {
            printf("invalid interface index, Quit\n");
            break;
        }

        // 打开采集卡，返回采集卡句柄
        nRet = MV_FG_OpenInterface(nSelectedInterfaceIndex, &hInterface);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open No.%d Interface error, %#x\n", nSelectedInterfaceIndex, nRet);
            break;
        }

        // 枚举卡上的相机
        nRet = MV_FG_UpdateDeviceList(hInterface, &bChanged);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Update Device list error, %#x\n", nRet);
            break;
        }

        // 获取并打印设备信息
        unsigned int nDeviceNumber = 0;
        nRet = MV_FG_GetNumDevices(hInterface, &nDeviceNumber);
        if (MV_FG_SUCCESS != nRet || 0 == nDeviceNumber)
        {
            printf("No devices found\n");
            break;
        }

        for (unsigned int i = 0; i < nDeviceNumber; i++)
        {
            MV_FG_DEVICE_INFO stDeviceInfo = {0};

            nRet = MV_FG_GetDeviceInfo(hInterface, i, &stDeviceInfo);
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Get Info of No.%u Device error, %#x\n", i, nRet);
                break;
            }

            if (stDeviceInfo.nDevType == MV_FG_CXP_DEVICE)
            {
                printf("[CXP]No.%d Device: \n\tUserDefinedName: %s\n\tModelName: %s\n\tSerialNumber: %s\n", i, 
                    stDeviceInfo.DevInfo.stCXPDevInfo.chUserDefinedName,
                    stDeviceInfo.DevInfo.stCXPDevInfo.chModelName,
                    stDeviceInfo.DevInfo.stCXPDevInfo.chSerialNumber);
            }
            else if (stDeviceInfo.nDevType == MV_FG_GEV_DEVICE)
            {
                printf("[GEV]No.%d Device: \n\tUserDefinedName: %s\n\tModelName: %s\n\tSerialNumber: %s\n", i, 
                    stDeviceInfo.DevInfo.stGEVDevInfo.chUserDefinedName,
                    stDeviceInfo.DevInfo.stGEVDevInfo.chModelName,
                    stDeviceInfo.DevInfo.stGEVDevInfo.chSerialNumber);
            }
            else if (stDeviceInfo.nDevType == MV_FG_CAMERALINK_DEVICE)
            {
                printf("[CML]No.%d Device: \n\tUserDefinedName: %s\n\tModelName: %s\n\tSerialNumber: %s\n", i, 
                    stDeviceInfo.DevInfo.stCMLDevInfo.chUserDefinedName,
                    stDeviceInfo.DevInfo.stCMLDevInfo.chModelName,
                    stDeviceInfo.DevInfo.stCMLDevInfo.chSerialNumber);
            }
        }
        if (MV_FG_SUCCESS != nRet)
        {
            break;
        }

        // 按任意键进行取流
        printf("Press any key to start acquisition\n");
        WaitForKeyPress();

        pstDeviceContext = (FG_DEVICE_CONTEXT*)malloc(sizeof(FG_DEVICE_CONTEXT) * nDeviceNumber);
        if (NULL == pstDeviceContext)
        {
            printf("Alloc device context failed\n");
            break;
        }

        memset(pstDeviceContext, 0, sizeof(FG_DEVICE_CONTEXT) * nDeviceNumber);
        for (unsigned int i = 0; i < nDeviceNumber; i++)
        {
            nRet = StartDeviceStream(hInterface, i, pstDeviceContext + i);
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Start No.%d device stream error, %#x\n", i, nRet);
                break;
            }
        }

        // 主线程等待用户输入，退出程序
        printf("Press any key to stop acquisition.\n");
        WaitForKeyPress();

        for (unsigned int i = 0; i < nDeviceNumber; i++)
        {
            StopDeviceStream(pstDeviceContext + i);
        }
    } while (0);

    // 释放相关资源
    if (NULL != pstDeviceContext)
    {
        free(pstDeviceContext);
        pstDeviceContext = NULL;
    }

    // 关闭采集卡
    if (NULL != hInterface)
    {
        nRet = MV_FG_CloseInterface(hInterface);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Close Interface error, %#x\n", nRet);
        }
        hInterface = NULL;
    }

    printf("Press any key to exit.\n");
    WaitForKeyPress();

    return 0;
}
