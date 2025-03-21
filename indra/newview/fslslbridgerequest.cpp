/**
 * @file fslslbridgerequest.cpp
 * @brief FSLSLBridgerequest implementation
 *
 * $LicenseInfo:firstyear=2011&license=fsviewerlgpl$
 * Phoenix qikfox3D Viewer Source Code
 * Copyright (C) 2011, The Phoenix qikfox3D Project, Inc.
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
 * The Phoenix qikfox3D Project, Inc., 1831 Oakwood Drive, Fairmont, Minnesota 56031-3225 USA
 * http://www.qikfox3Dviewer.org
 * $/LicenseInfo$
 */

#include "llviewerprecompiledheaders.h"

#include "fslslbridgerequest.h"
#include "fsradar.h"
#include "llsdutil.h"
#include "llcorehttputil.h"

#include <boost/tokenizer.hpp>


//If we get back a normal response, handle it here
void FSLSLBridgeRequest_Success(LLSD const &aData)
{
    LL_DEBUGS("FSLSLBridge") << ll_pretty_print_sd(aData) << LL_ENDL;
    //do not use - infinite loop, only here for testing.
    //FSLSLBridge::instance().viewerToLSL("Response_to_response|" + strContent);
}

//If we get back an error (not found, etc...), handle it here
void FSLSLBridgeRequest_Failure(LLSD const &aData)
{
    LL_WARNS("FSLSLBridge") << "FSLSLBridgeRequest::error(" << ll_pretty_print_sd(aData) << ")" << LL_ENDL;
}

void FSLSLBridgeRequestRadarPos_Success(LLSD const &aData)
{
    LL_DEBUGS("FSLSLBridge") << ll_pretty_print_sd(aData) << LL_ENDL;
    if (aData.has(LLCoreHttpUtil::HttpCoroutineAdapter::HTTP_RESULTS_CONTENT))
    {
        std::string strContent = aData[LLCoreHttpUtil::HttpCoroutineAdapter::HTTP_RESULTS_CONTENT].asString();
        //LL_INFOS("FSLSLBridge") << "Got info: " << strContent << LL_ENDL;
        // AO: parse content into pairs of [agent UUID,agent zHeight] , update our radar for each one

        LLUUID targetAv;
        F32 targetZ;

        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        boost::char_separator<char> sep(", ");
        tokenizer tokens(strContent, sep);
        for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
        {
            targetAv = LLUUID(*(tok_iter++));
            targetZ = (F32)::atof((*tok_iter).c_str());

            if (auto entry = FSRadar::getInstance()->getEntry(targetAv); entry)
            {
                entry->setZOffset(targetZ);
                //LL_INFOS("FSLSLBridge") << targetAv << " ::: " << targetZ << LL_ENDL;
            }
        }
    }
}
