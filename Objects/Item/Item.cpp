#include "Item.h"
#include "../../Utility/InputControl.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

//int item_image;

Item::Item():item_animation_move()
{
	location = Vector2D(0, 0);
	velocity = 0;

	start_x = 0;
	velocity = 0;

	ResourceManager* rm = ResourceManager::GetInstance();
	item_animation_move = rm->GetImages("Resource/image/Item/Item.png", 3, 3, 1, 100, 100);
	item_image = item_animation_move[0];
	/*item_image = LoadGraph("Resource/image/Item/Item.png");*/
}

Item::~Item()
{

}

void Item::Initialize()
{
	input = InputControl::GetInstance();
	collision.is_blocking = false;
	collision.object_type = eObjectType::item;
	collision.hit_object_type = { eObjectType::player };

	collision.radius = D_OBJECT_SIZE / 2.0f;

	z_layer = 5;
	box_size = Vector2D(32, 32);
}

void Item::Update(float delta_second)
{
	AnimeCount(delta_second);

}

void Item::Draw(const Vector2D& screen_offset) const
{
	float drawX = location.x + screen_offset.x;
	float drawY = location.y + screen_offset.y;

	DrawRotaGraph(drawX, drawY - 8, 1.0, 0.0, item_image, TRUE);

	DrawFormatString(640, 40, GetColor(255, 255, 255),
		"drawX: %.2f", drawX);
}

void Item::Finalize()
{

}

void Item::OnHitCollision(const GameObject* hit_object)
{
	if (hit_object->GetCollision().IsCheckHitTarget(eObjectType::player))
	{
		// プレイヤーに当たったときの処理
		printfDx("Player Hit!\n");
		delete_flag = true;
	}
}

const Vector2D& Item::GetLocation() const
{
	return location;
}

const Vector2D& Item::GetVelocity() const
{
	return velocity;
}

// 位置情報設定処理
void Item::SetLocation(const Vector2D& pos)
{
	GameObject::SetLocation(pos);
	start_x = pos.x;
}

void Item::AnimeCount(float delta_second)
{
	// 移動中のアニメーション
	item_animation_time += delta_second;
	if (item_animation_time >= 0.5f)
	{
		item_animation_time = 0.0f;
		item_animation_count++;
		if (item_animation_count >= 3)
		{
			item_animation_count = 0;
		}
		item_image = item_animation_move[item_animation_num[item_animation_count]];
	}
}