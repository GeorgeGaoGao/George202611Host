using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Company.Core.Dialog
{
    /// <summary>
    /// PopupBox.xaml 的交互逻辑
    /// </summary>
    public partial class PopupBox : Popup
    {
        public PopupBox()
        {
            InitializeComponent();
        }


        /// <summary>
        /// 透明度
        /// </summary>
        public new double Opacity
        {
            get { return (double)GetValue(OpacityProperty); }
            set { SetValue(OpacityProperty, value); }
        }

        public static new readonly DependencyProperty OpacityProperty =
            DependencyProperty.Register("Opacity", typeof(double), typeof(PopupBox), new PropertyMetadata(1.0,new PropertyChangedCallback(OnOpacityPropertyChangedCallback)));

        private static void OnOpacityPropertyChangedCallback(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (!(d is PopupBox box)) return;
            if (!(e.NewValue is double v)) return;
            box.border.Opacity = v;//赋值新的透明度
        }



        public string Message
        {
            get { return (string)GetValue(MessageProperty); }
            set { SetValue(MessageProperty, value); }
        }

        public static readonly DependencyProperty MessageProperty =
            DependencyProperty.Register("Message", typeof(string), typeof(PopupBox), new PropertyMetadata(string.Empty));


        private static PopupBox dialog = new PopupBox();
        private static DispatcherTimer timer = new DispatcherTimer();

        /// <summary>
        /// 弹出对话框
        /// </summary>
        /// <param name="message">消息</param>
        /// <param name="owner">所属窗体对象</param>
        /// <param name="seconds">对话框隐藏倒计时（秒）</param>
        public static void Show(string message, Window owner = null, int seconds = 1)
        {
            try
            {
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    if(owner == null)
                    {
                        owner = Application.Current.MainWindow;
                    }

                    dialog.Message = message;
                    dialog.PlacementTarget = owner;
                    dialog.Placement = PlacementMode.Center;
                    dialog.StaysOpen = true;
                    dialog.AllowsTransparency = true;
                    dialog.VerticalOffset = owner.ActualHeight / 3;
                    dialog.Opacity = 0.9;
                    dialog.IsOpen = true;

                    timer.Tick -= Timer_Tick;
                    timer.Tick += Timer_Tick;
                    timer.Interval = new TimeSpan(0, 0, seconds);
                    timer.Start();

                }));
            }
            catch 
            {
            }
        }

        private static void Timer_Tick(object sender, EventArgs e)
        {
            timer.Stop();
            Task.Run(() =>
            {
                try
                {
                    for (int i = 0; i < 100; i++)
                    {
                        Thread.Sleep(5);
                        if (Application.Current == null) return;
                        Application.Current.Dispatcher.Invoke(() =>
                        {
                            dialog.Opacity -= 0.01;
                        });
                    }

                    Application.Current.Dispatcher.Invoke(() =>
                    {
                        dialog.IsOpen = false;
                        dialog.Message = string.Empty;
                    });
                }
                catch
                {

                }
            });
        }
    }
}
