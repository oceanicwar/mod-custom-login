/*

# Custom Login Modifications - modified by Jeremy #

### Credits ###
------------------------------------------------------------------------------------------------------------------
#### A module for AzerothCore by StygianTheBest ([stygianthebest.github.io](http://stygianthebest.github.io)) ####

*/

#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "ScriptMgr.h"
#include "GuildMgr.h"

bool LoginEnable = 1;
bool LoginAnnounceModule = 1;
bool LoginPlayerAnnounce = 1;

class LoginConfig : public WorldScript
{
public:
    LoginConfig() : WorldScript("LoginConfig") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            // Load Configuration Settings
            SetInitialWorldSettings();
        }
    }

    // Load Configuration Settings
    void SetInitialWorldSettings()
    {
        LoginEnable = sConfigMgr->GetOption<bool>("Login.Enable", 1);
        LoginAnnounceModule = sConfigMgr->GetOption<bool>("Login.Announce", 1);
        LoginPlayerAnnounce = sConfigMgr->GetOption<bool>("Login.PlayerAnnounce", 1);
    }
};

class LoginAnnounce : public PlayerScript
{

public:

    LoginAnnounce() : PlayerScript("LoginAnnounce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (LoginEnable)
        {
            if (LoginAnnounceModule)
            {
                ChatHandler(player->GetSession()).SendSysMessage("");
            }
        }
    }
};

class CustomLogin : public PlayerScript
{

public:
    CustomLogin() : PlayerScript("CustomLogin") { }

    void OnLogin(Player* player)
    {
        // If enabled..
        if (LoginEnable)
        {
            // If enabled..
            if (LoginPlayerAnnounce)
            {
                // Announce Player Login
                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    std::ostringstream ss;
                    ss << "|cffFFFFFF[|cff2897FF Alliance |cffFFFFFF]:|cff4CFF00 " << player->GetName() << "|cffFFFFFF has come online.";
                    sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                }
                else
                {
                    std::ostringstream ss;
                    ss << "|cffFFFFFF[|cffFF0000 Horde |cffFFFFFF]:|cff4CFF00 " << player->GetName() << "|cffFFFFFF has come online.";
                    sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                }
            }
        }
    }

    void OnLogout(Player *player)
    {
        if (LoginEnable)
        {
            // If enabled..
            if (LoginPlayerAnnounce)
            {
                // Announce Player Login
                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    std::ostringstream ss;
                    ss << "|cffFFFFFF[|cff2897FF Alliance |cffFFFFFF]:|cff4CFF00 " << player->GetName() << "|cffFFFFFF has gone offline.";
                    sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                }
                else
                {
                    std::ostringstream ss;
                    ss << "|cffFFFFFF[|cffFF0000 Horde |cffFFFFFF]:|cff4CFF00 " << player->GetName() << "|cffFFFFFF has gone offline.";
                    sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                }
            }
        }
    }
};

void AddCustomLoginScripts()
{
    new LoginConfig();
    new LoginAnnounce();
    new CustomLogin();
}
