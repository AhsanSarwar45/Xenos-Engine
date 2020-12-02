#include "xenospch.h"
#include "SubTexture.h"


namespace Xenos
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2 minBound, const glm::vec2 maxBound)
		:m_Texture(texture)
	{
		m_TexCoords[0] = { minBound.x, minBound.y };
		m_TexCoords[1] = { maxBound.x, minBound.y };
		m_TexCoords[2] = { maxBound.x, maxBound.y };
		m_TexCoords[3] = { minBound.x, maxBound.y };
	}
	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min{ (coords.x * cellSize.x) / texture->GetWidth() , (coords.y * cellSize.y) / texture->GetHeight() };
		glm::vec2 max{ ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth() , ((coords.y + spriteSize.y) * cellSize.x) / texture->GetHeight() };
		
		return  CreateRef<SubTexture2D>(texture, min, max);

	}
}