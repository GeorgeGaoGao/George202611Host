using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.ControlCard
{
    /// <summary>
    /// 运动控制卡的接口
    /// </summary>
    public interface IControlCard
    {
        /// <summary>
        /// 表示控制卡是否初始化完成
        /// </summary>
        bool Initialized { get; }

        /// <summary>
        /// 是否就绪
        /// </summary>
        bool IsReady { get; }

        /// <summary>
        /// 运动轴是否回零
        /// </summary>
        bool IsAxisHomed { get; }

        /// <summary>
        /// 初始化相机
        /// </summary>
        /// <returns></returns>
        bool Init(IControlCardConfigProvider provider);

        /// <summary>
        /// 关闭控制卡
        /// </summary>
        void Close();

        /// <summary>
        /// 设置运动轴速度模式
        /// </summary>
        void SetSpeedMode(SpeedMode mode);

        /// <summary>
        /// 运动轴回零
        /// </summary>
        /// <param name="message"></param>
        /// <returns></returns>
        bool GoHome(out string message);

        /// <summary>
        /// 移动轴
        /// </summary>
        /// <param name="axisType">轴的类型</param>
        /// <param name="um">移动的距离</param>
        /// <param name="message"></param>
        /// <returns></returns>
        bool Move(AxisType axisType,double um, out string message);

        /// <summary>
        /// 连续运动
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="moveDirection"></param>
        /// <returns></returns>
        bool Move(AxisType axisType, MoveDirection moveDirection);

        /// <summary>
        /// 停止轴运动
        /// </summary>
        /// <param name="axisType"></param>
        void Stop(AxisType? axisType);
    }
}
