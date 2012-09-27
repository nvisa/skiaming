using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace WebPartSample
{
	public class ListProperties
	{
        public string ListTitle { get; set; }
        public int ItemCount { get; set; }
        public int FieldCount { get; set; }
        public int FolderCount { get; set; }
        public int ViewCount {get; set; }
        public int WorkFlowCount { get; set; }
	}
}
