#include "Barracks.h"

#include "../../../../main.h"

#include "../../../../engine/UI/Widget.h"
#include "../../../../engine/UI/Button.h"
#include "../../../../engine/UI/Image.h"
#include "../../../../engine/UI/ProgressBar.h"

#include "../../../../engine/managers/EngineManager.h"
#include "../../../../engine/managers/HUDManager.h"
#include "../../../../engine/managers/RenderManager.h"

Barracks::Barracks(const glm::ivec2& position) :
    Building(position, glm::ivec2(3), EBuildingType::EBT_Barracks)
{
    _wdg = GetEngine()->GetHUDManager()->CreateWidget();
}

Barracks::~Barracks()
{
    if(_wdg)
    {
        _wdg->Destroy();
    }
}

void Barracks::Replace()
{
    ConfigureUI();
    Building::Replace();
    SetSelected(_is_selected);
}

void Barracks::ConfigureUI()
{
    if(_wdg)
    {
        glm::vec2 start_position = glm::vec2(500.f, 10.f);
        glm::vec2 size = glm::vec2(70.f, 70.f);
        std::vector<std::string> units_buttons_images = { "mush1", "mush2", "mush3"};
        for(int i = 0; i < units_buttons_images.size(); ++i)
        {
            glm::vec2 current_pos = start_position + glm::vec2(size.x * i, 0);
            Button* button = _wdg->AddElement<Button>(current_pos, size);
            Renderer::Sprite* spr = GetEngine()->GetRenderManager()->CreateSprite<Renderer::Sprite>(nullptr
                                                                                                    , current_pos
                                                                                                    , size, units_buttons_images[i], BUTTON);
            Image* img = _wdg->AddElement<Image>(current_pos, size);
            img->SetSprite(spr);
            button->SetFilling(img);
        }

        ProgressBar* progress_bar = _wdg->AddElement<ProgressBar>(start_position + glm::vec2((units_buttons_images.size() + 1) * size.x, 0.f), glm::vec2(size.x * 3, size.y));
        progress_bar->SetEmptySpriteByName("emptyProgressBar");
	    progress_bar->SetFullSpriteByName("fullProgressBar");
        progress_bar->SetPercentage(0.1f);
    }
    else
    {
#ifdef DEBUG
        std::cout << "Widget is nullptr\n"; 
#endif
    }
}

void Barracks::SetSelected(bool is_selected)
{
    Pawn::SetSelected(is_selected);

    size_t size = _wdg->GetUIElementsCount();

    for(size_t i = 0; i < size; ++i)
    {
        _wdg->GetElement(i)->SetRender(_is_selected);
    }   
}

template<typename T>
void Barracks::StartTraining()
{
    
}