// Copyright © Microsoft Corporation.  All Rights Reserved.
// This code released under the terms of the 
// Microsoft Public License (MS-PL, http://opensource.org/licenses/ms-pl.html.)
//
//Copyright (C) Microsoft Corporation.  All rights reserved.
namespace NorthwindMapping
{
    using System;

    public partial class Employee
    {
        public override string ToString()
        {
            return string.Format(System.Globalization.CultureInfo.CurrentCulture, "{0} {1} {2}", this._TitleOfCourtesy, this._FirstName, this._LastName);
        }
    }
}
