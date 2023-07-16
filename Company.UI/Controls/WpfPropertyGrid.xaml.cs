using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Company.UI.Controls
{
    /// <summary>
    /// WpfPropertyGrid.xaml 的交互逻辑
    /// </summary>
    public partial class WpfPropertyGrid : UserControl
    {
        public WpfPropertyGrid()
        {
            InitializeComponent();
        }


        /// <summary>
        /// 表示绑定一个参数对象
        /// </summary>
        public object SelectedObject
        {
            get { return (object)GetValue(SelectedObjectProperty); }
            set { SetValue(SelectedObjectProperty, value); }
        }

        public static readonly DependencyProperty SelectedObjectProperty =
            DependencyProperty.Register(nameof(SelectedObject), typeof(object), typeof(WpfPropertyGrid), new FrameworkPropertyMetadata(SelectedObjectPropertyCallBack));

        private static void SelectedObjectPropertyCallBack(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if(d is WpfPropertyGrid wpfPropertyGrid)
            {
                wpfPropertyGrid.propertyGrid.SelectedObject = e.NewValue;
            }
        }
    }
}
