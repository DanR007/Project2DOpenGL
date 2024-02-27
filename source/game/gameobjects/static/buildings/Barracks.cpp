#include "Barracks.h"

#include "../../units/Unit.h"

#include "../../units/army/Soldier.h"
#include "../../units/army/RangeSoldier.h"

#include "../../../../main.h"

#include "../../../../engine/UI/Widget.h"
#include "../../../../engine/UI/Button.h"
#include "../../../../engine/UI/Image.h"
#include "../../../../engine/UI/ProgressBar.h"

#include "../../../../engine/managers/GameManager.h"
#include "../../../../engine/managers/EngineManager.h"
#include "../../../../engine/managers/HUDManager.h"
#include "../../../../engine/managers/RenderManager.h"

#include "../../../../engine/AI/NavMesh.h"

#include "../../../../engine/controllers/PlayerController.h"

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

void Barracks::Update(const float& deltaTime)
{
    if(_is_training)
    {
        _current_training_time += deltaTime;
    }

    if(GetIsSelected())
    {
        int progress_bar_index = _wdg->GetUIElementsCount() - 1;

        ProgressBar* progress_bar = static_cast<ProgressBar*>(_wdg->GetElement(progress_bar_index));
        if(progress_bar)
        {
            float percantage = _is_training ? _current_training_time / _max_training_time : 0.f;
            progress_bar->SetPercentage(percantage);
        }
    }

    Pawn::Update(deltaTime);
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
        std::vector<void(Barracks::*)()> _button_on_click_events = { &Barracks::TrainMelee, &Barracks::TrainRange, &Barracks::TrainStrongMelee };
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
            button->SetOnClickEvent(this, _button_on_click_events[i]);
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
    _free_place_around_building = GetFreePositionAroundBuilding();

    if(_free_place_around_building == glm::ivec2(-2))
    {
#ifdef DEBUG
    std::cout << "Нет свободного места вокруг казармы\n";
#endif
        return;
    }

    //выставляем солдата в точку, где его не будет видно
    glm::ivec2 start_pos = GetWorld()->GetSizeMap() + glm::ivec2(100);

    T* t = GetEngine()->GetWorld()->SpawnActor<T>(start_pos);
    if(dynamic_cast<Soldier*>(t))
    {
        _new_unit = dynamic_cast<Soldier*>(t);
    }
    else
    {
#ifdef DEBUG
        std::cout << "Ты че шиз? Почему то, что появляется в казарме не является Soldier?\n";
#endif
        dynamic_cast<Object*>(t)->Destroy();
        return;
    }

    if(GetEngine()->GetWorld()->GetPlayerController(_player_id)->EnoughResources(_new_unit->GetCost()))
    {
        GetEngine()->GetWorld()->GetPlayerController(_player_id)->MinusResources(_new_unit->GetCost());
    }
    else
    {
        _new_unit->Destroy();
        return;
    }

    _is_training = true;

    _max_training_time = _new_unit->GetTrainingTime();
    _current_training_time = 0.f;
    GetEngine()->Invoke(this, &Barracks::EndTrainig, _max_training_time);
}

void Barracks::EndTrainig()
{
    if(GetEngine()->GetWorld()->GetNavMesh()->IsFreeCell(_free_place_around_building))
    {
        glm::vec2 pos = GetEngine()->GetWorld()->ConvertToWindowSpace(_free_place_around_building);
        _new_unit->SetMapPosition(_free_place_around_building);
        _new_unit->SetPosition(pos);
        _new_unit->Replace();

        _is_training = false;
    }
}

void Barracks::TrainMelee()
{
    std::cout << "Train Melee\n";
}
void Barracks::TrainRange()
{
    std::cout << "Train Range\n";
    StartTraining<RangeSoldier>();
}
void Barracks::TrainStrongMelee()
{
    std::cout << "Train Strong Melee\n";
}