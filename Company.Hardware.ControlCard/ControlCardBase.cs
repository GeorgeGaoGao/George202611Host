using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Company.Hardware.ControlCard
{
    /// <summary>
    /// 控制卡的抽象父类，定义了业务逻辑，具体的实现由子类完成
    /// </summary>
    public abstract class ControlCardBase : IControlCard
    {
        public bool Initialized {get;private set;}

        public bool IsReady => Initialized && IsAxisHomed;

        /// <summary>
        /// 运动轴是否回零
        /// </summary>
        public  bool IsAxisHomed { get;  set; }

        /// <summary>
        /// 运动轴正在回零中
        /// </summary>
        public bool IsAxisHoming { get; set; }

        /// <summary>
        /// 轴运动速度模式
        /// </summary>
        protected SpeedMode SpeedMode { get;private set;}
        /// <summary>
        /// 控制卡的配置参数
        /// </summary>
        protected ControlCardConfig Config { get; set; }

        /// <summary>
        /// 获取AxisType枚举的元素集合
        /// </summary>
        protected IEnumerable<AxisType> AxisTypes { get; private set; } = Enum.GetValues(typeof(AxisType)).Cast<AxisType>();

        public void Close()
        {
            if(Initialized)
            {
                DoStop(null, AxisStopMode.减速停止);
                DoClose();
                Initialized = false;
            }
        }

        

        public IControlCardConfigProvider Provider { get; private set; }
        public bool Init(IControlCardConfigProvider provider)
        {
            Provider = provider;
            Config = provider.ControlCardConfig;

            if (Initialized)
            {
                throw new Exception("重复初始化控制卡");
            }

            if (DoInit())
            {
                Initialized = true;
                DoConfigure();
                return true;
            }

            return false;
        }

        public bool Move(AxisType axisType, double um, out string message)
        {
            if (!IsReady) 
            {
                message = "运动轴未准备好";
                return false;
            }
            bool result = MoveAxis(axisType, um, out string v);
            message = v;
            return result;
        }

        /// <summary>
        /// 移动轴功能
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="um"></param>
        /// <param name="v"></param>
        /// <returns></returns>
        private bool MoveAxis(AxisType axisType, double um, out string v)
        {
            //判断当前轴是否开启使能
            if (!DoGetAxisEnable(axisType))
            {
                v = "当前轴未开启使能";
                return false;
            }
            //判断当前轴是否正在运动
            if (!DoGetAxisStopped(axisType))
            {
                v = "当前轴正在运动中";
                return false;
            }

            bool result = DoMoveAxis(axisType, um);

            while (true)
            {
                if (DoGetAxisStopped(axisType))
                {
                    break;
                }

                Thread.Sleep(5);
            }

            v = "当前轴运动完成";
            return result;
        }

        /// <summary>
        /// 轴的连续运动
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="moveDirection"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        public bool Move(AxisType axisType, MoveDirection moveDirection)
        {
            if (!IsReady)
            {
                return false;
            }

            //判断当前轴是否开启使能
            if (!DoGetAxisEnable(axisType))
            {
                return false;
            }
            //判断当前轴是否正在运动
            if (!DoGetAxisStopped(axisType))
            {
                return false;
            }

            return DoMoveContinue(axisType, moveDirection);
        }

        public void SetSpeedMode(SpeedMode mode)
        {
            SpeedMode = mode;
        }

        public void Stop(AxisType? axisType)
        {
            DoStop(axisType, AxisStopMode.减速停止);
        }

        /// <summary>
        /// 轴回零
        /// </summary>
        /// <param name="message"></param>
        /// <returns></returns>
        public  bool GoHome(out string message)
        {
            if (!Initialized)
            {
                throw new Exception("控制卡未初始化");
            }

            DoStop(null, AxisStopMode.减速停止);

            Thread.Sleep(100);

            try
            {
                IsAxisHoming = true;
                IsAxisHomed = false;
                IsAxisHomed = DoGoHome(out message);
            }
            catch(Exception ex)
            {
                message = ex.Message;
            }
            finally
            {
                IsAxisHoming = false;
            }

            return true;
        }





        //抽象方法成员


        /// <summary>
        /// 初始化控制卡
        /// </summary>
        /// <returns></returns>
        protected abstract bool DoInit();

        /// <summary>
        /// 配置控制卡
        /// </summary>
        protected abstract void DoConfigure();

        /// <summary>
        /// 停止所有轴
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="stopMode"></param>
        protected abstract void DoStop(AxisType? axisType, AxisStopMode stopMode);

        /// <summary>
        /// 关闭
        /// </summary>
        protected abstract void DoClose();

        

        /// <summary>
        /// 读某个轴的使能状态
        /// </summary>
        /// <param name="axisType"></param>
        /// <returns></returns>
        protected abstract bool DoGetAxisEnable(AxisType axisType);

        /// <summary>
        /// 写某个轴的使能状态
        /// </summary>
        /// <param name="axisType"></param>
        /// <returns></returns>
        protected abstract bool DoSetAxisEnable(AxisType axisType, bool v);

        /// <summary>
        /// 读某个轴的运动状态
        /// </summary>
        /// <param name="axisType"></param>
        /// <returns></returns>
        protected abstract bool DoGetAxisStopped(AxisType axisType);

        /// <summary>
        /// 移动某个轴到指定的距离
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="um"></param>
        /// <returns></returns>
        protected abstract bool DoMoveAxis(AxisType axisType, double um);

        /// <summary>
        /// 某个轴的连续运动
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="moveDirection"></param>
        protected abstract bool DoMoveContinue(AxisType axisType, MoveDirection moveDirection);

        /// <summary>
        /// 执行回零操作
        /// </summary>
        /// <param name="message"></param>
        protected abstract bool DoGoHome(out string message);
        
    }
}
