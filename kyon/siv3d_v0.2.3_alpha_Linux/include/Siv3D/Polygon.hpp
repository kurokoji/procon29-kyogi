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
# include "Array.hpp"
# include "PointVector.hpp"

namespace s3d
{
	class Polygon
	{
	private:

		class CPolygon;

		std::unique_ptr<CPolygon> pImpl;

	public:

		Polygon();

		Polygon(const Polygon& polygon);

		Polygon(Polygon&& polygon);

		Polygon(const Vec2* outer, size_t size, const Array<Array<Vec2>>& holes = {});

		explicit Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes = {})
			: Polygon(outer.data(), outer.size(), holes) {}

		Polygon(const Array<Vec2>& outer, const Array<uint32>& indices, const RectF& boundingRect);

		Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<Float2>& vertices, const Array<uint32>& indices, const RectF& boundingRect);

		Polygon(const Shape2D& shape);

		explicit Polygon(std::initializer_list<Vec2> outer)
			: Polygon(outer.begin(), outer.size()) {}

		~Polygon();

		Polygon& operator =(const Polygon& polygon);

		Polygon& operator =(Polygon&& polygon);

		explicit operator bool() const { return !isEmpty(); }

		bool isEmpty() const;

		bool hasHoles() const;

		size_t num_holes() const;

		void swap(Polygon& polygon) noexcept;

		const Array<Vec2>& outer() const;

		const Array<Array<Vec2>>& inners() const;

		const Array<Float2>& vertices() const;
		
		const Array<uint32>& indices() const;
		
		const RectF& boundingRect() const;

		size_t num_triangles() const;

		Triangle triangle(size_t index) const;

		Polygon& addHole(const Array<Vec2>& hole);

		Polygon& addHoles(const Array<Array<Vec2>>& holes);

		Polygon movedBy(double x, double y) const;

		Polygon movedBy(const Vec2& v) const
		{
			return movedBy(v.x, v.y);
		}

		Polygon& moveBy(double x, double y);

		Polygon& moveBy(const Vec2& v)
		{
			return moveBy(v.x, v.y);
		}

		Polygon rotated(double angle) const;

		Polygon rotatedAt(const Vec2& pos, double angle) const;

		Polygon& rotate(double angle);

		Polygon& rotateAt(const Vec2& pos, double angle);

		Polygon transformed(double s, double c, const Vec2& pos) const;

		Polygon& transform(double s, double c, const Vec2& pos);

		Polygon scaled(double s) const;

		Polygon& scale(double s);

		double area() const;

		double perimeter() const;

		Vec2 centroid() const;

		Polygon calculateConvexHull() const;

		Polygon calculateBuffer(double distance) const;

		Polygon calculateRoundBuffer(double distance) const;

		Polygon simplified(double maxDistance = 2.0) const;

		bool append(const Polygon& polygon);

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		bool intersects(const Polygon& polygon) const;

		template <class Shape2DType>
		bool contains(const Shape2DType& shape) const
		{
			return Geometry2D::Contains(*this, shape);
		}

		bool leftClicked() const;

		bool leftPressed() const;

		bool leftReleased() const;

		bool rightClicked() const;

		bool rightPressed() const;

		bool rightReleased() const;

		bool mouseOver() const;

		const Polygon& paint(Image& dst, const Color& color) const;

		const Polygon& paint(Image& dst, double x, double y, const Color& color) const;

		const Polygon& paint(Image& dst, const Vec2& pos, const Color& color) const;

		const Polygon& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		const Polygon& overwrite(Image& dst, double x, double y, const Color& color, bool antialiased = true) const;

		const Polygon& overwrite(Image& dst, const Vec2& pos, const Color& color, bool antialiased = true) const;

		const Polygon& draw(const ColorF& color = Palette::White) const;

		void draw(double x, double y, const ColorF& color = Palette::White) const;

		void draw(const Vec2& pos, const ColorF& color = Palette::White) const;

		//const Polygon& draw(const Array<ColorF>& colors) const;

		const Polygon& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Polygon& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawTransformed(double s, double c, const Vec2& pos, const ColorF& color = Palette::White) const;

		const CPolygon* _detail() const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Polygon& value)
	{
		output << CharType('(');

		output << CharType('(');

		bool b = false;

		for (const auto& point : value.outer())
		{
			if (std::exchange(b, true))
			{
				output << CharType(',');
			}

			output << point;
		}

		output << CharType(')');

		if (value.inners())
		{
			output << CharType(',');

			output << CharType('(');

			b = false;

			for (const auto& hole : value.inners())
			{
				if (std::exchange(b, true))
				{
					output << CharType(',');

					output << CharType('(');
				}

				bool b2 = false;

				for (const auto& point : hole)
				{
					if (std::exchange(b2, true))
					{
						output << CharType(',');
					}

					output << point;
				}

				output << CharType(')');
			}
		}

		return output << CharType(')');
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{

}

//////////////////////////////////////////////////
//
//	Swap
//
//////////////////////////////////////////////////

namespace std
{
	inline void swap(s3d::Polygon& a, s3d::Polygon& b) noexcept
	{
		a.swap(b);
	}
}
