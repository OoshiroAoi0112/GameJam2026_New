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
	box_size = Vector2D(32, 50);
}

void Item::Update(float delta_second)
{
	AnimeCount(delta_second);
	collision.radius = box_size.x / 2;

	collision.point[0] = location + Vector2D(0, -box_size.y / 2 + collision.radius);
	collision.point[1] = location + Vector2D(0, box_size.y / 2 - collision.radius);
}

void Item::Draw(const Vector2D& screen_offset) const
{
	float drawX = location.x + screen_offset.x;
	float drawY = location.y + screen_offset.y;

	__super::Draw(screen_offset);

	DrawRotaGraph(drawX, drawY - 8, 1.0, 0.0, item_image, TRUE);

	DrawFormatString(
		1000, 70,
		GetColor(255, 255, 255),
		"enemu_location.x = %.2f",
		location.x
	);

	DrawFormatString(
		1000, 100,
		GetColor(255, 255, 255),
		"ItemX = %.2f",
		drawX
	);

	// 当たり判定可視化
	Vector2D p0 = collision.point[0] + screen_offset;
	Vector2D p1 = collision.point[1] + screen_offset;

	// 上下の円
	DrawCircle(p0.x, p0.y, collision.radius, GetColor(0, 0, 255), FALSE);
	DrawCircle(p1.x, p1.y, collision.radius, GetColor(0, 0, 255), FALSE);

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