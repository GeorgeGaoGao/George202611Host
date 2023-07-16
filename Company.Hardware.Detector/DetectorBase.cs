using Company.Core.Model;
using Company.Logger;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Detector
{
    public abstract class DetectorBase : IDetector
    {
        public DetectorConfig DetectorConfig { get; private set; }

        public bool Initialized {get;private set;}

        /// <summary>
        /// 是否采集中
        /// </summary>
        public bool IsGrabbing { get; set;}


        public event Action<DetectorImage> OnGrabbed;

        public bool Close()
        {
            if(Initialized)
            {
                if(DoClose())
                {
                    return true;
                }
            }

            return false;
        }

        public bool Init(IDetectorConfigProvider provider)
        {
            this.DetectorConfig = provider.DetectorConfig;

            provider.OnChanged += (() =>
            {
                //todo 重新初始化

                Logs.LogInfo($"平板探测器重新初始化 Width:{DetectorConfig.Width}  Height:{DetectorConfig.Height}");

                DoInit();

            });


            if (Initialized)
            {
                throw new Exception("重复初始化平板探测器");
            }
            if (DoInit())
            {
                return true;
            }

            return false;
        }

        /// <summary>
        /// 开始采集
        /// </summary>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        public bool Grab()
        {
            if(!Initialized)
            {
                throw new Exception("未初始化平板探测器");
            }

            if(DoGrab())
            {
                IsGrabbing= true;
                return true;
            }

            return false;
        }


        protected void InvokeOnGrabbed(UnmanagedArray2D<ushort> image)
        {
            if (OnGrabbed == null) return;

            foreach (Action<DetectorImage> item in OnGrabbed.GetInvocationList())
            {
                item.Invoke(new DetectorImage(image));
            }
        }


        // 抽象方法，由子类实现

        public abstract bool DoGrab();
        public abstract bool DoClose();
        public abstract bool DoInit();
    }
}
