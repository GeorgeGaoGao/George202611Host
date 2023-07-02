using Company.Core.Enums;
using Company.Core.Helper;
using Company.Core.Ioc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Company.Core.Language
{
    [ExposedService(Lifetime.Singleton,typeof(ILanguageManager))]
    public class LanguageManager : ILanguageManager
    {
        private ResourceDictionary Resource { get; set; }
        private string Uri { get; set; }
        public LanguageManager()
        {
            Set(LanguageType.CN);//设置默认语言为简体中文
        }

        /// <summary>
        /// 索引器
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        public string this[string key]
        {
            get
            {
                if (this.Resource != null && this.Resource.Contains(key))
                { 
                  return Resource[key].ToString();  
                }

                return this[key];
            }
        }

        public LanguageType Current { get;private set; }

        public void Set(LanguageType language)
        {
            Assert.NotNull(language);

            if (this.Uri == null)
            {
                ResourceDictionary resourceDictionary = Application.Current.Resources.MergedDictionaries[0];
                string path = resourceDictionary.Source.AbsolutePath;
                this.Uri = path.Remove(path.LastIndexOf("/"));
            }

            string target = $"{Uri}/{language}.xaml";
            this.Resource = (ResourceDictionary)Application.LoadComponent(new Uri(target, UriKind.RelativeOrAbsolute));
            Application.Current.Resources.MergedDictionaries.RemoveAt(0);
            Application.Current.Resources.MergedDictionaries.Insert(0, Resource);

            if(Current != language)
            {
                Current= language;

                //todo 保存到系统设置里面
            }
        }
    }
}
