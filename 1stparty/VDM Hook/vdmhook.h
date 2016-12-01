#pragma once

#ifdef VDMHOOK_EXPORTS
# define VDMHOOK_EXPORT extern "C" __declspec(dllexport)
#else
# define VDMHOOK_EXPORT extern "C" __declspec(dllimport)
#endif