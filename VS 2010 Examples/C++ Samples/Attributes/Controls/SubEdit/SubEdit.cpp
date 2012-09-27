// SubEdit.cpp : Implementation of DLL Exports.
//
// This is a part of the Active Template Library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

// You will need the NT SUR Beta 2 SDK or VC 4.2 or higher in order to build
// this project.  This is because you will need MIDL 3.00.15 or higher and new
// headers and libs.  If you have VC 4.2 installed, then everything should
// already be configured correctly.

// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL,
//      run nmake -f SubEditps.mak in the project directory.

#include "stdafx.h"
#include "resource.h"


[ emitidl ];

[ module(dll, uuid = "{0720EB03-0A81-4b02-8187-AB8D96BE45DA}", name = "CONTROL", helpstring = "control 1.0 Type Library") ];