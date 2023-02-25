#pragma once

enum class EResponseType
{
	ERT_Ignore, ERT_Overlap, ERT_Block
};

enum class EObjectTypes
{
	EOT_Character, EOT_StaticObject, EOT_Projectile, EOT_DynamicObject, EOT_InteractiveObject, EOT_Pawn
};

enum class ERaycastTypes
{
	ERT_Character, ERT_StaticObject, ERT_Visible
};