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

        public bool Init(CameraConfig cameraConfig)
        {
            CameraConfig = cameraConfig;
            if (Initialized)
            {
                throw new Exception("相机重复初始化");
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
        public abstract void DoClose();
        public abstract bool DoInit();
    }
}
