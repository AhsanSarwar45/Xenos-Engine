#include "SpriteEditorWindow.h"
#include <imgui/imgui.h>

void Xenos::SpriteEditorWindow::ShowWindow(Ref<Texture2D>& texture)
{
	ImGui::Begin("Tilemap");

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	static ImVector<ImVec2> points;
	static ImVec2 scrolling(0.0f, 0.0f);
	static bool opt_enable_grid = true;
	static bool opt_enable_context_menu = true;
	static bool adding_line = false;
	static bool snapping = true;
	static int gridSize = 32;
	static ImVec2 startPos;


	ImGui::InputInt("Grid Size", &gridSize, 4);
	ImGui::Checkbox("Enable grid", &opt_enable_grid);
	ImGui::Checkbox("Enable context menu", &opt_enable_context_menu);
	ImGui::Checkbox("Enable Snapping", &snapping);
	ImGui::Text("Mouse Left: drag to add lines,\nMouse Right: drag to scroll, click for context menu.");

	if (gridSize < 4) gridSize = 4;

	ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();

	float sizeAvailable = ImGui::GetContentRegionAvailWidth();
	float ratio = sizeAvailable / (float)texture->GetWidth();

	ImVec2 canvas_sz = ImVec2(sizeAvailable, (float)texture->GetHeight() * ratio);
	if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
	if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
	ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

	//ImGui::InvisibleButton("canvas", ImVec2{ sizeAvailable, (float)m_SpriteSheet->GetHeight() * ratio });

	/*if (is_hovered && abs(ImGui::GetScrollY()) > 0)
	{
		zoomLevel += ImGui::GetScrollY() * 0.05f;
	}*/

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.3f, 0.3f, 0.3f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.3f, 0.3f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.3f, 0.3f, 0.0f });
	ImGui::ImageButton((void*)texture->GetRendererID(), ImVec2{ sizeAvailable, (float)texture->GetHeight() * ratio }, ImVec2{ 0,1 }, ImVec2{ 1, 0 }, 0);
	bool hovered = ImGui::IsItemHovered();

	if (hovered && !adding_line && ImGui::IsMouseClicked(0))
	{
		startPos = ImGui::GetMousePos();
		
		if (snapping)
		{
			float effGridSize = gridSize * ratio;
			startPos.x = canvas_p0.x + floorf((startPos.x - canvas_p0.x) / effGridSize) * effGridSize;
			startPos.y = canvas_p0.y + floorf((startPos.y - canvas_p0.y) / effGridSize) * effGridSize;;
		}
		adding_line = true;
	}
	if (hovered && adding_line)
	{
		ImVec4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
		const ImU32 col32 = ImColor(color);
		ImVec2 endPos = ImGui::GetMousePos();
		if (snapping)
		{
			float effGridSize = gridSize * ratio;
			endPos.x = canvas_p0.x + floorf((endPos.x - canvas_p0.x) / effGridSize) * effGridSize;
			endPos.y = canvas_p0.y + floorf((endPos.y - canvas_p0.y) / effGridSize) * effGridSize;;
		}

		draw_list->AddRect(ImVec2(startPos.x, startPos.y), endPos, col32, 0.0f, ImDrawCornerFlags_All, 0.8f);

		//points.back() = mouse_pos_in_canvas;
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
			adding_line = false;
	}

	ImGui::PopStyleColor(3);
	if (opt_enable_grid)
	{

		for (float x = 0; x < canvas_sz.x / ratio + 1.0f; x += gridSize)
		{
			draw_list->AddLine(ImVec2(canvas_p0.x + (x * ratio), canvas_p0.y), ImVec2(canvas_p0.x + (x * ratio), canvas_p1.y), IM_COL32(200, 0, 0, 50));
		}

		for (float y = 0; y < canvas_sz.y / ratio + 1.0f; y += gridSize)
			draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + (y * ratio)), ImVec2(canvas_p1.x, canvas_p0.y + (y * ratio)), IM_COL32(200, 0, 0, 50));
	}


	ImGui::End();
}
