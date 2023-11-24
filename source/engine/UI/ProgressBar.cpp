#include "ProgressBar.h"

#include "../../main.h"

#include "../renderer/Sprite.h"

#include "../managers/EngineManager.h"
#include "../managers/RenderManager.h"

ProgressBar::ProgressBar(const glm::vec2& position, const glm::vec2& size):
    UIElement(position, size)
{
    _percentage = 0.f;
    _full_sprite = nullptr;
    _empty_sprite = nullptr;
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::SetPercentage(const float& percentage)
{
    _percentage = percentage;

    if(_full_sprite)
    {
        glm::vec2 size = GetSize();

        _full_sprite->SetSize(glm::vec2(size.x * _percentage, size.y));
    }
}

void ProgressBar::SetFullSprite(Renderer::Sprite* full)
{
    if(_full_sprite)
    {
        _full_sprite->Destroy();
    }

    _full_sprite = full;
    Attach(_full_sprite);

    glm::vec2 size = GetSize();

    _full_sprite->SetPosition(GetPosition());
    _full_sprite->SetSize(glm::vec2(size.x * _percentage, size.y));
}

void ProgressBar::SetEmptySprite(Renderer::Sprite* empty)
{
    if(_empty_sprite)
    {
        _empty_sprite->Destroy();
    }

    _empty_sprite = empty;
    Attach(_empty_sprite);

    _empty_sprite->SetPosition(GetPosition());
    _empty_sprite->SetSize(GetSize());
}

void ProgressBar::SetFullSpriteByName(const std::string& full_name)
{
    if(_full_sprite)
    {
        _full_sprite->Destroy();
    }
    glm::vec2 size = GetSize();

    _full_sprite = GetEngine()->GetRenderManager()->CreateSprite<Renderer::Sprite>(this
                                                                                    , GetPosition()
                                                                                    , glm::vec2(size.x * _percentage, size.y)
                                                                                    , full_name
                                                                                    , "textureAtlas"
                                                                                    , TEXT_IMAGES);
}

void ProgressBar::SetEmptySpriteByName(const std::string& empty_name)
{
    if(_empty_sprite)
    {
        _empty_sprite->Destroy();
    }

    _empty_sprite = GetEngine()->GetRenderManager()->CreateSprite<Renderer::Sprite>(this
                                                                                    , GetPosition()
                                                                                    , GetSize()
                                                                                    , empty_name
                                                                                    , "textureAtlas"
                                                                                    , TEXT_IMAGES);
}