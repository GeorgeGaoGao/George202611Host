using Company.Core.Helper;
using Company.Core.Model;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Company.Hardware.Detector.None
{
    internal class NoneDetector : DetectorBase
    {
        private Task _task;
        private UnmanagedArray2D<ushort> unmanagedArray;
        public override bool DoClose()
        {
            IsGrabbing = false;
            return true;
        }

        public override bool DoGrab()
        {
            if(_task==null|| _task.IsCompleted)
            {
                IsGrabbing = true;
                _task = Task.Factory.StartNew(RunGrab, TaskCreationOptions.LongRunning);
            }

            return true;
        }

        private void RunGrab()
        {
            while(IsGrabbing)
            {
                //定时输出本地的tiff图像
                if(unmanagedArray.Width!= DetectorConfig.Width|| unmanagedArray.Height != DetectorConfig.Height)
                {
                    throw new Exception("系统设置中FPD尺寸与实际FPD分辨率不一致");
                }

                using(var temp = unmanagedArray.DeepClone())
                {
                    InvokeOnGrabbed(temp);
                }

                Thread.Sleep(50);
            }
        }

        public override bool DoInit()
        {
            string filename = $"data\\{DetectorConfig.Photo}";
            if (File.Exists(filename))
            {
                unmanagedArray = ImageHelper.LoadTiff(filename);
            }
            else
            {
                throw new Exception($"{filename}不存在");
            }

            unmanagedArray = unmanagedArray ?? new UnmanagedArray2D<ushort>(DetectorConfig.Width, DetectorConfig.Height);

            Thread.Sleep(1000);

            return true;
        }
    }
}
