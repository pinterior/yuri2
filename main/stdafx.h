#pragma once

#include "../common/targetver.h"

#include <cstdlib>
#include <memory>
#include <type_traits>
#include <utility>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <atlbase.h>
#include <atlapp.h>
#include <atlcrack.h>
#include <atlmisc.h>
#include <atlctrls.h>

#include "../common/hook.h"

#include "resource.h"

#include "dialog.h"
#include "game.h"
#include "main.h"
#include "message.h"
