/*! \file svdreport.cpp
 * \brief Aggregate User Statistics module.
 *
 * $Id$
 *
 */

#include "copyright.h"
#include "autoconf.h"
#include "config.h"
#include "externs.h"

#include "attrs.h"
#include "command.h"

#define NPERIODS 24
void do_report(dbref executor, dbref caller, dbref enactor, int extra)
{
    UNUSED_PARAMETER(caller);
    UNUSED_PARAMETER(enactor);
    UNUSED_PARAMETER(extra);

    UTF8 *buff = alloc_mbuf("do_report");
    int nBin[NPERIODS];
    int i;

    for (i = 0; i < NPERIODS; i++)
    {
        nBin[i] = 0;
    }

    CLinearTimeAbsolute ltaNow, ltaPlayer;
    ltaNow.GetLocal();

    const int PeriodInSeconds = 28800;

    int iPlayer;
    DO_WHOLE_DB(iPlayer)
    {
        if (isPlayer(iPlayer))
        {
            int aowner, aflags;
            UTF8 *player_last = atr_get("do_report.43", iPlayer, A_LAST, &aowner, &aflags);

            if (ltaPlayer.SetString(player_last))
            {
                CLinearTimeDelta ltd(ltaPlayer, ltaNow);
                int ltdSeconds = ltd.ReturnSeconds();
                int iBin = ltdSeconds / PeriodInSeconds;
                if (0 <= iBin && iBin < NPERIODS)
                {
                    nBin[iBin]++;
                }
            }
            free_lbuf(player_last);
        }
    }

    int iHour, nSum = 0;
    notify(executor, T("Day   Hours     Players  Total"));
    for (i = 0, iHour = 0; i < NPERIODS; i++, iHour += 8)
    {
        nSum += nBin[i];
        mux_sprintf(buff, MBUF_SIZE, "%3d %03d - %03d: %6d %6d",
            iHour/24 + 1, iHour, iHour+8, nBin[i], nSum);
        notify(executor, buff);
    }
    free_mbuf(buff);
}

