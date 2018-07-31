﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "LetterCase.hpp"

namespace s3d
{
	[[nodiscard]] String ToString(bool value, LetterCase letterCase = LetterCase::Lower);
}
