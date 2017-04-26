/* ****************************************************************************
*
* Copyright (c) Microsoft Corporation. All rights reserved.
*
*
* This file is part of Microsoft R Host.
*
* Microsoft R Host is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* Microsoft R Host is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Microsoft R Host.  If not, see <http://www.gnu.org/licenses/>.
*
* ***************************************************************************/

#include "devicewrapper.h"
#include "msvcrt.h"

namespace rhost {
    namespace grdevices {
        devicewrapper::devicewrapper() {
            _ver = R_GE_getVersion();
        }


        devicewrapper::devicewrapper(pDevDesc dd) {
            _ver = R_GE_getVersion();
            switch (_ver) {
            case 11:
                dd_11 = reinterpret_cast<DevDesc11*>(dd);
                break;
            case 12:
                dd_12 = reinterpret_cast<DevDesc12*>(dd);
                break;
            }
        }

        void* devicewrapper::allocate() {
            int ver = R_GE_getVersion();
            switch (ver) {
            case 11: return rhost::msvcrt::calloc(1, sizeof(DevDesc11));
            case 12: return rhost::msvcrt::calloc(1, sizeof(DevDesc12));
            default: return nullptr;
            }
        }

        pDevDesc devicewrapper::get_pDevDesc() {
            switch (_ver) {
            case 11: return reinterpret_cast<pDevDesc>(dd_11);
            case 12: return reinterpret_cast<pDevDesc>(dd_12);
            default: return nullptr;
            }
        }

        RHOST_DEV_DESC_V11(RHOST_DEV_WRAPPER_DEFINE_GETSET_COMMON)
        RHOST_DEV_DESC_V11_ARRAY(RHOST_DEV_WRAPPER_DEFINE_GETSET_COMMON_ARRAY)
        RHOST_DEV_DESC_V12(RHOST_DEV_WRAPPER_DEFINE_GETSET_V12)
    }
}
