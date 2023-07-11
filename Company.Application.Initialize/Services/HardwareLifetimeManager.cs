using Company.Application.Initialize.Models;
using Company.Core.Ioc;
using Company.Hardware.Camera;
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
        /// <summary>
        /// 表示所有硬件加载成功
        /// </summary>
        public bool IsInitialized { get; set; }

        public ICamera Camera { get; }

        public IDetector Detector { get; }

        public HardwareLifetimeManager(ICamera camera, IDetector detector)
        {
            Camera = camera;
            Detector = detector;
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

            Task<bool> task_camera = Task.Run(() => Camera.Init(new CameraConfig()));
            Task<bool> task_detector = Task.Run(() => Detector.Init(new DetectorConfig()));
            
            var list = await Task.WhenAll(task_camera, task_detector);//等待
            bool result = list.All(p => p);

            if (!result)
            {
                string msg = "硬件初始化失败：";
                if (task_camera.Result == false)
                    msg += "相机|";
                if (task_detector.Result == false)
                    msg += "平板探测器|";

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
