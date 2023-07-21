using Company.Logger;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Company.Hardware.ControlCard.None
{
    /// <summary>
    /// 仿真控制卡
    /// </summary>
    class NoneControlCard : ControlCardBase
    {
        protected override void DoClose()
        {
            
        }

        protected override void DoConfigure()
        {
            
        }

        protected override bool DoGetAxisEnable(AxisType axisType)
        {
            return true;
        }

        protected override bool DoGetAxisStopped(AxisType axisType)
        {
            return true;
        }

        protected override bool DoGoHome(out string message)
        {
            message = "回零成功";
            return true;
        }

        protected override bool DoInit()
        {
            Provider.OnChanged += (() =>
            {
                //todo... 当控制卡参数发生变化时，在这里重新设置控制卡的参数
            });

            return true;
        }

        protected override bool DoMoveAxis(AxisType axisType, double um)
        {
            Thread.Sleep((int)(um * 1));

            return true;
        }

        protected override bool DoMoveContinue(AxisType axisType, MoveDirection moveDirection)
        {
            return true;
        }

        protected override bool DoSetAxisEnable(AxisType axisType, bool v)
        {
            int enable = v ? 1 : 0;
            int axis = (int)axisType;

            return true;
        }

        /// <summary>
        /// 停止轴运动
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="stopMode"></param>
        /// <exception cref="NotImplementedException"></exception>
        protected override void DoStop(AxisType? axisType, AxisStopMode stopMode)
        {
            if (axisType.HasValue)
            {
                StopAxis(axisType.Value);
            }
            else
            {
                foreach (var item in AxisTypes)
                {
                    StopAxis(item);
                }
            }
        }

        private void StopAxis(AxisType axisType)
        {
            Thread.Sleep(500);//耗时模拟
        }
    }
}
