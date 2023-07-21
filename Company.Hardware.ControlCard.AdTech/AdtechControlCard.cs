using ADT_CARD_632XE;
using Company.Core.Dialog;
using Company.Logger;
using DEMO632XE;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Company.Hardware.ControlCard.AdTech
{
    /// <summary>
    /// 众为兴控制卡
    /// </summary>
    class AdtechControlCard : ControlCardBase
    {
        private int cardno;//控制卡号

        private readonly Bit 急停 = new Bit(2, 1);
        

        /// <summary>
        /// 配置控制卡
        /// </summary>
        /// <exception cref="NotImplementedException"></exception>
        protected override void DoConfigure()
        {
            int result = 0;
            int board = 0;
            int logic = 0;

            //设置与获取原点/限位/急停信号输入端口映射
            result += adt_card_632xe.adt_set_axis_io_map(cardno, 0, 4, 急停.Board, 急停.Port);
            //设置与获取原点/限位/急停信号模式与有效电平
            result += adt_card_632xe.adt_set_hardlimit_mode(cardno, 0, 4, 1, 1, 1);

            foreach (var item in AxisTypes)
            {
                int axis = (int)item;

                //正限位
                result += adt_card_632xe.adt_set_axis_io_map(cardno, axis, 0, board, 0);
                result += adt_card_632xe.adt_set_hardlimit_mode(cardno, axis, 0, 1, logic, 1);

                //负限位
                result += adt_card_632xe.adt_set_axis_io_map(cardno, axis, 1, board, 1);
                result += adt_card_632xe.adt_set_hardlimit_mode(cardno, axis, 1, 1, logic, 1);

                //原点信号
                result += adt_card_632xe.adt_set_axis_io_map(cardno, axis, 2, board, 2);
                result += adt_card_632xe.adt_set_hardlimit_mode(cardno, axis, 2, 1, logic, 0);

                //设置脉冲当量和编程模式
                result += adt_card_632xe.adt_set_unit_mode(cardno, axis, 0);//编程模式
                result += adt_card_632xe.adt_set_pulse_equiv(cardno, axis, 1000);//脉冲当量
            }

            //创建插补坐标系
            result += adt_card_632xe.adt_set_inp_coordinate(cardno, 63, 3, new int[] { 3, 4 });
            //设置脉冲当量
            result += adt_card_632xe.adt_set_unit_mode(cardno, 63, 0);

            //软限位
            int enable = 1;//启用软限位
            foreach (var item in AxisTypes)
            {
                int axis = (int)item;
                double ppos = 0;
                double npos = 0;
                result += adt_card_632xe.adt_set_softlimit_mode(cardno, axis, enable, ppos, npos, (int)AxisStopMode.减速停止);
            }

            if (result != 0)
            {
                Logs.LogError($"adt_card_632xe控制卡配置参数异常");
            }
        }

        protected override bool DoGetAxisEnable(AxisType axisType)
        {
            int axis = (int)axisType;
            adt_card_632xe.adt_get_axis_enable(cardno, axis,out int enable);//获取轴的使能状态 
            return enable == 1;//1表示使能
        }

        protected override bool DoSetAxisEnable(AxisType axisType,bool v)
        {
            int enable = v? 1 : 0;
            int axis = (int)axisType;
            int result = adt_card_632xe.adt_set_axis_enable(cardno, axis, enable);//设置轴的使能状态 
            if(result != 0)
            {
                Logs.LogError($"adt_card_632xe控制卡设置轴的使能状态异常");
            }
            return result == 1;
        }

        protected override bool DoGetAxisStopped(AxisType axisType)
        {
            int axis = (int)axisType;
            int result = adt_card_632xe.adt_get_stopdata(cardno, axis,out int stopdata);//获取轴的停止信息
            if(result != 0)
            {
                Logs.LogError($"adt_card_632xe控制卡获取轴的停止信息异常");
            }
            return stopdata == 0;
        }

        //回零点
        protected override bool DoGoHome(out string message)
        {
            IsAxisHomed = false;
            message = string.Empty;
            int result = 0;
            foreach (var item in AxisTypes)
            {
                int axis = (int)(item);
                result += adt_card_632xe.adt_set_servo_home(cardno, axis, 1);
            }
            if (result != 0)
            {
                Logs.LogError($"adt_card_632xe控制卡回零失败");
            }
            return result == 0; 
        }

        protected override bool DoInit()
        {
            try
            {
                int card_count = 0;
                int result = adt_card_632xe.adt_initial(out card_count, 0);
                if(result != 0)
                {
                    Logs.LogError($"adt_card_632xe控制卡加载失败");
                    return false;
                }

                if (card_count != 1)
                {
                    Logs.LogError($"adt_card_632xe控制卡数量不等于1");
                    return false;
                }

                int[] indexs= new int[10];//设置卡号的索引
                adt_card_632xe.adt_get_card_index(out card_count, indexs);
                cardno = indexs[0];

                if (Start())
                {
                    return true;
                }
            }
            catch (Exception ex) 
            {
                Logs.LogError(ex);
            }

            return false;
        }

        /// <summary>
        /// 启动控制卡
        /// </summary>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        private bool Start()
        {
            adt_card_632xe.adt_ecat_stop(cardno);//终止总线通信
            int result = adt_card_632xe.adt_ecat_load_flash_cfg(cardno);//加载控制卡存储的总线配置参数
            if(result != 0 )
            {
                Logs.LogError($"adt_card_632xe控制卡加载总线配置参数失败:{adt_global.adt_decode_error_code(result)}");
                return false;
            }

            result = adt_card_632xe.adt_ecat_start(cardno);
            if (result != 0)
            {
                Logs.LogError($"adt_card_632xe控制卡开始失败:{adt_global.adt_decode_error_code(result)}");
                return false;
            }

            return true;
        }

        /// <summary>
        /// 定量运动
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="um"></param>
        /// <returns></returns>
        protected override bool DoMoveAxis(AxisType axisType, double um)
        {
            int axis = (int)axisType;
            int result = adt_card_632xe.adt_pmove_unit(cardno, axis, um, 0);
            return result == 0;
        }

        /// <summary>
        /// 连续运动
        /// </summary>
        /// <param name="axisType"></param>
        /// <param name="moveDirection"></param>
        /// <returns></returns>
        protected override bool DoMoveContinue(AxisType axisType, MoveDirection moveDirection)
        {
            int axis = (int)(axisType); 
            int result = adt_card_632xe.adt_continue_move(cardno,axis,(int)moveDirection);//单轴JOG驱动
            return result == 0;
        }

        protected override void DoStop(AxisType? axisType, AxisStopMode stopMode)
        {
            int axis = axisType.HasValue? (int)axisType.Value : 0;
            int result = adt_card_632xe.adt_set_axis_stop(cardno, axis, (int)stopMode);
            if (result != 0 )
            {
                Logs.LogError($"adt_card_632xe控制卡{axis}轴停止失败");
                PopupBox.Show($"adt_card_632xe控制卡{axis}轴停止失败");
            }
        }

        protected override void DoClose()
        {
            int result = adt_card_632xe.adt_ecat_stop(cardno);//终止总线通信
            if (result != 0 )
            {
                Logs.LogError($"adt_card_632xe控制卡停止失败");
                PopupBox.Show($"adt_card_632xe控制卡停止失败");
            }
            result = adt_card_632xe.adt_close_card();//控制卡资源释放
            if (result != 0 )
            {
                Logs.LogError($"adt_card_632xe控制卡关闭失败");
            }
        }
    }
}
