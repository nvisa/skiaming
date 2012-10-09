// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
using System.Data.Linq;
using System.Data.Linq.Mapping;
using System.Data;
using System.Collections.Generic;
using System.Reflection;
using System.Linq;
using System.Linq.Expressions;
using System.ComponentModel;
using System;

namespace BdcSampleCSharp
{
	public partial class CustomerDataContext
	{
        public CustomerDataContext() :
            base(global::BdcSampleCSharp.Settings.Default.NORTHWNDConnectionString, mappingSource)
        {
            OnCreated();
        }
	}
}
