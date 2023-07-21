using Company.Application.Initialize.Models;
using Company.Application.Share.Config;
using Company.Core.Ioc;
using Company.Hardware.Camera;
using Company.Hardware.ControlCard;
using Company.Hardware.Detector;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace Company.Application.Initialize.Services
{

    /// <summary>
    /// 硬件生命周期管理器
    /// </summary>
    [ExposedService(Lifetime.Singleton)]
    public class HardwareLifetimeManager
    {
        public ISystemConfigProvider SystemConfigProvider { get; set; }

        /// <summary>
        /// 表示所有硬件加载成功
        /// </summary>
        public bool IsInitialized { get; set; }

        /// <summary>
        /// 相机设备
        /// </summary>
        public ICamera Camera { get; }
        /// <summary>
        /// 平板探测器设备
        /// </summary>
        public IDetector Detector { get; }
        /// <summary>
        /// 控制卡设备
        /// </summary>
        public IControlCard ControlCard { get; }

        public HardwareLifetimeManager(ISystemConfigProvider systemConfigProvider ,ICamera camera, IDetector detector,IControlCard controlCard)
        {
            SystemConfigProvider= systemConfigProvider;
            Camera = camera;
            Detector = detector;
            ControlCard = controlCard; 
        }

        /// <summary>
        /// 加载所有硬件
        /// </summary>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        public async Task<InitResult> InitAsync()
        {
            if(IsInitialized)
            {
                throw new Exception("重复初始化硬件");
            }

            Task<bool> task_camera = Task.Run(() => Camera.Init(SystemConfigProvider));
            Task<bool> task_detector = Task.Run(() => Detector.Init(SystemConfigProvider));
            Task<bool> task_controlcard = Task.Run(() => ControlCard.Init(SystemConfigProvider));

            var list = await Task.WhenAll(task_camera, task_detector,task_controlcard);//等待
            bool result = list.All(p => p);

            if (!result)
            {
                string msg = "硬件初始化失败：";
                if (task_camera.Result == false)
                    msg += "相机|";
                if (task_detector.Result == false)
                    msg += "平板探测器|";
                if (task_controlcard.Result == false)
                    msg += "控制卡|";

                msg = msg.Remove(msg.Length - 1);

                return new InitResult { Message = msg, Success = false };
            }


            IsInitialized = true;

            return new InitResult { Message = "硬件初始化成功", Success = true };

        }

        /// <summary>
        /// 关闭所有硬件
        /// </summary>
        public void Close()
        {
            try
            {
                Camera.Close();
            }
            catch(Exception ex)
            {
                //todo 
            }

            try
            {
                Detector.Close();
            }
            catch (Exception ex)
            {
                //todo 
            }
        }
    }
}
