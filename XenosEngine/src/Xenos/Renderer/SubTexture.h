#pragma once
#include "Texture.h"
#include <glm/glm.hpp>

namespace Xenos
{
	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2 minBound, const glm::vec2 maxBound);

		const glm::vec2* GetTexCoords() const { return m_TexCoords; }
		const Ref<Texture2D> GetTexture() const { return m_Texture; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1,1 });

	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];
	};

}

