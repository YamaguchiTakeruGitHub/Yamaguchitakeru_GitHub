#pragma once



namespace TKRLib
{
	class ColliderData abstract
	{
	public:

		enum class Kind
		{
			Sphere,
			Line2D			
		};

		ColliderData(Kind kind) { this->kind = kind; }
		virtual ~ColliderData() {}
		Kind GetKind() const { return kind; }

	private:
		Kind kind;
	};
}