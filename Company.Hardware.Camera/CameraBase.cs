using Company.Logger;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Camera
{
    public abstract class CameraBase : ICamera
    {
        public CameraConfig CameraConfig { get; private set; }
        public bool Initialized {get;private set;}

        public event Action<Photo> OnGrabbed;

        public void Close()
        {
            if (Initialized)
            {
                DoClose();
                Initialized = false;
            }
        }



        public bool Init(ICameraConfigProvider provider)
        {
            CameraConfig = provider.CameraConfig;

            provider.OnChanged += (() =>
            {
                //todo 重新初始化

                Logs.LogInfo($"相机重新初始化 Width:{CameraConfig.Width}  Height:{CameraConfig.Height}");

                DoInit();

            });

            if (Initialized)
            {
                Logs.LogError(new Exception("相机重复初始化"));
            }

            if (DoInit())
            {
                Initialized = true;
                return true;
            }

            return false;
        }


        protected void InvokeOnGrabbed(Photo image)
        {
            if (OnGrabbed == null) return;

            foreach (Action<Photo> item in OnGrabbed.GetInvocationList())
            {
                item.Invoke(image);
            }
        }


        // 抽象方法，由子类实现

        public abstract bool Trigger();
        public abstract bool DoClose();
        public abstract bool DoInit();
    }
}
