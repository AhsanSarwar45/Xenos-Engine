#include "xenospch.h"
#include "InputMapping.h"
#include "magic_enum.hpp"

namespace Xenos
{
	std::string_view GetActionString(Action action)
	{
		return magic_enum::enum_name(action);
	}
	std::string_view GetContextString(Context context)
	{
		return magic_enum::enum_name(context);
	}
}