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
# include <memory>
# include "Fwd.hpp"
# include "NamedParameter.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "Optional.hpp"

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

namespace s3d
{
	struct XMLElementDetail
	{
		std::shared_ptr<tinyxml2::XMLDocument> document;

		const tinyxml2::XMLElement* element;

		XMLElementDetail() = default;

		XMLElementDetail(const std::shared_ptr<tinyxml2::XMLDocument>& doc, const tinyxml2::XMLElement* elem);
	};

	class XMLElement
	{
	protected:

		std::unique_ptr<XMLElementDetail> m_detail;
	
	public:

		XMLElement();

		XMLElement(const std::shared_ptr<tinyxml2::XMLDocument>& doc, const tinyxml2::XMLElement* element);

		bool isNull() const;

		explicit operator bool() const
		{
			return !isNull();
		}

		String name() const;

		String text() const;

		XMLElement firstChild() const;

		XMLElement nextSibling() const;

		XMLElement parent() const;

		Array<std::pair<String, String>> attributes() const;

		Optional<String> attribute(const String& name) const;
	};

	class XMLReader : public XMLElement
	{
	public:

		XMLReader() = default;

		explicit XMLReader(const FilePath& path, bool preserveWhitespace = false);

		explicit XMLReader(Arg::code_<String> code, bool preserveWhitespace = false);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		explicit XMLReader(Reader&& reader, bool preserveWhitespace = false)
			: XMLReader()
		{
			open(std::make_shared<Reader>(std::forward<Reader>(reader)), preserveWhitespace);
		}

		explicit XMLReader(const std::shared_ptr<IReader>& reader, bool preserveWhitespace = false);

		bool open(const FilePath& path, bool preserveWhitespace = false);

		bool open(Arg::code_<String> code, bool preserveWhitespace = false);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader, bool preserveWhitespace = false)
		{
			return open(std::make_shared<Reader>(std::forward<Reader>(reader)), preserveWhitespace);
		}

		bool open(const std::shared_ptr<IReader>& reader, bool preserveWhitespace = false);

		void close();

		bool isOpend() const;

		explicit operator bool() const
		{
			return isOpend();
		}
	};
}
