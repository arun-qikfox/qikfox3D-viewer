/**
 * @file floatermedialists.cpp
 * @brief Floater to edit media white/blacklists - implementation
 *
 * $LicenseInfo:firstyear=2011&license=fsviewerlgpl$
 * Phoenix qikfox3D Viewer Source Code
 * Copyright (C) 2011, Sione Lomu
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
 * $/LicenseInfo$
 */
#include "llviewerprecompiledheaders.h"

#include "floatermedialists.h"
#include "llfloaterreg.h"
#include "llnotificationsutil.h"
#include "llscrolllistctrl.h"
#include "lltrans.h"
#include "llviewerparcelmedia.h"

FloaterMediaLists::FloaterMediaLists(const LLSD& key) :
    LLFloater(key)
{
}

bool FloaterMediaLists::postBuild()
{
    mWhitelistSLC = getChild<LLScrollListCtrl>("whitelist");
    mBlacklistSLC = getChild<LLScrollListCtrl>("blacklist");

    childSetAction("add_whitelist", boost::bind(&FloaterMediaLists::onWhitelistAdd, this));
    childSetAction("remove_whitelist", boost::bind(&FloaterMediaLists::onWhitelistRemove, this));
    childSetAction("add_blacklist", boost::bind(&FloaterMediaLists::onBlacklistAdd, this));
    childSetAction("remove_blacklist", boost::bind(&FloaterMediaLists::onBlacklistRemove, this));

    for (LLSD::array_iterator p_itr = LLViewerParcelMedia::getInstance()->mMediaFilterList.beginArray();
         p_itr != LLViewerParcelMedia::getInstance()->mMediaFilterList.endArray();
         ++p_itr)
    {
        LLSD itr = (*p_itr);
        LLSD element;
        element["columns"][0]["column"] = "list";
        element["columns"][0]["value"] = itr["domain"].asString();
        if (itr["action"].asString() == "allow")
        {
            mWhitelistSLC->addElement(element);
        }
        else if (itr["action"].asString() == "deny")
        {
            mBlacklistSLC->addElement(element);
        }
    }

    mWhitelistSLC->sortByColumn("list", true);
    mBlacklistSLC->sortByColumn("list", true);

    return true;
}

void FloaterMediaLists::onWhitelistAdd()
{
    LLSD payload, args;
    args["LIST"] = LLTrans::getString("MediaFilterWhitelist");
    payload["whitelist"] = true;
    LLNotificationsUtil::add("AddToMediaList", args, payload, &FloaterMediaLists::handleAddDomainCallback);
}

void FloaterMediaLists::onWhitelistRemove()
{
    LLScrollListItem* selected = mWhitelistSLC->getFirstSelected();

    if (selected)
    {
        std::string domain = mWhitelistSLC->getSelectedItemLabel();

        LLViewerParcelMedia* inst = LLViewerParcelMedia::getInstance();
        for (S32 i = 0; i < (S32)inst->mMediaFilterList.size(); ++i)
        {
            if (inst->mMediaFilterList[i]["domain"].asString() == domain)
            {
                inst->mMediaFilterList.erase(i);
                inst->saveDomainFilterList();
                //HACK: should really see if the URL being deleted
                //  is the same as the saved one
                inst->mMediaLastURL = "";
                inst->mAudioLastURL = "";
                inst->mMediaReFilter = true;
                break;
            }
        }
        mWhitelistSLC->deleteSelectedItems();
    }
}

void FloaterMediaLists::onBlacklistAdd()
{
    LLSD payload, args;
    args["LIST"] = LLTrans::getString("MediaFilterBlacklist");
    payload["whitelist"] = false;
    LLNotificationsUtil::add("AddToMediaList", args, payload, &FloaterMediaLists::handleAddDomainCallback);
}

void FloaterMediaLists::onBlacklistRemove()
{
    LLScrollListItem* selected = mBlacklistSLC->getFirstSelected();

    if (selected)
    {
        std::string domain = mBlacklistSLC->getSelectedItemLabel();

        LLViewerParcelMedia* inst = LLViewerParcelMedia::getInstance();
        for (S32 i = 0; i < (S32)inst->mMediaFilterList.size(); ++i)
        {
            if (inst->mMediaFilterList[i]["domain"].asString() == domain)
            {
                inst->mMediaFilterList.erase(i);
                inst->saveDomainFilterList();
                //HACK: should really see if the URL being deleted
                //  is the same as the saved one
                inst->mMediaLastURL = "";
                inst->mAudioLastURL = "";
                inst->mMediaReFilter = true;
                break;
            }
        }

        mBlacklistSLC->deleteSelectedItems();
    }
}

//static
bool FloaterMediaLists::handleAddDomainCallback(const LLSD& notification, const LLSD& response)
{
    S32 option = LLNotificationsUtil::getSelectedOption(notification, response);
    if (option == 0)
    {
        LLViewerParcelMedia* inst = LLViewerParcelMedia::getInstance();
        const std::string domain = inst->extractDomain(response["url"].asString());
        if (domain.empty())
        {
            LL_INFOS("MediaFilter") << "No domain specified" << LL_ENDL;
            return false;
        }

        bool whitelist = notification["payload"]["whitelist"].asBoolean();
        LLSD newmedia;
        newmedia["domain"] = domain;
        newmedia["action"] = (whitelist ? "allow" : "deny");
        inst->mMediaFilterList.append(newmedia);
        inst->saveDomainFilterList();

        LLFloater* floater = LLFloaterReg::findInstance("media_lists");
        if (floater)
        {
            LLScrollListCtrl* list = floater->getChild<LLScrollListCtrl>(whitelist ? "whitelist" : "blacklist");
            LLSD element;
            element["columns"][0]["column"] = "list";
            element["columns"][0]["value"] = domain;

            list->addElement(element);
            list->sortByColumn("list", true);
        }
    }
    return false;
}
