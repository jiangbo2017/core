/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <cppuhelper/factory.hxx>
#include <comphelper/processfactory.hxx>
#include <com/sun/star/container/XSet.hpp>

#include <com/sun/star/datatransfer/XDataFormatTranslator.hpp>
#include "ftransl.hxx"

#define SERVICE_NAME  "com.sun.star.datatransfer.DataFormatTranslator"

#define IMPL_NAME  "com.sun.star.datatransfer.DataFormatTranslator"

using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::registry;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::datatransfer;

namespace
{

    // functions to create a new Clipboad instance; is needed by factory helper implementation
    // @param rServiceManager - service manager, useful if the component needs other uno services
    // so we should give it to every UNO-Implementation component

    Reference< XInterface > SAL_CALL createInstance( const Reference< XMultiServiceFactory >& rServiceManager )
    {
        return Reference< XInterface >( static_cast< XDataFormatTranslator* >( new CDataFormatTranslatorUNO( comphelper::getComponentContext(rServiceManager) ) ) );
    }
}

extern "C"
{

SAL_DLLPUBLIC_EXPORT void* SAL_CALL ftransl_component_getFactory( const sal_Char* pImplName, void* pSrvManager, void* /*pRegistryKey*/ )
{
    void* pRet = nullptr;

    if ( pSrvManager && ( 0 == rtl_str_compare( pImplName, IMPL_NAME ) ) )
    {
        Sequence< OUString > aSNS { SERVICE_NAME };

        Reference< XSingleServiceFactory > xFactory ( createOneInstanceFactory(
            static_cast< XMultiServiceFactory* > ( pSrvManager ),
            OUString::createFromAscii( pImplName ),
            createInstance,
            aSNS ) );
        if ( xFactory.is() )
        {
            xFactory->acquire();
            pRet = xFactory.get();
        }
    }

    return pRet;
}

} // extern "C"

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
