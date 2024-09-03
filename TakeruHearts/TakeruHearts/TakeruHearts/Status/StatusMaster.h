#pragma once

namespace Status
{

	class StatusMaster
	{
	public:
		StatusMaster();

		void Init();

		const float& GetHP() const { return HitPoint; }
		const float& GetMP() const { return MagicPoint; }

		void SetHP(const float& set) { HitPoint = set; }
		void SetMP(const float& set) { MagicPoint = set; }

	private:
		float HitPoint;
		float MagicPoint;

	};

}
