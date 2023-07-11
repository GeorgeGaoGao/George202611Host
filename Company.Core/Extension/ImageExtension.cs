using Company.Core.Helper;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Extension
{
    public static class ImageExtension
    {
        /// <summary>
        /// BitmapSource 转 Bitmap
        /// </summary>
        /// <param name="source"></param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        public static Bitmap ToBitmap(this System.Windows.Media.Imaging.BitmapSource source)
        {
            Assert.NotNull(source);

            PixelFormat format;

            if(source.Format == System.Windows.Media.PixelFormats.Gray8)
            {
                format = PixelFormat.Format8bppIndexed;
            }
            else if(source.Format== System.Windows.Media.PixelFormats.Bgr24)
            {
                format = PixelFormat.Format24bppRgb;
            }
            else if(source.Format== System.Windows.Media.PixelFormats.Bgr32)
            {
                format = PixelFormat.Format32bppArgb;
            }
            else if(source.Format== System.Windows.Media.PixelFormats.Gray16)
            {
                format = PixelFormat.Format16bppGrayScale;
            }
            else
            {
                throw new Exception($"未实现{source.Format}格式的转换");
            }

            Bitmap bitmap = new Bitmap(source.PixelWidth, source.PixelHeight, format);
            BitmapData data = bitmap.LockBits(new Rectangle(Point.Empty, bitmap.Size), ImageLockMode.WriteOnly, bitmap.PixelFormat);
            source.CopyPixels(
                System.Windows.Int32Rect.Empty,data.Scan0,
                data.Height * data.Stride,
                data.Stride);
            bitmap.UnlockBits(data);
            return bitmap;
        }

        public static BitmapData LockBits(this Bitmap source)
        {
            return source.LockBits(new Rectangle(Point.Empty, source.Size), ImageLockMode.ReadWrite, source.PixelFormat);
        }
    }
}
