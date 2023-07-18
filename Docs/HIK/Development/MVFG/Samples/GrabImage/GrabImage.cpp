/***************************************************************************************************
 *  @file   GrabImage.cpp
 *  @ver    v1.0.0  创建文件.
 *          v1.0.1  移除了缓存对齐的要求。
****************************************************************************************************/

#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include "MVFGControl.h"

bool g_bExit = FALSE;
#define BUFFER_NUMBER           3       // 申请的缓存个数

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
void SaveRawImage(int nImageNo, MV_FG_BUFFER_INFO* pstImageInfo)
{
    if (pstImageInfo)
    {
        char szFileName[256] = {0};

        sprintf_s(szFileName, 256, "Image_w%d_h%d_n%d.raw", pstImageInfo->nWidth, pstImageInfo->nHeight, nImageNo);
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
        STREAMHANDLE        hStream = (STREAMHANDLE)pUser;
        BUFFERHANDLE        hBuffer = NULL;
        MV_FG_BUFFER_INFO   stFrameInfo = {0};
        int                 nSaveImage = 10;

        // 开启取流
        int nRet = MV_FG_StartAcquisition(hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Start Acquisition failed, %#x\n", nRet);
            return nRet;
        }

        while(!g_bExit)
        {
            // 获取图片缓存
            nRet = MV_FG_GetImageBuffer(hStream, &hBuffer, 1000);
            if (MV_FG_SUCCESS == nRet)
            {
                nRet = MV_FG_GetBufferInfo(hBuffer, &stFrameInfo);
                if (MV_FG_SUCCESS == nRet)
                {
                    printf("FrameNumber:%-8I64d\tWidth: %d\tHeight: %d\n", stFrameInfo.nFrameID, stFrameInfo.nWidth, stFrameInfo.nHeight);

                    if (nSaveImage > 0)
                    {
                        SaveRawImage(--nSaveImage, &stFrameInfo);
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
                printf("Get image buffer failed, %#x\n", nRet);
            }

        }

        // 停止取流
        nRet = MV_FG_StopAcquisition(hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Stop Acquisition failed, %#x\n", nRet);
            return nRet;
        }
    }
    
    return MV_FG_SUCCESS;
}

int main(int argc, char** argv)
{
    int             nRet = MV_FG_SUCCESS;
    IFHANDLE        hInterface = NULL;
    DEVHANDLE       hDevice = NULL;
    STREAMHANDLE    hStream = NULL;
    BUFFERHANDLE    hBuffer[BUFFER_NUMBER] = {0}; 
    void*           pBuffer[BUFFER_NUMBER] = {0};

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

        // 枚举采集卡上的相机
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

        // 让用户选择设备
        int nSelectedDeviceIndex = -1;
        printf("Select a device: ");
        scanf_s("%d", &nSelectedDeviceIndex);
        ClearStdin();

        if ((nSelectedDeviceIndex < 0) || (nSelectedDeviceIndex >= (int)nDeviceNumber))
        {
            printf("invalid device index, Quit\n");
            break;
        }

        // 打开设备，获取设备句柄
        nRet = MV_FG_OpenDevice(hInterface, nSelectedDeviceIndex, &hDevice);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open device error, %#x\n", nRet);
            hDevice = NULL;
            break;
        }

        // 关闭触发模式
        nRet = MV_FG_SetEnumValueByString(hDevice, "TriggerMode", "Off");
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Turn off TriggerMode failed, %#x\n", nRet);
            break;
        }

        // 获取流通道个数
        unsigned int nStreamNumber = 0;
        nRet = MV_FG_GetNumStreams(hDevice, &nStreamNumber);
        if (MV_FG_SUCCESS != nRet || 0 == nStreamNumber)
        {
            printf("No Stream available\n");
            break;
        }

        // 打开流通道(目前只支持单个流通道)
        nRet = MV_FG_OpenStream(hDevice, 0, &hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open Stream error, %#x\n", nRet);
            break;
        }

        // 获取图像大小
        unsigned int nImagePayloadSize = 0;
        nRet = MV_FG_GetPayloadSize(hStream, &nImagePayloadSize);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Get payload size error, %#x\n", nRet);
            break;
        }

        // 分配并注册用于保存图片的缓存
        for (unsigned int i = 0; i < BUFFER_NUMBER; i++)
        {
            // 分配图像缓存
            pBuffer[i] = malloc(nImagePayloadSize);
            if (NULL == pBuffer[i])
            {
                printf("Allocate Buffer error\n");
                nRet = MV_FG_ERR_OUT_OF_MEMORY;
                break;
            }

            // 注册缓存供SDK使用
            nRet = MV_FG_AnnounceBuffer(hStream, pBuffer[i], nImagePayloadSize, NULL, &(hBuffer[i]));
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

        // 将所有缓存放入输入队列，已备取流使用
        nRet = MV_FG_FlushQueue(hStream, MV_FG_BUFFER_QUEUE_ALL_TO_INPUT);
        if (MV_FG_SUCCESS != nRet)
        {
            break;
        }

        // 创建线程进行取流
        void* hThreadHandle = (void*) _beginthreadex(NULL , 0 , GrabbingThread , hStream, 0 , NULL);
        if (NULL == hThreadHandle)
        {
            printf("Create Thread Error\n");
            break;
        }

        printf("Press any key to stop acquisition.\n");
        WaitForKeyPress();

        g_bExit = true;
        WaitForSingleObject(hThreadHandle, INFINITE);
        CloseHandle(hThreadHandle);
        hThreadHandle = NULL;
    } while (0);

    // 释放相关资源
    if (NULL != hStream)
    {
        // 清空缓存队列
        nRet = MV_FG_FlushQueue(hStream, MV_FG_BUFFER_QUEUE_ALL_DISCARD);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Flush Buffer Queue error, %#x\n", nRet);
        }

        // 回收并释放注册的缓存
        for (unsigned int i = 0; i < BUFFER_NUMBER; i++)
        {
            if (NULL != hBuffer[i])
            {
                nRet = MV_FG_RevokeBuffer(hStream, hBuffer[i], NULL, NULL);
                if (MV_FG_SUCCESS != nRet)
                {
                    printf("Revoke Buffer failed, %#x\n", nRet);
                }
                hBuffer[i] = NULL;
            }

            if (NULL != pBuffer[i])
            {
                free(pBuffer[i]);
                pBuffer[i] = NULL;
            }
        }

        // 关闭流通道
        nRet = MV_FG_CloseStream(hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Close Stream error, %#x\n", nRet);
        }
        hStream = NULL;
    }

    // 关闭设备
    if (NULL != hDevice)
    {
        nRet = MV_FG_CloseDevice(hDevice);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Close device error, %#x\n", nRet);
        }
        hDevice = NULL;
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
