//#include "Camera.h"
//#include "Math.h"
//#define PI 3.14159265359
//
//Camera* Camera::GetInstance()
//{
//	static Camera instance;
//	return &instance;
//}
//
//Camera::Camera()
//{
//}
//
//Camera::~Camera()
//{
//}
//
//void Camera::Initialize(Input* input, DXInput* dxInput,Player* player)
//{
//	//引数から受け取ったデータを代入
//	this->input_ = input;
//	this->dxInput_ = dxInput;
//	this->player_ = player;
//
//	//射影変換
//	 matProjection_ = XMMatrixPerspectiveFovLH(
//		XMConvertToRadians(45.0f),			//上下画角45度
//		(float)window_width / window_height,//アスペクト比(画面横幅/画面立幅)
//		0.1f, 1000.0f						//前端、奥端
//	);
//
//	 //行列計算
//	 matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
//}
//
//
//void Camera::Update()
//{
//	homind();
//	//行列計算
//	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
//}
//
//void Camera::Update2()
//{
//	float x = 0;
//	float y = 0;
//	float z = 0;
//
//	//カメラをプレイヤーの真後ろに移動
//	x = player_->GetPosition1().x + (/*sin(-player_->GetRotation().x + (PI / 2) + lengthX_) **/ cos(-player_->GetRotation().y - (PI / 2) + lengthX_) * length_);
//	y = player_->GetPosition1().y + (cos(-player_->GetRotation().x + (PI * 18 / 40)) * length_);
//	z = player_->GetPosition1().z + (/*sin(-player_->GetRotation().x + (PI / 2) + lengthZ_) **/ sin(-player_->GetRotation().y - (PI / 2) + lengthZ_) * length_);
//
//
//	//天井を調整
//	if (sin(-player_->GetRotation().x + (PI / 2)) <= 0)
//	{
//		up_ = { 0,-1,0 };
//	}
//	else
//	{
//		up_ = { 0,1,0 };
//	}
//	up_ = { 0,1,0 };
//
//	//カメラの座標に代入
//	eye_ = { x,y,z };
//	//注視点をプレイヤーの座標にする
//	target_ = { player_->GetPosition1().x ,player_->GetPosition1().y,player_->GetPosition1().z };
//	//行列計算
//	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
//}
//
//void Camera::TitleUpdate()
//{
//	TitleHomind();
//	//行列計算
//	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
//}
//
//void Camera::MoveToGameUpdate()
//{
//	//タイマー始動
//	moveToGameTimer_++;
//
//	//時期が画面の外に出続けるまで架空の自機をホーミング
//	if (moveToGameTimer_ < 280)
//	{
//		TitleHomind();
//	}
//
//	if (moveToGameTimer_ >= 280 && moveToGameTimer_ <= 400)
//	{
//		target_.y += 8;
//		eye_.y += 7;
//	}
//
//	//行列計算
//	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
//}
//
//void Camera::Phase1RecollectionUpdate()
//{
//	//eyeの初期位置をセット
//	if (phase1RecollectionTimer_ == 0)
//	{
//		eye_ = { -100, -30, -80 };
//		target_ = { -30, 0, 0 };
//	}
//
//	phase1RecollectionTimer_++;
//
//	if (phase1RecollectionTimer_ < 480)
//	{
//		eye_.x += 0.4;
//		eye_.y += 0.2;
//		eye_.z -= 0.2;
//
//		target_.x += 0.1;
//	}
//
//	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
//}
//
//void Camera::GameClearUpdate()
//{
//	eye_.x += 0.1;
//	target_.x += 0.1;
//	eye_.y += 0.1;
//	target_.y += 0.1;
//	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
//}
//
//void Camera::homind()
//{
//	//左右
//	float addX = dxInput_->GamePad.state.Gamepad.sThumbRX / (32767.0f) * (PI / 90);
//	float moveRange = PI;
//	if (dxInput_->GamePad.state.Gamepad.sThumbRX > 15000 || dxInput_->GamePad.state.Gamepad.sThumbRX < -15000)
//	{
//		if (lengthX_ < moveRange && lengthX_ > -moveRange)
//		{
//			lengthX_ -= addX;
//			lengthZ_ -= addX;
//		}
//		if (lengthX_ > moveRange)
//		{
//			lengthX_ = moveRange - addX;
//			lengthZ_ = moveRange - addX;
//		}
//		if (lengthX_ < -moveRange)
//		{
//			lengthX_ = -moveRange - addX;
//			lengthZ_ = -moveRange - addX;
//		}
//	}
//	//ステックに触っていないときの処理
//	else if (lengthX_ != 0)
//	{
//		if (lengthX_ < -(PI / 90))
//		{
//			lengthX_ += (PI / 90);
//			lengthZ_ += (PI / 90);
//		}
//		else if (lengthX_ > (PI / 90))
//		{
//			lengthX_ -= (PI / 90);
//			lengthZ_ -= (PI / 90);
//		}
//	}
//
//	float x = 0;
//	float y = 0;
//	float z = 0;
//
//	//カメラをプレイヤーの真後ろに移動
//	x = player_->GetPosition1().x + (/*sin(-player_->GetRotation().x + (PI / 2) + lengthX_) **/ cos(-player_->GetRotation().y - (PI / 2) + lengthX_) * length_);
//	y = player_->GetPosition1().y + (cos(-player_->GetRotation().x + (PI * 18 / 40)) * length_);
//	z = player_->GetPosition1().z + (/*sin(-player_->GetRotation().x + (PI / 2) + lengthZ_) **/ sin(-player_->GetRotation().y - (PI / 2) + lengthZ_) * length_);
//
//
//	//天井を調整
//	if (sin(-player_->GetRotation().x + (PI / 2)) <= 0)
//	{
//		up_ = { 0,-1,0 };
//	}
//	else
//	{
//		up_ = { 0,1,0 };
//	}
//	up_ = { 0,1,0 };
//
//	//カメラの座標に代入
//	eye_ = { x,y,z };
//	//注視点をプレイヤーの座標にする
//	target_ = { player_->GetPosition1().x ,player_->GetPosition1().y,player_->GetPosition1().z };
//}
//
//void Camera::TitleHomind()
//{
//	//左右
//	float addX = dxInput_->GamePad.state.Gamepad.sThumbRX / (32767.0f) * (PI / 90);
//	float moveRange = PI / 3;
//	if (dxInput_->GamePad.state.Gamepad.sThumbRX > 15000 || dxInput_->GamePad.state.Gamepad.sThumbRX < -15000)
//	{
//		if (lengthX_ < moveRange && lengthX_ > -moveRange)
//		{
//			lengthX_ -= addX;
//			lengthZ_ -= addX;
//		}
//		if (lengthX_ > moveRange)
//		{
//			lengthX_ = moveRange - addX;
//			lengthZ_ = moveRange - addX;
//		}
//		if (lengthX_ < -moveRange)
//		{
//			lengthX_ = -moveRange - addX;
//			lengthZ_ = -moveRange - addX;
//		}
//	}
//	//ステックに触っていないときの処理
//	else if (lengthX_ != 0)
//	{
//		if (lengthX_ < -(PI / 90))
//		{
//			lengthX_ += (PI / 90);
//			lengthZ_ += (PI / 90);
//		}
//		else if (lengthX_ > (PI / 90))
//		{
//			lengthX_ -= (PI / 90);
//			lengthZ_ -= (PI / 90);
//		}
//	}
//
//	float x = 0;
//	float y = 0;
//	float z = 0;
//
//	//カメラをプレイヤーの真後ろに移動
//	x = player_->GetPosition1().x + (/*sin(-player_->GetRotation().x + (PI / 2) + lengthX_) **/ cos(-player_->GetRotation().y - (PI * 0.8) + lengthX_) * titleLength_);
//	y = player_->GetPosition1().y + (cos(-player_->GetRotation().x + (PI * 15 / 40)) * titleLength_);
//	z = player_->GetPosition1().z + (/*sin(-player_->GetRotation().x + (PI / 2) + lengthZ_) **/ sin(-player_->GetRotation().y - (PI * 0.8) + lengthZ_) * titleLength_);
//
//
//	//天井を調整
//	if (sin(-player_->GetRotation().x + (PI / 2)) <= 0)
//	{
//		up_ = { 0,-1,0 };
//	}
//	else
//	{
//		up_ = { 0,1,0 };
//	}
//	up_ = { 0,1,0 };
//
//	//カメラの座標に代入
//	eye_ = { x,y,z };
//	//注視点をプレイヤーの座標にする
//	target_ = { player_->GetPosition1().x ,player_->GetPosition1().y,player_->GetPosition1().z };
//}
//
//void Camera::SetTarget(XMFLOAT3 pos)
//{
//	target_ = pos;
//}
//
//void Camera::SetEye(XMFLOAT3 pos)
//{
//	eye_ = pos;
//}
//
//void Camera::SetGameClear()
//{
//	eye_ = { -60,20,-150 };
//	target_ = { -20,0,0 };
//}
