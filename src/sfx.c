#include "sfx.h"
#include "resources.h"

#include <windows.h>
#include <mmsystem.h>

static void s_play_resource_async(int rc_id)
{
    PlaySound(MAKEINTRESOURCE(rc_id), NULL, SND_RESOURCE | SND_ASYNC);
}

void gk_sfx_success(void)
{
    s_play_resource_async(IDR_SFX_SUCCESS);
}

void gk_sfx_failure(void)
{
    s_play_resource_async(IDR_SFX_FAILURE);
}