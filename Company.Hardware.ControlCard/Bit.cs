using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.ControlCard
{
    /// <summary>
    /// 控制卡输入输出IO点位，用于读取和写入
    /// </summary>
    public struct Bit
    {
        /// <summary>
        /// 节点号，[0，16]，0表示伺服本身IO，1-16表示扩展节点号
        /// </summary>
        public int Board { get; }

        /// <summary>
        /// 输入端口号，[0,15]
        /// </summary>
        public int Port { get; }

        public Bit(int board, int port)
        {
            Board = board;
            Port = port;
        }

        public Bit(int port)
        {
            Port = port;
            Board= 0;
        }

        public static implicit operator int (Bit bit)
        {
            return bit.Port;
        }
    }
}
