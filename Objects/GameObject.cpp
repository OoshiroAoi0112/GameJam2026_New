#include "GameObject.h"
#include "DxLib.h"

GameObject::GameObject()
	: owner_scene(nullptr)
	, location(0.0f)
	, graphic_images(NULL)
	, flip_flag(false)
	, delete_flag(false)
	, mobility(eMobilityType::Stationary) // mobility を初期化
	, z_layer(0)               // z_layer を初期化
{

}

GameObject::~GameObject()
{
	// 自身の終了処理
	this->Finalize();
}

void GameObject::Initialize()
{

}

void GameObject::Update(float delta_second)
{

}

void GameObject::Draw(const Vector2D& screen_offset) const
{
	Vector2D draw_pos;
	draw_pos.x = location.x + screen_offset.x;
	draw_pos.y = location.y + screen_offset.y;

	DrawGraph(
		static_cast<int>(draw_pos.x),
		static_cast<int>(draw_pos.y),
		image,
		TRUE
	);
}

void GameObject::Finalize()
{

}

void GameObject::OnHitCollision(GameObject* hit_object)
{
}

void GameObject::PostCollision(float delta_second)
{
}

Vector2D& GameObject::GetLocation()
{
	// TODO: return ステートメントをここに挿入します
	return location;
}

const CapsuleCollision& GameObject::GetCollision() const
{
	// TODO: return ステートメントをここに挿入します
	return collision;
}

Vector2D GameObject::GetBoxSize() const
{
	return this->box_size;
}

const int GameObject::GetZLayer() const
{
	return 0;
}

const eMobilityType GameObject::GetMobility() const
{
	return eMobilityType();
}

//void GameObject::SetLocation(const Vector2D& location)
//{
//	this->location = location;
//}

void GameObject::SetOwnerScene(SceneBase* scene)
{
	this->owner_scene = scene;
}

const bool GameObject::GetDeleteFlag() const
{
	return false;
}
