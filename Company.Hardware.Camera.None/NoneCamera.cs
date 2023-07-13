using Company.Core.Helper;
using Company.Core.Model;
using Company.Logger;
using System;
using System.Collections.Generic;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Company.Hardware.Camera.None
{
    internal class NoneCamera : CameraBase
    {
        private UnmanagedArray2D<ColorBGRA> unmanagedArray;

        public override bool DoClose()
        {
            return true;
        }

        public override bool DoInit()
        {
            unmanagedArray = new UnmanagedArray2D<ColorBGRA>(CameraConfig.Width, CameraConfig.Height);
            string filename = $"data\\{CameraConfig.Photo}";
            if(File.Exists(filename))
            {
                System.Drawing.Bitmap bitmap = ImageHelper.Load(filename);
                if(unmanagedArray.Width!=bitmap.Width|| unmanagedArray.Height != bitmap.Height)
                {
                    Logs.LogError(new Exception("系统设置中相机尺寸与实际相机分辨率不一致"));
                }
                BitmapData data = bitmap.LockBits(new System.Drawing.Rectangle(0,0,bitmap.Width,bitmap.Height),
                    System.Drawing.Imaging.ImageLockMode.ReadWrite,
                    System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                MemoryHelper.CopyMemory(unmanagedArray.Header, data.Scan0, unmanagedArray.Length);
                bitmap.UnlockBits(data);
                return true;
            }

            Thread.Sleep(1000);

            return false;
        }

        public override bool Trigger()
        {
            Task.Delay(50).ContinueWith(t =>
            {
                InvokeOnGrabbed(new Photo(unmanagedArray));
            });

            return true ;
        }
    }
}
