#include "Precompiled.h"
#include "Animator.h"

using namespace CEngine;
using namespace CEngine::Graphics;
using namespace CEngine::Math;

void BlendNode::PlayAnimation(ModelID id, int clipIndex, bool looping)
{
	mModelID = id;
	mClipIndex = clipIndex;
	mLooping = looping;
	mAnimationTick = 0.0f;
}

void BlendNode::Update(float deltaTime)
{
	auto model = ModelManager::Get()->GetModel(mModelID);
	const auto& animClip = model->animationClips[mClipIndex];
	mAnimationTick += animClip.tickDuration * deltaTime;
	if (mAnimationTick > animClip.tickDuration)
	{
		if (mLooping && animClip.tickDuration > 0.0f)
		{
			while (mAnimationTick > animClip.tickDuration)
			{
				mAnimationTick -= animClip.tickDuration;
			}
		}
		else
		{
			mAnimationTick = animClip.tickDuration;
		}
	}
}

bool BlendNode::GetToParentTransfore(const Bone* bone, Transform& toParentTransform) const
{
	toParentTransform = Transform();
	auto model = ModelManager::Get()->GetModel(mModelID);
	const auto& animClip = model->animationClips[mClipIndex];
	auto& animation = animClip.boneAnimations[bone->index];
	if (animation == nullptr)
	{
		return false;
	}

	toParentTransform = animation->GetTransform(mAnimationTick);
	return true;
}

void Animator::Initialize(ModelID id)
{
	mModelID = id;
}

void Animator::PlayAnimation(int clipIndex, bool looping, float blendDuration)
{
	auto model = ModelManager::Get()->GetModel(mModelID);
	ASSERT(clipIndex < model->animationClips.size(), "Animator -- Invaild clip index");

	auto& animClip = model->animationClips[clipIndex];
	if (blendDuration > 0.0f)
	{
		mNextClipIndex = clipIndex;
		mBlendDuration = blendDuration;
		mBlendTime = 0.0f;
		mNextAnim.PlayAnimation(mModelID, clipIndex, looping);
	}
	else
	{
		mClipIndex = clipIndex;
		mNextClipIndex = -1;
		mBlendDuration = 0.0f;
		mCurrentAnim.PlayAnimation(mModelID, clipIndex, looping);
	}
}

void Animator::Update(float deltaTime)
{
	mCurrentAnim.Update(deltaTime);
	if (mNextClipIndex > -1)
	{
		mNextAnim.Update(deltaTime);
		mBlendTime += deltaTime;
		mBlendTime = mBlendDuration * 0.5f;
		if (mBlendTime >= mBlendDuration)
		{
			PlayAnimation(mNextClipIndex, mNextAnim.IsLooping());
		}
	}
}

bool Animator::IsFinished()
{
	if (mCurrentAnim.IsLooping())
	{
		return false;
	}

	auto model = ModelManager::Get()->GetModel(mModelID);
	const auto& animClip = model->animationClips[mClipIndex];
	return animClip.tickDuration <= mCurrentAnim.GetAnimationTick();
}

size_t Animator::GetAnimationCount() const
{
	auto model = ModelManager::Get()->GetModel(mModelID);
	return model->animationClips.size();
}

Math::Matrix4 Animator::GetToParentTransfore(const Bone* bone) const
{
	Transform fromTransform, toTransform;
	if (mCurrentAnim.GetToParentTransfore(bone, fromTransform))
	{
		if (mNextClipIndex != -1)
		{
			float t = Math::Clamp(mBlendTime / mBlendDuration, 0.0f, 1.0f);
			if (mNextAnim.GetToParentTransfore(bone, toTransform))
			{
				Transform blendtransform;
				blendtransform.position = Math::Lerp(fromTransform.position, toTransform.position, t);
				blendtransform.rotation = Math::Quaternion::Slerp(fromTransform.rotation, toTransform.rotation, t);
				blendtransform.scale = Math::Lerp(fromTransform.scale, toTransform.scale, t);

				return blendtransform.GetMatrix4();
			}
		}
		return fromTransform.GetMatrix4();
	}
	return bone->toParentTransform;
}

const Model* Animator::GetModel() const
{
	return ModelManager::Get()->GetModel(mModelID);
}

const AnimationClip& Animator::GetAnimClip() const
{
	auto model = ModelManager::Get()->GetModel(mModelID);
	return model->animationClips[mClipIndex];
}