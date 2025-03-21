/** 
 * @file llviewerprecompiledheaders.h
 * @brief precompiled headers for newview project
 * @author James Cook
 *
 * $LicenseInfo:firstyear=2005&license=viewerlgpl$
 * Second Life Viewer Source Code
 * Copyright (C) 2010, Linden Research, Inc.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 2.1 of the License only.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * Linden Research, Inc., 945 Battery Street, San Francisco, CA  94111  USA
 * $/LicenseInfo$
 */


#ifndef LL_LLVIEWERPRECOMPILEDHEADERS_H
#define LL_LLVIEWERPRECOMPILEDHEADERS_H

#include "llwin32headers.h"

// This file MUST be the first one included by each .cpp file
// in viewer.
// It is used to precompile headers for improved build speed.

#include "linden_common.h"

#include <algorithm>
#include <deque>
#include <functional>
#include <map>
#include <set>
#include <vector>

// Library headers from llcommon project:
#include "indra_constants.h"
#include "llinitparam.h"
#include "llapp.h"
#include "llcriticaldamp.h"
#include "lldefs.h"
#include "lldepthstack.h"
#include "llerror.h"
#include "llfasttimer.h"
#include "llframetimer.h"
#include "llpointer.h"
#include "llprocessor.h"
#include "llrefcount.h"
#include "llsafehandle.h"
#include "llsd.h"
#include "llsingleton.h"
#include "llstl.h"
#include "llstrider.h"
#include "llstring.h"
#include "llsys.h"
#include "lltimer.h"
#include "stdtypes.h"
#include "u64.h"

// Library includes from llmath project
#include "llmath.h"
#include "llbboxlocal.h"
#include "llcamera.h"
#include "llcoord.h"
#include "llcoordframe.h"
#include "llcrc.h"
#include "llplane.h"
#include "llquantize.h"
#include "llrand.h"
#include "llrect.h"
#include "lluuid.h"
#include "m3math.h"
#include "m4math.h"
#include "llquaternion.h"
#include "v2math.h"
#include "v3color.h"
#include "v3dmath.h"
#include "v3math.h"
#include "v4color.h"
#include "v4coloru.h"
#include "v4math.h"
#include "xform.h"

#include "lldir.h"

// Library includes from llmessage project
#include "llcachename.h"

// qikfox3D additions
#include "llavatarname.h"
#include "llavatarnamecache.h"
#include "llcorehttputil.h"
#include "llfloater.h"
#include "llformat.h"
#include "llmatrix4a.h"
#include "llpanel.h"
#include "lluictrl.h"
#include "llvector4a.h"
#include "llview.h"
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/signals2.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/function/function1.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#endif
