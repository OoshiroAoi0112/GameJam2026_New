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
	//オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, graphic_images, TRUE, this->flip_flag);
}

void GameObject::Finalize()
{

}

void GameObject::OnHitCollision(const GameObject* hit_object)
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
